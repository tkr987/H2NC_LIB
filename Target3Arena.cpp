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
#include "Target3Arena.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target3Arena::Target3Arena(double start_posx, double start_posy, double move_speed, double move_time, int lv)
{
	// 変数 初期化
	action_ = 0;
	count_frames_ = 0;
	health_ = 100;
	lv_ = lv;
	delete_flag_ = false;
	move_speed_ = move_speed;
	speed_down_value_ = -move_speed / move_time;
	speed_up_value_ = move_speed / move_time;
	main_ = new Target(start_posx, start_posy, 15);
	cube_[0] = new Target(start_posx + 64, start_posy, 15);
	cube_[1] = new Target(start_posx - 64, start_posy, 15);
	cube_[2] = new Target(start_posx + 40, start_posy - 60, 15);
	cube_[3] = new Target(start_posx - 40, start_posy - 60, 15);
	aparam_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgdiv_main_shadow_ = 0;
	imgfile_arms_cube_ = ImgManager::LoadImg("data/10_img_arms/ArmsBlue20.png");
	imgfile_arms_main_ = ImgManager::LoadImg("data/img_target/Arms1Red.png");
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH140;
	imgfile_cube_ = ImgManager::LoadImg(IMG_TARGET_CUBE140_NUMX, IMG_TARGET_CUBE140_NUMY, IMG_TARGET_CUBE140_SIZEX, IMG_TARGET_CUBE140_SIZEY, "data/img_target/CubeOrange140.png");
	imgfile_cube_lock_ = ImgManager::LoadImg("data/img_target/LockCube.png");
	imgfile_main_ = ImgManager::LoadImg(4, 1, 32, 32, "data/img_target/Target3Arena.png");
	imgfile_main_lock_ = ImgManager::LoadImg("data/img_target/LockArena.png");
	// サウンドファイル
	soundfile_bomb_ = SoundManager::Load("data/sound/target_bomb2.wav");
	soundfile_lock_ = SoundManager::Load("data/sound/target_lock.wav");
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
	aparam_->img_id_ = imgfile_arms_main_;
	aparam_->img_rotate_ = false;
	aparam_->shot_pow_ = 1;
	aparam_->shot_range_ = 2.0;
}


Target3Arena::~Target3Arena() {
	delete main_;
	delete cube_[0];
	delete cube_[1];
	delete cube_[2];
	delete cube_[3];
	delete aparam_;
	delete eparam_death_;
}


