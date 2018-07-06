#include "TeemoBackgroundMission1.h"
#include "TeemoMission3.h"
#include "TeemoTargetEx3.h"
#include "UserAI.h"


void TeemoMission3::Create(void)
{
	//*****************************************************
	// スクロールする背景やBGMを子オブジェクトとして追加
	//*****************************************************
	AddBackground(new TeemoBackgroundMission1);

	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddTarget(1, 600, new TeemoTargetEx3);

	//**************************************
	// ユーザーを子オブジェクトとして追加
	//**************************************
	AddUser(new UserAi);
}

void TeemoMission3::Delete(void)
{
	ClearTarget();
}
