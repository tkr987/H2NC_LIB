#pragma once

#include "NyaTarget.h"

namespace H2NLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
}

//*************************************
// Act1(), Draw1() ‚ÅŽg‚¤ƒNƒ‰ƒX
//*************************************
class TeemoExDevice311
{
public:
	H2NLIB::DevicePropertyX1* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice311();
	~TeemoExDevice311();
};

class TeemoEx3bMain
{
public:
	TeemoExDevice311 device11_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	TeemoEx3bMain();
	~TeemoEx3bMain();
};



class TeemoTargetEx3b : public H2NLIB::NyaTarget
{
public:
	TeemoTargetEx3b();
	~TeemoTargetEx3b();
	void MissionRun(void);
private:
	int count_frame_;
	TeemoEx3bMain main_;
	void Act1(void);
	void Draw1(void);
};

