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
#include "Target4Caulimo.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target4Caulimo::Target4Caulimo(double start_posx, double start_posy, double move_speed, int lv)
{

	// ターゲット、パラメータ
	main_ = new Target(start_posx, start_posy, 16);
	cube_[0] = new Target(start_posx - 150, start_posy - 40, 16);
	cube_[1] = new Target(start_posx - 90, start_posy - 40, 16);
	cube_[2] = new Target(start_posx - 30, start_posy - 40, 16);
	cube_[3] = new Target(start_posx + 30, start_posy - 40, 16);
	cube_[4] = new Target(start_posx + 90, start_posy - 40, 16);
	cube_[5] = new Target(start_posx + 150, start_posy - 40, 16);
	aparam_cube_ = new ArmsParam1;
	aparam_main_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 変数 初期化
	act11_move_speed_ = move_speed;
	act12_cube_shot_angle_l_ = 45;
	act12_cube_shot_angle_r_ = 45;
	action_ = 10;
	frames_ = -1;
	health_ = 300;
	lv_ = lv;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_cube_ = IMG_LOAD_ARMS_GREEN20T;
	imgfile_arms_main_ = IMG_LOAD_ARMS_RED26T;
	imgfile_cube_ = IMG_LOAD_TARGET_CUBE_BLUE140;
	imgfile_cube_lock_ = IMG_LOAD_TARGET_LOCK_CUBE;
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH140;
	imgfile_main_ = IMG_LOAD_TARGET_MAIN_STAGE4_CAULIMO;
	imgfile_main_lock_ = IMG_LOAD_TARGET_LOCK_STAGE4_CAULIMO;
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
	// Arms Cube 固定パラメータ
	aparam_cube_->img_id_ = imgfile_arms_cube_;
	aparam_cube_->shot_pow_ = 1;
	aparam_cube_->shot_range_ = ARMS_PARAM_RANGE_GREEN20T;
	aparam_cube_->shot_speed_ = 7.5;
	// Arms Main 固定パラメータ
	aparam_main_->img_id_ = imgfile_arms_main_;
	aparam_main_->shot_pow_ = 1;
	aparam_main_->shot_range_ = ARMS_PARAM_RANGE_RED26T;
	aparam_main_->shot_speed_ = 3.5;
	aparam_main_->shot_wait_ = 0;
}


Target4Caulimo::~Target4Caulimo() {
	delete main_;
	delete aparam_cube_;
	delete aparam_main_;
	delete eparam_death_;
}


void Target4Caulimo::Run(void)
{

	switch (action_) {
	case 10:
		srand(16);
		main_->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		for (int i = 0; i < 6; i++)
			cube_[i]->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		action_ = 11;
		frames_ = -1;
		break;
	case 11:
		Collision1();
		Draw();
		Act11_Move();
		if (act11_move_speed_ == 0) {
			action_ = 12;
			frames_ = -1;
		}
		if (health_ < 0) {
			action_ = 20;
			frames_ = -1;
		}
		if (frames_ == 1000) {
			action_ = 21;
			frames_ = -1;
		}
		break;
	case 12:
		Act12_CubeShotHard();
		Act12_MainShotHard(0, 0);
		Act12_MainShotHard(5, 90);
		Act12_MainShotHard(0, 180);
		Act12_MainShotHard(5, 270);
		Collision2();
		Draw();
		if (health_ < 0) {
			action_ = 20;
			frames_ = -1;
		}
		if (frames_ == 1000) {
			action_ = 21;
			frames_ = -1;
		}
		break;
	case 20:
		ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_LARGE);
		ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_SMALL);
		ImgManager::SwingY(20, 3);
		Delete(1.0, true, true);
		action_ = 22;
		frames_ = -1;
		break;
	case 21:
		Delete(0.0, false, false);
		action_ = 22;
		frames_ = -1;
		break;
	case 22:
		// 終了
		break;
	}

	frames_++;
}


void Target4Caulimo::Act11_Move(void)
{
	double main_y;

	for (int i = 0; i < 6; i++)
		cube_[i]->MoveA(NULL, &act11_move_speed_);
	main_->MoveA(NULL, &act11_move_speed_);
	main_->GetPos(NULL, &main_y);

	if (main_y < 60)
		return;

	if (act11_move_speed_ - 0.1 < 0) {
		act11_move_speed_ = 0;
	} else {
		act11_move_speed_ -= 0.1;
	}
}


