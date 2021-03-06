#include <cmath>
#include <deque>
#include "NyaPosition.h"
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaString.h"

#define __DEBUG__

using namespace std;
using namespace HNLIB;


list<DeviceGadget14> NyaDevice::gadget14_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget14> NyaDevice::gadget14_wait_list_;
list<DeviceGadget24> NyaDevice::gadget24_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget24> NyaDevice::gadget24_wait_list_;
list<DeviceGadget34> NyaDevice::gadget34_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget34> NyaDevice::gadget34_wait_list_;
list<DeviceGadget1414> NyaDevice::gadget1414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget1414> NyaDevice::gadget1414_wait_list_;
list<DeviceGadget1424> NyaDevice::gadget1424_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget1424> NyaDevice::gadget1424_wait_list_;
list<DeviceGadget2414> NyaDevice::gadget2414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget2414> NyaDevice::gadget2414_wait_list_;
list<DeviceGadget2424> NyaDevice::gadget2424_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget2424> NyaDevice::gadget2424_wait_list_; 
list<DeviceGadget3414> NyaDevice::gadget3414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget3414> NyaDevice::gadget3414_wait_list_; 
list<DeviceGadget3424> NyaDevice::gadget3424_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget3424> NyaDevice::gadget3424_wait_list_;

//***************************
// class DevicePropertyX
//***************************

DevicePropertyX1::DevicePropertyX1()
{
	collision_power_ = 1;
	collision_range_ = 1;
	delay_time_frame_ = 0;
	draw_angle_deg_ = 0;
	draw_angle_speed_deg_ = 0;
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

DevicePropertyX3::DevicePropertyX3()
{
	collision_power_ = 1;
	collision_range_ = 1;
	delay_time_frame_ = 0;
	draw_angle_deg_ = 0;
	draw_angle_speed_deg_ = 0;
	move_angle_deg_ = 0;
	move_speed_ = 1;
	move_speed_accel_ = 0;
}

//**********************
// class DeviceGadget
//**********************

DeviceGadget14::DeviceGadget14()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	for (auto& e : phandle_collection_)
		e = NyaPosition::CreateHandle();
}

DeviceGadget14::~DeviceGadget14()
{
	delete device_gpx_;
	device_gpx_ = nullptr;
	delete dpx_;
	dpx_ = nullptr;
	for (auto& e : phandle_collection_)
		NyaPosition::DeleteHandle(e);
}

DeviceGadget24::DeviceGadget24()
{
	gadget_dpx_ = new DevicePropertyX2;
	device_gpx_ = new GraphicPropertyX4;
	for (auto& e : phandle_collection_)
		e = NyaPosition::CreateHandle();
}

DeviceGadget24::~DeviceGadget24()
{
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	for (auto& e : phandle_collection_)
		NyaPosition::DeleteHandle(e);
}

DeviceGadget34::DeviceGadget34()
{
	gadget_dpx_ = new DevicePropertyX3;
	device_gpx_ = new GraphicPropertyX4;
	for (auto& e : phandle_collection_)
		e = NyaPosition::CreateHandle();
}

DeviceGadget34::~DeviceGadget34()
{
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	for (auto& e : phandle_collection_)
		NyaPosition::DeleteHandle(e);
}

DeviceGadget1414::DeviceGadget1414()
{
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	for (auto& e : phandle_collection_)
		e = NyaPosition::CreateHandle();
}

DeviceGadget1414::~DeviceGadget1414()
{
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	for (auto& e : phandle_collection_)
		NyaPosition::DeleteHandle(e);
}

DeviceGadget1424::DeviceGadget1424()
{
	effect_epx_ = new EffectPropertyX2;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	for (auto& e : phandle_collection_)
		e = NyaPosition::CreateHandle();
}

DeviceGadget1424::~DeviceGadget1424()
{
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	for (auto& e : phandle_collection_)
		NyaPosition::DeleteHandle(e);
}


DeviceGadget2414::DeviceGadget2414()
{
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX2;
	device_gpx_ = new GraphicPropertyX4;
	for (auto& e : phandle_collection_)
		e = NyaPosition::CreateHandle();
}

DeviceGadget2414::~DeviceGadget2414()
{
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	for (auto& e : phandle_collection_)
		NyaPosition::DeleteHandle(e);
}

DeviceGadget2424::DeviceGadget2424()
{
	device_gpx_ = new GraphicPropertyX4;
	dpx_ = new DevicePropertyX2;
	effect_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX2;
	for (auto& e : phandle_collection_)
		e = NyaPosition::CreateHandle();
}

