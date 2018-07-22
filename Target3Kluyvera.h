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

class Target3KluyveraDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target3KluyveraDevice();
	~Target3KluyveraDevice();
};

class Target3KluyveraMain
{
public:
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoLock lock_;
	Target3KluyveraMain();
	~Target3KluyveraMain();
};

class Target3Kluyvera : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target3Kluyvera(int x, int y, bool turn);
	~Target3Kluyvera();
private:
	unsigned int count_frame_;
	Target3KluyveraDevice device_;
	Target3KluyveraMain main_;
	unsigned int mode_;
	bool turn_;
	void Act1(void);
	void Draw1(void);
};

