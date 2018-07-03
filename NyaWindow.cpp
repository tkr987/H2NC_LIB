#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <tuple>
#include "DxLib.h"
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaEnding.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaInterface.h"
#include "NyaMission.h"
#include "NyaOpening.h"
#include "NyaPosition.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "NyaUser.h"
#include "NyaWindow.h"

#define __DEBUG__

using namespace std;
using namespace std::experimental::filesystem;
using namespace H2NLIB;


WindowChild::WindowChild()
{
	mission_index_ = 0;
	ending_ = nullptr;
	opening_ = nullptr;
}

NyaWindow::NyaWindow(string title)
{
	InterfaceHandleTitle* ihandle_title;

	//******************
	// DXLIB初期化
	//******************
	SetMainWindowText("happy 2 nya C++ DXLIB STG wrapper v73");		// タイトル
	ChangeWindowMode(true);											// ウィンドウモード
	SetGraphMode(1280, 720, 32);									// 画面サイズ, 色数
	DxLib_Init();													// 初期化
	SetAlwaysRunFlag(true);											// 非アクティブ状態でも動作させる
	SetUseDivGraphFlag(false);										// グラフィック描画分割方法
	SetDrawScreen(DX_SCREEN_BACK);									// 描画先グラフィック領域の指定

	// ディレクトリ作成
	create_directory("replay");

	// 各クラス内でDXLIB関数を利用する可能性があるので
	// DXLIB初期化後にInit()を呼び出す必要がある。
	NyaInterface::Init();
	ihandle_title = NyaInterface::GetHandleTitle();
	ihandle_title->name_ = title;
	
	// フォント設定
	NyaString::SettingFont("fps_font", 14, 2);
	NyaString::SettingFont("window_title_font", 30, 4);
	NyaString::SettingFont("debug_font", 10, 2);

	// メンバ変数の初期化
	event_ = eEVENT::TITLE;
	event_next_ = eEVENT::enum_zero;
}


NyaWindow::~NyaWindow(void)
{
	// 親オブジェクトのNyaWindowを破棄するときに子オブジェクトを破棄する
	for (auto& e : child_.mission_collection_)
		delete e;

	DxLib_End();
}

/**
@brief ミッションを追加する関数
@param mission 追加するミッション
@note
 NyaWindowの子オブジェクトとしてミッションが追加される。
**/
void NyaWindow::Child(NyaMission* mission)
{
	child_.mission_collection_.push_back(mission);
}

void NyaWindow::Child(NyaOpening * opening)
{
	child_.opening_ = opening;
}

/**
 @brief 実行関数
 @note
  ライブラリの全ての処理が実行される
  よって、ライブラリ使用者はmain関数で必ず呼び出す必要がある
**/
void NyaWindow::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	std::chrono::system_clock::time_point debug_time_start, debug_time_end;
	long long debug_time_msec;

	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1 && event_ != eEVENT::WINDOW_CLOSE)
	{

		// TODO
		// mission all clear と add_child(mission) の関係
		// nya interface skill の初期化(ミッション→リプレイのとき不具合)
		// save replay or not save replay 状態遷移確認
		// game実行時にswingが実行されることがある
		// NyaDevice::Clear()時に経験値追加(NyaDeviceのリストサイズ取得関数を作る必要あり)

		//*********************************************************************
		// イベントの更新に使う変数をenum_zeroで初期化しておく
		// NyaWindowのメンバ関数でevent_next_の値をenum_zero以外にしたとき
		// Run()の最後にイベントを更新する処理をおこなう
		//*********************************************************************
		event_next_ = eEVENT::enum_zero;

		//***********************
		// NyaWindow メンバ関数
		// タイトル画面
		// オープニング処理
		// ミッション処理
		// エンディング処理
		// リプレイ保存
		//***********************
		Title();
		Opening();
		Mission();
		Ending();
		SaveReplay();
		NotSaveReplay();

		//******************************************************
		// ライブラリの処理
		// 引数なしの関数は常に実行される
		// eventを引数に取る関数はイベントによって処理が変わる
		//*******************************************************

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaDevice::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 620, "[600, 620] NyaDevice::Run() %d msec", (int)debug_time_msec);
#else 
		NyaDevice::Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaEffect::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 640, "[600, 640] NyaEffect::Run() %d msec", (int)debug_time_msec);
#else 
		NyaEffect::Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaGraphic::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 660, "[600, 660] NyaGraphic::Run() %d msec", (int)debug_time_msec);
