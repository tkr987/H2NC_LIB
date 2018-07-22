#pragma once

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class TeemoFactory
{
public:
	TeemoFactory();
	~TeemoFactory();
	static void TargetAttackBlue1(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx);
	static void TargetAttackBlue2(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gadget_gpx, HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* effect_gpx);
	static void TargetAttackBlue3(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gadget_gpx, HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* effect_gpx);
	static void TargetAttackBlue4(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gadget_gpx, HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* effect_gpx);
	static void TargetAttackBlue7(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gadget_gpx, HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* effect_gpx);
	static void TargetAttackOrange1(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gadget_gpx, HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* effect_gpx);
	static void TargetAttackOrange3(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx, HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* effect_gpx);
	static void TargetAttackOrange5(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx);
	static void TargetAttackOrange9(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gadget_gpx, HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* effect_gpx);
	static void TargetAttackPurple3(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gadget_gpx, HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* effect_gpx);
	static void TargetAttackRed5(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx, HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* effect_gpx);
	static void TargetAttackWhite5(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx);
	static void TargetCube(HNLIB::GraphicPropertyX4* gpx);
	static void TargetCubeBlue(HNLIB::GraphicPropertyX4* gpx);
	static void TargetDeath1(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx);
	static void TargetDeath1(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx, HNLIB::SoundPropertyX* spx);
	static void TargetDeath2(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx);
	static void TargetDeath2(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx, HNLIB::SoundPropertyX* spx);
};


