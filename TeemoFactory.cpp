#include <string>
#include "HNLIB.h"
#include "TeemoFactory.h"

using namespace HNLIB;

TeemoFactory::TeemoFactory()
{
}


TeemoFactory::~TeemoFactory()
{
}

void TeemoFactory::TargetCube(GraphicPropertyX4* gpx)
{
	gpx->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx->file_);
}

void TeemoFactory::TargetDeath1(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx)
{
	epx->interval_time_frame_ = 3;
	gpx->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death2.png", &gpx->file_);
}

void TeemoFactory::TargetDeath2(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx)
{
	epx->interval_time_frame_ = 3;
	gpx->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(8, 8, "img/target/death2.png", &gpx->file_);
}

