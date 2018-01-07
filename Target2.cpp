#include <map>
#include <stdlib.h>
#include "DxLib.h"
#include "DefineNH.h"
#include "DesignManager.h"
#include "FpsManager.h"
#include "TargetBase.h"
#include "Target1Anello.h"
#include "Target1Erythro.h"
#include "Target1Sipho.h"
#include "Target2Colti.h"
#include "Target2Seadma.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;
using namespace std;

/*!
@brief stage1関数
@param target_inst ターゲット読み込み(1)，ターゲット実行(2)
@param lv 難易度指定(0/1)
@note
 multimapに生成フレームとターゲットの組みを格納
 mapなので生成フレーム順に自動ソートされる
*/
void Target2(int target_inst, int lv)
{
	//int star;
	//multimap<long, TargetBase*>::iterator it;
	//static long frames;
	//static long cframes;
	//static multimap<long, TargetBase*> map_target;

	//if (target_inst == INST_LOAD) {
	//	// *********
	//	//  wave 1
	//	// *********
	//	frames = 0;
	//	cframes = 100;
	//	map_target.insert(pair<int, TargetBase*>(cframes, new Target2Seadma(400, 100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes, new Target2Colti(900, 100, 180, 4, lv)));
	//	// *********
	//	//  wave 2
	//	// *********
	//	cframes = 1900;
	//	map_target.insert(pair<int, TargetBase*>(cframes, new Target1Anello(400, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Anello(350, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Anello(450, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Anello(300, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Anello(500, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Anello(250, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Anello(550, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Anello(200, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Anello(600, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 500, new Target1Anello(150, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 500, new Target1Anello(650, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes, new Target1Anello(400, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Anello(350, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Anello(450, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Anello(300, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Anello(500, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Anello(250, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Anello(550, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Anello(200, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Anello(600, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 500, new Target1Anello(150, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 500, new Target1Anello(650, -140, lv)));
	//	cframes = 2400;
	//	map_target.insert(pair<int, TargetBase*>(cframes, new Target1Sipho(400, 50, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Sipho(300, 50, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Sipho(500, 50, lv)));
	//	cframes = 2600;
	//	map_target.insert(pair<int, TargetBase*>(cframes, new Target1Anello(400, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Anello(350, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Anello(450, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Anello(300, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Anello(500, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Anello(250, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Anello(550, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Anello(200, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Anello(600, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 500, new Target1Anello(150, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 500, new Target1Anello(650, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes, new Target1Anello(400, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Anello(350, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Anello(450, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Anello(300, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Anello(500, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Anello(250, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Anello(550, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Anello(200, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Anello(600, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 500, new Target1Anello(150, -140, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 500, new Target1Anello(650, -140, lv)));
	//	// *********
	//	//  wave 3
	//	// *********
	//	cframes = 2900;
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Polyoma(150, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Polyoma(200, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Polyoma(150, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Polyoma(200, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Polyoma(150, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Polyoma(200, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Polyoma(150, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Polyoma(200, -100, lv)));
	//	cframes = 3100;

	//	cframes = 3600;
	//	map_target.insert(pair<int, TargetBase*>(cframes, new Target1Erythro(500, 150, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Polyoma(475, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Polyoma(525, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Polyoma(475, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Polyoma(525, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Polyoma(475, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Polyoma(525, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Polyoma(475, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Polyoma(525, -100, lv)));
	//	cframes = 4200;
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Polyoma(375, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Polyoma(425, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Polyoma(375, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Polyoma(425, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Polyoma(375, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Polyoma(425, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Polyoma(375, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Polyoma(425, -100, lv)));
	//	cframes = 4800;
	//	map_target.insert(pair<int, TargetBase*>(cframes, new Target1Erythro(300, 150, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Polyoma(275, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Polyoma(325, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Polyoma(275, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Polyoma(325, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Polyoma(275, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Polyoma(325, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Polyoma(275, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Polyoma(325, -100, lv)));
	//	cframes = 5400;
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Polyoma(475, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 100, new Target1Polyoma(525, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Polyoma(475, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 200, new Target1Polyoma(525, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Polyoma(475, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 300, new Target1Polyoma(525, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Polyoma(475, -100, lv)));
	//	map_target.insert(pair<int, TargetBase*>(cframes + 400, new Target1Polyoma(525, -100, lv)));
	//	cframes = 5700;

	//	// *********
	//	//  wave 4
	//	// *********
	//	cframes = 6200;
	//	srand(6200);
	//	for (int i = 0; i < 40; i++) {
	//		map_target.insert(pair<int, TargetBase*>(cframes + 10 * i, new Target1Phycodna(100 + rand() % 600, -100 + rand() % 50, lv)));
	//	}
	//	// ********
	//	//  boss
	//	// ********
	//	cframes = 7000;
	//	map_target.insert(pair<int, TargetBase*>(cframes, new Target1MRAB(400, -100, lv)));
	//}

	//if (target_inst == INST_RUN) {
	//	DesignManager::GetStar(&star);
	//	if (star != -1)
	//		frames++;
	//	for (it = map_target.begin(); it != map_target.end(); ++it) {
	//		if (it->first < frames)
	//			it->second->Run();
	//	}
	//}
}

