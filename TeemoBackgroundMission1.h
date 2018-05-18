#pragma once

#include "NyaBackground.h"

namespace H2NLIB
{
	class DeviceProperty1;
}

class TeemoBackgroundMission1 : public H2NLIB::NyaBackground
{
public:
	TeemoBackgroundMission1();
	~TeemoBackgroundMission1();
	void Act(void);
	void Draw(void);
private:
	H2NLIB::GraphicProperty1* gp_;
};

