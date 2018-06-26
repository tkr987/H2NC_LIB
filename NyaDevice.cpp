#include <cmath>
#include <deque>
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;


list<DeviceGadget14> NyaDevice::dg14_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget14> NyaDevice::dg14_wait_list_(DEVICE_GADGET_MAX_DEFAULT);
list<DeviceGadget1414> NyaDevice::dg1414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget1414> NyaDevice::dg1414_wait_list_(DEVICE_GADGET_MAX_DEFAULT);
list<DeviceGadget2414> NyaDevice::dg2414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget2414> NyaDevice::dg2414_wait_list_(DEVICE_GADGET_MAX_DEFAULT);

DeviceGadget14::DeviceGadget14()
{
	gadget_dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
		gadget_phandle_collection_[i] = new PositionHandle;
}

DeviceGadget14::~DeviceGadget14()
{
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}

DeviceGadget1414::DeviceGadget1414()
{
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
		gadget_phandle_collection_[i] = new PositionHandle;
}

DeviceGadget1414::~DeviceGadget1414()
{
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}


H2NLIB::DeviceGadget2414::DeviceGadget2414()
{
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX2;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
		gadget_phandle_collection_[i] = new PositionHandle;
}

H2NLIB::DeviceGadget2414::~DeviceGadget2414()
{
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}

DevicePropertyX1::DevicePropertyX1()
{
	collision_power_ = 1;
	collision_range_ = 1;
	delay_time_frame_ = 0;
	draw_angle_deg_ = 0;
	move_angle_deg_ = 0;
	move_speed_ = 1;
}

DevicePropertyX2::DevicePropertyX2()
{
	collision_power_ = 1;
	collision_range_ = 1;
	delay_time_frame_ = 0;
	draw_angle_deg_ = 0;
	draw_angle_speed_deg_ = 0;
	move_angle_deg_ = 0;
	move_angle_speed_deg_ = 0;
	move_speed_ = 1;
}

/**
@brief 攻撃type14関数
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度
@note
 オブジェクトの最大個数は10000個。
 衝突判定の精度は[1-10]の値で指定、大きい値ほど高精度になる。
 それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される
**/
void NyaDevice::Attack14(const DevicePropertyX1* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type,  unsigned int collision_accuracy)
{
	static list<DeviceGadget14>::iterator it_from, it_to;

	// 最大個数まで生成されているときは何もしない
	if (dg14_wait_list_.begin() == dg14_wait_list_.end())
		return;

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = dg14_wait_list_.begin();
	it_from->clear_ = false;
	it_from->collision_accuracy_ = collision_accuracy;
	it_from->count_frame_ = 0;
	it_from->move_angle_deg_ = gadget_dpx->move_angle_deg_;
	it_from->move_angle_rad_ = AngleToRad(gadget_dpx->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_x_ /= collision_accuracy;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_y_ /= collision_accuracy;
	*it_from->gadget_dpx_ = *gadget_dpx;
	*it_from->gadget_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->gadget_phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->gadget_phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->gadget_phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->gadget_phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->gadget_phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->gadget_phandle_collection_[i]->health_ = 1;
	}

	it_to = dg14_attack_list_[static_cast<int>(gadget_type)].begin();
	dg14_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(dg14_wait_list_), it_from);
}

/**
@brief 攻撃type1414関数
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param effect_dpx エフェクト用デバイスプロパティ
@param effect_gpx エフェクト用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param effect_type エフェクトのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度
@note
 エフェクト付き攻撃関数。
 ガジェットの最大個数は10000個。
 衝突判定の精度は[1-10]の値で指定、大きい値ほど高精度になる。
 それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される。
**/
void NyaDevice::Attack1414(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget1414>::iterator it_from, it_to;

	// 最大個数まで生成されているときは何もしない
	if (dg1414_wait_list_.begin() == dg1414_wait_list_.end())
		return;

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = dg1414_wait_list_.begin();
	it_from->clear_ = false;
	it_from->collision_accuracy_ = collision_accuracy;
	it_from->count_frame_ = 0;
	it_from->effect_type_ = effect_type;
	it_from->move_angle_deg_ = gadget_dpx->move_angle_deg_;
	it_from->move_angle_rad_ = AngleToRad(gadget_dpx->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_x_ /= collision_accuracy;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_y_ /= collision_accuracy;
	*it_from->effect_epx_ = *effect_epx;
	*it_from->effect_gpx_ = *effect_gpx;
	*it_from->gadget_dpx_ = *gadget_dpx;
	*it_from->gadget_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->gadget_phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->gadget_phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->gadget_phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->gadget_phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->gadget_phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->gadget_phandle_collection_[i]->health_ = 1;
	}
	it_to = dg1414_attack_list_[static_cast<int>(gadget_type)].begin();
	dg1414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(dg1414_wait_list_), it_from);
}

