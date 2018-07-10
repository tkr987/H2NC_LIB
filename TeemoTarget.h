#pragma once
#include "NyaTarget.h"

namespace HNLIB
{
	class DevicePropertyX1;
	class GraphicPropertyX4;
	class EffectPropertyX1;
}

class TeemoDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	TeemoDevice();
	~TeemoDevice();
};

class TeemoTargetMain
{
public:
	TeemoDevice device_;
	HNLIB::GraphicPropertyX4* gpx_;
	TeemoTargetMain();
	~TeemoTargetMain();
};

class TeemoTarget : public HNLIB::NyaTarget 
{
public:
	void Act(void);
	void Draw(void);
	TeemoTarget();
private:
	unsigned int count_frame_;
	TeemoTargetMain main_;
};

