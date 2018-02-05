#include <cmath>
#include "NyaDevice.h"
#include "NyaEffect.h"
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

	nya_effect_ = new NyaEffect;
	nya_position_ = new NyaPosition;
	set_effect_.first = false;
	get<0>(set_graphic_) = false;

	// 弾オブジェクトの最大個数は10000個
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
	delete nya_effect_;
	delete nya_position_;
}

void NyaDevice::Attack(DevicePropertyX* dpx)
{
	eOBJECT::GROUP object_group;
	list<Bullet>::iterator it;

	// 弾オブジェクトが最大個数まで生成されているときは何もしない
	if (wait_list_.begin() == wait_list_.end())
		return;
	
	it = wait_list_.begin();
	it->device_setting_id_ = dpx->device_setting_id_;
	it->draw_angle_ = dpx->draw_angle_;
	it->move_angle_  = AngleToRad(dpx->move_angle_);
	it->move_x_ = cos(it->move_angle_) * dpx->move_speed_;
	it->move_y_ = sin(it->move_angle_) * dpx->move_speed_;
	it->phx_->health_max_ = 1;
	it->phx_->health_now_ = 1;
	it->phx_->grid_x_ = dpx->create_x_;
	it->phx_->grid_y_ = dpx->create_y_;
	it->set_effect_.first = set_effect_.first;
	it->set_effect_.second = set_effect_.second;
	get<0>(it->set_graphic_) = get<0>(set_graphic_);
	get<1>(it->set_graphic_) = get<1>(set_graphic_);
	get<2>(it->set_graphic_) = get<2>(set_graphic_);

	object_group = setting_vector_[dpx->device_setting_id_].object_group_;
	wait_list_.splice(attack_list_[object_group].begin(), wait_list_, it);
}

void NyaDevice::Run(void)
{
	for (int group = eOBJECT::GROUP::enum_zero; group != eOBJECT::GROUP::sizeof_enum; group++)
		Calculate((eOBJECT::GROUP)group);
}

void NyaDevice::SetEffect(int effect_setting_id)
{
	set_effect_.first = true;
	set_effect_.second = effect_setting_id;
}

void NyaDevice::SetGraphic(int graphic_file_id, int graphic_file_div)
{
	get<0>(set_graphic_) = true;
	get<1>(set_graphic_) = graphic_file_id;
	get<2>(set_graphic_) = graphic_file_div;
}

int NyaDevice::LoadSetting(DeviceSetting* setting)
{
	setting_vector_.push_back(*setting);

	return ((int)setting_vector_.size() - 1);
}

void NyaDevice::Calculate(eOBJECT::GROUP group)
{
	EffectPropertyX epx;
	GraphicPropertyX4 gpx4;
	tuple<int, int, int> color = make_tuple(255, 255, 255);
	list<Bullet>::iterator it_delete;

	///////////////
	// 削除処理
	///////////////
	for (list<Bullet>::iterator it = attack_list_[group].begin(); it != attack_list_[group].end(); ++it) {

		// 表示領域の限界を超えた
		// 他のオブジェクトと衝突するなどして弾オブジェクトのヘルスがゼロになった
		if ((int)it->phx_->grid_x_ < 0 || 1000 < (int)it->phx_->grid_x_ || (int)it->phx_->grid_y_ < 0 || 700 < (int)it->phx_->grid_y_) {
		
			it_delete = --it;
			attack_list_[group].splice(wait_list_.begin(), attack_list_[group], ++it_delete);

		} else if (it->phx_->health_now_ <= 0) {

			// エフェクト描画処理
			if (it->set_effect_.first) {
				epx.grid_x_ = (int)it->phx_->grid_x_;
				epx.grid_y_ = (int)it->phx_->grid_y_;
				epx.setting_id_ = it->set_effect_.second;
				nya_effect_->Draw(&epx);
			}

			it_delete = --it;
			attack_list_[group].splice(wait_list_.begin(), attack_list_[group], ++it_delete);
		}
	}

	////////////////////
	// 削除以外の処理
	////////////////////
	gpx4.flag_trans_ = true;
	gpx4.flag_turn_ = false;
	for (list<Bullet>::iterator it = attack_list_[group].begin(); it != attack_list_[group].end(); ++it) {

		// 描画処理
		if (get<0>(it->set_graphic_)) {
			gpx4.draw_angle_ = it->draw_angle_;
			gpx4.draw_angle_ += setting_vector_[it->device_setting_id_].draw_rotate_;
			gpx4.extend_rate_ = setting_vector_[it->device_setting_id_].draw_extend_;
			gpx4.file_div_ = get<2>(it->set_graphic_);
			gpx4.file_id_ = get<1>(it->set_graphic_);
			gpx4.object_group_ = setting_vector_[it->device_setting_id_].object_group_;
			gpx4.pos_cx_ = (int)it->phx_->grid_x_;
			gpx4.pos_cy_ = (int)it->phx_->grid_y_;
			nya_graphic_->Draw(&gpx4);
		}

		// 衝突判定処理
		it->phx_->collision_pow_ = setting_vector_[it->device_setting_id_].collision_pow_;
		it->phx_->collision_range_ = setting_vector_[it->device_setting_id_].collision_range_;
		nya_position_->Collision(it->phx_, group);

		// 移動処理
		it->phx_->grid_x_pre_ = it->phx_->grid_x_;
		it->phx_->grid_y_pre_ = it->phx_->grid_y_;
		it->phx_->grid_x_ += it->move_x_;
		it->phx_->grid_y_ += it->move_y_;
	}
}


