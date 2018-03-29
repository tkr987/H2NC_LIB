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
	class NyaGraphic;
	class NyaInput;
	class NyaMission;
	class NyaPosition;
	class NyaSound;
	class NyaTarget;
	class NyaUser;

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

	class WindowMission
	{
	public:
		bool valid_;
		int index_;
		std::vector<NyaMission*> nya_mission_vector_;
		WindowMission()
		{
			valid_ = false;
			index_ = 0;
		}
	};

	class NyaWindow
	{
	public:
		void AddChMission(NyaMission*);
		void AddChUser(NyaUser* user);
		int Init(std::string title);
		void Run(void);
		NyaWindow();
		~NyaWindow();
	private:
		ePROCESS::NUM process_;
		std::string title_name_;
		WindowUser ch_user_;
		WindowMission ch_mission_;
		NyaDesign* nya_design_;
		NyaDevice* nya_device_;
		NyaEffect* nya_effect_;
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		NyaSound* nya_sound_;
		void RunChMission(void);
		void RunChUser(void);
		void RunFPS(int x, int y);
		void RunProcessUpdate(void);
		void RunTitle(void);
	};

}
