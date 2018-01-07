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
#include "Boss1MRAB.h"
#include "DebugPrint.h"

//#define __DEBUG__

using namespace NH2;
using namespace NH2T;


Boss1MRAB::Boss1MRAB(double x, double y, int lv)
{
	main_ = new Target(x, y, 32);
	cristal_orange_[0] = new Target(x + 100, y, 24);
	cristal_orange_[1] = new Target(x - 100, y, 24);
	cristal_red_[0] = new Target(x + 32, y - 48, 24);
	cristal_red_[1] = new Target(x - 32, y - 48, 24);	
	aparam_cristal_ = new ArmsParam1;
	aparam_act21_cristal_ = new ArmsParam1;
	aparam_act23_cristal_orange_ = new ArmsParam1;
	aparam_act23_cristal_red_ = new ArmsParam1;
	aparam_act41_main_ = new ArmsParam1;
	eparam_death_cristal_ = new EffectParam1b;
	eparam_death_main_ = new EffectParam1b;
	// 変数初期化
	health_ = 2000;
	health_max_ = 2000;
	frames_ = 0;
	lv_ = lv;
	phase_ = 10;
	act21_shot_angle_ = rand() % 110 + 35;
	act23_move_angle_ = 0;
	DesignManager::SetBossHealth(100.0);
	// 画像ファイル
	imgdiv_cristal_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_orange20t_ = IMG_LOAD_ARMS_ORANGE20T;
	imgfile_arms_red20t_ = IMG_LOAD_ARMS_RED20T;
	imgfile_arms_red16t_ = IMG_LOAD_ARMS_RED16T;
	imgfile_cristal_orange_ = IMG_LOAD_TARGET_CRISTAL_ORANGE120;
	imgfile_cristal_red_ = IMG_LOAD_TARGET_CRISTAL_RED120;
	imgfile_cristal_lock_ = IMG_LOAD_TARGET_LOCK_CRISTAL;
	imgfile_death_cristal_ = IMG_LOAD_EFFECT_DEATH140;
	imgfile_death_main_ = IMG_LOAD_EFFECT_DEATH427;
	imgfile_main_ = IMG_LOAD_TARGET_BOSS1_MRAB;
	imgfile_main_lock_ = ImgManager::LoadImg("data/img_target/LockMRAB.png");
	// サウンドファイル
	soundfile_lock_ = SoundManager::Load("data/sound/target_lock.wav");
	soundfile_death_cristal_ = SOUND_LOAD_TARGET_DEATH3;
	soundfile_death_main_ = SOUND_LOAD_BOSS_DEATH;
	// Arms Cristal 固定パラメータ
	//aparam_cristal_->img_angle_ = 0;
	//aparam_cristal_->img_id_ = imgfile_arms_red20t_;
	//aparam_cristal_->img_rotate_ = 0;
	//aparam_cristal_->shot_pow_ = 1;
	//aparam_cristal_->shot_range_ = 2.0;
	// Arms Cristal 固定パラメータ
	aparam_act21_cristal_->img_angle_ = 0;
	aparam_act21_cristal_->img_id_ = imgfile_arms_red20t_,
	aparam_act21_cristal_->img_rotate_ = 0;
	aparam_act21_cristal_->shot_pow_ = 1;
	aparam_act21_cristal_->shot_range_ = ARMS_PARAM_RANGE_RED20T;
	// Arms Cristal Orange 固定パラメータ
	aparam_act23_cristal_orange_->img_angle_ = 0;
	aparam_act23_cristal_orange_->img_id_ = imgfile_arms_orange20t_;
	aparam_act23_cristal_orange_->img_rotate_ = 0;
	aparam_act23_cristal_orange_->shot_pow_ = 1;
	aparam_act23_cristal_orange_->shot_range_ = ARMS_PARAM_RANGE_ORANGE20T;
	aparam_act23_cristal_orange_->shot_speed_ = 2.5;
	aparam_act23_cristal_orange_->shot_wait_ = 0;
	// Arms Cristal Red 固定パラメータ
	aparam_act23_cristal_red_->img_angle_ = 0;
	aparam_act23_cristal_red_->img_id_ = imgfile_arms_red20t_;
	aparam_act23_cristal_red_->img_rotate_ = 0;
	aparam_act23_cristal_red_->shot_pow_ = 1;
	aparam_act23_cristal_red_->shot_range_ = ARMS_PARAM_RANGE_RED20T;
	aparam_act23_cristal_red_->shot_speed_ = 5.0;
	aparam_act23_cristal_red_->shot_wait_ = 0;
	// Arms Main 固定パラメータ
	aparam_act41_main_->img_angle_ = 0;
	aparam_act41_main_->img_id_ = imgfile_arms_red16t_;
	aparam_act41_main_->img_rotate_ = 0;
	aparam_act41_main_->shot_pow_ = 1;
	aparam_act41_main_->shot_range_ = ARMS_PARAM_RANGE_PURPLE16T;
	aparam_act41_main_->shot_wait_ = 0;
	// エフェクト設定 Death Cristal
	eparam_death_cristal_->blend_alpha_ = 255;
	eparam_death_cristal_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_cristal_->extend_rate_ = 1.0;
	eparam_death_cristal_->group_ = eOBJECT::GROUP::TARGET_EFFECT;
	eparam_death_cristal_->img_divmax_ = 64;
	eparam_death_cristal_->img_divmin_ = 0;
	eparam_death_cristal_->img_id_ = imgfile_death_cristal_;
	eparam_death_cristal_->img_interval_ = 1;
	// エフェクト設定 Death Main
	eparam_death_main_->blend_alpha_ = 255;
	eparam_death_main_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_main_->extend_rate_ = 1.0;
	eparam_death_main_->group_ = eOBJECT::GROUP::TARGET_EFFECT;
	eparam_death_main_->img_divmax_ = 63;
	eparam_death_main_->img_divmin_ = 0;
	eparam_death_main_->img_id_ = imgfile_death_main_;
	eparam_death_main_->img_interval_ = 1;
}

