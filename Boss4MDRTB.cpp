#include "DxLib.h"
#include "DefineNH.h"
#include "ArmsManager.h"
#include "DesignManager.h"
#include "EffectManager.h"
#include "FpsManager.h"
#include "ImgManager.h"
#include "PosManager.h"
#include "SoundManager.h"
#include "Target.h"
#include "Boss3OXA48.h"
#include "Boss4MDRTB.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace std;
using namespace NH2;
using namespace NH2T;


Boss4MDRTB::Boss4MDRTB(double y, int lv)
{	
	list<Boss4Cube*>::iterator it;

	// Y座標だけ設定しておくターゲット
	main_ = new Target(-200, y, 32);
	cristal1_[0] = new Target(-200, y - 64, 24);
	cristal1_[1] = new Target(-200, y - 64, 24);
	cristal1_[2] = new Target(-200, y - 64, 24);
	cristal1_[3] = new Target(-200, y - 64, 24);
	cristal1_[4] = new Target(-200, y - 64, 24);
	cristal1_[5] = new Target(-200, y - 64, 24);
	// 座標を後で設定するターゲット
	for (int i = 0; i < 12; i++) {
		cristalL_[i] = new Target(-200, -200, 24);
		cristalR_[i] = new Target(-200, -200, 24);
	}
	cristal2_[0] = new Target(-200, -200, 24);
	cristal2_[1] = new Target(-200, -200, 24);
	for (int i = 0; i < 16; i++)
		cristal3_[i] = new Target(-200, -200, 24);
	for (int i = 0; i < 128; i++)
		cube_wait_.push_front(new Boss4Cube);
	for (it = cube_wait_.begin(); it != cube_wait_.end(); ++it)
		(*it)->target_ = new Target(-200, -200, 24);
	// パラメータ生成
	aparam_act20_cristal_ = new ArmsParam1;
	aparam_act20_main_ = new ArmsParam1;
	aparam_act21_cristal_ = new ArmsParam1;
	aparam_act31_cube_ = new ArmsParam1;
	aparam_act43_cristal_ = new ArmsParam1;
	aparam_act43_main_ = new ArmsParam1;
	aparam_act52_cristal_ = new ArmsParam1;
	aparam_act52_main_ = new ArmsParam1;
	eparam_death_cristal_ = new EffectParam1;
	eparam_death_cube_ = new EffectParam1;
	eparam_death_main_ = new EffectParam1b;
	// 変数初期化
	action_ = 10;
	end_flag_ = false;
	health_ = 10000;
	health_max_ = 10000;
	frames_ = 0;
	lv_ = lv;
	act20_main_shot_angleL_ = -180 - 3;
	act20_main_shot_angleR_ = -180 + 3;
	act43_main_shot_angle_[0] = 90;
	act43_main_shot_angle_[1] = -90;
	// 画像ファイル
	imgdiv_cristal_ = 0;
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_blue16t_ = IMG_LOAD_ARMS_BLUE16T;
	imgfile_arms_blue32t_ = IMG_LOAD_ARMS_BLUE32T;
	imgfile_arms_green20t_ = IMG_LOAD_ARMS_GREEN20T;
	imgfile_arms_purple20t_ = IMG_LOAD_ARMS_PURPLE20T;
	imgfile_arms_red16t_ = IMG_LOAD_ARMS_RED16T;
	imgfile_arms_red20t_ = IMG_LOAD_ARMS_RED20T;
	imgfile_arms_red26t_ = IMG_LOAD_ARMS_RED26T;
	imgfile_arms_red30t_ = IMG_LOAD_ARMS_RED30T;
	imgfile_cristal_green_ = IMG_LOAD_TARGET_CRISTAL_GREEN120;
	imgfile_cristal_red_ = IMG_LOAD_TARGET_CRISTAL_RED120;
	imgfile_cube_blue_ = IMG_LOAD_TARGET_CUBE_BLUE140;
	imgfile_death_cube_ = IMG_LOAD_EFFECT_DEATH120;
	imgfile_death_cristal_ = IMG_LOAD_EFFECT_DEATH80;
	imgfile_death_main_ = IMG_LOAD_EFFECT_DEATH427;
	imgfile_main_ = IMG_LOAD_TARGET_BOSS4_MDRTB;
	imgfile_lock_cristal_ = IMG_LOAD_TARGET_LOCK_CRISTAL;
	imgfile_lock_cube_ = IMG_LOAD_TARGET_LOCK_CUBE;
	imgfile_lock_main_ = IMG_LOAD_TARGET_LOCK_BOSS4_MDRTB;
	// サウンドファイル
	soundfile_lock_ = SOUND_LOAD_TARGET_LOCK;
	soundfile_death_cristal_ = SOUND_LOAD_TARGET_DEATH2;
	soundfile_death_cube_ = SOUND_LOAD_TARGET_DEATH2;
	soundfile_death_main_ = SOUND_LOAD_BOSS_DEATH;
	// Arms Act20 Cristal 固定パラメータ
	aparam_act20_cristal_->img_angle_ = 0;
	aparam_act20_cristal_->img_id_ = imgfile_arms_red16t_;
	aparam_act20_cristal_->img_rotate_ = 0;
	aparam_act20_cristal_->shot_pow_ = 1;
	aparam_act20_cristal_->shot_range_ = ARMS_PARAM_RANGE_RED16T;
	aparam_act20_cristal_->shot_wait_ = 0;
	// Arms Act20 Main 固定パラメータ
	aparam_act20_main_->img_angle_ = 0;
	aparam_act20_main_->img_id_ = imgfile_arms_red30t_;
	aparam_act20_main_->img_rotate_ = 0;
	aparam_act20_main_->shot_pow_ = 1;
	aparam_act20_main_->shot_range_ = ARMS_PARAM_RANGE_RED30T;
	aparam_act20_main_->shot_speed_ = 12.0;
	// Arms Act21 Cristal 固定パラメータ
	aparam_act21_cristal_->img_angle_ = 0;
	aparam_act21_cristal_->img_id_ = imgfile_arms_red16t_;
	aparam_act21_cristal_->img_rotate_ = 0;
	aparam_act21_cristal_->shot_pow_ = 1;
	aparam_act21_cristal_->shot_range_ = ARMS_PARAM_RANGE_RED16T;
	aparam_act21_cristal_->shot_speed_ = 3.0;
	aparam_act21_cristal_->shot_wait_ = 0;
	// ARMS ACT31 CRISTAL 固定パラメータ
	aparam_act31_cube_->img_angle_ = 0;
	aparam_act31_cube_->img_id_ = imgfile_arms_red20t_;
	aparam_act31_cube_->img_rotate_ = 0;
	aparam_act31_cube_->shot_pow_ = 1;
	aparam_act31_cube_->shot_range_ = ARMS_PARAM_RANGE_RED20T;
	aparam_act31_cube_->shot_speed_ = 2.0;
	aparam_act31_cube_->shot_wait_ = 0;
	// Arms Act43 Cristal 固定パラメータ
	aparam_act43_cristal_->img_angle_ = 0;
	aparam_act43_cristal_->img_id_ = imgfile_arms_purple20t_;
	aparam_act43_cristal_->img_rotate_ = 0;
	aparam_act43_cristal_->shot_pow_ = 1;
	aparam_act43_cristal_->shot_range_ = ARMS_PARAM_RANGE_PURPLE20T;
	aparam_act43_cristal_->shot_speed_ = 6.0;
	// Arms Act43 Main 固定パラメータ
	aparam_act43_main_->img_angle_ = 0;
	aparam_act43_main_->img_id_ = imgfile_arms_red26t_;
	aparam_act43_main_->img_rotate_ = 0;
	aparam_act43_main_->shot_pow_ = 1;
	aparam_act43_main_->shot_range_ = ARMS_PARAM_RANGE_RED26T;
	aparam_act43_main_->shot_speed_ = 4.0;
	aparam_act43_main_->shot_wait_ = 0;
	// Arms Act52 Cristal 固定パラメータ
	aparam_act52_cristal_->img_angle_ = 0;
	aparam_act52_cristal_->img_id_ = imgfile_arms_purple20t_;
	aparam_act52_cristal_->img_rotate_ = 0;
	aparam_act52_cristal_->shot_pow_ = 1;
	aparam_act52_cristal_->shot_range_ = ARMS_PARAM_RANGE_PURPLE20T;
	aparam_act52_cristal_->shot_speed_ = 10.0;
	// Arms Act52 Cristal 固定パラメータ
	aparam_act52_main_->img_angle_ = 0;
	aparam_act52_main_->img_id_ = imgfile_arms_blue16t_;
	aparam_act52_main_->img_rotate_ = 0;
	aparam_act52_main_->shot_pow_ = 1;
	aparam_act52_main_->shot_range_ = ARMS_PARAM_RANGE_BLUE16T;
	aparam_act52_main_->shot_speed_ = 12.0;
	// DEATH CUBE エフェクト設定
	eparam_death_cube_->extend_rate_ = 1.0;
	eparam_death_cube_->group_ = eOBJECT::NUM::TARGET_EFFECT;
	eparam_death_cube_->img_divmax_ = 8;
	eparam_death_cube_->img_divmin_ = 0;
	eparam_death_cube_->img_id_ = imgfile_death_cube_;
	eparam_death_cube_->img_interval_ = 2;
	// DEATH CRISTAL エフェクト設定
	eparam_death_cristal_->extend_rate_ = 1.0;
	eparam_death_cristal_->group_ = eOBJECT::NUM::TARGET_EFFECT;
	eparam_death_cristal_->img_divmax_ = 8;
	eparam_death_cristal_->img_divmin_ = 0;
	eparam_death_cristal_->img_id_ = imgfile_death_cristal_;
	eparam_death_cristal_->img_interval_ = 2;
	// DEATH MAIN エフェクト設定
	eparam_death_main_->blend_alpha_ = 255;
	eparam_death_main_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_main_->extend_rate_ = 1.0;
	eparam_death_main_->group_ = eOBJECT::NUM::TARGET_EFFECT;
	eparam_death_main_->img_divmax_ = 64;
	eparam_death_main_->img_divmin_ = 0;
	eparam_death_main_->img_id_ = imgfile_death_main_;
	eparam_death_main_->img_interval_ = 1;
}


