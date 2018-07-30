#include <tuple>
#include "HNLIB.h"
#include "TeemoLock.h"
#include "TeemoEnum.h"
#include "TeemoEx.h"
#include "TeemoFactory.h"

#define __DEBUG__

using namespace std;
using namespace HNLIB;

//*************************************
// Act1(), Draw1() で使うクラス
//*************************************

TeemoExDevice411::TeemoExDevice411()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 8;
	TeemoFactory::TargetAttackOrange9(dpx_, device_gpx_, epx_, effect_gpx_);
};

TeemoExDevice411::~TeemoExDevice411()
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

TeemoCube41::TeemoCube41()
{
	move_angle_ = 0;

	lock_ = new TeemoLock(eLOCK::CUBE);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	gpx_ = new GraphicPropertyX4;
	phandle_ = NyaPosition::CreateHandle();
	TeemoFactory::TargetCube(gpx_, phandle_);
}

TeemoCube41::~TeemoCube41()
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

TeemoExDevice421::TeemoExDevice421()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 2.5;
	TeemoFactory::TargetAttackOrange3(dpx_, device_gpx_, epx_, effect_gpx_);
};

TeemoExDevice421::~TeemoExDevice421()
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

TeemoExDevice422::TeemoExDevice422()
{
	dpx_ = new DevicePropertyX2;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 6;
	TeemoFactory::TargetAttackGreen3(dpx_, device_gpx_, epx_, effect_gpx_);
};

TeemoExDevice422::~TeemoExDevice422()
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

TeemoExDevice423::TeemoExDevice423()
{
	dpx_ = new DevicePropertyX2;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->draw_angle_speed_deg_ = 2;
	dpx_->move_speed_ = 7;
	TeemoFactory::TargetAttackGreen12(dpx_, device_gpx_, epx_, effect_gpx_);
};

TeemoExDevice423::~TeemoExDevice423()
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

TeemoExDevice424::TeemoExDevice424()
{
	dpx_ = new DevicePropertyX2;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->draw_angle_speed_deg_ = 2;
	dpx_->move_speed_ = 5;
	TeemoFactory::TargetAttackGreen13(dpx_, device_gpx_, epx_, effect_gpx_);
};

TeemoExDevice424::~TeemoExDevice424()
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

TeemoExCube42::TeemoExCube42()
{
	lock_ = new TeemoLock(eLOCK::CUBE);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	gpx_ = new GraphicPropertyX4;
	phandle_ = NyaPosition::CreateHandle();
	TeemoFactory::TargetCube(gpx_, phandle_);
}

TeemoExCube42::~TeemoExCube42()
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
// Act3(), Draw3() で使うクラス
//*************************************

TeemoExDevice431::TeemoExDevice431()
{
	dpx_ = new DevicePropertyX2;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 11;
	TeemoFactory::TargetAttackGreen11(dpx_, device_gpx_, epx_, effect_gpx_);
};

TeemoExDevice431::~TeemoExDevice431()
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

TeemoExDevice432::TeemoExDevice432()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 9;
	TeemoFactory::TargetAttackOrange3(dpx_, device_gpx_, epx_, effect_gpx_);
};

TeemoExDevice432::~TeemoExDevice432()
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


TeemoExCube43::TeemoExCube43()
{
	gpx_ = new GraphicPropertyX4;
	phandle_ = NyaPosition::CreateHandle();
	TeemoFactory::TargetCube(gpx_, phandle_);
}

TeemoExCube43::~TeemoExCube43()
{
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}



TeemoEx4Main::TeemoEx4Main() : health_max_(170000)
{
	lock_ = new TeemoLock(eLOCK::TEEMO_EX);

	death1_epx_ = new EffectPropertyX1;
	death1_gpx_ = new GraphicPropertyX4;
	death1_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath1(death1_epx_, death1_gpx_, death1_spx_);

	death2_epx_ = new EffectPropertyX1;
	death2_gpx_ = new GraphicPropertyX4;
	death2_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath2(death2_epx_, death2_gpx_, death2_spx_);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/teemo_ex.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 10;
	phandle_->grid_x_ =  SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -150;
	phandle_->health_ = health_max_;
}

