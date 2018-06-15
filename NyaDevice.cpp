#include <cmath>
#include <deque>
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;

#define DEVICE_GADGET_MAX_DEFAULT 10000


int NyaDevice::count_instance_ = 0;
list<DeviceGadget14> NyaDevice::dg14_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget14> NyaDevice::dg14_wait_list_;
list<DeviceGadget1414> NyaDevice::dg1414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget1414> NyaDevice::dg1414_wait_list_;
list<DeviceGadget2414> NyaDevice::dg2414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget2414> NyaDevice::dg2414_wait_list_;

DeviceGadget14::DeviceGadget14()
{
	gadget_dp_ = new DevicePropertyX1;
	gadget_gp_ = new GraphicPropertyX4;
	gadget_ph_ = new PositionHandle1;
}

DeviceGadget14::~DeviceGadget14()
{
	delete gadget_dp_;
	delete gadget_gp_;
	delete gadget_ph_;
}

DeviceGadget1414::DeviceGadget1414()
{
	effect_ep_ = new EffectProperty1;
	effect_gp_ = new GraphicPropertyX4;
	gadget_dp_ = new DevicePropertyX1;
	gadget_gp_ = new GraphicPropertyX4;
	gadget_ph_ = new PositionHandle1;
}

DeviceGadget1414::~DeviceGadget1414()
{
	delete effect_ep_;
	delete effect_gp_;
	delete gadget_dp_;
	delete gadget_gp_;
	delete gadget_ph_;
}

NyaDevice::NyaDevice()
{
	nya_effect_ = new NyaEffect;
	nya_position_ = new NyaPosition;


	// gadget 最大個数はデフォルトで10000個
	if (count_instance_ == 0)
	{ 
		dg14_wait_list_.resize(DEVICE_GADGET_MAX_DEFAULT);
		dg1414_wait_list_.resize(DEVICE_GADGET_MAX_DEFAULT);
	}

	count_instance_++;
}


NyaDevice::~NyaDevice()
{
	delete nya_effect_;
	delete nya_position_;
	count_instance_--;
}

/**
@brief 攻撃関数
@param dpx デバイスプロパティ
@param gadget_gpx4 ガジェットグラフィックプロパティ
@note
 オブジェクトの最大個数は10000個。
 この関数では下記メンバ変数を利用するので、必ず値を設定すること。
 gadget_dp->collision_pow_;			// gadget 衝突攻撃力
 gadget_dp->collision_range_;		// gadget 衝突範囲
 gadget_dp->create_grid_x_;			// gadget 生成x座標
 gadget_dp->create_grid_y_;			// gadget 生成y座標
 gadget_dp->move_angle_deg_;		// gadget 移動角度
 gadget_dp->move_speed_;			// gadget 移動速度
 gadget_gp->graphic_file_;			// gadget グラフィックファイル
 gadget_gp->file_div_;				// gadget グラフィック分割インデックス
 gadget_gp->draw_angle_;			// gadget 描画角度
 gadget_gp->extend_rate_;			// gadget 描画拡大率
 gadget_gp->flag_turn_;				// gadget 描画反転フラグ
 gadget_gp->flag_trans_;			// gadget 描画透過フラグ
 この関数では下記メンバ変数は利用しないため、値を設定しても無視される。
 gadget_gp->pos_cx_; gadget_gp->pos_cy_;
**/
void NyaDevice::Attack14(const DevicePropertyX1* const gadget_dp, const GraphicPropertyX4* const gadget_gp, eOBJECT gadget_type)
{
	static list<DeviceGadget14>::iterator it_from, it_to;

	// 最大個数まで生成されているときは何もしない
	if (dg14_wait_list_.begin() == dg14_wait_list_.end())
		return;

	it_from = dg14_wait_list_.begin();
	it_from->move_angle_rad_ = AngleToRad(gadget_dp->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dp->move_speed_;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dp->move_speed_;
	*it_from->gadget_dp_ = *gadget_dp;
	*it_from->gadget_gp_ = *gadget_gp;
	it_from->gadget_ph_->collision_hit_ = 0;
	it_from->gadget_ph_->collision_power_ = gadget_dp->collision_power_;
	it_from->gadget_ph_->collision_range_ = gadget_dp->collision_range_;
	it_from->gadget_ph_->grid_x_ = gadget_dp->create_x_;
	it_from->gadget_ph_->grid_y_ = gadget_dp->create_y_;
	it_from->gadget_ph_->health_ = 1;

	it_to = dg14_attack_list_[static_cast<int>(gadget_type)].begin();
	dg14_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(dg14_wait_list_), it_from);
}

