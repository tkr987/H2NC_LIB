#pragma once
#include "NyaTarget.h"
#include <array>

class TeemoLock;

namespace HNLIB 
{
	class DevicePropertyX1;
	class DevicePropertyX2;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class TeemoExDevice411
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice411();
	~TeemoExDevice411();
};

class TeemoCube41
{
public:
	TeemoExDevice411 device411_;
	TeemoLock* lock_;
	double move_angle_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoCube41();
	~TeemoCube41();
};

//*************************************
// Act2(), Draw2() で使うクラス
//*************************************
class TeemoExDevice421
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice421();
	~TeemoExDevice421();
};

class TeemoExDevice422
{
public:
	HNLIB::DevicePropertyX2* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice422();
	~TeemoExDevice422();
};

class TeemoExDevice423
{
public:
	HNLIB::DevicePropertyX2* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice423();
	~TeemoExDevice423();
};

class TeemoExDevice424
{
public:
	HNLIB::DevicePropertyX2* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice424();
	~TeemoExDevice424();
};

class TeemoExCube42
{
public:
	TeemoExDevice421 device21_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoExCube42();
	~TeemoExCube42();
};

//*************************************
// Act3(), Draw3() で使うクラス
//*************************************

class TeemoExDevice431
{
public:
	HNLIB::DevicePropertyX2* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice431();
	~TeemoExDevice431();
};

class TeemoExDevice432
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice432();
	~TeemoExDevice432();
};




class TeemoExCube43
{
public:
	double device_x_;
	double device_y_;
	TeemoExDevice432 device32_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
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
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death1_epx_;
	HNLIB::GraphicPropertyX4* death1_gpx_;
	HNLIB::SoundPropertyX* death1_spx_;
	HNLIB::EffectPropertyX1* death2_epx_;
	HNLIB::GraphicPropertyX4* death2_gpx_;
	HNLIB::SoundPropertyX* death2_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoEx4Main();
	~TeemoEx4Main();
};

class TeemoEx : public HNLIB::NyaTarget
{
public:
	TeemoEx();
	~TeemoEx();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	std::array<TeemoCube41, 8> cube41_collection_;
	std::array<TeemoExCube42, 6> cube2_collection_;
	std::array<TeemoExCube43, 4> cube3_collection_;
	TeemoEx4Main main_;
	int mode_;
	HNLIB::SoundPropertyX* warning_spx_;
	void Act1(void);
	void Act2(void);
	void Act3(void);
	void Draw1(void);
	void Draw2(void);
	void Draw3(void);
	void Draw4(void);
	static double AngleToRad(double x) { return (x * 3.14159265359 / 180.0); }
};

