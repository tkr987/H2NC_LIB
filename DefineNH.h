#pragma once

#define ARMS_MAXSIZE								4096
#define ARMS_PARAM_RANGE_BLUE16T					4.0
#define ARMS_PARAM_RANGE_BLUE20T					6.0
#define ARMS_PARAM_RANGE_BLUE32T					12.0
#define ARMS_PARAM_RANGE_GREEN20T					6.0
#define ARMS_PARAM_RANGE_ORANGE20T					6.0
#define ARMS_PARAM_RANGE_PURPLE16T					5.0
#define ARMS_PARAM_RANGE_PURPLE20T					6.0
#define ARMS_PARAM_RANGE_RED16T						5.0
#define ARMS_PARAM_RANGE_RED20T						7.0
#define ARMS_PARAM_RANGE_RED26T						9.0
#define ARMS_PARAM_RANGE_RED30T						11.0
#define EFFECT_TOKEN_MAXSIZE						8192
// Arms Image
#define IMG_LOAD_ARMS_BLUE16T						ImgManager::LoadImg("data/10_img_arms/ArmsBlue16T.png")
#define IMG_LOAD_ARMS_BLUE20T						ImgManager::LoadImg("data/10_img_arms/ArmsBlue20T.png")
#define IMG_LOAD_ARMS_BLUE32T						ImgManager::LoadImg("data/10_img_arms/ArmsBlue32T.png")
#define IMG_LOAD_ARMS_GREEN20T						ImgManager::LoadImg("data/10_img_arms/ArmsGreen20T.png")
#define IMG_LOAD_ARMS_ORANGE20T						ImgManager::LoadImg("data/10_img_arms/ArmsOrange20T.png")
#define IMG_LOAD_ARMS_PURPLE16T						ImgManager::LoadImg("data/10_img_arms/ArmsPurple16T.png")
#define IMG_LOAD_ARMS_PURPLE20T						ImgManager::LoadImg("data/10_img_arms/ArmsPurple20T.png")
#define IMG_LOAD_ARMS_PURPLE100U					ImgManager::LoadImg("data/10_img_arms/ArmsPurple100U.png")
#define IMG_LOAD_ARMS_RED16T						ImgManager::LoadImg("data/10_img_arms/ArmsRed16T.png")
#define IMG_LOAD_ARMS_RED20T						ImgManager::LoadImg("data/10_img_arms/ArmsRed20T.png")
#define IMG_LOAD_ARMS_RED26T						ImgManager::LoadImg("data/10_img_arms/ArmsRed26T.png")
#define IMG_LOAD_ARMS_RED30T						ImgManager::LoadImg("data/10_img_arms/ArmsRed30T.png")
// Continue Image
#define IMG_LOAD_CONTINUE_NO						ImgManager::LoadImg("data/img_continue/No.png")
#define IMG_LOAD_CONTINUE_YES						ImgManager::LoadImg("data/img_continue/Yes.png")
// Design Image
#define IMG_LOAD_DESIGN_BOSS_HEALTH_BLACK			ImgManager::LoadImg("data/12_img_design/BossHealthBlack.png")
#define IMG_LOAD_DESIGN_BOSS_HEALTH_FRAME			ImgManager::LoadImg("data/12_img_design/BossHealthFrame.png")
#define IMG_LOAD_DESIGN_BOSS_HEALTH_GREEN			ImgManager::LoadImg("data/12_img_design/BossHealthGreen.png")
#define IMG_LOAD_DESIGN_BOSS_HEALTH_RED				ImgManager::LoadImg("data/12_img_design/BossHealthRed.png")
#define IMG_LOAD_DESIGN_CLOCK_DIAL					ImgManager::LoadImg("data/12_img_design/ClockDial.png")
#define IMG_LOAD_DESIGN_CLOCK_HANDS					ImgManager::LoadImg("data/12_img_design/ClockHands.png")
#define IMG_LOAD_DESIGN_CLOCK_PIN					ImgManager::LoadImg("data/12_img_design/ClockPin.png")
// Effect Image
#define IMG_LOAD_EFFECT_DEATH80						ImgManager::LoadImg(4, 2, 80, 80, "data/img_effect/Death80.png")
#define IMG_LOAD_EFFECT_DEATH120					ImgManager::LoadImg(8, 4, 120, 120, "data/img_effect/Death120.png")
#define IMG_LOAD_EFFECT_DEATH140					ImgManager::LoadImg(8, 8, 140, 140, "data/img_effect/Death140.png")
#define IMG_LOAD_EFFECT_DEATH427					ImgManager::LoadImg(8, 8, 427, 427, "data/img_effect/Death427.png")
#define IMG_LOAD_EFFECT_FLASH256					ImgManager::LoadImg(5, 4, 256, 256, "data/img_effect/Flash256.png")
// Result Image
#define IMG_LOAD_RESULT_CLEAR_STAGE					ImgManager::LoadImg(1, 3, 224, 32, "data/img_result/ClearStage.png")
#define IMG_LOAD_RESULT_SCORE_NUMBER				ImgManager::LoadImg(10, 1, 16, 32, "data/img_result/ScoreNumber.png")
#define IMG_LOAD_RESULT_SCORE_PT					ImgManager::LoadImg("data/img_result/ScorePt.png")
#define IMG_LOAD_RESULT_STAGE						ImgManager::LoadImg("data/img_result/Stage.png")
// Target Boss Image
#define IMG_LOAD_TARGET_BOSS1_MRAB					ImgManager::LoadImg(2, 1, 32, 32, "data/img_target/Boss1MRAB.png")
#define IMG_LOAD_TARGET_BOSS3_OXA48					ImgManager::LoadImg(2, 1, 32, 32, "data/img_target/Boss3OXA48.png")
#define IMG_LOAD_TARGET_BOSS4_MDRTB					ImgManager::LoadImg(6, 6, 32, 32, "data/img_target/Boss4MDRTB.png")
// Target Cristal Image
#define IMG_LOAD_TARGET_CRISTAL_GREEN120			ImgManager::LoadImg(5, 4, 120, 120, "data/img_target/CristalGreen120.png")
#define IMG_LOAD_TARGET_CRISTAL_ORANGE120			ImgManager::LoadImg(5, 4, 120, 120, "data/img_target/CristalOrange120.png")
#define IMG_LOAD_TARGET_CRISTAL_RED120				ImgManager::LoadImg(5, 4, 120, 120, "data/img_target/CristalRed120.png")
// Target Cube Image
#define IMG_LOAD_TARGET_CUBE_BLUE140				ImgManager::LoadImg(5, 1, 140, 140, "data/img_target/CubeBlue140.png")
// Target Lock Image
#define IMG_LOAD_TARGET_LOCK_CRISTAL				ImgManager::LoadImg("data/img_target/LockCristal.png")
#define IMG_LOAD_TARGET_LOCK_CUBE					ImgManager::LoadImg("data/img_target/LockCube.png")
#define IMG_LOAD_TARGET_LOCK_BOSS4_MDRTB			ImgManager::LoadImg("data/img_target/LockMDRTB.png")
#define IMG_LOAD_TARGET_LOCK_OXA48					ImgManager::LoadImg("data/img_target/LockOXA48.png")
#define IMG_LOAD_TARGET_LOCK_STAGE1_ANELLO			ImgManager::LoadImg("data/img_target/LockAnello.png")
#define IMG_LOAD_TARGET_LOCK_STAGE1_DENSO			ImgManager::LoadImg("data/img_target/LockDenso.png")
#define IMG_LOAD_TARGET_LOCK_STAGE1_ERYTHRO			ImgManager::LoadImg("data/img_target/LockErythro.png")
#define IMG_LOAD_TARGET_LOCK_STAGE1_PICORNA			ImgManager::LoadImg("data/img_target/LockPicorna.png")
#define IMG_LOAD_TARGET_LOCK_STAGE1_VIRGA			ImgManager::LoadImg("data/img_target/LockVirga.png")
#define IMG_LOAD_TARGET_LOCK_STAGE1_SIPHO			ImgManager::LoadImg("data/img_target/LockSipho.png")
#define IMG_LOAD_TARGET_LOCK_STAGE4_BORNA			ImgManager::LoadImg("data/img_target/LockBorna.png")
#define IMG_LOAD_TARGET_LOCK_STAGE4_CAULIMO			ImgManager::LoadImg("data/img_target/LockCaulimo.png")
#define IMG_LOAD_TARGET_LOCK_STAGE4_DENSO			ImgManager::LoadImg("data/img_target/LockDenso.png")
#define IMG_LOAD_TARGET_LOCK_STAGE4_HEPADNA			ImgManager::LoadImg("data/img_target/LockHepadna.png")
#define IMG_LOAD_TARGET_LOCK_STAGE4_RETRO			ImgManager::LoadImg("data/img_target/LockRetro.png")
// Target Main Image
#define IMG_LOAD_TARGET_MAIN_STAGE1_ANELLO			ImgManager::LoadImg(4, 2, 33, 24, "data/img_target/Target1Anello.png")
#define IMG_LOAD_TARGET_MAIN_STAGE1_ERYTHRO			ImgManager::LoadImg(4, 1, 57, 24, "data/img_target/Target1Erythro.png")
#define IMG_LOAD_TARGET_MAIN_STAGE1_DENSO			ImgManager::LoadImg(4, 1, 32, 32, "data/img_target/Target1Denso.png")
#define IMG_LOAD_TARGET_MAIN_STAGE1_SIPHO			ImgManager::LoadImg(8, 2, 33, 24, "data/img_target/Target1Sipho.png")
#define IMG_LOAD_TARGET_MAIN_STAGE1_PICORNA			ImgManager::LoadImg("data/img_target/Target1Picorna.png")
#define IMG_LOAD_TARGET_MAIN_STAGE1_VIRGA			ImgManager::LoadImg(5, 4, 32, 32, "data/img_target/Target1Virga.png")
#define IMG_LOAD_TARGET_MAIN_STAGE4_BORNA			ImgManager::LoadImg(3, 1, 32, 32, "data/img_target/Target4Borna.png")
#define IMG_LOAD_TARGET_MAIN_STAGE4_CAULIMO			ImgManager::LoadImg(6, 2, 32, 32, "data/img_target/Target4Caulimo.png")
#define IMG_LOAD_TARGET_MAIN_STAGE4_DENSO			ImgManager::LoadImg(4, 1, 32, 32, "data/img_target/Target4Denso.png")
#define IMG_LOAD_TARGET_MAIN_STAGE4_HEPADNA			ImgManager::LoadImg(2, 1, 32, 32, "data/img_target/Target4Hepadna.png")
#define IMG_LOAD_TARGET_MAIN_STAGE4_RETRO_L			ImgManager::LoadImg(4, 1, 32, 32, "data/img_target/Target4RetroL.png")
#define IMG_LOAD_TARGET_MAIN_STAGE4_RETRO_R			ImgManager::LoadImg(4, 1, 32, 32, "data/img_target/Target4RetroR.png")
// User Image
#define IMG_LOAD_USER_DOT							ImgManager::LoadImg("data/img_user1/dot.png")
#define IMG_LOAD_USER_EXARMS						ImgManager::LoadImg("data/img_user1/ExArms.png")
#define IMG_LOAD_USER_START							ImgManager::LoadImg("data/img_user1/Start.png")
//#define IMG_SIZEX_TARGET_ADENO						30
//#define IMG_SIZEY_TARGET_ADENO						29
#define IMG_TARGET_BOMB1_NUMX						9
#define IMG_TARGET_BOMB1_NUMY						1
#define IMG_TARGET_BOMB1_SIZEX						36
#define IMG_TARGET_BOMB1_SIZEY						36
#define IMG_TARGET_DEATH1_NUMX						9
#define IMG_TARGET_DEATH1_NUMY						1
#define IMG_TARGET_DEATH1_SIZEX						36
#define IMG_TARGET_DEATH1_SIZEY						36
#define IMG_TARGET_DEATH2_DIVNUM					8
#define IMG_TARGET_DEATH2_NUMX						4
#define IMG_TARGET_DEATH2_NUMY						2
#define IMG_TARGET_DEATH120_DIVNUM					7
#define IMG_TARGET_DEATH120_NUMX					7
#define IMG_TARGET_DEATH120_NUMY					1
#define IMG_TARGET_DEATH120_SIZEX					120
#define IMG_TARGET_DEATH120_SIZEY					120
#define IMG_SIZEX_TARGET_CUBE1						24
#define IMG_SIZEY_TARGET_CUBE1						22
#define IMG_SIZEX_TARGET_CUBE2						32
#define IMG_SIZEY_TARGET_CUBE2						29
#define IMG_SIZEX_TARGET_CUBE3						50
#define IMG_SIZEY_TARGET_CUBE3						46
#define IMG_TARGET_CUBE32_NUMX						5
#define IMG_TARGET_CUBE32_NUMY						1
#define IMG_TARGET_CUBE32_SIZEX						32
#define IMG_TARGET_CUBE32_SIZEY						32
#define IMG_TARGET_CUBE140_NUMX						5
#define IMG_TARGET_CUBE140_NUMY						1
#define IMG_TARGET_CUBE140_SIZEX					140
#define IMG_TARGET_CUBE140_SIZEY					140
#define IMG_TARGET_CUBE60_NUMX						5
#define IMG_TARGET_CUBE60_NUMY						1
#define IMG_TARGET_CUBE60_SIZEX						60
#define IMG_TARGET_CUBE60_SIZEY						55
#define INST_LOAD									1
#define INST_RUN									2
#define LV_NORMAL									1
#define LV_HARD										2
#define POS_NAME_USER_MAIN							"pos_name_user_main"
#define SOUND_LOAD_BOSS_DEATH						SoundManager::Load("data/sound/BossDeath.wav")
#define SOUND_LOAD_TARGET_DEATH2					SoundManager::Load("data/sound/TargetDeath2.wav")
#define SOUND_LOAD_TARGET_DEATH3					SoundManager::Load("data/sound/TargetDeath3.wav")
#define SOUND_LOAD_TARGET_LOCK						SoundManager::Load("data/sound/TargetLock.wav")
#define DRAW_PANEL_CENTER							384
#define DRAW_PANEL_MAX_X							608
#define DRAW_PANEL_MAX_Y							576
#define DRAW_PANEL_MIN_X							160
#define DRAW_PANEL_MIN_Y							32
#define RETURN_RESULT_RUN_END						1
#define RETURN_RESULT_RUN_OK						2

