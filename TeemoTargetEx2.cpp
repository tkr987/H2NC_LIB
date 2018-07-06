#include <tuple>
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaInput.h"
#include "NyaInterface.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "TeemoEnum.h"
#include "TeemoTargetEx2.h"

#define __DEBUG__

using namespace std;
using namespace H2NLIB;

//*************************************
// Act1(), Draw1() で使うクラス
//*************************************

TeemoExDevice211::TeemoExDevice211()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_BLUE3;
	dpx_->move_speed_ = 2;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue3.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice211::~TeemoExDevice211()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExDevice212::TeemoExDevice212()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 11;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice212::~TeemoExDevice212()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExCube21::TeemoExCube21()
{
	device_gap_angle_ = 40;
	death_epx_ = new EffectPropertyX1;
	death_epx_->interval_time_frame_ = 3;
	death_gpx_ = new GraphicPropertyX4;
	death_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &death_gpx_->file_);
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.01;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoExCube21::~TeemoExCube21()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

//**********************************
// Act2(), Draw2() で使うクラス
//**********************************
TeemoExDevice221::TeemoExDevice221()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_BLUE2;
	dpx_->move_speed_ = 6;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue2.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice221::~TeemoExDevice221()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExDevice222::TeemoExDevice222()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 8;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice222::~TeemoExDevice222()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExDevice223::TeemoExDevice223()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 8;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice223::~TeemoExDevice223()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExCube22::TeemoExCube22()
{
	death_epx_ = new EffectPropertyX1;
	death_epx_->interval_time_frame_ = 3;
	death_gpx_ = new GraphicPropertyX4;
	death_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &death_gpx_->file_);
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.01;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoExCube22::~TeemoExCube22()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

//*************************************
// Act3(), Draw3() で使うクラス
//*************************************

TeemoExDevice232::TeemoExDevice232()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 11;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice232::~TeemoExDevice232()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExCube23::TeemoExCube23()
{
	death_epx_ = new EffectPropertyX1;
	death_epx_->interval_time_frame_ = 3;
	death_gpx_ = new GraphicPropertyX4;
	death_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &death_gpx_->file_);
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoExCube23::~TeemoExCube23()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

//*****************
// TeemoExMain
//*****************

TeemoExMain2::TeemoExMain2() : health_max_(15000) 
{
	death1_epx_ = new EffectPropertyX1;
	death1_epx_->interval_time_frame_ = 3;
	death1_gpx_ = new GraphicPropertyX4;
	death1_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &death1_gpx_->file_);

	death2_epx_ = new EffectPropertyX1;
	death2_epx_->interval_time_frame_ = 3;
	death2_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile(8, 8, "img/target/death2.png", &death2_gpx_->file_);

	gpx_ = new GraphicPropertyX4;
	phandle_ = NyaPosition::CreateHandle();
	NyaGraphic::LoadGraphicFile("img/target/teemo_ex2.png", &gpx_->file_);
	phandle_->health_ = health_max_;
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -200;

}

TeemoExMain2::~TeemoExMain2()
{
	delete gpx_;
	gpx_ = nullptr;
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
}

//*****************
// TeemoTargetEx
//*****************

TeemoTargetEx2::TeemoTargetEx2(void)
{
	count_frame_ = 0;
	mode_ = 1;
	NyaInterface::GetHandleWarning()->LoadSound("sound/warning.wav", 20);
}

TeemoTargetEx2::~TeemoTargetEx2(void)
{
	NyaInterface::GetHandleWarning()->DeleteSound();
}

//***************************
// TeemoTargetEx メンバ関数
//***************************

void TeemoTargetEx2::Act(void)
{
	switch (mode_)
	{
	case 1:
		Act1();
		break;
	case 2:
		Act2();
		break;
	case 3:
		Act3();
		break;
	}

	count_frame_++;
}

void TeemoTargetEx2::Draw(void)
{
	switch (mode_)
	{
	case 1:
		Draw1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 65)
		{
			count_frame_ = 0;
			mode_ = 2;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
		}
		break;
	case 2:
		Draw2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 35)
		{
			count_frame_ = 0;
			mode_ = 3;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
		}
		break;
	case 3:
		Draw3();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 0)
		{
			count_frame_ = 0;
			mode_ = 4;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
		}
		break;
	case 4:
		Draw4();
		break;
	}
}