DeviceGadget2424::~DeviceGadget2424()
{
	delete device_gpx_;
	device_gpx_ = nullptr;
	delete dpx_;
	dpx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	for (auto& e : phandle_collection_)
		NyaPosition::DeleteHandle(e);
}

DeviceGadget3414::DeviceGadget3414()
{
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX3;
	device_gpx_ = new GraphicPropertyX4;
	for (auto& e : phandle_collection_)
		e = NyaPosition::CreateHandle();
}

DeviceGadget3414::~DeviceGadget3414()
{
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	for (auto& e : phandle_collection_)
		NyaPosition::DeleteHandle(e);
}

HNLIB::DeviceGadget3424::DeviceGadget3424()
{
	device_gpx_ = new GraphicPropertyX4;
	dpx_ = new DevicePropertyX3;
	effect_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX2;
	for (auto& e : phandle_collection_)
		e = NyaPosition::CreateHandle();
}

DeviceGadget3424::~DeviceGadget3424()
{
	delete device_gpx_;
	device_gpx_ = nullptr;
	delete dpx_;
	dpx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	for (auto& e : phandle_collection_)
		NyaPosition::DeleteHandle(e);
}

//*************************************
// NyaDevice メンバ関数 (public)
//*************************************

/**
@brief 攻撃 type-14
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度
@note
 衝突判定の精度は[1-9]の値で指定、大きい値ほど高精度になる
 それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される
**/
void NyaDevice::Attack14(const DevicePropertyX1* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type,  unsigned int collision_accuracy)
{
	static list<DeviceGadget14>::iterator it_from, it_to;

	// 生成できないときはサイズを増やす
	if (gadget14_wait_list_.begin() == gadget14_wait_list_.end())
		gadget14_wait_list_.resize(1);

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget14_wait_list_.begin();
	it_from->clear_ = false;
	it_from->collision_accuracy_ = collision_accuracy;
	it_from->count_frame_ = 0;
	it_from->move_angle_deg_ = gadget_dpx->move_angle_deg_;
	it_from->move_angle_rad_ = AngleToRad(gadget_dpx->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_x_ /= collision_accuracy;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_y_ /= collision_accuracy;
	*it_from->device_gpx_ = *gadget_gpx;
	*it_from->dpx_ = *gadget_dpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->phandle_collection_[i]->health_ = 1;
	}

	it_to = gadget14_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget14_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget14_wait_list_), it_from);
}

/**
@brief 攻撃 type-24
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度
@note
 衝突判定の精度は[1-9]の値で指定、大きい値ほど高精度になる
 それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される
**/
void NyaDevice::Attack24(const DevicePropertyX2* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type,  unsigned int collision_accuracy)
{
	static list<DeviceGadget24>::iterator it_from, it_to;

	// 生成できないときはサイズを増やす
	if (gadget24_wait_list_.begin() == gadget24_wait_list_.end())
		gadget24_wait_list_.resize(1);

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget24_wait_list_.begin();
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
	*it_from->device_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->phandle_collection_[i]->health_ = 1;
	}

	it_to = gadget24_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget24_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget24_wait_list_), it_from);
}

/**
@brief 攻撃 type-34
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度
@note
 衝突判定の精度は[1-9]の値で指定、大きい値ほど高精度になる
 それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される
**/
void NyaDevice::Attack34(const DevicePropertyX3* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type,  unsigned int collision_accuracy)
{
	static list<DeviceGadget34>::iterator it_from, it_to;

	// 生成できないときはサイズを増やす
	if (gadget34_wait_list_.begin() == gadget34_wait_list_.end())
		gadget34_wait_list_.resize(1);

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget34_wait_list_.begin();
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
	*it_from->device_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->phandle_collection_[i]->health_ = 1;
	}

	it_to = gadget34_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget34_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget34_wait_list_), it_from);
}

/**
@brief 攻撃 type-1414
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param effect_dpx エフェクト用デバイスプロパティ
@param effect_gpx エフェクト用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param effect_type エフェクトのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度
@note
 エフェクト付き攻撃関数
 衝突判定の精度は[1-9]の値で指定、大きい値ほど高精度になる
 それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される
**/
void NyaDevice::Attack1414(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget1414>::iterator it_from, it_to;

	// 最大個数まで生成されているときは何もしない
	if (gadget1414_wait_list_.begin() == gadget1414_wait_list_.end())
		gadget1414_wait_list_.resize(1);

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget1414_wait_list_.begin();
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
	it_from->effect_gpx_->file_.div_collection_ = gadget_gpx->file_.div_collection_;
	*it_from->effect_gpx_ = *effect_gpx;
	*it_from->gadget_dpx_ = *gadget_dpx;
	*it_from->device_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->phandle_collection_[i]->health_ = 1;
	}
	it_to = gadget1414_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget1414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget1414_wait_list_), it_from);
}

