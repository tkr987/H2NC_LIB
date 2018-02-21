#pragma once


namespace H2NLIB {

	//namespace eGRAPHIC {
	//	enum NUM {
	//		TYPE1, TYPE2, TYPE3, TYPE4, TYPE5, TYPE6, TYPE7, TYPE8,
	//		TYPE1B, TYPE2B, TYPE3B, TYPE4B, TYPE5B, TYPE6B, TYPE7B, TYPE8B,
	//	};
	//};


	namespace eINPUT {
		enum NUM { 
			ENTER, UP, RIGHT, DOWN, LEFT, Q, W, E, R, SPACE, sizeof_enum, 
		};
	};


	// **********************
	//  オブジェクトの種類
	// **********************
	namespace eOBJECT {
		enum GROUP {
			enum_zero,
			TARGET1, TARGET2, TARGET3, TARGET4, TARGET5,
			TARGET_ATTACK1, TARGET_ATTACK2, TARGET_ATTACK3, TARGET_ATTACK4, TARGET_ATTACK5, 
			TARGET_ATTACK_EFFECT1, TARGET_ATTACK_EFFECT2, TARGET_ATTACK_EFFECT3, TARGET_ATTACK_EFFECT4, TARGET_ATTACK_EFFECT5, 
			TARGET_EFFECT1, TARGET_EFFECT2, TARGET_EFFECT3, TARGET_EFFECT4, TARGET_EFFECT5, 
			USER1, USER2, USER3, USER4, USER5, 
			USER_ATTACK1, USER_ATTACK2, USER_ATTACK3, USER_ATTACK4, USER_ATTACK5, 
			USER_ATTACK_EFFECT1, USER_ATTACK_EFFECT2, USER_ATTACK_EFFECT3, USER_ATTACK_EFFECT4, USER_ATTACK_EFFECT5, 
			USER_EFFECT1, USER_EFFECT2, USER_EFFECT3, USER_EFFECT4, USER_EFFECT5, 
			sizeof_enum
		};
	};

	// ************
	//  プロセス
	// ************
	namespace ePROCESS {
		enum NUM {
			enum_zero,
			TITLE, MISSION_LOAD, MISSION_RUN, MISSION_STOP, CLEAR, CONTINUE, OVER, REPLAY, 
			sizeof_enum
		};
	};

}

