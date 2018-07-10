#include "TeemoBackgroundMission1.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx.h"
#include "UserAI.h"

using namespace HNLIB;

void TeemoMission1::Create(void) 
{
	unsigned int id = 0;
	InterfaceHandleSkill* ihandle_mission_skill;

	//*****************************************************
	// スクロールする背景やBGMを子オブジェクトとして追加
	//*****************************************************
	AddBackground(new TeemoBackgroundMission1);

	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddTarget(5, 600, new TargetExTeemo);

	//**************************************
	// ユーザーを子オブジェクトとして追加
	//**************************************
	AddUser(new UserAi);

	//******************
	// interface 設定
	//******************
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::Q)] = "Skill Q (power)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::W)] = "Passive W (bit)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::E)] = "Passive E (speed)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::R)] = "Skill R (ult)";
}

void TeemoMission1::Delete(void)
{
	// user以外は次のミッションに引き継がないので初期化しておく
	ClearBackground();
	ClearTarget();
}

