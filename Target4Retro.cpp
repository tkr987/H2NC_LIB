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
#include "Target4Retro.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target4Retro::Target4Retro(double start_posx, double start_posy, double move_speed, double move_angle, int lv)
{

	// ターゲット、パラメータ
	main_ = new Target(start_posx, start_posy, 16);
	aparam_main_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 変数 初期化
	act11_move_angle_ = CalcRAD(move_angle);
	act11_move_speed_ = move_speed;
	action_ = 10;
	frames_ = 0;
	health_ = 100;
	lv_ = lv;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_main_ = IMG_LOAD_ARMS_PURPLE16T;
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH120;
	if (-90 <= move_angle && move_angle < 90) {
		imgfile_main_ = IMG_LOAD_TARGET_MAIN_STAGE4_RETRO_R;
	} else {
		imgfile_main_ = IMG_LOAD_TARGET_MAIN_STAGE4_RETRO_L;
	}
	imgfile_main_lock_ = IMG_LOAD_TARGET_LOCK_STAGE4_RETRO;
	// サウンドファイル
	soundfile_death_ = SOUND_LOAD_TARGET_DEATH2;
	soundfile_lock_ = SOUND_LOAD_TARGET_LOCK;
	// 爆発エフェクト設定
	eparam_death_->blend_alpha_ = 255;
	eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::NUM::TARGET_EFFECT;
	eparam_death_->img_divmax_ = 32;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 1;
	// Arms Main 固定パラメータ
	aparam_main_->img_id_ = imgfile_arms_main_;
	aparam_main_->shot_pow_ = 1;
	aparam_main_->shot_range_ = ARMS_PARAM_RANGE_PURPLE16T;
	aparam_main_->shot_speed_ = 4.0;
}


Target4Retro::~Target4Retro() {
	delete main_;
	delete aparam_main_;
	delete eparam_death_;
}


void Target4Retro::Run(void)
{

	switch (action_) {
	case 10:
		main_->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		action_ = 11;
		frames_ = -1;
		break;
	case 11:
		Collision();
		Draw();
		Act11_ShotHard();
		Act11_Move();
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


	#ifdef __DEBUG__
		main_->GetPos(&x, NULL);
		DebugPrint::SetData(615, 160, "target_x_: %d", x);
	#endif
}


void Target4Retro::Act11_ShotHard(void)
{
	double angle;
	double angle90;
	int rank_wait;			// ランク依存の弾数

	if (lv_ != LV_HARD)
		return;
	if (frames_ % 30 != 0)
		return;
	if (!main_->InsidePanel())
		return;

	angle = main_->GetAtan(eOBJECT::NUM::USER, POS_NAME_USER_MAIN, 0);
	angle90 = CalcRAD(90);
	DesignManager::GetRank(&rank_wait);
	rank_wait /= 3;
	for (int wait = 0; wait < 4 + rank_wait; wait++) {
		aparam_main_->shot_wait_ = wait * 3;
		aparam_main_->shot_angle_ = angle;
		main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
		aparam_main_->shot_x_ -= (5 * cos(angle + angle90));
		aparam_main_->shot_y_ -= (5 * sin(angle + angle90));
		ArmsManager::TargetShotSmall(aparam_main_);
		aparam_main_->shot_angle_ = angle;
		main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
		aparam_main_->shot_x_ += (5 * cos(angle + angle90));
		aparam_main_->shot_y_ += (5 * sin(angle + angle90));
		ArmsManager::TargetShotSmall(aparam_main_);
	}
}


void Target4Retro::Collision(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	health_ -= damage;
}


void Target4Retro::Delete(double scale, bool effect, bool sound)
{
	double add_alv		= 0.1 * scale;				// 加算ALV
	double add_exarms	= 2.0 * scale;				// 加算ExArms
	double add_rank		= 0.01 * scale;				// 加算ランク
	long   add_score	= (long)(1000 * scale);		// 加算スコア

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


void Target4Retro::Draw(void)
{
	const int divmax_main = 4;

	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % divmax_main;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.5, 0);
}


void Target4Retro::Act11_Move(void)
{
	main_->MoveB(act11_move_angle_, act11_move_speed_);
}

