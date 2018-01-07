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
#include "Target3Corona.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target3Corona::Target3Corona(double start_posx, double start_posy, bool reverse, int lv)
{
	// 変数 初期化
	action_ = 0;
	angle_cube_[0] =   0 + 10;
	angle_cube_[1] =  90 + 10;
	angle_cube_[2] = 180 + 10;
	angle_cube_[3] = 270 + 10;
	angle_reverse_ = reverse;
	count_ = 0;
	damage_ = 0;
	lv_ = lv;
	delete_flag_ = false;
//	start_posx_ =
//	start_posy_ =
//	end_posx_ =
//	end_posy_ =
	main_ = new Target(start_posx, start_posy, 15);
	cube_[0] = new Target(start_posx + cos(CalcRAD(angle_cube_[0])) * 64, start_posy + sin(CalcRAD(angle_cube_[0])) * 64, 15);
	cube_[1] = new Target(start_posx + cos(CalcRAD(angle_cube_[1])) * 64, start_posy + sin(CalcRAD(angle_cube_[1])) * 64, 15);
	cube_[2] = new Target(start_posx + cos(CalcRAD(angle_cube_[2])) * 64, start_posy + sin(CalcRAD(angle_cube_[2])) * 64, 15);
	cube_[3] = new Target(start_posx + cos(CalcRAD(angle_cube_[3])) * 64, start_posy + sin(CalcRAD(angle_cube_[3])) * 64, 15);
	aparam_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgdiv_main_shadow_ = 0;
	imgfile_arms_cube_ = ImgManager::LoadImg("data/10_img_arms/ArmsBlue20.png");
	imgfile_arms_main_ = ImgManager::LoadImg("data/img_target/Arms1Red.png");
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH140;
	imgfile_cube_ = ImgManager::LoadImg(IMG_TARGET_CUBE60_NUMX, IMG_TARGET_CUBE60_NUMY, IMG_TARGET_CUBE60_SIZEX, IMG_TARGET_CUBE60_SIZEY, "data/img_target/CubeBlue60.png");
	imgfile_cube_lock_ = ImgManager::LoadImg("data/img_target/LockCube.png");
	imgfile_main_ = ImgManager::LoadImg(5, 2, 54, 54, "data/img_target/MainCorona.png");
	imgfile_main_lock_ = ImgManager::LoadImg("data/img_target/LockPandora.png");
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
	aparam_->img_id_ = imgfile_arms_cube_;
	aparam_->img_rotate_ = false;
	aparam_->shot_pow_ = 1;
	aparam_->shot_range_ = 2.0;
}


Target3Corona::~Target3Corona() {
	delete main_;
	delete cube_[0];
	delete cube_[1];
	delete cube_[2];
	delete cube_[3];
	delete aparam_;
}


void Target3Corona::Run(void)
{

	if (delete_flag_)
		return;

	Move();
	Draw();
	AttackHard();
	AttackNormal();
	Collision();
	Delete();
	count_++;
}


void Target3Corona::AttackHard(void)
{
	int rank_freq;			// ランク依存の攻撃頻度
	double rank_speed;		// ランク依存の攻撃速度


	if (lv_ != LV_HARD)
		return;

	// 攻撃頻度更新
	DesignManager::GetRank(&rank_freq);
	rank_freq /= 100;

	// 攻撃頻度判定
	if (count_ % (40 - rank_freq * 6) != 0)
		return;

	// 攻撃速度更新
	DesignManager::GetRank(&rank_speed);
	aparam_->shot_speed_ = 4.0 + rank_speed / 100.0;

	// 攻撃処理
	for (int i = 0; i < 4; i++) {
		if (cube_[i]->InsidePanel(-64)) {
			cube_[i]->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
			aparam_->shot_angle_ = CalcRAD(angle_cube_[i] - 9);
			ArmsManager::TargetShotSmall(aparam_);
			aparam_->shot_angle_ = CalcRAD(angle_cube_[i] - 6);
			ArmsManager::TargetShotSmall(aparam_);
			aparam_->shot_angle_ = CalcRAD(angle_cube_[i] - 3);
			ArmsManager::TargetShotSmall(aparam_);
			aparam_->shot_angle_ = CalcRAD(angle_cube_[i]);
			ArmsManager::TargetShotSmall(aparam_);
			aparam_->shot_angle_ = CalcRAD(angle_cube_[i] + 3);
			ArmsManager::TargetShotSmall(aparam_);
			aparam_->shot_angle_ = CalcRAD(angle_cube_[i] + 6);
			ArmsManager::TargetShotSmall(aparam_);
			aparam_->shot_angle_ = CalcRAD(angle_cube_[i] + 9);
			ArmsManager::TargetShotSmall(aparam_);
		}
	}
}


void Target3Corona::AttackNormal(void)
{
	int rank_freq;			// ランク依存の攻撃頻度

	if (lv_ != LV_NORMAL)
		return;

	// 攻撃頻度更新
	DesignManager::GetRank(&rank_freq);
	rank_freq /= 100;
	if (count_ % (40 - rank_freq * 3) != 0)
		return;
}


void Target3Corona::Collision(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// draw_window 拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	for (int i = 0; i < 4; i++) {
		damage += cube_[i]->Collision(extension);
		cube_[i]->CollisionImg(imgfile_main_lock_, 0, interval);
		cube_[i]->CollisionSound(soundfile_lock_, interval);
	}
	DesignManager::AddScore(damage);
	damage_ += damage;
}


void Target3Corona::Delete(void)
{
	const int max_damage = 100;		// 最大ダメージ
	const double add_alv = 0.1;		// 加算ALV
	const double add_exarms = 2.0;	// 加算ExArms

	if (10000 <= count_) {
		delete_flag_ = true;
		main_->DeleteData(0);
		for (int i = 0; i < 4; i++)
			cube_[i]->DeleteData(0);
	} else if (max_damage <= damage_) {
		main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
		main_->DeleteData(add_alv);
		for (int i = 0; i < 4; i++) {
			cube_[i]->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
			cube_[i]->DeleteData(add_alv);
		}
		SoundManager::Play(soundfile_bomb_, DX_PLAYTYPE_BACK);
		DesignManager::AddExArms(add_exarms);
		delete_flag_ = true;
	}
}


void Target3Corona::Draw(void)
{
	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 10;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cube_ = ++imgdiv_cube_ % 5;

	main_->Draw(imgfile_main_,  imgdiv_main_, 0);
	cube_[0]->Draw(imgfile_cube_, imgdiv_cube_, 0);
	cube_[1]->Draw(imgfile_cube_, imgdiv_cube_, 0);
	cube_[2]->Draw(imgfile_cube_, imgdiv_cube_, 0);
	cube_[3]->Draw(imgfile_cube_, imgdiv_cube_, 0);
}


void Target3Corona::Move(void)
{
	double x, y;
	double move_angle;
	double move_speed = 0.5;

	if (!angle_reverse_) {
		move_angle = 1.0;
	} else {
		move_angle = -1.0;
	}

	main_->MoveA(NULL, &move_speed);
	for (int i = 0; i < 4; i++) {
		main_->GetPos(&x, &y);
		angle_cube_[i] += move_angle;
		x += cos(CalcRAD(angle_cube_[i])) * 64;
		y += sin(CalcRAD(angle_cube_[i])) * 64;
		cube_[i]->SetPos(&x, &y);
	}
}


