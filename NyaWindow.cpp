#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <tuple>
#include "DxLib.h"
#include "HNLIB.h"
#define __DEBUG__

using namespace std;
using namespace std::experimental::filesystem;
using namespace HNLIB;


WindowChild::WindowChild()
{
	mission_index_ = 0;
	ending_ = nullptr;
	opening_ = nullptr;
}

WindowReplay::WindowReplay()
{
	existed_file_ = false;
	new_file_ = false;
}

void WindowReplay::Clear(void)
{
	date_.clear();
	existed_file_ = false;
	new_file_ = false;
	seed_.clear();
	title_.clear();
}


NyaWindow::NyaWindow(string title)
{
	//******************
	// DXLIB初期化
	//******************
	SetMainWindowText("happy 2 nya C++ DXLIB STG wrapper v88");		// タイトル
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
	// インターフェースの初期化をする
	NyaInterface::Init();
	NyaInterface::GetHandleTitle()->name_ << title;
	
	// フォント設定
	NyaString::SettingFont("fps_font", 14, 2);
	NyaString::SettingFont("window_title_font", 30, 4);
	NyaString::SettingFont("not_replay_font", 50, 6);
	NyaString::SettingFont("debug_font", 10, 2);

	// メンバ変数の初期化
	event_ = eEVENT::TITLE;
	event_next_ = eEVENT::enum_zero;
}


NyaWindow::~NyaWindow(void)
{
	// 親オブジェクトのNyaWindowを破棄するときに子オブジェクトを破棄する
	delete child_.opening_;
	child_.opening_ = nullptr;
	for (auto& e : child_.mission_collection_)
	{
		delete e;
		e = nullptr;
	}
	delete child_.ending_;
	child_.ending_ = nullptr;

	DxLib_End();
}

/**
@brief ミッションを追加する
@param mission 追加するミッション
@note
 NyaWindowの子オブジェクトとしてミッションが追加される。
**/
void NyaWindow::Child(NyaMission* mission)
{
	child_.mission_collection_.push_back(mission);
}

void NyaWindow::Child(NyaOpening* opening)
{
	child_.opening_ = opening;
}

void NyaWindow::Child(NyaEnding* ending)
{
	child_.ending_ = ending;
}


/**
 @brief ライブラリを実行する
 @note
  この関数を呼ばない限りライブラリの処理は実行されない。
  ライブラリ使用者はmain関数で必ず呼び出す必要がある。
**/
void NyaWindow::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	std::chrono::system_clock::time_point debug_time_start, debug_time_end;
	long long debug_time_msec;

	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1 && event_ != eEVENT::WINDOW_CLOSE)
	{
		// TODO
		// stage1
		// new delete ok, collision range, stage1 main_img extend rate

		//*********************************************************************
		// イベントの更新に使う変数をenum_zeroで初期化しておく
		// NyaWindowのメンバ関数でevent_next_の値をenum_zero以外にしたとき
		// Run()の最後にイベントを更新する処理をおこなう
		//*********************************************************************
		event_next_ = eEVENT::enum_zero;

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
		NyaEffect::Run(event_);
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 640, "[600, 640] NyaEffect::Run() %d msec", (int)debug_time_msec);
#else 
		NyaEffect::Run(event_);
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
		NyaPosition::Run(event_);
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 680, "[600, 680] NyaPosition::Run() %d msec", (int)debug_time_msec);
#else 
		NyaPosition::Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaInput::Run(event_);
		NyaInterface::Run(event_);
		NyaSound::Run();
		NyaString::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 700, "[600, 700] Nya*****::Run() %d msec", (int)debug_time_msec);
#else
		NyaInput::Run(event_);
		NyaInterface::Run(event_);
		NyaSound::Run();
		NyaString::Run();
#endif

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
@brief エンディングの処理をする
@note
 エンディングが登録されてないときは何もせず次のイベントに遷移する
