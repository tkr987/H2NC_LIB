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

class TeemoDevice111
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice111();
	~TeemoDevice111();
};

class TeemoDevice121
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice121();
	~TeemoDevice121();
};


class TeemoCube11
{
public:
	TeemoDevice111 device111_;
	TeemoLock* lock_;
	double move_angle_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoCube11();
	~TeemoCube11();
};

class TeemoMain1
{
public:
	TeemoDevice121 device121_;
	const unsigned int exp_;
	const unsigned int health_max_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death1_epx_;
	HNLIB::GraphicPropertyX4* death1_gpx_;
	HNLIB::EffectPropertyX1* death2_epx_;
	HNLIB::GraphicPropertyX4* death2_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoMain1();
	~TeemoMain1();
};

class TeemoMark1 : public HNLIB::NyaTarget
{
public:
	TeemoMark1();
	~TeemoMark1();
private:
	unsigned int count_frame_;
	std::array<TeemoCube11, 2> cube11_collection_;
	TeemoMain1 main_;
	unsigned int mode_;
	HNLIB::SoundPropertyX* warning_spx_;
	void Act(void);
	void Act1(void);
	void Act2(void);
	void Draw(void);
	void Draw1(void);
	void Draw2(void);
	void Draw3(void);
};

