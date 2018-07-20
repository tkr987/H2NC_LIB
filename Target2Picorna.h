#pragma once
#include <array>
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

class Target2PicornaCubeDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target2PicornaCubeDevice();
	~Target2PicornaCubeDevice();
};

class Target2PicornaCube
{
public:
	Target2PicornaCubeDevice device_;
	TargetLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target2PicornaCube();
	~Target2PicornaCube();
};

class Target2PicornaDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target2PicornaDevice();
	~Target2PicornaDevice();
};

class Target2PicornaMain
{
public:
	Target2PicornaDevice device_;
	const unsigned int health_max_;
	TargetLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target2PicornaMain();
	~Target2PicornaMain();
};


class Target2Picorna : public HNLIB::NyaTarget
{
public:
	Target2Picorna(int x, int y);
	~Target2Picorna();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	std::array<Target2PicornaCube, 4> cube_collection_;
	Target2PicornaMain main_;
	unsigned int mode_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};

