#pragma once

#pragma once
#include "NyaTarget.h"

class TargetLock;

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class Target2ChloroflexiDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target2ChloroflexiDevice();
	~Target2ChloroflexiDevice();
};

class Target2ChloroflexiMain
{
public:
	Target2ChloroflexiDevice device_;
	const unsigned int health_max_;
	TargetLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target2ChloroflexiMain();
	~Target2ChloroflexiMain();
};


class Target2Chloroflexi : public HNLIB::NyaTarget
{
public:
	Target2Chloroflexi(int x, int y);
	~Target2Chloroflexi();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	Target2ChloroflexiMain main_;
	unsigned int mode_;
	bool turn_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};