TeemoEx4Main::~TeemoEx4Main()
{
	NyaGraphic::Delete(&gpx_->file_);

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

TeemoEx::TeemoEx()
{
	count_frame_ = 0;
	mode_ = 0;

	warning_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/warning.wav", &warning_spx_->file_);
	NyaSound::ChangeVolume(&warning_spx_->file_, 20);

	// フォント設定
	NyaString::SettingFont("warning_logo_font", 64, 4);
	NyaString::SettingFont("ex_logo_font", 100, 12);
}


TeemoEx::~TeemoEx()
{
	delete warning_spx_;
	warning_spx_ = nullptr;
}

void TeemoEx::Act(void)
{

	switch (mode_)
	{
	case 0:
		if (NyaInterface::GetHandleContinue()->cnum_ != 0)
			NyaInterface::GetHandleComplete()->valid_ = true;
		else
		{
			mode_ = 1;
			count_frame_ = 0;
		}
		break;
	case 1:
		Act1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_EX_MODE1_HEALTH)
		{
			count_frame_ = 0;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
			NyaSound::Play(main_.death1_spx_);
		}
		break;
	case 2:
		Act2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_EX_MODE2_HEALTH)
		{
			count_frame_ = 0;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
			NyaSound::Play(main_.death1_spx_);
		}
		break;
	case 3:
		Act3();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_EX_MODE3_HEALTH)
		{
			count_frame_ = 0;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
			NyaSound::Play(main_.death1_spx_);
		}
		break;
	case 4:
		if (count_frame_ == 30 * 8)
		{
			NyaGraphic::Swing();
			NyaSound::Play(main_.death2_spx_);
		}
		if (count_frame_ == FPS_MAX * 8)
			NyaInterface::GetHandleComplete()->valid_ = true;
		break;
	}

	count_frame_++;
}

void TeemoEx::Draw(void)
{
	switch (mode_)
	{
	case 1:
		Draw1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_EX_MODE1_HEALTH)
			mode_ = 2;
		break;
	case 2:
		Draw2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_EX_MODE2_HEALTH)
			mode_ = 3;
		break;
	case 3:
		Draw3();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_EX_MODE3_HEALTH)
			mode_ = 4;
		break;
	case 4:
		Draw4();
		break;
	}

#ifdef __DEBUG__
	const tuple<int, int, int> white = make_tuple(255, 255, 255);
	NyaString::Write("design_fps_font", white, 50, 90, "[50, 90] count_frame = %u", count_frame_);
#endif
}

