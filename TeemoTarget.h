#pragma once

#include "NyaTarget.h"


namespace H2NLIB {
	class NyaString;
	class DevicePropertyX1;
	class GraphicPropertyX4;
	class PositionHandle1;
}

struct TargetTeemoMain
{
public:
	H2NLIB::GraphicPropertyX4* gp_;
	H2NLIB::PositionHandle1* ph_;
	TargetTeemoMain();
	~TargetTeemoMain();
};


class TeemoTarget : public H2NLIB::NyaTarget {
public:
	void MissionClear(void);
	void MissionCreate(void);
	void MissionDelete(void);
	void MissionRun(void);
private:
	unsigned int count_frame_;
	TargetTeemoMain teemo_main_;
	void Act(void);
	void Draw(void);
};

