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
#include "DebugPrint.h"

//#define __DEBUG__

using namespace NH2;
using namespace NH2T;


Boss3OXA48::Boss3OXA48(double y, int lv)
{	
	// Y座標だけ設定しておく
	main_ = new Target(-100, y, 32);
	cristal_[0] = new Target(-100, y - 70, 24);
	cristal_[1] = new Target(-100, y - 40, 24);
	cristal_[2] = new Target(-100, y - 65, 24);
	cristal_[3] = new Target(-100, y - 50, 24);
	cristal_[4] = new Target(-100, y - 10, 24);
	cristal_[5] = new Target(-100, y - 30, 24);
	cristal_[6] = new Target(-100, y - 30, 24);
	cristal_[7] = new Target(-100, y - 10, 24);
	cristal_[8] = new Target(-100, y - 50, 24);
	cristal_[9] = new Target(-100, y - 65, 24);
	cristal_[10] = new Target(-100, y - 40, 24);
	cristal_[11] = new Target(-100, y - 70, 24);
	cristal2_[0] = new Target(-100, -100, 24);
	cristal2_[1] = new Target(-100, -100, 24);
	aparam_act1_cristal_ = new ArmsParam1;
	aparam_act1_main_ = new ArmsParam1;
	aparam_act3_cristal_ = new ArmsParam1;
	aparam_act4_cristal_ = new ArmsParam1;
	aparam_act6_cristal_ = new ArmsParam1;
	aparam_act6_main_ = new ArmsParam1;
	aparam_act11_cristal_ = new ArmsParam1;
	eparam_death_cristal_ = new EffectParam1;
	eparam_death_main_ = new EffectParam1b;
	// 変数初期化
	action_ = 0;
	end_flag_ = false;
	health_ = 800;
	health_max_ = 800;
	frames_ = 0;
	lv_ = lv;
	act1_shot1_angleL_ = 90;
	act1_shot1_angleR_ = 90;
	act1_shot2_angleL_ = 90;
	act1_shot2_angleR_ = 90;
	act3_move_angle_ = 0;
	// 画像ファイル
	imgdiv_cristal_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_blue16t_ = IMG_LOAD_ARMS_BLUE16T;
	imgfile_arms_blue32t_ = IMG_LOAD_ARMS_BLUE32T;
	imgfile_arms_red20t_ = IMG_LOAD_ARMS_RED20T;
	imgfile_cristal_red_ = IMG_LOAD_TARGET_CRISTAL_RED120;
	imgfile_cristal_lock_ = IMG_LOAD_TARGET_LOCK_CRISTAL;
	imgfile_death_cristal_ = IMG_LOAD_EFFECT_DEATH80;
	imgfile_death_main_ = IMG_LOAD_EFFECT_DEATH427;
	imgfile_main_ = IMG_LOAD_TARGET_BOSS3_OXA48;
	imgfile_main_lock_ = IMG_LOAD_TARGET_LOCK_OXA48;
	// サウンドファイル
	soundfile_lock_ = SoundManager::Load("data/sound/target_lock.wav");
	soundfile_death_cristal_ = SoundManager::Load("data/sound/TargetDeath2.wav");
	// ARMS ACT1 CRISTAL 固定パラメータ
	aparam_act1_cristal_->img_angle_ = 0;
	aparam_act1_cristal_->img_id_ = imgfile_arms_red20t_;
	aparam_act1_cristal_->img_rotate_ = 0;
	aparam_act1_cristal_->shot_pow_ = 1;
	aparam_act1_cristal_->shot_range_ = ARMS_PARAM_RANGE_RED20T;
	// ARMS ACT1 MAIN 固定パラメータ
	aparam_act1_main_->img_angle_ = 0;
	aparam_act1_main_->img_id_ = imgfile_arms_blue32t_;
	aparam_act1_main_->img_rotate_ = 0;
	aparam_act1_main_->shot_pow_ = 1;
	aparam_act1_main_->shot_range_ = ARMS_PARAM_RANGE_BLUE32T;
	aparam_act1_main_->shot_speed_ = 3.0;
	aparam_act1_main_->shot_wait_ = 0;
	// ARMS ACT3 CRISTAL 固定パラメータ
	aparam_act3_cristal_->img_angle_ = 0;
	aparam_act3_cristal_->img_id_ = imgfile_arms_red20t_;
	aparam_act3_cristal_->img_rotate_ = 0;
	aparam_act3_cristal_->shot_pow_ = 1;
	aparam_act3_cristal_->shot_range_ = ARMS_PARAM_RANGE_RED20T;
	aparam_act3_cristal_->shot_wait_ = 0;
	// ARMS ACT4 CRISTAL 固定パラメータ
	aparam_act4_cristal_->img_angle_ = 0;
	aparam_act4_cristal_->img_id_ = imgfile_arms_red20t_;
	aparam_act4_cristal_->img_rotate_ = 0;
	aparam_act4_cristal_->shot_pow_ = 1;
	aparam_act4_cristal_->shot_range_ = ARMS_PARAM_RANGE_RED20T;
	aparam_act4_cristal_->shot_wait_ = 0;
	// ARMS ACT6 CRISTAL 固定パラメータ
	aparam_act6_cristal_->img_angle_ = 0;
	aparam_act6_cristal_->img_id_ = imgfile_arms_red20t_;
	aparam_act6_cristal_->img_rotate_ = 0;
	aparam_act6_cristal_->shot_pow_ = 1;
	aparam_act6_cristal_->shot_range_ = ARMS_PARAM_RANGE_RED20T;
	aparam_act6_cristal_->shot_wait_ = 0;
	// ARMS ACT6 MAIN 固定パラメータ
	aparam_act6_main_->img_angle_ = 0;
	aparam_act6_main_->img_id_ = imgfile_arms_blue16t_;
	aparam_act6_main_->img_rotate_ = 0;
	aparam_act6_main_->shot_pow_ = 1;
	aparam_act6_main_->shot_range_ = ARMS_PARAM_RANGE_BLUE16T;
	aparam_act6_main_->shot_wait_ = 0;
	// ARMS ACT11 CRISTAL 固定パラメータ
	aparam_act11_cristal_->img_angle_ = 0;
	aparam_act11_cristal_->img_id_ = imgfile_arms_blue16t_;
	aparam_act11_cristal_->img_rotate_ = 0;
	aparam_act11_cristal_->shot_pow_ = 1;
	aparam_act11_cristal_->shot_range_ = ARMS_PARAM_RANGE_BLUE16T;
	aparam_act11_cristal_->shot_wait_ = 0;
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
	// その他 設定
	DesignManager::SetBossHealth(100);
}

