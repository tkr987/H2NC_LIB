#pragma once


// ******************************************************************
//  �I�u�W�F�N�g�̎��
//  TARGET_READY ... �^�[�Q�b�g���W�g�[�N���p ���s�҂����
//  TARGET_RUN ... �^�[�Q�b�g���W�g�[�N���p �������s���̏��
// ******************************************************************
namespace eOBJECT {
	enum GROUP {
		enum_zero,
		TITLE_MAIN, MAP_BOTTOM, STAGE_CONTINUE, STAGE_RESULT, TARGET_READY, TARGET_RUN_FLY, TARGET_RUN_WALK, 
		TARGET_EFFECT, TARGET_ARMS_EFFECT, USER, USER_EFFECT, USER_ARMS, USER_ARMS_EFFECT, 
		TARGET_ARMS_LARGE, TARGET_ARMS_SMALL, MAP_TOP, DESIGN_LAYER1, DESIGN_LAYER2, DESIGN_LAYER3, TITLE_HELP, 
		sizeof_enum
	};
};