Boss4MDRTB::~Boss4MDRTB()
{
	list<Boss4Cube*>::iterator it;

	delete main_;
	for (int i = 0; i < 6; i++)
		delete cristal1_[i];
	for (int i = 0; i < 12; i++) {
		delete cristalL_[i];
		delete cristalR_[i];
	}
	delete cristal2_[0];
	delete cristal2_[1];
	for (int i = 0; i < 16; i++)
		delete cristal3_[i];
	for (it = cube_run_.begin(); it != cube_run_.end(); ++it) {
		delete (*it)->target_;
		delete *it;
	}
	for (it = cube_wait_.begin(); it != cube_wait_.end(); ++it) {
		delete (*it)->target_;
		delete *it;
	}
	delete aparam_act20_cristal_;
	delete aparam_act20_main_;
	delete aparam_act21_cristal_;
	delete aparam_act31_cube_;
	delete aparam_act43_cristal_;
	delete aparam_act43_main_;
	delete aparam_act52_cristal_;
	delete aparam_act52_main_;
	delete eparam_death_cube_;
	delete eparam_death_cristal_;
	delete eparam_death_main_;
}


void Boss4MDRTB::Run(void)
{
	double main_posy;
	double health_percent = (health_ / health_max_) * 100.0;
	list<Boss4Cube*>::iterator it;

	if (end_flag_)
		return;

	// ******************************************
	//  アクション分岐
	//  act 10	  ... 乱数の初期化、座標設定
	//  act 11    ... 移動
	//  act 20-22 ... 攻撃パターン１
	//  act 30-33 ... 攻撃パターン２
	//  act 40-45 ... 攻撃パターン３
	//  act 50-55 ... 攻撃パターン４
	//  act 100   ... 終了
	// ******************************************
	switch (action_) {
	case 10:
		srand(128);
		DesignManager::FlagDrawBossHealth(true);
		DesignManager::SetBossHealthColor("green");
		main_->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		for (int i = 0; i < 6; i++)
			cristal1_[i]->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		for (it = cube_wait_.begin(); it != cube_wait_.end(); ++it)
			(*it)->target_->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		for (int i = 0; i < 12; i++) {
			cristalL_[i]->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
			cristalR_[i]->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		}
		cristal2_[0]->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		cristal2_[1]->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		for (int i = 0; i < 16; i++)
			cristal3_[i]->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		Act10_SetPosition();
		action_ = 11;
		frames_ = -1;
		break;
	case 11:
		Act11_Move();
		Collision1();
		Draw1();
		main_->GetPos(NULL, &main_posy);
		if (150 < main_posy) {
			main_posy = 150;
			main_->SetPos(NULL, &main_posy);
			action_ = 20;
			frames_ = -1;
		}
		break;
	case 20:
		Act20_CristalShotHard();
		Act20_MainMove();
		Act20_MainShotHard();
		Collision1();
		Draw1();
		if (frames_ == 220 * 3 + 60 - 1) {
			action_ = 21;
			frames_ = -1;
		}
		if (health_percent < 15) {
			action_ = 22;
			frames_ = -1;
		}
		break;
	case 21:
		Act21_MainMove();
		Act21_CristalShotHard();
		Collision1();
		Draw1();
		if (frames_ == 49 || health_percent < 15) {
			action_ = 22;
			frames_ = -1;
		}
		break;
	case 22:
		Act22_Delete();
		if (15 <= health_percent) {
			action_ = 30;
			frames_ = -1;
		} else {
			action_ = 50;
			frames_ = -1;
		}
		break;
	case 30:
		Collision2();
		Draw2();
		if (frames_ == 199) {
			action_ = 31;
			frames_ = -1;
		}
		break;
	case 31:
		Act31_CubeCreate();
		Act31_CubeCreate();
		Act31_CubeDelete();
		Act31_CubeRun();
		Collision3();
		Draw3();
		if (frames_ == 749 || health_percent < 15) {
			action_ = 32;
			frames_ = -1;
		}
		break;
	case 32:
		Act32_CubeDeleteAll();
		Collision4();
		Draw4();
		action_ = 33;
		frames_ = -1;
		break;
	case 33:
		Collision4();
		Draw4();
		if (frames_ ==  399 && 15 <= health_percent) {
			action_ = 41;
			frames_ = -1;
		} else if (frames_ == 399 && health_percent < 15) {
			ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_LARGE);
			ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_SMALL);
			action_ = 50;
			frames_ = -1;
		}
		break;
	case 41:
		Act41_CristalCreate();
		Collision5();
		Draw5();
		action_ = 42;
		frames_ = -1;
		break;
	case 42:
		Act42_CristalMove();
		Collision5();
		Draw5();
		if (frames_ == (149)) {
			action_ = 43;
			frames_ = -1;
		}
		break;
	case 43:
		Act43_MainShotHard1();
		Act43_MainShotHard2();
		Act43_CristalShotHard();
		Collision6();
		Draw5();
		if (health_percent < 15) {
			ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_LARGE);
			ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_SMALL);
			action_ = 44;
			frames_ = -1;
		}
		break;
	case 44:
		Act44_CristalDelete();
		Collision7();
		action_ = 45;
		frames_ = -1;
		break;
	case 45:
		Collision7();
		Draw6();
		if (frames_ == 49) {
			action_ = 50;
			frames_ = 0;
		}
	case 50:
		Act50_CristalCreate();
		Collision8();
		Draw7();
		DesignManager::SetBossHealthColor("red");
		action_ = 51;
		frames_ = -1;
		break;
	case 51:
		Act51_CristalMove();
		Act51_MainMove();
		Collision8();
		Draw7();
		if (frames_ == 149) {
			action_ = 52;
			frames_ = -1;
		}
		break;
	case 52:
		Act52_CristalShotHard();
		Act52_CristalShotHard();
		Act52_CristalMove();
		Act52_MainShotHard(0);
		Act52_MainShotHard(90);
		Act52_MainShotHard(180);
		Act52_MainShotHard(270);
		Collision9();
		Draw7();
		if (health_ < 0) {
			ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_LARGE);
			ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_SMALL);
			action_ = 53;
			frames_ = -1;
		}
		break;
	case 53:
		Act53_Delete();
		action_ = 54;
		frames_ = -1;
		break;
	case 54:
		if (frames_ == 50) {
			ImgManager::SwingY(20, 3);
			action_ = 100;
			frames_ = -1;
		}
		break;
	case 100:
		// 終了
		break;
	default:
		break;
	}

	// *****************
	//  その他の処理
	// *****************

	// 体力表示
	DesignManager::SetBossHealth(health_percent);

	// フレーム数のカウント＆体力減少
	frames_++;
	if (frames_ % 10 == 0)
		health_ -= 2;

	// デバッグ
	#ifdef __DEBUG__
		DebugPrint::SetData(650, 300, "health_=%d", (int)(health_ / health_max_) * 100);
	#endif
}


