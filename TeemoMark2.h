#pragma once
#include <array>
#include "NyaTarget.h"

class TeemoLock;

namespace HNLIB 
{
	class DevicePropertyX1;
	class DevicePropertyX3;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

//*************************************
// Act1(), Draw1() で使うクラス
//*************************************
class TeemoDevice211
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice211();
	~TeemoDevice211();
};

class TeemoDevice212
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice212();
	~TeemoDevice212();
};

class TeemoCube21
{
public:
	TeemoDevice212 device212_;
	int device_gap_angle_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoCube21();
	~TeemoCube21();
};


//********************************
// Act2(), Draw2() で使うクラス
//********************************

class TeemoDevice221
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice221();
	~TeemoDevice221();
};

class TeemoDevice222
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice222();
	~TeemoDevice222();
};

class TeemoDevice223
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice223();
	~TeemoDevice223();
};

class TeemoCube22
{
public:
	TeemoDevice222 device222_;
	TeemoDevice222 device223_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoCube22();
	~TeemoCube22();
};

//********************************
// Act3(), Draw3() で使うクラス
//********************************

class TeemoDevice232
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice232();
	~TeemoDevice232();
};

class TeemoCube23
{
public:
	TeemoDevice232 device232_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoCube23();
	~TeemoCube23();
};

class TeemoMain2
{
public:
	TeemoDevice211 device211_;
	TeemoDevice221 device221_;
	const unsigned int health_max_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death1_epx_;
	HNLIB::GraphicPropertyX4* death1_gpx_;
	HNLIB::EffectPropertyX1* death2_epx_;
	HNLIB::GraphicPropertyX4* death2_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoMain2();
	~TeemoMain2();
};

class TeemoMark2 : public HNLIB::NyaTarget
{
public:
	TeemoMark2();
	~TeemoMark2();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	std::array<TeemoCube21, 4> cube21_collection_;
	std::array<TeemoCube22, 2> cube22_collection_;
	std::array<TeemoCube23, 10> cube23_collection_;
	TeemoMain2 main_;
	int mode_;
	HNLIB::SoundPropertyX* warning_spx_;
	void Act1(void);
	void Act2(void);
	void Act3(void);
	void Draw1(void);
	void Draw2(void);
	void Draw3(void);
	void Draw4(void);
};