Boss1MRAB::~Boss1MRAB()
{
	delete main_;
	delete aparam_cristal_;
	delete aparam_act41_main_;
}


void Boss1MRAB::Draw(void)
{
	switch(phase_) {
	case 10:
	case 11:
	case 21:
	case 22:
	case 23:
	case 24:
		if (FpsManager::GetInterval(20) == 0)
			imgdiv_main_ = ++imgdiv_main_ % 2;
		if (FpsManager::GetInterval(4) == 0)
			imgdiv_cristal_ = ++imgdiv_cristal_ % 20;

		main_->Draw(imgfile_main_, imgdiv_main_, 1.5, 0);
		cristal_orange_[0]->Draw(imgfile_cristal_red_, imgdiv_cristal_, 0.5, 0);
		cristal_orange_[1]->Draw(imgfile_cristal_red_, imgdiv_cristal_, 0.5, 0);
		cristal_red_[0]->Draw(imgfile_cristal_red_, imgdiv_cristal_, 0.5, 0);
		cristal_red_[1]->Draw(imgfile_cristal_red_, imgdiv_cristal_, 0.5, 0);
		break;
	case 31:
	case 32:
	case 41:
		if (FpsManager::GetInterval(20) == 0)
			imgdiv_main_ = ++imgdiv_main_ % 2;

		main_->Draw(imgfile_main_, imgdiv_main_, 1.5, 0);
		break;
	case 51:
	case 52:
		break;
	};
}


