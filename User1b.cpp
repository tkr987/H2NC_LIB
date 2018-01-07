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
#include "User1b.h"
//#define __DEBUG__

using namespace NH2;

User1b::User1b(void)
{
	aparam_ = new ArmsParam1;
	aparam_ex_ = new ArmsParam1;
	eparam_death_ = new EffectParam1;
	eparam_flash_ = new EffectParam1b;
	iparam_exarms_ = new ImgParam4;
	iparam_main_ = new ImgParam4;
	iparam_start_ = new ImgParam4;
	iparam_sub_ = new ImgParam4;
	pparam_main_ = new PosParam1;
	// 画像ファイル
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH80;
	imgfile_dot_ = IMG_LOAD_USER_DOT;
	imgfile_arms_ = IMG_LOAD_ARMS_PURPLE100U;
	imgfile_effect_arms_ = ImgManager::LoadImg(4, 1, 64, 64, "data/img_effect/UserArms64.png");
	imgfile_effect_flash_ = IMG_LOAD_EFFECT_FLASH256;
	imgfile_exarms_ = IMG_LOAD_USER_EXARMS;
	imgfile_start_ = IMG_LOAD_USER_START;
	imgfile_sub_ = ImgManager::LoadImg(16, 1, 48, 48, "data/img_user1/sub.png");
	imgfile_user1a_ = ImgManager::LoadImg(5, 2, 152, 152, "data/img_user1/user1a.png");
	imgfile_user1b_ = ImgManager::LoadImg(5, 2, 152, 152, "data/img_user1/user1b.png");
	// サウンドファイル
	soundfile_arms_ = SoundManager::Load("data/sound/user_arms1v2.wav");
	soundfile_death_ = SoundManager::Load("data/sound/target_death2.wav");
	soundfile_exarms_start_ = SoundManager::Load("data/sound/user_exarms_start.wav");
}

User1b::~User1b(void)
{
	delete aparam_;
	delete aparam_ex_;
	delete eparam_death_;
	delete eparam_flash_;
	delete iparam_exarms_;
	delete iparam_main_;
	delete iparam_sub_;
	delete pparam_main_;
}

void User1b::Clear(void)
{
	// 変数初期化
	exarms_draw_angle_l_ = 0;
	exarms_draw_angle_r_ = 0;
	exarms_flag_ = false;
	exarms_time_ = 0;
	frames_ = 0;
	start_draw_angle_ = 0;
	imgdiv_main_ = 5;
	imgdiv_sub_ = 0;
//	sync_movecount_ = 0;
	// エフェクト設定
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::GROUP::USER_EFFECT;
	eparam_death_->img_divmax_ = 7;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 2;
	// Img ExArms 固定パラメータ
	iparam_exarms_->extend_rate_ = 1.0;
	iparam_exarms_->flag_trans_ = true;
	iparam_exarms_->flag_turn_ = false;
	iparam_exarms_->group_type_ = eOBJECT::GROUP::USER;
	// Img Main 固定パラメータ
	iparam_main_->draw_angle_ = 0;
	iparam_main_->extend_rate_ = 0.4;
	iparam_main_->flag_trans_ = true;
	iparam_main_->flag_turn_ = false;
	iparam_main_->group_type_ = eOBJECT::GROUP::USER;
	// Img Sub 固定パラメータ
	iparam_start_->draw_angle_ = 0;
	iparam_start_->extend_rate_ = 0.5;
	iparam_start_->flag_trans_ = true;
	iparam_start_->flag_turn_ = false;
	iparam_start_->group_type_ = eOBJECT::GROUP::USER;
	// Img Sub 固定パラメータ
	iparam_sub_->draw_angle_ = 0;
	iparam_sub_->extend_rate_ = 0.5;
	iparam_sub_->flag_trans_ = true;
	iparam_sub_->flag_turn_ = false;
	iparam_sub_->group_type_ = eOBJECT::GROUP::USER;
	// Arms 固定パラメータ
	aparam_->hit_effect_ = true;
	aparam_->hit_effect_img_divmax_ = 3;
	aparam_->hit_effect_img_divmin_ = 0;
	aparam_->hit_effect_img_extend_rate_ = 0.5;
	aparam_->hit_effect_img_id_ = imgfile_effect_arms_;
	aparam_->hit_effect_img_interval_ = 1;
	aparam_->img_id_ = imgfile_arms_;
	aparam_->img_rotate_ = 0;
	aparam_->shot_range_ = 8.0;
	aparam_->shot_speed_ = 16.0;
	// Effect Flash 固定パラメータ
	eparam_flash_->blend_alpha_ = 255;
	eparam_flash_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_flash_->extend_rate_ = 1.0;
	eparam_flash_->group_ = eOBJECT::GROUP::USER_EFFECT;
	eparam_flash_->img_divmax_ = 19;
	eparam_flash_->img_divmin_ = 0;
	eparam_flash_->img_id_ = imgfile_effect_flash_;
	eparam_flash_->img_interval_ = 1;
	// POS PARAM 初期パラメータ
	pparam_main_->SetPow(1.0);
	pparam_main_->SetRange(2.0);
	pparam_main_->SetStartX(200);
	pparam_main_->SetStartY(450);
	PosManager::Generate(eOBJECT::GROUP::USER, pparam_main_, POS_NAME_USER_MAIN);
	// その他 設定
//	DesignManager::SetAttackLV(1.0);
	DesignManager::SetExArms(150);
	DesignManager::SetStar(2);
}