void TeemoTargetEx2::Act1(void)
{
	PositionHandle phandle_user;

	if (count_frame_ == 1)
	{	// 行動開始1フレーム目
		NyaInterface::GetHandleHealth()->valid_ = true;
		NyaInterface::GetHandleWarning()->draw_valid_ = true;
		NyaInterface::GetHandleWarning()->sound_valid_ = true;
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);
	}

	if (count_frame_ == FPS_MAX * 3)
	{	// cubeを初期位置へ配置
		cube21_collection_[0].phandle_->grid_x_ = 50;
		cube21_collection_[0].phandle_->grid_y_ = 50;
		cube21_collection_[1].phandle_->grid_x_ = SCREEN_MAX_X - 50;
		cube21_collection_[1].phandle_->grid_y_ = 50;
		cube21_collection_[2].phandle_->grid_x_ = SCREEN_MAX_X - 50;
		cube21_collection_[2].phandle_->grid_y_ = SCREEN_MAX_Y - 60;
		cube21_collection_[3].phandle_->grid_x_ = 50;
		cube21_collection_[3].phandle_->grid_y_ = SCREEN_MAX_Y - 60;
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube21_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 4)
		return;

	if (count_frame_ % (FPS_MAX * 3) == FPS_MAX)
	{	// main移動処理
		int move_end_x = (int)main_.phandle_->grid_x_ + NyaInput::GetRand(-50, 50);
		if (250 <= move_end_x  && move_end_x < SCREEN_MAX_X - 250)
			NyaPosition::MoveGridMode(main_.phandle_, move_end_x, main_.phandle_->grid_y_, FPS_MAX);
	}


	if (count_frame_ % 30 == 0)
	{	// main攻撃処理
		main_.device211_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device211_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 20; way++)
		{
			main_.device211_.dpx_->move_angle_deg_ += 4;
			NyaDevice::Attack1414(main_.device211_.dpx_, main_.device211_.gadget_gpx_, main_.device211_.epx_, main_.device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device211_.dpx_->move_angle_deg_ += (180 - 80);
		for (int way = 0; way < 20; way++)
		{
			main_.device211_.dpx_->move_angle_deg_ += 4;
			NyaDevice::Attack1414(main_.device211_.dpx_, main_.device211_.gadget_gpx_, main_.device211_.epx_, main_.device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device211_.dpx_->move_angle_deg_ += (180 - 80 - 30);
	}

	if (count_frame_ % 4 == 0 && count_frame_ % (FPS_MAX * 8) < FPS_MAX * 3)
	{	// cube攻撃処理
		for (int cube_index = 0; cube_index < 4; cube_index++)
		{
			NyaPosition::FindHandle("user_main_handle", &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
			cube21_collection_[cube_index].device212_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ += cube21_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.gadget_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ -= cube21_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.gadget_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			if (6 < cube21_collection_[cube_index].device_gap_angle_)
				cube21_collection_[cube_index].device_gap_angle_--;
		}
	}
	else if (count_frame_ % 4 == 0 && FPS_MAX * 3 <= count_frame_ % (FPS_MAX * 8))
	{	// cube攻撃処理
		for (int cube_index = 0; cube_index < 4; cube_index++)
		{
			NyaPosition::FindHandle("user_main_handle", &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
			cube21_collection_[cube_index].device212_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ += cube21_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.gadget_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ -= cube21_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.gadget_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			if (cube21_collection_[cube_index].device_gap_angle_ < 40)
				cube21_collection_[cube_index].device_gap_angle_ ++;
		}
	}
}

void TeemoTargetEx2::Act2(void)
{
	// mainを初期位置に移動させる
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 2);

	if (count_frame_ == FPS_MAX * 3)
	{	// cubeを初期位置に移動させる
		cube22_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_;
		cube22_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_;
		cube22_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_;
		cube22_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_;
		NyaPosition::MoveGridMode(cube22_collection_[0].phandle_, main_.phandle_->grid_x_ - 100, main_.phandle_->grid_y_ - 50, FPS_MAX * 2);
		NyaPosition::MoveGridMode(cube22_collection_[1].phandle_, main_.phandle_->grid_x_ + 100, main_.phandle_->grid_y_ - 50, FPS_MAX * 2);
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube22_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 5)
		return;

	if (count_frame_ % (FPS_MAX * 3) == FPS_MAX)
	{	// main移動処理
		int move_end_x = (int)main_.phandle_->grid_x_ + NyaInput::GetRand(-50, 50);
		if (250 <= move_end_x  && move_end_x < SCREEN_MAX_X - 250)
			NyaPosition::MoveGridMode(main_.phandle_, move_end_x, main_.phandle_->grid_y_, FPS_MAX);
	}

	// cube座標更新
	cube22_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube22_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_;
	cube22_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube22_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_;

	if (count_frame_ % (FPS_MAX * 3) == 0)
	{	// main攻撃処理
		main_.device221_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device221_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device221_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		for (int way = 0; way < 72; way++)
		{
			main_.device221_.dpx_->move_angle_deg_ += 5;
			NyaDevice::Attack1414(main_.device221_.dpx_, main_.device221_.gadget_gpx_, main_.device221_.epx_, main_.device221_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}

	if (count_frame_ % 20 == 0)
	{	// cube攻撃処理
		for (int way = 0; way < 4; way ++)
		{
			double gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ - 90));
			double gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ - 90));
			cube22_collection_[0].device222_.dpx_->create_x_ = cube22_collection_[0].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[0].device222_.dpx_->create_y_ = cube22_collection_[0].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 5; delay++)
			{
				cube22_collection_[0].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[0].device222_.dpx_, cube22_collection_[0].device222_.gadget_gpx_, cube22_collection_[0].device222_.epx_, cube22_collection_[0].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ + 90));
			gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ + 90));
			cube22_collection_[0].device222_.dpx_->create_x_ = cube22_collection_[0].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[0].device222_.dpx_->create_y_ = cube22_collection_[0].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 5; delay++)
			{
				cube22_collection_[0].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[0].device222_.dpx_, cube22_collection_[0].device222_.gadget_gpx_, cube22_collection_[0].device222_.epx_, cube22_collection_[0].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube22_collection_[0].device222_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		}
		for (int way = 0; way < 4; way ++)
		{
			double gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ - 90));
			double gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ - 90));
			cube22_collection_[1].device222_.dpx_->create_x_ = cube22_collection_[1].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[1].device222_.dpx_->create_y_ = cube22_collection_[1].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 5; delay++)
			{
				cube22_collection_[1].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[1].device222_.dpx_, cube22_collection_[1].device222_.gadget_gpx_, cube22_collection_[1].device222_.epx_, cube22_collection_[1].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ + 90));
			gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ + 90));
			cube22_collection_[1].device222_.dpx_->create_x_ = cube22_collection_[1].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[1].device222_.dpx_->create_y_ = cube22_collection_[1].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 5; delay++)
			{
				cube22_collection_[1].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[1].device222_.dpx_, cube22_collection_[1].device222_.gadget_gpx_, cube22_collection_[1].device222_.epx_, cube22_collection_[1].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube22_collection_[1].device222_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		}
	}
	if (count_frame_ % 20 == 10)
	{	// cube攻撃処理
		for (int way = 0; way < 4; way ++)
		{
			double gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ - 90));
			double gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ - 90));
			cube22_collection_[0].device222_.dpx_->create_x_ = cube22_collection_[0].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[0].device222_.dpx_->create_y_ = cube22_collection_[0].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 5; delay++)
			{
				cube22_collection_[0].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[0].device222_.dpx_, cube22_collection_[0].device222_.gadget_gpx_, cube22_collection_[0].device222_.epx_, cube22_collection_[0].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ + 90));
			gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ + 90));
			cube22_collection_[0].device222_.dpx_->create_x_ = cube22_collection_[0].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[0].device222_.dpx_->create_y_ = cube22_collection_[0].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 5; delay++)
			{
				cube22_collection_[0].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[0].device222_.dpx_, cube22_collection_[0].device222_.gadget_gpx_, cube22_collection_[0].device222_.epx_, cube22_collection_[0].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube22_collection_[0].device222_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		}
		for (int way = 0; way < 4; way ++)
		{
			double gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ - 90));
			double gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ - 90));
			cube22_collection_[1].device222_.dpx_->create_x_ = cube22_collection_[1].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[1].device222_.dpx_->create_y_ = cube22_collection_[1].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 5; delay++)
			{
				cube22_collection_[1].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[1].device222_.dpx_, cube22_collection_[1].device222_.gadget_gpx_, cube22_collection_[1].device222_.epx_, cube22_collection_[1].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ + 90));
			gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ + 90));
			cube22_collection_[1].device222_.dpx_->create_x_ = cube22_collection_[1].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[1].device222_.dpx_->create_y_ = cube22_collection_[1].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 5; delay++)
			{
				cube22_collection_[1].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[1].device222_.dpx_, cube22_collection_[1].device222_.gadget_gpx_, cube22_collection_[1].device222_.epx_, cube22_collection_[1].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube22_collection_[1].device222_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		}
	}
}

