#include <cmath>
#include <deque>
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;

#define DEVICE_OBJECT_MAX 10000

std::vector<DeviceOption> NyaDevice::option_vector_;
list<Gadget> NyaDevice::attack_list_[eOBJECT::NUM::sizeof_enum];
list<Gadget> NyaDevice::wait_list_;




NyaDevice::NyaDevice()
{
	DeviceOption default_option;
	static bool first_call = true;

	nya_effect_ = new NyaEffect;
	nya_position_ = new NyaPosition;

	set_effect_pair_.first = false;
	set_graphic_pair_.first = false;

	// 弾オブジェクトの最大個数は10000個
	if (first_call) {
		NewOption(&default_option);
		wait_list_.resize(DEVICE_OBJECT_MAX);
		for (auto& it : wait_list_) {
			it.effect_pair_.first = false;
			it.graphic_pair_.first = false;
			it.phx_ = nya_position_->Create();
		}
		first_call = false;
	}
}


NyaDevice::~NyaDevice()
{
	delete nya_effect_;
	delete nya_position_;
}

/**
@brief 攻撃関数
@param dpx プロパティ
@note
 弾オブジェクトの最大個数は10000個。
**/
void NyaDevice::Attack(DevicePropertyX* dpx, int option_index)
{
	static list<Gadget>::iterator it;

	// 弾オブジェクトが最大個数まで生成されているときは何もしない
	if (wait_list_.begin() == wait_list_.end())
		return;
	
	it = wait_list_.begin();
	it->device_option_index_ = option_index;
	it->draw_angle_ = option_vector_[option_index].draw_angle_;
	it->effect_pair_ = set_effect_pair_;
	it->graphic_pair_ = set_graphic_pair_;
	it->move_angle_  = AngleToRad(dpx->move_angle_);
	it->move_x_ = cos(it->move_angle_) * dpx->move_speed_;
	it->move_y_ = sin(it->move_angle_) * dpx->move_speed_;
	it->phx_->collision_hit_ = false;
	it->phx_->collision_pow_ = option_vector_[option_index].collision_pow_;
	it->phx_->collision_range_ = option_vector_[option_index].collision_range_;
	it->phx_->health_max_ = 1.0;
	it->phx_->health_now_ = 1.0;
	it->phx_->grid_x_ = dpx->create_x_;
	it->phx_->grid_y_ = dpx->create_y_;

	attack_list_[dpx->object_group_].splice(attack_list_[dpx->object_group_].begin(), move(wait_list_), it);
}

void NyaDevice::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (int group = eOBJECT::NUM::enum_zero; group != eOBJECT::NUM::sizeof_enum; group++)
		Calculate((eOBJECT::NUM)group);


	NyaString::Write("debug_font", white, 50, 190, "[50, 190] attack list size = %d", (int)attack_list_[eOBJECT::NUM::USER_ATTACK1].size());
	NyaString::Write("debug_font", white, 50, 210, "[50, 210] wait list size = %d", (int)wait_list_.size());
}

void NyaDevice::SetEffect(string file_pass, int div_x, int div_y, int animation_div_max, int animation_interval_time, eOBJECT::NUM object_group)
{
	set_effect_pair_.first = true;
	set_effect_pair_.second.animation_div_max_ = animation_div_max;
	set_effect_pair_.second.animation_interval_time_ = animation_interval_time;
	set_effect_pair_.second.file_id_ = nya_effect_->LoadFile(div_x, div_y, file_pass);
	set_effect_pair_.second.object_group_ = object_group;
	set_effect_pair_.second.effect_option_index_ = 0;
}

