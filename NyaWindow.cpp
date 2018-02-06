#include <chrono>
#include "DxLib.h"
#include "DebugPrint.h"
#include "NyaDevice.h"
#include "NyaDesign.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "NyaUser.h"
#include "NyaWindow.h"

#define __DEBUG__
#define FPS_MAX 60


using namespace H2NLIB;


NyaWindow::NyaWindow()
{

}


NyaWindow::~NyaWindow()
{
	delete nya_device_;
	delete nya_design_;
	delete nya_effect_;
	delete nya_graphic_;
	delete nya_posision_;
	DxLib_End();
}

int NyaWindow::Init(void)
{
	// *****************
	//  dxlib初期化
	// *****************
	SetMainWindowText("H2NC++LIB v59");		// タイトル
	ChangeWindowMode(true);					// ウィンドウモード
	SetGraphMode(1280, 720, 32);			// 画面サイズ, 色数
	if (DxLib_Init() == -1)					// 初期化
		return -1;							//
	SetAlwaysRunFlag(true);					// 非アクティブ状態でも動作させる
	SetUseDivGraphFlag(false);				// グラフィック描画分割方法
	SetDrawScreen(DX_SCREEN_BACK);			// 描画先グラフィック領域の指定

	// コンストラクタでDXLIB関数を利用する可能性があるので
	// DXLIB初期化後にインスタンスを生成する必要がある。
	nya_device_ = new NyaDevice;
	nya_design_ = new NyaDesign;
//	nya_effect_ = new NyaEffect;
	nya_graphic_ = new NyaGraphic;
	nya_posision_ = new NyaPosition;

	// 変数初期化
	set_user_ = false;
	set_target_ = false;
	
	// 設定
	NyaString::SettingFont("debug_window_font", 10, 2);


	return 0;
}


void NyaWindow::Run(void)
{
	int img = LoadGraph("img/teemo.png");
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	std::chrono::system_clock::time_point debug_time_start, debug_time_end;
	long long debug_time_msec;

	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1) {
		
		ClearDrawScreen();

		
		DrawGraph(100, 500, img, true);

//		nya_device_->Run();
//		nya_effect_->Run();

		debug_time_start = std::chrono::system_clock::now();
		nya_graphic_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_window_font", white, 600, 700, "[600, 700] NyaGraphic::Run() %d msec", (int)debug_time_msec);

		nya_posision_->Run();
		if (set_target_) {
			nya_target_->Action();
			nya_target_->Draw();
		}
//		if (set_user_) {
//			nya_user_->Action();
//			nya_user_->Draw();
//		}

		NyaInput::Run();
		nya_design_->Run();
		NyaString::Run();

		ScreenFlip();
	}

}

void NyaWindow::SetTarget(NyaTarget* target)
{
	nya_target_ = target;
	set_target_ = true;
}

void NyaWindow::SetUser(NyaUser* user)
{
	nya_user_ = user;
	set_user_ = true;
}

