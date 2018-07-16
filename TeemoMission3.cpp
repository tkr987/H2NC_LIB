#include "Target3Bacillus.h"
#include "Target3Bordetella.h"
#include "Target3Erwinia.h"
#include "Target3Pantoea.h"
#include "Target3Pseudomonad.h"
#include "Target3Shigella.h"
#include "Target3Vibrio.h"
#include "TeemoBack3.h"
#include "TeemoMark3.h"
#include "TeemoMission3.h"
#include "UserAI.h"


void TeemoMission3::Create(void)
{
	unsigned int ctime = 0;

	//*****************************************************
	// スクロールする背景やBGMを子オブジェクトとして追加
	//*****************************************************
	AddBack(new TeemoBack3);

	AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X - 210, 300));
	AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X - 70, 300));
	AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X + 70, 300));
	AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X + 210, 300));

	ctime = 3;
	AddTarget(ctime, ctime + 300, new TeemoMark3);

	////*******************************************
	//// ターゲットを子オブジェクトとして追加
	////*******************************************
	//AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X - 210, 300));
	//AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X - 70, 300));
	//AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X + 70, 300));
	//AddTarget(ctime, ctime + 30, new Target3Pantoea(SCREEN_CENTER_X + 210, 300));

	//ctime = 3;
	//// 左右移動target
	//AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X - 100, -100));
	//AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X      , -100));
	//AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X + 100, -100));
	//AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X - 300, -150));
	//AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X - 200, -150));
	//AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X + 200, -150));
	//AddTarget(ctime, ctime + 50, new Target3Erwinia(SCREEN_CENTER_X + 300, -150));
	//for (int i = 0; i < 10; i++)
	//{
	//	ctime += 2;
	//	AddTarget(ctime, ctime + 50, new Target3Erwinia());
	//	AddTarget(ctime, ctime + 50, new Target3Erwinia());
	//}
	//// 下移動+自機狙い移動+自機狙い
	//ctime = 8;
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(100, -100, 100, 110));
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(150, -100, 150, 110));
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(200, -100, 200, 110));
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(250, -100, 250, 110));
	//ctime = 13;
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 250, -100, SCREEN_MAX_X - 250, 110));
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 200, -100, SCREEN_MAX_X - 200, 110));
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 150, -100, SCREEN_MAX_X - 150, 110));
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 100, -100, SCREEN_MAX_X - 100, 110));
	//ctime = 18;
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_CENTER_X - 100, -100, SCREEN_CENTER_X - 100, 110));
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_CENTER_X -  50, -100, SCREEN_CENTER_X -  50, 110));
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_CENTER_X +  50, -100, SCREEN_CENTER_X +  50, 110));
	//AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_CENTER_X + 100, -100, SCREEN_CENTER_X + 100, 110));
	//ctime = 25;
	//for (int i = 0; i < 5; i++)
	//{
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(100, -100, 100, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(150, -100, 150, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(200, -100, 200, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(250, -100, 250, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 250, -100, SCREEN_MAX_X - 250, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 200, -100, SCREEN_MAX_X - 200, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 150, -100, SCREEN_MAX_X - 150, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 100, -100, SCREEN_MAX_X - 100, 110));
	//	ctime++;
	//}

	//ctime = 38;
	//// 壁+全範囲攻撃target
	//AddTarget(ctime, ctime + 90, new Target3Pseudomonad(-200, 150, SCREEN_MAX_X / 2 - 360, 150, true));
	//AddTarget(ctime, ctime + 90, new Target3Pseudomonad(-100, 150, SCREEN_MAX_X / 2 - 120, 150, true));
	//AddTarget(ctime, ctime + 90, new Target3Pseudomonad(SCREEN_MAX_X + 100, 150, SCREEN_MAX_X / 2 + 120, 150, false));
	//AddTarget(ctime, ctime + 90, new Target3Pseudomonad(SCREEN_MAX_X + 200, 150, SCREEN_MAX_X / 2 + 360, 150, false));
	//AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 - 200, -100));
	//AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 - 100, -100));
	//AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 + 100, -100));
	//AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 + 200, -100));
	//AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 - 300, -240));
	//AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 - 200, -240));
	//AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 + 200, -240));
	//AddTarget(ctime, ctime + 90, new Target3Shigella(SCREEN_MAX_X / 2 + 300, -240));


	//ctime = 50;
	//for (int i = 0; i < 5; i++)
	//{
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(100, -100, 100, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(150, -100, 150, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(200, -100, 200, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(250, -100, 250, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 250, -100, SCREEN_MAX_X - 250, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 200, -100, SCREEN_MAX_X - 200, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 150, -100, SCREEN_MAX_X - 150, 110));
	//	AddTarget(ctime, ctime + 30, new Target3Bacillus(SCREEN_MAX_X - 100, -100, SCREEN_MAX_X - 100, 110));
	//	ctime++;
	//}

	//// MID-BOSS + Uターン移動全範囲攻撃target
	//ctime = 57;
	//AddTarget(ctime, ctime + 50, new Target3Bordetella(SCREEN_CENTER_X, -100));
	//AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X - 260, -100, SCREEN_CENTER_X - 260, 150));
	//AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X - 180, -100, SCREEN_CENTER_X - 180, 120));
	//AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X - 100, -100, SCREEN_CENTER_X - 100, 150));
	//AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X + 100, -100, SCREEN_CENTER_X + 100, 150));
	//AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X + 180, -100, SCREEN_CENTER_X + 180, 120));
	//AddTarget(ctime + 13, ctime + 50, new Target3Vibrio(SCREEN_CENTER_X + 260, -100, SCREEN_CENTER_X + 260, 150));

	//ctime = 79;
	//AddTarget(ctime, ctime + 300, new TeemoMark3);

	//**************************************
	// ユーザーを子オブジェクトとして追加
	//**************************************
	AddUser(new UserAi);
}

void TeemoMission3::Delete(void)
{
	ClearBackground();
	ClearTarget();
//	ClearUser();
}
