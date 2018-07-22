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

class Target3PantoeaDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target3PantoeaDevice();
	~Target3PantoeaDevice();
};

class Target3PantoeaMain
{
public:
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoLock lock_;
	Target3PantoeaMain();
	~Target3PantoeaMain();
};


class Target3Pantoea : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target3Pantoea(int x, int y);
	~Target3Pantoea();
private:
	unsigned int count_frame_;
	Target3PantoeaDevice device_;
	Target3PantoeaMain main_;
	unsigned int mode_;
	void Act1(void);
	void Draw1(void);
};

