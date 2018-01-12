#include "DxLib.h"
#include "DebugPrint.h"
#include "NyaDesign.h"
#include "NyaString.h"
#include "NyaWindow.h"

#define __DEBUG__
#define FPS_MAX 50


using namespace H2NLIB;


NyaWindow::NyaWindow()
{

}


NyaWindow::~NyaWindow()
{
	delete nya_design_;
	delete nya_string_;
	DxLib_End();
}

int NyaWindow::Init(void)
{
	//	メモリリーク検出
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// *****************
	//  dxlib初期化
	// *****************
	SetMainWindowText("H2NC++LIB v53");		// タイトル
	ChangeWindowMode(true);					// ウィンドウモード
	SetGraphMode(1280, 720, 32);			// 画面サイズ, 色数
	if (DxLib_Init() == -1)					// 初期化
		return -1;							//
	SetAlwaysRunFlag(true);					// 非アクティブ状態でも動作させる
	SetUseDivGraphFlag(false);				// グラフィック描画分割方法

	// インスタンス
	nya_design_ = new NyaDesign();
	nya_string_ = new NyaString();

	// 描画先グラフィック領域の指定
	SetDrawScreen(DX_SCREEN_BACK);
	return 0;
}


void NyaWindow::Run(void)
{
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1) {
		
		ClearDrawScreen();

		FpsUpdater();

		nya_design_->Run();
		nya_string_->Run();
		DebugPrint::Run();


		ScreenFlip();
	}

}


void NyaWindow::FpsUpdater(void)
{

	static	int frame_ave_ = 0;					//フレームレート平均
	static	int wtime_ave_ = 0;					//wait時間平均
	static	int ltime_ave_ = 0;					//loop時間平均
	static	int frame_[FPS_MAX] = {};			//フレームレート
	static	int ltime_[FPS_MAX] = {};			//loop時間
	static	int wtime_[FPS_MAX] = {};			//wait時間
	static	int prev_time_ = 0;					//1フレーム前の時間
	static	int frame_count_ = 0;				//現在のフレーム(0～49)
	static unsigned int all_frame_count_ = 0;	//フレーム数をカウントし続ける変数


#ifdef __DEBUG__
//	DebugPrint::SetData(615, 220, "frames_: %d", fpsall++);
	if (frame_ave_ != 0) {
		DebugPrint::SetData(1180, 660, "fps[%.1f]", 1000.0 / (double)frame_ave_);
		DebugPrint::SetData(1180, 680, "loop[%dms]", ltime_ave_);
		DebugPrint::SetData(1180, 700, "wait[%dms]", wtime_ave_);
	}
#else
	if (frame_ave_ != 0)
		DebugPrint::SetData(1200, 700, "fps[%.1f]", 1000.0 / (double)frame_ave_);
#endif


	frame_count_ = ++all_frame_count_ % FPS_MAX;
	/*平均算出*/
	if (frame_count_ == FPS_MAX - 1)
	{
		frame_ave_ = 0;
		ltime_ave_ = 0;
		wtime_ave_ = 0;
		for (int i = 0; i < FPS_MAX; i++)
		{
			frame_ave_ += frame_[i];
			ltime_ave_ += ltime_[i];
			wtime_ave_ += wtime_[i];
		}
		frame_ave_ = frame_ave_ / FPS_MAX;
		ltime_ave_ = ltime_ave_ / FPS_MAX;
		wtime_ave_ = wtime_ave_ / FPS_MAX;
	}

	ltime_[frame_count_] = GetNowCount() - prev_time_;
	/*wait処理*/
	wtime_[frame_count_] = (1000 / FPS_MAX) - ltime_[frame_count_];
	if (0 < wtime_[frame_count_])
		Sleep(wtime_[frame_count_]);
	frame_[frame_count_] = GetNowCount() - prev_time_;
	prev_time_ = GetNowCount();
}