**/
void NyaWindow::Ending(void)
{
	switch(event_)
	{
	case eEVENT::ENDING_LOAD:
		if (NyaInterface::GetHandleContinue()->cnum_ != 0)
			event_next_ = eEVENT::NOT_REPLAY_SAVE;
		else
		{
			if (child_.ending_ == nullptr)
				event_next_ = eEVENT::REPLAY_SAVE;
			else
			{
				child_.ending_->Load();
				event_next_ = eEVENT::ENDING_RUN;
			}
		}
		break;
	case eEVENT::ENDING_RUN:
		child_.ending_->Run();
	if (NyaInput::IsPressKey(eINPUT::ENTER))
		event_next_ = eEVENT::ENDING_DELETE;
		break;
	case eEVENT::ENDING_DELETE:
		child_.ending_->Delete();
		NyaInterface::Init();
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
	if (child_.mission_collection_.size() == 0)
	{	// ミッションが登録されていないので何もしない
		event_next_ = eEVENT::TITLE;
		return;
	}

	//***************************************************************
	// イベント処理
	// note: eEVENT::MISSION_CREATEはeEVENT::TITLEから遷移してくる
	//***************************************************************
	switch (event_) 
	{
	// ミッション生成の処理
	// 1. NyaMission::Run()の引数にeEVENT::MISSION_CREATEを渡してミッションクリア時の処理をさせる
	// 2. eEVENT::MISSION_RUNに遷移する
	case eEVENT::MISSION_CREATE:
		child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_CREATE);
		event_next_ = eEVENT::MISSION_RUN;
		break;
	// ミッション実行の処理
	// NyaMission::Run()の引数にeEVENT::MISSION_RUNを渡してミッション実行時の処理をさせる
	// また、インターフェースのフラグ状況によって遷移先を決める
	case eEVENT::MISSION_RUN:
		child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_RUN);
		if (NyaInterface::GetHandleContinue()->valid_)
			event_next_ = eEVENT::MISSION_CONTINUE;
		else if (NyaInterface::GetHandleClear()->valid_)
			event_next_ = eEVENT::MISSION_CLEAR;
		else if (NyaInterface::GetHandleComplete()->valid_)
			event_next_ = eEVENT::MISSION_COMPLETE;
		break;
	// ミッションコンテニューの処理
	// - mission continue 画面が表示されているとき
	// NyaMission::Run()の引数にeEVENT::MISSION_CONTINUEを渡してコンテニュー画面の処理をさせる
	// - mission continue 画面の表示が終わったとき
	// continue ハンドルの値によって遷移先を決める
	// -- コンテニューする選択のとき
	//  eEVENT::MISSION_RUNに遷移する
	// -- コンテニューしない選択、かつコンテニュー回数が0のとき
	//  1. NyaMission::Run()の引数にeEVENT::MISSION_DELETEを渡してミッションを削除させる
	//  2. eEVENT::REPLAY_SAVEに遷移する
	// -- コンテニューしない選択だが、コンテニュー回数は0でないとき
	//  1. NyaMission::Run()の引数にeEVENT::MISSION_DELETEを渡してミッションを削除させる
	//  2. eEVENT::REPLAY_SAVEに遷移する
	case eEVENT::MISSION_CONTINUE:
		if (NyaInterface::GetHandleContinue()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_CONTINUE);
		else
		{
			if (NyaInterface::GetHandleContinue()->select_ == InterfaceHandleContinue::eSELECT::YES)
				event_next_ = eEVENT::MISSION_RUN;
			if (NyaInterface::GetHandleContinue()->select_ == InterfaceHandleContinue::eSELECT::NO && NyaInterface::GetHandleContinue()->cnum_ == 0)
				event_next_ = eEVENT::REPLAY_SAVE;
			if (NyaInterface::GetHandleContinue()->select_ == InterfaceHandleContinue::eSELECT::NO && NyaInterface::GetHandleContinue()->cnum_ != 0)
				event_next_ = eEVENT::NOT_REPLAY_SAVE;
		}
		break;
	// ミッションクリアの処理
	// - mission clear 画面が表示されているとき
	// NyaMission::Run()の引数にeEVENT::MISSION_CLEARを渡してミッションクリア時の処理をさせる
	// - mission clear 画面の表示が終わったとき
	// 1. 有効化されているインターフェースハンドルの無効化
	// 2. NyaMission::Run()の引数にeEVENT::MISSION_DELETEを渡してミッションを削除させる
	// 3. mission_index_を更新する
	// 4. eEVENT::MISSION_CREATEに遷移する
	case eEVENT::MISSION_CLEAR:
		if(NyaInterface::GetHandleClear()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_CLEAR);
		else 
		{
			NyaInterface::GetHandleHealth()->valid_ = false;
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_DELETE);
			child_.mission_index_++;
			event_next_ = eEVENT::MISSION_CREATE;
		}
		break;
	// ミッションコンプリートの処理
	// - mission complete 画面が表示されているとき
	// NyaMission::Run()の引数にeEVENT::MISSION_COMPLETEを渡してミッションコンプリート時の処理をさせる
	// - mission complete 画面の表示が終わったとき
	// 1. 有効化されているインターフェースハンドルの無効化
	// 2. eEVENT::ENDING_LOADに遷移する
	case eEVENT::MISSION_COMPLETE:
		if (NyaInterface::GetHandleComplete()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_COMPLETE);
		else
		{
			NyaInterface::GetHandleHealth()->valid_ = false;
			event_next_ = eEVENT::ENDING_LOAD;
		}
		break;
	// ミッション生成の処理(リプレイ)
	// 1. NyaMission::Run()の引数にeEVENT::MISSION_REPLAY_CREATEを渡してミッションクリア時の処理をさせる
	// 2. eEVENT::MISSION_REPLAY_RUNに遷移する
	case eEVENT::MISSION_REPLAY_CREATE:
		child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_REPLAY_CREATE);
		event_next_ = eEVENT::MISSION_REPLAY_RUN;
		break;
	// ミッション実行の処理(リプレイ)
	// NyaMission::Run()の引数にeEVENT::MISSION_REPLAY_RUNを渡してミッション実行時の処理をさせる
	// また、フラグ状況によって遷移先を決める
	// - 残機0ならreplay end flagをtrueにしてeEVENT::MISSION_REPLAY_ENDに遷移する
	// - mission clear flagがtrueならeEVENT::MISSION_REPLAY_CLEARに遷移する
	// - mission complete flagがtrueならeEVENT::MISSION_REPLAY_COMPLETEに遷移する
	case eEVENT::MISSION_REPLAY_RUN:
		child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_REPLAY_RUN);
		if (NyaInterface::GetHandleLife()->value_ == 0)
		{
			NyaInterface::GetHandleEnd()->valid_ = true;
			event_next_ = eEVENT::MISSION_REPLAY_END;
		}
		else if (NyaInterface::GetHandleClear()->valid_)
			event_next_ = eEVENT::MISSION_REPLAY_CLEAR;
		else if (NyaInterface::GetHandleComplete()->valid_)
			event_next_ = eEVENT::MISSION_REPLAY_COMPLETE;
		break;
	// リプレイ終了の処理
	// - replay end 画面が表示されているとき
	// 1. NyaMission::Run()の引数にeEVENT::MISSION_REPLAY_ENDを渡してリプレイ終了時の処理をさせる
	// 2. リプレイ終了画面の表示をする
	// - replay end 画面の表示が終わったとき
	// 1. インターフェースを初期化する
	// 2. eEVENT::TITLEに遷移する
	case eEVENT::MISSION_REPLAY_END:
		if (NyaInterface::GetHandleEnd()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_REPLAY_END);
		else
		{
			NyaInterface::Init();
			event_next_ = eEVENT::TITLE;
		}
		break;
	// ミッションクリアの処理(リプレイ)
	// - mission clear 画面が表示されているとき
	// NyaMission::Run()の引数にeEVENT::MISSION_REPLAY_CLEARを渡してリプレイクリア時の処理をさせる
	// - mission clear 画面の表示が終わったとき
	// 1. 有効化されているインターフェースハンドルの無効化
	// 2. NyaMission::Run()の引数にeEVENT::MISSION_DELETEを渡してミッションを削除させる
	// 3. mission_index_を更新する
	// 4. eEVENT::TITLEに遷移する
	case eEVENT::MISSION_REPLAY_CLEAR:
		if (NyaInterface::GetHandleClear()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_REPLAY_CLEAR);
		else
		{
			NyaInterface::GetHandleHealth()->valid_ = false;
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_DELETE);
			child_.mission_index_++;
			event_next_ = eEVENT::MISSION_REPLAY_CREATE;
		}
		break;
	// ミッションコンプリートの処理
	// - mission complete 画面が表示されているとき
	// NyaMission::Run()の引数にeEVENT::MISSION_COMPLETEを渡してミッションコンプリート時の処理をさせる
	// - mission complete 画面の表示が終わったとき
	// 1. インターフェースの初期化
	// 2. eEVENT::TITLEに遷移する
	case eEVENT::MISSION_REPLAY_COMPLETE:
		if (NyaInterface::GetHandleComplete()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_REPLAY_COMPLETE);
		else
		{
			NyaInterface::Init();
			event_next_ = eEVENT::TITLE;
		}
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
	int x, y;
	ifstream ifs;
	tuple<int, int, int> color;
	const tuple<int, int, int> white = make_tuple(255, 255, 255);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);
	static int select = 0;
	static bool first_call = true;		// trueならファイルの読み込みをおこなう

	if (event_ != eEVENT::REPLAY_SAVE)
		return;

	if (first_call)
	{	// インターフェースの初期化とリプレイファイルの有無判定
		NyaInterface::Init();
		for (int replay_index = 0; replay_index < 4; replay_index++)
		{
			if (replay_index == 0)
				ifs.open("replay/replay1.rep");
			else if (replay_index == 1)
				ifs.open("replay/replay2.rep");
			else if (replay_index == 2)
				ifs.open("replay/replay3.rep");
			else
				ifs.open("replay/replay4.rep");
			if (ifs.is_open())
			{
				getline(ifs, replay_collection_[replay_index].seed_);
				getline(ifs, replay_collection_[replay_index].date_);
				getline(ifs, replay_collection_[replay_index].title_);
				replay_collection_[replay_index].existed_file_ = true;
			}
			ifs.close();
		}
		first_call = false;
	}

	// カーソルキーの入力に応じて現在の選択を更新
	if (NyaInput::IsPressKey(eINPUT::DOWN))
		select = (select == 4) ? 0 : select + 1;
	if (NyaInput::IsPressKey(eINPUT::UP))
		select = (select == 0) ? 4 : select - 1;
	x = 60;
	y = 100 + (select + 1) * 100;
	NyaString::Write("window_title_font", red, x, y - 40, "★");

	// 現イベントの名前を表示
	x = 60;
	y = 100;
	NyaString::Write("window_title_font", white, x + 70, y - 40, "SAVE REPLAY");

	for (int replay_index = 0; replay_index < 4; replay_index++)
	{	// リプレイフォルダにあるファイルの表示
		y += 100;
		NyaString::Write("window_title_font", white, x, y - 40, "☆");
		if (replay_collection_[replay_index].new_file_)
			color = red;
		else
			color = white;
		if (replay_index == 0)
			NyaString::Write("window_title_font", color, x + 70, y - 40, "replay1");
		else if (replay_index == 1)
			NyaString::Write("window_title_font", color, x + 70, y - 40, "replay2");
		else if (replay_index == 2)
			NyaString::Write("window_title_font", color, x + 70, y - 40, "replay3");
		else
			NyaString::Write("window_title_font", color, x + 70, y - 40, "replay4");
		if (replay_collection_[replay_index].existed_file_)
		{
			NyaString::Write("window_title_font", color, x + 180, y - 40, "..." + replay_collection_[replay_index].title_);
			if (replay_index == 0)
				NyaString::Write("window_title_font", color, x + 70, y, "%s", replay_collection_[replay_index].date_ + " replay1.rep");
			else if (replay_index == 1)
				NyaString::Write("window_title_font", color, x + 70, y, "%s", replay_collection_[replay_index].date_ + " replay2.rep");
			else if (replay_index == 2)
				NyaString::Write("window_title_font", color, x + 70, y, "%s", replay_collection_[replay_index].date_ + " replay3.rep");
			else
				NyaString::Write("window_title_font", color, x + 70, y, "%s", replay_collection_[replay_index].date_ + " replay4.rep");
		}
		else
			NyaString::Write("window_title_font", color, x + 70, y, "%s", "no_replay");
	}

	// 終了の選択肢を表示
	y += 100;
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "END");

	// 新しくリプレイファイルを出力する
	// 書き込みしたあと表示を更新するため、first_callをtrueにする
	// 次のSaveReplay()呼び出し時に再読込みするので、再読込み前にClear()しておく
	if (NyaInput::IsPressKey(eINPUT::ENTER))
	{
		if (select == 0)
		{
			NyaInput::OutputReplay("replay/replay1.rep");
			first_call = true;
			replay_collection_[0].Clear();
			replay_collection_[0].new_file_ = true;
		}
		if (select == 1)
		{
			NyaInput::OutputReplay("replay/replay2.rep");
			first_call = true;
			replay_collection_[1].Clear();
			replay_collection_[1].new_file_ = true;
		}
		if (select == 2)
		{
			NyaInput::OutputReplay("replay/replay3.rep");
			first_call = true;
			replay_collection_[2].Clear();
			replay_collection_[2].new_file_ = true;
		}
		if (select == 3)
		{
			NyaInput::OutputReplay("replay/replay4.rep");
			first_call = true;
			replay_collection_[3].Clear();
			replay_collection_[3].new_file_ = true;
		}
	}

	if (NyaInput::IsPressKey(eINPUT::ENTER) && select == 4)
	{	// イベントの更新
		first_call = true;
		select = 0;
		for (auto& e : replay_collection_)
			e.Clear();
		event_next_ = eEVENT::TITLE;
	}
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

	// まず、インターフェースの初期化をしておく
	NyaInterface::Init();

	NyaString::Write("window_title_font", white, SCREEN_CENTER_X - 150, 100, "コンテニューしたので");
	NyaString::Write("window_title_font", white, SCREEN_CENTER_X - 195, 150, "リプレイの保存はできません");

	//**************************
	// 終了の選択肢を表示
	//**************************
	NyaString::Write("not_replay_font", white, SCREEN_CENTER_X - 140, SCREEN_MAX_Y - 250, "PRESS ENTER");

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
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	tuple<int, int, int> red = make_tuple(255, 0, 0);
	static int select = 0;
	static bool first_call = true;

	if (event_ != eEVENT::TITLE)
		return;

	if (first_call)
	{	// インターフェースの初期化とリプレイファイルの有無判定
		ifstream ifs;
		NyaDevice::Init();
		NyaGraphic::Init();
		NyaInterface::Init();
		NyaPosition::Init();
		NyaSound::Init();
		for (int replay_index = 0; replay_index < 4; replay_index++)
		{
			replay_collection_[replay_index].Clear();
			if (replay_index == 0)
				ifs.open("replay/replay1.rep");
			else if (replay_index == 1)
				ifs.open("replay/replay2.rep");
			else if (replay_index == 2)
				ifs.open("replay/replay3.rep");
			else
				ifs.open("replay/replay4.rep");
			if (ifs.is_open())
			{
				getline(ifs, replay_collection_[replay_index].seed_);
				getline(ifs, replay_collection_[replay_index].date_);
				getline(ifs, replay_collection_[replay_index].title_);
				replay_collection_[replay_index].existed_file_ = true;
			}
			ifs.close();
		}
		first_call = false;
	}

	// 選択の表示
	if (NyaInput::IsPressKey(eINPUT::DOWN))
		select = (select == 5) ? 0 : select + 1;
	if (NyaInput::IsPressKey(eINPUT::UP))
		select = (select == 0) ? 5 : select - 1;
	x = 60;
	y = (select + 1) * 100;
	if (select == 5)
		y += 40;
	NyaString::Write("window_title_font", red, x, y - 40, "★");

	// タイトルの表示
	x = 60;
	y = 100;
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "mission");
	NyaString::Write("window_title_font", white, x + 180, y - 40, "%s", "..." + NyaInterface::GetHandleTitle()->name_.str());

	for (int replay_index = 0; replay_index < 4; replay_index++)
	{	// リプレイフォルダにあるファイルの表示
		y += 100;
		NyaString::Write("window_title_font", white, x, y - 40, "☆");
		if (replay_index == 0)
			NyaString::Write("window_title_font", white, x + 70, y - 40, "replay1");
		else if (replay_index == 1)
			NyaString::Write("window_title_font", white, x + 70, y - 40, "replay2");
		else if (replay_index == 2)
			NyaString::Write("window_title_font", white, x + 70, y - 40, "replay3");
		else
			NyaString::Write("window_title_font", white, x + 70, y - 40, "replay4");
		if (replay_collection_[replay_index].existed_file_)
		{
			NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + replay_collection_[replay_index].title_);
			if (replay_index == 0)
				NyaString::Write("window_title_font", white, x + 70, y, "%s", replay_collection_[replay_index].date_ + " replay1.rep");
			else if (replay_index == 1)
				NyaString::Write("window_title_font", white, x + 70, y, "%s", replay_collection_[replay_index].date_ + " replay2.rep");
			else if (replay_index == 2)
				NyaString::Write("window_title_font", white, x + 70, y, "%s", replay_collection_[replay_index].date_ + " replay3.rep");
			else
				NyaString::Write("window_title_font", white, x + 70, y, "%s", replay_collection_[replay_index].date_ + " replay4.rep");
		}
		else
			NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	}

	// 終了の表示
	y += (100 + 40);
	NyaString::Write("window_title_font", white, x, y - 40, "☆");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "END");

	// 選択が決定された
	// イベントを遷移させるが、選択したリプレイファイルが存在しないときは遷移しない
	if (NyaInput::IsPressKey(eINPUT::ENTER))
	{
		// 前回のミッション内容が残っていることもあるので
		// NyaMission::Run()の引数にeEVENT::MISSION_DELETEを渡して全ミッションをクリアしておく
		// child_.mission_collection_[0]からミッション開始するためindexを0にする
		for (auto& e : child_.mission_collection_)
			e->Run(eEVENT::MISSION_DELETE);
		child_.mission_index_ = 0;

		// ミッションの開始なら乱数の初期化と時刻の取得をおこなう
		// リプレイの開始ならリプレイファイルを読み込む
		// (リプレイファイル読み込み関数内で乱数の初期化もされる)
		// 次にタイトルに戻ってきたときのために予めfirst_callをtrueにしておく。
		// イベントの更新をおこなう
		switch (select)
		{
		case 0:
			NyaInput::Init();
			first_call = true;
			event_next_ = eEVENT::OPENING_LOAD;
			break;
		case 1:
			if (NyaInput::InputReplay("replay/replay1.rep"))
			{
				first_call = true;
				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
			}
			else
				event_next_ = eEVENT::TITLE;
			break;
		case 2:
			if (NyaInput::InputReplay("replay/replay2.rep"))
			{
				first_call = true;
				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
			}
			else
				event_next_ = eEVENT::TITLE;
			break;
		case 3:
			if (NyaInput::InputReplay("replay/replay3.rep"))
			{
				first_call = true;
				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
			}
			else
				event_next_ = eEVENT::TITLE;
			break;
		case 4:
			if (NyaInput::InputReplay("replay/replay4.rep"))
			{
				first_call = true;
				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
			}
			else
				event_next_ = eEVENT::TITLE;
			break;
		case 5:
			event_next_ = eEVENT::WINDOW_CLOSE;
			break;
		}
	}
}

