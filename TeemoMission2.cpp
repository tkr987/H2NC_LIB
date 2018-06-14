#include "NyaInterface.h"
#include "TeemoBackgroundMission1.h"
#include "TeemoMission2.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx2.h"
#include "UserAI.h"

using namespace H2NLIB;


void TeemoMission2::Create(void)
{
	unsigned int id = 0;

	//*****************************************************
	// スクロールする背景やBGMを子オブジェクトとして追加
	//*****************************************************
	AddChild(new TeemoBackgroundMission1);

	//*******************************************
	// ターゲットを子オブジェクトとして追加
	//*******************************************
	AddChild(5, 600, new TargetExTeemo2, id++);

}

void TeemoMission2::Delete(void)
{
	ClearBackground();
	ClearTarget();
	ClearUser();
}
