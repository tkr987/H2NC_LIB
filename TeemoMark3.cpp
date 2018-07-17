#include "HNLIB.h"
#include "TargetLock.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "TeemoMark3.h"

#define TEEMO_MARK3_MODE1_HEALTH	75
#define TEEMO_MARK3_MODE2_HEALTH	30
#define TEEMO_MARK3_MODE3_HEALTH	0

using namespace std;
using namespace HNLIB;

//*************************************
// Act1(), Draw1() で使うクラス
//*************************************

TeemoDevice311::TeemoDevice311()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_BLUE2;
	dpx_->move_speed_ = 10;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue2.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoDevice311::~TeemoDevice311()
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

TeemoCube31::TeemoCube31()
{
	lock_ = new TargetLock;
	lock_->LoadGraphic("img/target/lock_cube.png");

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetCube(gpx_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoCube31::~TeemoCube31()
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

//*************************************
// Act2(), Draw2() で使うクラス
//*************************************

TeemoDevice321::TeemoDevice321()
{
	dpx_ = new DevicePropertyX3;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_BLUE2;
	dpx_->move_speed_ = 0.1;
	dpx_->move_speed_accel_ = 0.02;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue2.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoDevice321::~TeemoDevice321()
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

TeemoDevice322::TeemoDevice322()
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

TeemoDevice322::~TeemoDevice322()
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

TeemoCube32::TeemoCube32()
{
	lock_ = new TargetLock;
	lock_->LoadGraphic("img/target/lock_cube.png");

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.01;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoCube32::~TeemoCube32()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);

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

//*************************************
// Act3(), Draw3() で使うクラス
//*************************************

TeemoDevice331::TeemoDevice331()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_BLUE2;
	dpx_->move_speed_ = 8;
	way1_angle_ = 0;
	way2_angle_ = 180;
	way3_angle_ = 0;
	way4_angle_ = 180;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue2.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoDevice331::~TeemoDevice331()
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

TeemoDevice332::TeemoDevice332()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 3;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoDevice332::~TeemoDevice332()
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

TeemoCube33::TeemoCube33()
{
	lock_ = new TargetLock;
	lock_->LoadGraphic("img/target/lock_cube.png");

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoCube33::~TeemoCube33()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);

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
// Teemo3Main
//*****************

TeemoMain3::TeemoMain3() : health_max_(230000)
{
	lock_ = new TargetLock;
	lock_->LoadGraphic("img/target/lock_teemo_mark3.png");

	death1_epx_ = new EffectPropertyX1;
	death1_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death1_epx_, death1_gpx_);

	death2_epx_ = new EffectPropertyX1;
	death2_epx_->interval_time_frame_ = 3;
	death2_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath2(death2_epx_, death2_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/teemo_mark3.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->health_ = health_max_;
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -100;
}

TeemoMain3::~TeemoMain3()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);

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
	delete death_spx_;
	death_spx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

//***********************************************
// TeemoTargetEx コンストラクタ・デストラクタ
//***********************************************

TeemoMark3::TeemoMark3()
{
	// メンバ変数初期化
	count_frame_ = 0;
	mode_ = 1;

	// interface 初期化
	NyaInterface::GetHandleWarning()->LoadSound("sound/warning.wav", 20);
}


TeemoMark3::~TeemoMark3()
{
	NyaInterface::GetHandleWarning()->DeleteSound();
}

//***************************
// TeemoTargetEx メンバ関数
//***************************

void TeemoMark3::Act(void)
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
	case 4:
		if (count_frame_ == FPS_MAX * 8)
			NyaInterface::GetHandleClear()->valid_ = true;
		break;
	}

	count_frame_++;

#ifdef __DEBUG__
		NyaString::Write("design_fps_font", white, 50, 90, "[50, 90] count_frame = %u", count_frame_);
#endif
}

void TeemoMark3::Draw(void)
{
	switch (mode_)
	{
	case 1:
		Draw1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK3_MODE1_HEALTH)
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
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK3_MODE2_HEALTH)
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
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_MARK3_MODE3_HEALTH)
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

