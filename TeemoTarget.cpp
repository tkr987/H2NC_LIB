#include "H2NLIB.h"
#include "TeemoTarget.h"
using namespace std;
using namespace H2NLIB;

TeemoDevice::TeemoDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->move_angle_deg_ = 90;
	dpx_->move_speed_ = 3;
	dpx_->create_x_ = 400;
	dpx_->create_y_ = 200;
	gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gpx_->file_);
}

TeemoDevice::~TeemoDevice()
{
	delete dpx_;
	dpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
}

TeemoTargetMain::TeemoTargetMain()
{
	gpx_ = new GraphicPropertyX4;
	gpx_->draw_grid_cx_ = 400;
	gpx_->draw_grid_cy_ = 200;
	NyaGraphic::LoadGraphicFile("img/teemo_target.png", &gpx_->file_);
}

TeemoTargetMain::~TeemoTargetMain()
{
	delete gpx_;
	gpx_ = nullptr;
}

TeemoTarget::TeemoTarget()
{
	count_frame_ = 0;
}

void TeemoTarget::Act(void)
{	
	if (count_frame_ % FPS_MAX == 0)
		NyaDevice::Attack14(main_.device_.dpx_, main_.device_.gpx_, eOBJECT::TARGET_ATTACK1);

	count_frame_++;
}

void TeemoTarget::Draw(void)
{
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
}

