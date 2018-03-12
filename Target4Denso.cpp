#include <float.h>
#include <fstream>
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
#include "TargetBase.h"
#include "Target4Denso.h"

using namespace NH2;
using namespace NH2T;


Target4Denso::Target4Denso(double start_posx, double end_posy, int lv)
{
	const double start_posy = -200.0;

	// ターゲット、パラメータ生成
	main_ = new Target(start_posx, start_posy, 15);
	cube_[0] = new Target(start_posx - 60, start_posy - 45, 16);
	cube_[1] = new Target(start_posx - 30, start_posy - 30, 16);
	cube_[2] = new Target(start_posx + 30, start_posy - 30, 16);
	cube_[3] = new Target(start_posx + 60, start_posy - 45, 16);
	aparam_cube_ = new ArmsParam1;
	aparam_main_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 変数 初期化
	action_ = 10;
	frames_ = 0;
	health_ = 100;
	lv_ = lv;
	act11_end_position_y_ = end_posy;
	act11_move_speed_ = 5.0;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_cube_ = IMG_LOAD_ARMS_RED20T;
	imgfile_arms_main_ = IMG_LOAD_ARMS_RED26T;
	imgfile_cube_ = IMG_LOAD_TARGET_CUBE_BLUE140;
	imgfile_cube_lock_ = IMG_LOAD_TARGET_LOCK_CUBE;
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH120;
	imgfile_main_ = IMG_LOAD_TARGET_MAIN_STAGE4_DENSO;
	imgfile_main_lock_ = IMG_LOAD_TARGET_LOCK_STAGE4_DENSO;
	// サウンドファイル
	soundfile_death_ = SOUND_LOAD_TARGET_DEATH2;
	soundfile_lock_ = SOUND_LOAD_TARGET_LOCK;
	// Effect Death 固定パラメータ
	eparam_death_->blend_alpha_ = 255;
	eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::NUM::TARGET_EFFECT;
	eparam_death_->img_divmax_ = 32;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 1;
	// Arms Cube 固定パラメータ
	aparam_cube_->shot_pow_ = 1.0;
	aparam_cube_->shot_range_ = ARMS_PARAM_RANGE_RED20T;
	aparam_cube_->shot_speed_ = 8.0;
	aparam_cube_->img_angle_ = 0;
	aparam_cube_->img_id_ = imgfile_arms_cube_;
	// Arms Main 固定パラメータ
	aparam_main_->shot_pow_ = 1.0;
	aparam_main_->shot_range_ = ARMS_PARAM_RANGE_RED26T;
	aparam_main_->shot_speed_ = 5.0;
	aparam_main_->shot_wait_ = 0;
	aparam_main_->img_angle_ = 0;
	aparam_main_->img_id_ = imgfile_arms_main_;
}


Target4Denso::~Target4Denso()
{
	delete main_;
	for (int i = 0; i < 4; i++)
		delete cube_[i];
	delete aparam_main_;
	delete aparam_cube_;
}


void Target4Denso::Run(void)
{
	switch(action_) {
	case 10:
		main_->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		for (int i = 0; i < 4; i++)
			cube_[i]->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		action_ = 11;
		frames_ = -1;
		break;
	case 11:
		Collision();
		Draw();
		Act11_Move();
		if (act11_move_speed_ == 0) {
			action_ = 12;
			frames_ = -1;
		}
		if (health_ < 0) {
			action_ = 14;
			frames_ = -1;
		}
		break;
	case 12:
		Collision();
		Draw();
		ShotCubeHard();
		ShotMainHard();
		if (frames_ == 50) {
			action_ = 13;
			frames_ = -1;
		}
		if (health_ < 0) {
			action_ = 14;
			frames_ = -1;
		}
		break;
	case 13:
		Act13_Move();
		Collision();
		Draw();
		ShotCubeHard();
		ShotMainHard();
		if (health_ < 0) {
			action_ = 14;
			frames_ = -1;
		}
		if (frames_ == 2000) {
			action_ = 15;
			frames_ = -1;
		}
		break;
	case 14:
		Delete(1.0, true, true);
		action_ = 16;
		frames_ = -1;
		break;
	case 15:
		Delete(0.0, false, false);
		action_ = 16;
		frames_ = -1;
		break;
	case 16:
		// 終了
		break;
	}

	frames_++;
}



