#pragma once

#include "NyaBackground.h"

namespace H2NLIB
{
	class GraphicProperty1;
}

class TeemoBackgroundMission1 : public H2NLIB::NyaBackground
{
public:
	TeemoBackgroundMission1();
	~TeemoBackgroundMission1();
	void MissionRun(void);
	void MissionContinue(void);
private:
	H2NLIB::GraphicProperty1* gp_;
	void Act(void);
	void Draw(void);
};

