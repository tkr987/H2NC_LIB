#include "TeemoMission4.h"
#include "TeemoTargetEx4.h"

TeemoMission4::TeemoMission4()
{
}


TeemoMission4::~TeemoMission4()
{
}

void TeemoMission4::Create(void)
{
	unsigned int id = 0;

	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddChild(1, 3600, new TeemoTargetEx4, id++);
}

void TeemoMission4::Delete(void)
{
	ClearBackground();
	ClearTarget();
	ClearUser();
}