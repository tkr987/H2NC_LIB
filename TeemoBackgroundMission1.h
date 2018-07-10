#pragma once

#include "NyaBackground.h"

namespace HNLIB
{
	class GraphicPropertyX1;
}

class TeemoBackgroundMission1 : public HNLIB::NyaBackground
{
public:
	TeemoBackgroundMission1();
	~TeemoBackgroundMission1();
	void MissionClear(void);
	void MissionContinue(void);
	void MissionRun(void);
private:
	HNLIB::GraphicPropertyX1* gp_;
	void Act(void);
	void Draw(void);
};