/**
 @brief タイトル画面の処理をする関数
**/
//void NyaWindow::Title(void)
//{
//	int x, y;
//	string date, seed, title;
//	ifstream ifs;
//	tuple<int, int, int> white = make_tuple(255, 255, 255);
//	tuple<int, int, int> red = make_tuple(255, 0, 0);
//	static int select = 0;
//	InterfaceHandleSkill* ihandle_mission_skill = NyaInterface::GetHandleSkill();
//
//	if (event_ != eEVENT::TITLE)
//		return;
//
//	//******************
//	// 選択の表示
//	//******************
//	if (NyaInput::IsPressKey(eINPUT::DOWN))
//		select = (select == 5) ? 0 : select + 1;
//	if (NyaInput::IsPressKey(eINPUT::UP))
//		select = (select == 0) ? 5 : select - 1;
//	x = 60;
//	y = (select + 1) * 100;
//	if (select == 5)
//		y += 40;
//	NyaString::Write("window_title_font", red, x, y - 40, "★");
//
//	//******************
//	// タイトルの表示
//	//******************
//	x = 60;
//	y = 100;
//	NyaString::Write("window_title_font", white, x, y - 40, "☆");
//	NyaString::Write("window_title_font", white, x + 70, y - 40, "mission");
//	NyaString::Write("window_title_font", white, x + 180, y - 40, "%s", "..." + NyaInterface::GetHandleTitle()->name_.str());
//
//	//***********************
//	// リプレイの有無を表示
//	//***********************
//	y += 100;
//	ifs.open("replay/replay1.rep");
//	NyaString::Write("window_title_font", white, x, y - 40, "☆");
//	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay1");
//	if (ifs.is_open())
//	{
//		getline(ifs, seed);
//		getline(ifs, date);
//		getline(ifs, title);
//		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
//		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay1.rep");
//	}
//	else
//		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
//	ifs.close();
//	y += 100;
//	ifs.open("replay/replay2.rep");
//	NyaString::Write("window_title_font", white, x, y - 40, "☆");
//	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay2");
//	if (ifs.is_open())
//	{
//		getline(ifs, seed);
//		getline(ifs, date);
//		getline(ifs, title);
//		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
//		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay2.rep");
//	}
//	else
//		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
//	ifs.close();
//	y += 100;
//	ifs.open("replay/replay3.rep");
//	NyaString::Write("window_title_font", white, x, y - 40, "☆");
//	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay3");
//	if (ifs.is_open())
//	{
//		getline(ifs, seed);
//		getline(ifs, date);
//		getline(ifs, title);
//		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
//		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay3.rep");
//	}
//	else
//		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
//	ifs.close();
//	y += 100;
//	ifs.open("replay/replay4.rep");
//	NyaString::Write("window_title_font", white, x, y - 40, "☆");
//	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay4");
//	if (ifs.is_open())
//	{
//		getline(ifs, seed);
//		getline(ifs, date);
//		getline(ifs, title);
//		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
//		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay4.rep");
//	}
//	else
//		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
//	ifs.close();
//
//	//******************
//	// 終了の表示
//	//******************
//	y += (100 + 40);
//	NyaString::Write("window_title_font", white, x, y - 40, "☆");
//	NyaString::Write("window_title_font", white, x + 70, y - 40, "END");
//
//	//***********************************************************************************
//	// 選択が決定された
//	// イベントを遷移させるが、選択したリプレイファイルが存在しないときは遷移しない
//	//***********************************************************************************
//	if (NyaInput::IsPressKey(eINPUT::ENTER))
//	{	
//		// スキルのUIをクリア
//		// 前回のミッション内容が残っていることもあるので
//		// NyaMission::Run()の引数にeEVENT::MISSION_DELETEを渡して全ミッションをクリアしておく
//		// child_.mission_collection_[0]からミッション開始するためindexを0にする
//		ihandle_mission_skill->Clear();	
//		for (auto& e : child_.mission_collection_)
//			e->Run(eEVENT::MISSION_DELETE);
//		child_.mission_index_ = 0;
//
//		// ミッションの開始なら乱数の初期化と時刻の取得をおこなう
//		// リプレイの開始ならリプレイファイルを読み込む
//		// (リプレイファイル読み込み関数内で乱数の初期化もされる)
//		// イベントの更新をおこなう
//		switch (select)
//		{
//		case 0:
//			NyaInput::Init();	
//			event_next_ = eEVENT::OPENING_LOAD;
//			break;
//		case 1:
//			if (NyaInput::InputReplay("replay/replay1.rep"))
//				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
//			else
//				event_next_ = eEVENT::TITLE;
//			break;
//		case 2:
//			if (NyaInput::InputReplay("replay/replay2.rep"))
//				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
//			else
//				event_next_ = eEVENT::TITLE;
//			break;
//		case 3:
//			if (NyaInput::InputReplay("replay/replay3.rep"))
//				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
//			else
//				event_next_ = eEVENT::TITLE;
//			break;
//		case 4:
//			if (NyaInput::InputReplay("replay/replay4.rep"))
//				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
//			else
//				event_next_ = eEVENT::TITLE;
//			break;
//		case 5:
//			event_next_ = eEVENT::WINDOW_CLOSE;
//			break;
//		}
//	}
//}


