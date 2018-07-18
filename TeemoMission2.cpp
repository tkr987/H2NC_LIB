#include "Target2Adeno.h"
#include "Target2Polyoma.h"
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
	ctime = 3;
	AddTarget(ctime, ctime + 60, new Target2Adeno(150, -100));
	for (int i = 0; i < 8; i++)
	{
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(SCREEN_MAX_X + 150 + 50 * i, SCREEN_MAX_Y - 150, true));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(SCREEN_MAX_X + 150 + 50 * i, SCREEN_MAX_Y - 250, true));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(SCREEN_MAX_X + 150 + 50 * i, SCREEN_MAX_Y - 350, true));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(SCREEN_MAX_X + 150 + 50 * i, SCREEN_MAX_Y - 450, true));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(SCREEN_MAX_X + 150 + 50 * i, SCREEN_MAX_Y - 550, true));
	}




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
