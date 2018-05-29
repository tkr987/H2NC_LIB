#pragma once

#include "NyaTarget.h"

namespace H2NLIB 
{
	class NyaDevice;
	class NyaPosition;
	class NyaSound;
	class NyaString;
	class DeviceProperty1;
	class GraphicProperty4;
	class PositionHandle1;
}

class TargetExTeemoMain
{
public:
	H2NLIB::GraphicProperty4* gp_;
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
	H2NLIB::NyaPosition* nya_position_;
	TargetExTeemoMain main_;
	void Act(void);
	void Draw(void);
};

