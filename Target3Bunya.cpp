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
#include "Target3Bunya.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target3Bunya::Target3Bunya(double start_posx, double move_quadratic_a, double move_quadratic_vx, double move_quadratic_vy, double move_speed, int lv)
{
	double start_posy = QuadraticFunction(start_posx, move_quadratic_a, move_quadratic_vx, move_quadratic_vy);

	// 変数 初期化
	action_ = 0;
	count_frames_ = 0;
	health_ = 100;
	lv_ = lv;
	delete_flag_ = false;
	move_speed_ = move_speed;
	quadratic_a_ = move_quadratic_a;
	quadratic_vx_ = move_quadratic_vx;
	quadratic_vy_ = move_quadratic_vy;
	main_ = new Target(start_posx, start_posy, 15);
	cube_[0] = new Target(start_posx - 48, start_posy - 16, 15);
	cube_[1] = new Target(start_posx + 48, start_posy - 16, 15);
	aparam_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgdiv_main_shadow_ = 0;
	imgfile_arms_cube_ = ImgManager::LoadImg("data/10_img_arms/ArmsBlue20.png");
	imgfile_arms_main_ = ImgManager::LoadImg("data/img_target/Arms1Red.png");
	imgfile_death_ = ImgManager::LoadImg(IMG_TARGET_DEATH120_NUMX, IMG_TARGET_DEATH120_NUMY, IMG_TARGET_DEATH120_SIZEX, IMG_TARGET_DEATH120_SIZEY, "data/img_effect/TargetDeath120.png");
	imgfile_cube_ = ImgManager::LoadImg(IMG_TARGET_CUBE140_NUMX, IMG_TARGET_CUBE140_NUMY, IMG_TARGET_CUBE140_SIZEX, IMG_TARGET_CUBE140_SIZEY, "data/img_target/CubeOrange140.png");
	imgfile_cube_lock_ = ImgManager::LoadImg("data/img_target/LockCube.png");
	imgfile_main_ = ImgManager::LoadImg(4, 2, 25, 28, "data/img_target/MainBunya.png");
	imgfile_main_lock_ = ImgManager::LoadImg("data/img_target/LockBunya.png");
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
	aparam_->img_id_ = imgfile_arms_main_;
	aparam_->img_rotate_ = false;
	aparam_->shot_pow_ = 1;
	aparam_->shot_range_ = 2.0;
}


Target3Bunya::~Target3Bunya() {
	delete main_;
	delete cube_[0];
	delete cube_[1];
	delete aparam_;
}


void Target3Bunya::Run(void)
{

	if (delete_flag_)
		return;

	// *****************
	//  共通アクション
	// *****************
	Collision();
	Draw();
	if (500 < count_frames_) {
		action_ = 100;
	} else if (health_ < 0) {
		action_ = 101;
	}

	// *****************
	//  アクション分岐
	// *****************
	switch (action_) {
	case 0:
		Move1();
		if (main_->InsidePanel(0)) {
			action_ = 1;
			count_frames_ = 0;
		}
		break;
	case 1:
		Move1();
		if (count_frames_ == 50) {
			action_ = 2;
			count_frames_ = 0;
		}
		break;
	case 2:
		Move1();
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


void Target3Bunya::Attack1Hard(void)
{
	int rank_num;			// ランク依存の弾数
	double rank_speed;		// ランク依存の攻撃速度


	if (lv_ != LV_HARD)
		return;

	if (count_frames_ % 40 != 0)
		return;

	// 弾数の更新
	DesignManager::GetRank(&rank_num);
	rank_num = 4 + rank_num / 3;

	// 攻撃速度更新
	DesignManager::GetRank(&rank_speed);
	rank_speed = 1 + rank_speed / 3;
	aparam_->shot_speed_ = 5.0 + rank_speed;

	// ************
	//  攻撃処理
	// ************
	if (cube_[0]->InsidePanel(-32)) {
		cube_[0]->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = cube_[0]->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
		for (int num = 0; num < rank_num; num++) {
			aparam_->shot_wait_ = num * 3;
			ArmsManager::TargetShotSmall(aparam_);
		}
	}
	if (cube_[1]->InsidePanel(-32)) {
		cube_[1]->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = cube_[1]->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
		for (int num = 0; num < rank_num; num++) {
			aparam_->shot_wait_ = num * 3;
			ArmsManager::TargetShotSmall(aparam_);
		}
	}
}


void Target3Bunya::AttackNormal(void)
{

}


void Target3Bunya::Collision(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// 処理する領域の拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	for (int i = 0; i < 2; i++) {
		damage += cube_[i]->Collision(extension);
		cube_[i]->CollisionImg(imgfile_cube_lock_, 0, interval);
		cube_[i]->CollisionSound(soundfile_lock_, interval);
	}
	DesignManager::AddScore(damage);
	health_ -= damage;
}


void Target3Bunya::Delete(double scale, bool effect, bool sound)
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


void Target3Bunya::Draw(void)
{
	const int divmax_cube = IMG_TARGET_CUBE140_NUMX * IMG_TARGET_CUBE140_NUMY;
	const int divmax_main = 8;

	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % divmax_main;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cube_ = ++imgdiv_cube_ % divmax_cube;

	main_->Draw(imgfile_main_,  imgdiv_main_, 1.4, 0);
	cube_[0]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
	cube_[1]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
}


void Target3Bunya::Move1(void)
{
	double x, y;

	main_->GetPos(&x, NULL);
	x += move_speed_;
	y = QuadraticFunction(x, quadratic_a_, quadratic_vx_, quadratic_vy_);
	main_->SetPos(&x, &y);

	main_->GetPos(&x, &y);
	x = x - 48;
	y = y - 16;
	cube_[0]->SetPos(&x, &y);
	main_->GetPos(&x, &y);
	x = x + 48;
	y = y - 16;
	cube_[1]->SetPos(&x, &y);
}

