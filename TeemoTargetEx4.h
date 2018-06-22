#pragma once

#include "NyaTarget.h"
#include <array>

namespace H2NLIB 
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle1;
	class SoundPropertyX;
}

class TeemoExBullet41
{
public:
	H2NLIB::DevicePropertyX1* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExBullet41();
	~TeemoExBullet41();
};

class TeemoEx4Cube1
{
public:
	H2NLIB::GraphicPropertyX4* gpx_;
	double move_angle_;
	H2NLIB::PositionHandle1* phandle_;
	TeemoEx4Cube1();
	~TeemoEx4Cube1();
};


class TeemoEx4Main
{
public:
	const int health_max_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle1* phandle_;
	TeemoEx4Main();
	~TeemoEx4Main();
};

class TeemoTargetEx4 : public H2NLIB::NyaTarget
{
public:
	TeemoTargetEx4();
	~TeemoTargetEx4();
	void MissionRun(void);
private:
	unsigned int count_frame_;
	TeemoExBullet41 bullet1_;
	TeemoEx4Main main_;
	std::array<TeemoEx4Cube1, 8> cube1_collection_;
	H2NLIB::SoundPropertyX* warning_spx_;
	void Act1(void);
	void Draw1(void);
	static double AngleToRad(double x) { return (x * 3.14159265359 / 180.0); }
};