void Target4Caulimo::Act12_CubeShotHard(void)
{

	if (lv_ != LV_HARD)
		return;

	if (frames_ % 20 != 0)
		return;

	for (int i = 0; i < 3; i++) {
		if (!cube_[i]->InsidePanel())
			continue;
		aparam_cube_->shot_angle_ = CalcRAD(act12_cube_shot_angle_l_);
		for (int wait = 0; wait < 8; wait++) {
			cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			aparam_cube_->shot_wait_ = wait * 2;
			ArmsManager::TargetShotSmall(aparam_cube_);
		}
		aparam_cube_->shot_angle_ = CalcRAD(act12_cube_shot_angle_l_ + 90);
		for (int wait = 0; wait < 8; wait++) {
			cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			aparam_cube_->shot_wait_ = wait * 2;
			ArmsManager::TargetShotSmall(aparam_cube_);
		}
		aparam_cube_->shot_angle_ = CalcRAD(act12_cube_shot_angle_l_ + 180);
		for (int wait = 0; wait < 8; wait++) {
			cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			aparam_cube_->shot_wait_ = wait * 2;
			ArmsManager::TargetShotSmall(aparam_cube_);
		}
		aparam_cube_->shot_angle_ = CalcRAD(act12_cube_shot_angle_l_);
		for (int wait = 0; wait < 8; wait++) {
			cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			aparam_cube_->shot_wait_ = wait * 2;
			ArmsManager::TargetShotSmall(aparam_cube_);
		}
	}

	for (int i = 3; i < 6; i++) {
		if (!cube_[i]->InsidePanel())
			continue;
		aparam_cube_->shot_angle_ = CalcRAD(act12_cube_shot_angle_r_);
		for (int wait = 0; wait < 8; wait++) {
			cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			aparam_cube_->shot_wait_ = wait * 2;
			ArmsManager::TargetShotSmall(aparam_cube_);
		}
		aparam_cube_->shot_angle_ = CalcRAD(act12_cube_shot_angle_r_ + 90);
		for (int wait = 0; wait < 8; wait++) {
			cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			aparam_cube_->shot_wait_ = wait * 2;
			ArmsManager::TargetShotSmall(aparam_cube_);
		}
		aparam_cube_->shot_angle_ = CalcRAD(act12_cube_shot_angle_r_ + 180);
		for (int wait = 0; wait < 8; wait++) {
			cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			aparam_cube_->shot_wait_ = wait * 2;
			ArmsManager::TargetShotSmall(aparam_cube_);
		}
		aparam_cube_->shot_angle_ = CalcRAD(act12_cube_shot_angle_r_ + 270);
		for (int wait = 0; wait < 8; wait++) {
			cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			aparam_cube_->shot_wait_ = wait * 2;
			ArmsManager::TargetShotSmall(aparam_cube_);
		}
	}

	act12_cube_shot_angle_l_ -= 20;
	act12_cube_shot_angle_r_ += 20;
}


void Target4Caulimo::Act12_MainShotHard(double shot_frames, double base_angle)
{
	double angle;
	int rank_freq;			// ランク依存の弾数

	if (lv_ != LV_HARD)
		return;
	if (!main_->InsidePanel())
		return;

	DesignManager::GetRank(&rank_freq);
	if (frames_ % (20 - rank_freq) != shot_frames)
		return;

	angle = CalcRAD(base_angle + rand() % 90);
	aparam_main_->shot_angle_ = angle;
	for (int way = 0; way < 4; way++) {
		main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
		aparam_main_->shot_angle_ += CalcRAD(3);
		ArmsManager::TargetShotLarge(aparam_main_);
	}
	aparam_main_->shot_angle_ = angle;
	main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
	ArmsManager::TargetShotLarge(aparam_main_);
	for (int way = 0; way < 4; way++) {
		main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
		aparam_main_->shot_angle_ -= CalcRAD(3);
		ArmsManager::TargetShotLarge(aparam_main_);
	}
}


void Target4Caulimo::Collision1(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	for (int i = 0; i < 6; i++) {
		damage += cube_[i]->Collision(extension);
		cube_[i]->CollisionImg(imgfile_cube_lock_, 0, interval);
		cube_[i]->CollisionSound(soundfile_lock_, interval);
		DesignManager::AddScore(damage);
	}
//	health_ -= damage;
}


void Target4Caulimo::Collision2(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	for (int i = 0; i < 6; i++) {
		damage += cube_[i]->Collision(extension);
		cube_[i]->CollisionImg(imgfile_cube_lock_, 0, interval);
		cube_[i]->CollisionSound(soundfile_lock_, interval);
		DesignManager::AddScore(damage);
	}
	health_ -= damage;
}


void Target4Caulimo::Delete(double scale, bool effect, bool sound)
{
	double add_alv		= 0.1 * scale;				// 加算ALV
	double add_exarms	= 2.0 * scale;				// 加算ExArms
	double add_rank		= 0.01 * scale;				// 加算ランク
	long   add_score	= (long)(1000 * scale);		// 加算スコア

	// エフェクト追加
	if (effect) {
		main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
		for (int i = 0; i < 6; i++) {
			cube_[i]->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
		}
	}

	// サウンド追加
	if (sound)
		SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);

	// 削除処理
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
	for (int i = 0; i < 6; i++)
		cube_[i]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Target4Caulimo::Draw(void)
{
	const int divmax_cube = 5;
	const int divmax_main = 12;

	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cube_ = ++imgdiv_cube_ % divmax_cube;
	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % divmax_main;

	for (int i = 0; i < 6; i++)
		cube_[i]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
	main_->Draw(imgfile_main_, imgdiv_main_, 1.5, 0);
}



