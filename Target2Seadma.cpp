#include <float.h>
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
#include "Target2Seadma.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target2Seadma::Target2Seadma(double start_posx, double end_posy, int lv)
{
	const double start_posy = -200;
	const double move_speed = 5.0;

	main_ = new Target(start_posx, start_posy, 15);
	cube1_ = new Target(start_posx + 32, start_posy + 32, 15);
	cube2_ = new Target(start_posx - 32, start_posy + 32, 15);
	cube3_ = new Target(start_posx + 64, start_posy, 15);
	cube4_ = new Target(start_posx - 64, start_posy, 15);
	aparam_cube_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// 画像ファイル
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_cube_ = ImgManager::LoadImg("data/img_target/Arms1Red.png");
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH120;
	imgfile_cube_ = ImgManager::LoadImg(5, 1, IMG_SIZEX_TARGET_CUBE2, IMG_SIZEY_TARGET_CUBE2, "data/img_target/Cube2B.png");
	imgfile_cube_lock_ = ImgManager::LoadImg("data/img_target/LockCube.png");
	imgfile_main_ = ImgManager::LoadImg(4, 1, 48, 48, "data/img_target/MainSeadma.png");
	imgfile_main_lock_ = ImgManager::LoadImg("data/img_target/LockSeadma.png");
	// サウンドファイル
	soundfile_death_ = SoundManager::Load("data/sound/target_bomb2.wav");
	soundfile_lock_ = SoundManager::Load("data/sound/target_lock.wav");
	// 変数 初期化
	action_ = 0;
	damage_ = 0;
	frames_ = 0;
	lv_ = lv;
	delete_flag_ = false;
	start_posx_ = start_posx;
	end_posy_ = end_posy;
	move_speed_ = move_speed;
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
	aparam_cube_->img_angle_ = 0;
	aparam_cube_->img_id_ = imgfile_arms_cube_;
	aparam_cube_->img_rotate_ = 0;
	aparam_cube_->shot_pow_ = 1;
	aparam_cube_->shot_range_ = 2.0;
}

Target2Seadma::~Target2Seadma() {
	delete aparam_cube_;
	delete cube1_;
	delete cube2_;
	delete cube3_;
	delete cube4_;
	delete main_;
}

void Target2Seadma::Run(void) 
{
	const int arms_interval = 90;
	
	if (delete_flag_)
		return;

	frames_++;
	switch(action_) {
	case 0:
		Move1();
		if (move_speed_ < 0.5) {
			action_ = 1;
			frames_ = 0;
			move_speed_ = 0.5;
		}
		break;
	case 1:
		if (lv_ == LV_HARD) {
			Attack(arms_interval);
			Attack(arms_interval);
			Attack(arms_interval);
			Attack(arms_interval);
		} else {

		}
		Move2();
		break;
	}

	Draw();
	Collision();
	Delete();
}



void Target2Seadma::Attack(int interval)
{
	double rank;
	double shot_diff_angle;
	const double shot_speed = 4.0;

	if (frames_ % interval != 0)
		return;

	if (lv_ == LV_HARD) {
		// 共通パラメータ
		DesignManager::GetRank(&rank);
		aparam_cube_->shot_speed_ = shot_speed + rank / 150.0;
		// cube1
		if (cube1_->InsidePanel(-32)) {
			shot_diff_angle = cube1_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
			cube1_->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			for (double angle = -8.0; angle <= 8.0; angle += 4.0) {
				aparam_cube_->shot_angle_ = shot_diff_angle + CalcRAD(angle);
				ArmsManager::TargetShotSmall(aparam_cube_);
			}
		}
		// cube2
		if (cube2_->InsidePanel(-32)) {
			shot_diff_angle = cube2_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
			cube2_->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			for (double angle = -8.0; angle <= 8.0; angle += 4.0) {
				aparam_cube_->shot_angle_ = shot_diff_angle + CalcRAD(angle);
				ArmsManager::TargetShotSmall(aparam_cube_);
			}
		}
		// cube3
		if (cube3_->InsidePanel(-32)) {
			shot_diff_angle = cube3_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
			cube3_->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			for (double angle = -8.0; angle <= 8.0; angle += 4.0) {
				aparam_cube_->shot_angle_ = shot_diff_angle + CalcRAD(angle);
				ArmsManager::TargetShotSmall(aparam_cube_);
			}
		}
		// cube4
		if (cube4_->InsidePanel(-32)) {
			shot_diff_angle = cube4_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
			cube4_->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
			for (double angle = -8.0; angle <= 8.0; angle += 4.0) {
				aparam_cube_->shot_angle_ = shot_diff_angle + CalcRAD(angle);
				ArmsManager::TargetShotSmall(aparam_cube_);
			}
		}
	} else {

	}
}

