#include "Device.h"

using namespace H2NLIB;

Device::Device()
{

}


Device::~Device()
{

}

/**
@brief user �e�����֐�
@param param �p�����[�^�w��
@retval  1 ����
@retval -1 ���s
@note
 �e�����������E�ɓ��B�����Ƃ��͉������Ȃ�
**/
int Device::UserAttack(DevicePropertyX* dpx)
{

	//������

//	list<ShotToken>::iterator it;
//
//	// �����������E�ɒB���Ă��邩����
////	if (list_unused_.empty())
////		return -1;
//	// **********************************************************
//	//  �Ȃ�����L�v���O�������Ɣ���ł��Ȃ��̂ŉ��L�ő�p ...
//	// **********************************************************
//	if (list_unused_.begin() == list_unused_.end())
//		return -1;
//
//	// shot token ��p�p�����[�^
//	it = list_unused_.begin();
//	it->img_angle_ = dpx->img_angle_;
//	it->img_id_ = dpx->img_id_;
//	it->img_rotate_ = dpx->img_rotate_;
//	it->plus_x_ = cos(dpx->shot_angle_) * dpx->shot_speed_;
//	it->plus_y_ = sin(dpx->shot_angle_) * dpx->shot_speed_;
//	it->wait_frames_ = dpx->shot_wait_;
//
//	// pos �p�����[�^
//	it->pparam_->SetPow(dpx->shot_pow_);
//	it->pparam_->SetRange(dpx->shot_range_);
//	it->pparam_->SetStartX(dpx->shot_x_);
//	it->pparam_->SetStartY(dpx->shot_y_);
//	if (!PosManager::Generate(eOBJECT::GROUP::USER_ARMS, it->pparam_))
//		return -1;
//
//	// effect �p�����[�^
//	if (dpx->hit_effect_) {
//		it->hit_effect_ = true;
//		it->eparam_->extend_rate_ = dpx->hit_effect_img_extend_rate_;
//		it->eparam_->group_ = eOBJECT::USER_ARMS_EFFECT;
//		it->eparam_->img_divmax_ = dpx->hit_effect_img_divmax_;
//		it->eparam_->img_divmin_ = dpx->hit_effect_img_divmin_;
//		it->eparam_->img_id_ = dpx->hit_effect_img_id_;
//		it->eparam_->img_interval_ = dpx->hit_effect_img_interval_;
//	} else {
//		it->hit_effect_ = false;
//	}
//	
//	list_unused_.splice(list_wait_[eOBJECT::GROUP::USER_ARMS].begin(), list_unused_, it);
//	return 0;
}

void Device::Run(void)
{


}