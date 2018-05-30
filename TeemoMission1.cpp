#include "NyaInterface.h"
#include "NyaGraphic.h"
#include "TeemoBackgroundMission1.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx.h"
#include "UserAI.h"

using namespace H2NLIB;

void TeemoMission1::Create(void) 
{
	unsigned int id = 0;

	//*****************************************************
	// スクロールする背景やBGMを子オブジェクトとして追加
	//*****************************************************
	AddChild(new TeemoBackgroundMission1);

	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddChild(5, 600, new TargetExTeemo, id++);

	//**************************************
	// ユーザーを子オブジェクトとして追加
	//**************************************
	AddChild(new UserAI);

	//******************
	// interface 設定
	//******************
	NyaInterface::SetSkillName(eSKILL::Q, "Skill Q (power)");
	NyaInterface::SetSkillName(eSKILL::W, "Skill W (wave)");
	NyaInterface::SetSkillName(eSKILL::E, "Skill E (bit)");
	NyaInterface::SetSkillName(eSKILL::R, "Skill R (bomb)");
}

void TeemoMission1::Delete(void)
{
	DeleteBackground();
	DeleteTarget();
}

