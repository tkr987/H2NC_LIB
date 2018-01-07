#include <float.h>
#include "DxLib.h"
#include "ArmsManager.h"
#include "DefineNH.h"
#include "DesignManager.h"
#include "EffectManager.h"
#include "FpsManager.h"
#include "ImgManager.h"
#include "PosManager.h"
#include "SoundManager.h"
#include "Target.h"
#include "TargetBase.h"
#include "Target1Sipho.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target1Sipho::Target1Sipho(double start_posx, double end_posy, int lv)
{
	const double move_speed = 5.0;

	// ターゲット、パラメータ　生成
	main_ = new Target(start_posx, -200, 15);
	cube_[0] = new Target(start_posx - 80, -200 - 32, 15);
	cube_[1] = new Target(start_posx - 48, -200, 15);
	cube_[2] = new Target(start_posx + 48, -200, 15);
	cube_[3] = new Target(start_posx + 80, -200 - 32, 15);
	aparam_cube_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 変数 初期化
	end_posy_ = end_posy;
	frames_ = 0;
	health_ = 250;
	lv_ = lv;
	max_cube_ = 4;
	move_speed_ = move_speed;
	phase_ = 10;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_cube_ = IMG_LOAD_ARMS_BLUE16T;
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH140;
	imgfile_cube_ = IMG_LOAD_TARGET_CUBE_BLUE140;
	imgfile_cube_lock_ = IMG_LOAD_TARGET_LOCK_CUBE;
	imgfile_main_ = IMG_LOAD_TARGET_MAIN_STAGE1_SIPHO;
	imgfile_main_lock_ = IMG_LOAD_TARGET_LOCK_STAGE1_SIPHO;
	// サウンドファイル
	soundfile_death_ = SOUND_LOAD_TARGET_DEATH3;
	soundfile_lock_ = SOUND_LOAD_TARGET_LOCK;
	// 爆発エフェクト設定
	eparam_death_->blend_alpha_ = 255;
	eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::GROUP::TARGET_EFFECT;
	eparam_death_->img_divmax_ = 64;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 1;
	// ARMS CUBE 固定パラメータ
	aparam_cube_->shot_angle_ = CalcRAD(90);
	aparam_cube_->img_angle_ = 0;
	aparam_cube_->img_id_ = imgfile_arms_cube_;
	aparam_cube_->img_rotate_ = 0;
	aparam_cube_->shot_pow_ = 1;
	aparam_cube_->shot_range_ = 2.0;
}


Target1Sipho::~Target1Sipho()
{
	for (int i = 0; i < max_cube_; i++)
		delete cube_[i];
	delete main_;
	delete aparam_cube_;
}


void Target1Sipho::Action(void)
{
	switch(phase_) {
	case 10:
		main_->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		for (int i = 0; i < 4; i++)
			cube_[i]->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		phase_ = 11;
		frames_ = -1;
		break;
	case 11:
		Move1();
		if (move_speed_ == 0.5) {
			phase_ = 12;
			frames_ = -1;
		}
		break;
	case 12:
		Collision();
		Move2();
		ShotHard();
		if (health_ < 0) {
			phase_ = 13;
			frames_ = -1;
		}
		if (frames_ == 2000) {
			phase_ = 14;
			frames_ = -1;
		}
		break;
	case 13:
		Delete(1.0, true, true);
		ArmsManager::DeleteAll(eOBJECT::TARGET_ARMS_LARGE);
		ArmsManager::DeleteAll(eOBJECT::TARGET_ARMS_SMALL);
		ImgManager::SwingY(20, 3);
		phase_ = 15;
		frames_ = -1;
		break;
	case 14:
		Delete(0.0, false, false);
		phase_ = 15;
		frames_ = -1;
		break;
	case 15:
		// 終了
		break;
	}

	frames_++;
}


void Target1Sipho::Draw(void)
{
	const int divmax_cube = 5;
	const int divmax_main = 16;

	switch(phase_) {
	case 11:
	case 12:
		if (FpsManager::GetInterval(4) == 0)
			imgdiv_cube_ = ++imgdiv_cube_ % divmax_cube;
		if (FpsManager::GetInterval(20) == 0)
			imgdiv_main_ = ++imgdiv_main_ % divmax_main;

		for (int i = 0; i < max_cube_; i++)
			cube_[i]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
		main_->Draw(imgfile_main_, imgdiv_main_, 1.5, 0);
		break;
	}
}


void Target1Sipho::ShotHard(void)
{
	double rank;

	if (lv_ != LV_HARD)
		return;
	if (frames_ % 60 !=  0 && frames_ % 60 != 5 && frames_ % 60 != 10 &&
		frames_ % 60 != 15 && frames_ % 60 != 20)
		return;

	// 共通パラメータ
	DesignManager::GetRank(&rank);
	aparam_cube_->shot_speed_ = 4.0 + rank / 150.0;
	// cube1
	for (int i = 0; i < max_cube_; i++) {
		if (!cube_[i]->InsidePanel(-32))
			continue;
		cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
		aparam_cube_->shot_x_ -= 6;
		ArmsManager::TargetShotSmall(aparam_cube_);
		cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
		aparam_cube_->shot_x_ += 6;
		ArmsManager::TargetShotSmall(aparam_cube_);
	}
}


void Target1Sipho::Collision(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	for (int i = 0; i < max_cube_; i++) {
		damage += cube_[i]->Collision(extension);
		cube_[i]->CollisionImg(imgfile_cube_lock_, 0, interval);
		cube_[i]->CollisionSound(soundfile_lock_, interval);
		DesignManager::AddScore(damage);
	}
	health_ -= damage;
}


void Target1Sipho::Delete(double scale, bool effect, bool sound)
{
	double add_alv		= 0.500 * scale;				// 加算ALV
	double add_exarms	= 4.000 * scale;				// 加算ExArms
	double add_rank		= 0.006 * scale;				// 加算ランク
	long   add_score	= (long)(1000 * scale);		// 加算スコア

	// エフェクト追加
	if (effect) {
		main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
		for (int i = 0; i < max_cube_; i++) {
			cube_[i]->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
		}
	}

	// サウンド追加
	if (sound)
		SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);

	// 削除処理
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
	for (int i = 0; i < max_cube_; i++)
		cube_[i]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Target1Sipho::Move1(void)
{
	double y;

	main_->GetPos(NULL, &y);
	if (end_posy_ < y)
		move_speed_ = (move_speed_ - 0.2 < 0.5) ? 0.5 : move_speed_ - 0.2;

	main_->MoveA(NULL, &move_speed_);
	for (int i = 0; i < max_cube_; i++)
		cube_[i]->MoveA(NULL, &move_speed_);
}


void Target1Sipho::Move2(void)
{
	main_->MoveA(NULL, &move_speed_);
	for (int i = 0; i < max_cube_; i++)
		cube_[i]->MoveA(NULL, &move_speed_);
}
