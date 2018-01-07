#include "DxLib.h"
#include "ArmsManager.h"
#include "DesignManager.h"
#include "EffectManager.h"
#include "FpsManager.h"
#include "ImgManager.h"
#include "PosManager.h"
#include "SoundManager.h"
#include "Target.h"
#include "TargetBase.h"
#include "Target1Anello.h"
#include "DefineNH.h"
#include "DebugPrint.h"

#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target1Anello::Target1Anello(double start_posx, double start_posy, int lv)
{
	// ターゲット、パラメータ 生成
	main_ = new Target(start_posx, start_posy, 16);
	aparam_main_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 変数 初期化
	frames_ = 0;
	health_ = 10;
	lv_ = lv;
	phase_ = 10;
	// 画像ファイル
	imgdiv_main_ = 0;
	imgfile_arms_ = IMG_LOAD_ARMS_RED20T;
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH120;
	imgfile_main_ = IMG_LOAD_TARGET_MAIN_STAGE1_ANELLO;
	imgfile_main_lock_ = IMG_LOAD_TARGET_LOCK_STAGE1_ANELLO;
	// サウンドファイル
	soundfile_death_ = SOUND_LOAD_TARGET_DEATH2;
	soundfile_lock_ = SOUND_LOAD_TARGET_LOCK;
	// 爆発エフェクト設定
	eparam_death_->blend_alpha_ = 255;
	eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::GROUP::TARGET_EFFECT;
	eparam_death_->img_divmax_ = 32;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 1;
	// Arms Main 固定パラメータ
	aparam_main_->img_id_ = imgfile_arms_;
	aparam_main_->img_angle_ = 0.0;
	aparam_main_->img_rotate_ = 0.0;
	aparam_main_->shot_pow_ = 1.0;
	aparam_main_->shot_range_ = ARMS_PARAM_RANGE_GREEN20T;
	aparam_main_->shot_wait_ = 0;
}


Target1Anello::~Target1Anello()
{
	delete main_;
	delete aparam_main_;
	delete eparam_death_;
}


void Target1Anello::Action(void)
{
	switch (phase_) {
	case 10:
		main_->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		phase_ = 11;
		frames_ = -1;
		break;
	case 11:
		ShotHard();
		Collision();
		Move();
		if (health_ < 0) {
			phase_ = 12;
			frames_ = -1;
		}
		if (frames_ == 2000) {
			phase_ = 13;
			frames_ = -1;
		}
		break;
	case 12:
		Delete(1.0, true, true);
		phase_ = 14;
		frames_ = -1;
		break;
	case 13:
		Delete(0.0, false, false);
		phase_ = 14;
		frames_ = -1;
		break;
	case 14:
		// 終了
		break;
	default:
		break;
	}

	frames_++;
}

void Target1Anello::Draw(void)
{
	const int divmax_main = 8;

	switch (phase_) {
	case 11:
		if (FpsManager::GetInterval(20) == 0)
			imgdiv_main_ = ++imgdiv_main_ % divmax_main;
		main_->Draw(imgfile_main_, imgdiv_main_, 0);
		break;
	}
}


void Target1Anello::ShotHard(void)
{
	double rank_speed;

	if (lv_ != LV_HARD)
		return;
	if (frames_ % 150 != 0 && frames_ % 150 != 25)
		return;
	if (!main_->InsidePanel(-32))
		return;

	DesignManager::GetRank(&rank_speed, 0.3);
	main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
	aparam_main_->shot_speed_ = 5.0 + rank_speed;
	aparam_main_->shot_angle_ = CalcRAD(90);
	for (int i = 0; i < 3; i++) {
		aparam_main_->shot_angle_ -= CalcRAD(10);
		ArmsManager::TargetShotSmall(aparam_main_);
	}
	aparam_main_->shot_angle_ = CalcRAD(90);
	ArmsManager::TargetShotSmall(aparam_main_);
	aparam_main_->shot_angle_ = CalcRAD(90);
	for (int i = 0; i < 3; i++) {
		aparam_main_->shot_angle_ += CalcRAD(10);
		ArmsManager::TargetShotSmall(aparam_main_);
	}
}


void Target1Anello::Collision(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// draw_window 拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	health_ -= damage;
}


void Target1Anello::Delete(double scale, bool effect, bool sound)
{
	double add_alv		= 0.050 * scale;			// 加算ALV
	double add_exarms	= 1.000 * scale;			// 加算ExArms
	double add_rank		= 0.004 * scale;			// 加算ランク
	long   add_score	= (long)(100 * scale);		// 加算スコア

	// エフェクト追加
	if (effect) {
		main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
	}

	// サウンド追加
	if (sound)
		SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);

	// 削除処理
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Target1Anello::Move(void)
{
	const double move_speed = 2.0;
	const double move_angle = CalcRAD(90.0);

	main_->MoveB(move_angle, move_speed);
}
