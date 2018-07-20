#pragma once

#include <array>
#include <limits>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include "NyaEnum.h"


namespace HNLIB
{
	class SoundPropertyX;

	/**
	@brief mission clear 操作クラス
	@note
	 変数valid_をtrueにするとmission completeを表示する
	**/
	class InterfaceHandleClear
	{
	public:
		bool valid_;		//!< clear画面表示の有効化
		void Clear();
	};

	/**
	@brief mission complete 操作クラス
	@note
	 変数valid_をtrueにするとmission completeを表示する
	**/
	class InterfaceHandleComplete
	{
	public:
		bool valid_;		//!< complete画面表示の有効化
		void Clear();
	};

	/**
	@brief continue 操作クラス
	@note
	 ライブラリ使用者はvalid_とrecovery_以外のメンバ変数を使う必要はない。
	 - recovery_:
	 値を設定するとコンテニュー画面から戻ったときライフ数に反映される。
	 デフォルトでは値1に設定されている。
	 - valid_:
	 trueにするとコンテニュー画面を表示する。
	 [enter]キーで選択するとコンテニュー画面は自動的に閉じられる。
	 - cnum_:
	 0ならMISSION_COMPLETE時にリプレイをセーブするイベントに移行。
	 0以外ならMISSION_COMPLETE時にリプレイをセーブしない。
	 コンテニュー画面に表示される選択肢は2つなので、メンバ変数select_の値は[0,1]のみ。
	 メンバselect_の値を[0,1]以外にすると選択できなくなる。
	**/
	class InterfaceHandleContinue
	{
	public:
		unsigned int cnum_;				//!< continue回数
		unsigned int recovery_;			//!< continueから戻ったときのライフ数
		int select_;					//!< continue画面で現在選択している項目
		bool valid_;					//!< continue画面表示の有効化
		void Clear();
	};

	/**
	@brief replay end 操作クラス
	@note
	 変数valid_をtrueにするとreplay endを表示する
	**/
	class InterfaceHandleEnd
	{
	public:
		bool valid_;		//!< replay end 画面表示の有効化
		void Clear();
	};

	class InterfaceHandleHealth
	{
	public:
		bool valid_;
		double value_;
		void Clear();
	};

	/**
	@brief ライフ操作クラス
	@note
	 メンバvalue_には[0-8]の値を設定することができる。
	 0未満の値を設定したときは次フレームまでに0の値に自動的に変更される。
	 9以上の値を設定したときは次フレームまでに8の値に自動的に変更される。
	**/
	class InterfaceHandleLife
	{
	public:
		int value_;		//!< ライフ数
	};

	class InterfaceHandleSkill
	{
	public:
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv1_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv2_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv3_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv4_exp_;
		std::array<std::string, static_cast<int>(eSKILL::sizeof_enum)> name_;
		eSKILL select_;									// 現在選択しているスキル
		InterfaceHandleSkill();
		void AddExp(unsigned int value);
		void Clear(void);
	};

	class InterfaceHandleWarning
	{
	public:
		unsigned int draw_frame_;
		unsigned int draw_frame_max_;
		int draw_grid_x_;
		int draw_grid_y_;
		bool draw_valid_;
		SoundPropertyX* spx_;
		bool sound_valid_;
		void LoadSound(std::string file_pass, unsigned int volume = 100);
		void DeleteSound(void);
		InterfaceHandleWarning();
		~InterfaceHandleWarning();
	};



	class InterfaceHandleTitle
	{
	public:
		std::stringstream name_;
		InterfaceHandleTitle();
	};


	class NyaInterface {
	public:
		NyaInterface();
		~NyaInterface();
		static void Init(void);
		static void Run(eEVENT event_check);
		static InterfaceHandleClear* GetHandleClear(void) { return &handle_clear_; }
		static InterfaceHandleComplete* GetHandleComplete(void) { return &handle_complete_; }
		static InterfaceHandleContinue* GetHandleContinue(void) { return &handle_continue_; }
		static InterfaceHandleEnd* GetHandleEnd(void) { return &handle_end_; }
		static InterfaceHandleHealth* GetHandleHealth (void) { return &handle_health_; }
		static InterfaceHandleLife* GetHandleLife(void) { return &handle_life_; }
		static InterfaceHandleSkill* GetHandleSkill(void) { return &handle_skill_; }
		static InterfaceHandleTitle* GetHandleTitle(void) { return &handle_title_; }
		static InterfaceHandleWarning* GetHandleWarning(void) { return &handle_warning_; }
	private:
		static InterfaceHandleClear handle_clear_;
		static InterfaceHandleComplete handle_complete_;
		static InterfaceHandleContinue handle_continue_;
		static InterfaceHandleEnd handle_end_;
		static InterfaceHandleHealth handle_health_;
		static InterfaceHandleLife handle_life_;
		static InterfaceHandleSkill handle_skill_;
		static InterfaceHandleTitle handle_title_;
		static InterfaceHandleWarning handle_warning_;
		static void DrawBlack(int x, int y, int x2, int y2);
		static void DrawClear(int x, int y);
		static void DrawComplete(int x, int y);
		static void DrawContinue(int x, int y, eEVENT event_check);
		static void DrawEnd(int x, int y);
		static void DrawLIB(int x, int y);
		static void DrawHealth(void);
		static void DrawTitle(int x, int y);
		static void DrawInput(int x, int y);
		static void DrawLife(int x, int y);
		static void DrawSkill(int x, int y);
		static void DrawWarning(void);
	};

}