void Boss1MRAB::Action(void)
{
	double health_percent;

	// **********************
	//  boss health 描画
	// **********************
	DesignManager::GetBossHealth(&health_percent);
	if (30 <= health_percent) {
		DesignManager::SetBossHealthColor("green");
	} else {
		DesignManager::SetBossHealthColor("red");
	}
	DesignManager::SetBossHealth(100.0 * health_ / health_max_);

	// ******************************************
	//  アクション分岐
	//  phase 10    ... 初期化
	//  phase 11    ... 移動
	//  phase 21-24 ... 攻撃パターン１
	//  phase 31-32 ... 爆発処理
	//  act 41-33 ... 攻撃パターン２
	//  act 40-45 ... 攻撃パターン３
	//  act 50-55 ... 攻撃パターン４
	//  act 100   ... 終了
	// ******************************************
	switch(phase_) {
	case 10:
		DesignManager::FlagDrawBossHealth(true);
		DesignManager::SetBossHealthColor("green");
		main_->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		cristal_orange_[0]->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		cristal_orange_[1]->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		cristal_red_[0]->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		cristal_red_[1]->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		phase_ = 11;
		frames_ = -1;
		break;
	case 11:
		Act11_Move();
		Collision1();
		if (frames_ == 150) {
			phase_ = 21;
			frames_ = -1;
		}
		break;
	case 21:
		Act21_ShotHard1();
		Act21_ShotHard2();
		Collision2();
		DesignManager::GetBossHealth(&health_percent);
		if (frames_ == 249) {
			phase_ = 22;
			frames_ = -1;
		} else if (health_percent < 30) {
			phase_ = 31;
			frames_ = -1;
		}
		break;
	case 22:
		Collision2();
		DesignManager::GetBossHealth(&health_percent);
		if (frames_ == 80) {
			phase_ = 23;
			frames_ = -1;
		} else if (health_percent < 30) {
			phase_ = 31;
			frames_ = -1;
		}		
		break;
	case 23:
		Act23_Move();
		Act23_ShotHard();
		Collision2();
		DesignManager::GetBossHealth(&health_percent);
		if (frames_ == 900) {
			phase_ = 24;
			frames_ = -1;
		} else if (health_percent < 30) {
			phase_ = 31;
			frames_ = -1;
		}
		break;
	case 24:
		Collision2();
		if (frames_ == 300) {
			phase_ = 21;
			frames_ = -1;
		} else if (health_percent < 30) {
			phase_ = 31;
			frames_ = -1;
		}
		break;
	// **************
	//  体力30%以下
	// **************
	case 31:
		Act31_Delete();
		ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_SMALL);
		ImgManager::SwingY(30, 4);
		phase_ = 32;
		frames_ = -1;
		break;
	case 32:
		Collision3();
		if (frames_ == 100) {
			phase_ = 41;
			frames_ = -1;
		}
		break;
	case 41:
		Act41_ShotHard();
		Collision3();
		DesignManager::GetBossHealth(&health_percent);
		if (health_percent <= 0) {
			phase_ = 51;
			frames_ = -1;
		}
		break;
	// **********
	//  体力0%
	// **********
	case 51:
		Act51_Delete();
		ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_SMALL);
		ImgManager::SwingY(40, 5);
		phase_ = 52;
		frames_ = -1;
		break;
	case 52:
		break;
	};

	// フレーム数＆時間経過による体力減少
	frames_++;
	if (frames_ % 10 == 0)
		health_--;
}


void Boss1MRAB::Act11_Move(void)
{
	double move_speed = 1.5;

	main_->MoveA(NULL, &move_speed);
	cristal_orange_[0]->MoveA(NULL, &move_speed);
	cristal_orange_[1]->MoveA(NULL, &move_speed);
	cristal_red_[0]->MoveA(NULL, &move_speed);
	cristal_red_[1]->MoveA(NULL, &move_speed);
}


