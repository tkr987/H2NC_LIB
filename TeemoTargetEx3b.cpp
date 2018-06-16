#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "TeemoTargetEx3b.h"

using namespace H2NLIB;

TeemoEx3bMain::TeemoEx3bMain()
{
	gpx_ = new GraphicPropertyX4;
	phandle_ = new PositionHandle1;
}

TeemoEx3bMain::~TeemoEx3bMain()
{
	delete gpx_;
	gpx_ = nullptr;
	delete phandle_;
	phandle_ = nullptr;
}

TeemoTargetEx3b::TeemoTargetEx3b()
{
	count_frame_ = 0;
	
	// main ƒƒ“ƒo‚ð‰Šú‰»
	NyaGraphic::LoadGraphicFile("img/target/teemo_ex3b.png", &main_.gpx_->file_);
	main_.phandle_->health_ = 1000;
	main_.phandle_->collision_power_ = 1;
	main_.phandle_->collision_range_ = 20;
	main_.phandle_->grid_x_ = -100;
	main_.phandle_->grid_y_ = -100;
}


TeemoTargetEx3b::~TeemoTargetEx3b()
{
	NyaGraphic::DeleteGraphicFile(&main_.gpx_->file_);
}

void TeemoTargetEx3b::MissionRun(void)
{
	Act();
	Draw();
}

void TeemoTargetEx3b::Act(void)
{

}

void TeemoTargetEx3b::Draw(void)
{

}

