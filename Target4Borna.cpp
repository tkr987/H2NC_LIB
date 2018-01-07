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
#include "Target4Borna.h"
#include "DebugPrint.h"
//#define __DEBUG__

using namespace NH2;
using namespace NH2T;

Target4Borna::Target4Borna(double start_posx, double start_posy, int lv)
{

	// �^�[�Q�b�g�A�p�����[�^
	main_ = new Target(start_posx, start_posy, 16);
	cube_[0] = new Target(start_posx, start_posy - 100, 16);
	cube_[1] = new Target(start_posx, start_posy -  50, 16);
	cube_[2] = new Target(start_posx +  50, start_posy, 16);
	cube_[3] = new Target(start_posx + 100, start_posy, 16);
	cube_[4] = new Target(start_posx, start_posy +  50, 16);
	cube_[5] = new Target(start_posx, start_posy + 100, 16);
	cube_[6] = new Target(start_posx -  50, start_posy, 16);
	cube_[7] = new Target(start_posx - 100, start_posy, 16);
	aparam_cube_ = new ArmsParam1;
	aparam_main_ = new ArmsParam1;
	eparam_death_ = new EffectParam1b;
	// �ϐ� ������
	action_ = 10;
	frames_ = -1;
	health_ = 300;
	lv_ = lv;
	// �摜�t�@�C��
	imgdiv_cube_ = 0;
	imgdiv_main_ = 0;
	imgfile_arms_cube_ = IMG_LOAD_ARMS_RED20T;
	imgfile_arms_main_ = IMG_LOAD_ARMS_RED20T;
	imgfile_death_ = IMG_LOAD_EFFECT_DEATH140;
	imgfile_cube_ = IMG_LOAD_TARGET_CUBE_BLUE140;
	imgfile_cube_lock_ = IMG_LOAD_TARGET_LOCK_CUBE;
	imgfile_main_ = IMG_LOAD_TARGET_MAIN_STAGE4_BORNA;
	imgfile_main_lock_ = IMG_LOAD_TARGET_LOCK_STAGE4_BORNA;
	// �T�E���h�t�@�C��
	soundfile_death_ = SOUND_LOAD_TARGET_DEATH3;
	soundfile_lock_ = SOUND_LOAD_TARGET_LOCK;
	// �����G�t�F�N�g�ݒ�
	eparam_death_->blend_alpha_ = 255;
	eparam_death_->blend_mode_ = DX_BLENDMODE_ADD;
	eparam_death_->extend_rate_ = 1.0;
	eparam_death_->group_ = eOBJECT::GROUP::TARGET_EFFECT;
	eparam_death_->img_divmax_ = 64;
	eparam_death_->img_divmin_ = 0;
	eparam_death_->img_id_ = imgfile_death_;
	eparam_death_->img_interval_ = 1;
	// Arms Cube �Œ�p�����[�^
	aparam_cube_->img_id_ = imgfile_arms_cube_;
	aparam_cube_->shot_pow_ = 1;
	aparam_cube_->shot_range_ = ARMS_PARAM_RANGE_RED20T;
	aparam_cube_->shot_speed_ = 6.0;
	// Arms Main �Œ�p�����[�^
	aparam_main_->img_id_ = imgfile_arms_main_;
	aparam_main_->shot_pow_ = 1;
	aparam_main_->shot_range_ = ARMS_PARAM_RANGE_RED20T;
	aparam_main_->shot_speed_ = 6.0;
}


Target4Borna::~Target4Borna() {
	delete main_;
	delete aparam_cube_;
	delete aparam_main_;
	delete eparam_death_;
}


void Target4Borna::Run(void)
{

	switch (action_) {
	case 10:
		srand(16);
		main_->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		for (int i = 0; i < 8; i++)
			cube_[i]->SetGroup(eOBJECT::GROUP::TARGET_RUN_FLY);
		action_ = 11;
		frames_ = -1;
		break;
	case 11:
		Act11_ShotHard();
		Collision1();
		Draw();
		if (health_ < 0) {
			action_ = 20;
			frames_ = -1;
		}
		if (frames_ == 3000) {
			action_ = 21;
			frames_ = -1;
		}
		break;
	case 20:
		ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_LARGE);
		ArmsManager::DeleteAll(eOBJECT::GROUP::TARGET_ARMS_SMALL);
		ImgManager::SwingY(20, 3);
		Delete(1.0, true, true);
		action_ = 22;
		frames_ = -1;
		break;
	case 21:
		Delete(0.0, false, false);
		action_ = 22;
		frames_ = -1;
		break;
	case 22:
		// �I��
		break;
	}

	frames_++;
}