void Boss4MDRTB::Act10_SetPosition(void)
{
	double map_center_x;
	double set_posx;

	PosManager::GetRelativeMapCenterX(&map_center_x);
	main_->SetPos(&map_center_x, NULL);

	set_posx = map_center_x - 250;
	cristal1_[0]->SetPos(&set_posx, NULL);
	set_posx = map_center_x - 150;
	cristal1_[1]->SetPos(&set_posx, NULL);
	set_posx = map_center_x - 50;
	cristal1_[2]->SetPos(&set_posx, NULL);
	set_posx = map_center_x + 50;
	cristal1_[3]->SetPos(&set_posx, NULL);
	set_posx = map_center_x + 150;
	cristal1_[4]->SetPos(&set_posx, NULL);
	set_posx = map_center_x + 250;
	cristal1_[5]->SetPos(&set_posx, NULL);
}


void Boss4MDRTB::Act11_Move(void)
{
	double move_speed = 1.5;

	main_->MoveA(NULL, &move_speed);
	for (int i = 0; i < 6; i++)
		cristal1_[i]->MoveA(NULL, &move_speed);
}


void Boss4MDRTB::Act20_CristalShotHard(void)
{
	int cristal_number;
	int rank_speed;
	int wave_max = 30;
	int wave_angle = 360 / wave_max;
	double shot_angle;

	// *****************
	//  クリスタル攻撃
	// *****************

	if (frames_ % 3 != 0)
		return;
	if (frames_ % 220 < 90 || 130 < frames_ % 220)
		return;

	cristal_number = rand() % 6;
	DesignManager::GetRank(&rank_speed);
	aparam_act20_cristal_->shot_speed_ = 7.0 + (rank_speed / 3);
	cristal1_[cristal_number]->GetPos(&aparam_act20_cristal_->shot_x_, &aparam_act20_cristal_->shot_y_);
	for (int wave = 0; wave < wave_max; wave++) {
		shot_angle = rand() % 360;
		aparam_act20_cristal_->shot_angle_ = CalcRAD(shot_angle);
		ArmsManager::TargetShotSmall(aparam_act20_cristal_);
	}
}