void TeemoTargetEx2::Act3(void)
{
	PositionHandle phandle_user;

	// main初期位置へ移動
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 2);

	if (count_frame_ == FPS_MAX * 3)
	{	// cube初期位置へ移動
		for (auto& e : cube23_collection_)
		{
			e.phandle_->grid_x_ = main_.phandle_->grid_x_;
			e.phandle_->grid_y_ = main_.phandle_->grid_y_;
		}
		for (int i = 0; i < 5; i++)
			NyaPosition::MoveGridMode(cube23_collection_[i].phandle_, main_.phandle_->grid_x_ - (5 - i) * 70, 80, FPS_MAX * 2);
		for (int i = 5; i < 10; i++)
			NyaPosition::MoveGridMode(cube23_collection_[i].phandle_, main_.phandle_->grid_x_ + (i - 4) * 70, 80, FPS_MAX * 2);
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube23_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 5)
		return;

	// main移動処理
	if (count_frame_ % FPS_MAX == 0)
	{
		int move_end_x = (int)main_.phandle_->grid_x_ + NyaInput::GetRand(-20, 20);
		int move_end_y = (int)main_.phandle_->grid_y_ + NyaInput::GetRand(-20, 20);
		if (SCREEN_MIN_X + 250 < move_end_x  && move_end_x < SCREEN_MAX_X - 250 && SCREEN_MIN_Y + 140 < move_end_y && move_end_y < SCREEN_MIN_Y + 200)
		NyaPosition::MoveGridMode(main_.phandle_, move_end_x, move_end_y, FPS_MAX - 3);
	}

	if (count_frame_ % FPS_MAX * 2 == 0)
	{
		// cube攻撃処理
		int cube_index = 3;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.gadget_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 6;
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.gadget_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 0;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 9;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24)
	{
		// cube攻撃処理
		int cube_index = 4;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.gadget_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 5;
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.gadget_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 1;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 8;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 2)
	{
		// cube攻撃処理
		int cube_index = 0;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.gadget_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 9;
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.gadget_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 2;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 7;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 3)
	{
		// cube攻撃処理
		int cube_index = 1;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.gadget_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 8;
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.gadget_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 3;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 6;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 4)
	{
		// cube攻撃処理
		int cube_index = 2;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.gadget_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 7;
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.gadget_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 4;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 5;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
}

