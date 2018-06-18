
#include "NyaGraphic.h"
#include "TeemoBackgroundMission1.h"

using namespace H2NLIB;


TeemoBackgroundMission1::TeemoBackgroundMission1()
{
	gp_ = new GraphicPropertyX1;
	gp_->draw_grid_x_ = 0;
	gp_->draw_grid_y_ = -2560 + 720;
	NyaGraphic::LoadGraphicFile("img/back/back1.png", &gp_->file_);
}


TeemoBackgroundMission1::~TeemoBackgroundMission1()
{
	NyaGraphic::DeleteGraphicFile(&gp_->file_);
	delete gp_;
}

void TeemoBackgroundMission1::MissionClear(void)
{
	Draw();
}

void TeemoBackgroundMission1::MissionContinue(void)
{
	Draw();
}

void TeemoBackgroundMission1::MissionRun(void)
{
	Act();
	Draw();
}

void TeemoBackgroundMission1::Act(void)
{
	const double limit_scroll_max_y = -10.0;
	const int scroll_max_time_sec = 30;
	const double scroll_speed_per_frame = (double)gp_->file_.size_y_ / (double)(scroll_max_time_sec * MAX_FPS);
	
	if (gp_->draw_grid_y_ < limit_scroll_max_y)
		gp_->draw_grid_y_ += scroll_speed_per_frame;
}


void TeemoBackgroundMission1::Draw(void)
{
	NyaGraphic::Draw(gp_, eOBJECT::BACK_MAP1);
}


