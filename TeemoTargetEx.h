#pragma once

#include "NyaTarget.h"

namespace HNLIB 
{
	class NyaDevice;
	class NyaSound;
	class NyaString;
	class DevicePropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
}

class TargetExTeemoMain
{
public:
	const unsigned int health_max_;
	HNLIB::GraphicPropertyX4* gp_;
	HNLIB::PositionHandle* ph_;
	TargetExTeemoMain();
	~TargetExTeemoMain();
};

class TargetExTeemo : public HNLIB::NyaTarget
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