/**
@brief 攻撃 type-1424
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param effect_dpx エフェクト用デバイスプロパティ
@param effect_gpx エフェクト用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param effect_type エフェクトのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度
@note
 エフェクト付き攻撃関数
 衝突判定の精度は[1-9]の値で指定、大きい値ほど高精度になる
 それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される
**/
void NyaDevice::Attack1424(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX2* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget1424>::iterator it_from, it_to;

	// 最大個数まで生成されているときは何もしない
	if (gadget1424_wait_list_.begin() == gadget1424_wait_list_.end())
		gadget1424_wait_list_.resize(1);

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget1424_wait_list_.begin();
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
	it_from->effect_gpx_->file_.div_collection_ = gadget_gpx->file_.div_collection_;
	*it_from->effect_gpx_ = *effect_gpx;
	*it_from->gadget_dpx_ = *gadget_dpx;
	*it_from->device_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->phandle_collection_[i]->health_ = 1;
	}
	it_to = gadget1424_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget1424_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget1424_wait_list_), it_from);
}

/**
@brief 攻撃 type-2414
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param effect_dpx エフェクト用デバイスプロパティ
@param effect_gpx エフェクト用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param effect_type エフェクトのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度
@note
 エフェクトと角速度を指定できる攻撃関数
 衝突判定の精度は[1-9]の値で指定、大きい値ほど高精度になる
 それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される
**/

void NyaDevice::Attack2414(const DevicePropertyX2* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget2414>::iterator it_from, it_to;

	if (gadget2414_wait_list_.begin() == gadget2414_wait_list_.end())
		gadget2414_wait_list_.resize(1);

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget2414_wait_list_.begin();
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
	*it_from->device_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->phandle_collection_[i]->health_ = 1;
	}

	it_to = gadget2414_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget2414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget2414_wait_list_), it_from);
}

/**
@brief 攻撃 type-2424
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param effect_dpx エフェクト用デバイスプロパティ
@param effect_gpx エフェクト用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param effect_type エフェクトのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度倍率(指定しなければ精度1倍で実行される)
@note
エフェクトと角速度を指定できる攻撃関数。
衝突判定の精度倍率は[1-9]の値で指定、大きい値ほど高精度になる。
それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される。
**/

void NyaDevice::Attack2424(const DevicePropertyX2* dpx, const GraphicPropertyX4* device_gpx, const EffectPropertyX2* epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget2424>::iterator it_from, it_to;

	if (gadget2424_wait_list_.begin() == gadget2424_wait_list_.end())
		gadget2424_wait_list_.resize(1);

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget2424_wait_list_.begin();
	it_from->clear_ = false;
	it_from->collision_accuracy_ = collision_accuracy;
	it_from->count_frame_ = 0;
	it_from->effect_type_ = effect_type;
	it_from->move_angle_deg_ = dpx->move_angle_deg_;
	it_from->move_angle_rad_ = AngleToRad(dpx->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * dpx->move_speed_;
	it_from->move_x_ /= collision_accuracy;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * dpx->move_speed_;
	it_from->move_y_ /= collision_accuracy;
	*it_from->device_gpx_ = *device_gpx;
	*it_from->dpx_ = *dpx;
	*it_from->effect_gpx_ = *effect_gpx;
	*it_from->epx_ = *epx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->phandle_collection_[i]->collision_power_ = dpx->collision_power_;
		it_from->phandle_collection_[i]->collision_range_ = dpx->collision_range_;
		it_from->phandle_collection_[i]->grid_x_ = dpx->create_x_;
		it_from->phandle_collection_[i]->grid_y_ = dpx->create_y_;
		it_from->phandle_collection_[i]->health_ = 1;
	}

	it_to = gadget2424_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget2424_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget2424_wait_list_), it_from);
}

