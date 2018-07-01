#include <tuple>
#include "NyaInterface.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "TeemoTargetEx.h"

#define __DEBUG__

using namespace std;
using namespace H2NLIB;

TargetExTeemoMain::TargetExTeemoMain() : health_max_(500) 
{
	gp_ = new GraphicPropertyX4;
	ph_ = new PositionHandle;

}

TargetExTeemoMain::~TargetExTeemoMain()
{

	delete gp_;
	gp_ = nullptr;
	delete ph_;
	ph_ = nullptr;
}

TargetExTeemo::TargetExTeemo(void)
{
	InterfaceHandleWarning* handle_warning;

	count_frame_ = 0;

	// mission warning handle 設定
	handle_warning = NyaInterface::GetHandleWarning();
	NyaSound::LoadFile("sound/warning.wav", &handle_warning->spx_->file_);
	NyaSound::ChangeVolume(&handle_warning->spx_->file_, 20);

	// target ex teemo main property
	NyaGraphic::LoadGraphicFile("img/target_teemo.png", &main_.gp_->file_);
	main_.ph_->health_ = main_.health_max_;
	main_.ph_->collision_power_ = 1;
	main_.ph_->collision_range_ = 20;
	main_.ph_->grid_x_ = 300;
	main_.ph_->grid_y_ = 200;
}

TargetExTeemo::~TargetExTeemo(void)
{

	InterfaceHandleWarning* ihandle_warning;

	// 使用したグラフィックデータなどはデストラクタで破棄する
	NyaGraphic::DeleteGraphicFile(&main_.gp_->file_);
	ihandle_warning = NyaInterface::GetHandleWarning();
	NyaSound::DeleteSoundFile(&ihandle_warning->spx_->file_);
}


void TargetExTeemo::MissionRun(void)
{
	Act();
	Draw();
}

void TargetExTeemo::Act(void)
{
	InterfaceHandleMissionClear* ihandle_mission_clear;
	InterfaceHandleMissionEx* ihandle_mission_ex;
	InterfaceHandleSkill *ihandle_mission_skill;
	InterfaceHandleWarning* ihandle_warning;

	// 行動開始1フレーム目
	// mission ex モードをtrueにする
	// mission warning 表示を実行する
	if (count_frame_ == 1)
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->valid_ = true;
		ihandle_warning = NyaInterface::GetHandleWarning();
		ihandle_warning->draw_valid_ = true;
		ihandle_warning->sound_valid_ = true;
	}

	// 通常処理
	NyaPosition::Collide(main_.ph_, eOBJECT::TARGET1);
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	ihandle_mission_skill->exp_[static_cast<int>(ihandle_mission_skill->select_)] += main_.ph_->collision_hit_damage_;
	count_frame_++;

	// ヘルスが0以下になったらmission clearを表示する
	if (main_.ph_->health_ <= 0)
	{
		ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
		ihandle_mission_clear->valid_ = true;
	}

}

void TargetExTeemo::Draw(void)
{
	InterfaceHandleMissionEx* ihandle_mission_ex;
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	// 本体の描画
	main_.gp_->draw_grid_cx_ = main_.ph_->grid_x_;
	main_.gp_->draw_grid_cy_ = main_.ph_->grid_y_;
	NyaGraphic::Draw(main_.gp_, eOBJECT::TARGET1);

	// ヘルスバー(%)の表示をする
	// ただし、ヘルス0以下のときゲージ0(%)として表示する
	if (0 < main_.ph_->health_) 
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->value_ = (double)main_.ph_->health_ / (double)main_.health_max_ * 100.0;
	}
	else
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->value_ = 0;
	}

#ifdef __DEBUG__
	NyaString::Write("debug_font", white, 50, 90, "[50, 790] target ex health = %d", (int)main_.ph_->health_);
#endif
}