void User1b::Run(void)
{
	int star;

	DesignManager::GetStar(&star);
	if (star == -1)
		return;

	if (exarms_flag_) {
		aparam_->shot_pow_ = 1.1;
	} else {
		aparam_->shot_pow_ = 1.0;
	}

	Collision();
	Draw();
	DrawEx();
	Move();
	Shot1();
	Shot2();
	ShotEx1();
	ShotEx2();
	UpdateEx();
	frames_++;

	#ifdef __DEBUG__
		ImgManager::Draw(imgfile_dot_, 0, iparam_main_);
	#endif
}


void User1b::Draw(void)
{
	int alv;

	// 無敵時間
	if (frames_ < 150) {
		PosManager::GetPos(pparam_main_, &iparam_start_->pos_cx_, &iparam_start_->pos_cy_);
		ImgManager::Draw(imgfile_start_, 0, iparam_start_);
		iparam_start_->draw_angle_ += CalcRAD(2.0);
	}

	// 左右入力でメイン画像を傾かせる
	if (frames_ % 2 == 0) {
		if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && imgdiv_main_ < 9) {
			imgdiv_main_++;
		} else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && 1 < imgdiv_main_) {
			imgdiv_main_--;
		}
	}
	// 左右入力がないとき，メイン画像の傾きを戻す
	if (frames_ % 3 == 0 && !KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::LEFT)) {
		if ((5 < imgdiv_main_)) {
			imgdiv_main_--;
		} else if (imgdiv_main_ < 5) {
			imgdiv_main_++;
		}
	}
	// ***************************
	//  メイン画像を描画する
	// ***************************
	PosManager::GetPosX(pparam_main_, &iparam_main_->pos_cx_);
	PosManager::GetPosY(pparam_main_, &iparam_main_->pos_cy_);
	if (frames_ % 20 < 10) {
		ImgManager::Draw(imgfile_user1a_, imgdiv_main_, iparam_main_);
	} else {
		ImgManager::Draw(imgfile_user1b_, imgdiv_main_, iparam_main_);
	}

	// ***************************
	//  サブ画像を描画する
	// ***************************
	DesignManager::GetAttackLV(&alv, 1.0);
	PosManager::GetPos(pparam_main_, &iparam_sub_->pos_cx_, &iparam_sub_->pos_cy_);
	iparam_sub_->pos_cx_ -= 36;
	iparam_sub_->pos_cy_ += 22;
	ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
	PosManager::GetPos(pparam_main_, &iparam_sub_->pos_cx_, &iparam_sub_->pos_cy_);
	iparam_sub_->pos_cx_ += 36;
	iparam_sub_->pos_cy_ += 22;
	ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
	if (400 <= alv) {
		PosManager::GetPos(pparam_main_, &iparam_sub_->pos_cx_, &iparam_sub_->pos_cy_);
		iparam_sub_->pos_cx_ -= 60;
		iparam_sub_->pos_cy_ += 22;
		ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
		PosManager::GetPos(pparam_main_, &iparam_sub_->pos_cx_, &iparam_sub_->pos_cy_);
		iparam_sub_->pos_cx_ += 60;
		iparam_sub_->pos_cy_ += 22;
		ImgManager::Draw(imgfile_sub_, imgdiv_sub_, iparam_sub_);
	}
	imgdiv_sub_ = ++imgdiv_sub_ % 16;

