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

class Target1TenericutesCubeDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target1TenericutesCubeDevice();
	~Target1TenericutesCubeDevice();
};


class Target1TenericutesMainDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target1TenericutesMainDevice();
	~Target1TenericutesMainDevice();
};

class Target1TenericutesCube
{
public:
	Target1TenericutesCubeDevice device_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target1TenericutesCube();
	~Target1TenericutesCube();
};

class Target1TenericutesMain
{
public:
	Target1TenericutesMainDevice device_;
	const unsigned int health_max_;
	TeemoLock* lock_;
	const unsigned int exp_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target1TenericutesMain();
	~Target1TenericutesMain();
};

class Target1Tenericutes : public HNLIB::NyaTarget
{
public:
	Target1Tenericutes(int x, int y);
	~Target1Tenericutes();
private:
	unsigned int count_frame_;
	std::array<Target1TenericutesCube, 2> cube_collection_;
	Target1TenericutesMain main_;
	unsigned int mode_;
	void Act(void);
	void Act1(void);
	void Draw(void);
	void Draw1(void);
};



