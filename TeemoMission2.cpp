#include "NyaInterface.h"
#include "TeemoBackgroundMission1.h"
#include "TeemoMission2.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx2.h"
#include "UserAI.h"

using namespace HNLIB;


void TeemoMission2::Create(void)
{
	//*****************************************************
	// スクロールする背景やBGMを子オブジェクトとして追加
	//*****************************************************
	AddBackground(new TeemoBackgroundMission1);

	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddTarget(1, 600, new TeemoTargetEx2);

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
