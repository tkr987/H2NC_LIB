#include "DxLib.h"
#include "DebugPrint.h"
#include "DesignManager.h"
#include "DefineNH.h"
#include "PosManager.h"
#include "StageTarget.h"
#include "Boss1MRAB.h"
#include "TargetBase.h"
#include "Target1Anello.h"
#include "Target1Denso.h"
#include "Target1Erythro.h"
#include "Target1Picorna.h"
#include "Target1Sipho.h"
#include "Target1Virga.h"
#define __DEBUG__

using namespace std;
using namespace NH2;
using namespace NH2T;


void StageTarget::MemoryInit(void)
{

}


void StageTarget::MemoryEnd(void)
{

}


void StageTarget::DataDelete(void)
{
	for (multimap<long, TargetBase*>::iterator it = map_target_.begin(); it != map_target_.end(); ++it)
		delete it->second;
}


void StageTarget::DataLoad(eGEVENT::TYPE type, long start_frames)
{
	phase_ = 10;

	if (type == eGEVENT::TYPE::STAGE1_HARD_LOAD) {
		srand(10);
		CreateTarget1(LV_HARD);
	} else if (type == eGEVENT::TYPE::STAGE2_HARD_LOAD) {
		srand(20);
		CreateTarget2(LV_HARD);
	} else if (type == eGEVENT::TYPE::STAGE3_HARD_LOAD) {
		srand(30);
		CreateTarget3(LV_HARD);
	}
	frames_ = start_frames;
}


void StageTarget::CreateTarget1(int lv)
{
	long create_frames = 0;
	int map_center_x, map_center_y;
	int map_min_x, map_max_x;
	int map_min_y, map_max_y;

	PosManager::GetRelativeMapCenterX(&map_center_x);
	PosManager::GetRelativeMapCenterX(&map_center_y);
	PosManager::GetRelativeMapMinX(&map_min_x);
	PosManager::GetRelativeMapMaxX(&map_max_x);
	PosManager::GetRelativeMapMinY(&map_min_y);
	PosManager::GetRelativeMapMaxY(&map_max_y);


	// target load
	// *********
	//  wave 1
	// *********
	//create_frames = 50;
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -110, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -170, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -230, lv)));

	//create_frames = 300;
	//for (int n = 0; n < 10; n++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + n * 30 + rand() % 5, new Target1Denso(map_min_x + 50 + rand() % 250, 50 + rand() % 100, lv)));

	//create_frames = 550;
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -110, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -170, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -230, lv)));

	//create_frames = 800;
	//for (int n = 0; n < 10; n++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + n * 30 + rand() % 5, new Target1Denso(map_max_x - 50 - rand() % 250, 50 + rand() % 100, lv)));

	//create_frames = 1150;
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -150, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -250, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -150, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -250, lv)));

	//create_frames = 1300;
	//for (int n = 0; n < 10; n++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + n * 20 + rand() % 5, new Target1Denso(map_center_x - rand() % 250, 50 + rand() % 100, lv)));
	//for (int n = 0; n < 10; n++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + n * 20 + rand() % 5, new Target1Denso(map_center_x + rand() % 250, 50 + rand() % 100, lv)));

	//// *********
	////  wave 2
	//// *********
	//create_frames = 1900;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Anello(400, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(350, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(450, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(300, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(500, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(250, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(550, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(200, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(600, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(150, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(650, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Anello(400, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(350, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(450, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(300, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(500, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(250, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(550, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(200, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(600, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(150, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(650, -140, lv)));
	//create_frames = 2350;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Sipho(400, 50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Sipho(300, 50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Sipho(500, 50, lv)));
	//create_frames = 2600;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Anello(400, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(350, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(450, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(300, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(500, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(250, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(550, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(200, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(600, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(150, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(650, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Anello(400, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(350, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(450, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(300, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(500, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(250, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(550, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(200, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(600, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(150, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(650, -140, lv)));

	//// *********
	////  wave 3
	//// *********
	//create_frames = 3000;
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -110, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -170, lv)));
	//create_frames = 3200;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Erythro(map_max_x - 200, 80, lv)));

	//create_frames = 3400;
	//for (int n = 0; n < 10; n++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + n * 30 + rand() % 5, new Target1Denso(map_min_x + 50 + rand() % 250, 50 + rand() % 100, lv)));	
	//create_frames = 3600;
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -110, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -170, lv)));
	//create_frames = 3800;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Erythro(map_min_x + 200, 130, lv)));

	//create_frames = 4300;
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_min_x + 250, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_min_x + 250, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_min_x + 250,  50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_max_x - 250, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_max_x - 250, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_max_x - 250,  50, lv)));
	//create_frames = 4350;
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_min_x + 200, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_min_x + 200, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_min_x + 200,  50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_max_x - 200, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_max_x - 200, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_max_x - 200,  50, lv)));
	//create_frames = 4400;
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_min_x + 150, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_min_x + 150, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_min_x + 150,  50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_max_x - 150, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_max_x - 150, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_max_x - 150,  50, lv)));
	//create_frames = 4450;
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_min_x + 100, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_min_x + 100, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_min_x + 100,  50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_max_x - 100, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_max_x - 100, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_max_x - 100,  50, lv)));
	//create_frames = 4800;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Erythro(map_center_x, 180, lv)));

	//// *********
	////  wave 4
	//// *********
	//create_frames = 5600;
	//for (int i = 0; i < 40; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + 10 * i, new Target1Picorna(100 + rand() % 600, -100 + rand() % 50, lv)));

	// ********
	//  boss
	// ********
	create_frames = 6450;
	map_target_.insert(pair<int, TargetBase*>(create_frames, new Boss1MRAB(map_center_x, -100, lv)));
}


void StageTarget::CreateTarget2(int lv)
{

}


void StageTarget::CreateTarget3(int lv)
{

}



void StageTarget::Run(eGEVENT::TYPE *type) 
{
	int user_star;

	DesignManager::GetStar(&user_star);
	// ********************************
	//  case 10: 通常
	//  case 11: コンテニュー表示
	//  case 12: ボス戦終了
	//  case 13: リザルト画面へ移行
	// ********************************
	switch (phase_) {
	case 10:
		for (multimap<long, TargetBase*>::iterator it = map_target_.begin(); it != map_target_.end(); ++it) {
			if (it->first < frames_) {
				it->second->Action();
				it->second->Draw();
			}
		}
		if (user_star == -1)
			phase_ = 11;
		break;
	case 11:
		for (multimap<long, TargetBase*>::iterator it = map_target_.begin(); it != map_target_.end(); ++it) {
			if (it->first < frames_)
				it->second->Draw();
		}
		if (user_star != -1)
			phase_ = 10;
		break;
	default:
		break;
	}

	if (user_star != -1)
		frames_++;

#ifdef __DEBUG__
	int color = GetColor(255, 255, 255);
	DebugPrint::SetData(10, 190, "frame = %ld", frames_);
#endif
}

