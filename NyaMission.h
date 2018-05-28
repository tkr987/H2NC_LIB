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
		virtual void Create(void) = 0;		// eEVENT::MISSION_CLEATEで実行される
		virtual void Delete(void){}			// eEVENT::MISSION_DELETEで実行される
		void AddChild(NyaBackground* background);
		void AddChild(int start_time_sec, int end_time_sec, NyaTarget* target, unsigned int id);
		void AddChild(NyaUser* user);
		void DeleteBackground(void);
		void DeleteTarget(void);
		void DeleteUser(void);
		void Run(eEVENT check_event);
	private:
		// eEVENT::MISSION_RUNの状態のフレーム数をカウントする
		// UINT_MAXを超えるミッションは正常動作しないので注意
		unsigned int count_frame_;
		static NyaBackground* background_;
		static NyaUser* user_;
		static std::vector<MissionTarget*> mission_target_collection_;
	};

}
