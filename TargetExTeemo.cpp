#include <tuple>
#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "TargetExTeemo.h"

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

void TargetExTeemo::Act(void)
{
	DesignHandleMissionClear* handle_mission_clear;
	DesignHandleMissionEx* handle_mission_ex;
	DesignHandleMissionWarning* handle_mission_warning;


	if (count_ == 1)
	{
		handle_mission_ex = nya_design_->GetHandleMissionEx();
		handle_mission_ex->valid_ = true;
		handle_mission_ex->value_ = 100;
		handle_mission_warning = nya_design_->GetHandleMissionWarning();
		handle_mission_warning->draw_valid_ = true;
		handle_mission_warning->sound_valid_ = true;
	}

	nya_position_->Collision(main_.ph_, eOBJECT::NUM::TARGET1);
	

	if (main_.ph_->health_now_ <= 0)
	{
		handle_mission_clear = nya_design_->GetHandleMissionClear();
		handle_mission_clear->valid_ = true;
	}

	count_++;
}

void TargetExTeemo::Draw(void)
{
	DesignHandleMissionEx* handle_mission_ex;
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	main_.gp_->draw_grid_cx_ = main_.ph_->grid_x_;
	main_.gp_->draw_grid_cy_ = main_.ph_->grid_y_;
	nya_graphic_->Draw(main_.gp_, eOBJECT::NUM::TARGET1);

	if (0 < main_.ph_->health_now_) 
	{
		handle_mission_ex = nya_design_->GetHandleMissionEx();
		handle_mission_ex->value_ = main_.ph_->health_now_ / main_.ph_->health_max_ * 100;
	}
	else
	{
		handle_mission_ex = nya_design_->GetHandleMissionEx();
		handle_mission_ex->value_ = 0;
	}

	NyaString::Write("debug_font", white, 50, 90, "[50, 790] target ex health = %d", (int)main_.ph_->health_now_);
}


void TargetExTeemo::MissionEnd(void)
{
	DesignHandleMissionWarning* handle_mission_warning;

	handle_mission_warning = nya_design_->GetHandleMissionWarning();
	nya_sound_->DeleteSoundFile(&handle_mission_warning->sp_->sound_file_);
	nya_graphic_->DeleteGraphicFile(&main_.gp_->graphic_file_);

	delete nya_design_;
	delete nya_graphic_;
	delete nya_position_;
}


void TargetExTeemo::MissionStart(void)
{
	DesignHandleMissionWarning* handle_mission_warning;

	count_ = 0;

	nya_design_ = new NyaDesign;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
	nya_sound_ = new NyaSound;

	// mission warning
	handle_mission_warning = nya_design_->GetHandleMissionWarning();
	nya_sound_->LoadSoundFile("sound/warning.wav", &handle_mission_warning->sp_->sound_file_);
	nya_sound_->ChangeVolume(handle_mission_warning->sp_, 20);

	// target ex teemo main property
	nya_graphic_->LoadGraphicFile("img/target_teemo.png", &main_.gp_->graphic_file_);
	main_.ph_->health_max_ = 100;
	main_.ph_->health_now_ = 100;
	main_.ph_->collision_pow_ = 1;
	main_.ph_->collision_range_ = 20;
	main_.ph_->grid_x_ = 300;
	main_.ph_->grid_y_ = 200;
	nya_position_->Regist(main_.ph_);
}