void NyaDevice::SetEffect(std::string file_pass, int div_x, int div_y, int animation_div_max, int animation_interval_time, eOBJECT::NUM object_group, double draw_angle, double draw_extend_, double draw_move_x_, double draw_move_y_)
{
	EffectOption option;

	set_effect_pair_.first = true;
	set_effect_pair_.second.animation_div_max_ = animation_div_max;
	set_effect_pair_.second.animation_interval_time_ = animation_interval_time;
	set_effect_pair_.second.file_id_ = nya_effect_->LoadFile(div_x, div_y, file_pass);
	set_effect_pair_.second.object_group_ = object_group;
	option.draw_angle_ = draw_angle;
	option.draw_extend_ = draw_extend_;
	option.draw_move_x_ = draw_move_x_;
	option.draw_move_y_ = draw_move_y_;
	set_effect_pair_.second.effect_option_index_ = nya_effect_->NewOption(&option);
}

void NyaDevice::SetGraphic(string file_pass)
{
	set_graphic_pair_.first = true;
	set_graphic_pair_.second.file_div_ = 0;
	set_graphic_pair_.second.file_id_ = nya_graphic_->LoadFile(file_pass);
}

int NyaDevice::NewOption(DeviceOption* setting)
{
	if (option_vector_.size() == INT_MAX)
		return -1;

	option_vector_.push_back(*setting);

	return ((int)option_vector_.size() - 1);
}


void NyaDevice::Calculate(eOBJECT::NUM group)
{
	static EffectPropertyX epx;
	static GraphicPropertyX4 gpx4;
	static deque<list<Gadget>::iterator> delete_deque;


	///////////////
	// 削除処理
	///////////////
	for (auto it = attack_list_[group].begin(); it != attack_list_[group].end(); ++it)
	{
		// 表示領域の限界を超えた
		// 他のオブジェクトと衝突した
		if ((int)it->phx_->grid_x_ < 0 || 1000 < (int)it->phx_->grid_x_ ||
			(int)it->phx_->grid_y_ < 0 || 700 < (int)it->phx_->grid_y_)
		{
			delete_deque.push_back(it);
		}
		else if (it->phx_->collision_hit_)
		{
			// エフェクト描画処理
			if (it->effect_pair_.first)
			{
				epx.animation_div_max_ = it->effect_pair_.second.animation_div_max_;
				epx.animation_interval_time_ = set_effect_pair_.second.animation_interval_time_;
				epx.file_id_ = set_effect_pair_.second.file_id_;
				epx.grid_x_ = (int)it->phx_->grid_x_;
				epx.grid_y_ = (int)it->phx_->grid_y_;
				epx.object_group_ = set_effect_pair_.second.object_group_;
				nya_effect_->Draw(&epx, set_effect_pair_.second.effect_option_index_);
			}
			delete_deque.push_back(it);
		}
	}

	while (!delete_deque.empty())
	{
		wait_list_.splice(wait_list_.begin(), move(attack_list_[group]), delete_deque.front());
		delete_deque.pop_front();
	}


	////////////////////
	// 削除以外の処理
	////////////////////
	gpx4.flag_trans_ = true;
	gpx4.flag_turn_ = false;
	for (auto& it : attack_list_[group])
	{

		// 描画処理
		if (it.graphic_pair_.first)
		{
			gpx4.draw_angle_ = it.draw_angle_;
			it.draw_angle_ += option_vector_[it.device_option_index_].draw_rotate_;
			gpx4.extend_rate_ = option_vector_[it.device_option_index_].draw_extend_;
			gpx4.file_div_ = it.graphic_pair_.second.file_div_;
			gpx4.file_id_ = it.graphic_pair_.second.file_id_;
			gpx4.object_group_ = group;
			gpx4.pos_cx_ = (int)it.phx_->grid_x_;
			gpx4.pos_cy_ = (int)it.phx_->grid_y_;
			nya_graphic_->Draw(&gpx4);
		}

		// 衝突判定処理
		it.phx_->collision_pow_ = option_vector_[it.device_option_index_].collision_pow_;
		it.phx_->collision_range_ = option_vector_[it.device_option_index_].collision_range_;
		nya_position_->Collision(it.phx_, group);

		// 移動処理
		it.phx_->grid_x_pre_ = it.phx_->grid_x_;
		it.phx_->grid_y_pre_ = it.phx_->grid_y_;
		it.phx_->grid_x_ += it.move_x_;
		it.phx_->grid_y_ += it.move_y_;
	}
}


