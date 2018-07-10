#include "Target3Kluyvera.h"
#include "Target3Pantoea.h"
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
	AddTarget(0, 60, new Target3Pantoea(SCREEN_MAX_X / 2 - 210, 350));
	AddTarget(0, 60, new Target3Pantoea(SCREEN_MAX_X / 2 - 70, 350));
	AddTarget(0, 60, new Target3Pantoea(SCREEN_MAX_X / 2 + 70, 350));
	AddTarget(0, 60, new Target3Pantoea(SCREEN_MAX_X / 2 + 210, 350));
	for (int i = 0; i < 8; i++)
	{
		AddTarget(2, 32, new Target3Kluyvera(-100 - (i * 100) + 40, 200, false));
		AddTarget(2, 32, new Target3Kluyvera(-100 - (i * 100), 200, false));
	}
	AddTarget(100, 600, new TeemoTargetEx3);

	//**************************************
	// ユーザーを子オブジェクトとして追加
	//**************************************
	AddUser(new UserAi);
}

void TeemoMission3::Delete(void)
{
	ClearTarget();
}
