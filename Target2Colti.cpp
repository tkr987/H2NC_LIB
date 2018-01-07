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
#include "Target2Colti.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target2Colti::Target2Colti(double start_posx, double start_posy, double move_angle, double move_speed, unsigned int lv)
{

	// 変数 初期化
	action_ = 0;
	damage_ = 0;
	frames_ = 0;
	lv_ = lv;
	delete_flag_ = false;
	move_angle_ = CalcRAD(move_angle);
	move_speed_ = move_speed;
	main_ = new Target(start_posx, start_posy, 15);
	aparam_main_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 画像ファイル
	imgdiv_main_ = 0;
//	imgfile_death_ = ImgManager::LoadImg(IMG_TARGET_DEATH2_NUMX, IMG_TARGET_DEATH2_NUMY, IMG_TARGET_DEATH2_SIZEX, IMG_TARGET_DEATH2_SIZEY, "data/img_target/Death2.png");
	imgfile_main_ = ImgManager::LoadImg(7, 2, 36, 36, "data/img_target/MainColti.png");
	imgfile_main_arms_ = ImgManager::LoadImg("data/img_target/Arms1Red.png");
	imgfile_main_lock_ = ImgManager::LoadImg("data/img_target/LockColti.png");
	// サウンドファイル
	soundfile_delete_ = SoundManager::Load("data/sound/target_death2.wav");
	soundfile_lock_ = SoundManager::Load("data/sound/target_lock.wav");
	// ARMS CUBE 固定パラメータ
	aparam_main_->img_angle_ = 0;
	aparam_main_->img_id_ = imgfile_main_arms_;
	aparam_main_->img_rotate_ = 0;
	aparam_main_->shot_pow_ = 1;
	aparam_main_->shot_range_ = 4.0;
	// 爆発エフェクト設定
	eparam_death_->blend_alpha_ = 255;
	eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::GROUP::TARGET_EFFECT;
	eparam_death_->img_divmax_ = 32;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 1;
}

Target2Colti::~Target2Colti()
{
	delete main_;
	delete aparam_main_;
}

void Target2Colti::Run(void) 
{

	if (delete_flag_)
		return;

	frames_++;

	// ランク更新
	if (frames_ == 1) {
		DesignManager::GetRank(&rank_);
		rank_ = rank_ / 100;
	}

	Move();

	// 攻撃
	if (lv_ == LV_HARD) {
		Attack(6 + rank_);
	} else {
		Attack(4 + rank_);
	}

	Draw();
	Collision();
	Delete();
}

void Target2Colti::Attack(double shot_speed)
{
	const int attack_interval = 60;

	if (frames_ % attack_interval != 1 && frames_ % attack_interval != 31)
		return;	
	if (!main_->InsidePanel(-32))
		return;

	aparam_main_->shot_angle_ = main_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
	main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
	aparam_main_->shot_speed_ = shot_speed + rank_;
	ArmsManager::TargetShotSmall(aparam_main_);
}

/**
@brief 衝突処理関数
@return なし
@note
 蓄積ダメージを更新する。
 ダメージに応じてスコアを増加させる。
**/
void Target2Colti::Collision(void)
{
	double damage = 0;				// １フレームあたりのダメージ
	const int extension = 0;		// draw_window 拡張
	const int interval = 50;		// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	damage_ += damage;
}

/**
@brief 削除関数
@note
 ターゲット内部フレーム数，
 またはダメージ量によって削除処理をおこなう。
**/
void Target2Colti::Delete(void)
{
	const int max_damage = 200;			// 最大ダメージ
	const double add_alv = 0.1;			// 加算Alv値
	const double add_exarms = 2.0;		// 加算ExArms値
	const double add_rank = 0.1;		// 加算Rank値

	if (900 <= frames_) {
		main_->DeleteData(0, 0);
		delete_flag_ = true;
	} else if (max_damage <= damage_) {
		main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
		main_->DeleteData(add_alv, add_rank);
		DesignManager::AddExArms(add_exarms);
		SoundManager::Play(soundfile_delete_, DX_PLAYTYPE_BACK);
		delete_flag_ = true;
	}
}


void Target2Colti::Draw(void)
{
	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 14;

	main_->Draw(imgfile_main_, imgdiv_main_, 0);
}

void Target2Colti::Move(void)
{
	main_->MoveB(move_angle_, move_speed_);
}

