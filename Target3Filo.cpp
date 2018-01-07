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
#include "Target3Filo.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target3Filo::Target3Filo(double start_posx, double start_posy, int lv)
{
	// �ϐ� ������
	action_ = 0;
	count_frames_ = 0;
	health_ = 100;
	lv_ = lv;
	delete_flag_ = false;
	main_ = new Target(start_posx, start_posy, 15);
	aparam_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// �摜�t�@�C��
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
//	imgdiv_main_shadow_ = 0;
//	imgfile_arms_cube_ = ImgManager::LoadImg("data/10_img_arms/ArmsBlue20.png");
	imgfile_arms_main_ = ImgManager::LoadImg("data/img_target/Arms1Red.png");
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH120;
//	imgfile_cube_ = ImgManager::LoadImg(IMG_TARGET_CUBE140_NUMX, IMG_TARGET_CUBE140_NUMY, IMG_TARGET_CUBE140_SIZEX, IMG_TARGET_CUBE140_SIZEY, "data/img_target/CubeOrange140.png");
//	imgfile_cube_lock_ = ImgManager::LoadImg("data/img_target/LockCube.png");
	imgfile_main_ = ImgManager::LoadImg(4, 1, 32, 32, "data/img_target/MainFilo.png");
	imgfile_main_lock_ = ImgManager::LoadImg("data/img_target/LockFilo.png");
	// �T�E���h�t�@�C��
	soundfile_bomb_ = SoundManager::Load("data/sound/target_bomb2.wav");
	soundfile_lock_ = SoundManager::Load("data/sound/target_lock.wav");
	// �����G�t�F�N�g�ݒ�
	eparam_death_->blend_alpha_ = 255;
	eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::GROUP::TARGET_EFFECT;
	eparam_death_->img_divmax_ = 32;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 1;
	// ARMS CUBE �Œ�p�����[�^
	aparam_->hit_effect_ = false;
	aparam_->img_id_ = imgfile_arms_main_;
	aparam_->img_rotate_ = false;
	aparam_->shot_pow_ = 1;
	aparam_->shot_range_ = 2.0;
	aparam_->shot_wait_ = 0;
}


Target3Filo::~Target3Filo() {
	delete main_;
	delete aparam_;
}


void Target3Filo::Run(void)
{

	if (delete_flag_)
		return;

	// *****************
	//  ���ʃA�N�V����
	// *****************
	Collision();
	Draw();
	if (2000 < count_frames_) {
		action_ = 100;
	} else if (health_ < 0) {
		action_ = 101;
	}

	// *****************
	//  �A�N�V��������
	// *****************
	switch (action_) {
	case 0:
		AttackNormal();
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


void Target3Filo::Attack1Hard(void)
{
	int rank_freq;			// �����N�ˑ��̍U���p�x
	double rank_speed;		// �����N�ˑ��̍U�����x

	if (lv_ != LV_HARD)
		return;

	// �U���p�x�X�V
	DesignManager::GetRank(&rank_freq);
	if (count_frames_ % (30 - rank_freq) != 0)
		return;

	// �U�����x�X�V
	DesignManager::GetRank(&rank_speed);
	aparam_->shot_speed_ = 3.0 + rank_speed / 3;

	// ************
	//  �U������
	// ************
	if (main_->InsidePanel(-32)) {
		main_->GetPos(&aparam_->shot_x_, &aparam_->shot_y_);
		for (int wave = -2; wave < 3; wave++) {
			aparam_->shot_angle_ = main_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
			aparam_->shot_angle_ += wave * CalcRAD(10);
			ArmsManager::TargetShotSmall(aparam_);
		}
	}
}


void Target3Filo::AttackNormal(void)
{

}


void Target3Filo::Collision(void)
{
	double damage = 0;			// �P�t���[��������̃_���[�W
	const int extension = 0;	// ��������̈�̊g��
	const int interval = 50;	// �C���^�[�o������

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	health_ -= damage;
}


void Target3Filo::Delete(double scale, bool effect, bool sound)
{
	double add_alv		= 0.1 * scale;				// ���ZALV
	double add_exarms	= 2.0 * scale;				// ���ZExArms
	double add_rank		= 0.01 * scale;				// ���Z�����N
	long   add_score	= (long)(1000 * scale);		// ���Z�X�R�A

	// �G�t�F�N�g�ǉ�
	if (effect) {
		main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
	}

	// �T�E���h�ǉ�
	if (sound)
		SoundManager::Play(soundfile_bomb_, DX_PLAYTYPE_BACK);

	// �폜����
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Target3Filo::Draw(void)
{
	const int divmax_main = 4;

	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % divmax_main;

	main_->Draw(imgfile_main_, imgdiv_main_, 1.4, 0);
}


void Target3Filo::Move1(void)
{

}

