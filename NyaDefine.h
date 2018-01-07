#pragma once


// ******************************************************************
//  オブジェクトの種類
//  TARGET_READY ... ターゲット座標トークン用 実行待ち状態
//  TARGET_RUN ... ターゲット座標トークン用 処理実行中の状態
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
