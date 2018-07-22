#include "HNLIB.h"
#include "Target1Pantoea.h"

using namespace HNLIB;

Target1PantoeaMain::Target1PantoeaMain()
{
	death1_epx_ = new EffectPropertyX1;
	death1_epx_->interval_time_frame_ = 3;
	death1_gpx_ = new GraphicPropertyX4;
	death1_gpx_->extend_rate_ = 0.5;
	NyaGraphic::Load(4, 2, "img/target/death1.png", &death1_gpx_->file_);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/teemo_ex3.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -100;
}

Target1PantoeaMain::~Target1PantoeaMain()
{
	NyaGraphic::Delete(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
	delete phandle_;
	phandle_ = nullptr;
}

Target1Pantoea::Target1Pantoea()
{

}


Target1Pantoea::~Target1Pantoea()
{

}

void Target1Pantoea::Act()
{

}

void Target1Pantoea::Draw(void)
{

}

Target1PantoeaDevice::Target1PantoeaDevice()
{
}

Target1PantoeaDevice::~Target1PantoeaDevice()
{
}
