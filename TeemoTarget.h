#pragma once

#include "NyaTarget.h"


namespace H2NLIB {
	class NyaDevice;
	class NyaPosition;
	class NyaString;
	class DeviceProperty1;
	class GraphicProperty4;
	class PositionHandle1;
}

struct TargetTeemoMain
{
public:
	H2NLIB::GraphicProperty4* gp_;
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
	H2NLIB::NyaDevice* nya_device_;
	H2NLIB::NyaPosition* nya_position_;
	TargetTeemoMain teemo_main_;
	void Act(void);
	void Draw(void);
};

