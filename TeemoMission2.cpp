#include "Target2Adeno.h"
#include "Target2Chloroflexi.h"
#include "Target2Ectromelia.h"
#include "Target2Pantoea.h"
#include "Target2Picorna.h"
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
	AddTarget(ctime, ctime + 30, new Target2Pantoea(SCREEN_CENTER_X - 210, 300));
	AddTarget(ctime, ctime + 30, new Target2Pantoea(SCREEN_CENTER_X - 70, 300));
	AddTarget(ctime, ctime + 30, new Target2Pantoea(SCREEN_CENTER_X + 70, 300));
	AddTarget(ctime, ctime + 30, new Target2Pantoea(SCREEN_CENTER_X + 210, 300));

	// 下攻撃+左右移動+360
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
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(520, -50));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(580, -50));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(560, -110));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(580, -240));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(640, -240));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(700, -240));
	ctime = 20;
	AddTarget(ctime, ctime + 60, new Target2Adeno(SCREEN_MAX_X - 150, -100));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(145, -85));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(200, -155));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(200, -210));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(200, -265));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(420, -380));
	for (int i = 0; i < 8; i++)
	{
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(-150 - 50 * i, SCREEN_MAX_Y - 150, false));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(-150 - 50 * i, SCREEN_MAX_Y - 250, false));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(-150 - 50 * i, SCREEN_MAX_Y - 350, false));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(-150 - 50 * i, SCREEN_MAX_Y - 450, false));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(-150 - 50 * i, SCREEN_MAX_Y - 550, false));
	}

	// MID-BOSS
	ctime = 44;
	AddTarget(ctime, ctime + 60, new Target2Picorna(SCREEN_CENTER_X, -100));

	ctime = 70;
	for (int i = 0; i < 30; i++)
	{
		AddTarget(ctime, ctime + 30, new Target2Ectromelia(SCREEN_CENTER_X - 300, SCREEN_MAX_Y + 150 + 50 * i));
		AddTarget(ctime, ctime + 30, new Target2Ectromelia(SCREEN_CENTER_X - 100, SCREEN_MAX_Y + 150 + 50 * i));
		AddTarget(ctime, ctime + 30, new Target2Ectromelia(SCREEN_CENTER_X + 100, SCREEN_MAX_Y + 150 + 50 * i));
		AddTarget(ctime, ctime + 30, new Target2Ectromelia(SCREEN_CENTER_X + 300, SCREEN_MAX_Y + 150 + 50 * i));
	}
	
	ctime = 100;
	AddTarget(ctime, ctime + 300, new TeemoTargetEx2);

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
