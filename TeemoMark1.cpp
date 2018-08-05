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
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetAttackOrange1(dpx_, device_gpx_, epx_, effect_gpx_);
}

TeemoDevice111::~TeemoDevice111()
{
	delete dpx_;
	dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
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
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

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
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

//*************************************
// Act2(), Draw2() で使うクラス
//*************************************

TeemoDevice121::TeemoDevice121()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 9;
	TeemoFactory::TargetAttackRed2(dpx_, device_gpx_, epx_, effect_gpx_);
}

TeemoDevice121::~TeemoDevice121()
{
	delete dpx_;
	dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

//*****************
// TeemoMain
//*****************

TeemoMain1::TeemoMain1() : exp_(50000), health_max_(22000) 
{
	lock_ = new TeemoLock(eLOCK::TEEMO_MARK1);

	death1_epx_ = new EffectPropertyX1;
	death1_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death1_epx_, death1_gpx_);
	death1_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death1.wav", &death1_spx_->file_);
	NyaSound::ChangeVolume(&death1_spx_->file_, 50);

	death2_epx_ = new EffectPropertyX1;
	death2_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath2(death2_epx_, death2_gpx_);
	death2_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death2.wav", &death2_spx_->file_);
	NyaSound::ChangeVolume(&death2_spx_->file_, 40);
	gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/teemo_mark1.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -200;
	phandle_->health_ = health_max_;
}

TeemoMain1::~TeemoMain1()
{
	NyaGraphic::Delete(&gpx_->file_);
	NyaSound::Delete(&death1_spx_->file_);
	NyaSound::Delete(&death2_spx_->file_);

	delete lock_;
	lock_ = nullptr;
	delete death1_epx_;
	death1_epx_ = nullptr;
	delete death1_gpx_;
	death1_gpx_ = nullptr;
	delete death1_spx_;
	death1_spx_ = nullptr;
	delete death2_epx_;
	death2_epx_ = nullptr;
	delete death2_gpx_;
	death2_gpx_ = nullptr;
	delete death2_spx_;
	death2_spx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

TeemoMark1::TeemoMark1(void)
{
	count_frame_ = 0;
	mode_ = 1;

	warning_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/warning.wav", &warning_spx_->file_);
	NyaSound::ChangeVolume(&warning_spx_->file_, 30);
}

TeemoMark1::~TeemoMark1(void)
{
	NyaSound::Delete(&warning_spx_->file_);

	delete warning_spx_;
	warning_spx_ = nullptr;
}

void TeemoMark1::Act(void)
{
	switch(mode_)
	{ 
	case 1:
		Act1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK1_MODE1_MIN_HEALTH)
		{
			count_frame_ = 0;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaSound::Play(main_.death1_spx_);
		}
		break;
	case 2:
		Act2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_MARK1_MODE2_MIN_HEALTH)
		{
			count_frame_ = 0;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
		}
		break;
	case 3:
		if (count_frame_ == 30 * 8)
		{
			NyaInterface::GetHandleLife()->value_ += 1;
			NyaInterface::GetHandleSkill()->AddExp(main_.exp_);
			NyaSound::Play(main_.death2_spx_);
		}
		if (count_frame_ == 30 * 18)
			NyaInterface::GetHandleClear()->valid_ = true;
		break;
	}


	if (FPS_MAX * 60 * 4 < count_frame_)
		NyaInterface::GetHandleLife()->value_ = 0;
	count_frame_++;
}

void TeemoMark1::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK1_MODE1_MIN_HEALTH)
			mode_ = 2;
		break;
	case 2:
		Draw2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_MARK1_MODE2_MIN_HEALTH)
			mode_ = 3;
		break;
	case 3:
		Draw3();
		break;
	}
}

