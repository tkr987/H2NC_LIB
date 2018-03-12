#include "DxLib.h"
#include "ArmsManager.h"
#include "DesignManager.h"
#include "EffectManager.h"
#include "FpsManager.h"
#include "ImgManager.h"
#include "KeyManager.h"
#include "PosManager.h"
#include "SoundManager.h"
#include "DefineNH.h"
#include "DebugPrint.h"
#include "User1.h"
#define __DEBUG__

using namespace NH2;

User1::User1(void)
{
	aparam_ = new ArmsParam1;
	aparam_ex_ = new ArmsParam1;
	eparam_death_ = new EffectParam1;
	iparam_exeffect1_ = new ImgParam4b;
	iparam_exeffect2_ = new ImgParam4b;
	iparam_exeffect3a_ = new ImgParam4;
	iparam_exeffect3b_ = new ImgParam4;
	iparam_main_ = new ImgParam4;
	iparam_main_invincible_ = new ImgParam4b;
	iparam_sub_ = new ImgParam4;
	pparam_ = new PosParam1;
	// 画像ファイル
	imgfile_arms1a = ImgManager::LoadImg("data/img_user1/arms1a.png");
	imgfile_arms1b = ImgManager::LoadImg("data/img_user1/arms1b.png");
//	imgfile_death_ = ImgManager::LoadImg(4, 2, IMG_TARGET_DEATH2_SIZEX, IMG_TARGET_DEATH2_SIZEY, "data/img_user1/Death.png");
	imgfile_dot_ = IMG_LOAD_USER_DOT;
	imgfile_exarms_ = ImgManager::LoadImg("data/img_user1/exarmsv2.png");
	imgfile_effect_arms_ = ImgManager::LoadImg(4, 1, 64, 64, "data/img_effect/UserArms64.png");
	imgfile_effect_exarms_ = ImgManager::LoadImg(4, 1, 45, 45, "data/img_user1/effect_exarms.png");
	imgfile_exeffect1_ = ImgManager::LoadImg("data/img_user1/exeffect1.png");
	imgfile_exeffect2_ = ImgManager::LoadImg("data/img_user1/exeffect2.png");
	imgfile_exeffect3_ = ImgManager::LoadImg("data/img_user1/exeffect3.png");
	imgfile_sub_ = ImgManager::LoadImg(16, 1, 48, 48, "data/img_user1/sub.png");
	imgfile_user1a_ = ImgManager::LoadImg(5, 2, 152, 152, "data/img_user1/user1a.png");
	imgfile_user1b_ = ImgManager::LoadImg(5, 2, 152, 152, "data/img_user1/user1b.png");
	// サウンドファイル
	soundfile_arms_ = SoundManager::Load("data/sound/user_arms1v2.wav");
	soundfile_death_ = SoundManager::Load("data/sound/target_death2.wav");
	soundfile_exstart_ = SoundManager::Load("data/sound/user_exstart.wav");
}

User1::~User1(void)
{
	delete aparam_;
	delete aparam_ex_;
	delete iparam_exeffect1_;
	delete iparam_exeffect2_;
	delete iparam_exeffect3a_;
	delete iparam_exeffect3b_;
	delete iparam_main_;
	delete iparam_main_invincible_;
	delete iparam_sub_;
	delete pparam_;
}

