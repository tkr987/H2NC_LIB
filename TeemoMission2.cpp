#include "TeemoMission2.h"
#include "TeemoTarget.h"
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
	NyaTarget* teemo_target = new TeemoTarget;

	AddChTarget(1, 30, teemo_target);
	LoadBack("img/back3.png", -430, -2560 + 720, 2560 - 720, 180);

}
