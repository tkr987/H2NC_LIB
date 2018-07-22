#pragma once
#include <array>
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

class Target2AdenoCubeDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target2AdenoCubeDevice();
	~Target2AdenoCubeDevice();
};

class Target2AdenoCube
{
public:
	Target2AdenoCubeDevice device_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target2AdenoCube();
	~Target2AdenoCube();
};

class Target2AdenoDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target2AdenoDevice();
	~Target2AdenoDevice();
};

class Target2AdenoMain
{
public:
	Target2AdenoDevice device_;
	unsigned int health_max_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target2AdenoMain();
	~Target2AdenoMain();
};


class Target2Adeno : public HNLIB::NyaTarget
{
public:
	Target2Adeno(int x, int y);
	~Target2Adeno();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	std::array<Target2AdenoCube, 2> cube_collection_;
	Target2AdenoMain main_;
	unsigned int mode_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};