void User1::Clear(void)
{
	// 変数初期化
	invincible_frames_ = 0;
	imgdiv_main_ = 5;
	imgdiv_sub_ = 0;
	sync_movecount_ = 0;
	// エフェクト設定
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::NUM::USER_EFFECT;
	eparam_death_->img_divmax_ = 8;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 2;
	// IMG MAIN 固定パラメータ
	iparam_main_->draw_angle_ = 0;
	iparam_main_->extend_rate_ = 0.4;
	iparam_main_->flag_trans_ = true;
	iparam_main_->flag_turn_ = false;
	iparam_main_->group_type_ = eOBJECT::NUM::USER;
	// IMG MAIN INVINCIBLE 固定パラメータ
	iparam_main_invincible_->blend_alpha_ = 255;
	iparam_main_invincible_->blend_mode_ = DX_BLENDMODE_INVSRC;
	iparam_main_invincible_->draw_angle_ = 0.0;
	iparam_main_invincible_->extend_rate_ = 0.4;
	iparam_main_invincible_->flag_trans_ = true;
	iparam_main_invincible_->flag_turn_ = false;
	iparam_main_invincible_->group_type_ = eOBJECT::NUM::USER;
	// IMG SUB 固定パラメータ
	iparam_sub_->draw_angle_ = 0;
	iparam_sub_->extend_rate_ = 0.5;
	iparam_sub_->flag_trans_ = true;
	iparam_sub_->flag_turn_ = false;
	iparam_sub_->group_type_ = eOBJECT::NUM::USER;
	// ARMS 固定パラメータ
	aparam_->hit_effect_ = true;
	aparam_->hit_effect_img_divmax_ = 4;
	aparam_->hit_effect_img_divmin_ = 0;
	aparam_->hit_effect_img_extend_rate_ = 0.5;
	aparam_->hit_effect_img_id_ = imgfile_effect_arms_;
	aparam_->hit_effect_img_interval_ = 1;
	aparam_->img_id_ = imgfile_arms1a;
	aparam_->img_rotate_ = 0;
	aparam_->shot_pow_ = 1;
	aparam_->shot_range_ = 8.0;
	aparam_->shot_speed_ = 16.0;
	// EX ARMS 固定パラメータ
	aparam_ex_->hit_effect_ = true;
	aparam_ex_->hit_effect_img_divmax_ = 4;
	aparam_ex_->hit_effect_img_divmin_ = 0;
	aparam_ex_->hit_effect_img_id_ = imgfile_effect_exarms_;
	aparam_ex_->hit_effect_img_interval_ = 1;
	aparam_ex_->img_id_ = imgfile_exarms_;
	aparam_ex_->img_rotate_ = 0;
	aparam_ex_->shot_pow_ = 7;
	aparam_ex_->shot_range_ = 12;
	aparam_ex_->shot_speed_ = 16.0;
	// EX EFFECT 1 固定パラメータ
	iparam_exeffect1_->blend_mode_ = DX_BLENDMODE_ALPHA;
	iparam_exeffect1_->draw_angle_ = 0;
	iparam_exeffect1_->flag_trans_ = true;
	iparam_exeffect1_->flag_turn_ = false;
	iparam_exeffect1_->group_type_ = eOBJECT::NUM::USER;
	// EX EFFECT 2 固定パラメータ
	iparam_exeffect2_->blend_alpha_ = 200;
	iparam_exeffect2_->blend_mode_ = DX_BLENDMODE_ALPHA;
	iparam_exeffect2_->draw_angle_ = 0;
	iparam_exeffect2_->flag_trans_ = true;
	iparam_exeffect2_->flag_turn_ = false;
	iparam_exeffect2_->group_type_ = eOBJECT::NUM::USER;
	// EX EFFECT 3A 固定パラメータ
	iparam_exeffect3a_->extend_rate_ = 1.0;
	iparam_exeffect3a_->flag_trans_ = true;
	iparam_exeffect3a_->flag_turn_ = false;
	iparam_exeffect3a_->group_type_ = eOBJECT::NUM::USER;
	// EX EFFECT 3B 固定パラメータ
	iparam_exeffect3b_->extend_rate_ = 1.0;
	iparam_exeffect3b_->flag_trans_ = true;
	iparam_exeffect3b_->flag_turn_ = false;
	iparam_exeffect3b_->group_type_ = eOBJECT::NUM::USER;
	// POS PARAM 初期パラメータ
	pparam_->SetRange(2.0);
//	pparam_->SetStartX(DRAW_PANEL_CENTER);
//	pparam_->SetStartY(DRAW_PANEL_MAX_Y - 64.0);
	pparam_->SetStartX(200);
	pparam_->SetStartY(450);
	PosManager::Generate(eOBJECT::NUM::USER, pparam_, POS_NAME_USER_MAIN);
	// その他 設定
	DesignManager::SetAttackLV(1.0);
	DesignManager::SetExArms(150);
	DesignManager::SetStar(2);
}

void User1::Run(void)
{
	//int alv;
	//double pos_x;
	//double pos_y;

	//if (DesignManager::GetStar() == 0)
	//	return;

	//// *************
	////  攻撃力更新
	//// *************
	//PosManager::GetPosX(pparam_, &pos_x);
	//PosManager::GetPosY(pparam_, &pos_y);
	//DesignManager::GetAttackLV(&alv);
	//pparam_->SetPow(1 + alv / 100);
	//if (invincible_frames_ < 250) {
	//	if (DesignManager::GetExTime() <= 0) {
	//		Attack1();
	//	} else {
	//		AttackEx1();
	//	}
	//	if (400 < alv) {
	//		if (DesignManager::GetExTime() <= 0) {
	//			Attack2();
	//		} else {
	//			AttackEx2();
	//		}
	//	}
	//	if (800 < alv){
	//		if (600 < DesignManager::GetExTime()) {
	//			Attack3();
	//		} else {
	//			AttackEx3();
	//		}
	//	}
	//}

	//// ***********
	////  移動処理
	//// ***********
	//if (invincible_frames_ < 250)
	//	Move();

	//// ***********
	////  衝突処理
	//// ***********
	//Collision();

	//// ***********
	////  描画処理
	//// ***********
	//if (invincible_frames_ < 250) {
	//	if (invincible_frames_ == 0) {
	//		Draw1();
	//	} else {
	//		DrawInvincible();
	//	}
	//	if (400 < alv)
	//		Draw2();
	//	if (800 < alv)
	//		Draw3();
	//}

	////ImgManager::Draw(imgdot, 0, iparam_main_);
	
}

