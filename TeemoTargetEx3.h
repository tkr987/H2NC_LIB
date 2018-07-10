#pragma once

#include <array>
#include "NyaTarget.h"

namespace HNLIB
{
	class DevicePropertyX1;
	class DevicePropertyX3;
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
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice311();
	~TeemoExDevice311();
};

class TeemoExCube31
{
public:
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoExCube31();
	~TeemoExCube31();
};

//*************************************
// Act2(), Draw2() で使うクラス
//*************************************
class TeemoExDevice321
{
public:
	HNLIB::DevicePropertyX3* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice321();
	~TeemoExDevice321();
};

class TeemoExDevice322
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice322();
	~TeemoExDevice322();
};

class TeemoExCube32
{
public:
	TeemoExDevice322 device322_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoExCube32();
	~TeemoExCube32();
};


//*************************************
// Act3(), Draw3() で使うクラス
//*************************************
class TeemoExDevice331
{
public:
	double way1_angle_;
	double way2_angle_;
	double way3_angle_;
	double way4_angle_;
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice331();
	~TeemoExDevice331();
};

class TeemoExDevice332
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice332();
	~TeemoExDevice332();
};


class TeemoExCube33
{
public:
	TeemoExDevice332 device332_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoExCube33();
	~TeemoExCube33();
};

class TeemoEx3Main
{
public:
	HNLIB::EffectPropertyX1* death1_epx_;
	HNLIB::GraphicPropertyX4* death1_gpx_;
	HNLIB::EffectPropertyX1* death2_epx_;
	HNLIB::GraphicPropertyX4* death2_gpx_;
	TeemoExDevice311 device311_;
	TeemoExDevice321 device321_;
	TeemoExDevice331 device331_;
	HNLIB::GraphicPropertyX4* gpx_;
	const int health_max_;
	HNLIB::PositionHandle* phandle_;
	TeemoEx3Main();
	~TeemoEx3Main();
};



class TeemoTargetEx3 : public HNLIB::NyaTarget
{
public:
	TeemoTargetEx3();
	~TeemoTargetEx3();
	void Act(void);
	void Draw(void);
private:
	int count_frame_;
	std::array<TeemoExCube31, 100> cube31_collection_;
	std::array<TeemoExCube32, 6> cube32_collection_;
	std::array<TeemoExCube33, 4> cube33_collection_;
	TeemoEx3Main main_;
	int mode_;
	void Act1(void);
	void Act2(void);
	void Act3(void);
	void Draw1(void);
	void Draw2(void);
	void Draw3(void);
	void Draw4(void);
};