#ifdef __DEBUG__
	DebugPrint::SetData(400, 450, "user_x[%d]",iparam_main_->pos_cx_);
	DebugPrint::SetData(400, 470, "user_y[%d]", iparam_main_->pos_cy_);
#endif
}


void User1b::DrawEx(void)
{

	if (exarms_time_ == 250) {
		PosManager::GetPos(pparam_main_, &eparam_flash_->x_, &eparam_flash_->y_);
		EffectManager::Create(eparam_flash_);
		exarms_draw_angle_l_ = 0;
		exarms_draw_angle_r_ = 0;
	}
	if (0 < exarms_time_) {
		PosManager::GetPos(pparam_main_, &iparam_exarms_->pos_cx_, &iparam_exarms_->pos_cy_);
		iparam_exarms_->draw_angle_ = exarms_draw_angle_l_;
		ImgManager::Draw(imgfile_exarms_, 0, iparam_exarms_);
		iparam_exarms_->draw_angle_ = exarms_draw_angle_r_;
		ImgManager::Draw(imgfile_exarms_, 0, iparam_exarms_);
		exarms_draw_angle_l_ += CalcRAD(-10);
		exarms_draw_angle_r_ += CalcRAD(10);
	}
}


void User1b::Shot1(void)
{
	double alv;

	if (frames_ % 5 != 0)
		return;
	if (KeyManager::GetKeyFlagNow(eKEY::SLOW))
		return;
	if (!KeyManager::GetKeyFlagNow(eKEY::ARMS))
		return;

	DesignManager::GetAttackLV(&alv);
	aparam_->shot_pow_ = (exarms_flag_) ? 1.0 + alv * 0.003 : 1.0;
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_angle_ = CalcRAD(-100.0);
	aparam_->shot_x_ -= 30;
	aparam_->img_angle_ = CalcRAD(-100.0);
	ArmsManager::UserShot(aparam_);
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_angle_ = CalcRAD(-90.0);
	aparam_->shot_x_ -= 15;
	aparam_->img_angle_ = CalcRAD(-90.0);
	ArmsManager::UserShot(aparam_);
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_angle_ = CalcRAD(-90.0);
	aparam_->img_angle_ = CalcRAD(-90.0);
	aparam_->shot_x_ += 15;
	ArmsManager::UserShot(aparam_);
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_angle_ = CalcRAD(-80.0);
	aparam_->shot_x_ += 30;
	aparam_->img_angle_ = CalcRAD(-80.0);
	ArmsManager::UserShot(aparam_);
	if (200 <= alv) {
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = CalcRAD(-110.0);
		aparam_->shot_x_ -= 36;
		aparam_->shot_y_ += 22;
		aparam_->img_angle_ = CalcRAD(-110.0);
		ArmsManager::UserShot(aparam_);
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = CalcRAD(-70.0);
		aparam_->shot_x_ += 36;
		aparam_->shot_y_ += 22;
		aparam_->img_angle_ = CalcRAD(-70.0);
		ArmsManager::UserShot(aparam_);	}
	if(400 <= alv) {
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = CalcRAD(-120.0);
		aparam_->shot_x_ -= 60;
		aparam_->shot_y_ += 22;
		aparam_->img_angle_ = CalcRAD(-120.0);
		ArmsManager::UserShot(aparam_);
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = CalcRAD(-60.0);
		aparam_->shot_x_ += 60;
		aparam_->shot_y_ += 22;
		aparam_->img_angle_ = CalcRAD(-60.0);
		ArmsManager::UserShot(aparam_);	
	}

}

