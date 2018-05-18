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
	enum class eINPUT
	{ 
		UP, RIGHT, DOWN, LEFT, Q, W, E, R, SPACE, ENTER, sizeof_enum, 
	};


	// **********************
	//  オブジェクトの種類
	// **********************
	enum class eOBJECT 
	{
		enum_zero,
		BACK_MAP1, BACK_MAP2, BACK_MAP3, BACK_MAP4, BACK_MAP5,  
		TARGET1, TARGET2, TARGET3, TARGET4, TARGET5,
		TARGET_ATTACK1, TARGET_ATTACK2, TARGET_ATTACK3, TARGET_ATTACK4, TARGET_ATTACK5, 
		TARGET_ATTACK_EFFECT1, TARGET_ATTACK_EFFECT2, TARGET_ATTACK_EFFECT3, TARGET_ATTACK_EFFECT4, TARGET_ATTACK_EFFECT5, 
		TARGET_EFFECT1, TARGET_EFFECT2, TARGET_EFFECT3, TARGET_EFFECT4, TARGET_EFFECT5, 
		USER1, USER2, USER3, USER4, USER5, 
		USER_ATTACK1, USER_ATTACK2, USER_ATTACK3, USER_ATTACK4, USER_ATTACK5, 
		USER_ATTACK_EFFECT1, USER_ATTACK_EFFECT2, USER_ATTACK_EFFECT3, USER_ATTACK_EFFECT4, USER_ATTACK_EFFECT5, 
		USER_EFFECT1, USER_EFFECT2, USER_EFFECT3, USER_EFFECT4, USER_EFFECT5, 
		sizeof_enum,
	};
	
	inline eOBJECT& operator++(eOBJECT& object)
	{
		if (object != eOBJECT::sizeof_enum)
			object = static_cast<eOBJECT>(static_cast<int>(object) + 1);
		
		return object;
	}


	// ************
	//  イベント
	// ************
	enum class eEVENT
	{
		enum_zero,
		TITLE, 
		MISSION_INITIALIZE, MISSION_LOAD, MISSION_RUN, MISSION_CONTINUE, MISSION_CLEAR, MISSION_ALL_CLEAR, MISSION_END, MISSION_FINALIZE, 
		MISSION_REPLAY_INITIALIZE, MISSION_REPLAY_LOAD, MISSION_REPLAY_RUN, MISSION_REPLAY_OVER, MISSION_REPLAY_CLEAR, MISSION_REPLAY_ALL_CLEAR, MISSION_REPLAY_END, MISSION_REPLAY_FINALIZE, 
		REPLAY_SAVE, 
		WINDOW_CLOSE, 
		sizeof_enum,
	};

	// ************
	//  スキル
	// ************

	enum class eSKILL
	{
			enum_zero, 
			Q, W, E, R, 
			sizeof_enum,
	};

	inline eSKILL& operator++(eSKILL& skill)
	{
		if (skill != eSKILL::sizeof_enum)
			skill = static_cast<eSKILL>(static_cast<int>(skill) + 1);
		
		return skill;
	}

}

