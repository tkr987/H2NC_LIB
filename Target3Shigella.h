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

class Target3ShigellaDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target3ShigellaDevice();
	~Target3ShigellaDevice();
};

class Target3ShigellaMain
{
public:
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoLock lock_;
	Target3ShigellaMain();
	~Target3ShigellaMain();
};

class Target3Shigella : public HNLIB::NyaTarget
{
public:
	Target3Shigella(int x, int y);
	~Target3Shigella();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	Target3ShigellaDevice device_;
	Target3ShigellaMain main_;
	unsigned int mode_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};

