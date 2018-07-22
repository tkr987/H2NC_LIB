#pragma once
#include <array>
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

class Target3BordetellaCubeDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target3BordetellaCubeDevice();
	~Target3BordetellaCubeDevice();
};

class Target3BordetellaCube
{
public:
	Target3BordetellaCubeDevice device_;
	TeemoLock lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target3BordetellaCube();
	~Target3BordetellaCube();
};

class Target3BordetellaDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target3BordetellaDevice();
	~Target3BordetellaDevice();
};

class Target3BordetellaMain
{
public:
	unsigned int health_max_;
	Target3BordetellaDevice device_;
	TeemoLock lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target3BordetellaMain();
	~Target3BordetellaMain();
};


class Target3Bordetella : public HNLIB::NyaTarget
{
public:
	Target3Bordetella(int x, int y);
	~Target3Bordetella();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	std::array<Target3BordetellaCube, 2> cube_collection_;
	Target3BordetellaMain main_;
	unsigned int mode_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};

