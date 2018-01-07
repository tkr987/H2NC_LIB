#include "DesignManager.h"
#include "DefineNH.h"
#include "PosManager.h"
#include "Target4.h"
#include "TargetBase.h"
#include "Boss4MDRTB.h"
#include "Target4Borna.h"
#include "Target4Denso.h"
#include "Target4Hepadna.h"
#include "Target4Retro.h"
#include "Target4Caulimo.h"

using namespace std;
using namespace NH2;
using namespace NH2T;

void Target4::End(void)
{
	for (multimap<long, TargetBase*>::iterator it = map_target_.begin(); it != map_target_.end(); ++it)
		delete it->second;
}

void Target4::Init(int lv)
{	
	int map_max_x, map_min_y;
	// 変数初期化
	frames_ = 0;
	phase_ = 0;
	
	PosManager::GetRelativeMapMaxX(&map_max_x);
	PosManager::GetRelativeMapMinY(&map_min_y);
	// target load
//	long cframes = 6500;
	long cframes = 100;
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Boss4MDRTB(-150, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target4Retro(map_max_x - 100, 300, 1.0, 180, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target4Caulimo(300, map_min_y - 200, 3.0, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target4Hepadna(300, map_min_y - 200, 3.0, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target4Borna(300, map_min_y - 200, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target4Denso(300, map_min_y + 50, lv)));
}

eGEVENT::TYPE Target4::Run(void) 
{
	int star;
	double boss_health;
	eGEVENT::TYPE return_type;

	DesignManager::GetStar(&star);
	if (star != -1)
		frames_++;

	// ********************************
	//  case 0: 通常
	//  case 1: ボス戦終了
	//  case 2: リザルト画面へ移行
	// ********************************
	switch (phase_) {
	case 0:
		for (multimap<long, TargetBase*>::iterator it = map_target_.begin(); it != map_target_.end(); ++it) {
			if (it->first < frames_)
				it->second->Run();
		}
		return_type = eGEVENT::TYPE::STAGE4_HARD_RUN;
		DesignManager::GetBossHealth(&boss_health);
		if (6500 < frames_ && boss_health <= 0.0) {
			phase_ = 1;
			frames_ = 0;
		}
		break;
	case 1:
		for (multimap<long, TargetBase*>::iterator it = map_target_.begin(); it != map_target_.end(); ++it)
			it->second->Run();
		if (frames_ == 400) {
			phase_ = 2;
			frames_ = 0;
		}
		return_type = eGEVENT::TYPE::STAGE4_HARD_RUN;
		break;
	case 2:
		return_type = eGEVENT::TYPE::RESULT_LOAD_STAGE4;
		break;
	default:
		break;
	}

	return return_type;
}

