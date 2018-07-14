#pragma once
#include "NyaTarget.h"
#include "TargetLock.h"

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class Target3VibrioDeathDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target3VibrioDeathDevice();
	~Target3VibrioDeathDevice();
};

class Target3VibrioDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target3VibrioDevice();
	~Target3VibrioDevice();
};

class Target3VibrioMain
{
public:
	Target3VibrioDeathDevice device2_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TargetLock lock_;
	Target3VibrioMain();
	~Target3VibrioMain();
};

class Target3Vibrio : public HNLIB::NyaTarget
{
public:
	Target3Vibrio(int x, int y, int max_x, int max_y);
	~Target3Vibrio();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	Target3VibrioDevice device_;
	Target3VibrioMain main_;
	unsigned int mode_;
	int move_max_x_;
	int move_max_y_;
	void Act1(void);
	void Draw1(void);
};


