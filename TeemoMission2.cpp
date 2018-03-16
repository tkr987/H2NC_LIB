#include "TeemoMission2.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx.h"
#include "NyaTarget.h"

using namespace H2NLIB;


TeemoMission2::TeemoMission2()
{

}


TeemoMission2::~TeemoMission2()
{

}

void TeemoMission2::Load(void)
{
	//NyaTarget* teemo_target = new TeemoTarget;
	NyaTarget* teemo_target_ex = new TeemoTargetEx;

	//AddChTarget(3, 180, teemo_target);
	AddChTarget(3, 180, teemo_target_ex);
	LoadBack("img/back3.png", -430, -2560 + 720, 2560 - 720, 180);

}
