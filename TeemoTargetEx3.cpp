#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaInterface.h"
#include "NyaPosition.h"
#include "TeemoEnum.h"
#include "TeemoTargetEx3.h"

using namespace std;
using namespace H2NLIB;

//*************************************
// Act1(), Draw1() で使うクラス
//*************************************

TeemoExDevice311::TeemoExDevice311()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 11;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice311::~TeemoExDevice311()
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

TeemoExCube31::TeemoExCube31()
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

TeemoExCube31::~TeemoExCube31()
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
// Act2(), Draw2() で使うクラス
//*************************************

TeemoExDevice321::TeemoExDevice321()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_BLUE3;
	dpx_->move_speed_ = 2;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue3.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice321::~TeemoExDevice321()
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

TeemoExDevice322::TeemoExDevice322()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 11;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice322::~TeemoExDevice322()
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

TeemoExCube32::TeemoExCube32()
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

TeemoExCube32::~TeemoExCube32()
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
// TeemoEx3Main
//*****************

TeemoEx3Main::TeemoEx3Main() : /*health_max_(15000)*/ health_max_(1000)
{
	gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/teemo_ex3.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->health_ = health_max_;
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -100;
}

TeemoEx3Main::~TeemoEx3Main()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
	delete phandle_;
	phandle_ = nullptr;
}

//***********************************************
// TeemoTargetEx コンストラクタ・デストラクタ
//***********************************************

TeemoTargetEx3::TeemoTargetEx3()
{
	NyaInterface::GetHandleWarning()->LoadSound("sound/warning.wav", 20);
	count_frame_ = 0;

}


TeemoTargetEx3::~TeemoTargetEx3()
{
	NyaInterface::GetHandleWarning()->DeleteSound();
}

//***************************
// TeemoTargetEx メンバ関数
//***************************

void TeemoTargetEx3::MissionRun(void)
{
	static int mode = 1;

	switch (mode)
	{
	case 1:
		Act1();
		Draw1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 60)
		{
			count_frame_ = 0;
			mode = 2;
			NyaGraphic::Swing();
		}
		break;
	case 2:
		Act2();
		Draw2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 0)
		{
			count_frame_ = 0;
			mode = 3;
			NyaGraphic::Swing();
		}

		break;

	}

	count_frame_++;

#ifdef __DEBUG__
		NyaString::Write("design_fps_font", white, 50, 90, "[50, 90] count_frame = %u", count_frame_);
#endif
}

