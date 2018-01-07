#pragma once
#include <fstream>

namespace eKEY {
	enum TYPE { ENTER, UP, RIGHT, DOWN, LEFT, ARMS, SLOW, EXARMS, sizeof_enum };
};

namespace NH2 {

	class KeyManager {
	protected:
		static int key1_;		//çUåÇ
		static int key2_;		//ï‚èï
		static int key3_;		//ë¨ìx
		static bool flag_now_[eKEY::sizeof_enum];
		static bool flag_pre_[eKEY::sizeof_enum];
	public:
		static void Clear(void);
		static bool IsHoldKey(eKEY::TYPE type) { return (flag_pre_[type] == true && flag_now_[type] == true) ? true : false; }
		static bool IsPressKey(eKEY::TYPE type) { return (flag_pre_[type] == false && flag_now_[type] == true) ? true : false; }
		static bool GetKeyFlagNow(eKEY::TYPE type) { return flag_now_[type]; }
		static bool GetKeyFlagPre(eKEY::TYPE type) { return flag_pre_[type]; }
	};

}

