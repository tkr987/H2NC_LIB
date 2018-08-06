// 2018年
//#if _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif

//#include <vld.h> 

#include "HNLIB.h"
#include "TeemoMission.h"
#include "TeemoMission1.h"
#include "TeemoMission2.h"
#include "TeemoMission3.h"
#include "TeemoMission4.h"
#include "TeemoOpening.h"
#include "TeemoEnding.h"

using namespace HNLIB;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//	メモリリーク検出
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 初期化
	NyaWindow* nya_window = new HNLIB::NyaWindow("teemo on duty");

	// mission 追加
	NyaOpening* teemo_opening = new TeemoOpening;
	nya_window->Child(teemo_opening);
//	HNLIB::NyaMission* teemo_mission = new TeemoMission;
//	nya_window->Child(teemo_mission);
//	NyaMission* teemo_mission1 = new TeemoMission1;
//	nya_window->Child(teemo_mission1);
//	HNLIB::NyaMission* teemo_mission2 = new TeemoMission2;
//	nya_window->Child(teemo_mission2);
	HNLIB::NyaMission* teemo_mission3 = new TeemoMission3;
	nya_window->Child(teemo_mission3);
	HNLIB::NyaMission* teemo_mission4 = new TeemoMission4;
	nya_window->Child(teemo_mission4);
	NyaEnding* teemo_ending = new TeemoEnding;
	nya_window->Child(teemo_ending);
	// 実行
	nya_window->Run();

	delete nya_window;
	return 0;
}

