#include "TeemoMission4.h"
#include "TeemoTargetEx4.h"
#include "UserAI.h"

TeemoMission4::TeemoMission4()
{
}


TeemoMission4::~TeemoMission4()
{
}

void TeemoMission4::Create(void)
{
	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddTarget(1, 3600, new TeemoTargetEx4);

	//**************************************
	// ユーザーを子オブジェクトとして追加
	//**************************************
	AddUser(new UserAi);
}

void TeemoMission4::Delete(void)
{
	ClearBackground();
	ClearTarget();
	ClearUser();
}