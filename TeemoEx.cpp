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
	gadget_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetAttackOrange9(dpx_, gadget_gpx_, epx_, effect_gpx_);
	dpx_->move_speed_ = 8;
};

TeemoExDevice411::~TeemoExDevice411()
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

TeemoCube41::TeemoCube41()
{
	move_angle_ = 0;
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

TeemoCube41::~TeemoCube41()
{
	delete lock_;
	lock_ = nullptr;
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete death_spx_;
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
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 5;
	dpx_->move_speed_ = 2.5;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice421::~TeemoExDevice421()
{
	NyaGraphic::Delete(&gadget_gpx_->file_);
	NyaGraphic::Delete(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExDevice422::TeemoExDevice422()
{
	dpx_ = new DevicePropertyX2;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 10;
	dpx_->move_speed_ = 6;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/attack_green1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice422::~TeemoExDevice422()
{
	NyaGraphic::Delete(&gadget_gpx_->file_);
	NyaGraphic::Delete(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExDevice423::TeemoExDevice423()
{
	dpx_ = new DevicePropertyX2;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 6;
	dpx_->draw_angle_speed_deg_ = 2;
	dpx_->move_speed_ = 7;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/attack_green4.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice423::~TeemoExDevice423()
{
	NyaGraphic::Delete(&gadget_gpx_->file_);
	NyaGraphic::Delete(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExDevice424::TeemoExDevice424()
{
	dpx_ = new DevicePropertyX2;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 4;
	dpx_->draw_angle_speed_deg_ = 2;
	dpx_->move_speed_ = 5;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/attack_green5.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice424::~TeemoExDevice424()
{
	NyaGraphic::Delete(&gadget_gpx_->file_);
	NyaGraphic::Delete(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExCube42::TeemoExCube42()
{
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.4;
	NyaGraphic::Load(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoExCube42::~TeemoExCube42()
{
	NyaGraphic::Delete(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}


TeemoExDevice431::TeemoExDevice431()
{
	dpx_ = new DevicePropertyX2;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 10;
	dpx_->move_speed_ = 12;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/attack_green3.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice431::~TeemoExDevice431()
{
	NyaGraphic::Delete(&gadget_gpx_->file_);
	NyaGraphic::Delete(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExDevice432::TeemoExDevice432()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 6;
	dpx_->move_speed_ = 10;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = 120;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice432::~TeemoExDevice432()
{
	NyaGraphic::Delete(&gadget_gpx_->file_);
	NyaGraphic::Delete(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}


TeemoExCube43::TeemoExCube43()
{
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.4;
	NyaGraphic::Load(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoExCube43::~TeemoExCube43()
{
	NyaGraphic::Delete(&gpx_->file_);
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
	NyaGraphic::Load("img/target/teemo_ex4.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 10;
	phandle_->grid_x_ =  SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -100;
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
	death1_epx_ = nullptr;
	delete death2_gpx_;
	death1_gpx_ = nullptr;
	delete death2_spx_;
	death1_spx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

TeemoEx::TeemoEx()
{
	// メンバ変数初期化
	count_frame_ = 0;
	warning_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/warning.wav", &warning_spx_->file_);
	NyaSound::ChangeVolume(&warning_spx_->file_, 20);

	mode_ = 0;

	// フォント設定
	NyaString::SettingFont("warning_logo_font", 64, 4);
	NyaString::SettingFont("ex_logo_font", 100, 12);
}


TeemoEx::~TeemoEx()
{
	delete warning_spx_;
	warning_spx_ = nullptr;
	NyaGraphic::Delete(&main_.gpx_->file_);
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
			mode_ = 2;
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
			NyaSound::Play(cube41_collection_[0].death_spx_);
		}
		break;
	case 2:
		Act2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_EX_MODE2_HEALTH)
		{
			count_frame_ = 0;
			mode_ = 3;
			NyaGraphic::Swing();
		}
		break;
	case 3:
		Act3();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_EX_MODE3_HEALTH)
		{
			count_frame_ = 0;
			mode_ = 4;
		}
		break;
	case 4:
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
		break;
	case 2:
		Draw2();
		break;
	case 3:
		Draw3();
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
			GraphicPropertyX4* cube_gadget_gpx = e.device411_.gadget_gpx_;
			EffectPropertyX1* cube_epx = e.device411_.epx_;
			GraphicPropertyX4* cube_effect_gpx = e.device411_.effect_gpx_;
			cube_dpx->create_x_ = e.phandle_->grid_x_;
			cube_dpx->create_y_ = e.phandle_->grid_y_;
			for (int bullet_index = -10; bullet_index < 11; bullet_index++)
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
			cube2_collection_[i].phandle_->grid_x_ = main_.phandle_->grid_x_;
			cube2_collection_[i].phandle_->grid_y_ = main_.phandle_->grid_y_;
		}
		NyaPosition::MoveGridMode(cube2_collection_[0].phandle_, main_.phandle_->grid_x_ - 300, 60, FPS_MAX * 3);
		NyaPosition::MoveGridMode(cube2_collection_[1].phandle_, main_.phandle_->grid_x_ - 200, 60, FPS_MAX * 3);
		NyaPosition::MoveGridMode(cube2_collection_[2].phandle_, main_.phandle_->grid_x_ - 100, 60, FPS_MAX * 3);
		NyaPosition::MoveGridMode(cube2_collection_[3].phandle_, main_.phandle_->grid_x_ + 100, 60, FPS_MAX * 3);
		NyaPosition::MoveGridMode(cube2_collection_[4].phandle_, main_.phandle_->grid_x_ + 200, 60, FPS_MAX * 3);
		NyaPosition::MoveGridMode(cube2_collection_[5].phandle_, main_.phandle_->grid_x_ + 300, 60, FPS_MAX * 3);
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_damage_);
	for (int i = 0; i < 6; i++)
	{
		NyaPosition::Collide(cube2_collection_[i].phandle_, eOBJECT::TARGET1);
		ihandle_mission_skill->AddExp(cube2_collection_[i].phandle_->collision_hit_damage_);
	}


	if (count_frame_ < FPS_MAX * 5)
		return;

	// ヘルス減少
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (int i = 0; i < 6; i++)
		main_.phandle_->health_ -= cube2_collection_[i].phandle_->collision_hit_damage_;

	if (count_frame_ % 15 == 0)
	{
		main_.device22_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device22_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 4; way++)
		{
			main_.device22_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack2414(main_.device22_.dpx_, main_.device22_.gadget_gpx_, main_.device22_.epx_, main_.device22_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		main_.device23_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device23_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 4; way++)
		{
			main_.device23_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack2414(main_.device23_.dpx_, main_.device23_.gadget_gpx_, main_.device23_.epx_, main_.device23_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		main_.device24_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device24_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 4; way++)
		{
			main_.device24_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack2414(main_.device24_.dpx_, main_.device24_.gadget_gpx_, main_.device24_.epx_, main_.device24_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 1);
		}
	}

	if (count_frame_ < FPS_MAX * 8)
		return;
	
	if (count_frame_ % (FPS_MAX * 4 * 3) == FPS_MAX * 4 * 2)
	{
		cube_dpx = cube2_collection_[2].device21_.dpx_;
		cube_gadget_gpx = cube2_collection_[2].device21_.gadget_gpx_;
		cube_epx = cube2_collection_[2].device21_.epx_;
		cube_effect_gpx = cube2_collection_[2].device21_.effect_gpx_;
		cube_dpx->create_x_ = cube2_collection_[2].phandle_->grid_x_;
		cube_dpx->create_y_ = cube2_collection_[2].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		cube_dpx = cube2_collection_[3].device21_.dpx_;
		cube_gadget_gpx = cube2_collection_[3].device21_.gadget_gpx_;
		cube_epx = cube2_collection_[3].device21_.epx_;
		cube_effect_gpx = cube2_collection_[3].device21_.effect_gpx_;
		cube_dpx->create_x_ = cube2_collection_[3].phandle_->grid_x_;
		cube_dpx->create_y_ = cube2_collection_[3].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}
	else if (count_frame_ % (FPS_MAX * 4 * 3) == 0)
	{
		cube_dpx = cube2_collection_[1].device21_.dpx_;
		cube_gadget_gpx = cube2_collection_[1].device21_.gadget_gpx_;
		cube_epx = cube2_collection_[1].device21_.epx_;
		cube_effect_gpx = cube2_collection_[1].device21_.effect_gpx_;
		cube_dpx->create_x_ = cube2_collection_[1].phandle_->grid_x_;
		cube_dpx->create_y_ = cube2_collection_[1].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		cube_dpx = cube2_collection_[4].device21_.dpx_;
		cube_gadget_gpx = cube2_collection_[4].device21_.gadget_gpx_;
		cube_epx = cube2_collection_[4].device21_.epx_;
		cube_effect_gpx = cube2_collection_[4].device21_.effect_gpx_;
		cube_dpx->create_x_ = cube2_collection_[4].phandle_->grid_x_;
		cube_dpx->create_y_ = cube2_collection_[4].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}
	else if (count_frame_ % (FPS_MAX * 4 * 3) == FPS_MAX * 4)
	{
		cube_dpx = cube2_collection_[0].device21_.dpx_;
		cube_gadget_gpx = cube2_collection_[0].device21_.gadget_gpx_;
		cube_epx = cube2_collection_[0].device21_.epx_;
		cube_effect_gpx = cube2_collection_[0].device21_.effect_gpx_;
		cube_dpx->create_x_ = cube2_collection_[0].phandle_->grid_x_;
		cube_dpx->create_y_ = cube2_collection_[0].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 6)
		{
			cube_dpx->move_angle_deg_ += 6;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		cube_dpx = cube2_collection_[5].device21_.dpx_;
		cube_gadget_gpx = cube2_collection_[5].device21_.gadget_gpx_;
		cube_epx = cube2_collection_[5].device21_.epx_;
		cube_effect_gpx = cube2_collection_[5].device21_.effect_gpx_;
		cube_dpx->create_x_ = cube2_collection_[5].phandle_->grid_x_;
		cube_dpx->create_y_ = cube2_collection_[5].phandle_->grid_y_;
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
			cube_gadget_gpx = cube3_collection_[i].device32_.gadget_gpx_;
			if (i == 0 || i == 1)
				cube_dpx->move_angle_deg_ -= 10;
			else
				cube_dpx->move_angle_deg_ += 10;
			for (int n = 0; n < 8; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
			for (int n = 0; n < 8; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
			for (int n = 0; n < 8; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
			for (int n = 0; n < 8; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
		}
	}


	if (count_frame_ % (FPS_MAX * 14) < FPS_MAX * 8 && count_frame_ % 6 == 0)
	{
		update_device_angle = (-5 < update_device_angle) ? update_device_angle - 1 : -5;
		main_.device31_.dpx_->move_angle_speed_deg_ = (main_.device31_.dpx_->move_angle_speed_deg_ < 1.6) ? main_.device31_.dpx_->move_angle_speed_deg_ + 0.1 : 1.6;
		main_.device31_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device31_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device31_.dpx_->move_angle_deg_ += update_device_angle;
		for (int way = 0 ; way < 12; way++)
		{
			NyaDevice::Attack2414(main_.device31_.dpx_, main_.device31_.gadget_gpx_, main_.device31_.epx_, main_.device31_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			main_.device31_.dpx_->move_angle_deg_ -= 30;
		}
	}
	else if (FPS_MAX * 8 <= count_frame_ % (FPS_MAX * 14) && count_frame_ % 6 == 0)
	{
		update_device_angle = (update_device_angle < 5) ? update_device_angle + 1 : 5;
		main_.device31_.dpx_->move_angle_speed_deg_ = (-1.6 < main_.device31_.dpx_->move_angle_speed_deg_) ? main_.device31_.dpx_->move_angle_speed_deg_ - 0.1 : -1.6;
		main_.device31_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device31_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device31_.dpx_->move_angle_deg_ += update_device_angle;
		for (int way = 0 ; way < 12; way++)
		{
			NyaDevice::Attack2414(main_.device31_.dpx_, main_.device31_.gadget_gpx_, main_.device31_.epx_, main_.device31_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
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
		if (NyaInput::GetFrameCount() % 5 == 0)
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

	// cube描画
	for (auto& e : cube2_collection_)
	{
		if (count_frame_ % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
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
		NyaGraphic::Swing();
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