void User1::Attack1(void)
{
	double pos_x;
	double pos_y;

	PosManager::GetPosX(pparam_, &pos_x);
	PosManager::GetPosY(pparam_, &pos_y);
	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
		aparam_->shot_angle_ = CalcRAD(258.0);
		aparam_->shot_x_ = pos_x - 36;
		aparam_->shot_y_ = pos_y + 20;
		aparam_->img_angle_ = CalcRAD(-12.0);
		ArmsManager::UserShot(aparam_);
		aparam_->shot_angle_ = CalcRAD(270.0);
		aparam_->shot_x_ = pos_x - 16;
		aparam_->shot_y_ = pos_y;
		aparam_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_);
		aparam_->shot_angle_ = CalcRAD(270.0);
		aparam_->shot_x_ = pos_x + 16;
		aparam_->shot_y_ = pos_y;
		aparam_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_);
		aparam_->shot_angle_ = CalcRAD(282.0);
		aparam_->shot_x_ = pos_x + 36;
		aparam_->shot_y_ = pos_y + 20;
		aparam_->img_angle_ = CalcRAD(12.0);
		ArmsManager::UserShot(aparam_);
	} else if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
		aparam_->shot_angle_ = CalcRAD(264.0);
		aparam_->shot_x_ = pos_x - 36;
		aparam_->shot_y_ = pos_y + 5;
		aparam_->img_angle_ = CalcRAD(-6.0);
		ArmsManager::UserShot(aparam_);
		aparam_->shot_angle_ = CalcRAD(270.0);
		aparam_->shot_x_ = pos_x - 16;
		aparam_->shot_y_ = pos_y;
		aparam_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_);
		aparam_->shot_angle_ = CalcRAD(270.0);
		aparam_->shot_x_ = pos_x + 16;
		aparam_->shot_y_ = pos_y;
		aparam_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_);
		aparam_->shot_angle_ = CalcRAD(276.0);
		aparam_->shot_x_ = pos_x + 36;
		aparam_->shot_y_ = pos_y + 5;
		aparam_->img_angle_ = CalcRAD(6.0);
		ArmsManager::UserShot(aparam_);
	}
}

void User1::Attack2(void)
{
	double pos_x;
	double pos_y;

	PosManager::GetPosX(pparam_, &pos_x);
	PosManager::GetPosY(pparam_, &pos_y);
	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
		aparam_->shot_angle_ = 250.0;
		aparam_->shot_x_ = pos_x - 62;
		aparam_->shot_y_ = pos_y + 20;
		aparam_->img_angle_ = -20.0;
		ArmsManager::UserShot(aparam_);
		aparam_->shot_angle_ = 290.0;
		aparam_->shot_x_ = pos_x + 62;
		aparam_->shot_y_ = pos_y + 20;
		aparam_->img_angle_ = 20.0;
		ArmsManager::UserShot(aparam_);
	} else if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
		aparam_->shot_angle_ = 260.0;
		aparam_->shot_x_ = pos_x - 62;
		aparam_->shot_y_ = pos_y + 20;
		aparam_->img_angle_ = -10.0;
		ArmsManager::UserShot(aparam_);
		aparam_->shot_angle_ = 280.0;
		aparam_->shot_x_ = pos_x + 62;
		aparam_->shot_y_ = pos_y + 20;
		aparam_->img_angle_ = 10.0;
		ArmsManager::UserShot(aparam_);
	}
}

void User1::Attack3(void)
{
	double pos_x;
	double pos_y;

	PosManager::GetPosX(pparam_, &pos_x);
	PosManager::GetPosY(pparam_, &pos_y);
	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS)) {
		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
		aparam_->shot_angle_ = 270.0;
		aparam_->shot_x_ = pos_x - 46;
		aparam_->shot_y_ = pos_y + 4;
		aparam_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_);
		aparam_->shot_angle_ = 270.0;
		aparam_->shot_x_ = pos_x + 46;
		aparam_->shot_y_ = pos_y + 4;
		aparam_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_);
	}
}

