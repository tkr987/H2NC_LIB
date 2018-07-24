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

class Target1ChlamydiaeCubeDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target1ChlamydiaeCubeDevice();
	~Target1ChlamydiaeCubeDevice();
};


class Target1ChlamydiaeMainDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target1ChlamydiaeMainDevice();
	~Target1ChlamydiaeMainDevice();
};

class Target1ChlamydiaeCube
{
public:
	Target1ChlamydiaeCubeDevice device_;
	TeemoLock* lock_;
	double move_angle_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target1ChlamydiaeCube();
	~Target1ChlamydiaeCube();
};

class Target1ChlamydiaeMain
{
public:
	Target1ChlamydiaeMainDevice device1_;
	Target1ChlamydiaeMainDevice device2_;
	const unsigned int health_max_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target1ChlamydiaeMain();
	~Target1ChlamydiaeMain();
};

class Target1Chlamydiae : public HNLIB::NyaTarget
{
public:
	Target1Chlamydiae(int x, int y);
	~Target1Chlamydiae();
private:
	unsigned int count_frame_;
	std::array<Target1ChlamydiaeCube, 4> cube_collection_;
	Target1ChlamydiaeMain main_;
	unsigned int mode_;
	void Act(void);
	void Act1(void);
	void Draw(void);
	void Draw1(void);
};