namespace eGEVENT {
	enum TYPE {
		RESULT_LOAD_STAGE1,	RESULT_LOAD_STAGE2, RESULT_LOAD_STAGE3, RESULT_LOAD_STAGE4, 
		RESULT_RUN_STAGE1,	RESULT_RUN_STAGE2, RESULT_RUN_STAGE3, RESULT_RUN_STAGE4, 
		STAGE1_NORMAL_LOAD, STAGE1_NORMAL_RUN, STAGE1_HARD_LOAD, STAGE1_HARD_RUN, STAGE1_CLEAR, STAGE1_GAME_OVER, 
		STAGE2_NORMAL_LOAD, STAGE2_NORMAL_RUN, STAGE2_HARD_LOAD, STAGE2_HARD_RUN, STAGE2_CLEAR, STAGE2_GAME_OVER, 
		STAGE3_NORMAL_LOAD, STAGE3_NORMAL_RUN, STAGE3_HARD_LOAD, STAGE3_HARD_RUN, STAGE3_CLEAR, STAGE3_GAME_OVER, 
		STAGE4_NORMAL_LOAD, STAGE4_NORMAL_RUN, STAGE4_HARD_LOAD, STAGE4_HARD_RUN, STAGE4_CLEAR, STAGE4_GAME_OVER, 
		STAGE_GAME_OVER,
		TITLE_RUN,
	};
}

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


// *****************************************
//  爆発エフェクト120 パラメータサンプル
// *****************************************
	//eparam_death_->blend_alpha_ = 255;
	//eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	//eparam_death_->extend_rate_ = 1.0;
	//eparam_death_->group_ = eOBJECT::GROUP::TARGET_EFFECT;
	//eparam_death_->img_divmax_ = 31;
	//eparam_death_->img_divmin_ = 0;
	//eparam_death_->img_id_ = imgfile_death_;
	//eparam_death_->img_interval_ = 1;

// *****************************************
//  爆発エフェクト140 パラメータサンプル
// *****************************************
	//eparam_death_->blend_alpha_ = 255;
	//eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	//eparam_death_->extend_rate_ = 1.0;
	//eparam_death_->group_ = eOBJECT::GROUP::TARGET_EFFECT;
	//eparam_death_->img_divmax_ = 63;
	//eparam_death_->img_divmin_ = 0;
	//eparam_death_->img_id_ = imgfile_death_;
	//eparam_death_->img_interval_ = 1;