void User1::AttackEx1(void) 
{
	double pos_x;
	double pos_y;

	PosManager::GetPosX(pparam_, &pos_x);
	PosManager::GetPosY(pparam_, &pos_y);
	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
		aparam_ex_->shot_angle_ = CalcRAD(258.0);
		aparam_ex_->shot_x_ = pos_x - 36;
		aparam_ex_->shot_y_ = pos_y + 20;
		aparam_ex_->img_angle_ = CalcRAD(-12.0);
		ArmsManager::UserShot(aparam_ex_);
		aparam_ex_->shot_angle_ = CalcRAD(270.0);
		aparam_ex_->shot_x_ = pos_x - 16;
		aparam_ex_->shot_y_ = pos_y;
		aparam_ex_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_ex_);
		aparam_ex_->shot_angle_ = CalcRAD(270.0);
		aparam_ex_->shot_x_ = pos_x + 16;
		aparam_ex_->shot_y_ = pos_y;
		aparam_ex_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_ex_);
		aparam_ex_->shot_angle_ = CalcRAD(282.0);
		aparam_ex_->shot_x_ = pos_x + 36;
		aparam_ex_->shot_y_ = pos_y - 20;
		aparam_ex_->img_angle_ = CalcRAD(12.0);
		ArmsManager::UserShot(aparam_ex_);
	} else if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
		aparam_ex_->shot_angle_ = CalcRAD(264.0);
		aparam_ex_->shot_x_ = pos_x - 36;
		aparam_ex_->shot_y_ = pos_y + 5;
		aparam_ex_->img_angle_ = CalcRAD(-6.0);
		ArmsManager::UserShot(aparam_ex_);
		aparam_ex_->shot_angle_ = CalcRAD(270.0);
		aparam_ex_->shot_x_ = pos_x - 16;
		aparam_ex_->shot_y_ = pos_y;
		aparam_ex_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_ex_);
		aparam_ex_->shot_angle_ = CalcRAD(270.0);
		aparam_ex_->shot_x_ = pos_x + 16;
		aparam_ex_->shot_y_ = pos_y;
		aparam_ex_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_ex_);
		aparam_ex_->shot_angle_ = CalcRAD(276.0);
		aparam_ex_->shot_x_ = pos_x + 36;
		aparam_ex_->shot_y_ = pos_y - 5;
		aparam_ex_->img_angle_ = CalcRAD(6.0);
		ArmsManager::UserShot(aparam_ex_);
	}
}

void User1::AttackEx2(void)
{
	double pos_x;
	double pos_y;

	PosManager::GetPosX(pparam_, &pos_x);
	PosManager::GetPosY(pparam_, &pos_y);
	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
		aparam_ex_->shot_angle_ = 250.0;
		aparam_ex_->shot_x_ = pos_x - 62;
		aparam_ex_->shot_y_ = pos_y + 20;
		aparam_ex_->img_angle_ = -20.0;
		ArmsManager::UserShot(aparam_ex_);
		aparam_ex_->shot_angle_ = 290.0;
		aparam_ex_->shot_x_ = pos_x + 62;
		aparam_ex_->shot_y_ = pos_y + 20;
		aparam_ex_->img_angle_ = 20.0;
		ArmsManager::UserShot(aparam_ex_);
	} else if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
		aparam_ex_->shot_angle_ = 260.0;
		aparam_ex_->shot_x_ = pos_x - 62;
		aparam_ex_->shot_y_ = pos_y + 20;
		aparam_ex_->img_angle_ = -10.0;
		ArmsManager::UserShot(aparam_ex_);
		aparam_ex_->shot_angle_ = 280.0;
		aparam_ex_->shot_x_ = pos_x + 62;
		aparam_ex_->shot_y_ = pos_y + 20;
		aparam_ex_->img_angle_ = 10.0;
		ArmsManager::UserShot(aparam_ex_);
	}

}

void User1::AttackEx3(void)
{
	double pos_x;
	double pos_y;

	PosManager::GetPosX(pparam_, &pos_x);
	PosManager::GetPosY(pparam_, &pos_y);
	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS)) {
		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
		aparam_ex_->shot_angle_ = 270.0;
		aparam_ex_->shot_x_ = pos_x - 46;
		aparam_ex_->shot_y_ = pos_y + 4;
		aparam_ex_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_ex_);
		aparam_ex_->shot_angle_ = 270.0;
		aparam_ex_->shot_x_ = pos_x + 46;
		aparam_ex_->shot_y_ = pos_y + 4;
		aparam_ex_->img_angle_ = 0;
		ArmsManager::UserShot(aparam_ex_);
	}
}

void User1::Collision(void)
{
	static int hoge = 0;

	if (invincible_frames_ != 0)
		invincible_frames_--;

	if (invincible_frames_ == 0 && PosManager::GetHit(pparam_) != 0) {
		hoge = 1;
		DesignManager::AddClockRank(-4.0);
//		DesignManager::SetStar(DesignManager::GetStar()-1);
		PosManager::GetPosX(pparam_, &eparam_death_->x_);
		PosManager::GetPosY(pparam_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);	
		SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);
//		invincible_frames_ = 300;
	}
