#include "NyaGraphic.h"
#include "TeemoBack1.h"
#include "TeemoEnum.h"

using namespace HNLIB;


TeemoBack1::TeemoBack1()
{
	gpx_ = new GraphicPropertyX1;
	gpx_->draw_grid_x_ = -400;
	gpx_->draw_grid_y_ = -2560 + 720;
	NyaGraphic::LoadGraphicFile("img/back/back1.png", &gpx_->file_);
}


TeemoBack1::~TeemoBack1()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
}

void TeemoBack1::Act(void)
{
	const double limit_scroll_max_y = -4.0;
	
	if (gpx_->draw_grid_y_ < limit_scroll_max_y)
		gpx_->draw_grid_y_ += MAP_SCROLL_PER_FRAME;
}


void TeemoBack1::Draw(void)
{
	NyaGraphic::Draw(gpx_, eOBJECT::BACK_MAP1);
}


