// 2018�N
//#if _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif

//#include <vld.h> 

#include "DxLib.h"
#include "NyaWindow.h"
#include "TeemoMission1.h"
#include "TeemoMission2.h"
#include "TeemoMission4.h"
#include "TeemoOpening.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//	���������[�N���o
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ������
	H2NLIB::NyaWindow* nya_window = new H2NLIB::NyaWindow("teemo on duty");

	// mission �ǉ�
	H2NLIB::NyaOpening* teemo_opening = new TeemoOpening;
	nya_window->AddChild(teemo_opening);
//	H2NLIB::NyaMission* teemo_mission1 = new TeemoMission1;
//	nya_window->AddChild(teemo_mission1);
//	H2NLIB::NyaMission* teemo_mission2 = new TeemoMission2;
//	nya_window->AddChild(teemo_mission2);
	H2NLIB::NyaMission* teemo_mission4 = new TeemoMission4;
	nya_window->AddChild(teemo_mission4);

	// ���s
	nya_window->Run();

	// �I��
	delete nya_window;

	return 0;
}

