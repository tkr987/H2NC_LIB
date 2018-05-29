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

TargetExTeemoMain::TargetExTeemoMain()
{
	gp_ = new GraphicProperty4;
	ph_ = new PositionHandle1;

}

TargetExTeemoMain::~TargetExTeemoMain()
{

	delete gp_;
	delete ph_;
}

TargetExTeemo::TargetExTeemo(void)
{
	InterfaceHandleMissionWarning* handle_mission_warning;

	count_frame_ = 0;

	nya_position_ = new NyaPosition;

	// mission warning setting
	handle_mission_warning = NyaInterface::GetHandleMissionWarning();
	NyaSound::LoadSoundFile("sound/warning.wav", &handle_mission_warning->sp_->sound_file_);
	NyaSound::ChangeVolume(&handle_mission_warning->sp_->sound_file_, 20);

	// target ex teemo main property
	NyaGraphic::LoadGraphicFile("img/target_teemo.png", &main_.gp_->graphic_file_);
	main_.ph_->health_max_ = 100;
	main_.ph_->health_now_ = 100;
	main_.ph_->collision_pow_ = 1;
	main_.ph_->collision_range_ = 20;
	main_.ph_->grid_x_ = 300;
	main_.ph_->grid_y_ = 200;
	nya_position_->Regist(main_.ph_);
}

TargetExTeemo::~TargetExTeemo(void)
{

	InterfaceHandleMissionWarning* ihandle_mission_warning;

	// 使用したグラフィックデータなどはデストラクタで破棄する
	NyaGraphic::DeleteGraphicFile(&main_.gp_->graphic_file_);
	ihandle_mission_warning = NyaInterface::GetHandleMissionWarning();
	NyaSound::DeleteSoundFile(&ihandle_mission_warning->sp_->sound_file_);

	delete nya_position_;
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
	InterfaceHandleMissionWarning* ihandle_mission_warning;

	// 行動開始1フレーム目
	// mission ex モードをtrueにする
	// mission warning 表示を実行する
	if (count_frame_ == 1)
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->valid_ = true;
		ihandle_mission_ex->value_ = 100;
		ihandle_mission_warning = NyaInterface::GetHandleMissionWarning();
		ihandle_mission_warning->draw_valid_ = true;
		ihandle_mission_warning->sound_valid_ = true;
	}

	// 通常処理
	nya_position_->Collision(main_.ph_, eOBJECT::TARGET1);
	count_frame_++;

	// ヘルスが0以下になったらmission clearを表示する
	if (main_.ph_->health_now_ <= 0)
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
	if (0 < main_.ph_->health_now_) 
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->value_ = main_.ph_->health_now_ / main_.ph_->health_max_ * 100;
	}
	else
	{
		ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
		ihandle_mission_ex->value_ = 0;
	}

#ifdef __DEBUG__
	NyaString::Write("debug_font", white, 50, 90, "[50, 790] target ex health = %d", (int)main_.ph_->health_now_);
#endif
}

