#pragma once

#include "NyaTarget.h"
#include <array>

namespace H2NLIB 
{
	class DevicePropertyX1;
	class DevicePropertyX2;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
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

class TeemoExDevice42
{
public:
	H2NLIB::DevicePropertyX2* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice42();
	~TeemoExDevice42();
};

class TeemoExDevice421
{
public:
	H2NLIB::DevicePropertyX2* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice421();
	~TeemoExDevice421();
};

class TeemoEx4Cube1
{
public:
	H2NLIB::GraphicPropertyX4* gpx_;
	double move_angle_;
	H2NLIB::PositionHandle* phandle_;
	TeemoEx4Cube1();
	~TeemoEx4Cube1();
};

class TeemoExCube42
{
public:
	TeemoExDevice42 device2_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	TeemoExCube42();
	~TeemoExCube42();
};



class TeemoEx4Main
{
public:
	const int health_max_;
	TeemoExDevice421 device21_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
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
	std::array<TeemoExCube42, 4> cube2_collection_;
	H2NLIB::SoundPropertyX* warning_spx_;
	void Act1(void);
	void Draw1(void);
	void Act2(void);
	void Draw2(void);
	static double AngleToRad(double x) { return (x * 3.14159265359 / 180.0); }
};

