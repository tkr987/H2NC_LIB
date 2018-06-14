#pragma once

#include "NyaTarget.h"

namespace H2NLIB 
{
	class NyaDevice;
	class NyaSound;
	class NyaString;
	class DevicePropertyX1;
	class GraphicPropertyX4;
	class PositionHandle1;
}

class TargetExTeemoMain
{
public:
	H2NLIB::GraphicPropertyX4* gp_;
	H2NLIB::PositionHandle1* ph_;
	TargetExTeemoMain();
	~TargetExTeemoMain();
};

class TargetExTeemo : public H2NLIB::NyaTarget
{
public:
	TargetExTeemo();
	~TargetExTeemo();
	void MissionRun(void);
private:
	unsigned int count_frame_;
	TargetExTeemoMain main_;
	void Act(void);
	void Draw(void);
};