void Boss1MRAB::Act21_ShotHard1(void)
{
	int rank_speed;

	if (lv_ != LV_HARD)
		return;
	if (frames_ % 50 != 0)
		return;

	DesignManager::GetRank(&rank_speed);
	aparam_act21_cristal_->shot_speed_ = 6.0 + rank_speed;
	act21_shot_angle_ = CalcRAD(rand() % 80 + 50);
	cristal_orange_[0]->GetPos(&aparam_act21_cristal_->shot_x_, &aparam_act21_cristal_->shot_y_);
	for (int i = 0; i < 7; i++) {
		aparam_act21_cristal_->shot_angle_ = act21_shot_angle_ + CalcRAD(rand() % 30 - 15);
		aparam_act21_cristal_->shot_wait_ = i * 2;
		ArmsManager::TargetShotSmall(aparam_act21_cristal_);
		aparam_act21_cristal_->shot_angle_ = act21_shot_angle_ + CalcRAD(rand() % 30 - 15);
		ArmsManager::TargetShotSmall(aparam_act21_cristal_);
	}
}

void Boss1MRAB::Act21_ShotHard2(void)
{
	int rank_speed;

	if (lv_ != LV_HARD)
		return;
	if (frames_ % 50 != 25)
		return;

	DesignManager::GetRank(&rank_speed);
	aparam_act21_cristal_->shot_speed_ = 6.0 + rank_speed;
	act21_shot_angle_ = CalcRAD(rand() % 80 + 50);
	cristal_orange_[1]->GetPos(&aparam_act21_cristal_->shot_x_, &aparam_act21_cristal_->shot_y_);
	for (int i = 0; i < 7; i++) {
		aparam_act21_cristal_->shot_angle_ = act21_shot_angle_ + CalcRAD(rand() % 30 - 15);
		aparam_act21_cristal_->shot_wait_ = i * 2;
		ArmsManager::TargetShotSmall(aparam_act21_cristal_);
		aparam_act21_cristal_->shot_angle_ = act21_shot_angle_ + CalcRAD(rand() % 30 - 15);
		ArmsManager::TargetShotSmall(aparam_act21_cristal_);
	}
}


void Boss1MRAB::Act23_Move(void)
{
	double x, y;

	if (frames_ <= 900) {
		act23_move_angle_ += CalcRAD(2);
		main_->GetPos(&x, &y);
		x += cos(act23_move_angle_) * 100;
		y += sin(act23_move_angle_) * 100;
		cristal_orange_[0]->SetPos(&x, &y);
		main_->GetPos(&x, &y);
		x += cos(act23_move_angle_ + CalcRAD(180)) * 100;
		y += sin(act23_move_angle_ + CalcRAD(180)) * 100;
		cristal_orange_[1]->SetPos(&x, &y);
	}
}

