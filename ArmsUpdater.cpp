#include "DxLib.h"
#include "ArmsUpdater.h"
#include "DesignManager.h"
#include "EffectManager.h"
#include "PosManager.h"
#include "ImgManager.h"
#include "DebugPrint.h"

#define __DEBUG__

using namespace std;
using namespace NH2;
using namespace NH3;
static int debug_shotnum = 0;

void ArmsUpdater::Run(void)
{
	list<ArmsToken>::iterator it;

	debug_shotnum = 0;
	RemoveTargetArms();
	RemoveUserArms();
//	Remove(eARMS::GROUP::USER_ARMS);
//	Remove(eARMS::GROUP::TARGET_ARMS);
	Calculate(eOBJECT::NUM::USER_ARMS);
	Calculate(eOBJECT::NUM::TARGET_ARMS_SMALL);
	Calculate(eOBJECT::NUM::TARGET_ARMS_LARGE);
	Draw(eOBJECT::NUM::USER_ARMS);
	Draw(eOBJECT::NUM::TARGET_ARMS_SMALL);
	Draw(eOBJECT::NUM::TARGET_ARMS_LARGE);

#ifdef __DEBUG__
	DebugPrint::SetData(615, 180, "shot_num_: %d", debug_shotnum);
#endif

}

/**
@brief ���W�v�Z�i�X�V�j�֐�
@param group �w��GROUP
@return �Ȃ�
@note
 �w�肵��GROUP�̍��W�����ׂčX�V����B
**/
void ArmsUpdater::Calculate(eOBJECT::GROUP group)
{
	list<ArmsToken>::iterator it;
	list<ArmsToken>::iterator it_delete;

	// �ҋ@�t���[�����̊m�F
	for (it = list_wait_[group].begin(); it != list_wait_[group].end(); ++it) {
		if (it->wait_frames_ == 0) {
			PosManager::SetRange(it->pparam_, it->pos_range_);
			it_delete = --it;
			list_wait_[group].splice(list_used_[group].begin(), list_wait_[group], ++it_delete);
		} else {
			it->wait_frames_--;
		}
	}
	// ���W���X�V����
	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		PosManager::MovePosA(it->pparam_, &it->plus_x_, &it->plus_y_);

#ifdef __DEBUG__
	debug_shotnum++;
#endif

	}
}



/*!
@brief �`��֐�
@param type �`�悷��ARMS�v�f�̎��
@return �Ȃ�
*/
void ArmsUpdater::Draw(eOBJECT::GROUP group)
{
	ImgParam4 iparam;
	list<ArmsToken>::iterator it;

	// Arms Token ���ʕ`��p�����[�^
	iparam.extend_rate_ = 1.0;
	iparam.flag_trans_ = true;
	iparam.flag_turn_ = false;
	iparam.group_type_ = group;
	// ArmsToken �`��
	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		it->img_angle_ += it->img_rotate_;
		iparam.draw_angle_ = it->img_angle_;
		PosManager::GetPosX(it->pparam_, &iparam.pos_cx_);
		PosManager::GetPosY(it->pparam_, &iparam.pos_cy_);
		ImgManager::Draw(it->img_id_, 0, &iparam);
	}
}

