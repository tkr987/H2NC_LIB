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

void TeemoFactory::TargetAttackBlue1(DevicePropertyX1* dpx, GraphicPropertyX4* gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_BLUE1;
	NyaGraphic::Load("img/target/attack_blue1.png", &gpx->file_);
}

void TeemoFactory::TargetAttackBlue2(DevicePropertyX1 * dpx, GraphicPropertyX4 * gadget_gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_BLUE2;
	NyaGraphic::Load("img/target/attack_blue2.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackBlue3(DevicePropertyX1 * dpx, GraphicPropertyX4 * gadget_gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_BLUE3;
	NyaGraphic::Load("img/target/attack_blue3.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackBlue4(DevicePropertyX1 * dpx, GraphicPropertyX4 * gadget_gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_BLUE4;
	NyaGraphic::Load("img/target/attack_blue4.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackBlue7(DevicePropertyX1 * dpx, GraphicPropertyX4 * gadget_gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_BLUE7;
	NyaGraphic::Load("img/target/attack_blue7.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackGreen3(DevicePropertyX1* dpx, GraphicPropertyX4* gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_GREEN3;
	NyaGraphic::Load("img/target/attack_green3.png", &gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackGreen3(DevicePropertyX2* dpx, GraphicPropertyX4* gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_GREEN3;
	NyaGraphic::Load("img/target/attack_green3.png", &gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackGreen11(DevicePropertyX2* dpx, GraphicPropertyX4* gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_GREEN11;
	NyaGraphic::Load("img/target/attack_green11.png", &gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackGreen12(DevicePropertyX2* dpx, GraphicPropertyX4* gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_GREEN12;
	NyaGraphic::Load("img/target/attack_green12.png", &gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackGreen13(DevicePropertyX2* dpx, GraphicPropertyX4* gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_GREEN13;
	NyaGraphic::Load("img/target/attack_green13.png", &gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}


void TeemoFactory::TargetAttackOrange1(DevicePropertyX1 * dpx, GraphicPropertyX4 * gadget_gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_ORANGE1;
	NyaGraphic::Load("img/target/attack_orange1.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackOrange2(DevicePropertyX1 * dpx, GraphicPropertyX4 * gadget_gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_ORANGE2;
	NyaGraphic::Load("img/target/attack_orange2.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackOrange9(DevicePropertyX1 * dpx, GraphicPropertyX4 * gadget_gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_ORANGE9;
	NyaGraphic::Load("img/target/attack_orange9.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackOrange3(DevicePropertyX1* dpx, GraphicPropertyX4* gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_ORANGE3;
	NyaGraphic::Load("img/target/attack_orange3.png", &gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackRed2(DevicePropertyX1* dpx, GraphicPropertyX4* gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_RED2;
	NyaGraphic::Load("img/target/attack_red2.png", &gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackRed5(DevicePropertyX1* dpx, GraphicPropertyX4* gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_RED5;
	dpx->draw_angle_speed_deg_ = 2;
	NyaGraphic::Load("img/target/attack_red5.png", &gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackOrange5(DevicePropertyX1* dpx, GraphicPropertyX4* gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_ORANGE5;
	dpx->draw_angle_speed_deg_ = 2;
	NyaGraphic::Load("img/target/attack_orange5.png", &gpx->file_);
}

void TeemoFactory::TargetAttackPurple1(DevicePropertyX1* dpx, GraphicPropertyX4* gadget_gpx, EffectPropertyX1* epx, GraphicPropertyX4* effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_PURPLE1;
	NyaGraphic::Load("img/target/attack_purple1.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackPurple2(DevicePropertyX1* dpx, GraphicPropertyX4* gadget_gpx, EffectPropertyX1* epx, GraphicPropertyX4* effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_PURPLE2;
	NyaGraphic::Load("img/target/attack_purple2.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackPurple3(DevicePropertyX1* dpx, GraphicPropertyX4* gadget_gpx, EffectPropertyX1* epx, GraphicPropertyX4* effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_PURPLE3;
	NyaGraphic::Load("img/target/attack_purple3.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackWhite5(DevicePropertyX1* dpx, GraphicPropertyX4* gpx, EffectPropertyX1* epx, GraphicPropertyX4* effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_WHITE5;
	dpx->draw_angle_speed_deg_ = 2;
	NyaGraphic::Load("img/target/attack_white5.png", &gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackYellow1(DevicePropertyX1 * dpx, GraphicPropertyX4 * gadget_gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_YELLOW1;
	NyaGraphic::Load("img/target/attack_yellow1.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetAttackYellow2(DevicePropertyX1 * dpx, GraphicPropertyX4 * gadget_gpx, EffectPropertyX1 * epx, GraphicPropertyX4 * effect_gpx)
{
	dpx->collision_range_ = TARGET_ATTACK_RANGE_YELLOW2;
	NyaGraphic::Load("img/target/attack_yellow2.png", &gadget_gpx->file_);
	epx->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	NyaGraphic::Load("img/target/point.png", &effect_gpx->file_);
}

void TeemoFactory::TargetCube(GraphicPropertyX4* gpx)
{
	gpx->extend_rate_ = 0.4;
	NyaGraphic::Load(5, 1, "img/target/cube_orange.png", &gpx->file_);
}

void TeemoFactory::TargetCube(GraphicPropertyX4* gpx, PositionHandle* phandle)
{
	gpx->extend_rate_ = 0.4;
	NyaGraphic::Load(5, 1, "img/target/cube_orange.png", &gpx->file_);
	phandle->collision_range_ = TARGET_CUBE_RANGE;
}

void TeemoFactory::TargetCubeBlue(GraphicPropertyX4* gpx)
{
	gpx->extend_rate_ = 0.4;
	NyaGraphic::Load(5, 1, "img/target/cube_blue.png", &gpx->file_);
}

void TeemoFactory::TargetDeath1(EffectPropertyX1* epx, GraphicPropertyX4* gpx)
{
	epx->interval_time_frame_ = 3;
	NyaGraphic::Load(4, 2, "img/target/death1.png", &gpx->file_);
}

void TeemoFactory::TargetDeath2(EffectPropertyX1* epx, GraphicPropertyX4* gpx)
{
	epx->interval_time_frame_ = 3;
	gpx->extend_rate_ = 0.8;
	NyaGraphic::Load(8, 8, "img/target/death2.png", &gpx->file_);
}
