#pragma once

#include <string>
#include <vector>
#include <utility>
#include "NyaEnum.h"

namespace H2NLIB
{
	class NyaEnding;
	class NyaMission;
	class NyaOpening;

	// 子オブジェクトmission関連
	class ChildMission
	{
	public:
		bool valid_;
		int index_;
		std::vector<NyaMission*> mission_collection_;
		ChildMission();
	};

	// nya window
	// H2N C++ DXLIB STG wrapper: happy 2 nya C++ DXLIB STG wrapper
	class NyaWindow
	{
	public:
		NyaWindow(std::string title);
		~NyaWindow();
		void AddChild(NyaOpening* opening);
		void AddChild(NyaMission* mission);
		void Run(void);
	private:
		eEVENT event_;
		eEVENT event_next_;
		H2NLIB::NyaEnding* ending_;
		ChildMission child_mission_;
		H2NLIB::NyaOpening* opening_;
		void Ending(void);
		void Mission(void);
		void NotSaveReplay(void);
		void Opening(void);
		void SaveReplay(void);
		void Title(void);
		void WaitFPS(int x, int y);
	};

}