Boss3OXA48::~Boss3OXA48()
{
	delete main_;
	for (int i = 0; i < 12; i++)
		delete cristal_[i];
	for (int i = 0; i < 2; i++)
		delete cristal2_[i];
	delete aparam_act1_cristal_;
	delete aparam_act1_main_;
	delete aparam_act3_cristal_;
	delete aparam_act4_cristal_;
	delete aparam_act6_cristal_;
	delete aparam_act6_main_;
	delete aparam_act11_cristal_;
	delete eparam_death_cristal_;
	delete eparam_death_main_;
}


void Boss3OXA48::Run(void)
{
	double panel_center_x;
	double cristal_posx, cristal_posy;
	double main_posy, main_posx;
	double health_percent = (health_ / health_max_) * 100.0;

	if (end_flag_)
		return;

#ifdef __DEBUG__
	DebugPrint::SetData(650, 300, "health_=%d", (int)(health_ / health_max_) * 100);
#endif

	// ******************************************
	//  アクション分岐
	//  act 0	 ... 乱数の初期化、座標設定
	//  act 1    ... 移動
	//  act 2	 ... 攻撃パターン１
	//  act 3-5	 ... 攻撃パターン２
	//  act 6-8  ... 攻撃パターン３
	//  act 9-12 ... 攻撃パターン４
	//  act 100  ... 終了
	// ******************************************
	switch (action_) {
	case 0:
		srand(48);
		DesignManager::FlagDrawBossHealth(true);
		main_->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		for (int i = 0; i < 12; i++)
			cristal_[i]->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		Act0_SetPosition();
		action_ = 1;
		break;
	case 1:
		Act1_Move();
		main_->GetPos(NULL, &main_posy);
		if (150 < main_posy) {
			main_posy = 150;
			main_->SetPos(NULL, &main_posy);
			action_ = 2;
			frames_ = 0;
		}
		break;
	case 2:
		Act2_ShotHard1();
		Act2_ShotHard2();
		Act2_ShotHard3();
		if (frames_ == 400) {
			action_ = 3;
			frames_ = 0;
		}
		break;
	case 3:
		if (frames_ == 150) {
			action_ = 4;
			frames_ = 0;
		}
		break;
	case 4:
		Act4_ShotHard();
		if (frames_ == 300) {
			action_ = 5;
			frames_ = 0;
		}
		break;
	case 5:
		Act5_ShotHard();
		if (frames_ == 40) {
			main_->GetPos(&main_posx, &main_posy);
			PosManager::GetRelativePanelCenterX(&panel_center_x);
			act5_main_movex_ = (panel_center_x - main_posx) / 150.0;
			for (int i = 0; i < 6; i++) {
				cristal_[i]->GetPos(&cristal_posx, &cristal_posy);
				act5_cristal_movex_[i] = (panel_center_x + 30 - i * 60 - cristal_posx) / 150.0;
				act5_cristal_movey_[i] = (main_posy + 100 - cristal_posy) / 150.0;
			}
			for (int i = 6; i < 12; i++) {
				cristal_[i]->GetPos(&cristal_posx, &cristal_posy);
				act5_cristal_movex_[i] = (panel_center_x - 30 + (i - 6) * 60 - cristal_posx) / 150.0;
				act5_cristal_movey_[i] = (main_posy + 100 - cristal_posy) / 150.0;
			}
			action_ = 6;
			frames_ = 0;
		}
		break;
	case 6:
		Act6_Move();
		if (frames_ == 150) {
			action_ = 7;
			frames_ = 0;
		}
		break;
	case 7:
		Act7_ShotHard1();
		Act7_ShotHard2();
		Act7_ShotHard3();
		Act7_Move();
		if (frames_ == 800) {
			PosManager::GetRelativePanelCenterX(&panel_center_x);
			main_->GetPos(&main_posx, &main_posy);
			act7_main_movex_ = (panel_center_x - main_posx) / 150.0;
			cristal_[0]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[0] = (panel_center_x - 255.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[0] = (main_posy - 70.0 - cristal_posy) / 150.0;
			cristal_[1]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[1] = (panel_center_x - 220.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[1] = (main_posy - 40.0 - cristal_posy) / 150.0;
			cristal_[2]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[2] = (panel_center_x - 180.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[2] = (main_posy - 65.0 - cristal_posy) / 150.0;
			cristal_[3]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[3] = (panel_center_x - 130.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[3] = (main_posy - 50.0 - cristal_posy) / 150.0;
			cristal_[4]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[4] = (panel_center_x - 100.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[4] = (main_posy - 10.0 - cristal_posy) / 150.0;
			cristal_[5]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[5] = (panel_center_x - 50.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[5] = (main_posy - 30.0 - cristal_posy) / 150.0;
			cristal_[6]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[6] = (panel_center_x + 50.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[6] = (main_posy - 30.0 - cristal_posy) / 150.0;
			cristal_[7]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[7] = (panel_center_x + 100.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[7] = (main_posy - 10.0 - cristal_posy) / 150.0;
			cristal_[8]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[8] = (panel_center_x + 130.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[8] = (main_posy - 50.0 - cristal_posy) / 150.0;
			cristal_[9]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[9] = (panel_center_x + 180.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[9] = (main_posy - 65.0 - cristal_posy) / 150.0;
			cristal_[10]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[10] = (panel_center_x + 220.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[10] = (main_posy - 40.0 - cristal_posy) / 150.0;
			cristal_[11]->GetPos(&cristal_posx, &cristal_posy);
			act7_cristal_movex_[11] = (panel_center_x + 255.0 - cristal_posx) / 150.0;
			act7_cristal_movey_[11] = (main_posy - 70.0 - cristal_posy) / 150.0;
			action_ = 8;
			frames_ = 0;
		}
		break;
	case 8:
		Act8_Move();
		if (frames_ == 150) {
			action_ = 2;
			frames_ = 0;
		}
		break;
	case 9:
		main_->MoveA(&act8_main_movex_, NULL);
		if (frames_ == 150) {
			action_ = 10;
			frames_ = 0;
		}
		break;
	case 10:
		main_->GetPos(&main_posx, &main_posy);
		cristal_posx = main_posx;
		cristal_posy = main_posy;
		cristal2_[0]->SetPos(&cristal_posx, &cristal_posy);
		cristal2_[1]->SetPos(&cristal_posx, &cristal_posy);
		cristal2_[0]->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		cristal2_[1]->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		act10_cristal2_movex_[0] = (panel_center_x + 200 - cristal_posx) / 150.0;
		act10_cristal2_movex_[1] = (panel_center_x - 200 - cristal_posx) / 150.0;
		action_ = 11;
		frames_ = 0;
		break;
	case 11:
		cristal2_[0]->MoveA(&act10_cristal2_movex_[0], NULL);
		cristal2_[1]->MoveA(&act10_cristal2_movex_[1], NULL);
		if (frames_ == 150) {
			action_ = 12;
			frames_ = 0;
		}
		break;
	case 12:
		Act12_ShotHard1();
		Act12_ShotHard1();
		Act12_ShotHard2();
		Act12_ShotHard2();
		break;
	case 100:
		break;
	default:
		break;
	}


	// *****************
	//  その他の処理
	// *****************

	// 体力表示
	DesignManager::SetBossHealth(health_percent);
	if (health_percent < 15) {
		DesignManager::SetBossHealthColor("red");
	} else {
		DesignManager::SetBossHealthColor("green");
	}
	// 体力30% クリスタル爆発処理
	if (action_ < 9 && health_percent < 30) {
		DeleteCristal(1.0, true, true);
		ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_SMALL);
		ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_LARGE);
		main_->GetPos(&main_posx, &main_posy);
		PosManager::GetRelativePanelCenterX(&panel_center_x);
		act8_main_movex_ = (panel_center_x - main_posx) / 150.0;
		action_ = 9;
		frames_ = 0;
	}
	// 体力0% メイン爆発処理 クリスタル爆発処理
	if (health_percent < 0) {
		DeleteMain(1.0, true, true);
		DeleteCristal2(1.0, true, true);
		ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_SMALL);
		ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_LARGE);
		DesignManager::FlagDrawBossHealth(false);
		action_ = 100;
		frames_ = 0;
		end_flag_ = true;
	}
	// 描画＆衝突判定
	if (30 <= health_percent) {
		Collision1();
		Draw1();
	} else if (0 < health_percent && health_percent < 30){
		Collision2();
		Draw2();
	}
	// フレーム数のカウント＆体力減少
	frames_++;
	if (frames_ % 10 == 0)
		health_ -= 2;
}

void Boss3OXA48::Act0_SetPosition(void)
{
	double panel_center_x;
	double set_posx;

	PosManager::GetRelativePanelCenterX(&panel_center_x);
	main_->SetPos(&panel_center_x, NULL);

	set_posx = panel_center_x - 255;
	cristal_[0]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x - 220;
	cristal_[1]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x - 180;
	cristal_[2]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x - 130;
	cristal_[3]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x - 100;
	cristal_[4]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x - 50;
	cristal_[5]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x + 50;
	cristal_[6]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x + 100;
	cristal_[7]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x + 130;
	cristal_[8]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x + 180;
	cristal_[9]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x + 220;
	cristal_[10]->SetPos(&set_posx, NULL);
	set_posx = panel_center_x + 255;
	cristal_[11]->SetPos(&set_posx, NULL);
}

void Boss3OXA48::Act1_Move(void)
{
	double move_speed = 1.5;

	main_->MoveA(NULL, &move_speed);
	for (int i = 0; i < 12; i++)
		cristal_[i]->MoveA(NULL, &move_speed);
}


void Boss3OXA48::Act2_ShotHard1(void)
{
	int rank_num;
	int rank_speed;
	int wave_max = 7;
	int wave_angle = 360 / wave_max;

	// *****************
	//  クリスタル攻撃
	// *****************


	if (frames_ % 40 != 0)
		return;
	DesignManager::GetRank(&rank_num);
	rank_num = rank_num / 3;
	DesignManager::GetRank(&rank_speed);
	aparam_act1_cristal_->shot_speed_ = 8.0 + (rank_speed / 3);
	for (int i = 3; i < 6; i++) {
		cristal_[i]->GetPos(&aparam_act1_cristal_->shot_x_, &aparam_act1_cristal_->shot_y_);
		for (int wave = 0; wave < wave_max; wave++) {
			for (int wait = 0; wait < 12 + rank_num; wait += 2) {
				aparam_act1_cristal_->shot_wait_ = wait;
				aparam_act1_cristal_->shot_angle_ = CalcRAD(act1_shot1_angleL_ + wave * wave_angle);
				ArmsManager::TargetShotSmall(aparam_act1_cristal_);
			}
		}
	}
	for (int i = 6; i < 9; i++) {
		cristal_[i]->GetPos(&aparam_act1_cristal_->shot_x_, &aparam_act1_cristal_->shot_y_);
		for (int wave = 0; wave < wave_max; wave++) {
			for (int wait = 0; wait < 12 + rank_num; wait += 2) {
				aparam_act1_cristal_->shot_wait_ = wait;
				aparam_act1_cristal_->shot_angle_ = CalcRAD(act1_shot1_angleR_ + wave * wave_angle);
				ArmsManager::TargetShotSmall(aparam_act1_cristal_);
			}
		}
	}
	act1_shot1_angleL_ -= 10;
	act1_shot1_angleR_ += 10;
}

void Boss3OXA48::Act2_ShotHard2(void)
{
	int rank_num;
	int rank_speed;
	int wave_max = 7;
	int wave_angle = 360 / wave_max;

	// *****************
	//  クリスタル攻撃
	// *****************

	if (frames_ % 40 != 20)
		return;

	DesignManager::GetRank(&rank_num);
	rank_num = rank_num / 3;
	DesignManager::GetRank(&rank_speed);
	aparam_act1_cristal_->shot_speed_ = 8.0 + (rank_speed / 3);
	for (int i = 0; i < 3; i++) {
		cristal_[i]->GetPos(&aparam_act1_cristal_->shot_x_, &aparam_act1_cristal_->shot_y_);
		for (int wave = 0; wave < wave_max; wave++) {
			for (int wait = 0; wait < 12 + rank_num; wait += 2) {
				aparam_act1_cristal_->shot_wait_ = wait;
				aparam_act1_cristal_->shot_angle_ = CalcRAD(act1_shot2_angleL_ + wave * wave_angle);
				ArmsManager::TargetShotSmall(aparam_act1_cristal_);
			}
		}
	}
	for (int i = 9; i < 12; i++) {
		cristal_[i]->GetPos(&aparam_act1_cristal_->shot_x_, &aparam_act1_cristal_->shot_y_);
		for (int wave = 0; wave < wave_max; wave++) {
			for (int wait = 0; wait < 12 + rank_num; wait += 2) {
				aparam_act1_cristal_->shot_wait_ = wait;
				aparam_act1_cristal_->shot_angle_ = CalcRAD(act1_shot2_angleR_ + wave * wave_angle);
				ArmsManager::TargetShotSmall(aparam_act1_cristal_);
			}
		}
	}
	act1_shot2_angleL_ -= 10;
	act1_shot2_angleR_ += 10;
}


void Boss3OXA48::Act2_ShotHard3(void)
{
	int rank_wave;
	double shot_angle;

	// *****************
	//  メイン攻撃
	// *****************

	if (frames_ % 12 != 0)
		return;

	DesignManager::GetRank(&rank_wave);
	rank_wave = 2 + rank_wave / 3;

	shot_angle = rand() % 140 + 20;
	main_->GetPos(&aparam_act1_main_->shot_x_, &aparam_act1_main_->shot_y_);
	for (int wave = 1; wave <= rank_wave; wave++) {
		aparam_act1_main_->shot_angle_ = CalcRAD(shot_angle - wave * 3);
		ArmsManager::TargetShotSmall(aparam_act1_main_);
	}
	aparam_act1_main_->shot_angle_ = CalcRAD(shot_angle);
	ArmsManager::TargetShotSmall(aparam_act1_main_);
	for (int wave = 1; wave <= rank_wave; wave++) {
		aparam_act1_main_->shot_angle_ = CalcRAD(shot_angle + wave * 3);
		ArmsManager::TargetShotSmall(aparam_act1_main_);
	}
}


void Boss3OXA48::Act4_ShotHard(void)
{
	int cristal_number;
	int rank_wave;
	int rank_speed;
	int wave_max = 20;
	int wave_angle = 360 / wave_max;
	double shot_angle;

	// *****************
	//  クリスタル攻撃
	// *****************

	if (frames_ % 6 != 0)
		return;

	cristal_number = rand() % 12;
	DesignManager::GetRank(&rank_wave);
	wave_max += rank_wave;
	DesignManager::GetRank(&rank_speed);
	aparam_act3_cristal_->shot_speed_ = 9.0 + (rank_speed / 3);
	cristal_[cristal_number]->GetPos(&aparam_act3_cristal_->shot_x_, &aparam_act3_cristal_->shot_y_);
	for (int wave = 0; wave < wave_max; wave++) {
		shot_angle = rand() % 360;
		aparam_act3_cristal_->shot_angle_ = CalcRAD(shot_angle);
		ArmsManager::TargetShotSmall(aparam_act3_cristal_);
	}
}

void Boss3OXA48::Act5_ShotHard(void)
{
	int cristal_number;
	int rank_wave;
	int rank_speed;
	int wave_max = 20;
	int wave_angle = 360 / wave_max;
	double shot_angle;

	// *****************
	//  クリスタル攻撃
	// *****************

	if (frames_ % 2 != 0)
		return;

	cristal_number = rand() % 12;
	DesignManager::GetRank(&rank_wave);
	wave_max += rank_wave;
	DesignManager::GetRank(&rank_speed);
	aparam_act4_cristal_->shot_speed_ = 5.5 + (rank_speed / 3);
	cristal_[cristal_number]->GetPos(&aparam_act4_cristal_->shot_x_, &aparam_act4_cristal_->shot_y_);
	for (int wave = 0; wave < wave_max; wave++) {
		shot_angle = rand() % 360;
		aparam_act4_cristal_->shot_angle_ = CalcRAD(shot_angle);
		ArmsManager::TargetShotSmall(aparam_act4_cristal_);
	}
}


void Boss3OXA48::Act6_Move(void)
{
	for (int i = 0; i < 12; i++)
		cristal_[i]->MoveA(&act5_cristal_movex_[i], &act5_cristal_movey_[i]);
}


void Boss3OXA48::Act7_ShotHard1(void)
{
	int rank_wave;
	int rank_speed;
	int user_posy;
	int wave_max = 7;
	int wave_angle = 140 / wave_max;

	// *****************
	//  クリスタル攻撃
	// *****************

	if (frames_ % 80 != 0)
		return;

	DesignManager::GetRank(&rank_wave);
	wave_max += rank_wave;
	DesignManager::GetRank(&rank_speed);
	aparam_act6_cristal_->shot_speed_ = 1.5 + (rank_speed / 3);
	PosManager::GetPos(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, NULL, &user_posy);
	if (200 < user_posy) {
		for (int i = 0; i < 12; i += 2) {
			cristal_[i]->GetPos(&aparam_act6_cristal_->shot_x_, &aparam_act6_cristal_->shot_y_);
			for (int wave = 1; wave <= wave_max; wave++) {
				aparam_act6_cristal_->shot_angle_ = CalcRAD(10 + wave * wave_angle);
				ArmsManager::TargetShotSmall(aparam_act6_cristal_);
			}
		}
	} else {
		for (int i = 0; i < 12; i += 2) {
			cristal_[i]->GetPos(&aparam_act6_cristal_->shot_x_, &aparam_act6_cristal_->shot_y_);
			for (int wave = 1; wave <= wave_max; wave++) {
				aparam_act6_cristal_->shot_angle_ = CalcRAD(-10 - wave * wave_angle);
				ArmsManager::TargetShotSmall(aparam_act6_cristal_);
			}
		}
	}
}

void Boss3OXA48::Act7_ShotHard2(void)
{
	int rank_wave;
	int rank_speed;
	int user_posy;
	int wave_max = 7;
	int wave_angle = 140 / wave_max;

	// *****************
	//  クリスタル攻撃
	// *****************

	if (frames_ % 80 != 40)
		return;

	DesignManager::GetRank(&rank_wave);
	wave_max += rank_wave;
	DesignManager::GetRank(&rank_speed);
	aparam_act6_cristal_->shot_speed_ = 1.5 + (rank_speed / 3);
	PosManager::GetPos(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, NULL, &user_posy);
	if (200 < user_posy) {
		for (int i = 1; i < 12; i += 2) {
			cristal_[i]->GetPos(&aparam_act6_cristal_->shot_x_, &aparam_act6_cristal_->shot_y_);
			for (int wave = 1; wave <= wave_max; wave++) {
				aparam_act6_cristal_->shot_angle_ = CalcRAD(10 + wave * wave_angle);
				ArmsManager::TargetShotSmall(aparam_act6_cristal_);
			}
		}
	} else {
		for (int i = 1; i < 12; i += 2) {
			cristal_[i]->GetPos(&aparam_act6_cristal_->shot_x_, &aparam_act6_cristal_->shot_y_);
			for (int wave = 1; wave <= wave_max; wave++) {
				aparam_act6_cristal_->shot_angle_ = CalcRAD(-10 - wave * wave_angle);
				ArmsManager::TargetShotSmall(aparam_act6_cristal_);
			}
		}
	}
}

void Boss3OXA48::Act7_ShotHard3(void)
{
	int rank_speed;
	double user_posy;

	// ************
	//  メイン攻撃
	// ************

	if (frames_ % 30 != 10)
		return;

	PosManager::GetPos(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, NULL, &user_posy);
	if (user_posy < 200) {
		DesignManager::GetRank(&rank_speed);
		aparam_act6_main_->shot_speed_ = 5.0 + (rank_speed / 3);
		main_->GetPos(&aparam_act6_main_->shot_x_, &aparam_act6_main_->shot_y_);
		aparam_act6_main_->shot_x_ -= 15;
		for (int wait = 0; wait < 12; wait += 3) {
			aparam_act6_main_->shot_angle_ = CalcRAD(-90);
			aparam_act6_main_->shot_wait_ = wait;
			ArmsManager::TargetShotSmall(aparam_act6_main_);
		}
		main_->GetPos(&aparam_act6_main_->shot_x_, &aparam_act6_main_->shot_y_);
		for (int wait = 0; wait < 12; wait += 3) {
			aparam_act6_main_->shot_angle_ = CalcRAD(-90);
			aparam_act6_main_->shot_wait_ = wait;
			ArmsManager::TargetShotSmall(aparam_act6_main_);
		}
		main_->GetPos(&aparam_act6_main_->shot_x_, &aparam_act6_main_->shot_y_);
		aparam_act6_main_->shot_x_ += 15;
		for (int wait = 0; wait < 12; wait += 3) {
			aparam_act6_main_->shot_angle_ = CalcRAD(-90);
			aparam_act6_main_->shot_wait_ = wait;
			ArmsManager::TargetShotSmall(aparam_act6_main_);
		}
	} else {
		DesignManager::GetRank(&rank_speed);
		aparam_act6_main_->shot_speed_ = 5.0 + (rank_speed / 3);
		main_->GetPos(&aparam_act6_main_->shot_x_, &aparam_act6_main_->shot_y_);
		aparam_act6_main_->shot_x_ -= 15;
		for (int wait = 0; wait < 12; wait += 3) {
			aparam_act6_main_->shot_angle_ = CalcRAD(90);
			aparam_act6_main_->shot_wait_ = wait;
			ArmsManager::TargetShotSmall(aparam_act6_main_);
		}
		main_->GetPos(&aparam_act6_main_->shot_x_, &aparam_act6_main_->shot_y_);
		for (int wait = 0; wait < 12; wait += 3) {
			aparam_act6_main_->shot_angle_ = CalcRAD(90);
			aparam_act6_main_->shot_wait_ = wait;
			ArmsManager::TargetShotSmall(aparam_act6_main_);
		}
		main_->GetPos(&aparam_act6_main_->shot_x_, &aparam_act6_main_->shot_y_);
		aparam_act6_main_->shot_x_ += 15;
		for (int wait = 0; wait < 12; wait += 3) {
			aparam_act6_main_->shot_angle_ = CalcRAD(90);
			aparam_act6_main_->shot_wait_ = wait;
			ArmsManager::TargetShotSmall(aparam_act6_main_);
		}
	}
}

void Boss3OXA48::Act7_Move(void)
{
	double boss_posx, boss_posy;
	double user_posx, user_posy;

	// *****************
	//  メイン移動処理
	// *****************
	if (frames_ % 30 == 0) {
		PosManager::GetPos(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, &user_posx, &user_posy);
		main_->GetPos(&boss_posx, &boss_posy);
		act6_main_movex_ = (user_posx - boss_posx) / 10;
	}

	if (0 <= frames_ % 30 && frames_ % 30 < 10)
		main_->MoveA(&act6_main_movex_, NULL);
}


void Boss3OXA48::Act8_Move(void)
{
	main_->MoveA(&act7_main_movex_, NULL);
	for (int i = 0; i < 12; i++)
		cristal_[i]->MoveA(&act7_cristal_movex_[i], &act7_cristal_movey_[i]);
}

void Boss3OXA48::Act12_ShotHard1(void)
{
	int rank_speed;
	double angle;

	// *****************
	//  クリスタル攻撃
	// *****************

	if (frames_ % 8 != 0)
		return;

	angle = rand() % 360;
	DesignManager::GetRank(&rank_speed);
	aparam_act11_cristal_->shot_speed_ = 9.0 + (rank_speed / 3);

	for (int i = 0; i < 2; i++) {
		cristal2_[i]->GetPos(&aparam_act11_cristal_->shot_x_, &aparam_act11_cristal_->shot_y_);
		aparam_act11_cristal_->shot_angle_ = CalcRAD(angle);
		aparam_act11_cristal_->shot_x_ += (10 * cos(CalcRAD(angle + 90)));
		aparam_act11_cristal_->shot_y_ += (10 * sin(CalcRAD(angle + 90)));
		for (int wait = 0; wait < 8; wait += 2) {
			aparam_act11_cristal_->shot_wait_ = wait;
			ArmsManager::TargetShotSmall(aparam_act11_cristal_);
		}
		cristal2_[i]->GetPos(&aparam_act11_cristal_->shot_x_, &aparam_act11_cristal_->shot_y_);
		aparam_act11_cristal_->shot_angle_ = CalcRAD(angle);
		aparam_act11_cristal_->shot_x_ -= (10 * cos(CalcRAD(angle + 90)));
		aparam_act11_cristal_->shot_y_ -= (10 * sin(CalcRAD(angle + 90)));
		for (int wait = 0; wait < 8; wait += 2) {
			aparam_act11_cristal_->shot_wait_ = wait;
			ArmsManager::TargetShotSmall(aparam_act11_cristal_);
		}
	}
}

void Boss3OXA48::Act12_ShotHard2(void)
{
	int rank_speed;
	double angle;

	// *****************
	//  クリスタル攻撃
	// *****************

	if (frames_ % 8 != 4)
		return;

	angle = rand() % 360;
	DesignManager::GetRank(&rank_speed);
	aparam_act11_cristal_->shot_speed_ = 9.0 + (rank_speed / 3);

	for (int i = 0; i < 2; i++) {
		cristal2_[i]->GetPos(&aparam_act11_cristal_->shot_x_, &aparam_act11_cristal_->shot_y_);
		aparam_act11_cristal_->shot_angle_ = CalcRAD(angle);
		aparam_act11_cristal_->shot_x_ += (10 * cos(CalcRAD(angle + 90)));
		aparam_act11_cristal_->shot_y_ += (10 * sin(CalcRAD(angle + 90)));
		for (int wait = 0; wait < 8; wait += 2) {
			aparam_act11_cristal_->shot_wait_ = wait;
			ArmsManager::TargetShotSmall(aparam_act11_cristal_);
		}
		cristal2_[i]->GetPos(&aparam_act11_cristal_->shot_x_, &aparam_act11_cristal_->shot_y_);
		aparam_act11_cristal_->shot_angle_ = CalcRAD(angle);
		aparam_act11_cristal_->shot_x_ -= (10 * cos(CalcRAD(angle + 90)));
		aparam_act11_cristal_->shot_y_ -= (10 * sin(CalcRAD(angle + 90)));
		for (int wait = 0; wait < 8; wait += 2) {
			aparam_act11_cristal_->shot_wait_ = wait;
			ArmsManager::TargetShotSmall(aparam_act11_cristal_);
		}
	}
}

void Boss3OXA48::Collision1(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += main_->Collision(extension);
	for (int i = 0; i < 12; i++) {
		cristal_[i]->CollisionImg(imgfile_cristal_lock_, 0, interval);
		cristal_[i]->CollisionSound(soundfile_lock_, interval);
		damage += cristal_[i]->Collision(extension);
	}
	DesignManager::AddScore((long)damage);
	health_ -= damage;
}


void Boss3OXA48::Collision2(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += main_->Collision(extension);
	for (int i = 0; i < 2; i++) {
		cristal2_[i]->CollisionImg(imgfile_cristal_lock_, 0, interval);
		cristal2_[i]->CollisionSound(soundfile_lock_, interval);
		damage += cristal2_[i]->Collision(extension);
	}
	DesignManager::AddScore((long)damage);
	health_ -= (damage / 2);
}


void Boss3OXA48::Draw1(void)
{
	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 2;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cristal_ = ++imgdiv_cristal_ % 20;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);
	for (int i = 0; i < 12; i++)
		cristal_[i]->Draw(imgfile_cristal_red_, imgdiv_cristal_, 0.5, 0);
}


void Boss3OXA48::Draw2(void)
{
	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 2;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cristal_ = ++imgdiv_cristal_ % 20;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);
	for (int i = 0; i < 2; i++)
		cristal2_[i]->Draw(imgfile_cristal_red_, imgdiv_cristal_, 0.5, 0);
}


void Boss3OXA48::DeleteCristal(double scale, bool effect, bool sound)
{
	double add_alv		= 0.1 * scale;				// 加算ALV
	double add_exarms	= 2.0 * scale;				// 加算ExArms
	double add_rank		= 0.01 * scale;				// 加算ランク
	long   add_score	= (long)(1000 * scale);		// 加算スコア

	// エフェクト追加
	if (effect) {
		for (int i = 0; i < 12; i++) {
			cristal_[i]->GetPos(&eparam_death_cristal_->x_, &eparam_death_cristal_->y_);
			EffectManager::Create(eparam_death_cristal_);
		}
	}

	// サウンド追加
	if (sound)
		SoundManager::Play(soundfile_death_cristal_, DX_PLAYTYPE_BACK);

	// 削除処理
	for (int i = 0; i < 12; i++)
		cristal_[i]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}

void Boss3OXA48::DeleteCristal2(double scale, bool effect, bool sound)
{
	double add_alv		= 0.1 * scale;				// 加算ALV
	double add_exarms	= 2.0 * scale;				// 加算ExArms
	double add_rank		= 0.01 * scale;				// 加算ランク
	long   add_score	= (long)(1000 * scale);		// 加算スコア

	// エフェクト追加
	if (effect) {
		for (int i = 0; i < 4; i++) {
			cristal_[i]->GetPos(&eparam_death_cristal_->x_, &eparam_death_cristal_->y_);
			EffectManager::Create(eparam_death_cristal_);
		}
	}

	// サウンド追加
	if (sound)
		SoundManager::Play(soundfile_death_cristal_, DX_PLAYTYPE_BACK);

	// 削除処理
	for (int i = 0; i < 4; i++)
		cristal_[i]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Boss3OXA48::DeleteMain(double scale, bool effect, bool sound)
{
	double add_alv		= 0.1 * scale;				// 加算ALV
	double add_exarms	= 2.0 * scale;				// 加算ExArms
	double add_rank		= 0.01 * scale;				// 加算ランク
	long   add_score	= (long)(1000 * scale);		// 加算スコア

	// エフェクト追加
	if (effect) {
		main_->GetPos(&eparam_death_main_->x_, &eparam_death_main_->y_);
		EffectManager::Create(eparam_death_main_);
	}

	// サウンド追加
	if (sound)
		SoundManager::Play(soundfile_death_cristal_, DX_PLAYTYPE_BACK);

	// 振動処理
	ImgManager::SwingY(20, 5);

	// 削除処理
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
}
