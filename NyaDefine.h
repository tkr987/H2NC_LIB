#pragma once


namespace H2NLIB {

	namespace eGRAPHIC {
		enum DRAW {
			TYPE1, TYPE2, TYPE3, TYPE4, TYPE5, TYPE6, TYPE7, TYPE8,
			TYPE1B, TYPE2B, TYPE3B, TYPE4B, TYPE5B, TYPE6B, TYPE7B, TYPE8B,
		};
	};


	namespace eINPUT {
		enum KEY { 
			ENTER, UP, RIGHT, DOWN, LEFT, Q, W, E, R, SPACE, sizeof_enum, 
		};
	};


	// ******************************************************************
	//  �I�u�W�F�N�g�̎��
	//  TARGET_READY ... �^�[�Q�b�g���W�g�[�N���p ���s�҂����
	//  TARGET_RUN ... �^�[�Q�b�g���W�g�[�N���p �������s���̏��
	// ******************************************************************
	namespace eOBJECT {
		enum GROUP {
			enum_zero,
			TITLE_MAIN, MAP_BOTTOM, STAGE_CONTINUE, STAGE_RESULT, TARGET_READY, TARGET_RUN_FLY, TARGET_RUN_WALK, 
			TARGET_EFFECT, TARGET_ARMS_EFFECT, USER, USER_EFFECT, USER_BULLET, USER_BULLET_EFFECT, 
			TARGET_ARMS_LARGE, TARGET_ARMS_SMALL, MAP_TOP, DESIGN_LAYER1, DESIGN_LAYER2, DESIGN_LAYER3, TITLE_HELP, 
			sizeof_enum
		};
	};

}

