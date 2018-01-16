#pragma once

#include "NyaDefine.h"


namespace H2NLIB {

	class NyaInput {
	public:
		NyaInput();
		~NyaInput();
		void Run(void);
		bool IsHoldKey(eINPUT::KEY key) { return (flag_pre_[key] == true && flag_now_[key] == true) ? true : false; }
		bool IsPressKey(eINPUT::KEY key) { return (flag_pre_[key] == false && flag_now_[key] == true) ? true : false; }
		bool GetKeyFlagNow(eINPUT::KEY key) { return flag_now_[key]; }
		bool GetKeyFlagPre(eINPUT::KEY key) { return flag_pre_[key]; }
	private:
		static bool flag_now_[eINPUT::KEY::sizeof_enum];
		static bool flag_pre_[eINPUT::KEY::sizeof_enum];
	};

}

