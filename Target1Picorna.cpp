#include "DxLib.h"
#include "ArmsManager.h"
#include "DesignManager.h"
#include "EffectManager.h"
#include "FpsManager.h"
#include "ImgManager.h"
#include "PosManager.h"
#include "SoundManager.h"
#include "Target.h"
#include "Target1Picorna.h"
#include "DefineNH.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target1Picorna::Target1Picorna(double start_posx, double start_posy, int lv)
{
	// 変数 初期化
	frames_ = 0;
	health_ = 5;
	phase_ = 10;
	lv_ = lv;
	draw_angle_ = rand() % 360;
	main_ = new Target(start_posx, start_posy, 15);
	aparam_cube_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 画像ファイル
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH120;
	imgfile_main_ = IMG_LOAD_TARGET_MAIN_STAGE1_PICORNA;
	imgfile_main_lock_ = IMG_LOAD_TARGET_LOCK_STAGE1_PICORNA;
	// サウンドファイル
	soundfile_death_ = SOUND_LOAD_TARGET_DEATH2;
	soundfile_lock_ = SOUND_LOAD_TARGET_LOCK;
	// ARMS CUBE 固定パラメータ
	aparam_cube_->img_angle_ = 0;
	aparam_cube_->shot_pow_ = 1;
	aparam_cube_->shot_range_ = 2.0;
	// 爆発エフェクト設定
	eparam_death_->blend_alpha_ = 255;
	eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::NUM::TARGET_EFFECT;
	eparam_death_->img_divmax_ = 32;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 1;
}

Target1Picorna::~Target1Picorna() {
	delete main_;
	delete aparam_cube_;
	delete eparam_death_;
}

/*!
@brief 実行関数
*/
void Target1Picorna::Action(void) 
{
	switch(phase_) {
	case 10:
		main_->SetGroup(eOBJECT::NUM::TARGET_RUN_FLY);
		phase_ = 11;
		frames_ = -1;
		break;
	case 11:
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
	}
	
	frames_++;
}


void Target1Picorna::Draw(void)
{	
	switch (phase_){
	case 11:
		draw_angle_ += CalcRAD(2);
		main_->Draw(imgfile_main_, 0, draw_angle_);
		break;
	}
}


void Target1Picorna::Collision(void)
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


void Target1Picorna::Delete(double scale, bool effect, bool sound)
{
	double add_alv		= 0.05 * scale;				// 加算ALV
	double add_exarms	= 0.10 * scale;				// 加算ExArms
	double add_rank		= 0.01 * scale;				// 加算ランク
	long   add_score	= (long)(50 * scale);		// 加算スコア

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


void Target1Picorna::Move(void)
{
	const double move_speed = 4.0;
	const double move_angle = CalcRAD(90.0);

	main_->MoveB(move_angle, move_speed);
}
