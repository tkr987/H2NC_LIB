#include "Target2Adeno.h"
#include "TeemoBack2.h"
#include "TeemoMission2.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx2.h"
#include "UserAI.h"

using namespace HNLIB;


void TeemoMission2::Create(void)
{
	unsigned int ctime = 0;
	//*****************************************************
	// スクロールする背景やBGMを子オブジェクトとして追加
	//*****************************************************
	AddBack(new TeemoBack2);

	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddTarget(ctime, ctime + 60, new Target2Adeno(150, -100, 150, 70));
	AddTarget(100, 600, new TeemoTargetEx2);

	//**************************************
	// ユーザーを子オブジェクトとして追加
	//**************************************
	AddUser(new UserAi);
}

void TeemoMission2::Delete(void)
{
	ClearBackground();
	ClearTarget();
	ClearUser();
}