void User1b::Shot2(void)
{
	double alv;

	if (frames_ % 5 != 0)
		return;
	if (!KeyManager::GetKeyFlagNow(eKEY::SLOW))
		return;
	if (!KeyManager::GetKeyFlagNow(eKEY::ARMS))
		return;

	DesignManager::GetAttackLV(&alv);
	aparam_->shot_angle_ = CalcRAD(-90.0);
	aparam_->img_angle_ = CalcRAD(-90.0);
	aparam_->shot_pow_ = (exarms_flag_) ? 1.0 + alv * 0.003 : 1.0;
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_x_ -= 30;
	ArmsManager::UserShot(aparam_);
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_x_ -= 15;
	ArmsManager::UserShot(aparam_);
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_x_ += 15;
	ArmsManager::UserShot(aparam_);
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_x_ += 30;
	ArmsManager::UserShot(aparam_);
	if (200 <= alv) {
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_x_ -= 36;
		aparam_->shot_y_ += 22;
		ArmsManager::UserShot(aparam_);
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_x_ += 36;
		aparam_->shot_y_ += 22;
		ArmsManager::UserShot(aparam_);
	}
	if (400 <= alv) {
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_x_ -= 60;
		aparam_->shot_y_ += 22;
		ArmsManager::UserShot(aparam_);
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_x_ += 60;
		aparam_->shot_y_ += 22;	
		ArmsManager::UserShot(aparam_);
	}
}

void User1b::ShotEx1(void)
{
	double alv;

	if (!exarms_flag_)
		return;
	if (frames_ % 5 != 0)
		return;
	if (KeyManager::GetKeyFlagNow(eKEY::SLOW))
		return;
	if (!KeyManager::GetKeyFlagNow(eKEY::ARMS))
		return;

	DesignManager::GetAttackLV(&alv);
	aparam_->shot_pow_ = (exarms_flag_) ? 1.0 + alv * 0.003 : 1.0;
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_angle_ = CalcRAD(-95.0);
	aparam_->shot_x_ -= 30;
	aparam_->img_angle_ = CalcRAD(-95.0);
	ArmsManager::UserShot(aparam_);
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_angle_ = CalcRAD(-85.0);
	aparam_->shot_x_ += 30;
	aparam_->img_angle_ = CalcRAD(-85.0);
	ArmsManager::UserShot(aparam_);
	if (200 <= alv) {
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = CalcRAD(-105.0);
		aparam_->shot_x_ -= 36;
		aparam_->shot_y_ += 22;
		aparam_->img_angle_ = CalcRAD(-105.0);
		ArmsManager::UserShot(aparam_);
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = CalcRAD(-75.0);
		aparam_->shot_x_ += 36;
		aparam_->shot_y_ += 22;
		aparam_->img_angle_ = CalcRAD(-75.0);
		ArmsManager::UserShot(aparam_);	}
	if(400 <= alv) {
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = CalcRAD(-115.0);
		aparam_->shot_x_ -= 60;
		aparam_->shot_y_ += 22;
		aparam_->img_angle_ = CalcRAD(-115.0);
		ArmsManager::UserShot(aparam_);
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_angle_ = CalcRAD(-65.0);
		aparam_->shot_x_ += 60;
		aparam_->shot_y_ += 22;
		aparam_->img_angle_ = CalcRAD(-65.0);
		ArmsManager::UserShot(aparam_);	
	}
}


