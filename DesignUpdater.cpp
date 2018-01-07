#include <math.h>
#include "DebugPrint.h"
#include "DesignUpdater.h"
#include "KeyManager.h"
#include "ImgManager.h"
#include "PosManager.h"
#define __DEBUG__

using namespace NH2;
using namespace NH3;

DesignUpdater::DesignUpdater(void) : NH2::DesignManager() 
{
	// �`��֘A�̏�����
	iparam1_alv_ = new ImgParam1;
	iparam1_boss_frame_ = new ImgParam1;
	iparam1_boss_health_ = new ImgParam1;
	iparam1_clock_dial_ = new ImgParam1;
	iparam4_clock_hands_ = new ImgParam4;
	iparam1_key_ = new ImgParam1;
	iparam1_score_ = new ImgParam1;
	iparam1_window_ = new ImgParam1;
	iparam1_exarms_ = new ImgParam1;
	iparam3_exarms_ = new ImgParam3;
	imgfile_clock_dial_ = IMG_LOAD_DESIGN_CLOCK_DIAL;
	imgfile_clock_hands_ = IMG_LOAD_DESIGN_CLOCK_HANDS;
	imgfile_clock_pin_ = IMG_LOAD_DESIGN_CLOCK_PIN;
	imgfile_gblack_ = ImgManager::LoadImg("data/12_img_design/gblack.png");
	imgfile_gblue_ = ImgManager::LoadImg("data/12_img_design/gblue.png");
	imgfile_gred_ = ImgManager::LoadImg("data/12_img_design/gred.png");
	imgfile_boss_health_black_ = IMG_LOAD_DESIGN_BOSS_HEALTH_BLACK;
	imgfile_boss_health_frame_ = IMG_LOAD_DESIGN_BOSS_HEALTH_FRAME;
	imgfile_boss_health_green_ = IMG_LOAD_DESIGN_BOSS_HEALTH_GREEN;
	imgfile_boss_health_red_ = IMG_LOAD_DESIGN_BOSS_HEALTH_RED;
	imgfile_kblack_ = ImgManager::LoadImg("data/12_img_design/kblack.png");
	imgfile_kred_ = ImgManager::LoadImg("data/12_img_design/kred.png");
	imgfile_rank_ = ImgManager::LoadImg(10, 1, 24, 48, "data/12_img_design/rank.png");
	imgfile_score_ = ImgManager::LoadImg(10, 1, 23, 35, "data/12_img_design/score_v3.png");
	imgfile_star_ = ImgManager::LoadImg("data/12_img_design/star.png");
	imgfile_window_ = ImgManager::LoadImg("data/12_img_design/window.png");
	// �`��Œ�p�����[�^, ALV
	iparam1_alv_->flag_trans_ = true;
	iparam1_alv_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER3;
	// �`��Œ�p�����[�^, BOSS FRAME
	iparam1_boss_frame_->flag_trans_ = true;
	iparam1_boss_frame_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER3;
	// �`��Œ�p�����[�^, BOSS HEALTH
	iparam1_boss_health_->flag_trans_ = false;
	iparam1_boss_health_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER1;
	// �`��Œ�p�����[�^�C���v��
	iparam1_clock_dial_->flag_trans_ = true;
	iparam1_clock_dial_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER3;
	// �`��Œ�p�����[�^�C���v�j
	iparam4_clock_hands_->extend_rate_ = 1.0;
	iparam4_clock_hands_->flag_trans_ = true;
	iparam4_clock_hands_->flag_turn_ = false;
	iparam4_clock_hands_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER3;
	// EX-ARMS �Q�[�W�`��Œ�p�����[�^
	iparam1_exarms_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER1;
	iparam1_exarms_->flag_trans_ = false;
	iparam3_exarms_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER1;
	iparam3_exarms_->flag_trans_ = false;
	// �`��Œ�p�����[�^, �L�[����
	iparam1_key_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER1;
	iparam1_key_->flag_trans_ = false;
	// �`��Œ�p�����[�^, �X�R�A
	iparam1_score_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER3;
	iparam1_score_->x_ = 0;
	iparam1_score_->y_ = 0;
	iparam1_score_->flag_trans_ = true;
	// �`��Œ�p�����[�^, �E�B���h�E
	iparam1_window_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER2;
	iparam1_window_->x_ = 0;
	iparam1_window_->y_ = 0;
	iparam1_window_->flag_trans_ = true;
	iparam1_ = new ImgParam1;
	iparam3_ = new ImgParam3;
	iparam4_ = new ImgParam4;
}