#else 
		NyaGraphic::Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaPosition::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 680, "[600, 680] NyaPosition::Run() %d msec", (int)debug_time_msec);
#else 
		NyaPosition::Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaInput::Run(event_);
		NyaInterface::Run();
		NyaSound::Run();
		NyaString::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 700, "[600, 700] Nya*****::Run() %d msec", (int)debug_time_msec);
#else
		NyaInput::Run(event_);
		NyaInterface::Run();
		NyaSound::Run();
		NyaString::Run();
#endif

		//*****************************
		// 画面更新
		// フレームレートの処理
		//*****************************
		ScreenFlip();
		ClearDrawScreen();
		WaitFPS(1010, 695);

		//*******************************************************************************
		// enum_zeroでないならNyaWindowのメンバ関数でevent_next_を変更したということ
		// enum_zeroでないならイベントの更新をする
		//*******************************************************************************
		if (event_next_ != eEVENT::enum_zero)
			event_ = event_next_;
	}

}

/**
@brief エンディングの処理をする関数
@note
 エンディングが登録されてないときは何もせず次のイベントに遷移する
**/
void NyaWindow::Ending(void)
{
	switch(event_)
	{
		case eEVENT::ENDING_LOAD:
			if (child_.ending_ == nullptr)
				event_next_ = eEVENT::REPLAY_SAVE;
			else
			{
				child_.ending_->Load();
				event_next_ = eEVENT::ENDING_RUN;
			}
			break;
		case eEVENT::ENDING_RUN:
			child_.ending_->Run();
		if (NyaInput::IsPressKey(eINPUT::ENTER))
			event_next_ = eEVENT::ENDING_DELETE;
			break;
		case eEVENT::ENDING_DELETE:
			child_.ending_->Delete();
			event_next_ = eEVENT::REPLAY_SAVE;
			break;
	}
}


/**
 @brief ミッションの処理をする関数
 @note
  ミッションが登録されてない場合は何もしないでタイトルに戻る
**/
void NyaWindow::Mission(void)
{
	InterfaceHandleMissionAllOver* ihandle_mission_all_over;
	InterfaceHandleMissionClear* ihandle_mission_clear;
	InterfaceHandleMissionEx* ihandle_mission_ex;

	if (child_.mission_collection_.size() == 0)
	{
		event_next_ = eEVENT::TITLE;
		return;
	}

	// イベント毎にミッションの子オブジェクトであるuser, target, backgraoundの処理をおこなう
	if (child_.mission_index_ < child_.mission_collection_.size())
		child_.mission_collection_[child_.mission_index_]->Run(event_);

	switch (event_) 
	{	// インデックスの更新
	case eEVENT::TITLE:
		// 最低でも1フレームはタイトル画面にいるのでindexは必ず更新される
		child_.mission_index_ = 0;
		break;
	case eEVENT::MISSION_DELETE:
	case eEVENT::MISSION_REPLAY_DELETE:
		child_.mission_index_++;
		break;
	}

	switch (event_) 
	{	// イベントの更新
	case eEVENT::MISSION_CREATE:
		event_next_ = eEVENT::MISSION_RUN;
		break;
	case eEVENT::MISSION_RUN:
		ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
		if (ihandle_mission_clear->valid_)
			event_next_ = eEVENT::MISSION_CLEAR;
		ihandle_mission_all_over = NyaInterface::GetHandleMissionAllOver();
		if (ihandle_mission_all_over->valid_)
			event_next_ = eEVENT::MISSION_ALL_CLEAR;
		break;
	case eEVENT::MISSION_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::ENTER))
		{
			ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
			ihandle_mission_clear->valid_ = false;
			ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
			ihandle_mission_ex->valid_ = false;
			event_next_ = eEVENT::MISSION_DELETE;
		}
		break;
	case eEVENT::MISSION_ALL_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::ENTER))
		{
			ihandle_mission_all_over = NyaInterface::GetHandleMissionAllOver();
			ihandle_mission_all_over->valid_ = false;
			ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
			ihandle_mission_ex->valid_ = false;
			event_next_ = eEVENT::ENDING_LOAD;
		}
		break;
	case eEVENT::MISSION_DELETE:
		if (child_.mission_index_ < child_.mission_collection_.size())
			event_next_ = eEVENT::MISSION_CREATE;
		else
			event_next_ = eEVENT::TITLE;
		break;
	//**************************************
	// 以下はリプレイの再生時のイベント
	//**************************************
	case eEVENT::MISSION_REPLAY_CREATE:
		event_next_ = eEVENT::MISSION_REPLAY_RUN;
		break;
	case eEVENT::MISSION_REPLAY_RUN:
		ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
		if (ihandle_mission_clear->valid_)
			event_next_ = eEVENT::MISSION_REPLAY_CLEAR;
		ihandle_mission_all_over = NyaInterface::GetHandleMissionAllOver();
		if (ihandle_mission_all_over->valid_)
			event_next_ = eEVENT::MISSION_REPLAY_ALL_CLEAR;
		break;
	case eEVENT::MISSION_REPLAY_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::ENTER))
		{
			ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
			ihandle_mission_clear->valid_ = false;
			ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
			ihandle_mission_ex->valid_ = false;
			event_ = eEVENT::MISSION_REPLAY_DELETE;
		}
		break;
	case eEVENT::MISSION_REPLAY_ALL_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::ENTER))
		{
			ihandle_mission_all_over = NyaInterface::GetHandleMissionAllOver();
			ihandle_mission_all_over->valid_ = false;
			ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
			ihandle_mission_ex->valid_ = false;
			event_next_ = eEVENT::MISSION_REPLAY_DELETE;
		}
		break;
	case eEVENT::MISSION_REPLAY_DELETE:
		if (child_.mission_index_ < child_.mission_collection_.size())
			event_next_ = eEVENT::MISSION_REPLAY_CREATE;
		else
			event_next_ = eEVENT::TITLE;
		break;
	}
}

