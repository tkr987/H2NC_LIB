#include "DxLib.h"
#include "DebugPrint.h"
#include "NyaAttack.h"
#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
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
	delete nya_attack_;
	delete nya_design_;
	delete nya_graphic_;
	delete nya_posision_;
	DxLib_End();
}

int NyaWindow::Init(void)
{
	//	メモリリーク検出
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// *****************
	//  dxlib初期化
	// *****************
	SetMainWindowText("H2NC++LIB v56");		// タイトル
	ChangeWindowMode(true);					// ウィンドウモード
	SetGraphMode(1280, 720, 32);			// 画面サイズ, 色数
	if (DxLib_Init() == -1)					// 初期化
		return -1;							//
	SetAlwaysRunFlag(true);					// 非アクティブ状態でも動作させる
	SetUseDivGraphFlag(false);				// グラフィック描画分割方法
	SetDrawScreen(DX_SCREEN_BACK);			// 描画先グラフィック領域の指定

	// コンストラクタでDXLIB関数を利用する可能性があるので
	// DXLIB初期化後にインスタンスを生成する必要がある。
	nya_attack_ = new NyaAttack;
	nya_design_ = new NyaDesign;
	nya_graphic_ = new NyaGraphic;
	nya_posision_ = new NyaPosition;

	// 変数初期化
	set_user_ = false;

	return 0;
}


void NyaWindow::Run(void)
{
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1) {
		
		ClearDrawScreen();

		nya_attack_->Run();
		nya_design_->Run();
		nya_graphic_->Run();
		nya_posision_->Run();
		if (set_user_) {
			nya_user_->Action();
			nya_user_->Draw();
		}

		NyaInput::Run();
		NyaString::Run();
		DebugPrint::Run();

		FpsUpdater();

		ScreenFlip();
	}

}

void NyaWindow::SetUser(NyaUser* user)
{
	nya_user_ = user;
	set_user_ = true;
}

/**
@param FPS更新関数
@note
**/
void NyaWindow::FpsUpdater(void)
{

	static	int frame_ave_ = 0;					//フレームレート平均
	static	int wtime_ave_ = 0;					//wait時間平均
	static	int ltime_ave_ = 0;					//loop時間平均
	static	int frame_[FPS_MAX] = {};			//フレームレート
	static	int ltime_[FPS_MAX] = {};			//loop時間
	static	int wtime_[FPS_MAX] = {};			//wait時間
	static	int prev_time_ = 0;					//1フレーム前の時間
	static	int frame_count_ = 0;				//現在のフレーム(0～FPS_MAX-1)
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