void Target4Denso::Act11_Move(void)
{
	double y;

	main_->MoveA(NULL, &act11_move_speed_);
	for (int i = 0; i < 4; i++)
		cube_[i]->MoveA(NULL, &act11_move_speed_);

	main_->GetPos(NULL, &y);
	if (act11_end_position_y_ < y)
		act11_move_speed_ = (act11_move_speed_ - 0.2 < 0) ? 0 : act11_move_speed_ - 0.2;	
}


void Target4Denso::Act13_Move(void)
{
	if (frames_ == 0)
		act13_move_angle_ = main_->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);

	act13_move_speed_ = (4.0 < act13_move_speed_ + 0.1) ? 4.0 : act13_move_speed_ + 0.1;
	main_->MoveB(act13_move_angle_, act13_move_speed_);
	for (int i = 0; i < 4; i++)
		cube_[i]->MoveB(act13_move_angle_, act13_move_speed_);
}


void Target4Denso::Collision(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	for (int i = 0; i < 4; i++) {
		damage += cube_[i]->Collision(extension);
		cube_[i]->CollisionImg(imgfile_cube_lock_, 0, interval);
		cube_[i]->CollisionSound(soundfile_lock_, interval);
		DesignManager::AddScore(damage);
	}
	health_ -= damage;
}


void Target4Denso::Delete(double scale, bool effect, bool sound)
{
	double add_alv		= 0.1 * scale;				// 加算ALV
	double add_exarms	= 2.0 * scale;				// 加算ExArms
	double add_rank		= 0.01 * scale;				// 加算ランク
	long   add_score	= (long)(1000 * scale);		// 加算スコア

	// エフェクト追加
	if (effect) {
		main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
		for (int i = 0; i < 4; i++) {
			cube_[i]->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
		}
	}

	// サウンド追加
	if (sound)
		SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);

	// 削除処理
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
	for (int i = 0; i < 4; i++)
		cube_[i]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Target4Denso::Draw(void)
{
	const int divmax_cube = 5;
	const int divmax_main = 4;

	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cube_ = ++imgdiv_cube_ % divmax_cube;
	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % divmax_main;

	for (int i = 0; i < 4; i++)
		cube_[i]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
	main_->Draw(imgfile_main_, imgdiv_main_, 1.5, 0);
}


void Target4Denso::ShotMainHard(void)
{
	if (frames_ % 30 != 0)
		return;

	aparam_main_->shot_angle_ = main_->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
	for (int way = 0; way < 4; way++) {
		main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
		aparam_main_->shot_angle_ -= CalcRAD(3);
		ArmsManager::TargetShotLarge(aparam_main_);
	}
	aparam_main_->shot_angle_ = main_->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
	main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
	ArmsManager::TargetShotLarge(aparam_main_);
	aparam_main_->shot_angle_ = main_->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
	for (int way = 0; way < 4; way++) {
		main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
		aparam_main_->shot_angle_ += CalcRAD(3);
		ArmsManager::TargetShotLarge(aparam_main_);
	}
}


void Target4Denso::ShotCubeHard(void)
{
	double rank_wait;

	if (frames_ % 20 != 0)
		return;

	DesignManager::GetRank(&rank_wait, 0.3);
	for (int i = 0; i < 4; i++) {
		if (!cube_[i]->InsidePanel())
			continue;
		aparam_cube_->shot_angle_ = cube_[i]->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
		for (int wait = 0; wait < 5 + rank_wait; wait++) {
			cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			aparam_cube_->shot_wait_ = wait * 2;
			ArmsManager::TargetShotSmall(aparam_cube_);
		}
	}
}
