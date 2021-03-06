#include "Target1Aquificae.h"
#include "Target1Chlamydiae.h"
#include "Target1Chlorobi.h"
#include "Target1Dictyoglomi.h"
#include "Target1Firmicutes.h"
#include "Target1Pantoea.h"
#include "Target1Tenericutes.h"
#include "TeemoBack1.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"
#include "TeemoMark1.h"
#include "UserAI.h"

using namespace HNLIB;

void TeemoMission1::Create(void) 
{
	unsigned int ctime = 0;

	//*****************************************************
	// スクロールする背景やBGMを子オブジェクトとして追加
	//*****************************************************
	AddBack(new TeemoBack1);

	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddTarget(ctime, ctime + 30, new Target1Pantoea(SCREEN_CENTER_X - 210, 300));
	AddTarget(ctime, ctime + 30, new Target1Pantoea(SCREEN_CENTER_X - 70, 300));
	AddTarget(ctime, ctime + 30, new Target1Pantoea(SCREEN_CENTER_X + 70, 300));
	AddTarget(ctime, ctime + 30, new Target1Pantoea(SCREEN_CENTER_X + 210, 300));

	// 下移動+自機狙い移動
	ctime = 5;
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X - 250, -200, SCREEN_CENTER_X - 200, 150));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X      , -200, SCREEN_CENTER_X      , 150));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X + 250, -200, SCREEN_CENTER_X + 200, 150));
	ctime = 8;
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X - 300, -200, SCREEN_CENTER_X - 300, 150));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X - 100, -200, SCREEN_CENTER_X - 100, 150));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X + 100, -200, SCREEN_CENTER_X + 100, 150));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X + 300, -200, SCREEN_CENTER_X + 300, 150));
	ctime = 11;
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X - 240, -200, SCREEN_CENTER_X - 240, 150));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X - 120, -200, SCREEN_CENTER_X - 120, 150));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X      , -200, SCREEN_CENTER_X      , 150));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X + 120, -200, SCREEN_CENTER_X + 120, 150));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X + 240, -200, SCREEN_CENTER_X + 240, 150));

	// angle move + user狙い, 横攻撃
	ctime = 15;
	AddTarget(ctime, ctime + 50, new Target1Tenericutes(SCREEN_MAX_X - 200, -200));
	AddTarget(ctime    , ctime + 50, new Target1Aquificae(100, -80));
	AddTarget(ctime + 3, ctime + 50, new Target1Aquificae(150, -80));
	AddTarget(ctime + 6, ctime + 50, new Target1Aquificae(200, -80));
	ctime = 25;
	AddTarget(ctime, ctime + 50, new Target1Tenericutes(SCREEN_CENTER_X, -200));
	AddTarget(ctime    , ctime + 50, new Target1Aquificae(SCREEN_MAX_X - 100, -80));
	AddTarget(ctime + 3, ctime + 50, new Target1Aquificae(SCREEN_MAX_X - 150, -80));
	AddTarget(ctime + 6, ctime + 50, new Target1Aquificae(SCREEN_MAX_X - 200, -80));
	ctime = 35;
	AddTarget(ctime, ctime + 50, new Target1Tenericutes(200, -200));
	AddTarget(ctime    , ctime + 50, new Target1Aquificae(SCREEN_CENTER_X - 90, -80));
	AddTarget(ctime + 3, ctime + 50, new Target1Aquificae(SCREEN_CENTER_X - 90, -80));
	AddTarget(ctime + 6, ctime + 50, new Target1Aquificae(SCREEN_CENTER_X - 90, -80));
	AddTarget(ctime    , ctime + 50, new Target1Aquificae(SCREEN_CENTER_X + 90, -120));
	AddTarget(ctime + 3, ctime + 50, new Target1Aquificae(SCREEN_CENTER_X + 90, -120));
	AddTarget(ctime + 6, ctime + 50, new Target1Aquificae(SCREEN_CENTER_X + 90, -120));

	ctime = 50;
	AddTarget(ctime + 1, ctime + 50, new Target1Chlamydiae(SCREEN_CENTER_X, -200));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(100, -80));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(150, -80));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(200, -80));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(SCREEN_MAX_X - 200, -80));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(SCREEN_MAX_X - 150, -80));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(SCREEN_MAX_X - 100, -80));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(100, -200));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(150, -200));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(200, -200));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(SCREEN_MAX_X - 200, -200));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(SCREEN_MAX_X - 150, -200));
	AddTarget(ctime, ctime + 50, new Target1Firmicutes(SCREEN_MAX_X - 100, -200));

	ctime = 67;
	for (int i = 0; i < 7; i++)
	{
		AddTarget(ctime    , ctime + 20, new Target1Chlorobi());
		AddTarget(ctime + 1, ctime + 20, new Target1Chlorobi());
		AddTarget(ctime + 2, ctime + 20, new Target1Chlorobi());
		AddTarget(ctime + 3, ctime + 20, new Target1Chlorobi());
		AddTarget(ctime + 4, ctime + 20, new Target1Chlorobi());
		AddTarget(ctime + 5, ctime + 20, new Target1Chlorobi());
		AddTarget(ctime + 6, ctime + 20, new Target1Chlorobi());
	}

	ctime = 78;
	AddTarget(ctime, ctime + 300, new TeemoMark1);


	//**************************************
	// ユーザーを子オブジェクトとして追加
	//**************************************
	AddUser(new UserAi);

	//******************
	// interface 設定
	//******************
	/*
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::Q)] = "Skill Q (power)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::W)] = "Passive W (bit)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::E)] = "Passive E (speed)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::R)] = "Skill R (ult)";
	*/
}

void TeemoMission1::Delete(void)
{
	// user 以外は次のミッションに引き継がないのでクリアしておく
	ClearBackground();
	ClearTarget();
}

