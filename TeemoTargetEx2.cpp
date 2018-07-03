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
// Act1(), Draw1() で使用するクラス
//*************************************

TeemoExDevice211::TeemoExDevice211()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 5;
	dpx_->move_speed_ = 10;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
};

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

TeemoExCube21::TeemoExCube21()
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


TeemoExMain2::TeemoExMain2() : health_max_(10000) 
{
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

TeemoTargetEx2::TeemoTargetEx2(void)
{
	count_frame_ = 0;
	NyaInterface::GetHandleWarning()->LoadSound("sound/warning.wav", 20);
}

TeemoTargetEx2::~TeemoTargetEx2(void)
{
	NyaInterface::GetHandleWarning()->DeleteSound();
}


void TeemoTargetEx2::MissionRun(void)
{
	int mode = 1;

	switch (mode)
	{
	case 1:
		Act1();
		Draw1();
		break;
	}

	count_frame_++;
}


void TeemoTargetEx2::Act1(void)
{
	InterfaceHandleMissionClear* ihandle_mission_clear;
	InterfaceHandleMissionEx* ihandle_mission_ex;
	InterfaceHandleSkill *ihandle_mission_skill;
	InterfaceHandleWarning* ihandle_warning;
	PositionHandle phandle_user;

	// 行動開始1フレーム目
	// mission ex モードをtrueにする
	// mission warning 表示を実行する
	// 初期位置へ移動する
	if (count_frame_ == 1)
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->valid_ = true;
		ihandle_warning = NyaInterface::GetHandleWarning();
		ihandle_warning->draw_valid_ = true;
		ihandle_warning->sound_valid_ = true;
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);
	}

	if (count_frame_ == FPS_MAX * 4)
	{
		for (int i = 0; i < 10; i++)
		{
			cube21_collection_[i].phandle_->grid_x_ = main_.phandle_->grid_x_;
			cube21_collection_[i].phandle_->grid_y_ = main_.phandle_->grid_y_;
		}
		for (int i = 0; i < 5; i++)
			NyaPosition::MoveGridMode(cube21_collection_[i].phandle_, main_.phandle_->grid_x_ - (5 - i) * 70, 80, FPS_MAX * 2);
		for (int i = 5; i < 10; i++)
			NyaPosition::MoveGridMode(cube21_collection_[i].phandle_, main_.phandle_->grid_x_ + (i - 4) * 70, 80, FPS_MAX * 2);
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_damage_);
	for (int i = 0; i < 10; i++)
	{
		NyaPosition::Collide(cube21_collection_[i].phandle_, eOBJECT::TARGET1);
		ihandle_mission_skill->AddExp(cube21_collection_[i].phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= cube21_collection_[i].phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 6)
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
		cube21_collection_[cube_index].device211_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
		cube21_collection_[cube_index].device211_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube21_collection_[cube_index].device211_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device211_.dpx_, cube21_collection_[cube_index].device211_.gadget_gpx_, cube21_collection_[cube_index].device211_.epx_, cube21_collection_[cube_index].device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 6;
		cube21_collection_[cube_index].device211_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
		cube21_collection_[cube_index].device211_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube21_collection_[cube_index].device211_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device211_.dpx_, cube21_collection_[cube_index].device211_.gadget_gpx_, cube21_collection_[cube_index].device211_.epx_, cube21_collection_[cube_index].device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 0;
		move_x = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_x_ - 150, cube21_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_y_ - 100, cube21_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube21_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 9;
		move_x = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_x_ - 150, cube21_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_y_ - 100, cube21_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube21_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24)
	{
		// cube攻撃処理
		int cube_index = 4;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
		cube21_collection_[cube_index].device211_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube21_collection_[cube_index].device211_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device211_.dpx_, cube21_collection_[cube_index].device211_.gadget_gpx_, cube21_collection_[cube_index].device211_.epx_, cube21_collection_[cube_index].device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 5;
		cube21_collection_[cube_index].device211_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
		cube21_collection_[cube_index].device211_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube21_collection_[cube_index].device211_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device211_.dpx_, cube21_collection_[cube_index].device211_.gadget_gpx_, cube21_collection_[cube_index].device211_.epx_, cube21_collection_[cube_index].device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 1;
		move_x = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_x_ - 150, cube21_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_y_ - 100, cube21_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube21_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 8;
		move_x = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_x_ - 150, cube21_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_y_ - 100, cube21_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube21_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 2)
	{
		// cube攻撃処理
		int cube_index = 0;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
		cube21_collection_[cube_index].device211_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube21_collection_[cube_index].device211_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device211_.dpx_, cube21_collection_[cube_index].device211_.gadget_gpx_, cube21_collection_[cube_index].device211_.epx_, cube21_collection_[cube_index].device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 9;
		cube21_collection_[cube_index].device211_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
		cube21_collection_[cube_index].device211_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube21_collection_[cube_index].device211_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device211_.dpx_, cube21_collection_[cube_index].device211_.gadget_gpx_, cube21_collection_[cube_index].device211_.epx_, cube21_collection_[cube_index].device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 2;
		move_x = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_x_ - 150, cube21_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_y_ - 100, cube21_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube21_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 7;
		move_x = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_x_ - 150, cube21_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_y_ - 100, cube21_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube21_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 3)
	{
		// cube攻撃処理
		int cube_index = 1;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
		cube21_collection_[cube_index].device211_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube21_collection_[cube_index].device211_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device211_.dpx_, cube21_collection_[cube_index].device211_.gadget_gpx_, cube21_collection_[cube_index].device211_.epx_, cube21_collection_[cube_index].device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 8;
		cube21_collection_[cube_index].device211_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
		cube21_collection_[cube_index].device211_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube21_collection_[cube_index].device211_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device211_.dpx_, cube21_collection_[cube_index].device211_.gadget_gpx_, cube21_collection_[cube_index].device211_.epx_, cube21_collection_[cube_index].device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 3;
		move_x = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_x_ - 150, cube21_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_y_ - 100, cube21_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube21_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 6;
		move_x = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_x_ - 150, cube21_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_y_ - 100, cube21_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube21_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 4)
	{
		// cube攻撃処理
		int cube_index = 2;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
		cube21_collection_[cube_index].device211_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube21_collection_[cube_index].device211_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device211_.dpx_, cube21_collection_[cube_index].device211_.gadget_gpx_, cube21_collection_[cube_index].device211_.epx_, cube21_collection_[cube_index].device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 7;
		cube21_collection_[cube_index].device211_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
		cube21_collection_[cube_index].device211_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
		cube21_collection_[cube_index].device211_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube21_collection_[cube_index].device211_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device211_.dpx_, cube21_collection_[cube_index].device211_.gadget_gpx_, cube21_collection_[cube_index].device211_.epx_, cube21_collection_[cube_index].device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 4;
		move_x = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_x_ - 150, cube21_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_y_ - 100, cube21_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube21_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 5;
		move_x = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_x_ - 150, cube21_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube21_collection_[cube_index].phandle_->grid_y_ - 100, cube21_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube21_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
}

void TeemoTargetEx2::Draw1(void)
{
	InterfaceHandleMissionEx* ihandle_mission_ex;
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	// 本体の描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// ヘルスバー(%)の表示をする
	// ただし、ヘルス0以下のときゲージ0(%)として表示する
	if (0 < main_.phandle_->health_) 
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100;
	}
	else
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->value_ = 0;
	}
}

