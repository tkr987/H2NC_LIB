#pragma once

#pragma once

#include "NyaTarget.h"

namespace H2NLIB 
{
	class NyaDevice;
	class NyaSound;
	class NyaString;
	class DeviceProperty1;
	class GraphicProperty4;
	class PositionHandle1;
}

class TargetExTeemo2Main
{
public:
	H2NLIB::GraphicProperty4* gp_;
	H2NLIB::PositionHandle1* ph_;
	TargetExTeemo2Main();
	~TargetExTeemo2Main();
};

class TargetExTeemo2 : public H2NLIB::NyaTarget
{
public:
	TargetExTeemo2();
	~TargetExTeemo2();
	void MissionRun(void);
private:
	unsigned int count_frame_;
	TargetExTeemo2Main main_;
	void Act(void);
	void Draw(void);
};