DesignUpdater::~DesignUpdater(void)
{
	delete iparam1_alv_;
	delete iparam1_boss_frame_;
	delete iparam1_boss_health_;
	delete iparam1_clock_dial_;
	delete iparam4_clock_hands_;
	delete iparam1_key_;
	delete iparam1_exarms_;
	delete iparam3_exarms_;
	delete iparam1_;
	delete iparam3_;
	delete iparam4_;
}



void DesignUpdater::Run(void)
{
	// layer1
	DrawExArms();
//	DrawTargetHP();
	DrawKey();
	// layer2
	DrawWindow();
//	DrawExTime();
	// layer3
	DrawClockScore();
	DrawClockRank();
	DrawScore();
	DrawAttackLV();
	DrawStar();
	// layer1 & 3
	DrawBossHealth();
}

/**
@brief ExArms�`��֐�
@note
ExArms�͈̔͂�0-400%
**/
void DesignUpdater::DrawExArms(void)
{
	// gvalue_exarms 1%������̑�����
	const double exarms_width = 151.0 / 100.0;

	// EX-ARMS �Q�[�W�`��
	iparam1_exarms_->x_ = 7;
	iparam1_exarms_->y_ = 55;
	ImgManager::Draw(imgfile_gblue_, 0, iparam1_exarms_);
	iparam1_exarms_->x_ = 7;
	iparam1_exarms_->y_ = 79;
	ImgManager::Draw(imgfile_gblue_, 0, iparam1_exarms_);
	if (value_exarms_ == 200) {
		iparam1_exarms_->x_ = 7;
		iparam1_exarms_->y_ = 55;
		ImgManager::Draw(imgfile_gred_, 0, iparam1_exarms_);
		iparam1_exarms_->x_ = 7;
		iparam1_exarms_->y_ = 79;
		ImgManager::Draw(imgfile_gred_, 0, iparam1_exarms_);
		iparam3_exarms_->pos_x1_ = 7 + (int)(exarms_width * (value_exarms_ - 200));
		iparam3_exarms_->pos_y1_ = 103;
		iparam3_exarms_->pos_x2_ = 158;
		iparam3_exarms_->pos_y2_ = 175;
		ImgManager::Draw(imgfile_gblack_, 0, iparam3_exarms_);
		iparam1_exarms_->x_ = 7;
		iparam1_exarms_->y_ = 126;
		ImgManager::Draw(imgfile_gblack_, 0, iparam1_exarms_);
	} else if (0 <= value_exarms_ - 100) {
		iparam1_exarms_->x_ = 7;
		iparam1_exarms_->y_ = 55;
		ImgManager::Draw(imgfile_gred_, 0, iparam1_exarms_);
		iparam3_exarms_->pos_x1_ = 7 + (int)(exarms_width * (value_exarms_ - 100));
		iparam3_exarms_->pos_y1_ = 79;
		iparam3_exarms_->pos_x2_ = 158;
		iparam3_exarms_->pos_y2_ = 198;
		ImgManager::Draw(imgfile_gblack_, 0, iparam3_exarms_);
	} else if (0 < value_exarms_) {
		iparam3_exarms_->pos_x1_ = 7 + (int)(exarms_width * value_exarms_);
		iparam3_exarms_->pos_y1_ = 55;
		iparam3_exarms_->pos_x2_ = 158;
		iparam3_exarms_->pos_y2_ = 221;
		ImgManager::Draw(imgfile_gblack_, 0, iparam3_exarms_);
		iparam1_exarms_->x_ = 7;
		iparam1_exarms_->y_ = 79;
		ImgManager::Draw(imgfile_gblack_, 0, iparam1_exarms_);
	} else {
		iparam1_exarms_->x_ = 7;
		iparam1_exarms_->y_ = 55;
		ImgManager::Draw(imgfile_gblack_, 0, iparam1_exarms_);
		iparam1_exarms_->x_ = 7;
		iparam1_exarms_->y_ = 79;
		ImgManager::Draw(imgfile_gblack_, 0, iparam1_exarms_);
	}
}

/*!
@brief ALV�`��֐�
*/
void DesignUpdater::DrawAttackLV(void)
{
	int imgdiv;
	int imgx, imgy;
	long alv = (long)value_alv_;
	int keta = (int)log10(alv) + 1;

	imgx = 80;
	imgy = 114;
	if (alv == 0) {
		iparam1_alv_->x_ = imgx;
		iparam1_alv_->y_ = imgy;
		ImgManager::Draw(imgfile_rank_, 0, iparam1_alv_);
		return;
	}
	while(1 < keta) {
		imgdiv = (int)(alv / (long)pow(10.0, keta - 1));
		iparam1_alv_->x_ = imgx;
		iparam1_alv_->y_ = imgy;
		ImgManager::Draw(imgfile_rank_, imgdiv, iparam1_alv_);
		alv -= imgdiv * (long)pow(10.0, keta - 1);
		imgx += 23;
		keta--;
	}
	iparam1_alv_->x_ = imgx;
	iparam1_alv_->y_ = imgy;
	ImgManager::Draw(imgfile_rank_, alv, iparam1_alv_);
}



