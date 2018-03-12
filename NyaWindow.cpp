#include <chrono>
#include <tuple>
#include "DxLib.h"
#include "DebugPrint.h"
#include "NyaDevice.h"
#include "NyaDesign.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaMission.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "NyaUser.h"
#include "NyaWindow.h"

#define __DEBUG__

using namespace std;
using namespace H2NLIB;


NyaWindow::NyaWindow()
{

}


NyaWindow::~NyaWindow()
{
	delete nya_design_;
	delete nya_device_;
	delete nya_effect_;
	delete nya_graphic_;
	delete nya_position_;

	if (nya_user_.first)
		delete nya_user_.second;


	for (vector<NyaMission*>::iterator it = nya_mission_vector_.begin(); it != nya_mission_vector_.end(); ++it)
		delete *it;

	DxLib_End();
}

/**
@brief ミッションを追加する関数
@param mission 追加するミッション
@note
 NyaWindowの子オブジェクトとしてミッションが追加される。
 子オブジェクトは親オブジェクト(NyaWindow)がdeleteされるときに自動的に削除される。
 なので、子オブジェクト自体はdeleteを書く必要はない。
**/
void NyaWindow::AddChMission(NyaMission* mission)
{
	nya_mission_vector_.push_back(mission);
}

/**
@brief ユーザーを追加する関数
@param mission 追加するユーザー
@note
 NyaWindowの子オブジェクトとしてユーザーが追加される。
 子オブジェクトは親オブジェクト(NyaWindow)がdeleteされるときに自動的に削除される。
 なので、子オブジェクト自体はdeleteを書く必要はない。
**/

void NyaWindow::AddChUser(NyaUser* user)
{
	nya_user_.first = true;
	nya_user_.second = user;
}


/**
@brief 初期化関数
@param name タイトルの設定
@note
 必ず最初に一度呼び出すこと。
**/
int NyaWindow::Init(string title)
{
	// *****************
	//  dxlib初期化
	// *****************
	SetMainWindowText("H2NC++LIB v60");		// タイトル
	ChangeWindowMode(true);					// ウィンドウモード
	SetGraphMode(1280, 720, 32);			// 画面サイズ, 色数
	if (DxLib_Init() == -1)					// 初期化
		return -1;							//
	SetAlwaysRunFlag(true);					// 非アクティブ状態でも動作させる
	SetUseDivGraphFlag(false);				// グラフィック描画分割方法
	SetDrawScreen(DX_SCREEN_BACK);			// 描画先グラフィック領域の指定

	// コンストラクタでDXLIB関数を利用する可能性があるので
	// DXLIB初期化後にインスタンスを生成する必要がある。
	nya_design_ = new NyaDesign;
	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;

	// 変数初期化
	title_name_ = title;
	nya_user_.first = false;
	
	// 設定
	NyaString::SettingFont("window_title_font", 30, 4);
	NyaString::SettingFont("debug_font", 10, 2);

	return 0;
}


void NyaWindow::Run(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);
	static std::chrono::system_clock::time_point debug_time_start, debug_time_end;
	static long long debug_time_msec;


	// 各プロセス処理
	// プロセスの変更はここでおこなう
	nya_design_->SetProcess(ePROCESS::TITLE);
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1) {

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
#endif

		ClearDrawScreen();

		switch (nya_design_->GetProcess()) 
		{
		case ePROCESS::TITLE:
			nya_mission_index_ = 0;
			RunTitle();
			if (NyaInput::IsPressKey(eINPUT::ENTER))
				nya_design_->SetProcess(ePROCESS::MISSION_LOAD);
			break;
		case ePROCESS::MISSION_LOAD:
			if (nya_mission_vector_.size() != 0)
			{ 
				nya_mission_vector_[nya_mission_index_]->Load();
				nya_mission_vector_[nya_mission_index_]->Run();
			}
			nya_design_->SetProcess(ePROCESS::MISSION_RUN);
			break;
		case ePROCESS::MISSION_RUN:
			if (nya_user_.first) 
			{
				nya_user_.second->Action();
				nya_user_.second->Draw();
			}
			if (nya_mission_vector_.size() != 0)
				nya_mission_vector_[nya_mission_index_]->Run();
			break;
		case ePROCESS::MISSION_STOP:
			if (nya_user_.first) 
				nya_user_.second->Draw();
			if (nya_mission_vector_.size() != 0)
				nya_mission_vector_[nya_mission_index_]->Run();
		break;
		case ePROCESS::CLEAR:
			nya_mission_index_++;
			break;
		case ePROCESS::CONTINUE:
			break;
		case ePROCESS::OVER:
			break;
		}

#ifdef __DEBUG__
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 620, "[600, 620] NyaWindow Process %d msec", (int)debug_time_msec);
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_device_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 640, "[600, 640] NyaDevice::Run() %d msec", (int)debug_time_msec);
#else 
		nya_device_->Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_effect_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 660, "[600, 660] NyaEffect::Run() %d msec", (int)debug_time_msec);
#else 
		nya_effect_->Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_graphic_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 680, "[600, 680] NyaGraphic::Run() %d msec", (int)debug_time_msec);
#else 
		nya_graphic_->Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_position_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 700, "[600, 700] NyaPosition::Run() %d msec", (int)debug_time_msec);
#else 
		nya_position_->Run();
#endif

		NyaInput::Run();
		nya_design_->Run();
		NyaString::Run();
	
		ScreenFlip();
	}

}

void NyaWindow::RunTitle(void)
{
	static tuple<int, int, int> white = make_tuple(255, 37, 37);

	NyaString::Write("window_title_font", white, 100, 70, "title [%s] start", title_name_);
	NyaString::Write("window_title_font", white, 50, 70, "=>");
}

