#pragma once

#include <array>
#include "NyaTarget.h"

namespace H2NLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
}

//*************************************
// Act1(), Draw1() で使うクラス
//*************************************
class TeemoExDevice311
{
public:
	H2NLIB::DevicePropertyX1* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice311();
	~TeemoExDevice311();
};

class TeemoExCube31
{
public:
	TeemoExDevice311 device311_;
	H2NLIB::EffectPropertyX1* death_epx_;
	H2NLIB::GraphicPropertyX4* death_gpx_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	TeemoExCube31();
	~TeemoExCube31();
};

//*************************************
// Act2(), Draw2() で使うクラス
//*************************************
class TeemoExDevice321
{
public:
	H2NLIB::DevicePropertyX1* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice321();
	~TeemoExDevice321();
};

class TeemoExDevice322
{
public:
	H2NLIB::DevicePropertyX1* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice322();
	~TeemoExDevice322();
};

class TeemoExCube32
{
public:
	TeemoExDevice322 device322_;
	int device_gap_angle_;
	H2NLIB::EffectPropertyX1* death_epx_;
	H2NLIB::GraphicPropertyX4* death_gpx_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	TeemoExCube32();
	~TeemoExCube32();
};

class TeemoEx3Main
{
public:
	const int health_max_;
	TeemoExDevice311 device11_;
	TeemoExDevice321 device321_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	TeemoEx3Main();
	~TeemoEx3Main();
};



class TeemoTargetEx3 : public H2NLIB::NyaTarget
{
public:
	TeemoTargetEx3();
	~TeemoTargetEx3();
	void MissionRun(void);
private:
	int count_frame_;
	std::array<TeemoExCube31, 10> cube31_collection_;
	std::array<TeemoExCube32, 4> cube32_collection_;
	TeemoEx3Main main_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};