void TeemoTargetEx2::Draw1(void)
{
	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// ヘルスバー(%)の表示をする
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	for (auto& e : cube21_collection_)
	{
		// cube拡大
		if (e.gpx_->extend_rate_ < 0.4)
			e.gpx_->extend_rate_ += 0.01;
		// cube描画
		if (count_frame_ % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % 5;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 65)
	{	// cube爆発
		for (auto& e : cube21_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void TeemoTargetEx2::Draw2(void)
{
	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// ヘルスの表示をする
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	if (count_frame_ < FPS_MAX * 3)
		return;

	for (auto& e : cube22_collection_)
	{
		// cube拡大
		if (e.gpx_->extend_rate_ < 0.4)
			e.gpx_->extend_rate_ += 0.01;
		// cube描画
		if (count_frame_ % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % 5;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 35)
	{	// cube爆発
		for (auto& e : cube22_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void TeemoTargetEx2::Draw3(void)
{
	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// ヘルスバー(%)の表示をする
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	for (auto& e : cube23_collection_)
	{	// cube描画
		if (count_frame_ % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % 5;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 0)
	{	// cube爆発
		for (auto& e : cube23_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void TeemoTargetEx2::Draw4(void)
{
	if (count_frame_ < 30 * 7)
	{
		if (count_frame_ % 30 == 0)
		{	//小爆発処理
			main_.death1_epx_->grid_x_ = main_.phandle_->grid_x_ + NyaInput::GetRand(-30, 30);
			main_.death1_epx_->grid_y_ = main_.phandle_->grid_y_ + NyaInput::GetRand(-30, 30);
			NyaEffect::Draw(main_.death1_epx_, main_.death1_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}

	if (count_frame_ == 30 * 8)
	{	// 大爆発処理
		main_.death2_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death2_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death2_epx_, main_.death2_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaGraphic::Swing();
	}

	if (count_frame_ < 30 * 10)
	{	// main描画
		main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
		main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
		NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	}

	// ヘルスバー(%)の表示をする
	// ただし、ヘルス0以下のときゲージ0(%)として表示する
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
	else
		NyaInterface::GetHandleHealth()->value_ = 0;
}