#ifdef __DEBUG__
	DebugPrint::SetData(615, 200, "user_hoge_: %d", hoge);
#endif

}

void User1::Draw1(void)
{
//	// EX-ARMS 発動 (EX-TIME 250f)
//	if (KeyManager::IsPressKey(eKEY::EXARMS) && 100 <= DesignManager::GetExArms()) {
//		SoundManager::Play(soundfile_exstart_, DX_PLAYTYPE_BACK);
//		DesignManager::AddExArms(-100);
//		iparam_exeffect1_->blend_alpha_ = 255;
//		iparam_exeffect1_->extend_rate_ = 0.1;
//		PosManager::GetPosX(pparam_, &iparam_exeffect1_->pos_cx_);
//		PosManager::GetPosY(pparam_, &iparam_exeffect1_->pos_cy_);
//		iparam_exeffect2_->extend_rate_ = 0.1;
//		iparam_exeffect3a_->draw_angle_ = 0.0;
//		iparam_exeffect3b_->draw_angle_ = 0.0;
//		DesignManager::AddExTime(250);
//		ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_SMALL);
//	}
//	if (0 < DesignManager::GetExTime()) {
//		// exarms1a エフェクト(素材がないのでImgManagerで実現)
//		if (15 < iparam_exeffect1_->blend_alpha_) {
//			ImgManager::Draw(imgfile_exeffect1_, 0, iparam_exeffect1_);
//			iparam_exeffect1_->blend_alpha_ -= 15;
//			iparam_exeffect1_->extend_rate_ += 0.2;
//		}
//		if (10 < DesignManager::GetExTime()) {
//			iparam_exeffect3a_->draw_angle_ += 0.06;
//			PosManager::GetPosX(pparam_, &iparam_exeffect3a_->pos_cx_);
//			PosManager::GetPosY(pparam_, &iparam_exeffect3a_->pos_cy_);
//			ImgManager::Draw(imgfile_exeffect3_, 0, iparam_exeffect3a_);
//			iparam_exeffect3b_->draw_angle_ -= 0.06;
//			PosManager::GetPosX(pparam_, &iparam_exeffect3b_->pos_cx_);
//			PosManager::GetPosY(pparam_, &iparam_exeffect3b_->pos_cy_);
//			ImgManager::Draw(imgfile_exeffect3_, 0, iparam_exeffect3b_);
//		}
//		// exarms1b エフェクト(素材がないのでImgManagerで実現)
//		if (iparam_exeffect2_->extend_rate_ < 1.0)
//			iparam_exeffect2_->extend_rate_ += 0.1;
//		PosManager::GetPosX(pparam_, &iparam_exeffect2_->pos_cx_);
//		PosManager::GetPosY(pparam_, &iparam_exeffect2_->pos_cy_);
//		ImgManager::Draw(imgfile_exeffect2_, 0, iparam_exeffect2_);
//		DesignManager::AddExTime(-1);
//	}
//
//	// 左右入力でメイン画像を傾かせる
//	if (FpsManager::GetInterval(2) == 0) {
//		if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && imgdiv_main_ < 9) {
//			imgdiv_main_++;
//		}
//		else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && 1 < imgdiv_main_) {
//			imgdiv_main_--;
//		}
//	}
//	// 左右入力がないとき，メイン画像の傾きを戻す
//	if (FpsManager::GetInterval(3) == 0 && !KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::LEFT)) {
//		if ((5 < imgdiv_main_)) {
//			imgdiv_main_--;
//		}
//		else if (imgdiv_main_ < 5) {
//			imgdiv_main_++;
//		}
//	}
//	// メイン画像を描画する
//	PosManager::GetPosX(pparam_, &iparam_main_->pos_cx_);
//	PosManager::GetPosY(pparam_, &iparam_main_->pos_cy_);
//	if (FpsManager::GetInterval(20) < 10) {
//		ImgManager::Draw(imgfile_user1a_, imgdiv_main_, iparam_main_);
//	} else {
//		ImgManager::Draw(imgfile_user1b_, imgdiv_main_, iparam_main_);
//	}
//	// サブ画像を描画する
//	PosManager::GetPosX(pparam_, &iparam_sub_->pos_cx_);
//	iparam_sub_->pos_cx_ -= 36;
//	PosManager::GetPosY(pparam_, &iparam_sub_->pos_cy_);
//	iparam_sub_->pos_cy_ += 22;
//	ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
//	PosManager::GetPosX(pparam_, &iparam_sub_->pos_cx_);
//	iparam_sub_->pos_cx_ += 36;
//	PosManager::GetPosY(pparam_, &iparam_sub_->pos_cy_);
//	iparam_sub_->pos_cy_ += 22;
//	ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
//	imgdiv_sub_ = ++imgdiv_sub_ % 16;
//
//#ifdef __DEBUG__
//	DebugPrint::SetData(400, 450, "user_x[%d]",iparam_main_->pos_cx_);
//	DebugPrint::SetData(400, 470, "user_y[%d]", iparam_main_->pos_cy_);
//#endif
}

