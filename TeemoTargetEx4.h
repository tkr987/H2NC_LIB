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

class TeemoEx4Cube1
{
public:
	H2NLIB::GraphicPropertyX4* gpx_;
	double move_angle_;
	H2NLIB::PositionHandle* phandle_;
	TeemoEx4Cube1();
	~TeemoEx4Cube1();
};

//*************************************
// Act2(), Draw2() で使うクラス
//*************************************
class TeemoExDevice421
{
public:
	H2NLIB::DevicePropertyX1* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice421();
	~TeemoExDevice421();
};

class TeemoExDevice422
{
public:
	H2NLIB::DevicePropertyX2* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice422();
	~TeemoExDevice422();
};

class TeemoExDevice423
{
public:
	H2NLIB::DevicePropertyX2* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice423();
	~TeemoExDevice423();
};

class TeemoExDevice424
{
public:
	H2NLIB::DevicePropertyX2* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice424();
	~TeemoExDevice424();
};

class TeemoExCube42
{
public:
	TeemoExDevice421 device21_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	TeemoExCube42();
	~TeemoExCube42();
};

//*************************************
// Act3(), Draw3() で使うクラス
//*************************************

class TeemoExDevice431
{
public:
	H2NLIB::DevicePropertyX2* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice431();
	~TeemoExDevice431();
};

class TeemoExDevice432
{
public:
	H2NLIB::DevicePropertyX1* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice432();
	~TeemoExDevice432();
};




class TeemoExCube43
{
public:
	double device_x_;
	double device_y_;
	TeemoExDevice432 device32_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	TeemoExCube43();
	~TeemoExCube43();
};



class TeemoEx4Main
{
public:
	const int health_max_;
	TeemoExDevice422 device22_;
	TeemoExDevice423 device23_;
	TeemoExDevice424 device24_;
	TeemoExDevice431 device31_;
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
	std::array<TeemoExCube42, 6> cube2_collection_;
	std::array<TeemoExCube43, 4> cube3_collection_;
	H2NLIB::SoundPropertyX* warning_spx_;
	void Act1(void);
	void Draw1(void);
	void Act2(void);
	void Draw2(void);
	void Act3(void);
	void Draw3(void);
	static double AngleToRad(double x) { return (x * 3.14159265359 / 180.0); }
};