void Boss4MDRTB::Act20_MainMove(void)
{
	int min_x, max_x;
	int min_y, max_y;
	double movex_20f, movey_20f;
	double position_x, position_y;
	double move_speed = 1.5;

	if (frames_ % 220 == 100) {
		PosManager::GetRelativePanelMaxX(&max_x);
		PosManager::GetRelativePanelMinX(&min_x);
		PosManager::GetRelativePanelMaxY(&max_y);
		PosManager::GetRelativePanelMinY(&min_y);
		movex_20f = rand() % (max_x - min_x - 200) + min_x + 100;
		movey_20f = rand() % 100 + min_y + 100;
		main_->GetPos(&position_x, &position_y);
		act20_movex_1f_ = (movex_20f - position_x) / 20.0;
		act20_movey_1f_ = (movey_20f - position_y) / 20.0;
	}

	if (100 <= frames_ % 220 && frames_ % 220 < 120)
		main_->MoveA(&act20_movex_1f_, &act20_movey_1f_);
}


void Boss4MDRTB::Act20_MainShotHard(void)
{
	// *****************
	//  メイン攻撃
	// *****************

	if (60 < frames_ % 220)
		return;

	main_->GetPos(&aparam_act20_main_->shot_x_, &aparam_act20_main_->shot_y_);
	for (int wait = 0; wait < 30; wait += 2) {
		aparam_act20_main_->shot_wait_ = wait;
		aparam_act20_main_->shot_angle_ = main_->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, act20_main_shot_angleL_);
		ArmsManager::TargetShotSmall(aparam_act20_main_);
	}
	for (int wait = 0; wait < 30; wait += 2) {
		aparam_act20_main_->shot_wait_ = wait;
		aparam_act20_main_->shot_angle_ = main_->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, act20_main_shot_angleR_);
		ArmsManager::TargetShotSmall(aparam_act20_main_);
	}

	act20_main_shot_angleL_ -= 6;
	act20_main_shot_angleR_ += 6;
	if (frames_ % 220 == 60) {
		act20_main_shot_angleL_ = -180 - 3;
		act20_main_shot_angleR_ = -180 + 3;
	}

}


void Boss4MDRTB::Act21_CristalShotHard(void)
{
	int cristal_number;
	int rank_wave;
	int wave_max = 35;
	int wave_angle = 360 / wave_max;
	double shot_angle;

	if (frames_ % 2 != 0)
		return;

	cristal_number = rand() % 6;
	DesignManager::GetRank(&rank_wave);
	wave_max += rank_wave;
	cristal1_[cristal_number]->GetPos(&aparam_act21_cristal_->shot_x_, &aparam_act21_cristal_->shot_y_);
	for (int wave = 0; wave < wave_max; wave++) {
		shot_angle = rand() % 360;
		aparam_act21_cristal_->shot_angle_ = CalcRAD(shot_angle);
		ArmsManager::TargetShotSmall(aparam_act21_cristal_);
	}
}


void Boss4MDRTB::Act21_MainMove(void)
{
	int center_x;
	double position_x, position_y;
	double move_speed = 1.5;

	if (frames_ == 0) {
		PosManager::GetRelativeMapCenterX(&center_x);
		main_->GetPos(&position_x, &position_y);
		act21_movex_1f_ = (center_x - position_x) / 50.0;
		act21_movey_1f_ = (150 - position_y) / 50.0;
	}

	if (frames_ < 50)
		main_->MoveA(&act21_movex_1f_, &act21_movey_1f_);
}