/**
 @param リプレイの保存をする関数
 @note
  フォントはタイトル画面を流用
**/
void NyaWindow::SaveReplay(void)
{
	string pass;
	int x, y;
	string date, seed;
	ifstream ifs;
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	tuple<int, int, int> red = make_tuple(255, 0, 0);
	static int select = 1;

	if (event_ != eEVENT::REPLAY_SAVE)
		return;

	//************************************************
	// カーソルキーの入力に応じて現在の選択を更新
	//************************************************
	if (NyaInput::IsPressKey(eINPUT::DOWN))
		select = (select == 5) ? 1 : select + 1;
	if (NyaInput::IsPressKey(eINPUT::UP))
		select = (select == 1) ? 5 : select - 1;
	x = 60;
	y = 100 + select * 100;
	NyaString::Write("window_title_font", red, x, y - 40, "★");

	//****************************
	// 現イベントの名前を表示
	//****************************
	x = 60;
	y = 100;
	NyaString::Write("window_title_font", white, x + 70, y - 40, "SAVE REPLAY");

	//*******************************************
	// リプレイフォルダにあるファイルの表示
	//*******************************************
	y += 100;
	ifs.open("replay/replay1.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay1");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay1.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();
	y += 100;
	ifs.open("replay/replay2.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay2");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay2.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();
	y += 100;
	ifs.open("replay/replay3.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay3");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay3.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	y += 100;
	ifs.close();
	ifs.open("replay/replay4.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay4");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay4.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();

	//**************************
	// 終了の選択肢を表示
	//**************************
	y += 100;
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "END");

	//****************************
	// ファイルへの書き込み
	//****************************
	if (NyaInput::IsPressKey(eINPUT::ENTER))
	{
		if (select == 1)
			NyaInput::OutputReplay("replay/replay1.rep");
		if (select == 2)
			NyaInput::OutputReplay("replay/replay2.rep");
		if (select == 3)
			NyaInput::OutputReplay("replay/replay3.rep");
		if (select == 4)
			NyaInput::OutputReplay("replay/replay4.rep");
	}

	//******************
	// イベントの更新
	//******************
	if (NyaInput::IsPressKey(eINPUT::ENTER) && select == 5)
		event_next_ = eEVENT::MISSION_DELETE;
}

/**
 @param リプレイの保存をしない関数
 @note
  フォントはタイトル画面を流用
  コンテニューしていたら全てのミッションクリア後にNotSaveReplay()が呼ばれる。
**/
void NyaWindow::NotSaveReplay(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	if (event_ != eEVENT::NOT_REPLAY_SAVE)
		return;

	NyaString::Write("window_title_font", white, 32, 100, "コンテニューしたので");
	NyaString::Write("window_title_font", white, 32, 150, "リプレイの保存はできません");


	//**************************
	// 終了の選択肢を表示
	//**************************
	NyaString::Write("window_title_font", white, 32, 250, "PRESS ENTER");

	//******************
	// イベントの更新
	//******************
	if (NyaInput::IsPressKey(eINPUT::ENTER))
		event_next_ = eEVENT::TITLE;
}

