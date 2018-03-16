

// 2018年
//#if _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif

#include <vld.h> 

#include "DxLib.h"
#include "NyaWindow.h"
#include "TeemoMission1.h"
#include "UserAI.h"

// H2NC++LIB: happy 2 nya c++ library - DXLIB STGLIB

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//	メモリリーク検出
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 初期化
	H2NLIB::NyaWindow* nya_window = new H2NLIB::NyaWindow;
	nya_window->Init("teemo on duty");

	// user 登録
	H2NLIB::NyaUser* teemo_user = new UserAI;
	nya_window->AddChUser(teemo_user);

	// mission 追加
	H2NLIB::NyaMission* teemo_mission1 = new TeemoMission1;
	nya_window->AddChMission(teemo_mission1);

	// 実行
	nya_window->Run();

	// 終了
	delete nya_window;


	return 0;
}














// 2017年

//#include "ArmsUpdater.h"
//#include "DebugPrint.h"
//#include "DefineNH.h"
//#include "DesignUpdater.h"
//#include "DxLib.h"
//#include "EffectUpdater.h"
//#include "FpsUpdater.h"
//#include "ImgUpdater.h"
//#include "KeyUpdater.h"
//#include "Map.h"
//#include "PosUpdater.h"
//#include "Result.h"
//#include "SoundUpdater.h"
//#include "Stage1.h"
//#include "StageContinue.h"
//#include "StageSound.h"
//#include "StageTarget.h"
//#include "Title.h"
//#include "Target3.h"
//#include "Target4.h"
//#include "User1.h"
//#include "User1b.h"

//int Title(int inst);
//void Target1(int inst, int lv);
//void Target2(int inst, int lv);
//void User1b(int isnt);
//int User2(int inst);


//using namespace NH2;
//using namespace NH3;