void User1::Draw2(void)
{
	// 追加のサブ画像を描画する
	//PosManager::GetPosX(pos_main_, &iparam_sub_->pos_cx_);
	//iparam_sub_->pos_cx_ -= 62;
	//PosManager::GetPosY(pos_main_, &iparam_sub_->pos_cy_);
	//iparam_sub_->pos_cy_ += 22;
	//ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
	//PosManager::GetPosX(pos_main_, &iparam_sub_->pos_cx_);
	//iparam_sub_->pos_cx_ += 62;
	//PosManager::GetPosY(pos_main_, &iparam_sub_->pos_cy_);
	//iparam_sub_->pos_cy_ += 22;
	//ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
}

void User1::Draw3(void)
{
	// 追加のサブ画像を描画する
	//PosManager::GetPosX(pos_main_, &iparam_sub_->pos_cx_);
	//iparam_sub_->pos_cx_ -= 49;
	//PosManager::GetPosY(pos_main_, &iparam_sub_->pos_cy_);
	//iparam_sub_->pos_cy_ += 6;
	//ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
	//PosManager::GetPosX(pos_main_, &iparam_sub_->pos_cx_);
	//iparam_sub_->pos_cx_ += 49;
	//PosManager::GetPosY(pos_main_, &iparam_sub_->pos_cy_);
	//iparam_sub_->pos_cy_ += 6;
	//ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
}

void User1::DrawInvincible(void)
{
	//// EX-ARMS 発動 (EX-TIME 250f)
	//if (KeyManager::IsPressKey(eKEY::EXARMS) && 100 <= DesignManager::GetExArms()) {
	//	SoundManager::Play(soundfile_exstart_, DX_PLAYTYPE_BACK);
	//	DesignManager::AddExArms(-100);
	//	iparam_exeffect1_->blend_alpha_ = 255;
	//	iparam_exeffect1_->extend_rate_ = 0.1;
	//	PosManager::GetPosX(pparam_, &iparam_exeffect1_->pos_cx_);
	//	PosManager::GetPosY(pparam_, &iparam_exeffect1_->pos_cy_);
	//	iparam_exeffect2_->extend_rate_ = 0.1;
	//	iparam_exeffect3a_->draw_angle_ = 0.0;
	//	iparam_exeffect3b_->draw_angle_ = 0.0;
	//	DesignManager::AddExTime(250);
	//	ArmsManager::DeleteAll(eOBJECT::NUM::TARGET_ARMS_SMALL);
	//}
	//if (0 < DesignManager::GetExTime()) {
	//	// exarms1a エフェクト(素材がないのでImgManagerで実現)
	//	if (15 < iparam_exeffect1_->blend_alpha_) {
	//		ImgManager::Draw(imgfile_exeffect1_, 0, iparam_exeffect1_);
	//		iparam_exeffect1_->blend_alpha_ -= 15;
	//		iparam_exeffect1_->extend_rate_ += 0.2;
	//	}
	//	if (10 < DesignManager::GetExTime()) {
	//		iparam_exeffect3a_->draw_angle_ += 0.06;
	//		PosManager::GetPosX(pparam_, &iparam_exeffect3a_->pos_cx_);
	//		PosManager::GetPosY(pparam_, &iparam_exeffect3a_->pos_cy_);
	//		ImgManager::Draw(imgfile_exeffect3_, 0, iparam_exeffect3a_);
	//		iparam_exeffect3b_->draw_angle_ -= 0.06;
	//		PosManager::GetPosX(pparam_, &iparam_exeffect3b_->pos_cx_);
	//		PosManager::GetPosY(pparam_, &iparam_exeffect3b_->pos_cy_);
	//		ImgManager::Draw(imgfile_exeffect3_, 0, iparam_exeffect3b_);
	//	}
	//	// exarms2 エフェクト(素材がないのでImgManagerで実現)
	//	if (iparam_exeffect2_->extend_rate_ < 1.0)
	//		iparam_exeffect2_->extend_rate_ += 0.1;
	//	PosManager::GetPosX(pparam_, &iparam_exeffect2_->pos_cx_);
	//	PosManager::GetPosY(pparam_, &iparam_exeffect2_->pos_cy_);
	//	ImgManager::Draw(imgfile_exeffect2_, 0, iparam_exeffect2_);
	//	DesignManager::AddExTime(-1);
	//}

	//// 左右入力でメイン画像を傾かせる
	//if (FpsManager::GetInterval(3) == 0) {
	//	if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && imgdiv_main_ < 9) {
	//		imgdiv_main_++;
	//	}
	//	else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && 1 < imgdiv_main_) {
	//		imgdiv_main_--;
	//	}
	//}
	//// 左右入力がないとき，メイン画像の傾きを戻す
	//if (FpsManager::GetInterval(4) == 0 && !KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::LEFT)) {
	//	if ((5 < imgdiv_main_)) {
	//		imgdiv_main_--;
	//	}
	//	else if (imgdiv_main_ < 5) {
	//		imgdiv_main_++;
	//	}
	//}
	//// メイン画像を描画する
	//PosManager::GetPosX(pparam_, &iparam_main_invincible_->pos_cx_);
	//PosManager::GetPosY(pparam_, &iparam_main_invincible_->pos_cy_);
	//if (FpsManager::GetInterval(20) < 10) {
	//	ImgManager::Draw(imgfile_user1a_, imgdiv_main_, iparam_main_invincible_);
	//} else {
	//	ImgManager::Draw(imgfile_user1b_, imgdiv_main_, iparam_main_invincible_);
	//}
	//// サブ画像を描画する
	//PosManager::GetPosX(pparam_, &iparam_sub_->pos_cx_);
	//iparam_sub_->pos_cx_ -= 36;
	//PosManager::GetPosY(pparam_, &iparam_sub_->pos_cy_);
	//iparam_sub_->pos_cy_ += 22;
	//ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
	//PosManager::GetPosX(pparam_, &iparam_sub_->pos_cx_);
	//iparam_sub_->pos_cx_ += 36;
	//PosManager::GetPosY(pparam_, &iparam_sub_->pos_cy_);
	//iparam_sub_->pos_cy_ += 22;
	//ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
	//imgdiv_sub_ = ++imgdiv_sub_ % 16;
}