void Boss4MDRTB::Act22_Delete(void)
{
	double add_alv		= 0.1 * 1.0;				// 加算ALV
	double add_exarms	= 2.0 * 1.0;				// 加算ExArms
	double add_rank		= 0.01 * 1.0;				// 加算ランク
	long   add_score	= (long)(1000 * 1.0);		// 加算スコア

	// エフェクト追加
	if (true) {
		for (int i = 0; i < 6; i++) {
			cristal1_[i]->GetPos(&eparam_death_cristal_->x_, &eparam_death_cristal_->y_);
			EffectManager::Create(eparam_death_cristal_);
		}
	}

	// サウンド追加
	if (true)
		SoundManager::Play(soundfile_death_cristal_, DX_PLAYTYPE_BACK);

	// 削除処理
	for (int i = 0; i < 6; i++)
		cristal1_[i]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Boss4MDRTB::Act31_CubeCreate(void)
{
	int min_x, max_x;
	double cube_x, cube_y;
	list<Boss4Cube*>::iterator it;

	if (frames_ % 10 != 0)
		return;

	if (cube_wait_.begin() == cube_wait_.end())
		return;

	it = cube_wait_.begin();
	PosManager::GetRelativeMapMinX(&min_x);
	PosManager::GetRelativeMapMaxX(&max_x);
	cube_x = rand() % (max_x - min_x - 50) + min_x;
	cube_y = -150;
	(*it)->health_ = 10.0;
	(*it)->target_->SetPos(&cube_x, &cube_y);
	cube_wait_.splice(cube_run_.begin(), cube_wait_, it);
}


void Boss4MDRTB::Act31_CubeDelete(void)
{
	double cube_x, cube_y;
	double panel_max_y;
	list<Boss4Cube*>::iterator it, delete_it;

	PosManager::GetRelativePanelMaxY(&panel_max_y);
	for (it = cube_run_.begin(); it != cube_run_.end(); ++it) {
		(*it)->target_->GetPos(&cube_x, &cube_y);
		if ((*it)->health_ <= 0) {
			eparam_death_cube_->x_ = (int)cube_x;
			eparam_death_cube_->y_ = (int)cube_y;
			EffectManager::Create(eparam_death_cube_);
			(*it)->target_->GetPos(&aparam_act31_cube_->shot_x_, &aparam_act31_cube_->shot_y_);
			Act31_CubeShot();
			cube_x = cube_y = -200;
			(*it)->target_->SetPos(&cube_x, &cube_y);
			delete_it = --it;
			cube_run_.splice(cube_wait_.begin(), cube_run_, ++delete_it);
		} else if (panel_max_y - 10 < cube_y) {
			eparam_death_cube_->x_ = (int)cube_x;
			eparam_death_cube_->y_ = (int)cube_y;
			EffectManager::Create(eparam_death_cube_);
			(*it)->target_->GetPos(&aparam_act31_cube_->shot_x_, &aparam_act31_cube_->shot_y_);
			Act31_CubeShot();
			cube_x = cube_y = -200;
			(*it)->target_->SetPos(&cube_x, &cube_y);
			delete_it = --it;
			cube_run_.splice(cube_wait_.begin(), cube_run_, ++delete_it);
		}
	}
}


void Boss4MDRTB::Act31_CubeShot(void)
{
	int rank_wave;
	int wave_max = 20;
	
	DesignManager::GetRank(&rank_wave);

	for (int wave = 0; wave < wave_max + rank_wave; wave++) {
		aparam_act31_cube_->shot_angle_ = rand() % 360;
		ArmsManager::TargetShotSmall(aparam_act31_cube_);
	}
}


void Boss4MDRTB::Act31_CubeRun(void)
{
	double damage;
	double add_y = 2.0;
	double extension = 0;
	list<Boss4Cube*>::iterator it;

	for (it = cube_run_.begin(); it != cube_run_.end(); ++it) {
		damage = (*it)->target_->Collision(extension);
		(*it)->target_->MoveA(NULL, &add_y);
		(*it)->health_ -= damage;
	}
}


void Boss4MDRTB::Act32_CubeDeleteAll(void)
{
	double add_alv		= 0.1 * 1.0;				// 加算ALV
	double add_exarms	= 2.0 * 1.0;				// 加算ExArms
	double add_rank		= 0.01 * 1.0;				// 加算ランク
	long   add_score	= (long)(1000 * 1.0);		// 加算スコア
	double cube_x, cube_y;
	list<Boss4Cube*>::iterator it;

	while (cube_run_.begin() != cube_run_.end()) {
		it = cube_run_.begin();
		(*it)->target_->GetPos(&cube_x, &cube_y);
		eparam_death_cube_->x_ = (int)cube_x;
		eparam_death_cube_->y_ = (int)cube_y;
		EffectManager::Create(eparam_death_cube_);
		(*it)->target_->GetPos(&aparam_act31_cube_->shot_x_, &aparam_act31_cube_->shot_y_);
		Act32_CubeShot();
		(*it)->target_->DeleteData(add_alv, add_exarms, add_rank, add_score);
		cube_run_.splice(cube_wait_.begin(), cube_run_, it);
	}
}


void Boss4MDRTB::Act32_CubeShot(void)
{
	int rank_wave;
	int wave_max = 15;
	
	DesignManager::GetRank(&rank_wave);

	for (int wave = 0; wave < wave_max + rank_wave; wave++) {
		aparam_act31_cube_->shot_angle_ = rand() % 360;
		ArmsManager::TargetShotSmall(aparam_act31_cube_);
	}
}


void Boss4MDRTB::Act41_CristalCreate(void)
{
	double x, y;
	double main_posx, main_posy;
	double cristal_position_x, cristal_position_y;

	main_->GetPos(&x, &y);
	x -= 150;
	y -= 200;
	cristal2_[0]->SetPos(&x, &y);
	main_->GetPos(&x, &y);
	x += 150;
	y -= 200;
	cristal2_[1]->SetPos(&x, &y);

	main_->GetPos(&main_posx, &main_posy);
	cristal2_[0]->GetPos(&cristal_position_x, &cristal_position_y);
	act42_cristal_movey_[0] = (main_posy - cristal_position_y) / 150;
	cristal2_[1]->GetPos(&cristal_position_x, &cristal_position_y);
	act42_cristal_movey_[1] = (main_posy - cristal_position_y) / 150;
}


void Boss4MDRTB::Act42_CristalMove(void)
{
	cristal2_[0]->MoveA(NULL, &act42_cristal_movey_[0]);
	cristal2_[1]->MoveA(NULL, &act42_cristal_movey_[1]);
}


void Boss4MDRTB::Act43_CristalShotHard(void)
{
	int rank_wait;

	if (frames_ % 35 != 0)
		return;

	DesignManager::GetRank(&rank_wait);
	aparam_act43_cristal_->shot_angle_ = cristal2_[0]->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
	for (int wave = 1; wave < 2; wave++) {
		aparam_act43_cristal_->shot_angle_ -= CalcRAD(3.0);
		for (int wait = 0; wait < 6 + rank_wait; wait++) {
			aparam_act43_cristal_->shot_wait_ = wait * 3;
			cristal2_[0]->GetPos(&aparam_act43_cristal_->shot_x_, &aparam_act43_cristal_->shot_y_);
			ArmsManager::TargetShotSmall(aparam_act43_cristal_);
		}
	}
	aparam_act43_cristal_->shot_angle_ = cristal2_[0]->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
	for (int wait = 0; wait < 6 + rank_wait; wait++) {
		aparam_act43_cristal_->shot_wait_ = wait * 3;
		cristal2_[0]->GetPos(&aparam_act43_cristal_->shot_x_, &aparam_act43_cristal_->shot_y_);
		ArmsManager::TargetShotSmall(aparam_act43_cristal_);
	}
	aparam_act43_cristal_->shot_angle_ = cristal2_[0]->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
	for (int wave = 1; wave < 2; wave++) {
			aparam_act43_cristal_->shot_angle_ += CalcRAD(3.0);
		for (int wait = 0; wait < 6 + rank_wait; wait++) {
			aparam_act43_cristal_->shot_wait_ = wait * 3;
			cristal2_[0]->GetPos(&aparam_act43_cristal_->shot_x_, &aparam_act43_cristal_->shot_y_);
			ArmsManager::TargetShotSmall(aparam_act43_cristal_);
		}
	}
	DesignManager::GetRank(&rank_wait);
	aparam_act43_cristal_->shot_angle_ = cristal2_[1]->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
	for (int wave = 1; wave < 2; wave++) {
		aparam_act43_cristal_->shot_angle_ -= CalcRAD(3.0);
		for (int wait = 0; wait < 6 + rank_wait; wait++) {
			aparam_act43_cristal_->shot_wait_ = wait * 3;
			cristal2_[1]->GetPos(&aparam_act43_cristal_->shot_x_, &aparam_act43_cristal_->shot_y_);
			ArmsManager::TargetShotSmall(aparam_act43_cristal_);
		}
	}
	aparam_act43_cristal_->shot_angle_ = cristal2_[1]->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
	for (int wait = 0; wait < 6 + rank_wait; wait++) {
		aparam_act43_cristal_->shot_wait_ = wait * 3;
		cristal2_[1]->GetPos(&aparam_act43_cristal_->shot_x_, &aparam_act43_cristal_->shot_y_);
		ArmsManager::TargetShotSmall(aparam_act43_cristal_);
	}
	aparam_act43_cristal_->shot_angle_ = cristal2_[1]->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
	for (int wave = 1; wave < 2; wave++) {
			aparam_act43_cristal_->shot_angle_ += CalcRAD(3.0);
		for (int wait = 0; wait < 6 + rank_wait; wait++) {
			aparam_act43_cristal_->shot_wait_ = wait * 3;
			cristal2_[1]->GetPos(&aparam_act43_cristal_->shot_x_, &aparam_act43_cristal_->shot_y_);
			ArmsManager::TargetShotSmall(aparam_act43_cristal_);
		}
	}
}


void Boss4MDRTB::Act43_MainShotHard1(void)
{
	if (frames_ % 6 != 0)
		return;

	aparam_act43_main_->shot_angle_ = CalcRAD(act43_main_shot_angle_[0]);
	for (int wave = 1; wave < 10; wave++) {
		aparam_act43_main_->shot_angle_ -= CalcRAD(6.0);
		main_->GetPos(&aparam_act43_main_->shot_x_, &aparam_act43_main_->shot_y_);
		ArmsManager::TargetShotLarge(aparam_act43_main_);
	}
	aparam_act43_main_->shot_angle_ = CalcRAD(act43_main_shot_angle_[0]);
	main_->GetPos(&aparam_act43_main_->shot_x_, &aparam_act43_main_->shot_y_);
	ArmsManager::TargetShotLarge(aparam_act43_main_);
	aparam_act43_main_->shot_angle_ = CalcRAD(act43_main_shot_angle_[0]);
	for (int wave = 1; wave < 10; wave++) {
		aparam_act43_main_->shot_angle_ += CalcRAD(6.0);
		main_->GetPos(&aparam_act43_main_->shot_x_, &aparam_act43_main_->shot_y_);
		ArmsManager::TargetShotLarge(aparam_act43_main_);
	}

	act43_main_shot_angle_[0] += 12;
}


void Boss4MDRTB::Act43_MainShotHard2(void)
{
	if (frames_ % 6 != 0)
		return;

	aparam_act43_main_->shot_angle_ = CalcRAD(act43_main_shot_angle_[1]);
	for (int wave = 1; wave < 10; wave++) {
		aparam_act43_main_->shot_angle_ -= CalcRAD(6.0);
		main_->GetPos(&aparam_act43_main_->shot_x_, &aparam_act43_main_->shot_y_);
		ArmsManager::TargetShotLarge(aparam_act43_main_);
	}
	aparam_act43_main_->shot_angle_ = CalcRAD(act43_main_shot_angle_[1]);
	main_->GetPos(&aparam_act43_main_->shot_x_, &aparam_act43_main_->shot_y_);
	ArmsManager::TargetShotLarge(aparam_act43_main_);
	aparam_act43_main_->shot_angle_ = CalcRAD(act43_main_shot_angle_[1]);
	for (int wave = 1; wave < 10; wave++) {
		aparam_act43_main_->shot_angle_ += CalcRAD(6.0);
		main_->GetPos(&aparam_act43_main_->shot_x_, &aparam_act43_main_->shot_y_);
		ArmsManager::TargetShotLarge(aparam_act43_main_);
	}

	act43_main_shot_angle_[1] += 12;
}


void Boss4MDRTB::Act44_CristalDelete(void)
{
	double add_alv		= 0.1 * 1.0;				// 加算ALV
	double add_exarms	= 2.0 * 1.0;				// 加算ExArms
	double add_rank		= 0.01 * 1.0;				// 加算ランク
	long   add_score	= (long)(1000 * 1.0);		// 加算スコア

	// エフェクト追加
	if (true) {
		cristal2_[0]->GetPos(&eparam_death_cristal_->x_, &eparam_death_cristal_->y_);
		EffectManager::Create(eparam_death_cristal_);
		cristal2_[1]->GetPos(&eparam_death_cristal_->x_, &eparam_death_cristal_->y_);
		EffectManager::Create(eparam_death_cristal_);
	}

	// サウンド追加
	if (true)
		SoundManager::Play(soundfile_death_cristal_, DX_PLAYTYPE_BACK);

	// 削除処理
	cristal2_[0]->DeleteData(add_alv, add_exarms, add_rank, add_score);
	cristal2_[1]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Boss4MDRTB::Act50_CristalCreate(void)
{
	double cristal_position_x, cristal_position_y;
	double main_position_x, main_position_y;

	main_->GetPos(&main_position_x, &main_position_y);
	for (int i = 0; i < 16; i++)
		cristal3_[i]->SetPos(&main_position_x, &main_position_y);
	cristal_position_x = main_position_x - 20;
	cristal_position_y = main_position_y - 50;
	for (int i = 0; i < 8; i++) {
		act51_cristal_movex_[i] = (cristal_position_x - main_position_x) / 150;
		act51_cristal_movey_[i] = (cristal_position_y - main_position_y) / 150;
		cristal_position_x -= 40;
	}
	cristal_position_x = main_position_x + 20;
	cristal_position_y = main_position_y - 50;
	for (int i = 0; i < 8; i++) {
		act51_cristal_movex_[i + 8] = (cristal_position_x - main_position_x) / 150;
		act51_cristal_movey_[i + 8] = (cristal_position_y - main_position_y) / 150;
		cristal_position_x += 40;
	}
}


void Boss4MDRTB::Act51_CristalMove(void)
{
	for (int i = 0; i < 16; i++)
		cristal3_[i]->MoveA(&act51_cristal_movex_[i], &act51_cristal_movey_[i]);
}


void Boss4MDRTB::Act51_MainMove(void)
{
	double main_x, main_y;
	double map_max_x, map_min_x;

	if (frames_ == 0) {
		PosManager::GetRelativeMapMaxX(&map_max_x);
		PosManager::GetRelativeMapMinX(&map_min_x);
		main_->GetPos(&main_x, &main_y);
		act51_main_movex_ = (((map_max_x - map_min_x) / 2) - main_x) / 150;
		act51_main_movey_ = (150 - main_y) / 150;
	}
	main_->MoveA(&act51_main_movex_, &act51_main_movey_);
}


void Boss4MDRTB::Act52_CristalMove(void)
{
	double cristal_position_next_x, cristal_position_next_y;
	double cristal_position_now_x, cristal_position_now_y;
	double map_max_x;
	double map_min_x;
	double panel_min_y;

	// 次の移動座標を決定
	if (frames_ % 30 == 0) {
		PosManager::GetRelativeMapMaxX(&map_max_x);
		PosManager::GetRelativeMapMinX(&map_min_x);
		PosManager::GetRelativePanelMinY(&panel_min_y);
		for (int i = 0; i < 16; i++) {
			cristal3_[i]->GetPos(&cristal_position_now_x, &cristal_position_now_y);
			cristal_position_next_x = rand() % 200 - 100 + cristal_position_now_x;
			if (cristal_position_next_x < map_min_x + 50) {
				cristal_position_next_x = map_min_x + 50;
			} else if (map_max_x - 50 < cristal_position_next_x) {
				cristal_position_next_x = map_max_x - 50;
			}
			cristal_position_next_y = rand() % 100 - 50 + cristal_position_now_y;
			if (cristal_position_next_y < panel_min_y + 25) {
				cristal_position_next_y = panel_min_y + 25;
			} else if (panel_min_y + 25 + 100 < cristal_position_next_y) {
				cristal_position_next_y = panel_min_y + 25 + 100;
			}
			act52_cristal_movex_[i] = (cristal_position_next_x - cristal_position_now_x) / 10;
			act52_cristal_movey_[i] = (cristal_position_next_y - cristal_position_now_y) / 10;
		}
	}

	// 移動処理
	if (0 <= frames_ % 30 && frames_ % 30 < 10) {
		for (int i = 0; i < 16; i++)
			cristal3_[i]->MoveA(&act52_cristal_movex_[i], &act52_cristal_movey_[i]);
	}
}

void Boss4MDRTB::Act52_CristalShotHard(void)
{
	int shot_number;
	bool used_shot_number = false;

	if (frames_ % 30 == 0)
		act52_shot_time_ = 0;
	
	if (frames_ % 30 != 10 && frames_ % 30 != 12 && frames_ % 30 != 14 && frames_ % 30 != 16)
		return;

	shot_number = rand() % 16;
	act52_shot_number_stack_[act52_shot_time_] = shot_number;
	for (int i = 0; i < act52_shot_time_; i++) {
		if (shot_number == act52_shot_number_stack_[i])
			used_shot_number = true;
	}
	if (!used_shot_number) {
		aparam_act52_cristal_->shot_angle_ = cristal3_[shot_number]->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
		for (int wait = 0; wait < 6; wait++) {
			aparam_act52_cristal_->shot_wait_ = wait * 2;
			cristal3_[shot_number]->GetPos(&aparam_act52_cristal_->shot_x_, &aparam_act52_cristal_->shot_y_);
			ArmsManager::TargetShotSmall(aparam_act52_cristal_);
		}
	}

	act52_shot_time_++;
}


void Boss4MDRTB::Act52_MainShotHard(double base_angle)
{
	double angle;
	int rank_freq;

	DesignManager::GetRank(&rank_freq);
	if (frames_ % (5 - rank_freq) != 0)
		return;

	angle = rand() % 90 + base_angle;
	for (int wait = 0; wait < 5; wait++) {
		main_->GetPos(&aparam_act52_main_->shot_x_, &aparam_act52_main_->shot_y_);
		aparam_act52_main_->shot_angle_ = CalcRAD(angle);
		aparam_act52_main_->shot_x_ -= (10 * cos(CalcRAD(angle + 90)));
		aparam_act52_main_->shot_y_ -= (10 * sin(CalcRAD(angle + 90)));
		aparam_act52_main_->shot_wait_ = wait;
		ArmsManager::TargetShotSmall(aparam_act52_main_);
		main_->GetPos(&aparam_act52_main_->shot_x_, &aparam_act52_main_->shot_y_);
		aparam_act52_main_->shot_angle_ = CalcRAD(angle);
		aparam_act52_main_->shot_wait_ = wait;
		ArmsManager::TargetShotSmall(aparam_act52_main_);
		main_->GetPos(&aparam_act52_main_->shot_x_, &aparam_act52_main_->shot_y_);
		aparam_act52_main_->shot_angle_ = CalcRAD(angle);
		aparam_act52_main_->shot_x_ += (10 * cos(CalcRAD(angle + 90)));
		aparam_act52_main_->shot_y_ += (10 * sin(CalcRAD(angle + 90)));
		aparam_act52_main_->shot_wait_ = wait;
		ArmsManager::TargetShotSmall(aparam_act52_main_);
	}
}


void Boss4MDRTB::Act53_Delete(void)
{
	double add_alv		= 0.1 * 1.0;				// 加算ALV
	double add_exarms	= 2.0 * 1.0;				// 加算ExArms
	double add_rank		= 0.01 * 1.0;				// 加算ランク
	long   add_score	= (long)(1000 * 1.0);		// 加算スコア

	// エフェクト追加
	if (true) {
		for (int i = 0; i < 16; i++) {
			cristal3_[i]->GetPos(&eparam_death_cristal_->x_, &eparam_death_cristal_->y_);
			EffectManager::Create(eparam_death_cristal_);
		}
		main_->GetPos(&eparam_death_main_->x_, &eparam_death_main_->y_);
		EffectManager::Create(eparam_death_main_);
	}

	// サウンド追加
	if (true) {
		SoundManager::Play(soundfile_death_cristal_, DX_PLAYTYPE_BACK);
		SoundManager::Play(soundfile_death_main_, DX_PLAYTYPE_BACK);
	}

	// 削除処理
	for (int i = 0; i < 16; i++) 
		cristal3_[i]->DeleteData(add_alv, add_exarms, add_rank, add_score);
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
}



void Boss4MDRTB::Collision1(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	main_->CollisionImg(imgfile_lock_main_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += main_->Collision(extension);
	for (int i = 0; i < 7; i++) {
		cristal1_[i]->CollisionImg(imgfile_lock_cristal_, 0, interval);
		cristal1_[i]->CollisionSound(soundfile_lock_, interval);
		damage += cristal1_[i]->Collision(extension);
	}
	DesignManager::AddScore(damage);
	health_ -= damage * 3;
}


void Boss4MDRTB::Collision2(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	main_->CollisionImg(imgfile_lock_main_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += main_->Collision(extension);
	DesignManager::AddScore(damage);
//	health_ -= damage;
}


void Boss4MDRTB::Collision3(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間
	list<Boss4Cube*>::iterator it;

	main_->CollisionImg(imgfile_lock_main_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage = main_->Collision(extension);
	DesignManager::AddScore(damage);
	health_ -= damage;


	for (it = cube_run_.begin(); it != cube_run_.end(); ++it) {
		(*it)->target_->CollisionImg(imgfile_lock_cube_, 0, interval);
		(*it)->target_->CollisionSound(soundfile_lock_, interval);
		damage = (*it)->target_->Collision(extension);
		DesignManager::AddScore(damage);
		health_ -= damage * 3;
	}
}


void Boss4MDRTB::Collision4(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間
	list<Boss4Cube*>::iterator it;

	main_->CollisionImg(imgfile_lock_main_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage = main_->Collision(extension);
	DesignManager::AddScore(damage);
//	health_ -= damage;
}


void Boss4MDRTB::Collision5(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	main_->CollisionImg(imgfile_lock_main_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += main_->Collision(extension);
	cristal2_[0]->CollisionImg(imgfile_lock_cristal_, 0, interval);
	cristal2_[0]->CollisionSound(soundfile_lock_, interval);
	damage += cristal2_[0]->Collision(extension);
	cristal2_[1]->CollisionImg(imgfile_lock_cristal_, 0, interval);
	cristal2_[1]->CollisionSound(soundfile_lock_, interval);
	damage += cristal2_[1]->Collision(extension);
	DesignManager::AddScore(damage);
//	health_ -= damage * 3;
}


void Boss4MDRTB::Collision6(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	main_->CollisionImg(imgfile_lock_main_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += main_->Collision(extension);
	cristal2_[0]->CollisionImg(imgfile_lock_cristal_, 0, interval);
	cristal2_[0]->CollisionSound(soundfile_lock_, interval);
	damage += cristal2_[0]->Collision(extension);
	cristal2_[1]->CollisionImg(imgfile_lock_cristal_, 0, interval);
	cristal2_[1]->CollisionSound(soundfile_lock_, interval);
	damage += cristal2_[1]->Collision(extension);
	DesignManager::AddScore(damage);
	health_ -= damage * 3;
}


void Boss4MDRTB::Collision7(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間
	list<Boss4Cube*>::iterator it;

	main_->CollisionImg(imgfile_lock_main_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage = main_->Collision(extension);
	DesignManager::AddScore(damage);
//	health_ -= damage;
}


void Boss4MDRTB::Collision8(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	main_->CollisionImg(imgfile_lock_main_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += main_->Collision(extension);
	for (int i = 0; i < 16; i++) {
		cristal3_[i]->CollisionImg(imgfile_lock_cristal_, 0, interval);
		cristal3_[i]->CollisionSound(soundfile_lock_, interval);
		damage += cristal3_[i]->Collision(extension);
	}
	DesignManager::AddScore(damage);
//	health_ -= damage;
}


void Boss4MDRTB::Collision9(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	main_->CollisionImg(imgfile_lock_main_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += main_->Collision(extension);
	for (int i = 0; i < 16; i++) {
		cristal3_[i]->CollisionImg(imgfile_lock_cristal_, 0, interval);
		cristal3_[i]->CollisionSound(soundfile_lock_, interval);
		damage += cristal3_[i]->Collision(extension);
	}
	DesignManager::AddScore(damage);
	health_ -= damage;
}



void Boss4MDRTB::Draw1(void)
{
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 36;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cristal_ = ++imgdiv_cristal_ % 20;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);
	for (int i = 0; i < 6; i++)
		cristal1_[i]->Draw(imgfile_cristal_red_, imgdiv_cristal_, 0.5, 0);
}


void Boss4MDRTB::Draw2(void)
{
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 36;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);
}


void Boss4MDRTB::Draw3(void)
{
	list<Boss4Cube*>::iterator it;

	if (FpsManager::GetInterval(4) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 36;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cube_ = ++imgdiv_cube_ % 5;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);

	for (it = cube_run_.begin(); it != cube_run_.end(); ++it)
		(*it)->target_->Draw(imgfile_cube_blue_, imgdiv_cube_, 0.4, 0);
}


void Boss4MDRTB::Draw4(void)
{
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 36;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);
}


void Boss4MDRTB::Draw5(void)
{
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 36;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cristal_ = ++imgdiv_cristal_ % 20;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);
	cristal2_[0]->Draw(imgfile_cristal_red_, imgdiv_cristal_, 0.5, 0);
	cristal2_[1]->Draw(imgfile_cristal_red_, imgdiv_cristal_, 0.5, 0);
}


void Boss4MDRTB::Draw6(void)
{
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 36;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);
}


void Boss4MDRTB::Draw7(void)
{
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 36;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cristal_ = ++imgdiv_cristal_ % 20;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);
	for (int i = 0; i < 16; i++)
		cristal3_[i]->Draw(imgfile_cristal_red_, imgdiv_cristal_, 0.5, 0);
}