/**
@brief オープニングの処理をする関数
@note
 オープニングが登録されてないときは何もせず次のイベントに遷移する
**/
void NyaWindow::Opening(void)
{
	switch(event_)
	{
		case eEVENT::OPENING_LOAD:
			if (child_.opening_ == nullptr)
				event_next_ = eEVENT::MISSION_CREATE;
			else
			{
				child_.opening_->Load();
				event_next_ = eEVENT::OPENING_RUN;
			}
			break;
		case eEVENT::OPENING_RUN:
			child_.opening_->Run();
		if (NyaInput::IsPressKey(eINPUT::ENTER))
			event_next_ = eEVENT::OPENING_DELETE;
			break;
		case eEVENT::OPENING_DELETE:
			child_.opening_->Delete();
			event_next_ = eEVENT::MISSION_CREATE;
			break;
	}
}


/**
 @brief タイトル画面の処理をする関数
**/
void NyaWindow::Title(void)
{
	int x, y;
	string date, seed;
	ifstream ifs;
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	tuple<int, int, int> red = make_tuple(255, 0, 0);
	static int select = 0;
	InterfaceHandleSkill* ihandle_mission_skill = NyaInterface::GetHandleSkill();
	InterfaceHandleTitle* ihandle_title = NyaInterface::GetHandleTitle();

	if (event_ != eEVENT::TITLE)
		return;

	//******************
	// 選択の表示
	//******************
	if (NyaInput::IsPressKey(eINPUT::DOWN))
		select = (select == 5) ? 0 : select + 1;
	if (NyaInput::IsPressKey(eINPUT::UP))
		select = (select == 0) ? 5 : select - 1;
	x = 60;
	y = (select + 1) * 100;
	NyaString::Write("window_title_font", red, x, y - 40, "★");

	//******************
	// タイトルの表示
	//******************
	x = 60;
	y = 100;
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "mission");
	NyaString::Write("window_title_font", white, x + 70, y, "%s", ihandle_title->name_);

	//***********************
	// リプレイの有無を表示
	//***********************
	y += 100;
	ifs.open("replay/replay1.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay1");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay1.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();
	y += 100;
	ifs.open("replay/replay2.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay2");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay2.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();
	y += 100;
	ifs.open("replay/replay3.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay3");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay3.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();
	y += 100;
	ifs.open("replay/replay4.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay4");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay4.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();

	//******************
	// 終了の表示
	//******************
	y += 100;
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "END");

	//***********************
	// 選択が決定された
	//***********************
	if (NyaInput::IsPressKey(eINPUT::ENTER))
	{	
		ihandle_mission_skill->Clear();		// スキルのUIをクリア

		// ミッションの開始なら乱数の初期化をする
		// リプレイの開始ならリプレイファイルを読み込む
		// (リプレイファイル読み込み関数内で乱数の初期化がされる)
		if (select == 0)
			NyaInput::InitRand();	
		else if (select == 1)
			NyaInput::InputReplay("replay/replay1.rep");
		else if (select == 2)
			NyaInput::InputReplay("replay/replay2.rep");
		else if (select == 3)
			NyaInput::InputReplay("replay/replay3.rep");
		else if (select == 4)
			NyaInput::InputReplay("replay/replay4.rep");

		switch (select)
		{	// イベントの更新
		case 0:
			event_next_ = eEVENT::OPENING_LOAD;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			event_next_ = eEVENT::MISSION_REPLAY_CREATE;
			break;
		case 5:
			event_next_ = eEVENT::WINDOW_CLOSE;
			break;
		}
	}
}




/**
 @param FPS更新関数
 @note
  フレームレートの処理をする
**/
void NyaWindow::WaitFPS(int x, int y)
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
	const tuple<int, int, int> white = make_tuple(255, 255, 255);



//#ifdef __DEBUG__
//	if (frame_ave_ != 0) 
//	{
//		NyaString::Write("fps_font", white, x, y, "fps[%.1f fps]", 1000.0 / (double)frame_ave_);
//		NyaString::Write("fps_font", white, x + 100, y, "loop[%d ms]", ltime_ave_);
//		NyaString::Write("fps_font", white, x + 180, y, "wait[%d ms]", wtime_ave_);
//	}
//#else
	if (frame_ave_ != 0)
		NyaString::Write("fps_font", white, x + 170, y, "fps[%.1f fps]", 1000.0 / (double)frame_ave_);
//#endif


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


