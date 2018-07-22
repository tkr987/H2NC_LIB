#include "NyaGraphic.h"
#include "TeemoBack3.h"
#include "TeemoEnum.h"

using namespace HNLIB;


TeemoBack3::TeemoBack3()
{
	gpx_ = new GraphicPropertyX1;
	gpx_->draw_grid_x_ = -400;
	gpx_->draw_grid_y_ = -2560 + 720;
	NyaGraphic::Load("img/back/back3.png", &gpx_->file_);
}


TeemoBack3::~TeemoBack3()
{
	NyaGraphic::Delete(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
}

void TeemoBack3::Act(void)
{
	const double limit_scroll_max_y = -4.0;
	
	if (gpx_->draw_grid_y_ < limit_scroll_max_y)
		gpx_->draw_grid_y_ += MAP_SCROLL_PER_FRAME;
}


void TeemoBack3::Draw(void)
{
	NyaGraphic::Draw(gpx_, eOBJECT::BACK_MAP1);
}


