#include "Target1Chlamydiae.h"
#include "Target1Dictyoglomi.h"
#include "Target1Pantoea.h"
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
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X - 250, -200, SCREEN_CENTER_X - 200, 200));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X      , -200, SCREEN_CENTER_X      , 200));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X + 250, -200, SCREEN_CENTER_X + 200, 200));
	ctime = 9;
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X - 300, -200, SCREEN_CENTER_X - 300, 200));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X - 100, -200, SCREEN_CENTER_X - 100, 200));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X + 100, -200, SCREEN_CENTER_X + 100, 200));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X + 300, -200, SCREEN_CENTER_X + 300, 200));
	ctime = 13;
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X - 240, -200, SCREEN_CENTER_X - 240, 200));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X - 120, -200, SCREEN_CENTER_X - 120, 200));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X      , -200, SCREEN_CENTER_X      , 200));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X + 120, -200, SCREEN_CENTER_X + 120, 200));
	AddTarget(ctime, ctime + 30, new Target1Dictyoglomi(SCREEN_CENTER_X + 240, -200, SCREEN_CENTER_X + 240, 200));


	ctime = 50;
	AddTarget(ctime, ctime + 60, new Target1Chlamydiae(SCREEN_CENTER_X, -200));

	ctime = 80;
	AddTarget(ctime, ctime + 600, new TeemoMark1);


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
	// user以外は次のミッションに引き継がないので初期化しておく
	ClearBackground();
	ClearTarget();
}

