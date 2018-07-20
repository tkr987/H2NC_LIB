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

class Target2SpirochaetesDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target2SpirochaetesDevice();
	~Target2SpirochaetesDevice();
};

class Target2SpirochaetesMain
{
public:
	Target2SpirochaetesDevice device_;
	const unsigned int health_max_;
	TargetLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target2SpirochaetesMain();
	~Target2SpirochaetesMain();
};


class Target2Spirochaetes : public HNLIB::NyaTarget
{
public:
	Target2Spirochaetes(int x, int y);
	~Target2Spirochaetes();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	Target2SpirochaetesMain main_;
	unsigned int mode_;
	bool turn_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};