void User1b::ShotEx2(void)
{
	double alv;

	if (!exarms_flag_)
		return;
	if (frames_ % 5 != 0)
		return;
	if (!KeyManager::GetKeyFlagNow(eKEY::SLOW))
		return;
	if (!KeyManager::GetKeyFlagNow(eKEY::ARMS))
		return;

	DesignManager::GetAttackLV(&alv);
	aparam_->shot_angle_ = CalcRAD(-90.0);
	aparam_->img_angle_ = CalcRAD(-90.0);
	aparam_->shot_pow_ = (exarms_flag_) ? 1.0 + alv * 0.003 : 1.0;
	ArmsManager::UserShot(aparam_);
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_x_ -= 7;
	ArmsManager::UserShot(aparam_);
	PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
	aparam_->shot_x_ += 7;
	ArmsManager::UserShot(aparam_);
	if (200 <= alv) {
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_x_ -= 46;
		aparam_->shot_y_ += 22;
		ArmsManager::UserShot(aparam_);
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_x_ += 46;
		aparam_->shot_y_ += 22;
		ArmsManager::UserShot(aparam_);
	}
	if (400 <= alv) {
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_x_ -= 70;
		aparam_->shot_y_ += 22;
		ArmsManager::UserShot(aparam_);
		PosManager::GetPos(pparam_main_, &aparam_->shot_x_, &aparam_->shot_y_);
		aparam_->shot_x_ += 70;
		aparam_->shot_y_ += 22;	
		ArmsManager::UserShot(aparam_);
	}
}

void User1b::UpdateEx(void)
{
	double exarms;

	if (!exarms_flag_) {
		if (KeyManager::IsPressKey(eKEY::TYPE::EXARMS)) {
			DesignManager::GetExArms(&exarms);
			if (100 <= exarms) {
				exarms_flag_ = true;
				exarms_time_ = 250;
				ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_LARGE);
				ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_SMALL);
				DesignManager::AddExArms(-100.0);
				SoundManager::Play(soundfile_exarms_start_, DX_PLAYTYPE_BACK);
			}
		}
	} else {
		exarms_time_--;
		if (exarms_time_ == 0)
			exarms_flag_ = false;
	}
}


