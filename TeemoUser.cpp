#include "HNLIB.h"
#include "TeemoUser.h"
using namespace HNLIB;

TeemoUser::TeemoUser()
{
	gpx_ = new GraphicPropertyX4;
	gpx_->draw_grid_cx_ = 100;
	gpx_->draw_grid_cy_ = 500;
	NyaGraphic::LoadGraphicFile("img/teemo.png", &gpx_->file_);
}

TeemoUser::~TeemoUser()
{
	delete gpx_;
	gpx_ = nullptr;
}

void TeemoUser::Act(void)
{

}

void TeemoUser::Draw(void)
{
	NyaGraphic::Draw(gpx_, eOBJECT::USER1);
}
