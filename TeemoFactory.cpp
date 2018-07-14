#include <string>
#include "HNLIB.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"

using namespace HNLIB;

TeemoFactory::TeemoFactory()
{
}


TeemoFactory::~TeemoFactory()
{
}

void TeemoFactory::TargetAttackOrange5(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_ORANGE5;
	dpx->draw_angle_speed_deg_ = 2;
	NyaGraphic::LoadGraphicFile("img/target/attack_orange5.png", &gpx->file_);
}

void TeemoFactory::TargetCube(GraphicPropertyX4* gpx)
{
	gpx->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx->file_);
}

void TeemoFactory::TargetDeath1(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx)
{
	epx->interval_time_frame_ = 3;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &gpx->file_);
}

void TeemoFactory::TargetDeath2(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx)
{
	epx->interval_time_frame_ = 3;
	gpx->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(8, 8, "img/target/death2.png", &gpx->file_);
}