void Boss1MRAB::Act23_ShotHard(void)
{
	int rank_freq;
	const double angle40 = CalcRAD(40);
	const double angle30 = CalcRAD(30);
	const double angle24 = CalcRAD(24);
	const double angle10 = CalcRAD(10);

	if (lv_ != LV_HARD)
		return;

	DesignManager::GetRank(&rank_freq);
	
	// ******************
	//  cristal orange
	// ******************

	aparam_act23_cristal_orange_->shot_angle_ = CalcRAD(rand() % 360);
	if (frames_ < 180 && frames_ % 40 == 0) {
		cristal_orange_[0]->GetPos(&aparam_act23_cristal_orange_->shot_x_, &aparam_act23_cristal_orange_->shot_y_);
		if (cristal_orange_[0]->InsidePanel(0)) {
			for(int i = 0; i < 9; i++) {
				aparam_act23_cristal_orange_->shot_angle_ += angle40;
				ArmsManager::TargetShotSmall(aparam_act23_cristal_orange_);
			}
		}
		cristal_orange_[1]->GetPos(&aparam_act23_cristal_orange_->shot_x_, &aparam_act23_cristal_orange_->shot_y_);
		if (cristal_orange_[1]->InsidePanel(0)) {
			for(int i = 0; i < 9; i++) {
				aparam_act23_cristal_orange_->shot_angle_ += angle40;
				ArmsManager::TargetShotSmall(aparam_act23_cristal_orange_);
			}
		}
	} else if (180 <= frames_ && frames_ < 360 && frames_ % 20 == 0) {
		cristal_orange_[0]->GetPos(&aparam_act23_cristal_orange_->shot_x_, &aparam_act23_cristal_orange_->shot_y_);
		if (cristal_orange_[0]->InsidePanel(0)) {
			for(int i = 0; i < 12; i++) {
				aparam_act23_cristal_orange_->shot_angle_ += angle30;
				ArmsManager::TargetShotSmall(aparam_act23_cristal_orange_);
			}
		}
		cristal_orange_[1]->GetPos(&aparam_act23_cristal_orange_->shot_x_, &aparam_act23_cristal_orange_->shot_y_);
		if (cristal_orange_[1]->InsidePanel(0)) {
			for(int i = 0; i < 12; i++) {
				aparam_act23_cristal_orange_->shot_angle_ += angle30;
				ArmsManager::TargetShotSmall(aparam_act23_cristal_orange_);
			}
		}
	} else if (360 <= frames_ && frames_ < 900 && frames_ % 10 == 0) {
		cristal_orange_[0]->GetPos(&aparam_act23_cristal_orange_->shot_x_, &aparam_act23_cristal_orange_->shot_y_);
		if (cristal_orange_[0]->InsidePanel(0)) {
			for(int i = 0; i < 15; i++) {
				aparam_act23_cristal_orange_->shot_angle_ += angle24;
				ArmsManager::TargetShotSmall(aparam_act23_cristal_orange_);
			}
		}
		cristal_orange_[1]->GetPos(&aparam_act23_cristal_orange_->shot_x_, &aparam_act23_cristal_orange_->shot_y_);
		if (cristal_orange_[1]->InsidePanel(0)) {
			for(int i = 0; i < 15; i++) {
				aparam_act23_cristal_orange_->shot_angle_ += angle24;
				ArmsManager::TargetShotSmall(aparam_act23_cristal_orange_);
			}
		}
	}

	// ***************
	//  cristal red
	// ***************

	DesignManager::GetRank(&rank_freq, 4.0);
	aparam_act23_cristal_red_->shot_angle_ = CalcRAD(rand() % 360);
	if (180 <= frames_ && frames_ % (60 - rank_freq) == 0) {
		if (cristal_red_[0]->InsidePanel(0)) {
			cristal_red_[0]->GetPos(&aparam_act23_cristal_red_->shot_x_, &aparam_act23_cristal_red_->shot_y_);
			for (int i = 0; i < 36; i++) {
				aparam_act23_cristal_red_->shot_angle_ += angle10;
				ArmsManager::TargetShotSmall(aparam_act23_cristal_red_);
			}
		}
		if (cristal_red_[1]->InsidePanel(0)) {
			cristal_red_[1]->GetPos(&aparam_act23_cristal_red_->shot_x_, &aparam_act23_cristal_red_->shot_y_);
			for (int i = 0; i < 36; i++) {
				aparam_act23_cristal_red_->shot_angle_ += angle10;
				ArmsManager::TargetShotSmall(aparam_act23_cristal_red_);
			}
		}
	}

}

