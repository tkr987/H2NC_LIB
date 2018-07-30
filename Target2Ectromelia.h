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

class Target2EctromeliaDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target2EctromeliaDevice();
	~Target2EctromeliaDevice();
};

class Target2EctromeliaMain
{
public:
	Target2EctromeliaDevice device_;
	const unsigned int health_max_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target2EctromeliaMain();
	~Target2EctromeliaMain();
};


class Target2Ectromelia : public HNLIB::NyaTarget
{
public:
	Target2Ectromelia(int x, int y);
	~Target2Ectromelia();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	Target2EctromeliaMain main_;
	unsigned int mode_;
	bool turn_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};

