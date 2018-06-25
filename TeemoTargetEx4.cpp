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

TeemoExDevice421::TeemoExDevice421()
{
	dpx_ = new DevicePropertyX2;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 10;
	dpx_->move_speed_ = 12;
	dpx_->move_angle_deg_speed_ = 1.6;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_green3.png", &gadget_gpx_->file_);
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

TeemoEx4Cube1::TeemoEx4Cube1()
{
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	move_angle_ = 0;
	phandle_ = new PositionHandle;
	phandle_->collision_range_ = 20;
}

TeemoEx4Cube1::~TeemoEx4Cube1()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
	delete phandle_;
	phandle_ = nullptr;
}

TeemoExCube42::TeemoExCube42()
{
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.01;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = new PositionHandle;
	phandle_->collision_range_ = 20;
}

TeemoExCube42::~TeemoExCube42()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
	delete phandle_;
	phandle_ = nullptr;
}



TeemoEx4Main::TeemoEx4Main() : health_max_(1000)
{
	gpx_ = new GraphicPropertyX4;
	phandle_ = new PositionHandle;
}

TeemoEx4Main::~TeemoEx4Main()
{
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

void TeemoTargetEx4::MissionRun(void)
{
	static int mode = 1;
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	switch (mode)
	{
	case 1:
		Act1();
		Draw1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 90)
		{
			count_frame_ = 0;
			mode = 2;
		}
		break;
	case 2:
		Act2();
		Draw2();
		break;
	}

	count_frame_++;

#ifdef __DEBUG__
		NyaString::Write("design_fps_font", white, 50, 90, "[50, 90] count_frame = %u", count_frame_);
#endif
}

