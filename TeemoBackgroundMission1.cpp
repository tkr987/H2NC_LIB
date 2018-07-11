
#include "NyaGraphic.h"
#include "TeemoBackgroundMission1.h"

using namespace HNLIB;


TeemoBackgroundMission1::TeemoBackgroundMission1()
{
	gp_ = new GraphicPropertyX1;
	gp_->draw_grid_x_ = -400;
	gp_->draw_grid_y_ = -2560 + 720;
	NyaGraphic::LoadGraphicFile("img/back/back3.png", &gp_->file_);
}


TeemoBackgroundMission1::~TeemoBackgroundMission1()
{
	NyaGraphic::DeleteGraphicFile(&gp_->file_);
	delete gp_;
	gp_ = nullptr;
}

void TeemoBackgroundMission1::Act(void)
{
	const double limit_scroll_max_y = -10.0;
	
	if (gp_->draw_grid_y_ < limit_scroll_max_y)
		gp_->draw_grid_y_ += 0.2;
}


void TeemoBackgroundMission1::Draw(void)
{
	NyaGraphic::Draw(gp_, eOBJECT::BACK_MAP1);
}


