#include <cmath>
#include "NyaDevice.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaString.h"

using namespace H2NLIB;
using namespace std;

std::vector<DeviceSetting> NyaDevice::setting_vector_;
list<Bullet> NyaDevice::attack_list_[eOBJECT::GROUP::sizeof_enum];
list<Bullet> NyaDevice::wait_list_;


NyaDevice::NyaDevice()
{
	static bool first_call = true;

	nya_position_ = new NyaPosition;

	if (first_call) {
		wait_list_.resize(10000);
		for (auto it = wait_list_.begin(); it != wait_list_.end(); ++it) {
			it->phx_ = nya_position_->Create();
		}
		first_call = false;
	}
}


NyaDevice::~NyaDevice()
{
	delete nya_position_;
}

void NyaDevice::Attack(DevicePropertyX* dpx)
{
	eOBJECT::GROUP object_group;
	list<Bullet>::iterator it;

	if (wait_list_.begin() == wait_list_.end())
		return;
	
	it = wait_list_.begin();
	it->draw_angle_ = dpx->draw_angle_;
	it->move_angle_  = AngleToRad(dpx->move_angle_);
	it->move_x_ = cos(it->move_angle_) * dpx->move_speed_;
	it->move_y_ = sin(it->move_angle_) * dpx->move_speed_;
	it->phx_->health_max_ = 1;
	it->phx_->health_now_ = 1;
	it->phx_->x_ = dpx->create_x_;
	it->phx_->y_ = dpx->create_y_;
	it->setting_id_ = dpx->setting_id_;

	object_group = setting_vector_[dpx->setting_id_].object_group_;
	wait_list_.splice(attack_list_[object_group].begin(), wait_list_, it);
}

void NyaDevice::Run(void)
{
	Calculate(eOBJECT::GROUP::USER_ATTACK1);
	Calculate(eOBJECT::GROUP::TARGET_ATTACK1);
}

int NyaDevice::LoadSetting(DeviceSetting* setting)
{
	setting_vector_.push_back(*setting);

	return ((int)setting_vector_.size() - 1);
}

void NyaDevice::Calculate(eOBJECT::GROUP group)
{
	GraphicPropertyX4 gpx4;
	tuple<int, int, int> color = make_tuple(255, 255, 255);
	list<Bullet>::iterator it_delete;

	///////////////
	// 削除処理
	///////////////
	for (list<Bullet>::iterator it = attack_list_[group].begin(); it != attack_list_[group].end(); ++it) {

		// 表示サイズの境界を超えた
		if ((int)it->phx_->x_ < 0 || 1000 < (int)it->phx_->x_ || (int)it->phx_->y_ < 0 || 700 < (int)it->phx_->y_) {
			it_delete = --it;
			attack_list_[group].splice(wait_list_.begin(), attack_list_[group], ++it_delete);
		}
		// オブジェクトと衝突するなどして弾オブジェクトのヘルスがゼロになった
		if (it->phx_->health_now_ <= 0) {
			it_delete = --it;
			attack_list_[group].splice(wait_list_.begin(), attack_list_[group], ++it_delete);
		}
	}

	////////////////////
	// 色々な処理
	////////////////////
	gpx4.flag_trans_ = true;
	gpx4.flag_turn_ = false;
	for (list<Bullet>::iterator it = attack_list_[group].begin(); it != attack_list_[group].end(); ++it) {

		// 描画処理
		gpx4.draw_angle_ = it->draw_angle_;
		gpx4.draw_angle_ += setting_vector_[it->setting_id_].graphic_draw_rotate_;
		gpx4.extend_rate_ = setting_vector_[it->setting_id_].graphic_draw_extend_;
		gpx4.file_div_ = setting_vector_[it->setting_id_].graphic_file_div_;
		gpx4.file_id_ = setting_vector_[it->setting_id_].graphic_file_id_;
		gpx4.object_group_ = setting_vector_[it->setting_id_].object_group_;
		gpx4.pos_cx_ = (int)it->phx_->x_;
		gpx4.pos_cy_ = (int)it->phx_->y_;
		nya_graphic_->Draw(&gpx4);

		// 衝突判定処理
		it->phx_->pow_ = setting_vector_[it->setting_id_].position_collide_pow_;
		it->phx_->range_ = setting_vector_[it->setting_id_].position_collide_range_;
		nya_position_->Collision(it->phx_, group);

		// 移動処理
		it->phx_->x_pre_ = it->phx_->x_;
		it->phx_->y_pre_ = it->phx_->y_;
		it->phx_->x_ += it->move_x_;
		it->phx_->y_ += it->move_y_;
	}
}
