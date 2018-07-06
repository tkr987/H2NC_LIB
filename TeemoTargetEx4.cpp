#include <tuple>
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaEnum.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaInterface.h"
#include "NyaPosition.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "TeemoEnum.h"
#include "TeemoTargetEx4.h"

#define __DEBUG__

using namespace std;
using namespace H2NLIB;

TeemoExBullet41::TeemoExBullet41()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 2;
	dpx_->move_speed_ = 8;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
};

TeemoExBullet41::~TeemoExBullet41()
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
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice421::~TeemoExDevice421()
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

TeemoExDevice422::TeemoExDevice422()
{
	dpx_ = new DevicePropertyX2;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 10;
	dpx_->move_speed_ = 9;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_green1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice422::~TeemoExDevice422()
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

TeemoExDevice423::TeemoExDevice423()
{
	dpx_ = new DevicePropertyX2;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 6;
	dpx_->draw_angle_speed_deg_ = 2;
	dpx_->move_speed_ = 10;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_green4.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice423::~TeemoExDevice423()
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

TeemoExDevice424::TeemoExDevice424()
{
	dpx_ = new DevicePropertyX2;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 5;
	dpx_->draw_angle_speed_deg_ = 2;
	dpx_->move_speed_ = 8;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_green5.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice424::~TeemoExDevice424()
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

TeemoExCube42::TeemoExCube42()
{
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoExCube42::~TeemoExCube42()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
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
	NyaGraphic::LoadGraphicFile("img/target/attack_green3.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice431::~TeemoExDevice431()
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

TeemoExDevice432::TeemoExDevice432()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 6;
	dpx_->move_speed_ = 10;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = 120;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
};

TeemoExDevice432::~TeemoExDevice432()
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

TeemoEx4Cube1::TeemoEx4Cube1()
{
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	move_angle_ = 0;
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoEx4Cube1::~TeemoEx4Cube1()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

TeemoExCube43::TeemoExCube43()
{
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoExCube43::~TeemoExCube43()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}



TeemoEx4Main::TeemoEx4Main() : health_max_(1000)
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
}

TeemoEx4Main::~TeemoEx4Main()
{
	NyaGraphic::DeleteGraphicFile(&death1_gpx_->file_);
	delete death1_epx_;
	death1_epx_ = nullptr;
	delete death1_gpx_;
	death1_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	delete phandle_;
	phandle_ = nullptr;
}

TeemoTargetEx4::TeemoTargetEx4()
{
	// メンバ変数初期化
	count_frame_ = 0;
	warning_spx_ = new SoundPropertyX;
	NyaSound::LoadFile("sound/warning.wav", &warning_spx_->file_);
	NyaSound::ChangeVolume(&warning_spx_->file_, 20);

	// main メンバの初期化
	NyaGraphic::LoadGraphicFile("img/target/teemo_ex4.png", &main_.gpx_->file_);
	main_.phandle_->health_ = 1000;
	main_.phandle_->collision_power_ = 1;
	main_.phandle_->collision_range_ = 10;
	main_.phandle_->grid_x_ =  SCREEN_MAX_X / 2;
	main_.phandle_->grid_y_ = -100;

	mode_ = 1;

	// フォント設定
	NyaString::SettingFont("warning_logo_font", 64, 4);
	NyaString::SettingFont("ex_logo_font", 100, 12);
}


TeemoTargetEx4::~TeemoTargetEx4()
{
	delete warning_spx_;
	warning_spx_ = nullptr;
	NyaGraphic::DeleteGraphicFile(&main_.gpx_->file_);
}

void TeemoTargetEx4::Act(void)
{
	switch (mode_)
	{
	case 1:
		Act1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 80)
		{
			count_frame_ = 0;
			mode_ = 2;
			NyaGraphic::Swing();
		}
		break;
	case 2:
		Act2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 40)
		{
			count_frame_ = 0;
			mode_ = 3;
			NyaGraphic::Swing();
		}
		break;
	case 3:
		Act3();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= 0)
		{
			count_frame_ = 0;
			mode_ = 4;
		}
		break;
	}

	count_frame_++;
}

void TeemoTargetEx4::Draw(void)
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

void TeemoTargetEx4::Act1(void)
{
	InterfaceHandleSkill *ihandle_mission_skill;

	// 行動開始1フレーム目
	// mission ex モードをtrueにする
	// mission warning 表示を実行する
	if (count_frame_ == 1)
	{
		NyaInterface::GetHandleHealth()->valid_ = true;
		NyaInterface::GetHandleHealth()->value_ = 100;
		NyaSound::Play(warning_spx_);
	}

	// 移動処理
	if (main_.phandle_->grid_y_ < 140)
		main_.phandle_->grid_y_++;

	// 衝突判定　衝突ダメージだけ経験値を追加
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_damage_);

	if (count_frame_ == 350)
	{
		for (int i = 0; i < 8; i++)
		{
			cube1_collection_[i].move_angle_ = i * 45;
			cube1_collection_[i].phandle_->grid_x_ = main_.phandle_->grid_x_;
			cube1_collection_[i].phandle_->grid_y_ = main_.phandle_->grid_y_;
			NyaPosition::MoveLengthMode(cube1_collection_[i].phandle_, i * 45, 130, FPS_MAX * 3);
		}
	}

	if (count_frame_ < 350 + FPS_MAX * 2)
		return;

	for (int i = 0; i < 8; i++)
	{
		ihandle_mission_skill->AddExp(cube1_collection_[i].phandle_->collision_hit_damage_);
		NyaPosition::Collide(cube1_collection_[i].phandle_, eOBJECT::TARGET1);
		main_.phandle_->health_ -= cube1_collection_[i].phandle_->collision_hit_damage_;
	}


	if (600 <= count_frame_)
	{
		for (int i = 0; i < 8; i++)
		{
			cube1_collection_[i].move_angle_ += 5;
			cube1_collection_[i].phandle_->grid_x_ = main_.phandle_->grid_x_ + 130 * cos(AngleToRad(cube1_collection_[i].move_angle_));
			cube1_collection_[i].phandle_->grid_y_ = main_.phandle_->grid_y_ + 130 * sin(AngleToRad(cube1_collection_[i].move_angle_));
			NyaPosition::MoveLengthMode(cube1_collection_[i].phandle_, i * 45, 140, FPS_MAX * 3);
			if (count_frame_ % 15 == 0)
			{
				bullet1_.dpx_->create_x_ = cube1_collection_[i].phandle_->grid_x_;
				bullet1_.dpx_->create_y_ = cube1_collection_[i].phandle_->grid_y_;
				for (int bullet_index = -11; bullet_index < 12; bullet_index++)
				{
					bullet1_.dpx_->move_angle_deg_ = cube1_collection_[i].move_angle_ + (bullet_index * 2);
					NyaDevice::Attack1414(bullet1_.dpx_, bullet1_.gadget_gpx_, bullet1_.epx_, bullet1_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
				}
			}
		}
	}
}

void TeemoTargetEx4::Act2(void)
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
		main_.phandle_->health_ -= cube2_collection_[i].phandle_->collision_hit_damage_;
	}


	if (count_frame_ < FPS_MAX * 5)
		return;

	if (count_frame_ % 10 == 0)
	{
		main_.device22_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device22_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 5; way++)
		{
			main_.device22_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack2414(main_.device22_.dpx_, main_.device22_.gadget_gpx_, main_.device22_.epx_, main_.device22_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		main_.device23_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device23_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 5; way++)
		{
			main_.device23_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack2414(main_.device23_.dpx_, main_.device23_.gadget_gpx_, main_.device23_.epx_, main_.device23_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		main_.device24_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device24_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 5; way++)
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
		for (int angle = 0; angle < 360; angle += 4)
		{
			cube_dpx->move_angle_deg_ += 4;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		cube_dpx = cube2_collection_[3].device21_.dpx_;
		cube_gadget_gpx = cube2_collection_[3].device21_.gadget_gpx_;
		cube_epx = cube2_collection_[3].device21_.epx_;
		cube_effect_gpx = cube2_collection_[3].device21_.effect_gpx_;
		cube_dpx->create_x_ = cube2_collection_[3].phandle_->grid_x_;
		cube_dpx->create_y_ = cube2_collection_[3].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 4)
		{
			cube_dpx->move_angle_deg_ += 4;
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
		for (int angle = 0; angle < 360; angle += 4)
		{
			cube_dpx->move_angle_deg_ += 4;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		cube_dpx = cube2_collection_[4].device21_.dpx_;
		cube_gadget_gpx = cube2_collection_[4].device21_.gadget_gpx_;
		cube_epx = cube2_collection_[4].device21_.epx_;
		cube_effect_gpx = cube2_collection_[4].device21_.effect_gpx_;
		cube_dpx->create_x_ = cube2_collection_[4].phandle_->grid_x_;
		cube_dpx->create_y_ = cube2_collection_[4].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 4)
		{
			cube_dpx->move_angle_deg_ += 4;
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
		for (int angle = 0; angle < 360; angle += 4)
		{
			cube_dpx->move_angle_deg_ += 4;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		cube_dpx = cube2_collection_[5].device21_.dpx_;
		cube_gadget_gpx = cube2_collection_[5].device21_.gadget_gpx_;
		cube_epx = cube2_collection_[5].device21_.epx_;
		cube_effect_gpx = cube2_collection_[5].device21_.effect_gpx_;
		cube_dpx->create_x_ = cube2_collection_[5].phandle_->grid_x_;
		cube_dpx->create_y_ = cube2_collection_[5].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		for (int angle = 0; angle < 360; angle += 4)
		{
			cube_dpx->move_angle_deg_ += 4;
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

void TeemoTargetEx4::Act3(void)
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

	if (count_frame_ < FPS_MAX * 7)
		return;

	for (int i = 0; i < 4; i++)
	{
		NyaPosition::Collide(cube3_collection_[i].phandle_, eOBJECT::TARGET1);
		ihandle_mission_skill->AddExp(cube3_collection_[i].phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= cube3_collection_[i].phandle_->collision_hit_damage_;
	}

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
			for (int n = 0; n < 16; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
			for (int n = 0; n < 10; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
			for (int n = 0; n < 10; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
			for (int n = 0; n < 10; n++)
			{
				cube_dpx->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube_dpx->move_angle_deg_ += 90;
		}
	}


	if (count_frame_ % (FPS_MAX * 14) < FPS_MAX * 8 && count_frame_ % 5 == 0)
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
	else if (FPS_MAX * 8 <= count_frame_ % (FPS_MAX * 14) && count_frame_ % 5 == 0)
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


void TeemoTargetEx4::Draw1(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);

	if (count_frame_ < FPS_MAX * 5)
	{
		NyaString::Write("warning_logo_font", red, 310, 200, "WARNING");
		NyaString::Write("ex_logo_font", red, 255, 300, "EX BOSS");
	}

	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// cube描画
	for (int i = 0; i < 8; i++)
	{
		if (count_frame_ % 5 == 0)
			cube1_collection_[i].gpx_->file_div_ = ++cube1_collection_[i].gpx_->file_div_ % 5;
		cube1_collection_[i].gpx_->draw_grid_cx_ = cube1_collection_[i].phandle_->grid_x_;
		cube1_collection_[i].gpx_->draw_grid_cy_ = cube1_collection_[i].phandle_->grid_y_;
		NyaGraphic::Draw(cube1_collection_[i].gpx_, eOBJECT::TARGET1);
	}

	// ヘルスバー(%)の表示をする
	// ただし、ヘルス0以下のときゲージ0(%)として表示する
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
}

void TeemoTargetEx4::Draw2(void)
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
	for (int i = 0; i < 6; i++)
	{
		if (count_frame_ % 5 == 0)
			cube2_collection_[i].gpx_->file_div_ = ++cube2_collection_[i].gpx_->file_div_ % 5;
		cube2_collection_[i].gpx_->draw_grid_cx_ = cube2_collection_[i].phandle_->grid_x_;
		cube2_collection_[i].gpx_->draw_grid_cy_ = cube2_collection_[i].phandle_->grid_y_;
		NyaGraphic::Draw(cube2_collection_[i].gpx_, eOBJECT::TARGET1);
	}

	// ヘルスバー(%)の表示をする
	// ただし、ヘルス0以下のときゲージ0(%)として表示する
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
}

void TeemoTargetEx4::Draw3(void)
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
	for (int i = 0; i < 4; i++)
	{
		if (count_frame_ % 5 == 0)
			cube3_collection_[i].gpx_->file_div_ = ++cube3_collection_[i].gpx_->file_div_ % 5;
		cube3_collection_[i].gpx_->draw_grid_cx_ = cube3_collection_[i].phandle_->grid_x_;
		cube3_collection_[i].gpx_->draw_grid_cy_ = cube3_collection_[i].phandle_->grid_y_;
		NyaGraphic::Draw(cube3_collection_[i].gpx_, eOBJECT::TARGET1);
	}

	// ヘルスバー(%)の表示をする
	// ただし、ヘルス0以下のときゲージ0(%)として表示する
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
	else
		NyaInterface::GetHandleHealth()->value_ = 0;
}

void TeemoTargetEx4::Draw4(void)
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