void Target3Arena::Run(void)
{
	if (delete_flag_)
		return;

	// *****************
	//  共通アクション
	// *****************
	Collision();
	Draw();
	if (health_ < 0)
		action_ = 101;

	// *****************
	//  アクション分岐
	// *****************
	switch (action_) {
	case 0:
		Move1();
		if (move_speed_ == 0) {
			action_ = 1;
			count_frames_ = 0;
		}
		break;
	case 1:
		if (count_frames_ == 50) {
			action_ = 2;
			count_frames_ = 0;
		}
		break;
	case 2:
		Attack1Hard();
		Attack1Hard();
		if (count_frames_ == 300) {
			action_ = 3;
			count_frames_ = 0;
		}
		break;
	case 3:
		if (count_frames_ == 50) {
			action_ = 4;
			count_frames_ = 0;
		}
		break;
	case 4:
		Attack2Hard();
		if (count_frames_ == 300) {
			action_ = 5;
			count_frames_ = 0;
		}
		break;
	case 5:
		Move2();
		if (!main_->InsidePanel(256))
			action_ = 100;
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


void Target3Arena::Attack1Hard(void)
{
	int rank_freq;			// ランク依存の攻撃頻度
	double rank_speed;		// ランク依存の攻撃速度
	// 攻撃角度
	double angle = main_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);


	if (lv_ != LV_HARD)
		return;

	// 攻撃頻度更新
	DesignManager::GetRank(&rank_freq);
	rank_freq = 5 - rank_freq / 3;
	if (rand() % rank_freq != 0)
		return;

	// 攻撃速度更新
	DesignManager::GetRank(&rank_speed);
	rank_speed = 1 + rank_speed / 3;
	aparam_->shot_speed_ = 4.0 + rank_speed;

	// 攻撃処理
	if (main_->InsidePanel(-32)) {
		main_->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = angle + CalcRAD(-70 + rand() % 140);
		ArmsManager::TargetShotSmall(aparam_);
	}
}

void Target3Arena::Attack2Hard(void)
{
	int rank_num;			// ランク依存の弾数
	double rank_speed;		// ランク依存の攻撃速度


	if (lv_ != LV_HARD)
		return;

	if (count_frames_ % 40 != 0)
		return;

	// 弾数の更新
	DesignManager::GetRank(&rank_num);
	rank_num = 5 + rank_num / 3;

	// 攻撃速度更新
	DesignManager::GetRank(&rank_speed);
	rank_speed = 1 + rank_speed / 3;
	aparam_->shot_speed_ = 1.0 + rank_speed;

	// ************
	//  攻撃処理
	// ************
	if (!cube_[2]->InsidePanel(-32))
		return;

	cube_[0]->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
	for (aparam_->shot_angle_ = CalcRAD(-150); aparam_->shot_angle_ <= CalcRAD(150); aparam_->shot_angle_ += CalcRAD(10)) {
		for (int num = 0; num < rank_num; num++) {
			aparam_->shot_wait_ = num * 3;
			ArmsManager::TargetShotSmall(aparam_);
		}
	}
	cube_[2]->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
	for (aparam_->shot_angle_ = CalcRAD(-150); aparam_->shot_angle_ <= CalcRAD(150); aparam_->shot_angle_ += CalcRAD(10)) {
		for (int num = 0; num < rank_num; num++) {
			aparam_->shot_wait_ = num * 3;
			ArmsManager::TargetShotSmall(aparam_);
		}
	}
	cube_[1]->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
	for (aparam_->shot_angle_ = CalcRAD(30); aparam_->shot_angle_ <= CalcRAD(330); aparam_->shot_angle_ += CalcRAD(10)) {
		for (int num = 0; num < rank_num; num++) {
			aparam_->shot_wait_ = num * 3;
			ArmsManager::TargetShotSmall(aparam_);
		}
	}

	cube_[3]->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
	for (aparam_->shot_angle_ = CalcRAD(30); aparam_->shot_angle_ <= CalcRAD(330); aparam_->shot_angle_ += CalcRAD(10)) {
		for (int num = 0; num < rank_num; num++) {
			aparam_->shot_wait_ = num * 3;
			ArmsManager::TargetShotSmall(aparam_);
		}
	}
}


void Target3Arena::AttackNormal(void)
{

}


void Target3Arena::Collision(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	for (int i = 0; i < 4; i++) {
		damage += cube_[i]->Collision(extension);
		cube_[i]->CollisionImg(imgfile_cube_lock_, 0, interval);
		cube_[i]->CollisionSound(soundfile_lock_, interval);
	}
	DesignManager::AddScore(damage);
	health_ -= damage;
}


void Target3Arena::Delete(double scale, bool effect, bool sound)
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
		SoundManager::Play(soundfile_bomb_, DX_PLAYTYPE_BACK);

	// 削除処理
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
	for (int i = 0; i < 4; i++)
		cube_[i]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Target3Arena::Draw(void)
{
	const int divmax_cube = IMG_TARGET_CUBE140_NUMX * IMG_TARGET_CUBE140_NUMY;
	const int divmax_main = 4;

	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % divmax_main;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cube_ = ++imgdiv_cube_ % divmax_cube;

	main_->Draw(imgfile_main_,  imgdiv_main_, 1.4, 0);
	cube_[0]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
	cube_[1]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
	cube_[2]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
	cube_[3]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
}


void Target3Arena::Move1(void)
{
	const double move_angle = CalcRAD(90);

	if (move_speed_ + speed_down_value_ < 0) {
		move_speed_ = 0;
	} else {
		move_speed_ += speed_down_value_;
	}

	main_->MoveB(move_angle, move_speed_);
	for (int i = 0; i < 4; i++)
		cube_[i]->MoveB(move_angle, move_speed_);
}

void Target3Arena::Move2(void)
{
	const double move_angle = CalcRAD(-90);
	
	move_speed_ += speed_up_value_;

	main_->MoveB(move_angle, move_speed_);
	for (int i = 0; i < 4; i++)
		cube_[i]->MoveB(move_angle, move_speed_);
}
