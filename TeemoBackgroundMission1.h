#pragma once

#include "NyaBackground.h"

namespace H2NLIB
{
	class GraphicPropertyX1;
}

class TeemoBackgroundMission1 : public H2NLIB::NyaBackground
{
public:
	TeemoBackgroundMission1();
	~TeemoBackgroundMission1();
	void MissionClear(void);
	void MissionContinue(void);
	void MissionRun(void);
private:
	H2NLIB::GraphicPropertyX1* gp_;
	void Act(void);
	void Draw(void);
};