/**
@param FPSを更新する(milliseconds version)
**/
void NyaWindow::WaitFPS(int x, int y)
{
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	// フレームレート表示
	if (NyaInput::GetFrameCount() % FPS_MAX == 0)
	{	// １秒に１回の頻度で１フレームの処理にかかった平均時間を計算する
		fps_.frame_average_time_ = 0;
		for (auto& e : fps_.frame_time_collection_)
			fps_.frame_average_time_ += e;
		fps_.frame_average_time_ /= FPS_MAX;
	}
	if (fps_.frame_average_time_ != 0)
		NyaString::Write("fps_font", white, x + 170, y, "fps[%.1lf fps]", 1000.0 / (double)fps_.frame_average_time_);
	else
		NyaString::Write("fps_font", white, x + 170, y, "fps[%.1lf fps]", 0);

	// wait 処理
	fps_.frame_count_ = ++fps_.frame_count_ % FPS_MAX;
	fps_.wait_time_ = (1000 / FPS_MAX) - (GetNowCount() - fps_.prev_time_);
	if (0 < fps_.wait_time_)
		this_thread::sleep_for(std::chrono::milliseconds(fps_.wait_time_));
	fps_.frame_time_collection_[fps_.frame_count_] = GetNowCount() - fps_.prev_time_;
	fps_.prev_time_ = GetNowCount();
}


