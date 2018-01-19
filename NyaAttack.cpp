#include <cmath>
#include "NyaAttack.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaString.h"

using namespace H2NLIB;
using namespace std;


list<Bullet> NyaAttack::create_list_[eOBJECT::GROUP::sizeof_enum];
list<Bullet> NyaAttack::wait_list_;

NyaString* NyaAttack::nya_string_;

NyaAttack::NyaAttack()
{
	static bool first_call = true;

	gpx4_setting_graphic_ = new GraphicPropertyX4;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
	nya_string_ = new NyaString;

	if (first_call) {
		nya_string_->SettingFont("attack", 15, 2);
		first_call = false;
	}
}


NyaAttack::~NyaAttack()
{
	delete gpx4_setting_graphic_;
	delete nya_graphic_;
	delete nya_position_;
	delete nya_string_;
}

void NyaAttack::Create(AttackPropertyX* apx)
{
	list<Bullet>::iterator it;

	if (wait_list_.begin() == wait_list_.end())
		return;
	
	it = wait_list_.begin();
	it->draw_angle_ = apx->graphic_angle_;
	it->draw_rotate_ = 0;
	it->limit_max_x_ = 1200;
	it->limit_max_y_ = 800;
	it->limit_min_x_ = 0;
	it->limit_min_y_ = 0;
	it->move_angle_  = AngleToRad(apx->move_angle_);
	it->move_x_ = cos(it->move_angle_) * apx->move_speed_;
	it->move_y_ = sin(it->move_angle_) * apx->move_speed_;
	it->ppx_->x_ = apx->create_x_;
	it->ppx_->y_ = apx->create_y_;

	wait_list_.splice(create_list_[setting_group_].begin(), wait_list_, it);
}


void NyaAttack::Init(int size)
{
	wait_list_.resize(size);
	for (auto it = wait_list_.begin(); it != wait_list_.end(); ++it) {
		it->ppx_ = nya_position_->Create();
		it->ppx_->health_max_ = 1;
		it->ppx_->health_now_ = 1;
	}
}

void NyaAttack::Run(void)
{
	Calculate(eOBJECT::GROUP::USER_ATTACK1);
}

void NyaAttack::Calculate(eOBJECT::GROUP group)
{
	int count = 0;
	tuple<int, int, int> color = make_tuple(255, 255, 255);
	list<Bullet>::iterator it_delete;

	for (auto it = create_list_[group].begin(); it != create_list_[group].end(); ++it) {

		// 移動処理＆衝突判定処理
		it->ppx_->x_ += it->move_x_;
		it->ppx_->y_ += it->move_y_;
		//nya_position_->Collide(it->ppx_);

		// NyaAttack::SettingGraphic()以外の項目の設定＆描画処理
		it->draw_angle_ += it->draw_rotate_;
		gpx4_setting_graphic_->draw_angle_ = 0;
		gpx4_setting_graphic_->extend_rate_ = 1.0;
		gpx4_setting_graphic_->flag_trans_ = true;
		gpx4_setting_graphic_->flag_turn_ = false;
		gpx4_setting_graphic_->object_group_ = eOBJECT::GROUP::USER_ATTACK1;
		gpx4_setting_graphic_->pos_cx_ = (int)it->ppx_->x_;
		gpx4_setting_graphic_->pos_cy_ = (int)it->ppx_->y_;
		nya_graphic_->Draw(gpx4_setting_graphic_);

		// 表示限界の画面サイズ
		if ((int)it->ppx_->x_ < it->limit_min_x_ || it->limit_max_x_ < (int)it->ppx_->x_ || 
			(int)it->ppx_->y_ < it->limit_min_y_ || it->limit_max_y_ < (int)it->ppx_->y_) {

			it_delete = --it;
			create_list_[group].splice(wait_list_.begin(), create_list_[group], ++it_delete);
		}

		count++;
	}

	nya_string_->Write("attack", color, 50, 70, "(50, 70) attack-count = %d", count);
}

void NyaAttack::SettingEffect(void)
{


}

void NyaAttack::SettingGraphic(int file_id, int file_div)
{
	gpx4_setting_graphic_->extend_rate_ = 1.0;
	gpx4_setting_graphic_->file_div_ = file_div;
	gpx4_setting_graphic_->file_id_ = file_id;
	gpx4_setting_graphic_->flag_trans_ = true;
	gpx4_setting_graphic_->flag_turn_ = false;
}

void NyaAttack::SettingGroup(eOBJECT::GROUP group)
{
	setting_group_ = group;
}