void Boss1MRAB::Act31_Delete(void)
{
	double add_alv		= 0.1 * 1.0;				// 加算ALV
	double add_exarms	= 2.0 * 1.0;				// 加算ExArms
	double add_rank		= 0.01 * 1.0;				// 加算ランク
	long   add_score	= (long)(1000 * 1.0);		// 加算スコア

	// エフェクト追加
	if (true) {
		cristal_orange_[0]->GetPos(&eparam_death_cristal_->x_, &eparam_death_cristal_->y_);
		EffectManager::Create(eparam_death_cristal_);
		cristal_orange_[1]->GetPos(&eparam_death_cristal_->x_, &eparam_death_cristal_->y_);
		EffectManager::Create(eparam_death_cristal_);
		cristal_red_[0]->GetPos(&eparam_death_cristal_->x_, &eparam_death_cristal_->y_);
		EffectManager::Create(eparam_death_cristal_);
		cristal_red_[1]->GetPos(&eparam_death_cristal_->x_, &eparam_death_cristal_->y_);
		EffectManager::Create(eparam_death_cristal_);
	}

	// サウンド追加
	if (true)
		SoundManager::Play(soundfile_death_cristal_, DX_PLAYTYPE_BACK);

	// 削除処理
	cristal_orange_[0]->DeleteData(add_alv, add_exarms, add_rank, add_score);
	cristal_orange_[1]->DeleteData(add_alv, add_exarms, add_rank, add_score);
	cristal_red_[0]->DeleteData(add_alv, add_exarms, add_rank, add_score);
	cristal_red_[1]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Boss1MRAB::Act41_ShotHard(void)
{
	double rank_speed;

	DesignManager::GetRank(&rank_speed, 0.3);
	if (frames_ % 10 == 0 && main_->InsidePanel(0)) {
		aparam_act41_main_->shot_speed_ = 8.0 + rank_speed;
		main_->GetPos(&aparam_act41_main_->shot_x_, &aparam_act41_main_->shot_y_);
		for(int i = 0; i < 18; i++) {
			aparam_act41_main_->shot_angle_ = CalcRAD(rand() % 360);
			ArmsManager::TargetShotSmall(aparam_act41_main_);
		}
	}
}


void Boss1MRAB::Act51_Delete(void)
{
	double add_alv		= 0.1 * 1.0;				// 加算ALV
	double add_exarms	= 2.0 * 1.0;				// 加算ExArms
	double add_rank		= 0.01 * 1.0;				// 加算ランク
	long   add_score	= (long)(1000 * 1.0);		// 加算スコア

	// エフェクト追加
	if (true) {
		main_->GetPos(&eparam_death_main_->x_, &eparam_death_main_->y_);
		EffectManager::Create(eparam_death_main_);
	}

	// サウンド追加
	if (true)
		SoundManager::Play(soundfile_death_main_, DX_PLAYTYPE_BACK);

	// 削除処理
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Boss1MRAB::Collision1(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// draw_window 拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += cristal_orange_[0]->Collision(extension);
	cristal_orange_[0]->CollisionImg(imgfile_cristal_lock_, 0, interval);
	cristal_orange_[0]->CollisionSound(soundfile_lock_, interval);
	damage += cristal_orange_[1]->Collision(extension);
	cristal_orange_[1]->CollisionImg(imgfile_cristal_lock_, 0, interval);
	cristal_orange_[1]->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
//	health_ -= damage;			// 蓄積ダメージの更新
}


void Boss1MRAB::Collision2(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// draw_window 拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += cristal_orange_[0]->Collision(extension);
	cristal_orange_[0]->CollisionImg(imgfile_cristal_lock_, 0, interval);
	cristal_orange_[0]->CollisionSound(soundfile_lock_, interval);
	damage += cristal_orange_[1]->Collision(extension);
	cristal_orange_[1]->CollisionImg(imgfile_cristal_lock_, 0, interval);
	cristal_orange_[1]->CollisionSound(soundfile_lock_, interval);
	damage += cristal_red_[0]->Collision(extension);
	cristal_red_[0]->CollisionImg(imgfile_cristal_lock_, 0, interval);
	cristal_red_[0]->CollisionSound(soundfile_lock_, interval);
	damage += cristal_red_[1]->Collision(extension);
	cristal_red_[1]->CollisionImg(imgfile_cristal_lock_, 0, interval);
	cristal_red_[1]->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	health_ -= damage;			// 蓄積ダメージの更新
}


void Boss1MRAB::Collision3(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// draw_window 拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	health_ -= damage;			// 蓄積ダメージの更新
}