void TeemoTargetEx3::Act1(void)
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
			cube31_collection_[i].phandle_->grid_x_ = main_.phandle_->grid_x_;
			cube31_collection_[i].phandle_->grid_y_ = main_.phandle_->grid_y_;
		}
		for (int i = 0; i < 5; i++)
			NyaPosition::MoveGridMode(cube31_collection_[i].phandle_, main_.phandle_->grid_x_ - (5 - i) * 70, 80, FPS_MAX * 2);
		for (int i = 5; i < 10; i++)
			NyaPosition::MoveGridMode(cube31_collection_[i].phandle_, main_.phandle_->grid_x_ + (i - 4) * 70, 80, FPS_MAX * 2);
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_damage_);
	for (int i = 0; i < 10; i++)
	{
		NyaPosition::Collide(cube31_collection_[i].phandle_, eOBJECT::TARGET1);
		ihandle_mission_skill->AddExp(cube31_collection_[i].phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= cube31_collection_[i].phandle_->collision_hit_damage_;
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
		cube31_collection_[cube_index].device311_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube31_collection_[cube_index].phandle_, &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->create_x_ = cube31_collection_[cube_index].phandle_->grid_x_;
		cube31_collection_[cube_index].device311_.dpx_->create_y_ = cube31_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube31_collection_[cube_index].device311_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube31_collection_[cube_index].device311_.dpx_, cube31_collection_[cube_index].device311_.gadget_gpx_, cube31_collection_[cube_index].device311_.epx_, cube31_collection_[cube_index].device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 6;
		cube31_collection_[cube_index].device311_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube31_collection_[cube_index].phandle_, &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->create_x_ = cube31_collection_[cube_index].phandle_->grid_x_;
		cube31_collection_[cube_index].device311_.dpx_->create_y_ = cube31_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube31_collection_[cube_index].device311_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube31_collection_[cube_index].device311_.dpx_, cube31_collection_[cube_index].device311_.gadget_gpx_, cube31_collection_[cube_index].device311_.epx_, cube31_collection_[cube_index].device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 0;
		move_x = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_x_ - 150, cube31_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_y_ - 100, cube31_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube31_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 9;
		move_x = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_x_ - 150, cube31_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_y_ - 100, cube31_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube31_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24)
	{
		// cube攻撃処理
		int cube_index = 4;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube31_collection_[cube_index].phandle_, &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->create_x_ = cube31_collection_[cube_index].phandle_->grid_x_;
		cube31_collection_[cube_index].device311_.dpx_->create_y_ = cube31_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube31_collection_[cube_index].device311_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube31_collection_[cube_index].device311_.dpx_, cube31_collection_[cube_index].device311_.gadget_gpx_, cube31_collection_[cube_index].device311_.epx_, cube31_collection_[cube_index].device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 5;
		cube31_collection_[cube_index].device311_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube31_collection_[cube_index].phandle_, &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->create_x_ = cube31_collection_[cube_index].phandle_->grid_x_;
		cube31_collection_[cube_index].device311_.dpx_->create_y_ = cube31_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube31_collection_[cube_index].device311_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube31_collection_[cube_index].device311_.dpx_, cube31_collection_[cube_index].device311_.gadget_gpx_, cube31_collection_[cube_index].device311_.epx_, cube31_collection_[cube_index].device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 1;
		move_x = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_x_ - 150, cube31_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_y_ - 100, cube31_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube31_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 8;
		move_x = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_x_ - 150, cube31_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_y_ - 100, cube31_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube31_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 2)
	{
		// cube攻撃処理
		int cube_index = 0;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube31_collection_[cube_index].phandle_, &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->create_x_ = cube31_collection_[cube_index].phandle_->grid_x_;
		cube31_collection_[cube_index].device311_.dpx_->create_y_ = cube31_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube31_collection_[cube_index].device311_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube31_collection_[cube_index].device311_.dpx_, cube31_collection_[cube_index].device311_.gadget_gpx_, cube31_collection_[cube_index].device311_.epx_, cube31_collection_[cube_index].device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 9;
		cube31_collection_[cube_index].device311_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube31_collection_[cube_index].phandle_, &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->create_x_ = cube31_collection_[cube_index].phandle_->grid_x_;
		cube31_collection_[cube_index].device311_.dpx_->create_y_ = cube31_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube31_collection_[cube_index].device311_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube31_collection_[cube_index].device311_.dpx_, cube31_collection_[cube_index].device311_.gadget_gpx_, cube31_collection_[cube_index].device311_.epx_, cube31_collection_[cube_index].device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 2;
		move_x = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_x_ - 150, cube31_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_y_ - 100, cube31_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube31_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 7;
		move_x = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_x_ - 150, cube31_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_y_ - 100, cube31_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube31_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 3)
	{
		// cube攻撃処理
		int cube_index = 1;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube31_collection_[cube_index].phandle_, &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->create_x_ = cube31_collection_[cube_index].phandle_->grid_x_;
		cube31_collection_[cube_index].device311_.dpx_->create_y_ = cube31_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube31_collection_[cube_index].device311_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube31_collection_[cube_index].device311_.dpx_, cube31_collection_[cube_index].device311_.gadget_gpx_, cube31_collection_[cube_index].device311_.epx_, cube31_collection_[cube_index].device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 8;
		cube31_collection_[cube_index].device311_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube31_collection_[cube_index].phandle_, &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->create_x_ = cube31_collection_[cube_index].phandle_->grid_x_;
		cube31_collection_[cube_index].device311_.dpx_->create_y_ = cube31_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube31_collection_[cube_index].device311_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube31_collection_[cube_index].device311_.dpx_, cube31_collection_[cube_index].device311_.gadget_gpx_, cube31_collection_[cube_index].device311_.epx_, cube31_collection_[cube_index].device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 3;
		move_x = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_x_ - 150, cube31_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_y_ - 100, cube31_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube31_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 6;
		move_x = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_x_ - 150, cube31_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_y_ - 100, cube31_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube31_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 4)
	{
		// cube攻撃処理
		int cube_index = 2;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube31_collection_[cube_index].phandle_, &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->create_x_ = cube31_collection_[cube_index].phandle_->grid_x_;
		cube31_collection_[cube_index].device311_.dpx_->create_y_ = cube31_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube31_collection_[cube_index].device311_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube31_collection_[cube_index].device311_.dpx_, cube31_collection_[cube_index].device311_.gadget_gpx_, cube31_collection_[cube_index].device311_.epx_, cube31_collection_[cube_index].device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 7;
		cube31_collection_[cube_index].device311_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube31_collection_[cube_index].phandle_, &phandle_user);
		cube31_collection_[cube_index].device311_.dpx_->create_x_ = cube31_collection_[cube_index].phandle_->grid_x_;
		cube31_collection_[cube_index].device311_.dpx_->create_y_ = cube31_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 8; delay++)
		{
			cube31_collection_[cube_index].device311_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube31_collection_[cube_index].device311_.dpx_, cube31_collection_[cube_index].device311_.gadget_gpx_, cube31_collection_[cube_index].device311_.epx_, cube31_collection_[cube_index].device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cube移動処理
		double move_x, move_y;
		cube_index = 4;
		move_x = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_x_ - 150, cube31_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_y_ - 100, cube31_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube31_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 5;
		move_x = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_x_ - 150, cube31_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube31_collection_[cube_index].phandle_->grid_y_ - 100, cube31_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube31_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
}