//void User1::Attack1(void)
//{
//	double pos_x;
//	double pos_y;
//
//	PosManager::GetPosX(pparam_, &pos_x);
//	PosManager::GetPosY(pparam_, &pos_y);
//	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
//		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
//		aparam_->shot_angle_ = CalcRAD(258.0);
//		aparam_->shot_x_ = pos_x - 36;
//		aparam_->shot_y_ = pos_y + 20;
//		aparam_->img_angle_ = CalcRAD(-12.0);
//		ArmsManager::UserShot(aparam_);
//		aparam_->shot_angle_ = CalcRAD(270.0);
//		aparam_->shot_x_ = pos_x - 16;
//		aparam_->shot_y_ = pos_y;
//		aparam_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_);
//		aparam_->shot_angle_ = CalcRAD(270.0);
//		aparam_->shot_x_ = pos_x + 16;
//		aparam_->shot_y_ = pos_y;
//		aparam_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_);
//		aparam_->shot_angle_ = CalcRAD(282.0);
//		aparam_->shot_x_ = pos_x + 36;
//		aparam_->shot_y_ = pos_y + 20;
//		aparam_->img_angle_ = CalcRAD(12.0);
//		ArmsManager::UserShot(aparam_);
//	} else if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
//		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
//		aparam_->shot_angle_ = CalcRAD(264.0);
//		aparam_->shot_x_ = pos_x - 36;
//		aparam_->shot_y_ = pos_y + 5;
//		aparam_->img_angle_ = CalcRAD(-6.0);
//		ArmsManager::UserShot(aparam_);
//		aparam_->shot_angle_ = CalcRAD(270.0);
//		aparam_->shot_x_ = pos_x - 16;
//		aparam_->shot_y_ = pos_y;
//		aparam_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_);
//		aparam_->shot_angle_ = CalcRAD(270.0);
//		aparam_->shot_x_ = pos_x + 16;
//		aparam_->shot_y_ = pos_y;
//		aparam_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_);
//		aparam_->shot_angle_ = CalcRAD(276.0);
//		aparam_->shot_x_ = pos_x + 36;
//		aparam_->shot_y_ = pos_y + 5;
//		aparam_->img_angle_ = CalcRAD(6.0);
//		ArmsManager::UserShot(aparam_);
//	}
//}
//
//void User1::Attack2(void)
//{
//	double pos_x;
//	double pos_y;
//
//	PosManager::GetPosX(pparam_, &pos_x);
//	PosManager::GetPosY(pparam_, &pos_y);
//	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
//		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
//		aparam_->shot_angle_ = 250.0;
//		aparam_->shot_x_ = pos_x - 62;
//		aparam_->shot_y_ = pos_y + 20;
//		aparam_->img_angle_ = -20.0;
//		ArmsManager::UserShot(aparam_);
//		aparam_->shot_angle_ = 290.0;
//		aparam_->shot_x_ = pos_x + 62;
//		aparam_->shot_y_ = pos_y + 20;
//		aparam_->img_angle_ = 20.0;
//		ArmsManager::UserShot(aparam_);
//	} else if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
//		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
//		aparam_->shot_angle_ = 260.0;
//		aparam_->shot_x_ = pos_x - 62;
//		aparam_->shot_y_ = pos_y + 20;
//		aparam_->img_angle_ = -10.0;
//		ArmsManager::UserShot(aparam_);
//		aparam_->shot_angle_ = 280.0;
//		aparam_->shot_x_ = pos_x + 62;
//		aparam_->shot_y_ = pos_y + 20;
//		aparam_->img_angle_ = 10.0;
//		ArmsManager::UserShot(aparam_);
//	}
//}
//
//void User1::Attack3(void)
//{
//	double pos_x;
//	double pos_y;
//
//	PosManager::GetPosX(pparam_, &pos_x);
//	PosManager::GetPosY(pparam_, &pos_y);
//	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS)) {
//		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
//		aparam_->shot_angle_ = 270.0;
//		aparam_->shot_x_ = pos_x - 46;
//		aparam_->shot_y_ = pos_y + 4;
//		aparam_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_);
//		aparam_->shot_angle_ = 270.0;
//		aparam_->shot_x_ = pos_x + 46;
//		aparam_->shot_y_ = pos_y + 4;
//		aparam_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_);
//	}
//}
//
//void User1::AttackEx1(void) 
//{
//	double pos_x;
//	double pos_y;
//
//	PosManager::GetPosX(pparam_, &pos_x);
//	PosManager::GetPosY(pparam_, &pos_y);
//	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
//		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
//		aparam_ex_->angle_ = CalcRAD(258.0);
//		aparam_ex_->create_x_ = pos_x - 36;
//		aparam_ex_->create_y_ = pos_y + 20;
//		aparam_ex_->img_angle_ = CalcRAD(-12.0);
//		ArmsManager::UserShot(aparam_ex_);
//		aparam_ex_->angle_ = CalcRAD(270.0);
//		aparam_ex_->create_x_ = pos_x - 16;
//		aparam_ex_->create_y_ = pos_y;
//		aparam_ex_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_ex_);
//		aparam_ex_->angle_ = CalcRAD(270.0);
//		aparam_ex_->create_x_ = pos_x + 16;
//		aparam_ex_->create_y_ = pos_y;
//		aparam_ex_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_ex_);
//		aparam_ex_->angle_ = CalcRAD(282.0);
//		aparam_ex_->create_x_ = pos_x + 36;
//		aparam_ex_->create_y_ = pos_y - 20;
//		aparam_ex_->img_angle_ = CalcRAD(12.0);
//		ArmsManager::UserShot(aparam_ex_);
//	} else if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
//		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
//		aparam_ex_->angle_ = CalcRAD(264.0);
//		aparam_ex_->create_x_ = pos_x - 36;
//		aparam_ex_->create_y_ = pos_y + 5;
//		aparam_ex_->img_angle_ = CalcRAD(-6.0);
//		ArmsManager::UserShot(aparam_ex_);
//		aparam_ex_->angle_ = CalcRAD(270.0);
//		aparam_ex_->create_x_ = pos_x - 16;
//		aparam_ex_->create_y_ = pos_y;
//		aparam_ex_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_ex_);
//		aparam_ex_->angle_ = CalcRAD(270.0);
//		aparam_ex_->create_x_ = pos_x + 16;
//		aparam_ex_->create_y_ = pos_y;
//		aparam_ex_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_ex_);
//		aparam_ex_->angle_ = CalcRAD(276.0);
//		aparam_ex_->create_x_ = pos_x + 36;
//		aparam_ex_->create_y_ = pos_y - 5;
//		aparam_ex_->img_angle_ = CalcRAD(6.0);
//		ArmsManager::UserShot(aparam_ex_);
//	}
//}
//
//void User1::AttackEx2(void)
//{
//	double pos_x;
//	double pos_y;
//
//	PosManager::GetPosX(pparam_, &pos_x);
//	PosManager::GetPosY(pparam_, &pos_y);
//	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
//		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
//		aparam_ex_->angle_ = 250.0;
//		aparam_ex_->create_x_ = pos_x - 62;
//		aparam_ex_->create_y_ = pos_y + 20;
//		aparam_ex_->img_angle_ = -20.0;
//		ArmsManager::UserShot(aparam_ex_);
//		aparam_ex_->angle_ = 290.0;
//		aparam_ex_->create_x_ = pos_x + 62;
//		aparam_ex_->create_y_ = pos_y + 20;
//		aparam_ex_->img_angle_ = 20.0;
//		ArmsManager::UserShot(aparam_ex_);
//	} else if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
//		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
//		aparam_ex_->angle_ = 260.0;
//		aparam_ex_->create_x_ = pos_x - 62;
//		aparam_ex_->create_y_ = pos_y + 20;
//		aparam_ex_->img_angle_ = -10.0;
//		ArmsManager::UserShot(aparam_ex_);
//		aparam_ex_->angle_ = 280.0;
//		aparam_ex_->create_x_ = pos_x + 62;
//		aparam_ex_->create_y_ = pos_y + 20;
//		aparam_ex_->img_angle_ = 10.0;
//		ArmsManager::UserShot(aparam_ex_);
//	}
//
//}
//
//void User1::AttackEx3(void)
//{
//	double pos_x;
//	double pos_y;
//
//	PosManager::GetPosX(pparam_, &pos_x);
//	PosManager::GetPosY(pparam_, &pos_y);
//	if (FpsManager::GetInterval(5) == 0 && KeyManager::GetKeyFlagNow(eKEY::ARMS)) {
//		SoundManager::Play(soundfile_arms_, DX_PLAYTYPE_BACK);
//		aparam_ex_->angle_ = 270.0;
//		aparam_ex_->create_x_ = pos_x - 46;
//		aparam_ex_->create_y_ = pos_y + 4;
//		aparam_ex_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_ex_);
//		aparam_ex_->angle_ = 270.0;
//		aparam_ex_->create_x_ = pos_x + 46;
//		aparam_ex_->create_y_ = pos_y + 4;
//		aparam_ex_->img_angle_ = 0;
//		ArmsManager::UserShot(aparam_ex_);
//	}
//}