/**
@brief 攻撃 type-3414
@param gadget_dpx ガジェット用デバイスプロパティ
@param gadget_gpx ガジェット用グラフィックプロパティ
@param effect_dpx エフェクト用デバイスプロパティ
@param effect_gpx エフェクト用グラフィックプロパティ
@param gadget_type ガジェットのオブジェクトタイプ
@param effect_type エフェクトのオブジェクトタイプ
@param collision_accuracy 衝突判定の精度
@note
 エフェクトと角速度を指定できる攻撃関数
 衝突判定の精度は[1-9]の値で指定、大きい値ほど高精度になる
 それぞれの引数で指定したプロパティのメンバの中で使用しない値は設定しても無視される
**/
void NyaDevice::Attack3414(const DevicePropertyX3* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget3414>::iterator it_from, it_to;

	if (gadget3414_wait_list_.begin() == gadget3414_wait_list_.end())
		gadget3414_wait_list_.resize(1);

	// 衝突精度の値が範囲外のときは無効化
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget3414_wait_list_.begin();
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
	*it_from->device_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->phandle_collection_[i]->health_ = 1;
	}

	it_to = gadget3414_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget3414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget3414_wait_list_), it_from);
}

/**
 @brief クリア関数
 @param type クリアするオブジェクトタイプ
 @note
  引数で指定したtypeのgadgetを全てクリアする
**/
void NyaDevice::Clear(eOBJECT type)
{
	for (auto& e : gadget14_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget24_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget34_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget1414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget1424_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget2414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget2424_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget3414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget3424_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
}

void HNLIB::NyaDevice::Init(void)
{
	for (auto& e : gadget14_attack_list_)
		e.clear();
	for (auto& e : gadget24_attack_list_)
		e.clear();
	for (auto& e : gadget34_attack_list_)
		e.clear();
	for (auto& e : gadget1414_attack_list_)
		e.clear();
	for (auto& e : gadget1424_attack_list_)
		e.clear();
	for (auto& e : gadget2414_attack_list_)
		e.clear();
	for (auto& e : gadget2424_attack_list_)
		e.clear();
	for (auto& e : gadget3414_attack_list_)
		e.clear();
	for (auto& e : gadget3424_attack_list_)
		e.clear();
	gadget1414_wait_list_.clear();
	gadget1424_wait_list_.clear();
	gadget2414_wait_list_.clear();
	gadget2424_wait_list_.clear();
	gadget3414_wait_list_.clear();
	gadget3424_wait_list_.clear();
}

/**
@brief 全ての処理を実行する
@note
NyaWindow内で自動的に実行されるので、ライブラリ使用者が呼び出す必要はない。
**/
void NyaDevice::Run(void)
{
	for (eOBJECT type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; ++type)
		Calculate(type);

#ifdef __DEBUG__
	size_t wait_size = 0;
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	wait_size += gadget14_wait_list_.size();
	wait_size += gadget24_wait_list_.size();
	wait_size += gadget34_wait_list_.size();
	wait_size += gadget1414_wait_list_.size();
	wait_size += gadget2414_wait_list_.size();
	wait_size += gadget3414_wait_list_.size();
	NyaString::Write("debug_font", white, 50, 210, "[50, 210] device_wait_list size = %u", (unsigned int)wait_size);
#endif
}

size_t NyaDevice::Size(eOBJECT type)
{
	size_t attack_size = 0;

	attack_size += gadget14_attack_list_[static_cast<int>(type)].size();
	attack_size += gadget24_attack_list_[static_cast<int>(type)].size();
	attack_size += gadget34_attack_list_[static_cast<int>(type)].size();
	attack_size += gadget1414_attack_list_[static_cast<int>(type)].size();
	attack_size += gadget2414_attack_list_[static_cast<int>(type)].size();
	attack_size += gadget3414_attack_list_[static_cast<int>(type)].size();

	return attack_size;
}

//*************************************
// NyaDevice メンバ関数 (private)
//*************************************

/**
@brief gadgetの計算処理をする
**/
void NyaDevice::Calculate(eOBJECT type)
{
	deque<list<DeviceGadget14>::iterator> gadget14_delete_deque;
	deque<list<DeviceGadget24>::iterator> gadget24_delete_deque;
	deque<list<DeviceGadget34>::iterator> gadget34_delete_deque;
	deque<list<DeviceGadget1414>::iterator> gadget1414_delete_deque;
	deque<list<DeviceGadget1424>::iterator> gadget1424_delete_deque;
	deque<list<DeviceGadget2414>::iterator> gadget2414_delete_deque;
	deque<list<DeviceGadget2424>::iterator> gadget2424_delete_deque;
	deque<list<DeviceGadget3414>::iterator> gadget3414_delete_deque;
	deque<list<DeviceGadget3424>::iterator> gadget3424_delete_deque;

	//**********************************************************
	// Gadget14 削除処理
	// イテレータをコンテナに保存するため範囲for文は使わない
	//**********************************************************

	for (auto it = gadget14_attack_list_[static_cast<int>(type)].begin(); it != gadget14_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->phandle_collection_[it->collision_accuracy_ - 1], 128))
			gadget14_delete_deque.push_back(it);
		else if (it->clear_)
			gadget14_delete_deque.push_back(it);
		else
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					gadget14_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget14_delete_deque.empty())
	{
		gadget14_wait_list_.splice(gadget14_wait_list_.begin(), move(gadget14_attack_list_[static_cast<int>(type)]), gadget14_delete_deque.front());
		gadget14_delete_deque.pop_front();
	}

	//****************************
	// gadget14 削除以外の処理
	//****************************

	for (auto& e : gadget14_attack_list_[static_cast<int>(type)])
	{
		// count_frame_の初期値は0になっている
		// delay_time_frame_が1なら1フレームは何もしないようにしたい
		// したがって、インクリメントしてから判定してるのでcount_frame_ - 1で比較
		e.count_frame_++;
		if (e.count_frame_ - 1 < e.dpx_->delay_time_frame_)
			continue;

		// 移動処理と衝突判定処理
		for (unsigned int i = 0; i < e.collision_accuracy_; i++)
		{	// 衝突精度倍率の回数だけ繰り返し計算する
			e.phandle_collection_[i]->grid_x_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.phandle_collection_[i]->grid_y_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.phandle_collection_[i], type);
		}
		
		// 描画処理
		e.device_gpx_->draw_grid_cx_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.device_gpx_->draw_grid_cy_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.device_gpx_->draw_angle_deg_ = e.dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.device_gpx_, type);
		e.dpx_->draw_angle_deg_ += e.dpx_->draw_angle_speed_deg_;
	}

	//*********************************************************
	// Gadget24 削除処理
	// イテレータをコンテナに保存するため範囲for文は使わない
	//**********************************************************

	for (auto it = gadget24_attack_list_[static_cast<int>(type)].begin(); it != gadget24_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->phandle_collection_[it->collision_accuracy_ - 1], 128))
			gadget24_delete_deque.push_back(it);
		else if (it->clear_)
			gadget24_delete_deque.push_back(it);
		else
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					gadget24_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget24_delete_deque.empty())
	{
		gadget24_wait_list_.splice(gadget24_wait_list_.begin(), move(gadget24_attack_list_[static_cast<int>(type)]), gadget24_delete_deque.front());
		gadget24_delete_deque.pop_front();
	}

	//****************************
	// gadget24 削除以外の処理
	//****************************

	for (auto& e : gadget24_attack_list_[static_cast<int>(type)])
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
			e.phandle_collection_[i]->grid_x_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.phandle_collection_[i]->grid_y_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.phandle_collection_[i], type);
		}
		
		// 描画処理
		e.device_gpx_->draw_grid_cx_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.device_gpx_->draw_grid_cy_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.device_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.device_gpx_, type);
		e.gadget_dpx_->draw_angle_deg_ += e.gadget_dpx_->draw_angle_speed_deg_;
	}

	//**********************************************************
	// Gadget34 削除処理
	// イテレータをコンテナに保存するため範囲for文は使わない
	//**********************************************************

	for (auto it = gadget34_attack_list_[static_cast<int>(type)].begin(); it != gadget34_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->phandle_collection_[it->collision_accuracy_ - 1], 128))
			gadget34_delete_deque.push_back(it);
		else if (it->clear_)
			gadget34_delete_deque.push_back(it);
		else
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					gadget34_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget34_delete_deque.empty())
	{
		gadget34_wait_list_.splice(gadget34_wait_list_.begin(), move(gadget34_attack_list_[static_cast<int>(type)]), gadget34_delete_deque.front());
		gadget34_delete_deque.pop_front();
	}

	//****************************
	// gadget34 削除以外の処理
	//****************************

	for (auto& e : gadget34_attack_list_[static_cast<int>(type)])
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
			e.phandle_collection_[i]->grid_x_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.phandle_collection_[i]->grid_y_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.phandle_collection_[i], type);
		}
		// 加速度の処理
		e.gadget_dpx_->move_speed_ += e.gadget_dpx_->move_speed_accel_;
		e.move_x_ = cos(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_x_ /= e.collision_accuracy_;
		e.move_y_ = sin(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_y_ /= e.collision_accuracy_;

		// 描画処理
		e.device_gpx_->draw_grid_cx_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.device_gpx_->draw_grid_cy_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.device_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.device_gpx_, type);
		e.gadget_dpx_->draw_angle_deg_ += e.gadget_dpx_->draw_angle_speed_deg_;
	}

	//*********************************************************
	// Gadget1414 削除処理
	// イテレータをコンテナに保存するため範囲for文は使わない
	// 削除するときにエフェクト描画もおこなう
	//**********************************************************

	for (auto it = gadget1414_attack_list_[static_cast<int>(type)].begin(); it != gadget1414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->phandle_collection_[it->collision_accuracy_ - 1], 128))
			gadget1414_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = (int)it->phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = (int)it->phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			gadget1414_delete_deque.push_back(it);
		}
		else 
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->effect_epx_->grid_x_ = it->phandle_collection_[i]->collision_hit_x_;
					it->effect_epx_->grid_y_ = it->phandle_collection_[i]->collision_hit_y_;
					NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
					gadget1414_delete_deque.push_back(it);
					break;
				}
			}
		}

	}
	while (!gadget1414_delete_deque.empty())
	{
		gadget1414_wait_list_.splice(gadget1414_wait_list_.begin(), move(gadget1414_attack_list_[static_cast<int>(type)]), gadget1414_delete_deque.front());
		gadget1414_delete_deque.pop_front();
	}

	//****************************
	// gadget1414 削除以外の処理
	//****************************

	for (auto& e : gadget1414_attack_list_[static_cast<int>(type)])
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
			e.phandle_collection_[i]->grid_x_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.phandle_collection_[i]->grid_y_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.phandle_collection_[i], type);
		}
		
		// 描画処理
		e.device_gpx_->draw_grid_cx_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.device_gpx_->draw_grid_cy_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.device_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.device_gpx_, type);
		e.gadget_dpx_->draw_angle_deg_ += e.gadget_dpx_->draw_angle_speed_deg_;
	}

	//**********************************************************
	// Gadget1424 削除処理
	// イテレータをコンテナに保存するため範囲for文は使わない
	// 削除するときにエフェクト描画もおこなう
	//**********************************************************

	for (auto it = gadget1424_attack_list_[static_cast<int>(type)].begin(); it != gadget1424_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->phandle_collection_[it->collision_accuracy_ - 1], 128))
			gadget1424_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = &it->phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = &it->phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			gadget1424_delete_deque.push_back(it);
		}
		else 
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->effect_epx_->gap_x_ = it->phandle_collection_[i]->collision_hit_x_ - it->phandle_collection_[i]->collision_hit_handle_->grid_x_;
					it->effect_epx_->gap_y_ = it->phandle_collection_[i]->collision_hit_y_ - it->phandle_collection_[i]->collision_hit_handle_->grid_y_;
					it->effect_epx_->grid_x_ = &it->phandle_collection_[i]->collision_hit_handle_->grid_x_;
					it->effect_epx_->grid_y_ = &it->phandle_collection_[i]->collision_hit_handle_->grid_y_;
					NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
					gadget1424_delete_deque.push_back(it);
					break;
				}
			}
		}

	}
	while (!gadget1424_delete_deque.empty())
	{
		gadget1424_wait_list_.splice(gadget1424_wait_list_.begin(), move(gadget1424_attack_list_[static_cast<int>(type)]), gadget1424_delete_deque.front());
		gadget1424_delete_deque.pop_front();
	}

	//****************************
	// gadget1424 削除以外の処理
	//****************************

	for (auto& e : gadget1424_attack_list_[static_cast<int>(type)])
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
			e.phandle_collection_[i]->grid_x_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.phandle_collection_[i]->grid_y_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.phandle_collection_[i], type);
		}
		
		// 描画処理
		e.device_gpx_->draw_grid_cx_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.device_gpx_->draw_grid_cy_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.device_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.device_gpx_, type);
		e.gadget_dpx_->draw_angle_deg_ += e.gadget_dpx_->draw_angle_speed_deg_;
	}


	//**********************************************************
	// gadget2414 削除処理
	// イテレータをコンテナに保存するため範囲for文は使わない
	// 削除するときにエフェクト描画もおこなう
	//**********************************************************

	for (auto it = gadget2414_attack_list_[static_cast<int>(type)].begin(); it != gadget2414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->phandle_collection_[it->collision_accuracy_ - 1], 128))
			gadget2414_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = it->phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = it->phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			gadget2414_delete_deque.push_back(it);
		}
		else 
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->effect_epx_->grid_x_ = (int)it->phandle_collection_[i]->collision_hit_x_;
					it->effect_epx_->grid_y_ = (int)it->phandle_collection_[i]->collision_hit_y_;
					NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
					gadget2414_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget2414_delete_deque.empty())
	{
		gadget2414_wait_list_.splice(gadget2414_wait_list_.begin(), move(gadget2414_attack_list_[static_cast<int>(type)]), gadget2414_delete_deque.front());
		gadget2414_delete_deque.pop_front();
	}

	//****************************
	// gadget2414 削除以外の処理
	//****************************
	for (auto& e : gadget2414_attack_list_[static_cast<int>(type)])
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
			e.phandle_collection_[i]->grid_x_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.phandle_collection_[i]->grid_y_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.phandle_collection_[i], type);
		}

		// 角速度の処理
		e.move_angle_deg_ += e.gadget_dpx_->move_angle_speed_deg_;
		e.move_angle_rad_ = AngleToRad(e.move_angle_deg_);
		e.move_x_ = cos(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_x_ /= e.collision_accuracy_;
		e.move_y_ = sin(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_y_ /= e.collision_accuracy_;
		
		// 描画処理
		e.device_gpx_->draw_grid_cx_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.device_gpx_->draw_grid_cy_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.device_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.device_gpx_, type);
		e.gadget_dpx_->draw_angle_deg_ += e.gadget_dpx_->draw_angle_speed_deg_;
	}

	//**********************************************************
	// Gadget2424 削除処理
	// イテレータをコンテナに保存するため範囲for文は使わない
	// 削除するときにエフェクト描画もおこなう
	//**********************************************************

	for (auto it = gadget2424_attack_list_[static_cast<int>(type)].begin(); it != gadget2424_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->phandle_collection_[it->collision_accuracy_ - 1], 128))
			gadget2424_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->epx_->grid_x_ = &it->phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->epx_->grid_y_ = &it->phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->epx_, it->effect_gpx_, it->effect_type_);
			gadget2424_delete_deque.push_back(it);
		}
		else
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->epx_->gap_x_ = it->phandle_collection_[i]->collision_hit_x_ - it->phandle_collection_[i]->collision_hit_handle_->grid_x_;
					it->epx_->gap_y_ = it->phandle_collection_[i]->collision_hit_y_ - it->phandle_collection_[i]->collision_hit_handle_->grid_y_;
					it->epx_->grid_x_ = &it->phandle_collection_[i]->collision_hit_handle_->grid_x_;
					it->epx_->grid_y_ = &it->phandle_collection_[i]->collision_hit_handle_->grid_y_;
					NyaEffect::Draw(it->epx_, it->effect_gpx_, it->effect_type_);
					gadget2424_delete_deque.push_back(it);
					break;
				}
			}
		}

	}
	while (!gadget2424_delete_deque.empty())
	{
		gadget2424_wait_list_.splice(gadget2424_wait_list_.begin(), move(gadget2424_attack_list_[static_cast<int>(type)]), gadget2424_delete_deque.front());
		gadget2424_delete_deque.pop_front();
	}

	//****************************
	// gadget2424 削除以外の処理
	//****************************

	for (auto& e : gadget2424_attack_list_[static_cast<int>(type)])
	{
		// count_frame_の初期値は0になっている
		// delay_time_frame_が1なら1フレームは何もしないようにしたい
		// したがって、インクリメントしてから判定してるのでcount_frame_ - 1で比較
		e.count_frame_++;
		if (e.count_frame_ - 1 < e.dpx_->delay_time_frame_)
			continue;

		// 移動処理と衝突判定処理
		for (unsigned int i = 0; i < e.collision_accuracy_; i++)
		{
			e.phandle_collection_[i]->grid_x_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.phandle_collection_[i]->grid_y_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.phandle_collection_[i], type);
		}

		// 描画処理
		e.device_gpx_->draw_grid_cx_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.device_gpx_->draw_grid_cy_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.device_gpx_->draw_angle_deg_ = e.dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.device_gpx_, type);
		e.dpx_->draw_angle_deg_ += e.dpx_->draw_angle_speed_deg_;
	}

	//**********************************************************
	// gadget3414 削除処理
	// イテレータをコンテナに保存するため範囲for文は使わない
	// 削除するときにエフェクト描画もおこなう
	//**********************************************************

	for (auto it = gadget3414_attack_list_[static_cast<int>(type)].begin(); it != gadget3414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->phandle_collection_[it->collision_accuracy_ - 1], 128))
			gadget3414_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = it->phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = it->phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			gadget3414_delete_deque.push_back(it);
		}
		else 
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->effect_epx_->grid_x_ = (int)it->phandle_collection_[i]->collision_hit_x_;
					it->effect_epx_->grid_y_ = (int)it->phandle_collection_[i]->collision_hit_y_;
					NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
					gadget3414_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget3414_delete_deque.empty())
	{
		gadget3414_wait_list_.splice(gadget3414_wait_list_.begin(), move(gadget3414_attack_list_[static_cast<int>(type)]), gadget3414_delete_deque.front());
		gadget3414_delete_deque.pop_front();
	}

	//****************************
	// gadget3414 削除以外の処理
	//****************************

	for (auto& e : gadget3414_attack_list_[static_cast<int>(type)])
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
			e.phandle_collection_[i]->grid_x_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.phandle_collection_[i]->grid_y_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.phandle_collection_[i], type);
		}
		// 加速度の処理
		e.gadget_dpx_->move_speed_ += e.gadget_dpx_->move_speed_accel_;
		e.move_x_ = cos(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_x_ /= e.collision_accuracy_;
		e.move_y_ = sin(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_y_ /= e.collision_accuracy_;
		
		// 描画処理
		e.device_gpx_->draw_grid_cx_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.device_gpx_->draw_grid_cy_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.device_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.device_gpx_, type);
		e.gadget_dpx_->draw_angle_deg_ += e.gadget_dpx_->draw_angle_speed_deg_;
	}

	//**********************************************************
	// gadget3414 削除処理
	// イテレータをコンテナに保存するため範囲for文は使わない
	// 削除するときにエフェクト描画もおこなう
	//**********************************************************

	for (auto it = gadget3424_attack_list_[static_cast<int>(type)].begin(); it != gadget3424_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// フレームカウントが遅延時間に達していないなら何もしない
		if (it->count_frame_ < it->dpx_->delay_time_frame_)
			continue;

		// 表示領域の限界を超えた
		// クリアを指定された
		// 他のオブジェクトと衝突した
		if (!NyaPosition::InScreen(it->phandle_collection_[it->collision_accuracy_ - 1], 128))
			gadget3424_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->epx_->grid_x_ = &it->phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->epx_->grid_y_ = &it->phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->epx_, it->effect_gpx_, it->effect_type_);
			gadget3424_delete_deque.push_back(it);
		}
		else
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->epx_->grid_x_ = &it->phandle_collection_[i]->collision_hit_x_;
					it->epx_->grid_y_ = &it->phandle_collection_[i]->collision_hit_y_;
					NyaEffect::Draw(it->epx_, it->effect_gpx_, it->effect_type_);
					gadget3424_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget3424_delete_deque.empty())
	{
		gadget3424_wait_list_.splice(gadget3424_wait_list_.begin(), move(gadget3424_attack_list_[static_cast<int>(type)]), gadget3424_delete_deque.front());
		gadget3424_delete_deque.pop_front();
	}

	//****************************
	// gadget3424 削除以外の処理
	//****************************

	for (auto& e : gadget3424_attack_list_[static_cast<int>(type)])
	{
		// count_frame_の初期値は0になっている
		// delay_time_frame_が1なら1フレームは何もしないようにしたい
		// したがって、インクリメントしてから判定してるのでcount_frame_ - 1で比較
		e.count_frame_++;
		if (e.count_frame_ - 1 < e.dpx_->delay_time_frame_)
			continue;

		// 移動処理と衝突判定処理
		for (unsigned int i = 0; i < e.collision_accuracy_; i++)
		{
			e.phandle_collection_[i]->grid_x_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.phandle_collection_[i]->grid_y_ = e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.phandle_collection_[i], type);
		}
		// 加速度の処理
		e.dpx_->move_speed_ += e.dpx_->move_speed_accel_;
		e.move_x_ = cos(e.move_angle_rad_) * e.dpx_->move_speed_;
		e.move_x_ /= e.collision_accuracy_;
		e.move_y_ = sin(e.move_angle_rad_) * e.dpx_->move_speed_;
		e.move_y_ /= e.collision_accuracy_;

		// 描画処理
		e.device_gpx_->draw_grid_cx_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.device_gpx_->draw_grid_cy_ = (int)e.phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.device_gpx_->draw_angle_deg_ = e.dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.device_gpx_, type);
		e.dpx_->draw_angle_deg_ += e.dpx_->draw_angle_speed_deg_;
	}
}