//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	//	メモリリーク検出
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//
//
//	// ***************************
//	//  managerクラスの初期化
//	// ***************************
//	ImgManager::Init();
//	SoundManager::Init();
//	// ********************************
//	//  managerクラスのデータクリア
//	// ********************************
//	ArmsManager::Clear();
//	DesignManager::Clear();
//	EffectManager::Clear();
//	KeyManager::Clear();
//	PosManager::Clear();
//	// **********************
//	//  updater class new
//	// **********************
//	ArmsUpdater *arms_updater = new ArmsUpdater();
//	DesignUpdater *design_updater = new DesignUpdater();
//	EffectUpdater *effect_updater = new EffectUpdater();
//	FpsUpdater *fps_updater = new FpsUpdater();
//	ImgUpdater *img_updater = new ImgUpdater();
//	KeyUpdater *key_updater = new KeyUpdater();
//	PosUpdater *pos_updater = new PosUpdater();
//	SoundUpdater *sound_updater = new SoundUpdater();
//	// **********************
//	//  stage, target, user
//	// **********************
////	Stage1 *stage1 = new Stage1();
//	StageContinue *stage_continue = new StageContinue();
//	StageSound *stage_sound = new StageSound();
//	stage_sound->MemoryInit();
//	StageTarget *stage_target = new StageTarget();
//	stage_target->MemoryInit();
//	Map *map = new Map();
//	map->MemoryInit();
//	Result *result = new Result();
//	result->Init();
//	Title *title = new Title();
//	title->Init();
//	Target3 *target3 = new Target3();
//	Target4 *target4 = new Target4();
//	User1 *user1 = new User1();
//	User1b *user1b = new User1b();
//
//	// *******************************************************
//	//  イベント分岐
//	//  ProcessMessage()...メッセージ処理
//	//  CheckHitKey(KEY_INPUT_ESCAPE)...ESCが押されると終了
//	// *******************************************************
//	SetDrawScreen(DX_SCREEN_BACK);
//	eGEVENT::TYPE gevent = eGEVENT::TITLE_RUN;
//	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1) {
//
//		ClearDrawScreen();
//
//		switch (gevent) {
//			// **************
//			//  Title Load
//			// **************
//		case eGEVENT::TITLE_RUN:
//			title->Run(&gevent);
//			break;
//			// ***************
//			//  stage1 hard
//			// ***************
//		case eGEVENT::TYPE::STAGE1_HARD_LOAD:
//			srand(10);
//			map->DataLoad(1);
//			user1b->Clear();
////			stage_continue->DataLoad();
////			stage_sound->DataLoad(gevent);
////			stage_target->DataLoad(gevent, 6400);
////			stage1->Load(LV_HARD, 10, 0);
//			gevent = eGEVENT::STAGE1_HARD_RUN;
//			break;
//		case eGEVENT::TYPE::STAGE1_HARD_RUN:
//			map->Ran();
//			user1b->Run();
////			stage1->Run(&gevent);
////			stage_sound->Run();
////			stage_continue->Run(&gevent);
////			stage_target->Run(&gevent);
//			break;
//		case eGEVENT::TYPE::STAGE1_GAME_OVER:
//			//
//			gevent = eGEVENT::TYPE::TITLE_RUN;
//			break;
//		case eGEVENT::TYPE::RESULT_LOAD_STAGE1:
//			result->Load(1);
//			gevent = eGEVENT::TYPE::RESULT_RUN_STAGE1;
//			break;
//		case eGEVENT::TYPE::RESULT_RUN_STAGE1:
//			result->Run(1);
//			break;
////			// ***************
////			//  STAGE2 HARD
////			// ***************
////		case eGEVENT::STAGE2_HARD_LOAD:
////			srand(20);
//////			Map1(INST_LOAD);
//////			Target2(INST_LOAD, LV_HARD);
//////			user1->Init();
////			gevent = eGEVENT::STAGE2_HARD_RUN;
////			break;
////		case eGEVENT::STAGE2_HARD_RUN:
//////			Map1(INST_RUN);
//////			Target2(INST_RUN, LV_HARD);
//////			user1->Run();
////			break;
//			// ***************
//			//  STAGE3 HARD
//			// ***************
//		case eGEVENT::TYPE::STAGE3_HARD_LOAD:
//			srand(10);
//			map->DataLoad(3);
//			target3->Init(LV_HARD);
//			user1->Clear();
//			gevent = eGEVENT::STAGE3_HARD_RUN;
////			gevent = eGEVENT::TYPE::RESULT_LOAD_STAGE3;
//			break;
//		case eGEVENT::TYPE::STAGE3_HARD_RUN:
//			map->Ran();
//			gevent = target3->Run();
//			user1->Run();
//			break;
//		case eGEVENT::TYPE::RESULT_LOAD_STAGE3:
//			user1->Run();
//			result->Load(3);
//			gevent = eGEVENT::TYPE::RESULT_RUN_STAGE3;
//			break;
//		case eGEVENT::TYPE::RESULT_RUN_STAGE3:
//			user1->Run();
//			result->Run(3);
//			break;
//		case eGEVENT::TYPE::STAGE4_HARD_LOAD:
//			srand(10);
//			map->DataLoad(4);
//			target4->Init(LV_HARD);
//			user1->Clear();
//			gevent = eGEVENT::STAGE4_HARD_RUN;
////			gevent = eGEVENT::TYPE::RESULT_LOAD_STAGE3;
//			break;
//		case eGEVENT::TYPE::STAGE4_HARD_RUN:
//			map->Ran();
//			gevent = target4->Run();
//			user1->Run();
//			break;
//		case eGEVENT::TYPE::RESULT_LOAD_STAGE4:
//			user1->Run();
//			result->Load(3);
//			gevent = eGEVENT::TYPE::RESULT_RUN_STAGE4;
//			break;
//		case eGEVENT::TYPE::RESULT_RUN_STAGE4:
//			user1->Run();
//			result->Run(3);
//			break;
//		case eGEVENT::TYPE::STAGE_GAME_OVER:
//			gevent = eGEVENT::TYPE::TITLE_RUN;
//			break;
//		}
//
//
//		design_updater->Run();
//		effect_updater->Run();
//		arms_updater->Run();
//		img_updater->Run();
//		key_updater->Run();
//		fps_updater->Run();
//		pos_updater->Run();
//		sound_updater->Run();
//		DebugPrint::Run();
//
//
//		ScreenFlip();
//	}


	//// *************
	////  終了処理
	//// *************
	//map->MemoryEnd();
	//title->End();
	//stage_sound->MemoryEnd();
	//stage_target->MemoryEnd();
	//// ***************************
	////  updater class delete
	//// ***************************
	//delete arms_updater;
	//delete design_updater;
	//delete effect_updater;
	//delete fps_updater;
	//delete img_updater;
	//delete key_updater;
	//delete pos_updater;
	//delete sound_updater;
	//// *************************
	////  stage, target, user
	//// *************************
	//delete stage_continue;
	//delete stage_sound;
	//delete stage_target;
	//// **********************
	////  manager class end
	//// **********************
	//ArmsManager::End();
	//EffectManager::End();
	//ImgManager::End();
	//PosManager::End();
	//SoundManager::End();

	//return 0;
//}
//

