#include <math.h>
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
#include "Target3Asfar.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target3Asfar::Target3Asfar(double start_posx, double start_posy, double move_angle, double move_speed, int lv)
{
	// 変数 初期化
	action_ = 0;
	count_ = 0;
	damage_ = 0;
	lv_ = lv;
	delete_flag_ = false;
	cube_angle_ = 0;
	move_angle_ = move_angle;
	move_speed_ = move_speed;
	main_ = new Target(start_posx, start_posy, 15);
	cube_ = new Target(start_posx, start_posy, 15);
	aparam_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_ = ImgManager::LoadImg("data/img_target/Arms1Red.png");
	imgfile_cube_ = ImgManager::LoadImg(IMG_TARGET_CUBE140_NUMX, IMG_TARGET_CUBE140_NUMY, IMG_TARGET_CUBE140_SIZEX, IMG_TARGET_CUBE140_SIZEY, "data/img_target/CubeOrange140.png");
	imgfile_cube_lock_ = ImgManager::LoadImg("data/img_target/LockCube.png");
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH120;
	imgfile_main_ = ImgManager::LoadImg(4, 2, 45, 45, "data/img_target/MainAsfar.png");
	imgfile_main_lock_ = ImgManager::LoadImg("data/img_target/LockAsfar.png");
	// サウンドファイル
	soundfile_death_ = SoundManager::Load("data/sound/target_bomb2.wav");
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
	aparam_->img_angle_ = 0;
	aparam_->img_id_ = imgfile_arms_;
	aparam_->img_rotate_ = 0;
	aparam_->shot_pow_ = 1;
	aparam_->shot_range_ = 2.0;
}


Target3Asfar::~Target3Asfar() {
	delete cube_;
	delete main_;
	delete aparam_;
	delete eparam_death_;
}


void Target3Asfar::Run(void)
{
	if (delete_flag_)
		return;

	// メイン処理
	AttackHard();
	AttackNormal();
	Move();
	Draw();
	Collision();
	Delete();
	count_++;
}


void Target3Asfar::AttackHard(void)
{
	int rank;
	double atan2_cube;		// 自機とcubeの偏角
	double atan2_main;		// 自機とmainの偏角

	if (lv_ != LV_HARD)
		return;

	DesignManager::GetRank(&rank);
	aparam_->shot_speed_ = 5.0 + (double)rank / 100.0;
	rank /= 100;

	// 偏角の更新
	if (12 < count_ % (50 - rank * 6)) {
		atan2_cube = cube_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
		atan2_main = main_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
		if (atan2_main - atan2_cube < CalcRAD(3)) {
			cube_angle_ += CalcRAD(3);
		}
		else if (CalcRAD(3) < atan2_main - atan2_cube) {
			cube_angle_ += CalcRAD(-3);
		}
	}

	// 攻撃処理
	if (count_ % (50 - rank * 6) == 0) {
		aparam_->shot_angle_ = cube_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
		cube_->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
		if (cube_->InsidePanel(-64))
			ArmsManager::TargetShotSmall(aparam_);
	} else if (count_ % (50 - rank * 6) == 4) {
		cube_->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
		if (cube_->InsidePanel(-64))
			ArmsManager::TargetShotSmall(aparam_);
	} else if (count_ % (50 - rank * 6) == 8) {
		cube_->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
		if (cube_->InsidePanel(-64))
			ArmsManager::TargetShotSmall(aparam_);
	} else if (count_ % (50 - rank * 6) == 12) {
		cube_->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
		if (cube_->InsidePanel(-64))
			ArmsManager::TargetShotSmall(aparam_);
	}
}


void Target3Asfar::AttackNormal(void)
{
	//int rank;

	if (lv_ != LV_NORMAL)
		return;


}


void Target3Asfar::Collision(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// draw_window 拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += cube_->Collision(extension);
	cube_->CollisionImg(imgfile_cube_lock_, 0, interval);
	cube_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	damage_ += damage;
}

void Target3Asfar::Delete(void)
{
	const double alv = 0.1;				// 加算ALV値
	const double rank = 0.1;			// 加算Rank値
	const int max_damage = 500;			// 最大ダメージ
	const double add_exarms = 2.0;		// 加算ExArms値

	if (2000 <= count_) {
		main_->DeleteData(0,0);
		cube_->DeleteData(0,0);
		delete_flag_ = true;
	} else if (max_damage <= damage_) {
		main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
		main_->DeleteData(alv, rank);
		cube_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
		cube_->DeleteData(alv, rank);
		DesignManager::AddExArms(add_exarms);
		SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);
		delete_flag_ = true;
	}
}

void Target3Asfar::Draw(void)
{
	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 8;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cube_ = ++imgdiv_cube_ % 5;

	main_->Draw(imgfile_main_, imgdiv_main_, 0);
	cube_->Draw(imgfile_cube_, imgdiv_cube_, 0.25, 0);
}

void Target3Asfar::Move(void)
{
	double x, y;

	main_->MoveB(CalcRAD(move_angle_), move_speed_);
	main_->GetPos(&x, &y);
	x += cos(cube_angle_) * 32;
	y += sin(cube_angle_) * 32;
	cube_->SetPos(&x, &y);
}