/*!
@brief 衝突処理関数
@return なし
@note
 蓄積ダメージを更新する。
 ダメージに応じてスコアを増加させる。
*/
void Target2Seadma::Collision(void)
{
	double damage = 0;			// １フレームあたりのダメージ
	const int extension = 0;	// draw_window 拡張
	const int interval = 50;	// インターバル時間

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	damage += cube1_->Collision(extension);
	cube1_->CollisionImg(imgfile_cube_lock_, 0, interval);
	cube1_->CollisionSound(soundfile_lock_, interval);
	damage += cube2_->Collision(extension);
	cube2_->CollisionImg(imgfile_cube_lock_, 0, interval);
	cube2_->CollisionSound(soundfile_lock_, interval);
	damage += cube3_->Collision(extension);
	cube3_->CollisionImg(imgfile_cube_lock_, 0, interval);
	cube3_->CollisionSound(soundfile_lock_, interval);
	damage += cube4_->Collision(extension);
	cube4_->CollisionImg(imgfile_cube_lock_, 0, interval);
	cube4_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	damage_ += damage;
}

/*!
@brief 削除関数
@note
 ターゲット内部フレーム数，
 またはダメージ量によって削除処理をおこなう。
*/
void Target2Seadma::Delete(void)
{
	const int max_damage = 900;			// 最大ダメージ
	const double add_alv = 0.1;			// 加算ALV値
	const double add_rank = 0.1;		// 加算Rank値
	const double add_exarms = 2.0;		// 加算ExArms値

	if (lv_ != LV_HARD) {
		if (3000 <= frames_) {
			main_->DeleteData(0, 0);
			cube1_->DeleteData(0, 0);
			cube2_->DeleteData(0, 0);
			delete_flag_ = true;
		} else if (max_damage <= damage_) {
			main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
			main_->DeleteData(add_alv, add_rank);
			cube1_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
			cube1_->DeleteData(add_alv, add_rank);
			cube2_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
			cube2_->DeleteData(add_alv, add_rank);
			ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_SMALL);
			DesignManager::AddExArms(add_exarms);
			ImgManager::SwingY(20, 2);
			SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);
			delete_flag_ = true;
		}
	} else {
		if (3000 <= frames_) {
			main_->DeleteData(0, 0);
			cube1_->DeleteData(0, 0);
			cube2_->DeleteData(0, 0);
			cube3_->DeleteData(0, 0);
			cube4_->DeleteData(0, 0);			
			delete_flag_ = true;
		} else if (max_damage <= damage_) {
			main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
			main_->DeleteData(add_alv, add_rank);
			cube1_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
			cube1_->DeleteData(add_alv, add_rank);
			cube2_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
			cube2_->DeleteData(add_alv, add_rank);
			cube3_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
			cube3_->DeleteData(add_alv, add_rank);
			cube4_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
			cube4_->DeleteData(add_alv, add_rank);
			ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_SMALL);
			DesignManager::AddExArms(add_exarms);
			ImgManager::SwingY(20, 2);
			SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);
			delete_flag_ = true;
		}
	}
}

void Target2Seadma::Draw(void)
{

	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % 4;
	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cube_ = ++imgdiv_cube_ % 5;

	main_->Draw(imgfile_main_,  imgdiv_main_, 0);
	cube1_->Draw(imgfile_cube_, imgdiv_cube_, 0);
	cube2_->Draw(imgfile_cube_, imgdiv_cube_, 0);

	// LV_HARD 限定
	if (lv_ != LV_HARD)
		return;

	cube3_->Draw(imgfile_cube_, imgdiv_cube_, 0);
	cube4_->Draw(imgfile_cube_, imgdiv_cube_, 0);
}


void Target2Seadma::Move1(void)
{
	double y;

	main_->GetPos(NULL, &y);
	if (end_posy_ < y)
		move_speed_ -= 0.2;
	main_->MoveA(NULL, &move_speed_);
	cube1_->MoveA(NULL, &move_speed_);
	cube2_->MoveA(NULL, &move_speed_);
	cube3_->MoveA(NULL, &move_speed_);
	cube4_->MoveA(NULL, &move_speed_);
}

void Target2Seadma::Move2(void)
{
	main_->MoveA(NULL, &move_speed_);
	cube1_->MoveA(NULL, &move_speed_);
	cube2_->MoveA(NULL, &move_speed_);
	cube3_->MoveA(NULL, &move_speed_);
	cube4_->MoveA(NULL, &move_speed_);
}
