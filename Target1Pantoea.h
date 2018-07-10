#pragma once
#include "NyaTarget.h"

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
}

class Target1PantoeaDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target1PantoeaDevice();
	~Target1PantoeaDevice();
};

class Target1PantoeaMain
{
public:
	HNLIB::EffectPropertyX1* death1_epx_;
	HNLIB::GraphicPropertyX4* death1_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target1PantoeaMain();
	~Target1PantoeaMain();
};

class Target1Pantoea : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target1Pantoea();
	~Target1Pantoea();
private:
	Target1PantoeaMain main_;
	Target1PantoeaDevice device_;
};

