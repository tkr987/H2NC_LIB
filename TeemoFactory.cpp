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

void TeemoFactory::TargetAttackBlue1(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_BLUE1;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue1.png", &gpx->file_);
}

void TeemoFactory::TargetAttackBlue2(HNLIB::DevicePropertyX1 * dpx, HNLIB::GraphicPropertyX4 * gadget_gpx, HNLIB::EffectPropertyX1 * epx, HNLIB::GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_BLUE2;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue3.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackBlue7(HNLIB::DevicePropertyX1 * dpx, HNLIB::GraphicPropertyX4 * gadget_gpx, HNLIB::EffectPropertyX1 * epx, HNLIB::GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_BLUE7;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue7.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackOrange3(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx, HNLIB::EffectPropertyX1 * epx, HNLIB::GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_ORANGE3;
	NyaGraphic::LoadGraphicFile("img/target/attack_orange3.png", &gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackOrange5(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_ORANGE5;
	dpx->draw_angle_speed_deg_ = 2;
	NyaGraphic::LoadGraphicFile("img/target/attack_orange5.png", &gpx->file_);
}

void TeemoFactory::TargetAttackWhite5(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_WHITE5;
	dpx->draw_angle_speed_deg_ = 2;
	NyaGraphic::LoadGraphicFile("img/target/attack_white5.png", &gpx->file_);
}

void TeemoFactory::TargetCube(GraphicPropertyX4* gpx)
{
	gpx->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx->file_);
}

void TeemoFactory::TargetCubeBlue(GraphicPropertyX4* gpx)
{
	gpx->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_blue.png", &gpx->file_);
}

void TeemoFactory::TargetDeath1(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx)
{
	epx->interval_time_frame_ = 3;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &gpx->file_);
}

void TeemoFactory::TargetDeath1(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx, SoundPropertyX* spx)
{
	epx->interval_time_frame_ = 3;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &gpx->file_);
	NyaSound::LoadFile("sound/target_death1.wav", &spx->file_);
	NyaSound::ChangeVolume(&spx->file_, 40);
}

void TeemoFactory::TargetDeath2(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx)
{
	epx->interval_time_frame_ = 3;
	gpx->extend_rate_ = 0.8;
	NyaGraphic::LoadGraphicFile(8, 8, "img/target/death2.png", &gpx->file_);
}

void TeemoFactory::TargetDeath2(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx, HNLIB::SoundPropertyX* spx)
{
	epx->interval_time_frame_ = 3;
	gpx->extend_rate_ = 0.8;
	NyaGraphic::LoadGraphicFile(8, 8, "img/target/death2.png", &gpx->file_);
	NyaSound::LoadFile("sound/target_death2.wav", &spx->file_);
	NyaSound::ChangeVolume(&spx->file_, 40);
}