void TeemoTargetEx4::Act1(void)
{
	InterfaceHandleMissionEx* ihandle_mission_ex;
	InterfaceHandleMissionSkill *ihandle_mission_skill;

	// 行動開始1フレーム目
	// mission ex モードをtrueにする
	// mission warning 表示を実行する
	if (count_frame_ == 1)
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->valid_ = true;
		ihandle_mission_ex->value_ = 100;
		NyaSound::Play(warning_spx_);
	}

	// 移動処理
	if (main_.phandle_->grid_y_ < 140)
		main_.phandle_->grid_y_++;

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	ihandle_mission_skill = NyaInterface::GetHandleMissionSkill();
	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_damage_);

	if (count_frame_ == 350)
	{
		for (int i = 0; i < 8; i++)
		{
			cube1_collection_[i].move_angle_ = i * 45;
			cube1_collection_[i].phandle_->grid_x_ = main_.phandle_->grid_x_;
			cube1_collection_[i].phandle_->grid_y_ = main_.phandle_->grid_y_;
			NyaPosition::MoveAngleMode(cube1_collection_[i].phandle_, i * 45, 130, FPS_MAX * 3);
		}
	}

	if (600 <= count_frame_)
	{
		for (int i = 0; i < 8; i++)
		{
			cube1_collection_[i].move_angle_ += 5;
			cube1_collection_[i].phandle_->grid_x_ = main_.phandle_->grid_x_ + 130 * cos(AngleToRad(cube1_collection_[i].move_angle_));
			cube1_collection_[i].phandle_->grid_y_ = main_.phandle_->grid_y_ + 130 * sin(AngleToRad(cube1_collection_[i].move_angle_));
			NyaPosition::MoveAngleMode(cube1_collection_[i].phandle_, i * 45, 140, FPS_MAX * 3);
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
	static int update_device_angle = -5;
	InterfaceHandleMissionSkill *ihandle_mission_skill;
	DevicePropertyX1* cube_dpx;
	GraphicPropertyX4* cube_effect_gpx;
	EffectPropertyX1* cube_epx;
	GraphicPropertyX4* cube_gadget_gpx;

	if (count_frame_ == 1)
	{
		cube2_collection_[0].device22_.dpx_->move_angle_deg_ = 0;
		cube2_collection_[1].device22_.dpx_->move_angle_deg_ = 45;
		cube2_collection_[2].device22_.dpx_->move_angle_deg_ = 0;
		cube2_collection_[3].device22_.dpx_->move_angle_deg_ = 45;
	}

	cube2_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 140;
	cube2_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
	cube2_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ - 70;
	cube2_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
	cube2_collection_[2].phandle_->grid_x_ = main_.phandle_->grid_x_ + 70;
	cube2_collection_[2].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
	cube2_collection_[3].phandle_->grid_x_ = main_.phandle_->grid_x_ + 140;
	cube2_collection_[3].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	ihandle_mission_skill = NyaInterface::GetHandleMissionSkill();
	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_damage_);

	// ここから下の処理は
	// フレームカウントFPS_MAX * 3以上で実行する
	if (count_frame_ < FPS_MAX * 3)
		return;

	if (count_frame_ % 20 == 0)
	{
		cube2_collection_[0].device22_.dpx_->move_angle_deg_ -= 10;
		cube2_collection_[1].device22_.dpx_->move_angle_deg_ -= 10;
		cube2_collection_[2].device22_.dpx_->move_angle_deg_ += 10;
		cube2_collection_[3].device22_.dpx_->move_angle_deg_ += 10;
		for (int i = 0; i < 4; i++)
		{
			cube2_collection_[i].device22_.dpx_->create_x_ = cube2_collection_[i].phandle_->grid_x_;
			cube2_collection_[i].device22_.dpx_->create_y_ = cube2_collection_[i].phandle_->grid_y_;
			cube_dpx = cube2_collection_[i].device22_.dpx_;
			cube_effect_gpx = cube2_collection_[i].device22_.effect_gpx_;
			cube_epx = cube2_collection_[i].device22_.epx_;
			cube_gadget_gpx = cube2_collection_[i].device22_.gadget_gpx_;
			for (int n = 0; n < 16; n++)
			{
				cube2_collection_[i].device22_.dpx_->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube2_collection_[i].device22_.dpx_->move_angle_deg_ += 90;
			for (int n = 0; n < 16; n++)
			{
				cube2_collection_[i].device22_.dpx_->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube2_collection_[i].device22_.dpx_->move_angle_deg_ += 90;
			for (int n = 0; n < 16; n++)
			{
				cube2_collection_[i].device22_.dpx_->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube2_collection_[i].device22_.dpx_->move_angle_deg_ += 90;
			for (int n = 0; n < 16; n++)
			{
				cube2_collection_[i].device22_.dpx_->delay_time_frame_ = n * 2;
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube2_collection_[i].device22_.dpx_->move_angle_deg_ += 90;
		}
	}


	if (count_frame_ % (FPS_MAX * 14) < FPS_MAX * 8 && count_frame_ % 5 == 0)
	{
		update_device_angle = (-5 < update_device_angle) ? update_device_angle - 1 : -5;
		main_.device21_.dpx_->move_angle_deg_speed_ = (main_.device21_.dpx_->move_angle_deg_speed_ < 1.6) ? main_.device21_.dpx_->move_angle_deg_speed_ + 0.1 : 1.6;
		main_.device21_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device21_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device21_.dpx_->move_angle_deg_ += update_device_angle;
		for (int way = 0 ; way < 12; way++)
		{
			NyaDevice::Attack2414(main_.device21_.dpx_, main_.device21_.gadget_gpx_, main_.device21_.epx_, main_.device21_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			main_.device21_.dpx_->move_angle_deg_ -= 30;
		}
	}
	else if (FPS_MAX * 8 <= count_frame_ % (FPS_MAX * 14) && count_frame_ % 5 == 0)
	{
		update_device_angle = (update_device_angle < 5) ? update_device_angle + 1 : 5;
		main_.device21_.dpx_->move_angle_deg_speed_ = (-1.6 < main_.device21_.dpx_->move_angle_deg_speed_) ? main_.device21_.dpx_->move_angle_deg_speed_ - 0.1 : -1.6;
		main_.device21_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device21_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device21_.dpx_->move_angle_deg_ += update_device_angle;
		for (int way = 0 ; way < 12; way++)
		{
			NyaDevice::Attack2414(main_.device21_.dpx_, main_.device21_.gadget_gpx_, main_.device21_.epx_, main_.device21_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			main_.device21_.dpx_->move_angle_deg_ += 30;
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
	InterfaceHandleMissionEx* ihandle_mission_ex;
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
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
	}
	else
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->value_ = 0;
	}
}


void TeemoTargetEx4::Draw2(void)
{
	InterfaceHandleMissionEx* ihandle_mission_ex;
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);

	if (count_frame_ < FPS_MAX * 5)
	{
		for (int i = 0; i < 4; i++)
		{	// cube拡大
			if (cube2_collection_[i].gpx_->extend_rate_ < 0.4)
				cube2_collection_[i].gpx_->extend_rate_ += 0.01;
		}

	}

	// main描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// cube描画
	for (int i = 0; i < 4; i++)
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
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
	}
	else
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->value_ = 0;
	}
}

