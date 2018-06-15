#include <tuple>
#include "NyaInterface.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "TeemoTargetEx2.h"

#define __DEBUG__

using namespace std;
using namespace H2NLIB;

TargetExTeemo2Main::TargetExTeemo2Main() : health_max_(200) 
{
	gp_ = new GraphicPropertyX4;
	ph_ = new PositionHandle1;

}

TargetExTeemo2Main::~TargetExTeemo2Main()
{

	delete gp_;
	delete ph_;
}

TargetExTeemo2::TargetExTeemo2(void)
{
	InterfaceHandleMissionWarning* handle_mission_warning;

	count_frame_ = 0;

	// mission warning setting
	handle_mission_warning = NyaInterface::GetHandleMissionWarning();
	NyaSound::LoadSoundFile("sound/warning.wav", &handle_mission_warning->spx_->file_);
	NyaSound::ChangeVolume(&handle_mission_warning->spx_->file_, 20);

	// target ex teemo main property
	NyaGraphic::LoadGraphicFile("img/target_teemo.png", &main_.gp_->graphic_file_);
	main_.ph_->health_ = main_.health_max_;
	main_.ph_->collision_power_ = 1;
	main_.ph_->collision_range_ = 20;
	main_.ph_->grid_x_ = 300;
	main_.ph_->grid_y_ = 200;
}

TargetExTeemo2::~TargetExTeemo2(void)
{

	InterfaceHandleMissionWarning* ihandle_mission_warning;

	// 使用したグラフィックデータなどはデストラクタで破棄する
	NyaGraphic::DeleteGraphicFile(&main_.gp_->graphic_file_);
	ihandle_mission_warning = NyaInterface::GetHandleMissionWarning();
	NyaSound::DeleteSoundFile(&ihandle_mission_warning->spx_->file_);
}


void TargetExTeemo2::MissionRun(void)
{
	Act();
	Draw();
}

void TargetExTeemo2::Act(void)
{
	InterfaceHandleMissionAllOver* ihandle_mission_all_over;
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
	NyaPosition::Collision(main_.ph_, eOBJECT::TARGET1);
	count_frame_++;

	// ヘルスが0以下になったらmission clearを表示する
	if (main_.ph_->health_ <= 0)
	{
		ihandle_mission_all_over = NyaInterface::GetHandleMissionAllOver();
		ihandle_mission_all_over->valid_ = true;
	}

}

void TargetExTeemo2::Draw(void)
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
		ihandle_mission_ex->value_ = main_.ph_->health_ / main_.health_max_ * 100;
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

