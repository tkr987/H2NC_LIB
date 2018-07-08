#pragma once
#include "NyaTarget.h"

namespace H2NLIB
{
	class DevicePropertyX1;
	class GraphicPropertyX4;
	class EffectPropertyX1;
}

class TeemoDevice
{
public:
	H2NLIB::DevicePropertyX1* dpx_;
	H2NLIB::GraphicPropertyX4* gpx_;
	TeemoDevice();
	~TeemoDevice();
};

class TeemoTargetMain
{
public:
	TeemoDevice device_;
	H2NLIB::GraphicPropertyX4* gpx_;
	TeemoTargetMain();
	~TeemoTargetMain();
};

class TeemoTarget : public H2NLIB::NyaTarget 
{
public:
	void Act(void);
	void Draw(void);
	TeemoTarget();
private:
	unsigned int count_frame_;
	TeemoTargetMain main_;
};

