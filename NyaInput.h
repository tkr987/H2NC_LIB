#pragma once

#include <deque>
#include <sstream>
#include <string>
#include "NyaEnum.h"

namespace H2NLIB {

	class NyaInput {
	public:
		static void Run(const eEVENT check_event);
		static bool IsHoldKey(eINPUT key) { return (state_pre_[static_cast<int>(key)] == true && state_now_[static_cast<int>(key)] == true) ? true : false; }
		static bool IsPressKey(eINPUT key) { return (state_pre_[static_cast<int>(key)] == false && state_now_[static_cast<int>(key)] == true) ? true : false; }
		static bool GetKeyStateNow(eINPUT key) { return state_now_[static_cast<int>(key)]; }
		static bool GetKeyStatePre(eINPUT key) { return state_pre_[static_cast<int>(key)]; }
		static void InitRand(void);
		static void InputReplay(std::string file_name);
		static void OutputReplay(std::string file_name);
	private:
		static std::stringstream output_seed_;
		static std::stringstream output_date_;
		static std::deque<int> save_state_collection_;
		static bool state_now_[static_cast<int>(eINPUT::sizeof_enum)];
		static bool state_pre_[static_cast<int>(eINPUT::sizeof_enum)];

	};

}

