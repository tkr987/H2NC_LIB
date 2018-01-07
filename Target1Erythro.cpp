#include "DxLib.h"
#include "ArmsManager.h"
#include "DesignManager.h"
#include "EffectManager.h"
#include "FpsManager.h"
#include "ImgManager.h"
#include "PosManager.h"
#include "SoundManager.h"
#include "Target.h"
#include "Target1Erythro.h"
#include "DefineNH.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target1Erythro::Target1Erythro(double start_posx, double end_posy, int lv)
{
	// ターゲット、パラメータ　生成
	main_ = new Target(start_posx, -150, 15);
	cube_[0] = new Target(start_posx + 64, -150, 15);
	cube_[1] = new Target(start_posx - 64, -150, 15);
	aparam_cube_ = new ArmsParam1;
	aparam_main_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 変数 初期化
	act11_move_speed_ = 5.0;
	act13_shot_angle_r_ = CalcRAD(-30);
	act13_shot_angle_l_ = CalcRAD(210);
	act15_move_speed_ = 0.0;
	cube_max_ = 2;
	end_posy_ = end_posy;
	health_ = 200;
	lv_ = lv;
	phase_ = 10;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_cube_ = IMG_LOAD_ARMS_BLUE32T;
	imgfile_arms_main_ = IMG_LOAD_ARMS_BLUE20T;
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH140;
	imgfile_cube_ = IMG_LOAD_TARGET_CUBE_BLUE140;
	imgfile_cube_lock_ = IMG_LOAD_TARGET_LOCK_CUBE;
	imgfile_main_ = IMG_LOAD_TARGET_MAIN_STAGE1_ERYTHRO;
	imgfile_main_lock_ = IMG_LOAD_TARGET_LOCK_STAGE1_ERYTHRO;
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
	aparam_cube_->img_angle_ = 0;
	aparam_cube_->img_id_ = imgfile_arms_cube_;
	aparam_cube_->img_rotate_ = 0;
	aparam_cube_->shot_pow_ = 1;
	aparam_cube_->shot_range_ = 4.0;
	aparam_cube_->shot_speed_ = 6;
	// Arms Main 固定パラメータ
	aparam_main_->img_angle_ = 0;
	aparam_main_->img_id_ = imgfile_arms_main_;
	aparam_main_->img_rotate_ = 0;
	aparam_main_->shot_pow_ = 1;
	aparam_main_->shot_range_ = ARMS_PARAM_RANGE_BLUE20T;
	aparam_main_->shot_speed_ = 2;
	aparam_main_->shot_wait_ = 0;
}


Target1Erythro::~Target1Erythro() {
	delete main_;
	delete cube_[0];
	delete cube_[1];
	delete aparam_cube_;
	delete aparam_main_;
	delete eparam_death_;
}


void Target1Erythro::Action(void) {


	switch(phase_) {
	case 10:
		main_->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		cube_[0]->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		cube_[1]->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		phase_ = 11;
		frames_ = -1;
		break;
	case 11:
		Act11_Move();
		Collision();
		if (act11_move_speed_ == 0) {
			phase_ = 12;
			frames_ = -1;
		}
		if (health_ < 0) {
			phase_ = 16;
			frames_ = 0;
		}
		break;
	case 12:
		Collision();
		if (frames_ == 50) {
			phase_ = 13;
			frames_ = -1;
		}
		if (health_ < 0) {
			phase_ = 16;
			frames_ = 0;
		}
		break;
	case 13:
		Act13_ShotHard();
		Act13_ShotHardR();
		Act13_ShotHardL();
		Collision();
		if (frames_ == 132) {
			phase_ = 14;
			frames_ = -1;
		}
		if (health_ < 0) {
			phase_ = 16;
			frames_ = 0;
		}
		break;
	case 14:
		Collision();
		if (frames_ == 300) {
			phase_ = 15;
			frames_ = -1;
		}
		if (health_ < 0) {
			phase_ = 16;
			frames_ = 0;
		}
		break;
	case 15:
		Act15_Move();
		Collision();
		if (frames_ == 400) {
			phase_ = 17;
			frames_ = -1;
		}
		if (health_ < 0) {
			phase_ = 16;
			frames_ = 0;
		}
		break;
	case 16:
		Delete(1.0, true, true);
		ArmsManager::DeleteAll(eOBJECT::TARGET_ARMS_LARGE);
		ArmsManager::DeleteAll(eOBJECT::TARGET_ARMS_SMALL);
		ImgManager::SwingY(20, 3);
		phase_ = 18;
		frames_ = -1;
		break;
	case 17:
		Delete(0.0, false, false);
		phase_ = 18;
		frames_ = -1;
		break;
	case 18:
		// 終了
		break;
	}

	frames_++;
}