void TeemoMark3::Act1(void)
{
	static int cube_index = 0;

	// 行動開始1フレーム目
	// mission ex モードをtrueにする
	// mission warning 表示を実行する
	// 初期位置へ移動する
	if (count_frame_ == 1)
	{
		NyaInterface::GetHandleHealth()->valid_ = true;
		NyaInterface::GetHandleWarning()->draw_valid_ = true;
		NyaInterface::GetHandleWarning()->sound_valid_ = true;
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube31_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 5)
		return;

	if (count_frame_ % 5 == 0)
	{
		cube31_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_;
		cube31_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_;
		NyaPosition::MoveSpeedMode(cube31_collection_[cube_index].phandle_, NyaInput::GetRand(0, 360), 6, FPS_MAX * 4);
		cube_index = ++cube_index % 100;
	}

	if (count_frame_ % 5 == 0)
	{
		main_.device311_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device311_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 8; way++)
		{
			main_.device311_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
			NyaDevice::Attack1414(main_.device311_.dpx_, main_.device311_.gadget_gpx_, main_.device311_.epx_, main_.device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
	}
}

void TeemoMark3::Act2(void)
{
	// 初期位置へ移動する
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);

	if (count_frame_ == FPS_MAX * 3)
	{
		for (int cube_index = 0; cube_index < cube32_collection_.size(); cube_index++)
		{	// cubeを初期位置へ移動させる
			cube32_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_;
			cube32_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_;
			NyaPosition::MoveGridMode(cube32_collection_[cube_index].phandle_, main_.phandle_->grid_x_ - 375 + (cube_index * 150) , 170, FPS_MAX * 2);
		}
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube32_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 5)
		return;

	if (count_frame_ % 4 == 0 && FPS_MAX * 5 < count_frame_ % (FPS_MAX * 15))
	{	// cube攻撃処理
		DevicePropertyX1* cube_dpx;
		GraphicPropertyX4* cube_gadget_gpx;
		EffectPropertyX1* cube_epx;
		GraphicPropertyX4* cube_effect_gpx;
		PositionHandle phandle_user;
		int mod_frame = count_frame_ % (FPS_MAX * 15);
		for (auto& e : cube32_collection_)
		{
			cube_dpx = e.device322_.dpx_;
			cube_gadget_gpx = e.device322_.gadget_gpx_;
			cube_epx = e.device322_.epx_;
			cube_effect_gpx = e.device322_.effect_gpx_;
			cube_dpx->create_x_ = e.phandle_->grid_x_;
			cube_dpx->create_y_ = e.phandle_->grid_y_;
			if (FPS_MAX * 5 <= mod_frame && mod_frame < FPS_MAX * 7)
				cube_dpx->move_angle_deg_ = 90;
			else if (FPS_MAX * 7 <= mod_frame && mod_frame < FPS_MAX * 9)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-0.5, 0.5);
			else if (FPS_MAX * 9 <= mod_frame && mod_frame < FPS_MAX * 11)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-1.5, 1.5);
			else if (FPS_MAX * 11 <= mod_frame && mod_frame < FPS_MAX * 13)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-10, 10);
			else if (FPS_MAX * 13 <= mod_frame && mod_frame < FPS_MAX * 15)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-20, 20);
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			if (FPS_MAX * 5 <= mod_frame && mod_frame < FPS_MAX * 7)
				cube_dpx->move_angle_deg_ = 90;
			else if (FPS_MAX * 7 <= mod_frame && mod_frame < FPS_MAX * 9)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-5, 5);
			else if (FPS_MAX * 9 <= mod_frame && mod_frame < FPS_MAX * 11)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-10, 10);
			else if (FPS_MAX * 11 <= mod_frame && mod_frame < FPS_MAX * 13)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-15, 15);
			else if (FPS_MAX * 13 <= mod_frame && mod_frame < FPS_MAX * 15)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-20, 20);
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
	}

	if (FPS_MAX * 12 < count_frame_ && count_frame_ % (FPS_MAX * 15) == FPS_MAX * 14)
	{	// main攻撃処理
		main_.device321_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device321_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device321_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		for (int way = 0; way < 72; way++)
		{
			main_.device321_.dpx_->move_angle_deg_ += 5;
			NyaDevice::Attack3414(main_.device321_.dpx_, main_.device321_.gadget_gpx_, main_.device321_.epx_, main_.device321_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
	}

}

void TeemoMark3::Act3(void)
{
	// 行動開始1フレーム目
	// 初期位置へ移動する
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube33_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ == FPS_MAX * 3)
	{
		for (int cube_index = 0; cube_index < 4; cube_index++)
		{
			cube33_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_;
			cube33_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_;
		}
		NyaPosition::MoveGridMode(cube33_collection_[0].phandle_, main_.phandle_->grid_x_ - 300, 90, FPS_MAX * 2);
		NyaPosition::MoveGridMode(cube33_collection_[1].phandle_, main_.phandle_->grid_x_ - 150, 90, FPS_MAX * 2);
		NyaPosition::MoveGridMode(cube33_collection_[2].phandle_, main_.phandle_->grid_x_ + 150, 90, FPS_MAX * 2);
		NyaPosition::MoveGridMode(cube33_collection_[3].phandle_, main_.phandle_->grid_x_ + 300, 90, FPS_MAX * 2);
	}

	if (count_frame_ < FPS_MAX * 5)
		return;

	if (count_frame_ % 20 == 0)
	{	// main攻撃処理
		main_.device331_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device331_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device331_.dpx_->move_angle_deg_ = main_.device331_.way1_angle_;
		main_.device331_.way1_angle_ += 10;
		for (int delay = 0; delay < 8; delay++)
		{
			main_.device331_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(main_.device331_.dpx_, main_.device331_.gadget_gpx_, main_.device331_.epx_, main_.device331_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device331_.dpx_->move_angle_deg_ = main_.device331_.way2_angle_;
		main_.device331_.way2_angle_ += 10;
		for (int delay = 0; delay < 8; delay++)
		{
			main_.device331_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(main_.device331_.dpx_, main_.device331_.gadget_gpx_, main_.device331_.epx_, main_.device331_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device331_.dpx_->move_angle_deg_ = main_.device331_.way3_angle_;
		main_.device331_.way3_angle_ -= 10;
		for (int delay = 0; delay < 8; delay++)
		{
			main_.device331_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(main_.device331_.dpx_, main_.device331_.gadget_gpx_, main_.device331_.epx_, main_.device331_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device331_.dpx_->move_angle_deg_ = main_.device331_.way4_angle_;
		main_.device331_.way4_angle_ -= 10;
		for (int delay = 0; delay < 8; delay++)
		{
			main_.device331_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(main_.device331_.dpx_, main_.device331_.gadget_gpx_, main_.device331_.epx_, main_.device331_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}

	if (count_frame_ % 15 == 0)
	{	// cube攻撃処理
		DevicePropertyX1* cube_dpx;
		GraphicPropertyX4* cube_gadget_gpx;
		EffectPropertyX1* cube_epx;
		GraphicPropertyX4* cube_effect_gpx;
		PositionHandle phandle_user;
		NyaPosition::FindHandle("user", &phandle_user);
		for (int i = 0; i < 4; i++)
		{
			cube_dpx = cube33_collection_[i].device332_.dpx_;
			cube_gadget_gpx = cube33_collection_[i].device332_.gadget_gpx_;
			cube_epx = cube33_collection_[i].device332_.epx_;
			cube_effect_gpx = cube33_collection_[i].device332_.effect_gpx_;
			cube_dpx->create_x_ = cube33_collection_[i].phandle_->grid_x_;
			cube_dpx->create_y_ = cube33_collection_[i].phandle_->grid_y_;
			cube_dpx->move_angle_deg_ = NyaPosition::Angle(cube33_collection_[i].phandle_, &phandle_user);
			cube_dpx->move_angle_deg_ += (NyaInput::GetRand(-25, 25) - 2);
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			cube_dpx->move_angle_deg_++;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			cube_dpx->move_angle_deg_++;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			cube_dpx->move_angle_deg_++;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			cube_dpx->move_angle_deg_++;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}
}

void TeemoMark3::Draw1(void)
{
	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	main_.lock_->Run(main_.phandle_);

	// ヘルス表示
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	for (auto& e : cube31_collection_)
	{	// cube描画
		if (NyaInput::GetFrameCount() % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % 5;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		e.lock_->Run(e.phandle_);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK3_MODE1_HEALTH)
	{	// cube爆発
		for (auto& e : cube31_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
		NyaSound::Play(cube31_collection_[0].death_spx_);
	}
}

void TeemoMark3::Draw2(void)
{
	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	main_.lock_->Run(main_.phandle_);

	// ヘルス表示
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	if (count_frame_ < FPS_MAX * 3)
		return;

	for (auto& e : cube32_collection_)
	{	// cube描画
		if (e.gpx_->extend_rate_ < 0.4)
			e.gpx_->extend_rate_ += 0.01;
		if (NyaInput::GetFrameCount() % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % 5;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		e.lock_->Run(e.phandle_);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK3_MODE2_HEALTH)
	{	// cube爆発
		for (auto& e : cube32_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
		NyaSound::Play(cube32_collection_[0].death_spx_);
	}
}

void TeemoMark3::Draw3(void)
{
	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	main_.lock_->Run(main_.phandle_);

	// ヘルス表示
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	if (count_frame_ < FPS_MAX * 3)
		return;

	for (auto& e : cube33_collection_)
	{	// cube描画
		if (NyaInput::GetFrameCount() % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % 5;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		e.lock_->Run(e.phandle_);
	}

	
	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_MARK3_MODE3_HEALTH)
	{	// cube爆発
		for (auto& e : cube33_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
		NyaSound::Play(cube33_collection_[0].death_spx_);
	}
}

void TeemoMark3::Draw4(void)
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
		NyaSound::Play(main_.death_spx_);
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
