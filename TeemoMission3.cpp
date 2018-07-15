#include "Target3Bacillus.h"
#include "Target3Bordetella.h"
#include "Target3Erwinia.h"
#include "Target3Kluyvera.h"
#include "Target3Pantoea.h"
#include "Target3Pseudomonad.h"
#include "Target3Shigella.h"
#include "Target3Vibrio.h"
#include "TeemoBack3.h"
#include "TeemoMission3.h"
#include "TeemoTargetEx3.h"
#include "UserAI.h"


void TeemoMission3::Create(void)
{
	unsigned int ctime = 0;

	//*****************************************************
	// スクロールする背景やBGMを子オブジェクトとして追加
	//*****************************************************
	AddBack(new TeemoBack3);

	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X - 210, 300));
	AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X - 70, 300));
	AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X + 70, 300));
	AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X + 210, 300));

	ctime = 3;
	// 左右移動target
	AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X - 100, -100));
	AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X      , -100));
	AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X + 100, -100));
	AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X - 300, -150));
	AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X - 200, -150));
	AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X + 200, -150));
	AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X + 300, -150));
	for (int i = 0; i < 10; i++)
	{
		ctime += 2;
		AddTarget(ctime, ctime + 50, new Target3Erwinia());
		AddTarget(ctime, ctime + 50, new Target3Erwinia());
	}

	ctime = 25;
	// 壁+全範囲攻撃target
	AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 - 200, -120));
	AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 - 100, -120));
	AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 + 100, -120));
	AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 + 200, -120));
	AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 - 250, -260));
	AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 - 150, -260));
	AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 + 150, -260));
	AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 + 250, -260));
	ctime++;
	AddTarget(ctime, ctime + 90, new Target3Pseudomonad(-200, 150, SCREEN_MAX_X / 2 - 360, 150, true));
	AddTarget(ctime, ctime + 90, new Target3Pseudomonad(-100, 150, SCREEN_MAX_X / 2 - 120, 150, true));
	AddTarget(ctime, ctime + 90, new Target3Pseudomonad(SCREEN_MAX_X + 100, 150, SCREEN_MAX_X / 2 + 120, 150, false));
	AddTarget(ctime, ctime + 90, new Target3Pseudomonad(SCREEN_MAX_X + 200, 150, SCREEN_MAX_X / 2 + 360, 150, false));

	// MID-BOSS + Uターン移動全範囲攻撃target
	ctime = 55;
	AddTarget(ctime, ctime + 50, new Target3Bordetella(SCREEN_CENTER_X, -100));
	AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X - 260, -100, SCREEN_CENTER_X - 260, 150));
	AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X - 180, -100, SCREEN_CENTER_X - 180, 120));
	AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X - 100, -100, SCREEN_CENTER_X - 100, 150));
	AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X + 100, -100, SCREEN_CENTER_X + 100, 150));
	AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X + 180, -100, SCREEN_CENTER_X + 180, 120));
	AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X + 260, -100, SCREEN_CENTER_X + 260, 150));


	//for (int i = 6; i < 16; i+=2)
	//{
	//	AddTarget(ctime + i, ctime + 25, new Target3Bacillus(SCREEN_MAX_X / 2 -200, -100, SCREEN_MAX_X / 2 -200, 200));
	//	AddTarget(ctime + i, ctime + 25, new Target3Bacillus(SCREEN_MAX_X / 2 -200, -100, SCREEN_MAX_X / 2 -200, 200));
	//	AddTarget(ctime + i, ctime + 25, new Target3Bacillus(SCREEN_MAX_X / 2 -100, -100, SCREEN_MAX_X / 2 -100, 200));
	//	AddTarget(ctime + i, ctime + 25, new Target3Bacillus(SCREEN_MAX_X / 2 -100, -100, SCREEN_MAX_X / 2 -100, 200));
	//	AddTarget(ctime + i, ctime + 25, new Target3Bacillus(SCREEN_MAX_X / 2,      -100, SCREEN_MAX_X / 2     , 200));
	//	AddTarget(ctime + i, ctime + 25, new Target3Bacillus(SCREEN_MAX_X / 2,      -100, SCREEN_MAX_X / 2     , 200));
	//	AddTarget(ctime + i, ctime + 25, new Target3Bacillus(SCREEN_MAX_X / 2 +100, -100, SCREEN_MAX_X / 2 +100, 200));
	//	AddTarget(ctime + i, ctime + 25, new Target3Bacillus(SCREEN_MAX_X / 2 +100, -100, SCREEN_MAX_X / 2 +100, 200));
	//	AddTarget(ctime + i, ctime + 25, new Target3Bacillus(SCREEN_MAX_X / 2 +200, -100, SCREEN_MAX_X / 2 +200, 200));
	//	AddTarget(ctime + i, ctime + 25, new Target3Bacillus(SCREEN_MAX_X / 2 +200, -100, SCREEN_MAX_X / 2 +200, 200));
	//}


	//for (int i = 0; i < 8; i++)
	//{
	//	AddTarget(4, 34, new Target3Kluyvera(-100 - (i * 100) + 40, 200, false));
	//	AddTarget(4, 34, new Target3Kluyvera(-100 - (i * 100), 200, false));
	//	AddTarget(4, 34, new Target3Kluyvera(SCREEN_MAX_X + 100 + (i * 100) + 40, 200, true));
	//	AddTarget(4, 34, new Target3Kluyvera(SCREEN_MAX_X + 100 + (i * 100), 200, true));
	//}



	//for (int i = 0; i < 10; i++)
	//{
	//	AddTarget(20, 50, new Target3Bacillus(SCREEN_MAX_X - 200, -100, SCREEN_MAX_X - 200, 200));
	//	AddTarget(20, 50, new Target3Bacillus(SCREEN_MAX_X - 300, -100, SCREEN_MAX_X - 300, 200));
	//	AddTarget(22, 52, new Target3Bacillus(SCREEN_MAX_X - 200, -100, SCREEN_MAX_X - 200, 200));
	//	AddTarget(22, 52, new Target3Bacillus(SCREEN_MAX_X - 300, -100, SCREEN_MAX_X - 300, 200));
	//	AddTarget(24, 54, new Target3Bacillus(SCREEN_MAX_X - 200, -100, SCREEN_MAX_X - 200, 200));
	//	AddTarget(24, 54, new Target3Bacillus(SCREEN_MAX_X - 300, -100, SCREEN_MAX_X - 300, 200));
	//}

	//AddTarget(28, 88, new Target3Pseudomonad(-100, 300, SCREEN_MAX_X / 2 - 100, 300, false));
	//AddTarget(28, 88, new Target3Pseudomonad(-200, 300, SCREEN_MAX_X / 2 - 300, 300, false));
	//AddTarget(28, 88, new Target3Pseudomonad(SCREEN_MAX_X + 100, 300, SCREEN_MAX_X / 2 + 100, 300, true));
	//AddTarget(28, 88, new Target3Pseudomonad(SCREEN_MAX_X + 200, 300, SCREEN_MAX_X / 2 + 300, 300, true));

	AddTarget(100, 600, new TeemoTargetEx3);

	//**************************************
	// ユーザーを子オブジェクトとして追加
	//**************************************
	AddUser(new UserAi);
}

void TeemoMission3::Delete(void)
{
	ClearBackground();
	ClearTarget();
	ClearUser();
}
