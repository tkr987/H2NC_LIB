#include <cmath>
#include "NyaAttack.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaString.h"

using namespace H2NLIB;
using namespace std;


list<Bullet> NyaAttack::create_list_[eOBJECT::GROUP::sizeof_enum];
list<Bullet> NyaAttack::wait_list_;


NyaAttack::NyaAttack()
{
	static bool first_call = true;

	gpx4_bullet_ = new GraphicPropertyX4;
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
	delete gpx4_bullet_;
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
	it->move_angle_  = AngleToRad(apx->move_angle_);
	it->move_x_ = cos(it->move_angle_) * apx->move_speed_;
	it->move_y_ = sin(it->move_angle_) * apx->move_speed_;
	it->ppx_->x_ = apx->create_x_;
	it->ppx_->y_ = apx->create_y_;

	wait_list_.splice(create_list_[it->ppx_->object_group_].begin(), wait_list_, it);
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
		it->ppx_->x_ += it->move_x_;
		it->ppx_->y_ += it->move_y_;
		//nya_position_->Collide(it->ppx_);
		gpx4_bullet_->draw_angle_ = (int)it->draw_angle_;
		gpx4_bullet_->pos_cx_ = (int)it->ppx_->x_;
		gpx4_bullet_->pos_cy_ = (int)it->ppx_->y_;
		nya_graphic_->Draw(gpx4_bullet_);

		//if ((int)it->ppx_->x_ < it->limit_min_x_ || it->limit_max_x_ < (int)it->ppx_->x_ || 
		//	(int)it->ppx_->y_ < it->limit_min_y_ || it->limit_max_y_ < (int)it->ppx_->y_) {

		//	it_delete = --it;
		//	create_list_[group].splice(wait_list_.begin(), create_list_[group], ++it_delete);
		//}

		count++;
	}
	nya_string_->Write("attack", color, 400, 400, "attack-count=%d", count);
}


void NyaAttack::SettingBullet(eOBJECT::GROUP object_group, double pow, double range, int limit_min_x, int limit_max_x, int limit_min_y, int limit_max_y)
{
	for (auto it = wait_list_.begin(); it != wait_list_.end(); ++it) {
		it->limit_min_x_ = limit_min_x;
		it->limit_max_x_ = limit_max_x;
		it->limit_min_y_ = limit_min_y;
		it->limit_max_y_ = limit_max_y;
		it->ppx_->object_group_ = object_group;
		it->ppx_->pow_ = pow;
		it->ppx_->range_ = range;
	}
}

/**
 衝突判定設定関数
 @param collision_type 衝突判定処理の種類
 @param group1 セットする値１
 @param group2 セットする値２
 @note
 どのオブジェクトグループ同士で衝突判定処理をするのか設定するために使用する関数。
 衝突判定処理の種類は
 1 三平方の衝突判定処理
 2 簡略化された高速衝突判定処理
 例えば、eOBJECT::GROUP::USERとeOBJECT::GROUP::TARGET_ATTACKを引数で指定しておけば、
 NyaPosition::Run()にてUSERとTARGET_ATTACKのオブジェクト同士の衝突判定を実行するようになる。
 なお、NyaPosision::SettingCollision()でも同様の設定をすることが可能。
**/
void NyaAttack::SettingCollision(int collision_type, eOBJECT::GROUP group1, eOBJECT::GROUP group2)
{
	nya_position_->SettingCollision(collision_type, group1, group2);
}


void NyaAttack::SettingEffect(void)
{


}

void NyaAttack::SettingGraphic(eOBJECT::GROUP object_group, int file_id, int file_div, double extend_rate, bool flag_trans, bool flag_turn)
{
	for (auto it = wait_list_.begin(); it != wait_list_.end(); ++it) {
		gpx4_bullet_->extend_rate_ = extend_rate;
		gpx4_bullet_->file_div_ = file_div;
		gpx4_bullet_->file_id_ = file_id;
		gpx4_bullet_->flag_trans_ = flag_trans;
		gpx4_bullet_->flag_turn_ = flag_turn;
		gpx4_bullet_->object_group_ = object_group;
	}
}