/**
@brief 攻撃type2414関数
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param effect_dpx エフェクト用デバイスプロパティ
@param effect_gpx エフェクト用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param effect_type エフェクトのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度
@note
 エフェクトと角速度を指定できる攻撃関数。
 ガジェットの最大個数は10000個。
 衝突判定の精度は[1-10]の値で指定、大きい値ほど高精度になる。
 それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される。
**/

void NyaDevice::Attack2414(const DevicePropertyX2* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget2414>::iterator it_from, it_to;

		// 最大個数まで生成されているときは何もしない
	if (dg2414_wait_list_.begin() == dg2414_wait_list_.end())
		return;

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = dg2414_wait_list_.begin();
	it_from->clear_ = false;
	it_from->collision_accuracy_ = collision_accuracy;
	it_from->count_frame_ = 0;
	it_from->effect_type_ = effect_type;
	it_from->move_angle_deg_ = gadget_dpx->move_angle_deg_;
	it_from->move_angle_rad_ = AngleToRad(gadget_dpx->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_x_ /= collision_accuracy;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_y_ /= collision_accuracy;
	*it_from->effect_epx_ = *effect_epx;
	*it_from->effect_gpx_ = *effect_gpx;
	*it_from->gadget_dpx_ = *gadget_dpx;
	*it_from->gadget_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->gadget_phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->gadget_phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->gadget_phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->gadget_phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->gadget_phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->gadget_phandle_collection_[i]->health_ = 1;
	}

	it_to = dg2414_attack_list_[static_cast<int>(gadget_type)].begin();
	dg2414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(dg2414_wait_list_), it_from);
}

/**
 @brief クリア関数
 @param type クリアするオブジェクトタイプ
 @note
  引数で指定したtypeのgadgetを全てクリアする
**/
void NyaDevice::Clear(eOBJECT type)
{
	for (auto& e : dg14_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : dg1414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : dg2414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
}


void NyaDevice::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (eOBJECT type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; ++type)
		CalculateGadget(type);


	NyaString::Write("debug_font", white, 50, 190, "[50, 190] attack list size = %d", 10000 - (int)dg1414_wait_list_.size());
	NyaString::Write("debug_font", white, 50, 210, "[50, 210] wait list size = %d", (int)dg1414_wait_list_.size());
}


