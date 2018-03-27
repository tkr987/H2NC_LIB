#pragma once

#define FPS_MAX			60
#define SCREEN_MIN_X	0
#define SCREEN_MIN_Y	0
#define SCREEN_MAX_X	850
#define SCREEN_MAX_Y	750
#define SCREEN_MIN_X	0
#define SCREEN_MIN_Y	0



namespace H2NLIB
{
	// *****************
	//  入力の種類
	// *****************
	namespace eINPUT
	{
		enum NUM
		{ 
			ENTER, UP, RIGHT, DOWN, LEFT, Q, W, E, R, SPACE, sizeof_enum, 
		};
	};


	// **********************
	//  オブジェクトの種類
	// **********************
	namespace eOBJECT
	{
		enum NUM
		{
			enum_zero,
			MAP1, MAP2, MAP3, MAP4, MAP5,  
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
	namespace ePROCESS
	{
		enum NUM
		{
			enum_zero,
			TITLE, MISSION_LOAD, MISSION_RUN, MISSION_CONTINUE, MISSION_CLEAR, MISSION_DELETE, REPLAY_SAVE, 
			sizeof_enum
		};
	};


	namespace eSKILL
	{
		enum NUM
		{
			Q, W, E, R, sizeof_enum
		};
	};

}

