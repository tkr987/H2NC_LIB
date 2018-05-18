#pragma once

#include <string>
#include <vector>
#include <utility>
#include "NyaDefine.h"

namespace H2NLIB
{

	class NyaDesign;
	class NyaDevice;
	class NyaEffect;
	class NyaInput;
	class NyaMission;
	class NyaPosition;
	class NyaSound;
	class NyaTarget;
	class NyaUser;

	// 子オブジェクトuser関連
	class WindowUser
	{
	public:
		bool valid_;
		NyaUser* nya_user_;
		WindowUser()
		{
			valid_ = false;
		}
	};

	// 子オブジェクトmission関連
	class WindowMission
	{
	public:
		bool valid_;
		int index_;
		std::vector<NyaMission*> nya_mission_collection_;
		WindowMission()
		{
			valid_ = false;
			index_ = 0;
		}
	};

	// nya window
	class NyaWindow
	{
	public:
		NyaWindow();
		~NyaWindow();
		void AddChMission(NyaMission*);
		void AddChUser(NyaUser* user);
		int Init(std::string title);
		void Run(void);
	private:
		eEVENT event_;
		std::string title_;
		// 子オブジェクト
		WindowUser ch_user_;
		WindowMission ch_mission_;
		// nya class
		NyaDesign* nya_design_;
		NyaDevice* nya_device_;
		NyaEffect* nya_effect_;
		NyaPosition* nya_position_;
		NyaSound* nya_sound_;
		void GameEnd(void);
		void SaveReplay(void);
		void RunChMission(void);
		void RunChUser(void);
		void RunEventUpdate(void);
		void Title(void);
		void WaitFPS(int x, int y);
	};

}
