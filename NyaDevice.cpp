#include "Device.h"

using namespace H2NLIB;

Device::Device()
{

}


Device::~Device()
{

}

/**
@brief user 弾生成関数
@param param パラメータ指定
@retval  1 成功
@retval -1 失敗
@note
 弾生成数が限界に到達したときは何もしない
**/
int Device::UserAttack(DevicePropertyX* dpx)
{

	//未完成

//	list<ShotToken>::iterator it;
//
//	// 生成数が限界に達しているか判定
////	if (list_unused_.empty())
////		return -1;
//	// **********************************************************
//	//  なぜか上記プログラムだと判定できないので下記で代用 ...
//	// **********************************************************
//	if (list_unused_.begin() == list_unused_.end())
//		return -1;
//
//	// shot token 専用パラメータ
//	it = list_unused_.begin();
//	it->img_angle_ = dpx->img_angle_;
//	it->img_id_ = dpx->img_id_;
//	it->img_rotate_ = dpx->img_rotate_;
//	it->plus_x_ = cos(dpx->shot_angle_) * dpx->shot_speed_;
//	it->plus_y_ = sin(dpx->shot_angle_) * dpx->shot_speed_;
//	it->wait_frames_ = dpx->shot_wait_;
//
//	// pos パラメータ
//	it->pparam_->SetPow(dpx->shot_pow_);
//	it->pparam_->SetRange(dpx->shot_range_);
//	it->pparam_->SetStartX(dpx->shot_x_);
//	it->pparam_->SetStartY(dpx->shot_y_);
//	if (!PosManager::Generate(eOBJECT::GROUP::USER_ARMS, it->pparam_))
//		return -1;
//
//	// effect パラメータ
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