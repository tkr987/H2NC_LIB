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

class Target1AquificaeMainDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target1AquificaeMainDevice();
	~Target1AquificaeMainDevice();
};

class Target1AquificaeMain
{
public:
	TeemoLock* lock_;
	Target1AquificaeMainDevice device_;
	const unsigned int exp_;
	const unsigned int health_max_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target1AquificaeMain();
	~Target1AquificaeMain();
};

class Target1Aquificae : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target1Aquificae(int x, int y);
	~Target1Aquificae();
private:
	unsigned int count_frame_;
	Target1AquificaeMain main_;
	unsigned int mode_;
	void Act1(void);
	void Draw1(void);
};