/**
@brief ExTime�`��֐�
@note
ExTime 1f = 0.4�x�ŕ`��B
**/
void DesignUpdater::DrawExTime(void)
{

	//if (extime_ == 0) {
	//	exarms_clock_angle_ = 0;
	//} else if (extime_ != 0 && exarms_clock_angle_ + 10 < extime_) {
	//	exarms_clock_angle_ += 10;
	//} else if (extime_ != 0 && extime_ <= exarms_clock_angle_ + 10) {
	//	exarms_clock_angle_ = extime_;
	//}
	//iparam1_clock_dial_->x_ = 5;
	//iparam1_clock_dial_->y_ = 430;
//	ImgManager::Draw(imgfile_clock1_, 0, iparam1_clock_dial_);
	//iparam4_clock_hands_->draw_angle_ = CalcRAD(exarms_clock_angle_ * 0.4);
	//iparam4_clock_hands_->pos_cx_ = 77;
	//iparam4_clock_hands_->pos_cy_ = 501;
//	ImgManager::Draw(imgfile_clock2_, 0, iparam4_clock_hands_);
//	ImgManager::Draw(imgfile_clock3_, 0, iparam1_clock_dial_);
}

/**
@brief Score�{���`��֐�
**/
void DesignUpdater::DrawClockScore(void)
{
	const double angle1 = 360 / 12;		// �X�R�A�{��1.0�̂Ƃ��̊p�x

	iparam1_clock_dial_->x_ = -16;
	iparam1_clock_dial_->y_ = 270;
	ImgManager::Draw(imgfile_clock_dial_, 0, iparam1_clock_dial_);
	iparam4_clock_hands_->draw_angle_ = CalcRAD(value_score_ratio_ * angle1);
	iparam4_clock_hands_->pos_cx_ = 77;
	iparam4_clock_hands_->pos_cy_ = 366;
	ImgManager::Draw(imgfile_clock_hands_, 0, iparam4_clock_hands_);
	ImgManager::Draw(imgfile_clock_pin_, 0, iparam4_clock_hands_);
}

/**
@brief Rank�`��֐�
**/
void DesignUpdater::DrawClockRank(void)
{
	const double angle1 = 360 / 12;		// �����N1.0�̂Ƃ��̊p�x

#ifdef __DEBUG__
	int color = GetColor(255, 255, 255);
	DebugPrint::SetData(10, 170, "rank = %3.1f", value_rank_);
#endif

	iparam1_clock_dial_->x_ = -16;
	iparam1_clock_dial_->y_ = 410;
	ImgManager::Draw(imgfile_clock_dial_, 0, iparam1_clock_dial_);
	iparam4_clock_hands_->draw_angle_ = CalcRAD(value_rank_ * angle1);
	iparam4_clock_hands_->pos_cx_ = 77;
	iparam4_clock_hands_->pos_cy_ = 506;
	ImgManager::Draw(imgfile_clock_hands_, 0, iparam4_clock_hands_);
	ImgManager::Draw(imgfile_clock_pin_, 0, iparam4_clock_hands_);
}

/**
@brief �E�B���h�E�`��֐�
**/
void DesignUpdater::DrawWindow(void)
{
	iparam1_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER2;
	iparam1_->x_ = 0;
	iparam1_->y_ = 0;
	iparam1_->flag_trans_ = true;
	ImgManager::Draw(imgfile_window_, 0, iparam1_);
}

/**
@brief �X�R�A�`��֐�
**/
void DesignUpdater::DrawScore(void)
{
	int imgdiv;
	int imgx, imgy;
	long score = value_score_;
	int keta = (int)log10(score) + 1;
	static ImgParam1 iparam1;

	iparam1.flag_trans_ = true;
	imgx = 616;
	imgy = 56;
	if (score == 0) {
		for (int i = 0; i < 8; i++) {
			iparam1_score_->x_ = imgx;
			iparam1_score_->y_ = imgy;
			ImgManager::Draw(imgfile_score_, 0, iparam1_score_);
			imgx += 22;
		}
		return;
	}
	for (int i = 8; i != keta; i--) {
			iparam1_score_->x_ = imgx;
			iparam1_score_->y_ = imgy;
			ImgManager::Draw(imgfile_score_, 0, iparam1_score_);
			imgx += 22;
	}
	while(1 < keta) {
		imgdiv = (int)(score / (long)pow(10.0, keta - 1));
		iparam1_score_->x_ = imgx;
		iparam1_score_->y_ = imgy;
		ImgManager::Draw(imgfile_score_, imgdiv, iparam1_score_);
		score -= imgdiv * (long)pow(10.0, keta - 1);
		imgx += 22;
		keta--;
	}
	iparam1_score_->x_ = imgx;
	iparam1_score_->y_ = imgy;
	ImgManager::Draw(imgfile_score_, score, iparam1_score_);

}