void Target1Erythro::Act13_ShotHard(void)
{
	if (lv_ != LV_HARD)
		return;
	if (frames_ % 20 != 0)
		return;
	if (!main_->InsidePanel())
		return;

	main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
	aparam_main_->shot_angle_ = CalcRAD(90);
	for (int way = 0; way < 40; way++) {
		aparam_main_->shot_angle_ -= CalcRAD(2.0);
		ArmsManager::TargetShotSmall(aparam_main_);
	}
	aparam_main_->shot_angle_ = CalcRAD(90);
	ArmsManager::TargetShotSmall(aparam_main_);
	aparam_main_->shot_angle_ = CalcRAD(90);
	for (int way = 0; way < 40; way++) {
		aparam_main_->shot_angle_ += CalcRAD(2.0);
		ArmsManager::TargetShotSmall(aparam_main_);
	}

}


void Target1Erythro::Act13_ShotHardR(void)
{
	int rank_wait;

	if (lv_ != LV_HARD)
		return;
	if (frames_ % 6 != 0)
		return;
	if (!cube_[0]->InsidePanel())
		return;

	DesignManager::GetRank(&rank_wait, 0.5);
	for (int wait = 0; wait != 15 + rank_wait; wait++) {
		aparam_cube_->shot_wait_ = wait * 4;
		aparam_cube_->shot_angle_ = act13_shot_angle_r_;
		cube_[0]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
		ArmsManager::TargetShotSmall(aparam_cube_);
	}

	act13_shot_angle_r_ += CalcRAD(10);
}


void Target1Erythro::Act13_ShotHardL(void)
{
	int rank_wait;

	if (lv_ != LV_HARD)
		return;
	if (frames_ % 6 != 0)
		return;
	if (!cube_[1]->InsidePanel())
		return;

	DesignManager::GetRank(&rank_wait);
	for (int wait = 0; wait != 15 + rank_wait; wait++) {
		aparam_cube_->shot_wait_ = wait * 4;
		aparam_cube_->shot_angle_ = act13_shot_angle_l_;
		cube_[1]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
		ArmsManager::TargetShotSmall(aparam_cube_);
	}

	act13_shot_angle_l_ -= CalcRAD(10);
}


void Target1Erythro::Collision(void)
{
	double damage = 0;				// １フレームあたりのダメージ
	const int extension = 0;		// draw_window 拡張
	const int interval = 50;		// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += cube_[0]->Collision(extension);
	cube_[0]->CollisionImg(imgfile_cube_lock_, 0, interval);
	cube_[0]->CollisionSound(soundfile_lock_, interval);
	damage += cube_[1]->Collision(extension);
	cube_[1]->CollisionImg(imgfile_cube_lock_, 0, interval);
	cube_[1]->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	health_ -= damage;
}


void Target1Erythro::Delete(double scale, bool effect, bool sound)
{
	double add_alv		= 1.000 * scale;			// 加算ALV
	double add_exarms	= 5.000 * scale;			// 加算ExArms
	double add_rank		= 0.008 * scale;			// 加算ランク
	long   add_score	= (long)(2000 * scale);		// 加算スコア

	// エフェクト追加
	if (effect) {
		main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
		for (int i = 0; i < cube_max_; i++) {
			cube_[i]->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
		}
	}

	// サウンド追加
	if (sound)
		SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);

	// 削除処理
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
	for (int i = 0; i < cube_max_; i++)
		cube_[i]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Target1Erythro::Draw(void)
{
	const int divmax_cube = 5;
	const int divmax_main = 4;

	switch(phase_) {
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		if (FpsManager::GetInterval(4) == 0)
			imgdiv_cube_ = ++imgdiv_cube_ % divmax_cube;
		if (FpsManager::GetInterval(20) == 0)
			imgdiv_main_ = ++imgdiv_main_ % divmax_main;

		for (int i = 0; i < cube_max_; i++)
			cube_[i]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
		main_->Draw(imgfile_main_, imgdiv_main_, 1.5, 0);
		break;
	}
}

void Target1Erythro::Act11_Move(void)
{
	double y;
	const double move_angle = CalcRAD(90.0);

	main_->GetPos(NULL, &y);
	if (end_posy_ < y)
		act11_move_speed_ = (act11_move_speed_ - 0.2 < 0) ? 0 : act11_move_speed_ - 0.2;

	main_->MoveB(move_angle, act11_move_speed_);
	cube_[0]->MoveB(move_angle, act11_move_speed_);
	cube_[1]->MoveB(move_angle, act11_move_speed_);
}


void Target1Erythro::Act15_Move(void)
{
	const double move_angle = CalcRAD(-90.0);

	act15_move_speed_ = (4.0 < act15_move_speed_ + 0.01) ? 2.0 : act15_move_speed_ + 0.01;

	main_->MoveB(move_angle, act15_move_speed_);
	cube_[0]->MoveB(move_angle, act15_move_speed_);
	cube_[1]->MoveB(move_angle, act15_move_speed_);
}
