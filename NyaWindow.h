#pragma once
#include <array>
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

	class WindowFPS
	{
	public:
		int frame_average_time_;
		int frame_count_;
		std::array<int, FPS_MAX> frame_time_collection_;
		int prev_time_;
		int wait_time_;
	};

	class WindowFPS2
	{
	public:
		LONGLONG frame_average_time_;
		int frame_count_;
		std::array<LONGLONG, FPS_MAX> frame_time_collection_;
		LONGLONG prev_time_;
		LONGLONG wait_time_;
	};

	class WindowReplay
	{
	public:
		std::string date_;
		bool existed_file_;
		bool new_file_;
		std::string seed_;
		std::string title_;
		WindowReplay();
		void Clear(void);
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
		WindowFPS fps_;
		WindowFPS2 fps2_;
		std::array<WindowReplay, 4> replay_collection_;
		void Ending(void);
		void Mission(void);
		void NotSaveReplay(void);
		void Opening(void);
		void SaveReplay(void);
		void Title(void);
		void WaitFPS(int x, int y);
		void WaitFPS2(int x, int y);
	};

}
