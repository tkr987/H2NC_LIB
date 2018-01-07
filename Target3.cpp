#include "DesignManager.h"
#include "DefineNH.h"
#include "Target3.h"
#include "TargetBase.h"
#include "Target3Arena.h"
#include "Target3Asfar.h"
#include "Target3Corona.h"
#include "Target3Bunya.h"
#include "Target3Filo.h"
#include "Target3Rhabdo.h"
#include "Boss3OXA48.h"

using namespace std;
using namespace NH2;
using namespace NH2T;

void Target3::End(void)
{
	for (multimap<long, TargetBase*>::iterator it = map_target_.begin(); it != map_target_.end(); ++it)
		delete it->second;
}

void Target3::Init(int lv)
{
	// 変数初期化
	frames_ = 0;
	phase_ = 0;

	// target load
//	long cframes = 6500;
	long cframes = 100;
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target3Asfar(100, 350, -10, 1, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target3Corona(250, 100, false, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target3Arena(300, -100, 5, 3 * 50, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target3Bunya(100, 0.001, 300, 100, 2, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target3Filo(250, 100, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Target3Rhabdo(450, 100, lv)));
//	map_target_.insert(pair<long, TargetBase*>(cframes, new Boss3OXA48(-150, lv)));
}

eGEVENT::TYPE Target3::Run(void) 
{
	int star;
	int boss_health;
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
		return_type = eGEVENT::TYPE::STAGE3_HARD_RUN;
		DesignManager::GetBossHealth(&boss_health);
		if (6500 < frames_ && boss_health == 0) {
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
		return_type = eGEVENT::TYPE::STAGE3_HARD_RUN;
		break;
	case 2:
		return_type = eGEVENT::TYPE::RESULT_LOAD_STAGE3;
		break;
	default:
		break;
	}

	return return_type;
}