void User1b::Collision(void)
{
	if (frames_ < 150)
		return;

	if (PosManager::GetHit(pparam_main_) != 0) {
		ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_LARGE);
		ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_SMALL);
		DesignManager::AddClockRank(-4.0);
		DesignManager::AddStar(-1);
		PosManager::GetPos(pparam_main_, &eparam_death_->x_, &eparam_death_->y_);
//		EffectManager::Create(eparam_death_);	
		SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);
		frames_ = 0;
	}

}

//void User1::Draw1(void)
//{
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
//		ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_SMALL);
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
//}


//void User1::DrawInvincible(void)
//{
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
//		ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_SMALL);
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
//		// exarms2 エフェクト(素材がないのでImgManagerで実現)
//		if (iparam_exeffect2_->extend_rate_ < 1.0)
//			iparam_exeffect2_->extend_rate_ += 0.1;
//		PosManager::GetPosX(pparam_, &iparam_exeffect2_->pos_cx_);
//		PosManager::GetPosY(pparam_, &iparam_exeffect2_->pos_cy_);
//		ImgManager::Draw(imgfile_exeffect2_, 0, iparam_exeffect2_);
//		DesignManager::AddExTime(-1);
//	}
//
//	// 左右入力でメイン画像を傾かせる
//	if (FpsManager::GetInterval(3) == 0) {
//		if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && imgdiv_main_ < 9) {
//			imgdiv_main_++;
//		}
//		else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && 1 < imgdiv_main_) {
//			imgdiv_main_--;
//		}
//	}
//	// 左右入力がないとき，メイン画像の傾きを戻す
//	if (FpsManager::GetInterval(4) == 0 && !KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::LEFT)) {
//		if ((5 < imgdiv_main_)) {
//			imgdiv_main_--;
//		}
//		else if (imgdiv_main_ < 5) {
//			imgdiv_main_++;
//		}
//	}
//	// メイン画像を描画する
//	PosManager::GetPosX(pparam_, &iparam_main_invincible_->pos_cx_);
//	PosManager::GetPosY(pparam_, &iparam_main_invincible_->pos_cy_);
//	if (FpsManager::GetInterval(20) < 10) {
//		ImgManager::Draw(imgfile_user1a_, imgdiv_main_, iparam_main_invincible_);
//	} else {
//		ImgManager::Draw(imgfile_user1b_, imgdiv_main_, iparam_main_invincible_);
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
//}


