#include "TeemoMission3.h"
#include "TeemoTargetEx3b.h"


void TeemoMission3::Create(void)
{
	unsigned int id = 0;

	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddChild(5, 600, new TeemoTargetEx3b, id++);
}
