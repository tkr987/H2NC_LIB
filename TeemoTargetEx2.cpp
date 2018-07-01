#include <tuple>
#include "NyaDevice.h"
#include "NyaEffect.h"
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

TeemoExDevice211::TeemoExDevice211()
{
	dpx_ = new DevicePropertyX3;
	dpx_->move_angle_deg_ = 90;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = 5;
	dpx_->move_speed_ = 1;
	dpx_->move_speed_accel_ = 0.1;
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
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
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
	InterfaceHandleMissionAllOver* ihandle_mission_all_over;
	InterfaceHandleMissionEx* ihandle_mission_ex;
	InterfaceHandleSkill* ihandle_mission_skill;
	InterfaceHandleWarning* ihandle_warning;

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
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, 150, FPS_MAX * 3);
	}

	if (count_frame_ % 10 == 0)
	{
		main_.device211_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device211_.dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack3414(main_.device211_.dpx_, main_.device211_.gadget_gpx_, main_.device211_.epx_, main_.device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}


	// ヘルスが0以下になったらmission clearを表示する
	//if (main_.ph_->health_ <= 0)
	//{
	//	ihandle_mission_all_over = NyaInterface::GetHandleMissionAllOver();
	//	ihandle_mission_all_over->valid_ = true;
	//}

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