void DesignUpdater::DrawKey(void)
{
	iparam1_key_->x_ = 687;
	iparam1_key_->y_ = 335;
	ImgManager::Draw(imgfile_kblack_, 0, iparam1_key_);
	if (KeyManager::GetKeyFlagNow(eKEY::UP))
		ImgManager::Draw(imgfile_kred_, 0, iparam1_key_);
	iparam1_key_->x_ = 639;
	iparam1_key_->y_ = 383;
	ImgManager::Draw(imgfile_kblack_, 0, iparam1_key_);
	if (KeyManager::GetKeyFlagNow(eKEY::LEFT))
		ImgManager::Draw(imgfile_kred_, 0, iparam1_key_);
	iparam1_key_->x_ = 687;
	iparam1_key_->y_ = 431;
	ImgManager::Draw(imgfile_kblack_, 0, iparam1_key_);
	if (KeyManager::GetKeyFlagNow(eKEY::DOWN))
		ImgManager::Draw(imgfile_kred_, 0, iparam1_key_);
	iparam1_key_->x_ = 735;
	iparam1_key_->y_ = 383;
	ImgManager::Draw(imgfile_kblack_, 0, iparam1_key_);
	if (KeyManager::GetKeyFlagNow(eKEY::RIGHT))
		ImgManager::Draw(imgfile_kred_, 0, iparam1_key_);
	iparam1_key_->x_ = 639;
	iparam1_key_->y_ = 495;
	ImgManager::Draw(imgfile_kblack_, 0, iparam1_key_);
	if (KeyManager::GetKeyFlagNow(eKEY::ARMS))
		ImgManager::Draw(imgfile_kred_, 0, iparam1_key_);
	iparam1_key_->x_ = 687;
	iparam1_key_->y_ = 495;
	ImgManager::Draw(imgfile_kblack_, 0, iparam1_key_);
	if (KeyManager::GetKeyFlagNow(eKEY::SLOW))
		ImgManager::Draw(imgfile_kred_, 0, iparam1_key_);
	iparam1_key_->x_ = 735;
	iparam1_key_->y_ = 495;
	ImgManager::Draw(imgfile_kblack_, 0, iparam1_key_);
	if (KeyManager::GetKeyFlagNow(eKEY::EXARMS))
		ImgManager::Draw(imgfile_kred_, 0, iparam1_key_);
}




void DesignUpdater::DrawStar(void)
{
	iparam1_->group_type_ = eOBJECT::GROUP::DESIGN_LAYER3;
	iparam1_->flag_trans_ = true;
	iparam1_->x_ = 616;
	iparam1_->y_ = 128;
	for (int i = 0; i < value_star_; i++) {
		ImgManager::Draw(imgfile_star_, 0, iparam1_);
		iparam1_->x_ += 24;
	}
}

void DesignUpdater::DrawBossHealth(void)
{
	const double percent1 = 4.5;		// hp1% = 4.5dot

	if (!flag_draw_boss_health_)
		return;

	// �_���[�W�`��
	iparam1_boss_health_->x_ = DRAW_PANEL_MIN_X;
	iparam1_boss_health_->y_ = DRAW_PANEL_MIN_Y;
	ImgManager::Draw(imgfile_boss_health_black_, 0, iparam1_boss_health_);
	// �c�̗͕`��
	iparam1_boss_health_->x_ = (int)(DRAW_PANEL_MIN_X - (100 - value_boss_health_) * percent1);
	iparam1_boss_health_->y_ = DRAW_PANEL_MIN_Y;
	if (color_boss_health_ == "green") {
		ImgManager::Draw(imgfile_boss_health_green_, 0, iparam1_boss_health_);
	} else if (color_boss_health_ == "red") {
		ImgManager::Draw(imgfile_boss_health_red_, 0, iparam1_boss_health_);
	} else {
		ImgManager::Draw(imgfile_boss_health_black_, 0, iparam1_boss_health_);
	}
	// �g�`��
	iparam1_boss_frame_->x_ = DRAW_PANEL_MIN_X;
	iparam1_boss_frame_->y_ = DRAW_PANEL_MIN_Y;
	ImgManager::Draw(imgfile_boss_health_frame_, 0, iparam1_boss_frame_);
}



