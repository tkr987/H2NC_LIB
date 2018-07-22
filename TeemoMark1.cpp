#include <tuple>
#include "HNLIB.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "TeemoMark1.h"
#include "TeemoLock.h"

#define __DEBUG__

using namespace std;
using namespace HNLIB;

//*************************************
// Act1(), Draw1() で使うクラス
//*************************************

TeemoDevice111::TeemoDevice111()
{
	dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 10;
	TeemoFactory::TargetAttackOrange1(dpx_, gadget_gpx_, epx_, effect_gpx_);
}

TeemoDevice111::~TeemoDevice111()
{
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoCube11::TeemoCube11()
{
	lock_ = new TeemoLock(eLOCK::CUBE);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetCube(gpx_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoCube11::~TeemoCube11()
{
	delete lock_;
	lock_ = nullptr;
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete death_spx_;
	death_spx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

//*****************
// TeemoMain
//*****************

TeemoMain1::TeemoMain1() : health_max_(150000) 
{
	lock_ = new TeemoLock(eLOCK::TEEMO_MARK1);

	death1_epx_ = new EffectPropertyX1;
	death1_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death1_epx_, death1_gpx_);

	death2_epx_ = new EffectPropertyX1;
	death2_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath2(death2_epx_, death2_gpx_);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/teemo_mark1.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->health_ = health_max_;
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -200;
}

TeemoMain1::~TeemoMain1()
{
	NyaGraphic::Delete(&gpx_->file_);

	delete lock_;
	lock_ = nullptr;
	delete death1_epx_;
	death1_epx_ = nullptr;
	delete death1_gpx_;
	death1_gpx_ = nullptr;
	delete death2_epx_;
	death2_epx_ = nullptr;
	delete death2_gpx_;
	death2_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

TeemoMark1::TeemoMark1(void)
{
	count_frame_ = 0;
	mode_ = 1;

	// mission warning handle 設定
	NyaInterface::GetHandleWarning()->LoadSound("sound/warning.wav", 25);
}

TeemoMark1::~TeemoMark1(void)
{
	NyaInterface::GetHandleWarning()->DeleteSound();
}

void TeemoMark1::Act(void)
{
	switch(mode_)
	{ 
	case 1:
		Act1();
		break;
	}

	count_frame_++;
}

void TeemoMark1::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		break;
	}
}

void TeemoMark1::Act1(void)
{
	PositionHandle phandle_user;

	if (count_frame_ == 1)
	{	// 行動開始1フレーム目
		NyaInterface::GetHandleHealth()->valid_ = true;
		NyaInterface::GetHandleWarning()->draw_valid_ = true;
		NyaInterface::GetHandleWarning()->sound_valid_ = true;
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);
		cube11_collection_[0].move_angle_ = 180;
		cube11_collection_[1].move_angle_ = 0;
	}

	cube11_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 150;
	cube11_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_;
	cube11_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 150;
	cube11_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_;

	if (count_frame_ < FPS_MAX * 3)
		return;

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (auto& e : cube11_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (FPS_MAX * 3 <= count_frame_ && count_frame_ < FPS_MAX * 9)
	{
		if (count_frame_ % 30 == 0)
		{
			double move_base_angle = NyaInput::GetRand(55, 125);
			DevicePropertyX1* cube_dpx = cube11_collection_[0].device111_.dpx_;
			GraphicPropertyX4* cube_gadget_gpx = cube11_collection_[0].device111_.gadget_gpx_;
			EffectPropertyX1* cube_epx = cube11_collection_[0].device111_.epx_;
			GraphicPropertyX4* cube_effect_gpx = cube11_collection_[0].device111_.effect_gpx_;
			cube_dpx->create_x_ = cube11_collection_[0].phandle_->grid_x_;
			cube_dpx->create_y_ = cube11_collection_[0].phandle_->grid_y_;
			for (int way = 0; way < 12; way++)
			{
				cube_dpx->delay_time_frame_ = way;
				cube_dpx->move_angle_deg_ = move_base_angle + NyaInput::GetRand(-10.0, 10.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
		else if (count_frame_ % 30 == 15)
		{
			double move_base_angle = NyaInput::GetRand(55, 125);
			DevicePropertyX1* cube_dpx = cube11_collection_[1].device111_.dpx_;
			GraphicPropertyX4* cube_gadget_gpx = cube11_collection_[1].device111_.gadget_gpx_;
			EffectPropertyX1* cube_epx = cube11_collection_[1].device111_.epx_;
			GraphicPropertyX4* cube_effect_gpx = cube11_collection_[1].device111_.effect_gpx_;
			cube_dpx->create_x_ = cube11_collection_[1].phandle_->grid_x_;
			cube_dpx->create_y_ = cube11_collection_[1].phandle_->grid_y_;
			for (int way = 0; way < 12; way++)
			{
				cube_dpx->delay_time_frame_ = way;
				cube_dpx->move_angle_deg_ = move_base_angle + NyaInput::GetRand(-10.0, 10.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
	}

	//for (auto& e : cube11_collection_)
	//{
	//	e.move_angle_ ++;
	//	e.phandle_->grid_x_ = main_.phandle_->grid_x_ + 100 * cos(NyaInput::AngleToRad(e.move_angle_));
	//	e.phandle_->grid_y_ = main_.phandle_->grid_y_ + 100 * sin(NyaInput::AngleToRad(e.move_angle_));
	//}

	//if (count_frame_ % 4 == 0 && count_frame_ % (FPS_MAX * 8) < FPS_MAX * 3)
	//{	// cube攻撃処理
	//	for (int cube_index = 0; cube_index < 4; cube_index++)
	//	{
	//		NyaPosition::FindHandle("user", &phandle_user);
	//		cube21_collection_[cube_index].device212_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
	//		cube21_collection_[cube_index].device212_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
	//		cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
	//		cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ += cube21_collection_[cube_index].device_gap_angle_;
	//		NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.gadget_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
	//		cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
	//		cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ -= cube21_collection_[cube_index].device_gap_angle_;
	//		NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.gadget_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
	//		if (6 < cube21_collection_[cube_index].device_gap_angle_)
	//			cube21_collection_[cube_index].device_gap_angle_--;
	//	}
	//}
	//else if (count_frame_ % 4 == 0 && FPS_MAX * 3 <= count_frame_ % (FPS_MAX * 8))
	//{	// cube攻撃処理
	//	for (int cube_index = 0; cube_index < 4; cube_index++)
	//	{
	//		NyaPosition::FindHandle("user", &phandle_user);
	//		cube21_collection_[cube_index].device212_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
	//		cube21_collection_[cube_index].device212_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
	//		cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
	//		cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ += cube21_collection_[cube_index].device_gap_angle_;
	//		NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.gadget_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
	//		cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
	//		cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ -= cube21_collection_[cube_index].device_gap_angle_;
	//		NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.gadget_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
	//		if (cube21_collection_[cube_index].device_gap_angle_ < 40)
	//			cube21_collection_[cube_index].device_gap_angle_ ++;
	//	}
	//}
}

void TeemoMark1::Draw1(void)
{
	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube11_collection_)
	{
		// cube拡大
		if (e.gpx_->extend_rate_ < 0.4)
			e.gpx_->extend_rate_ += 0.01;
		// cube描画
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube ロック描画
		e.lock_->Run(e.phandle_);
	}

	// ヘルス表示
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK1_MODE1_HEALTH)
	{	// cube爆発
		for (auto& e : cube11_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

TeemoDevice121::TeemoDevice121()
{
}

TeemoDevice121::~TeemoDevice121()
{
}
