#pragma once
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

class Target2PantoeaDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target2PantoeaDevice();
	~Target2PantoeaDevice();
};

class Target2PantoeaMain
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
	Target2PantoeaMain();
	~Target2PantoeaMain();
};


class Target2Pantoea : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target2Pantoea(int x, int y);
	~Target2Pantoea();
private:
	unsigned int count_frame_;
	Target2PantoeaDevice device_;
	Target2PantoeaMain main_;
	unsigned int mode_;
	void Act1(void);
	void Draw1(void);
};



