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

class Target1FirmicutesMainDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target1FirmicutesMainDevice();
	~Target1FirmicutesMainDevice();
};

class Target1FirmicutesMain
{
public:
	TeemoLock* lock_;
	Target1FirmicutesMainDevice device_;
	const unsigned int exp_;
	const unsigned int health_max_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target1FirmicutesMain();
	~Target1FirmicutesMain();
};

class Target1Firmicutes : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target1Firmicutes(int x, int y);
	~Target1Firmicutes();
private:
	unsigned int count_frame_;
	Target1FirmicutesMain main_;
	unsigned int mode_;
	void Act1(void);
	void Draw1(void);
};