void NyaDevice::Attack1414(const DevicePropertyX1* gadget_dp, const GraphicPropertyX4* gadget_gp, const EffectProperty1* effect_ep, const GraphicPropertyX4* effect_gp, eOBJECT gadget_type, eOBJECT effect_type)
{
	static list<DeviceGadget1414>::iterator it_from, it_to;

	// 最大個数まで生成されているときは何もしない
	if (dg1414_wait_list_.begin() == dg1414_wait_list_.end())
		return;

	it_from = dg1414_wait_list_.begin();
	it_from->effect_type_ = effect_type;
	it_from->move_angle_rad_ = AngleToRad(gadget_dp->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dp->move_speed_;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dp->move_speed_;
	*it_from->effect_ep_ = *effect_ep;
	*it_from->effect_gp_ = *effect_gp;
	*it_from->gadget_dp_ = *gadget_dp;
	*it_from->gadget_gp_ = *gadget_gp;
	it_from->gadget_ph_->collision_hit_ = 0;
	it_from->gadget_ph_->collision_power_ = gadget_dp->collision_power_;
	it_from->gadget_ph_->collision_range_ = gadget_dp->collision_range_;
	it_from->gadget_ph_->grid_x_ = gadget_dp->create_x_;
	it_from->gadget_ph_->grid_y_ = gadget_dp->create_y_;
	it_from->gadget_ph_->health_ = 1;

	it_to = dg1414_attack_list_[static_cast<int>(gadget_type)].begin();
	dg1414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(dg1414_wait_list_), it_from);
}

void NyaDevice::Attack2414(DevicePropertyX2* gadget_dp, GraphicPropertyX4* gadget_gp, EffectProperty1* effect_ep, GraphicPropertyX4* effect_gp)
{

}

void NyaDevice::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (eOBJECT group = eOBJECT::enum_zero; group != eOBJECT::sizeof_enum; ++group)
		MoveGadget(group);


	NyaString::Write("debug_font", white, 50, 190, "[50, 190] attack list size = %d", (int)dg14_attack_list_[static_cast<int>(eOBJECT::USER_ATTACK1)].size());
	NyaString::Write("debug_font", white, 50, 210, "[50, 210] wait list size = %d", (int)dg14_wait_list_.size());
}


void NyaDevice::MoveGadget(eOBJECT type)
{
	static GraphicPropertyX4 gp;
	static deque<list<DeviceGadget14>::iterator> dg14_delete_deque;
	static deque<list<DeviceGadget1414>::iterator> dg1414_delete_deque;


	//***********************
	// Gadget14 削除処理
	//***********************
	for (auto it = dg14_attack_list_[static_cast<int>(type)].begin(); it != dg14_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// 表示領域の限界を超えた
		// 他のオブジェクトと衝突した
		if (!nya_position_->InScreen(it->gadget_ph_))
		{
			dg14_delete_deque.push_back(it);
		}
		else if (it->gadget_ph_->collision_hit_ != 0)
		{
			dg14_delete_deque.push_back(it);
		}
	}
	while (!dg14_delete_deque.empty())
	{
		dg14_wait_list_.splice(dg14_wait_list_.begin(), move(dg14_attack_list_[static_cast<int>(type)]), dg14_delete_deque.front());
		dg14_delete_deque.pop_front();
	}

	//***********************
	// Gadget1414 削除処理
	//***********************
	for (auto it = dg1414_attack_list_[static_cast<int>(type)].begin(); it != dg1414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// 表示領域の限界を超えた
		// 他のオブジェクトと衝突した
		if (!nya_position_->InScreen(it->gadget_ph_))
		{
			dg1414_delete_deque.push_back(it);
		}
		else if (it->gadget_ph_->collision_hit_ != 0)
		{
			it->effect_ep_->grid_x_ = (int)it->gadget_ph_->grid_x_;
			it->effect_ep_->grid_y_ = (int)it->gadget_ph_->grid_y_;
			nya_effect_->Draw(it->effect_ep_, it->effect_gp_, it->effect_type_);
			dg1414_delete_deque.push_back(it);
		}
	}
	while (!dg1414_delete_deque.empty())
	{
		dg1414_wait_list_.splice(dg1414_wait_list_.begin(), move(dg1414_attack_list_[static_cast<int>(type)]), dg1414_delete_deque.front());
		dg1414_delete_deque.pop_front();
	}

	//****************************
	// gadget14 削除以外の処理
	//****************************
	for (auto& e : dg14_attack_list_[static_cast<int>(type)])
	{
		// 移動処理
		e.gadget_ph_->grid_x_ += e.move_x_;
		e.gadget_ph_->grid_y_ += e.move_y_;
		
		// 描画処理
		e.gadget_gp_->draw_grid_cx_ = (int)e.gadget_ph_->grid_x_;
		e.gadget_gp_->draw_grid_cy_ = (int)e.gadget_ph_->grid_y_;
		nya_graphic_->Draw(e.gadget_gp_, type);

		// 衝突判定処理
		nya_position_->Collision(e.gadget_ph_, type);
	}

	//****************************
	// gadget1414 削除以外の処理
	//****************************
	for (auto& e : dg1414_attack_list_[static_cast<int>(type)])
	{
		// 移動処理
		e.gadget_ph_->grid_x_ += e.move_x_;
		e.gadget_ph_->grid_y_ += e.move_y_;
		
		// 描画処理
		e.gadget_gp_->draw_grid_cx_ = (int)e.gadget_ph_->grid_x_;
		e.gadget_gp_->draw_grid_cy_ = (int)e.gadget_ph_->grid_y_;
		nya_graphic_->Draw(e.gadget_gp_, type);

		// 衝突判定処理
		nya_position_->Collision(e.gadget_ph_, type);
	}

}


