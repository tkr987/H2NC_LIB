#pragma once


#include <string>
#include <utility>
#include <vector>
#include "NyaEnum.h"


namespace H2NLIB
{
	class NyaBackground;
	class NyaTarget;
	class NyaUser;

	// ***************************************************************************************
	// class MissionTarget
	// NyaMission::AddChTarget()で登録された内容を格納するために宣言されたクラス
	// start_timeやend_timeも保存されているので、NyaMission::Run()で処理することができる
	// ***************************************************************************************
	class MissionTarget
	{		
	public:
		unsigned int start_frame_;
		unsigned int end_frame_;
		NyaTarget* target_;
	};

	class NyaMission
	{
	public:
		NyaMission();
		virtual ~NyaMission();
		void AddChild(NyaBackground* background);
		void AddChild(int start_time_sec, int end_time_sec, NyaTarget* target, unsigned int id);
		void AddChild(NyaUser* user);
		void ClearBackground(void);
		void ClearTarget(void);
		void ClearUser(void);
		void Run(eEVENT check_event);
		/**
		 @brief ミッション作成イベントで実行する処理を定義する関数
		 @note
		  eEVENT::MISSION_CREATEで実行される
		**/
		virtual void Create(void) = 0;
		/**
		 @brief ミッション削除イベントで実行する処理を定義する関数
		 @note
		  eEVENT::MISSION_DELETEで実行される
		  Delete()の定義で処理を何も書かなかった場合、前のミッションのデータが引き継がれる
		**/
		virtual void Delete(void) = 0;
	private:
		// eEVENT::MISSION_RUNの状態のフレーム数をカウントする
		// UINT_MAXを超えるミッションは正常動作しないので注意
		unsigned int count_frame_;
		static NyaBackground* background_;
		static NyaUser* user_;
		static std::vector<MissionTarget*> mission_target_collection_;
	};

}