/**
@param FPSを更新する(microseconds version)
**/
void NyaWindow::WaitFPS2(int x, int y)
{
	LONGLONG now_time;
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	// フレームレート表示
	if (NyaInput::GetFrameCount() % FPS_MAX == 0)
	{	// １秒に１回の頻度で１フレームの処理にかかった平均時間を計算する
		fps2_.frame_average_time_ = 0;
		for (auto& e : fps2_.frame_time_collection_)
			fps2_.frame_average_time_ += e;
		fps2_.frame_average_time_ /= FPS_MAX;
	}
	if (fps2_.frame_average_time_ != 0)
		NyaString::Write("fps_font", white, x + 170, y, "fps[%.1lf fps]", (double)(1000000 / fps2_.frame_average_time_));
	else
		NyaString::Write("fps_font", white, x + 170, y, "fps[%.1lf fps]", 0);

	// wait 処理
	fps2_.frame_count_ = ++fps2_.frame_count_ % FPS_MAX;
	now_time = GetNowHiPerformanceCount();
	fps2_.wait_time_ = (1000000 / FPS_MAX) - (now_time - fps2_.prev_time_);
	if (0 < fps2_.wait_time_)
		this_thread::sleep_for(std::chrono::microseconds(fps2_.wait_time_));
	fps2_.frame_time_collection_[fps2_.frame_count_] = fps2_.prev_time_;
	fps2_.prev_time_ = GetNowHiPerformanceCount();
	fps2_.frame_time_collection_[fps2_.frame_count_] = fps2_.prev_time_ - fps2_.frame_time_collection_[fps2_.frame_count_];
}

