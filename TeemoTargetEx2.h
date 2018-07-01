#pragma once

#include "NyaTarget.h"

namespace H2NLIB 
{
	class DevicePropertyX1;
	class DevicePropertyX3;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
}

class TeemoExDevice211
{
public:
	H2NLIB::DevicePropertyX3* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice211();
	~TeemoExDevice211();
};

class TeemoExMain2
{
public:
	TeemoExDevice211 device211_;
	const unsigned int health_max_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	TeemoExMain2();
	~TeemoExMain2();
};

class TeemoTargetEx2 : public H2NLIB::NyaTarget
{
public:
	TeemoTargetEx2();
	~TeemoTargetEx2();
	void MissionRun(void);
private:
	unsigned int count_frame_;
	TeemoExMain2 main_;
	void Act1(void);
	void Draw1(void);
};