void TeemoTargetEx3::Act2(void)
{
	InterfaceHandleSkill *ihandle_mission_skill;
	PositionHandle phandle_user;

	if (count_frame_ == 1)
	{
		cube32_collection_[0].phandle_->grid_x_ = 50;
		cube32_collection_[0].phandle_->grid_y_ = 50;
		cube32_collection_[1].phandle_->grid_x_ = SCREEN_MAX_X - 50;
		cube32_collection_[1].phandle_->grid_y_ = 50;
		cube32_collection_[2].phandle_->grid_x_ = SCREEN_MAX_X - 50;
		cube32_collection_[2].phandle_->grid_y_ = SCREEN_MAX_Y - 60;
		cube32_collection_[3].phandle_->grid_x_ = 50;
		cube32_collection_[3].phandle_->grid_y_ = SCREEN_MAX_Y - 60;
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_damage_);
	for (int i = 0; i < 4; i++)
	{
		NyaPosition::Collide(cube32_collection_[i].phandle_, eOBJECT::TARGET1);
		ihandle_mission_skill->AddExp(cube32_collection_[i].phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= cube32_collection_[i].phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 4)
		return;

	// main攻撃処理
	if (count_frame_ % 30 == 0)
	{
		main_.device321_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device321_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 20; way++)
		{
			main_.device321_.dpx_->move_angle_deg_ += 4;
			NyaDevice::Attack1414(main_.device321_.dpx_, main_.device321_.gadget_gpx_, main_.device321_.epx_, main_.device321_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device321_.dpx_->move_angle_deg_ += (180 - 80);
		for (int way = 0; way < 20; way++)
		{
			main_.device321_.dpx_->move_angle_deg_ += 4;
			NyaDevice::Attack1414(main_.device321_.dpx_, main_.device321_.gadget_gpx_, main_.device321_.epx_, main_.device321_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device321_.dpx_->move_angle_deg_ += (180 - 80 - 30);
	}

	if (count_frame_ % 4 == 0 && count_frame_ % (FPS_MAX * 8) < FPS_MAX * 3)
	{	// cube攻撃処理
		for (int cube_index = 0; cube_index < 4; cube_index++)
		{
			NyaPosition::FindHandle("user_main_handle", &phandle_user);
			cube32_collection_[cube_index].device322_.dpx_->create_x_ = cube32_collection_[cube_index].phandle_->grid_x_;
			cube32_collection_[cube_index].device322_.dpx_->create_y_ = cube32_collection_[cube_index].phandle_->grid_y_;
			cube32_collection_[cube_index].device322_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube32_collection_[cube_index].phandle_, &phandle_user);
			cube32_collection_[cube_index].device322_.dpx_->move_angle_deg_ += cube32_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube32_collection_[cube_index].device322_.dpx_, cube32_collection_[cube_index].device322_.gadget_gpx_, cube32_collection_[cube_index].device322_.epx_, cube32_collection_[cube_index].device322_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			cube32_collection_[cube_index].device322_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube32_collection_[cube_index].phandle_, &phandle_user);
			cube32_collection_[cube_index].device322_.dpx_->move_angle_deg_ -= cube32_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube32_collection_[cube_index].device322_.dpx_, cube32_collection_[cube_index].device322_.gadget_gpx_, cube32_collection_[cube_index].device322_.epx_, cube32_collection_[cube_index].device322_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			if (6 < cube32_collection_[cube_index].device_gap_angle_)
				cube32_collection_[cube_index].device_gap_angle_--;
		}
	}
	else if (count_frame_ % 4 == 0 && FPS_MAX * 3 <= count_frame_ % (FPS_MAX * 8))
	{	// cube攻撃処理
		for (int cube_index = 0; cube_index < 4; cube_index++)
		{
			NyaPosition::FindHandle("user_main_handle", &phandle_user);
			cube32_collection_[cube_index].device322_.dpx_->create_x_ = cube32_collection_[cube_index].phandle_->grid_x_;
			cube32_collection_[cube_index].device322_.dpx_->create_y_ = cube32_collection_[cube_index].phandle_->grid_y_;
			cube32_collection_[cube_index].device322_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube32_collection_[cube_index].phandle_, &phandle_user);
			cube32_collection_[cube_index].device322_.dpx_->move_angle_deg_ += cube32_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube32_collection_[cube_index].device322_.dpx_, cube32_collection_[cube_index].device322_.gadget_gpx_, cube32_collection_[cube_index].device322_.epx_, cube32_collection_[cube_index].device322_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			cube32_collection_[cube_index].device322_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube32_collection_[cube_index].phandle_, &phandle_user);
			cube32_collection_[cube_index].device322_.dpx_->move_angle_deg_ -= cube32_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube32_collection_[cube_index].device322_.dpx_, cube32_collection_[cube_index].device322_.gadget_gpx_, cube32_collection_[cube_index].device322_.epx_, cube32_collection_[cube_index].device322_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			if (cube32_collection_[cube_index].device_gap_angle_ < 40)
				cube32_collection_[cube_index].device_gap_angle_ ++;
		}
	}

}

