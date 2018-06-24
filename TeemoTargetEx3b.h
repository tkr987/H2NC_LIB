#pragma once

#include "NyaTarget.h"

namespace H2NLIB {
	class DevicePropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
}

class TeemoEx3bMain
{
public:
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
	void Act(void);
	void Draw(void);
};

