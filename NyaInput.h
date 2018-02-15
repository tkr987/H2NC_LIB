#pragma once

#include "NyaDefine.h"


namespace H2NLIB {

	class NyaInput {
	public:
		NyaInput();
		~NyaInput();
		static void Run(void);
		static bool IsHoldKey(eINPUT::NUM key) { return (flag_pre_[key] == true && flag_now_[key] == true) ? true : false; }
		static bool IsPressKey(eINPUT::NUM key) { return (flag_pre_[key] == false && flag_now_[key] == true) ? true : false; }
		static bool GetKeyFlagNow(eINPUT::NUM key) { return flag_now_[key]; }
		static bool GetKeyFlagPre(eINPUT::NUM key) { return flag_pre_[key]; }
	private:
		static bool flag_now_[eINPUT::NUM::sizeof_enum];
		static bool flag_pre_[eINPUT::NUM::sizeof_enum];
	};

}

