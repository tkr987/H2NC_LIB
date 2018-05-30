#pragma once

#include <string>
#include <vector>
#include <utility>
#include "NyaEnum.h"

namespace H2NLIB
{
	class NyaDevice;
	class NyaEffect;
	class NyaInput;
	class NyaMission;
	class NyaPosition;
	class NyaTarget;
	class NyaUser;


	// 子オブジェクトmission関連
	class ChildMission
	{
	public:
		bool valid_;
		int index_;
		std::vector<NyaMission*> mission_collection_;
		ChildMission()
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
		void AddChild(NyaMission* mission);
		int Init(std::string title);
		void Run(void);
	private:
		eEVENT event_;
		std::string title_;
		ChildMission child_mission_;
		NyaDevice* nya_device_;
		NyaEffect* nya_effect_;
		NyaPosition* nya_position_;
		void Mission(void);
		void SaveReplay(void);
		void Title(void);
		void WaitFPS(int x, int y);
	};

}
