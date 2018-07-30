#pragma once
#include "NyaTarget.h"

class TeemoLock;

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class Target1ChlorobiMainDeathDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target1ChlorobiMainDeathDevice();
	~Target1ChlorobiMainDeathDevice();
};

class Target1ChlorobiMain
{
public:
	TeemoLock* lock_;
	Target1ChlorobiMainDeathDevice device_death_;
	const unsigned int exp_;
	const unsigned int health_max_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target1ChlorobiMain();
	~Target1ChlorobiMain();
};

class Target1Chlorobi : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target1Chlorobi();
	~Target1Chlorobi();
private:
	unsigned int count_frame_;
	Target1ChlorobiMain main_;
	unsigned int mode_;
	void Act1(void);
	void Draw1(void);
};