/**
@brief target arms �폜�֐�
@note
 ���E���z�����v�f�� unused_list �Ɉړ�������B
 �Փ˔��肪����Ƃ��� unused_list �Ɉړ�������B
**/
void ArmsUpdater::RemoveTargetArms()
{
	double hit;
	double x, y;
	list<ArmsToken>::iterator it, sit;
	const int POS_MIN_X = -64;
	const int POS_MIN_Y = -64;
	const int POS_MAX_X = 864;
	const int POS_MAX_Y = 664;


	for (it = list_used_[eOBJECT::NUM::TARGET_ARMS_SMALL].begin(); it != list_used_[eOBJECT::NUM::TARGET_ARMS_SMALL].end(); ++it) {
		PosManager::GetPosX(it->pparam_, &x);
		PosManager::GetPosY(it->pparam_, &y);
		hit = PosManager::GetHit(it->pparam_);
		if (x < POS_MIN_X || POS_MAX_X < x) {
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[eOBJECT::NUM::TARGET_ARMS_SMALL].splice(list_unused_.begin(), list_used_[eOBJECT::NUM::TARGET_ARMS_SMALL], ++sit);
		} else if (y < POS_MIN_Y || POS_MAX_Y < y) {
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[eOBJECT::NUM::TARGET_ARMS_SMALL].splice(list_unused_.begin(), list_used_[eOBJECT::NUM::TARGET_ARMS_SMALL], ++sit);
		} else if (hit != 0) {
			it->eparam_->x_ = (int)x;
			it->eparam_->y_ = (int)y;
			if (it->hit_effect_)
				EffectManager::Create(it->eparam_);
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[eOBJECT::NUM::TARGET_ARMS_SMALL].splice(list_unused_.begin(), list_used_[eOBJECT::NUM::TARGET_ARMS_SMALL], ++sit);
		}
	}
	for (it = list_used_[eOBJECT::NUM::TARGET_ARMS_LARGE].begin(); it != list_used_[eOBJECT::NUM::TARGET_ARMS_LARGE].end(); ++it) {
		PosManager::GetPosX(it->pparam_, &x);
		PosManager::GetPosY(it->pparam_, &y);
		hit = PosManager::GetHit(it->pparam_);
		if (x < POS_MIN_X || POS_MAX_X < x) {
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[eOBJECT::NUM::TARGET_ARMS_LARGE].splice(list_unused_.begin(), list_used_[eOBJECT::NUM::TARGET_ARMS_LARGE], ++sit);
		} else if (y < POS_MIN_Y || POS_MAX_Y < y) {
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[eOBJECT::NUM::TARGET_ARMS_LARGE].splice(list_unused_.begin(), list_used_[eOBJECT::NUM::TARGET_ARMS_LARGE], ++sit);
		} else if (hit != 0) {
			it->eparam_->x_ = (int)x;
			it->eparam_->y_ = (int)y;
			if (it->hit_effect_)
				EffectManager::Create(it->eparam_);
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[eOBJECT::NUM::TARGET_ARMS_LARGE].splice(list_unused_.begin(), list_used_[eOBJECT::NUM::TARGET_ARMS_LARGE], ++sit);
		}
	}

}

/**
@brief user arms �폜�֐�
@note
 ���E���z�����v�f�� unused_list �Ɉړ�������B
 �Փ˔��肪����Ƃ��� unused_list �Ɉړ�������B
**/
void ArmsUpdater::RemoveUserArms()
{
	double hit;
	double x, y;
	list<ArmsToken>::iterator it, sit;
	const int POS_MIN_X = -64;
	const int POS_MIN_Y = -64;
	const int POS_MAX_X = 864;
	const int POS_MAX_Y = 664;


	for (it = list_used_[eOBJECT::NUM::USER_ARMS].begin(); it != list_used_[eOBJECT::NUM::USER_ARMS].end(); ++it) {
		PosManager::GetPosX(it->pparam_, &x);
		PosManager::GetPosY(it->pparam_, &y);
		hit = PosManager::GetHit(it->pparam_);
		if (x < POS_MIN_X || POS_MAX_X < x) {
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[eOBJECT::NUM::USER_ARMS].splice(list_unused_.begin(), list_used_[eOBJECT::NUM::USER_ARMS], ++sit);
		} else if (y < POS_MIN_Y || POS_MAX_Y < y) {
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[eOBJECT::NUM::USER_ARMS].splice(list_unused_.begin(), list_used_[eOBJECT::NUM::USER_ARMS], ++sit);
		} else if (hit != 0) {
			it->eparam_->x_ = (int)x;
			it->eparam_->y_ = (int)y;
			if (it->hit_effect_)
				EffectManager::Create(it->eparam_);
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[eOBJECT::NUM::USER_ARMS].splice(list_unused_.begin(), list_used_[eOBJECT::NUM::USER_ARMS], ++sit);
		}
	}
}


/**
@brief �폜�֐�
@param group �w��GROUP
@note
 �����Ŏw�肵��GROUP��ArmsToken�ɑ΂���
 �폜���肨��э폜�����������Ȃ��B
 ���E���z�����v�f�� unused_list �Ɉړ�������B
 �Փ˔��肪����Ƃ��� unused_list �Ɉړ�������B
**/
void ArmsUpdater::Remove(eOBJECT::GROUP group)
{
	double hit;
	double x, y;
	list<ArmsToken>::iterator it, sit;
	const int POS_MIN_X = -64;
	const int POS_MIN_Y = -64;
	const int POS_MAX_X = 864;
	const int POS_MAX_Y = 664;


	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		PosManager::GetPosX(it->pparam_, &x);
		PosManager::GetPosY(it->pparam_, &y);
		hit = PosManager::GetHit(it->pparam_);
		if (x < POS_MIN_X || POS_MAX_X < x) {
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[group].splice(list_unused_.begin(), list_used_[group], ++sit);
		} else if (y < POS_MIN_Y || POS_MAX_Y < y) {
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[group].splice(list_unused_.begin(), list_used_[group], ++sit);
		} else if (hit != 0) {
			PosManager::Delete(it->pparam_);
			sit = --it;
			list_used_[group].splice(list_unused_.begin(), list_used_[group], ++sit);
		}
	}

}

