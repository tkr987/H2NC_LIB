#pragma once

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
class TeemoExDevice211
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice211();
	~TeemoExDevice211();
};

class TeemoExDevice212
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice212();
	~TeemoExDevice212();
};

class TeemoExCube21
{
public:
	TeemoExDevice212 device212_;
	int device_gap_angle_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoExCube21();
	~TeemoExCube21();
};


//********************************
// Act2(), Draw2() で使うクラス
//********************************

class TeemoExDevice221
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice221();
	~TeemoExDevice221();
};

class TeemoExDevice222
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice222();
	~TeemoExDevice222();
};

class TeemoExDevice223
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice223();
	~TeemoExDevice223();
};

class TeemoExCube22
{
public:
	TeemoExDevice222 device222_;
	TeemoExDevice222 device223_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoExCube22();
	~TeemoExCube22();
};

//********************************
// Act3(), Draw3() で使うクラス
//********************************

class TeemoExDevice232
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice232();
	~TeemoExDevice232();
};

class TeemoExCube23
{
public:
	TeemoExDevice232 device232_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoExCube23();
	~TeemoExCube23();
};

class TeemoExMain2
{
public:
	HNLIB::EffectPropertyX1* death1_epx_;
	HNLIB::GraphicPropertyX4* death1_gpx_;
	HNLIB::EffectPropertyX1* death2_epx_;
	HNLIB::GraphicPropertyX4* death2_gpx_;
	TeemoExDevice211 device211_;
	TeemoExDevice221 device221_;
	const unsigned int health_max_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoExMain2();
	~TeemoExMain2();
};

class TeemoTargetEx2 : public HNLIB::NyaTarget
{
public:
	TeemoTargetEx2();
	~TeemoTargetEx2();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	std::array<TeemoExCube21, 4> cube21_collection_;
	std::array<TeemoExCube22, 2> cube22_collection_;
	std::array<TeemoExCube23, 10> cube23_collection_;
	TeemoExMain2 main_;
	int mode_;
	void Act1(void);
	void Act2(void);
	void Act3(void);
	void Draw1(void);
	void Draw2(void);
	void Draw3(void);
	void Draw4(void);
};

