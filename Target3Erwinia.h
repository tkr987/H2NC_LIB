#pragma once


#pragma once
#include <array>
#include "NyaTarget.h"
#include "TeemoLock.h"

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}


class Target3ErwiniaDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target3ErwiniaDevice();
	~Target3ErwiniaDevice();
};

class Target3ErwiniaDeathDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target3ErwiniaDeathDevice();
	~Target3ErwiniaDeathDevice();
};

class Target3ErwiniaMain
{
public:
	unsigned int health_max_;
	Target3ErwiniaDevice device_;
	Target3ErwiniaDeathDevice device2_;
	TeemoLock lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target3ErwiniaMain();
	~Target3ErwiniaMain();
};


class Target3Erwinia : public HNLIB::NyaTarget
{
public:
	Target3Erwinia();
	Target3Erwinia(int x, int y);
	~Target3Erwinia();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	Target3ErwiniaMain main_;
	unsigned int mode_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};


