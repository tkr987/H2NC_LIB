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
#include "Target3Rhabdo.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target3Rhabdo::Target3Rhabdo(double start_posx, double start_posy, int lv)
{
	// 変数 初期化
	action_ = 0;
	count_frames_ = 0;
	health_ = 100;
	lv_ = lv;
	delete_flag_ = false;
	main_ = new Target(start_posx, start_posy, 15);
	aparam_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
//	imgdiv_main_shadow_ = 0;
//	imgfile_arms_cube_ = ImgManager::LoadImg("data/10_img_arms/ArmsBlue20.png");
	imgfile_arms_main_ = ImgManager::LoadImg("data/img_target/Arms1Red.png");
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH120;
//	imgfile_cube_ = ImgManager::LoadImg(IMG_TARGET_CUBE140_NUMX, IMG_TARGET_CUBE140_NUMY, IMG_TARGET_CUBE140_SIZEX, IMG_TARGET_CUBE140_SIZEY, "data/img_target/CubeOrange140.png");
//	imgfile_cube_lock_ = ImgManager::LoadImg("data/img_target/LockCube.png");
	imgfile_main_ = ImgManager::LoadImg(2, 1, 32, 32, "data/img_target/Target3Rhabdo.png");
	imgfile_main_lock_ = ImgManager::LoadImg("data/img_target/LockRhabdo.png");
	// サウンドファイル
	soundfile_bomb_ = SoundManager::Load("data/sound/target_bomb2.wav");
	soundfile_lock_ = SoundManager::Load("data/sound/target_lock.wav");
	// 爆発エフェクト設定
	eparam_death_->blend_alpha_ = 255;
	eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::GROUP::TARGET_EFFECT;
	eparam_death_->img_divmax_ = 32;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 1;
	// ARMS CUBE 固定パラメータ
	aparam_->hit_effect_ = false;
	aparam_->img_id_ = imgfile_arms_main_;
	aparam_->img_rotate_ = false;
	aparam_->shot_pow_ = 1;
	aparam_->shot_range_ = 2.0;
}


Target3Rhabdo::~Target3Rhabdo() {
	delete main_;
	delete aparam_;
}


void Target3Rhabdo::Run(void)
{

	if (delete_flag_)
		return;

	// *****************
	//  共通アクション
	// *****************
	Collision();
	Draw();
	if (2000 < count_frames_) {
		action_ = 100;
	} else if (health_ < 0) {
		action_ = 101;
	}

	// *****************
	//  アクション分岐
	// *****************
	switch (action_) {
	case 0:
		AttackNormal();
		Attack1Hard();
		break;
	case 100:
		Delete(0, false, false);
		delete_flag_ = true;
		break;
	case 101:
		Delete(1.0, true, true);
		delete_flag_ = true;
		break;
	}

	count_frames_++;
}


void Target3Rhabdo::Attack1Hard(void)
{
	int frames60 = count_frames_ % 60;

	if (lv_ != LV_HARD)
		return;
	if (frames60 != 40)
		return;

	// 攻撃速度更新
	aparam_->shot_speed_ = 4.0;

	// ************
	//  攻撃処理
	// ************
	if (main_->InsidePanel(-16)) {
		main_->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
		for (int wait = 0; wait < 20; wait += 4) {
			aparam_->shot_wait_ = wait;
			aparam_->shot_angle_ = CalcRAD(-180);
			ArmsManager::TargetShotSmall(aparam_);
		}
	}
}


void Target3Rhabdo::AttackNormal(void)
{

}


void Target3Rhabdo::Collision(void)
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


void Target3Rhabdo::Delete(double scale, bool effect, bool sound)
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
		SoundManager::Play(soundfile_bomb_, DX_PLAYTYPE_BACK);

	// 削除処理
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Target3Rhabdo::Draw(void)
{
	int frames60 = count_frames_ % 60;
	const int divmax_main = 2;

	if (0 <= frames60 && frames60 < 40) {
		imgdiv_main_ = 0;
	} else if (40 <= frames60 && frames60 < 60) {
		imgdiv_main_ = 1;
	}

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);
}


void Target3Rhabdo::Move1(void)
{

}