void User1b::Move(void)
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
	PosManager::GetPosX(pparam_main_, &position_x);
	if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (position_x + (-9.0 + move_axis_x) < panel_min_x) {
			move_position_x = 0;
		} else {
			move_position_x = (-9.0 + move_axis_x);
			PosManager::MovePosA(pparam_main_, &move_position_x, NULL);
		}
	} else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (position_x + (-4.5 + move_axis_x) < panel_min_x) {
			move_position_x = 0;
		} else {
			move_position_x = (-4.5 + move_axis_x);
			PosManager::MovePosA(pparam_main_, &move_position_x, NULL);
		}		
	} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (panel_max_x < position_x + (9.0 + move_axis_x)) {
			move_position_x = 0;
		} else {
			move_position_x = (9.0 + move_axis_x);
			PosManager::MovePosA(pparam_main_, &move_position_x, NULL);
		}		
	} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (panel_max_x < position_x + (4.5 + move_axis_x)) {
			move_position_x = 0;
		} else {
			move_position_x = (4.5 + move_axis_x);
			PosManager::MovePosA(pparam_main_, &move_position_x, NULL);
		}		
	}
	// 上下方向
	PosManager::GetPosY(pparam_main_, &position_y);
	if (KeyManager::GetKeyFlagNow(eKEY::UP) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (position_y - 9.0 < panel_min_y) {
			move_position_y = 0;
		} else {
			move_position_y = -9.0;
			PosManager::MovePosA(pparam_main_, NULL, &move_position_y);
		}
	} else if (KeyManager::GetKeyFlagNow(eKEY::UP) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (position_y - 4.5 < panel_min_y) {
			move_position_y = 0;
		} else {
			move_position_y = -4.5;
			PosManager::MovePosA(pparam_main_, NULL, &move_position_y);
		}
	} else if (KeyManager::GetKeyFlagNow(eKEY::DOWN) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (panel_max_y < position_y + 9.0) {
			move_position_y = 0;
		} else {
			move_position_y = 9.0;
			PosManager::MovePosA(pparam_main_, NULL, &move_position_y);
		}		
	} else if (KeyManager::GetKeyFlagNow(eKEY::DOWN) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (panel_max_y < position_y + 4.5) {
			move_position_y = 0;
		} else {
			move_position_y = 4.5;
			PosManager::MovePosA(pparam_main_, NULL, &move_position_y);
		}		
	}

	// ************
	//  軸移動２
	// ************
	// 左右方向
	if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (move_position_x == 0)
			PosManager::MoveAxisX(9.0 - move_axis_x);
	} else if (KeyManager::GetKeyFlagNow(eKEY::LEFT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (move_position_x == 0)
			PosManager::MoveAxisX(4.5 - move_axis_x);
	} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && !KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (move_position_x == 0)
			PosManager::MoveAxisX(-9.0 - move_axis_x);
	} else if (KeyManager::GetKeyFlagNow(eKEY::RIGHT) && KeyManager::GetKeyFlagNow(eKEY::SLOW)) {
		if (move_position_x == 0)
			PosManager::MoveAxisX(-4.5 - move_axis_x);
	}
}

