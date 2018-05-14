#pragma once

#include <deque>
#include <string>
#include "NyaDefine.h"


namespace H2NLIB {

	class NyaInput {
	public:
		NyaInput();
		~NyaInput();
		static void Run(const eEVENT::NUM check_event);
		static bool IsHoldKey(eINPUT::NUM key) { return (state_pre_[key] == true && state_now_[key] == true) ? true : false; }
		static bool IsPressKey(eINPUT::NUM key) { return (state_pre_[key] == false && state_now_[key] == true) ? true : false; }
		static bool GetKeyStateNow(eINPUT::NUM key) { return state_now_[key]; }
		static bool GetKeyStatePre(eINPUT::NUM key) { return state_pre_[key]; }
		static void InputFile(std::string file_name);
		static void OutputFile(std::string file_name);
	private:
		static std::deque<int> save_state_collection_;
		static bool state_now_[eINPUT::NUM::sizeof_enum];
		static bool state_pre_[eINPUT::NUM::sizeof_enum];

	};

}

