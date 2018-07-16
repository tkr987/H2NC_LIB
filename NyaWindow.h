#pragma once

#include <string>
#include <vector>
#include <utility>
#include "NyaEnum.h"

namespace HNLIB
{
	class NyaEnding;
	class NyaMission;
	class NyaOpening;

	// 子オブジェクト
	class WindowChild
	{
	public:
		int mission_index_;
		NyaEnding* ending_;
		std::vector<NyaMission*> mission_collection_;
		NyaOpening* opening_;
		WindowChild();
	};

	// nya window
	// H2N C++ DXLIB STG wrapper: happy 2 nya C++ DXLIB STG wrapper
	class NyaWindow
	{
	public:
		NyaWindow(std::string title);
		~NyaWindow();
		void Child(NyaOpening* opening);
		void Child(NyaMission* mission);
		void Child(NyaEnding* ending);
		void Run(void);
	private:
		eEVENT event_;
		eEVENT event_next_;
		WindowChild child_;
		void Ending(void);
		void Mission(void);
		void NotSaveReplay(void);
		void Opening(void);
		void SaveReplay(void);
		void Title(void);
		void WaitFPS(int x, int y);
	};

}
