#pragma once
#include "NyaTarget.h"
#include "TeemoLock.h"

class TeemoLock;

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class Target1PantoeaDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target1PantoeaDevice();
	~Target1PantoeaDevice();
};

class Target1PantoeaMain
{
public:
	const unsigned int exp_;
	const unsigned int health_max_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target1PantoeaMain();
	~Target1PantoeaMain();
};


class Target1Pantoea : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target1Pantoea(int x, int y);
	~Target1Pantoea();
private:
	unsigned int count_frame_;
	Target1PantoeaDevice device_;
	Target1PantoeaMain main_;
	unsigned int mode_;
	void Act1(void);
	void Draw1(void);
};