void User1::Move(void)
{
	double move_axis_x;
	double move_position_x, move_position_y;
	double position_x, position_y;
	double panel_max_x, panel_min_x;
	double panel_max_y, panel_min_y;


	PosManager::GetAbsolutePanelMaxX(&panel_max_x);
	PosManager::GetAbsolutePanelMinX(&panel_min_x);
	PosManager::GetAbsolutePanelMaxY(&panel_max_y);
	PosManager::GetAbsolutePanelMinY(&panel_min_y);
	// ************
	//  軸移動１
	// ************
	// 左右方向
	if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		move_axis_x = PosManager::MoveAxisX(2.0);
	} else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		move_axis_x = PosManager::MoveAxisX(1.0);
	} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		move_axis_x = PosManager::MoveAxisX(-2.0);
	} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		move_axis_x = PosManager::MoveAxisX(-1.0);
	}

	// ************
	//  自機移動
	// ************
	// 左右方向
	PosManager::GetPosX(pparam_, &position_x);
	if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (position_x + (-6.0 + move_axis_x) < panel_min_x) {
			move_position_x = 0;
		} else {
			move_position_x = (-6.0 + move_axis_x);
			PosManager::MovePosA(pparam_, &move_position_x, NULL);
		}
	} else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (position_x + (-3.0 + move_axis_x) < panel_min_x) {
			move_position_x = 0;
		} else {
			move_position_x = (-3.0 + move_axis_x);
			PosManager::MovePosA(pparam_, &move_position_x, NULL);
		}		
	} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (panel_max_x < position_x + (6.0 + move_axis_x)) {
			move_position_x = 0;
		} else {
			move_position_x = (6.0 + move_axis_x);
			PosManager::MovePosA(pparam_, &move_position_x, NULL);
		}		
	} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (panel_max_x < position_x + (3.0 + move_axis_x)) {
			move_position_x = 0;
		} else {
			move_position_x = (3.0 + move_axis_x);
			PosManager::MovePosA(pparam_, &move_position_x, NULL);
		}		
	}
	// 上下方向
	PosManager::GetPosY(pparam_, &position_y);
	if (KeyManager::GetKeyFlagNow(eKEY::UP) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (position_y - 6.0 < panel_min_y) {
			move_position_y = 0;
		} else {
			move_position_y = -6.0;
			PosManager::MovePosA(pparam_, NULL, &move_position_y);
		}
	} else if (KeyManager::GetKeyFlagNow(eKEY::UP) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (position_y - 3.0 < panel_min_y) {
			move_position_y = 0;
		} else {
			move_position_y = -3.0;
			PosManager::MovePosA(pparam_, NULL, &move_position_y);
		}
	} else if (KeyManager::GetKeyFlagNow(eKEY::DOWN) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (panel_max_y < position_y + 6.0) {
			move_position_y = 0;
		} else {
			move_position_y = 6.0;
			PosManager::MovePosA(pparam_, NULL, &move_position_y);
		}		
	} else if (KeyManager::GetKeyFlagNow(eKEY::DOWN) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (panel_max_y < position_y + 3.0) {
			move_position_y = 0;
		} else {
			move_position_y = 3.0;
			PosManager::MovePosA(pparam_, NULL, &move_position_y);
		}		
	}

	// ************
	//  軸移動２
	// ************
	// 左右方向
	if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (move_position_x == 0)
			PosManager::MoveAxisX(6.0 - move_axis_x);
	} else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (move_position_x == 0)
			PosManager::MoveAxisX(3.0 - move_axis_x);
	} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (move_position_x == 0)
			PosManager::MoveAxisX(-6.0 - move_axis_x);
	} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (move_position_x == 0)
			PosManager::MoveAxisX(-3.0 - move_axis_x);
	}


	//// ************
	////  軸移動１
	//// ************
	//// 左右方向
	//if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	move_axis_x = PosManager::MoveAxisX(2.0);
	//} else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	move_axis_x = PosManager::MoveAxisX(1.0);
	//} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	move_axis_x = PosManager::MoveAxisX(-2.0);
	//} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	move_axis_x = PosManager::MoveAxisX(-1.0);
	//}

	//// ************
	////  自機移動
	//// ************
	//// 左右方向
	//PosManager::GetPosX(pparam_, &position_x);
	//if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (position_x + (-6.0 + move_axis_x) < DRAW_PANEL_MIN_X) {
	//		move_position_x = 0;
	//	} else {
	//		move_position_x = (-6.0 + move_axis_x);
	//		PosManager::MovePosA(pparam_, &move_position_x, NULL);
	//	}
	//} else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (position_x + (-3.0 + move_axis_x) < DRAW_PANEL_MIN_X) {
	//		move_position_x = 0;
	//	} else {
	//		move_position_x = (-3.0 + move_axis_x);
	//		PosManager::MovePosA(pparam_, &move_position_x, NULL);
	//	}		
	//} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (DRAW_PANEL_MAX_X < position_x + (6.0 + move_axis_x)) {
	//		move_position_x = 0;
	//	} else {
	//		move_position_x = (6.0 + move_axis_x);
	//		PosManager::MovePosA(pparam_, &move_position_x, NULL);
	//	}		
	//} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (DRAW_PANEL_MAX_X < position_x + (3.0 + move_axis_x)) {
	//		move_position_x = 0;
	//	} else {
	//		move_position_x = (3.0 + move_axis_x);
	//		PosManager::MovePosA(pparam_, &move_position_x, NULL);
	//	}		
	//}
	//// 上下方向
	//PosManager::GetPosY(pparam_, &position_y);
	//if (KeyManager::GetKeyFlagNow(eKEY::UP) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (position_y - 6.0 < DRAW_PANEL_MIN_Y) {
	//		move_position_y = 0;
	//	} else {
	//		move_position_y = -6.0;
	//		PosManager::MovePosA(pparam_, NULL, &move_position_y);
	//	}
	//} else if (KeyManager::GetKeyFlagNow(eKEY::UP) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (position_y - 3.0 < DRAW_PANEL_MIN_Y) {
	//		move_position_y = 0;
	//	} else {
	//		move_position_y = -3.0;
	//		PosManager::MovePosA(pparam_, NULL, &move_position_y);
	//	}
	//} else if (KeyManager::GetKeyFlagNow(eKEY::DOWN) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (DRAW_PANEL_MAX_Y < position_y + 6.0) {
	//		move_position_y = 0;
	//	} else {
	//		move_position_y = 6.0;
	//		PosManager::MovePosA(pparam_, NULL, &move_position_y);
	//	}		
	//} else if (KeyManager::GetKeyFlagNow(eKEY::DOWN) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (DRAW_PANEL_MAX_Y < position_y + 3.0) {
	//		move_position_y = 0;
	//	} else {
	//		move_position_y = 3.0;
	//		PosManager::MovePosA(pparam_, NULL, &move_position_y);
	//	}		
	//}

	//// ************
	////  軸移動２
	//// ************
	//// 左右方向
	//if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (move_position_x == 0)
	//		PosManager::MoveAxisX(6.0 - move_axis_x);
	//} else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (move_position_x == 0)
	//		PosManager::MoveAxisX(3.0 - move_axis_x);
	//} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (move_position_x == 0)
	//		PosManager::MoveAxisX(-6.0 - move_axis_x);
	//} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
	//	if (move_position_x == 0)
	//		PosManager::MoveAxisX(-3.0 - move_axis_x);
	//}
}