void TeemoTargetEx3::Draw1(void)
{
	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);


	// ヘルスバー(%)の表示をする
	// ただし、ヘルス0以下のときゲージ0(%)として表示する
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleMissionEx()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
	else
		NyaInterface::GetHandleMissionEx()->value_ = 0;

	if (count_frame_ < FPS_MAX * 4)
		return;

	// cube描画
	for (int i = 0; i < 10; i++)
	{
		if (count_frame_ % 5 == 0)
			cube31_collection_[i].gpx_->file_div_ = ++cube31_collection_[i].gpx_->file_div_ % 5;
		cube31_collection_[i].gpx_->draw_grid_cx_ = cube31_collection_[i].phandle_->grid_x_;
		cube31_collection_[i].gpx_->draw_grid_cy_ = cube31_collection_[i].phandle_->grid_y_;
		NyaGraphic::Draw(cube31_collection_[i].gpx_, eOBJECT::TARGET1);
	}

	// cube爆発
	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 60)
	{
		for (int i = 0; i < 10; i++)
		{
			cube31_collection_[i].death_epx_->grid_x_ = cube31_collection_[i].phandle_->grid_x_;
			cube31_collection_[i].death_epx_->grid_y_ = cube31_collection_[i].phandle_->grid_y_;
			NyaEffect::Draw(cube31_collection_[i].death_epx_, cube31_collection_[i].death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void TeemoTargetEx3::Draw2(void)
{
	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// ヘルスバー(%)の表示をする
	// ただし、ヘルス0以下のときゲージ0(%)として表示する
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleMissionEx()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
	else
		NyaInterface::GetHandleMissionEx()->value_ = 0;

	for (int i = 0; i < 4; i++)
	{	// cube拡大
		if (cube32_collection_[i].gpx_->extend_rate_ < 0.4)
			cube32_collection_[i].gpx_->extend_rate_ += 0.01;
	}

	// cube描画
	for (int i = 0; i < 4; i++)
	{
		if (count_frame_ % 5 == 0)
			cube32_collection_[i].gpx_->file_div_ = ++cube32_collection_[i].gpx_->file_div_ % 5;
		cube32_collection_[i].gpx_->draw_grid_cx_ = cube32_collection_[i].phandle_->grid_x_;
		cube32_collection_[i].gpx_->draw_grid_cy_ = cube32_collection_[i].phandle_->grid_y_;
		NyaGraphic::Draw(cube32_collection_[i].gpx_, eOBJECT::TARGET1);
	}


}

//void TeemoTargetEx4::Act2(void)
//{
//	InterfaceHandleMissionEx* ihandle_mission_ex;
//	InterfaceHandleSkill *ihandle_mission_skill;
//
//	cube2_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 70;
//	cube2_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
//	cube2_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_     ;
//	cube2_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
//	cube2_collection_[2].phandle_->grid_x_ = main_.phandle_->grid_x_ + 70;
//	cube2_collection_[2].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
//	cube2_collection_[3].phandle_->grid_x_ = main_.phandle_->grid_x_ + 70;
//	cube2_collection_[3].phandle_->grid_y_ = main_.phandle_->grid_y_     ;
//	cube2_collection_[4].phandle_->grid_x_ = main_.phandle_->grid_x_ + 70;
//	cube2_collection_[4].phandle_->grid_y_ = main_.phandle_->grid_y_ + 70;
//	cube2_collection_[5].phandle_->grid_x_ = main_.phandle_->grid_x_     ;
//	cube2_collection_[5].phandle_->grid_y_ = main_.phandle_->grid_y_ + 70;
//	cube2_collection_[6].phandle_->grid_x_ = main_.phandle_->grid_x_ - 70;
//	cube2_collection_[6].phandle_->grid_y_ = main_.phandle_->grid_y_ + 70;
//	cube2_collection_[7].phandle_->grid_x_ = main_.phandle_->grid_x_ - 70;
//	cube2_collection_[7].phandle_->grid_y_ = main_.phandle_->grid_y_     ;
//
//	// 衝突判定　衝突ダメージだけ経験値を追加
//	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
//	ihandle_mission_skill = NyaInterface::GetHandleSkill();
//	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_);
//
//	// ここから下の処理は
//	// フレームカウントFPS_MAX * 4以上で実行する
//	if (count_frame_ < FPS_MAX * 3)
//		return;
//
//	if (count_frame_ % 2 == 0)
//	{
//		for (int i = 0; i < 8; i+=2)
//		{
//			cube2_collection_[i].device2_.dpx_->create_x_ = cube2_collection_[i].phandle_->grid_x_;
//			cube2_collection_[i].device2_.dpx_->create_y_ = cube2_collection_[i].phandle_->grid_y_;
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ += 8;
//			NyaDevice::Attack1414(cube2_collection_[i].device2_.dpx_, cube2_collection_[i].device2_.gadget_gpx_, cube2_collection_[i].device2_.epx_, cube2_collection_[i].device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ += 180;
//			NyaDevice::Attack1414(cube2_collection_[i].device2_.dpx_, cube2_collection_[i].device2_.gadget_gpx_, cube2_collection_[i].device2_.epx_, cube2_collection_[i].device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ += 180;
//		}
//		for (int i = 1; i < 8; i+=2)
//		{
//			cube2_collection_[i].device2_.dpx_->create_x_ = cube2_collection_[i].phandle_->grid_x_;
//			cube2_collection_[i].device2_.dpx_->create_y_ = cube2_collection_[i].phandle_->grid_y_;
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ -= 8;
//			NyaDevice::Attack1414(cube2_collection_[i].device2_.dpx_, cube2_collection_[i].device2_.gadget_gpx_, cube2_collection_[i].device2_.epx_, cube2_collection_[i].device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ -= 180;
//			NyaDevice::Attack1414(cube2_collection_[i].device2_.dpx_, cube2_collection_[i].device2_.gadget_gpx_, cube2_collection_[i].device2_.epx_, cube2_collection_[i].device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ -= 180;
//		}
//	}
//
//	// 移動処理
//	if (count_frame_ % FPS_MAX == 0)
//	{
//		int move_end_x = (int)main_.phandle_->grid_x_ + NyaInput::GetRand(-20, 20);
//		int move_end_y = (int)main_.phandle_->grid_y_ + NyaInput::GetRand(-20, 20);
//		if (SCREEN_MIN_X + 250 < move_end_x  && move_end_x < SCREEN_MAX_X - 250 && SCREEN_MIN_Y + 140 < move_end_y && move_end_y < SCREEN_MIN_Y + 200)
//		NyaPosition::MoveGridMode(main_.phandle_, move_end_x, move_end_y, FPS_MAX - 3);
//	}
//}