void TeemoEx::Act1(void)
{
	// 行動開始1フレーム目
	// ヘルス表示、WARNING SE 再生
	if (count_frame_ == 1)
	{
		NyaInterface::GetHandleHealth()->valid_ = true;
		NyaSound::Play(warning_spx_);
	}

	// 移動処理
	if (main_.phandle_->grid_y_ < 140)
		main_.phandle_->grid_y_++;

	if (count_frame_ == 350)
	{
		int cube_index = 0;
		for (auto& e : cube41_collection_)
		{
			e.move_angle_ = cube_index * 45;
			e.phandle_->grid_x_ = main_.phandle_->grid_x_;
			e.phandle_->grid_y_ = main_.phandle_->grid_y_;
			NyaPosition::MoveLengthMode(e.phandle_, cube_index * 45, 130, FPS_MAX * 3);
			cube_index++;
		}
	}

	if (count_frame_ < 350 + FPS_MAX * 2)
		return;

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube41_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
	}

	if (count_frame_ < FPS_MAX * 10)
		return;

	// ヘルス減少
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (auto& e : cube41_collection_)
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;

	int cube_index = 0;
	for (auto& e : cube41_collection_)
	{
		e.move_angle_ += 4.5;
		e.phandle_->grid_x_ = main_.phandle_->grid_x_ + 130 * cos(AngleToRad(e.move_angle_));
		e.phandle_->grid_y_ = main_.phandle_->grid_y_ + 130 * sin(AngleToRad(e.move_angle_));
		if (count_frame_ % 15 == 0)
		{
			DevicePropertyX1* cube_dpx = e.device411_.dpx_;
			GraphicPropertyX4* cube_gadget_gpx = e.device411_.device_gpx_;
			EffectPropertyX1* cube_epx = e.device411_.epx_;
			GraphicPropertyX4* cube_effect_gpx = e.device411_.effect_gpx_;
			cube_dpx->create_x_ = e.phandle_->grid_x_;
			cube_dpx->create_y_ = e.phandle_->grid_y_;
			for (int bullet_index = -8; bullet_index < 9; bullet_index++)
			{
				cube_dpx->move_angle_deg_ = e.move_angle_ + (bullet_index * 2);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
		cube_index++;
	}
}

void TeemoEx::Act2(void)
{
	DevicePropertyX1* cube_dpx;
	GraphicPropertyX4* cube_effect_gpx;
	EffectPropertyX1* cube_epx;
	GraphicPropertyX4* cube_gadget_gpx;
	InterfaceHandleSkill *ihandle_mission_skill;

	// 行動開始1フレーム目
	// mission ex モードをtrueにする
	// mission warning 表示を実行する
	if (count_frame_ == 1)
	{
		for (int i = 0; i < 6; i++)
		{
			cube42_collection_[i].phandle_->grid_x_ = main_.phandle_->grid_x_;
			cube42_collection_[i].phandle_->grid_y_ = main_.phandle_->grid_y_;
		}
		NyaPosition::MoveGridMode(cube42_collection_[0].phandle_, main_.phandle_->grid_x_ - 300, 60, FPS_MAX * 3);
		NyaPosition::MoveGridMode(cube42_collection_[1].phandle_, main_.phandle_->grid_x_ - 200, 60, FPS_MAX * 3);
		NyaPosition::MoveGridMode(cube42_collection_[2].phandle_, main_.phandle_->grid_x_ - 100, 60, FPS_MAX * 3);
		NyaPosition::MoveGridMode(cube42_collection_[3].phandle_, main_.phandle_->grid_x_ + 100, 60, FPS_MAX * 3);
		NyaPosition::MoveGridMode(cube42_collection_[4].phandle_, main_.phandle_->grid_x_ + 200, 60, FPS_MAX * 3);
		NyaPosition::MoveGridMode(cube42_collection_[5].phandle_, main_.phandle_->grid_x_ + 300, 60, FPS_MAX * 3);
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_damage_);
	for (int i = 0; i < 6; i++)
	{
		NyaPosition::Collide(cube42_collection_[i].phandle_, eOBJECT::TARGET1);
		ihandle_mission_skill->AddExp(cube42_collection_[i].phandle_->collision_hit_damage_);
	}


	if (count_frame_ < FPS_MAX * 5)
		return;

	// ヘルス減少
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (int i = 0; i < 6; i++)
		main_.phandle_->health_ -= cube42_collection_[i].phandle_->collision_hit_damage_;

	if (count_frame_ % 15 == 0)
	{
		main_.device22_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device22_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 4; way++)
		{
			main_.device22_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack2414(main_.device22_.dpx_, main_.device22_.device_gpx_, main_.device22_.epx_, main_.device22_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		main_.device23_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device23_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 4; way++)
		{
			main_.device23_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack2414(main_.device23_.dpx_, main_.device23_.device_gpx_, main_.device23_.epx_, main_.device23_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		main_.device24_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device24_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 4; way++)
		{
			main_.device24_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack2414(main_.device24_.dpx_, main_.device24_.device_gpx_, main_.device24_.epx_, main_.device24_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 1);
		}
	}

	if (count_frame_ < FPS_MAX * 8)
		return;
	
	if (count_frame_ % (FPS_MAX * 4 * 3) == FPS_MAX * 4 * 2)
	{
		cube_dpx = cube42_collection_[2].device421_.dpx_;
		cube_gadget_gpx = cube42_collection_[2].device421_.device_gpx_;
		cube_epx = cube42_collection_[2].device421_.epx_;
		cube_effect_gpx = cube42_collection_[2].device421_.effect_gpx_;
		cube_dpx->create_x_ = cube42_collection_[2].phandle_->grid_x_;
		cube_dpx->create_y_ = cube42_collection_[2].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		cube_dpx = cube42_collection_[3].device421_.dpx_;
		cube_gadget_gpx = cube42_collection_[3].device421_.device_gpx_;
		cube_epx = cube42_collection_[3].device421_.epx_;
		cube_effect_gpx = cube42_collection_[3].device421_.effect_gpx_;
		cube_dpx->create_x_ = cube42_collection_[3].phandle_->grid_x_;
		cube_dpx->create_y_ = cube42_collection_[3].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}
	else if (count_frame_ % (FPS_MAX * 4 * 3) == 0)
	{
		cube_dpx = cube42_collection_[1].device421_.dpx_;
		cube_gadget_gpx = cube42_collection_[1].device421_.device_gpx_;
		cube_epx = cube42_collection_[1].device421_.epx_;
		cube_effect_gpx = cube42_collection_[1].device421_.effect_gpx_;
		cube_dpx->create_x_ = cube42_collection_[1].phandle_->grid_x_;
		cube_dpx->create_y_ = cube42_collection_[1].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		cube_dpx = cube42_collection_[4].device421_.dpx_;
		cube_gadget_gpx = cube42_collection_[4].device421_.device_gpx_;
		cube_epx = cube42_collection_[4].device421_.epx_;
		cube_effect_gpx = cube42_collection_[4].device421_.effect_gpx_;
		cube_dpx->create_x_ = cube42_collection_[4].phandle_->grid_x_;
		cube_dpx->create_y_ = cube42_collection_[4].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}
	else if (count_frame_ % (FPS_MAX * 4 * 3) == FPS_MAX * 4)
	{
		cube_dpx = cube42_collection_[0].device421_.dpx_;
		cube_gadget_gpx = cube42_collection_[0].device421_.device_gpx_;
		cube_epx = cube42_collection_[0].device421_.epx_;
		cube_effect_gpx = cube42_collection_[0].device421_.effect_gpx_;
		cube_dpx->create_x_ = cube42_collection_[0].phandle_->grid_x_;
		cube_dpx->create_y_ = cube42_collection_[0].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		cube_dpx = cube42_collection_[5].device421_.dpx_;
		cube_gadget_gpx = cube42_collection_[5].device421_.device_gpx_;
		cube_epx = cube42_collection_[5].device421_.epx_;
		cube_effect_gpx = cube42_collection_[5].device421_.effect_gpx_;
		cube_dpx->create_x_ = cube42_collection_[5].phandle_->grid_x_;
		cube_dpx->create_y_ = cube42_collection_[5].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}

	if (count_frame_ < FPS_MAX * 20)
		return;

	if (count_frame_ % 32 == 0)
	{
		double move_x = NyaInput::GetRand(90.0, 760.0);
		double move_y = NyaInput::GetRand(150.0, 300.0);
		NyaPosition::MoveGridMode(main_.phandle_, move_x, move_y, 30);
	}
}

void TeemoEx::Act3(void)
{
	static int update_device_angle = -5;
	InterfaceHandleSkill *ihandle_mission_skill;
	DevicePropertyX1* cube_dpx;
	GraphicPropertyX4* cube_effect_gpx;
	EffectPropertyX1* cube_epx;
	GraphicPropertyX4* cube_gadget_gpx;

	if (count_frame_ == FPS_MAX)
	{
		main_.gpx_->draw_angle_deg_ = 0;
		NyaPosition::MoveGridMode(main_.phandle_, (double)SCREEN_MAX_X / 2.0, 150.0, FPS_MAX * 2);
		cube3_collection_[0].device32_.dpx_->move_angle_deg_ = 0;
		cube3_collection_[1].device32_.dpx_->move_angle_deg_ = 45;
		cube3_collection_[2].device32_.dpx_->move_angle_deg_ = 0;
		cube3_collection_[3].device32_.dpx_->move_angle_deg_ = 45;
	}

	if (count_frame_ < FPS_MAX * 4)
		return;

	cube3_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 140;
	cube3_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
	cube3_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ - 70;
	cube3_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
	cube3_collection_[2].phandle_->grid_x_ = main_.phandle_->grid_x_ + 70;
	cube3_collection_[2].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
	cube3_collection_[3].phandle_->grid_x_ = main_.phandle_->grid_x_ + 140;
	cube3_collection_[3].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;

	// 衝突判定　衝突ダメージだけ経験値を追加
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_damage_);
	for (int i = 0; i < 4; i++)
	{
		NyaPosition::Collide(cube3_collection_[i].phandle_, eOBJECT::TARGET1);
		ihandle_mission_skill->AddExp(cube3_collection_[i].phandle_->collision_hit_damage_);
	}

	if (count_frame_ < FPS_MAX * 7)
		return;

	// ヘルス減少
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (int i = 0; i < 4; i++)
		main_.phandle_->health_ -= cube3_collection_[i].phandle_->collision_hit_damage_;

	if (count_frame_ % 20 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			cube3_collection_[i].device32_.dpx_->create_x_ = cube3_collection_[i].phandle_->grid_x_;
			cube3_collection_[i].device32_.dpx_->create_y_ = cube3_collection_[i].phandle_->grid_y_;
			cube_dpx = cube3_collection_[i].device32_.dpx_;
			cube_effect_gpx = cube3_collection_[i].device32_.effect_gpx_;
			cube_epx = cube3_collection_[i].device32_.epx_;
			cube_gadget_gpx = cube3_collection_[i].device32_.device_gpx_;
			if (i == 0 || i == 1)
				cube_dpx->move_angle_deg_ -= 10;
			else
				cube_dpx->move_angle_deg_ += 10;
			for (int n = 0; n < 7; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
			for (int n = 0; n < 7; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
			for (int n = 0; n < 7; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
			for (int n = 0; n < 7; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
		}
	}


	if (count_frame_ % (FPS_MAX * 14) < FPS_MAX * 8 && count_frame_ % 7 == 0)
	{
		update_device_angle = (-5 < update_device_angle) ? update_device_angle - 1 : -5;
		main_.device31_.dpx_->move_angle_speed_deg_ = (main_.device31_.dpx_->move_angle_speed_deg_ < 1.6) ? main_.device31_.dpx_->move_angle_speed_deg_ + 0.1 : 1.6;
		main_.device31_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device31_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device31_.dpx_->move_angle_deg_ += update_device_angle;
		for (int way = 0 ; way < 12; way++)
		{
			NyaDevice::Attack2414(main_.device31_.dpx_, main_.device31_.device_gpx_, main_.device31_.epx_, main_.device31_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			main_.device31_.dpx_->move_angle_deg_ -= 30;
		}
	}
	else if (FPS_MAX * 8 <= count_frame_ % (FPS_MAX * 14) && count_frame_ % 7 == 0)
	{
		update_device_angle = (update_device_angle < 5) ? update_device_angle + 1 : 5;
		main_.device31_.dpx_->move_angle_speed_deg_ = (-1.6 < main_.device31_.dpx_->move_angle_speed_deg_) ? main_.device31_.dpx_->move_angle_speed_deg_ - 0.1 : -1.6;
		main_.device31_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device31_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device31_.dpx_->move_angle_deg_ += update_device_angle;
		for (int way = 0 ; way < 12; way++)
		{
			NyaDevice::Attack2414(main_.device31_.dpx_, main_.device31_.device_gpx_, main_.device31_.epx_, main_.device31_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			main_.device31_.dpx_->move_angle_deg_ += 30;
		}
	}

	// 移動処理
	if (count_frame_ % FPS_MAX == 0)
	{
		int move_end_x = (int)main_.phandle_->grid_x_ + NyaInput::GetRand(-20, 20);
		int move_end_y = (int)main_.phandle_->grid_y_ + NyaInput::GetRand(-20, 20);
		if (SCREEN_MIN_X + 250 < move_end_x  && move_end_x < SCREEN_MAX_X - 250 && SCREEN_MIN_Y + 140 < move_end_y && move_end_y < SCREEN_MIN_Y + 200)
		NyaPosition::MoveGridMode(main_.phandle_, move_end_x, move_end_y, FPS_MAX - 3);
	}
}


void TeemoEx::Draw1(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);

	if (count_frame_ < FPS_MAX * 5)
	{
		NyaString::Write("warning_logo_font", red, 310, 200, "WARNING");
		NyaString::Write("ex_logo_font", red, 255, 300, "EX BOSS");
	}

	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube41_collection_)
	{	// cube 描画
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube ロック描画
		e.lock_->Run(e.phandle_);
	}
	
	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_EX_MODE1_HEALTH)
	{	// cube爆発
		for (auto& e : cube41_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}

	// ヘルス表示
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
}

void TeemoEx::Draw2(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);

	// main描画
	if (FPS_MAX * 4 < count_frame_)
		main_.gpx_->draw_angle_deg_ -= 15;
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube42_collection_)
	{	// cube 描画
		if (count_frame_ % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube ロック描画
		e.lock_->Run(e.phandle_);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_EX_MODE2_HEALTH)
	{	// cube爆発
		for (auto& e : cube41_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}

	// ヘルス表示
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
}

void TeemoEx::Draw3(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);

	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	if (count_frame_ < FPS_MAX * 4)
		return;

	for (int i = 0; i < 4; i++)
	{	// cube拡大
		if (cube3_collection_[i].gpx_->extend_rate_ < 0.4)
			cube3_collection_[i].gpx_->extend_rate_ += 0.01;
	}

	// cube描画
	for (auto& e : cube3_collection_)
	{
		if (NyaInput::GetFrameCount() % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_EX_MODE3_HEALTH)
	{	// cube爆発
		for (auto& e : cube41_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}

	// ヘルス表示
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
}

void TeemoEx::Draw4(void)
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
	}

	if (count_frame_ < 30 * 10)
	{	// main描画
		main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
		main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
		NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	}

	// ヘルス表示
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
}