void Target4Borna::Act11_ShotHard(void)
{
	int rank_wait;			// �����N�ˑ��̒e��

	if (lv_ != LV_HARD)
		return;
	if (frames_ % 40 != 0)
		return;

	DesignManager::GetRank(&rank_wait, 0.3);
	for (int i = 0; i < 8; i++) {
		if (!cube_[i]->InsidePanel())
			continue;
		aparam_cube_->shot_angle_ = main_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
		cube_[i]->GetPos(&aparam_cube_->shot_x_, &aparam_cube_->shot_y_);
		for (int wait = 0; wait < 6 + rank_wait; wait++) {
			aparam_cube_->shot_wait_ = wait * 3;
			ArmsManager::TargetShotSmall(aparam_cube_);
		}
	}
	if (!main_->InsidePanel())
		return;
	aparam_main_->shot_angle_ = main_->GetAtan(eOBJECT::GROUP::USER, POS_NAME_USER_MAIN, 0);
	main_->GetPos(&aparam_main_->shot_x_, &aparam_main_->shot_y_);
	for (int wait = 0; wait < 6 + rank_wait; wait++) {
		aparam_main_->shot_wait_ = wait * 3;
		ArmsManager::TargetShotSmall(aparam_main_);
	}
}


void Target4Borna::Collision1(void)
{
	double damage = 0;			// �P�t���[��������̃_���[�W
	const int extension = 0;	// ��������̈�̊g��
	const int interval = 50;	// �C���^�[�o������

	damage += main_->Collision(extension);
	main_->CollisionImg(imgfile_main_lock_, 0, interval);
	main_->CollisionSound(soundfile_lock_, interval);
	DesignManager::AddScore(damage);
	for (int i = 0; i < 8; i++) {
		damage += cube_[i]->Collision(extension);
		cube_[i]->CollisionImg(imgfile_cube_lock_, 0, interval);
		cube_[i]->CollisionSound(soundfile_lock_, interval);
		DesignManager::AddScore(damage);
	}
	health_ -= damage;
}


void Target4Borna::Delete(double scale, bool effect, bool sound)
{
	double add_alv		= 0.1 * scale;				// ���ZALV
	double add_exarms	= 2.0 * scale;				// ���ZExArms
	double add_rank		= 0.01 * scale;				// ���Z�����N
	long   add_score	= (long)(1000 * scale);		// ���Z�X�R�A

	// �G�t�F�N�g�ǉ�
	if (effect) {
		main_->GetPos(&eparam_death_->x_, &eparam_death_->y_);
		EffectManager::Create(eparam_death_);
		for (int i = 0; i < 8; i++) {
			cube_[i]->GetPos(&eparam_death_->x_, &eparam_death_->y_);
			EffectManager::Create(eparam_death_);
		}
	}

	// �T�E���h�ǉ�
	if (sound)
		SoundManager::Play(soundfile_death_, DX_PLAYTYPE_BACK);

	// �폜����
	main_->DeleteData(add_alv, add_exarms, add_rank, add_score);
	for (int i = 0; i < 8; i++)
		cube_[i]->DeleteData(add_alv, add_exarms, add_rank, add_score);
}


void Target4Borna::Draw(void)
{
	const int divmax_cube = 5;
	const int divmax_main = 3;

	if (FpsManager::GetInterval(4) == 0)
		imgdiv_cube_ = ++imgdiv_cube_ % divmax_cube;
	if (FpsManager::GetInterval(20) == 0)
		imgdiv_main_ = ++imgdiv_main_ % divmax_main;

	for (int i = 0; i < 8; i++)
		cube_[i]->Draw(imgfile_cube_, imgdiv_cube_, 0.4, 0);
	main_->Draw(imgfile_main_, imgdiv_main_, 1.5, 0);
}



