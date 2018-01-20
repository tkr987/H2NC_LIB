#pragma once

#include "NyaDefine.h"


namespace H2NLIB {

	class NyaInput {
	public:
		NyaInput();
		~NyaInput();
		static void Run(void);
		static bool IsHoldKey(eINPUT::KEY key) { return (flag_pre_[key] == true && flag_now_[key] == true) ? true : false; }
		static bool IsPressKey(eINPUT::KEY key) { return (flag_pre_[key] == false && flag_now_[key] == true) ? true : false; }
		static bool GetKeyFlagNow(eINPUT::KEY key) { return flag_now_[key]; }
		static bool GetKeyFlagPre(eINPUT::KEY key) { return flag_pre_[key]; }
	private:
		static bool flag_now_[eINPUT::KEY::sizeof_enum];
		static bool flag_pre_[eINPUT::KEY::sizeof_enum];
	};

}

