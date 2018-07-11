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

class Target3BacillusDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target3BacillusDevice();
	~Target3BacillusDevice();
};

class Target3BacillusMain
{
public:
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TargetLock lock_;
	Target3BacillusMain();
	~Target3BacillusMain();
};

class Target3Bacillus : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target3Bacillus(int x, int y, int move_max_x, int move_max_y);
	~Target3Bacillus();
private:
	unsigned int count_frame_;
	Target3BacillusDevice device_;
	Target3BacillusMain main_;
	unsigned int mode_;
	double move_angle_;
	int move_max_x_;
	int move_max_y_;
	void Act1(void);
	void Draw1(void);
};