void NyaDevice::CalculateGadget(eOBJECT type)
{
	GraphicPropertyX4 gp;
	deque<list<DeviceGadget14>::iterator> dg14_delete_deque;
	deque<list<DeviceGadget1414>::iterator> dg1414_delete_deque;
	deque<list<DeviceGadget2414>::iterator> dg2414_delete_deque;

	//***********************
	// Gadget14 削除処理
	//***********************
	for (auto it = dg14_attack_list_[static_cast<int>(type)].begin(); it != dg14_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			dg14_delete_deque.push_back(it);
		else if (it->clear_)
			dg14_delete_deque.push_back(it);
		else
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->gadget_phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					dg14_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!dg14_delete_deque.empty())
	{
		dg14_wait_list_.splice(dg14_wait_list_.begin(), move(dg14_attack_list_[static_cast<int>(type)]), dg14_delete_deque.front());
		dg14_delete_deque.pop_front();
	}

	//****************************
	// gadget14 削除以外の処理
	//****************************
	for (auto& e : dg14_attack_list_[static_cast<int>(type)])
	{
		// count_frame_の初期値は0になっている
		// delay_time_frame_が1なら1フレームは何もしないようにしたい
		// したがって、インクリメントしてから判定してるのでcount_frame_ - 1で比較
		e.count_frame_++;
		if (e.count_frame_ - 1 < e.gadget_dpx_->delay_time_frame_)
			continue;

		// 衝突判定処理
		for (unsigned int i = 0; i < e.collision_accuracy_; i++)
		{
			e.gadget_phandle_collection_[i]->grid_x_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.gadget_phandle_collection_[i]->grid_y_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.gadget_phandle_collection_[i], type);
		}
		
		// 描画処理
		e.gadget_gpx_->draw_grid_cx_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.gadget_gpx_->draw_grid_cy_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.gadget_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.gadget_gpx_, type);
	}

	//*******************************************
	// Gadget1414 削除処理
	// 削除するときにエフェクト描画もおこなう
	//*******************************************
	for (auto it = dg1414_attack_list_[static_cast<int>(type)].begin(); it != dg1414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			dg1414_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			dg1414_delete_deque.push_back(it);
		}
		else 
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->gadget_phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[i]->collision_hit_x_;
					it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[i]->collision_hit_y_;
					NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
					dg1414_delete_deque.push_back(it);
					break;
				}
			}
		}

	}
	while (!dg1414_delete_deque.empty())
	{
		dg1414_wait_list_.splice(dg1414_wait_list_.begin(), move(dg1414_attack_list_[static_cast<int>(type)]), dg1414_delete_deque.front());
		dg1414_delete_deque.pop_front();
	}

	//****************************
	// gadget1414 削除以外の処理
	//****************************
	for (auto& e : dg1414_attack_list_[static_cast<int>(type)])
	{
		// count_frame_の初期値は0になっている
		// delay_time_frame_が1なら1フレームは何もしないようにしたい
		// したがって、インクリメントしてから判定してるのでcount_frame_ - 1で比較
		e.count_frame_++;
		if (e.count_frame_ - 1 < e.gadget_dpx_->delay_time_frame_)
			continue;

		// 移動処理と衝突判定処理
		for (unsigned int i = 0; i < e.collision_accuracy_; i++)
		{
			e.gadget_phandle_collection_[i]->grid_x_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.gadget_phandle_collection_[i]->grid_y_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.gadget_phandle_collection_[i], type);
		}
		
		// 描画処理
		e.gadget_gpx_->draw_grid_cx_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.gadget_gpx_->draw_grid_cy_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.gadget_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.gadget_gpx_, type);
	}


	//*******************************************
	// gadget2414 削除処理
	// 削除するときにエフェクト描画もおこなう
	//*******************************************
	for (auto it = dg2414_attack_list_[static_cast<int>(type)].begin(); it != dg2414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			dg2414_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			dg2414_delete_deque.push_back(it);
		}
		else 
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->gadget_phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[i]->collision_hit_x_;
					it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[i]->collision_hit_y_;
					NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
					dg2414_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!dg2414_delete_deque.empty())
	{
		dg2414_wait_list_.splice(dg2414_wait_list_.begin(), move(dg2414_attack_list_[static_cast<int>(type)]), dg2414_delete_deque.front());
		dg2414_delete_deque.pop_front();
	}

	//****************************
	// gadget2414 削除以外の処理
	//****************************
	for (auto& e : dg2414_attack_list_[static_cast<int>(type)])
	{
		// count_frame_の初期値は0になっている
		// delay_time_frame_が1なら1フレームは何もしないようにしたい
		// したがって、インクリメントしてから判定してるのでcount_frame_ - 1で比較
		e.count_frame_++;
		if (e.count_frame_ - 1 < e.gadget_dpx_->delay_time_frame_)
			continue;

		// 移動処理と衝突判定処理
		for (unsigned int i = 0; i < e.collision_accuracy_; i++)
		{
			e.gadget_phandle_collection_[i]->grid_x_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.gadget_phandle_collection_[i]->grid_y_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.gadget_phandle_collection_[i], type);
		}

		// 角速度の処理
		e.move_angle_deg_ += e.gadget_dpx_->move_angle_speed_deg_;
		e.move_angle_rad_ = AngleToRad(e.move_angle_deg_);
		e.move_x_ = cos(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_x_ /= e.collision_accuracy_;
		e.move_y_ = sin(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_y_ /= e.collision_accuracy_;
		
		// 描画処理
		e.gadget_gpx_->draw_grid_cx_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.gadget_gpx_->draw_grid_cy_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.gadget_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.gadget_gpx_, type);
		e.gadget_dpx_->draw_angle_deg_ += e.gadget_dpx_->draw_angle_speed_deg_;
	}
}

