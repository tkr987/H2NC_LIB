
#include "NyaGraphic.h"
#include "TeemoBackgroundMission1.h"

using namespace H2NLIB;



TeemoBackgroundMission1::TeemoBackgroundMission1()
{
	gp_ = new GraphicProperty1;
	gp_->draw_grid_x_ = 0;
	gp_->draw_grid_y_ = -2560 + 720;
	NyaGraphic::LoadGraphicFile("img/target_teemo.png", &gp_->graphic_file_);
}


TeemoBackgroundMission1::~TeemoBackgroundMission1()
{
	delete gp_;
}


void TeemoBackgroundMission1::Act(void)
{
	const double limit_scroll_max_y = -10.0;
	const int scroll_max_time_sec = 30;
	const double scroll_speed_per_frame = (double)gp_->graphic_file_.size_y_ / (double)(scroll_max_time_sec * FPS_MAX);
	
	if (gp_->draw_grid_y_ < limit_scroll_max_y)
		gp_->draw_grid_y_ += scroll_speed_per_frame;
}


void TeemoBackgroundMission1::Draw(void)
{
	NyaGraphic::Draw(gp_, eOBJECT::BACK_MAP1);
}

