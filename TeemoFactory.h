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
	static void TargetAttackOrange5(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx);
	static void TargetAttackWhite5(HNLIB::DevicePropertyX1* dpx, HNLIB::GraphicPropertyX4* gpx);
	static void TargetCube(HNLIB::GraphicPropertyX4* gpx);
	static void TargetDeath1(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx);
	static void TargetDeath1(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx, HNLIB::SoundPropertyX* spx);
	static void TargetDeath2(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx);
	static void TargetDeath2(HNLIB::EffectPropertyX1* epx, HNLIB::GraphicPropertyX4* gpx, HNLIB::SoundPropertyX* spx);
};