void TeemoMark1::Act1(void)
{
	PositionHandle phandle_user;

	if (count_frame_ == 1)
	{	// 行動開始1フレーム目
		NyaInterface::GetHandleHealth()->valid_ = true;
		NyaInterface::GetHandleWarning()->valid_ = true;
		NyaSound::Play(warning_spx_);
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);
		cube11_collection_[0].move_angle_ = 180;
		cube11_collection_[1].move_angle_ = 0;
	}

	cube11_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 150;
	cube11_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_;
	cube11_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 150;
	cube11_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_;

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

	if (FPS_MAX * 5 <= count_frame_ && count_frame_ < FPS_MAX * 11)
	{
		if (count_frame_ % 30 == 0)
		{
			double move_base_angle = NyaInput::GetRand(55, 125);
			DevicePropertyX1* cube_dpx = cube11_collection_[0].device111_.dpx_;
			GraphicPropertyX4* cube_gadget_gpx = cube11_collection_[0].device111_.device_gpx_;
			EffectPropertyX1* cube_epx = cube11_collection_[0].device111_.epx_;
			GraphicPropertyX4* cube_effect_gpx = cube11_collection_[0].device111_.effect_gpx_;
			cube_dpx->create_x_ = cube11_collection_[0].phandle_->grid_x_;
			cube_dpx->create_y_ = cube11_collection_[0].phandle_->grid_y_;
			cube_dpx->move_speed_ = 10;
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
			GraphicPropertyX4* cube_gadget_gpx = cube11_collection_[1].device111_.device_gpx_;
			EffectPropertyX1* cube_epx = cube11_collection_[1].device111_.epx_;
			GraphicPropertyX4* cube_effect_gpx = cube11_collection_[1].device111_.effect_gpx_;
			cube_dpx->create_x_ = cube11_collection_[1].phandle_->grid_x_;
			cube_dpx->create_y_ = cube11_collection_[1].phandle_->grid_y_;
			cube_dpx->move_speed_ = 10;
			for (int way = 0; way < 12; way++)
			{
				cube_dpx->delay_time_frame_ = way;
				cube_dpx->move_angle_deg_ = move_base_angle + NyaInput::GetRand(-10.0, 10.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
	}

	if (FPS_MAX * 12 <= count_frame_ && count_frame_ < FPS_MAX * 16)
	{
		// cube 移動
		int cube_index = 0;
		cube11_collection_[cube_index].move_angle_  += 1.5;
		cube11_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_ + 150 * cos(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));
		cube11_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_ + 150 * sin(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));
		cube_index = 1;
		cube11_collection_[cube_index].move_angle_  += 1.5;
		cube11_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_ + 150 * cos(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));
		cube11_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_ + 150 * sin(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));

		if (count_frame_ % 60 == 0)
		{	// cube 攻撃
			cube_index = 0;
			DevicePropertyX1* cube_dpx = cube11_collection_[cube_index].device111_.dpx_;
			GraphicPropertyX4* cube_gadget_gpx = cube11_collection_[cube_index].device111_.device_gpx_;
			EffectPropertyX1* cube_epx = cube11_collection_[cube_index].device111_.epx_;
			GraphicPropertyX4* cube_effect_gpx = cube11_collection_[cube_index].device111_.effect_gpx_;
			cube_dpx->create_x_ = cube11_collection_[cube_index].phandle_->grid_x_;
			cube_dpx->create_y_ = cube11_collection_[cube_index].phandle_->grid_y_;
			cube_dpx->delay_time_frame_ = 0;
			cube_dpx->move_speed_ = 3;
			for (int way = 0; way < 37; way++)
			{
				cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
			cube_index = 1;
			cube_dpx = cube11_collection_[cube_index].device111_.dpx_;
			cube_gadget_gpx = cube11_collection_[cube_index].device111_.device_gpx_;
			cube_epx = cube11_collection_[cube_index].device111_.epx_;
			cube_effect_gpx = cube11_collection_[cube_index].device111_.effect_gpx_;
			cube_dpx->create_x_ = cube11_collection_[cube_index].phandle_->grid_x_;
			cube_dpx->create_y_ = cube11_collection_[cube_index].phandle_->grid_y_;
			cube_dpx->delay_time_frame_ = 0;
			cube_dpx->move_speed_ = 3;
			for (int way = 0; way < 37; way++)
			{	
				cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
	}
	else if (FPS_MAX * 16 <= count_frame_ && count_frame_ < FPS_MAX * 20)
	{
		// cube 移動
		int cube_index = 0;
		cube11_collection_[cube_index].move_angle_  += 1.5;
		cube11_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_ + 150 * cos(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));
		cube11_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_ + 150 * sin(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));
		cube_index = 1;
		cube11_collection_[cube_index].move_angle_  += 1.5;
		cube11_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_ + 150 * cos(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));
		cube11_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_ + 150 * sin(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));

		if (count_frame_ % 30 == 0)
		{	// cube 攻撃
			cube_index = 0;
			DevicePropertyX1* cube_dpx = cube11_collection_[cube_index].device111_.dpx_;
			GraphicPropertyX4* cube_gadget_gpx = cube11_collection_[cube_index].device111_.device_gpx_;
			EffectPropertyX1* cube_epx = cube11_collection_[cube_index].device111_.epx_;
			GraphicPropertyX4* cube_effect_gpx = cube11_collection_[cube_index].device111_.effect_gpx_;
			cube_dpx->create_x_ = cube11_collection_[cube_index].phandle_->grid_x_;
			cube_dpx->create_y_ = cube11_collection_[cube_index].phandle_->grid_y_;
			cube_dpx->delay_time_frame_ = 0;
			cube_dpx->move_speed_ = 3.5;
			for (int way = 0; way < 41; way++)
			{
				cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
			cube_index = 1;
			cube_dpx = cube11_collection_[cube_index].device111_.dpx_;
			cube_gadget_gpx = cube11_collection_[cube_index].device111_.device_gpx_;
			cube_epx = cube11_collection_[cube_index].device111_.epx_;
			cube_effect_gpx = cube11_collection_[cube_index].device111_.effect_gpx_;
			cube_dpx->create_x_ = cube11_collection_[cube_index].phandle_->grid_x_;
			cube_dpx->create_y_ = cube11_collection_[cube_index].phandle_->grid_y_;
			cube_dpx->delay_time_frame_ = 0;
			cube_dpx->move_speed_ = 3.5;
			for (int way = 0; way < 41; way++)
			{	
				cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
	}
	else if (FPS_MAX * 20 <= count_frame_ && count_frame_ < FPS_MAX * 24)
	{
		// cube 移動
		int cube_index = 0;
		cube11_collection_[cube_index].move_angle_  += 1.5;
		cube11_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_ + 150 * cos(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));
		cube11_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_ + 150 * sin(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));
		cube_index = 1;
		cube11_collection_[cube_index].move_angle_  += 1.5;
		cube11_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_ + 150 * cos(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));
		cube11_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_ + 150 * sin(NyaInput::AngleToRad(cube11_collection_[cube_index].move_angle_));

		if (count_frame_ % 15 == 0)
		{	// cube 攻撃
			cube_index = 0;
			DevicePropertyX1* cube_dpx = cube11_collection_[cube_index].device111_.dpx_;
			GraphicPropertyX4* cube_gadget_gpx = cube11_collection_[cube_index].device111_.device_gpx_;
			EffectPropertyX1* cube_epx = cube11_collection_[cube_index].device111_.epx_;
			GraphicPropertyX4* cube_effect_gpx = cube11_collection_[cube_index].device111_.effect_gpx_;
			cube_dpx->create_x_ = cube11_collection_[cube_index].phandle_->grid_x_;
			cube_dpx->create_y_ = cube11_collection_[cube_index].phandle_->grid_y_;
			cube_dpx->delay_time_frame_ = 0;
			cube_dpx->move_speed_ = 4;
			for (int way = 0; way <45; way++)
			{
				cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
			cube_index = 1;
			cube_dpx = cube11_collection_[cube_index].device111_.dpx_;
			cube_gadget_gpx = cube11_collection_[cube_index].device111_.device_gpx_;
			cube_epx = cube11_collection_[cube_index].device111_.epx_;
			cube_effect_gpx = cube11_collection_[cube_index].device111_.effect_gpx_;
			cube_dpx->create_x_ = cube11_collection_[cube_index].phandle_->grid_x_;
			cube_dpx->create_y_ = cube11_collection_[cube_index].phandle_->grid_y_;
			cube_dpx->delay_time_frame_ = 0;
			cube_dpx->move_speed_ = 4;
			for (int way = 0; way < 45; way++)
			{	
				cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
	}

	if (count_frame_ == FPS_MAX * 24)
		count_frame_ = FPS_MAX;
}

void TeemoMark1::Act2(void)
{
	if (count_frame_ < FPS_MAX * 2)
		return;

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;

	if (count_frame_ % 4 == 0)
	{	// main 攻撃
		main_.device121_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device121_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device121_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1414(main_.device121_.dpx_, main_.device121_.device_gpx_, main_.device121_.epx_, main_.device121_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device121_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1414(main_.device121_.dpx_, main_.device121_.device_gpx_, main_.device121_.epx_, main_.device121_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device121_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1414(main_.device121_.dpx_, main_.device121_.device_gpx_, main_.device121_.epx_, main_.device121_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}
}

void TeemoMark1::Draw1(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube11_collection_)
	{	// cube 描画
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

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK1_MODE1_MIN_HEALTH)
	{	// cube 爆発
		for (auto& e : cube11_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
		NyaGraphic::Swing();
	}
}

void TeemoMark1::Draw2(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);

	// ヘルス表示
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
}

void TeemoMark1::Draw3(void)
{
	if (count_frame_ < 30 * 7)
	{
		if (count_frame_ % 30 == 0)
		{	//小爆発
			main_.death1_epx_->grid_x_ = main_.phandle_->grid_x_ + NyaInput::GetRand(-30, 30);
			main_.death1_epx_->grid_y_ = main_.phandle_->grid_y_ + NyaInput::GetRand(-30, 30);
			NyaEffect::Draw(main_.death1_epx_, main_.death1_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}

	if (count_frame_ == 30 * 8)
	{	// 大爆発
		main_.death2_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death2_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death2_epx_, main_.death2_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaGraphic::Swing();
	}

	if (count_frame_ < 30 * 10)
	{	// main 描画
		main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
		main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
		NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	}

	// ヘルス表示
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
}

