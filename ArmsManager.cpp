#include "DxLib.h"
#include "ArmsManager.h"
#include "DebugPrint.h"
#include "DesignManager.h"
#include "EffectManager.h"
#include "ImgManager.h"
#include "PosManager.h"

using namespace std;
using namespace NH2;
int ArmsManager::shot_num_;
int ArmsManager::imgfile_point_;
std::list<ArmsToken> ArmsManager::list_unused_;
std::list<ArmsToken> ArmsManager::list_wait_[eOBJECT::GROUP::sizeof_enum];
std::list<ArmsToken> ArmsManager::list_used_[eOBJECT::GROUP::sizeof_enum];

void ArmsManager::Clear(void)
{
	ArmsToken atemp;
	list<ArmsToken>::iterator it;

	// arms token 生成
	if(list_unused_.empty()) {
		for (int n  = 0; n < ARMS_MAXSIZE; n++)
			list_unused_.push_front(atemp);
		for (it = list_unused_.begin(); it != list_unused_.end(); ++it) {
			it->eparam_ = new EffectParam1;
			it->pparam_ = new PosParam1;
		}
		shot_num_ = ARMS_MAXSIZE;
	}
	// point 画像ロード
	imgfile_point_ = ImgManager::LoadImg(1, 9, 66, 24, "data/img_effect/Point.png");
}


void ArmsManager::End(void)
{
	list<ArmsToken>::iterator it;

	for (it = list_unused_.begin(); it != list_unused_.end(); ++it) {
		delete it->eparam_;
		delete it->pparam_;
	}
	list_unused_.clear();

	for (int group = eOBJECT::GROUP::enum_zero; group < eOBJECT::GROUP::sizeof_enum; group++) {
		for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
			delete it->eparam_;
			delete it->pparam_;
		}
		for (it = list_wait_[group].begin(); it != list_wait_[group].end(); ++it) {
			delete it->eparam_;
			delete it->pparam_;
		}
		list_used_[group].clear();
		list_wait_[group].clear();
	}
}



/**
@brief user 弾生成関数
@param param パラメータ指定
@retval  1 成功
@retval -1 失敗
@note
 弾生成数が限界に到達したときは何もしない
**/
int ArmsManager::UserShot(ArmsParam1* param)
{
	list<ArmsToken>::iterator it;

	// 生成数が限界に達しているか判定
//	if (list_unused_.empty())
//		return -1;
	// **********************************************************
	//  なぜか上記プログラムだと判定できないので下記で代用 ...
	// **********************************************************
	if (list_unused_.begin() == list_unused_.end())
		return -1;

	// arms token 専用パラメータ
	it = list_unused_.begin();
	it->img_angle_ = param->img_angle_;
	it->img_id_ = param->img_id_;
	it->img_rotate_ = param->img_rotate_;
	it->plus_x_ = cos(param->shot_angle_) * param->shot_speed_;
	it->plus_y_ = sin(param->shot_angle_) * param->shot_speed_;
	it->wait_frames_ = param->shot_wait_;

	// pos パラメータ
	it->pparam_->SetPow(param->shot_pow_);
	it->pparam_->SetRange(param->shot_range_);
	it->pparam_->SetStartX(param->shot_x_);
	it->pparam_->SetStartY(param->shot_y_);
	if (!PosManager::Generate(eOBJECT::GROUP::USER_ARMS, it->pparam_))
		return -1;

	// effect パラメータ
	if (param->hit_effect_) {
		it->hit_effect_ = true;
		it->eparam_->extend_rate_ = param->hit_effect_img_extend_rate_;
		it->eparam_->group_ = eOBJECT::USER_ARMS_EFFECT;
		it->eparam_->img_divmax_ = param->hit_effect_img_divmax_;
		it->eparam_->img_divmin_ = param->hit_effect_img_divmin_;
		it->eparam_->img_id_ = param->hit_effect_img_id_;
		it->eparam_->img_interval_ = param->hit_effect_img_interval_;
	} else {
		it->hit_effect_ = false;
	}
	
	list_unused_.splice(list_wait_[eOBJECT::GROUP::USER_ARMS].begin(), list_unused_, it);
	return 0;
}


/**
@brief target 弾生成関数
@param param パラメータ指定
@retval 1 成功
@retval -1 失敗
@note
 弾生成数が限界に到達したときは何もしない。
**/
int ArmsManager::TargetShotSmall(ArmsParam1* param)
{
	list<ArmsToken>::iterator it;

	// 生成数が限界に達しているか判定
//	if (list_unused_.empty())
//		return -1;
	// **********************************************************
	//  なぜか上記プログラムだと判定できないので下記で代用 ...
	// **********************************************************
	if (list_unused_.begin() == list_unused_.end())
		return -1;


	// arms token 専用パラメータ
	it = list_unused_.begin();
	it->img_angle_ = param->img_angle_;
	it->img_id_ = param->img_id_;
	it->img_rotate_ = param->img_rotate_;
	it->plus_x_ = cos(param->shot_angle_) * param->shot_speed_;
	it->plus_y_ = sin(param->shot_angle_) * param->shot_speed_;
	it->pos_range_ = param->shot_range_;
	it->wait_frames_ = param->shot_wait_;

	// pos パラメータ
	it->pparam_->SetPow(param->shot_pow_);
	it->pparam_->SetRange(0);
	it->pparam_->SetStartX(param->shot_x_);
	it->pparam_->SetStartY(param->shot_y_);
	if (!PosManager::Generate(eOBJECT::GROUP::TARGET_ARMS_SMALL, it->pparam_))
		return -1;

	// effect パラメータ
	if (param->hit_effect_) {
		it->eparam_->group_ = eOBJECT::TARGET_ARMS_EFFECT;
		it->eparam_->img_divmax_ = param->hit_effect_img_divmax_;
		it->eparam_->img_divmin_ = param->hit_effect_img_divmin_;
		it->eparam_->extend_rate_ = param->hit_effect_img_extend_rate_;
		it->eparam_->img_id_ = param->hit_effect_img_id_;
		it->eparam_->img_interval_ = param->hit_effect_img_interval_;
	} else {
		it->hit_effect_ = false;
	}

	list_unused_.splice(list_wait_[eOBJECT::GROUP::TARGET_ARMS_SMALL].begin(), list_unused_, it);
	return 0;
}

/**
@brief target 弾生成関数
@param param パラメータ指定
@retval 1 成功
@retval -1 失敗
@note
 弾生成数が限界に到達したときは何もしない。
**/
int ArmsManager::TargetShotLarge(ArmsParam1* param)
{
	list<ArmsToken>::iterator it;

	// 生成数が限界に達しているか判定
//	if (list_unused_.empty())
//		return -1;
	// **********************************************************
	//  なぜか上記プログラムだと判定できないので下記で代用 ...
	// **********************************************************
	if (list_unused_.begin() == list_unused_.end())
		return -1;


	// arms token 専用パラメータ
	it = list_unused_.begin();
	it->img_angle_ = param->img_angle_;
	it->img_id_ = param->img_id_;
	it->img_rotate_ = param->img_rotate_;
	it->plus_x_ = cos(param->shot_angle_) * param->shot_speed_;
	it->plus_y_ = sin(param->shot_angle_) * param->shot_speed_;
	it->pos_range_ = param->shot_range_;
	it->wait_frames_ = param->shot_wait_;

	// pos パラメータ
	it->pparam_->SetPow(param->shot_pow_);
	it->pparam_->SetRange(0);
	it->pparam_->SetStartX(param->shot_x_);
	it->pparam_->SetStartY(param->shot_y_);
	if (!PosManager::Generate(eOBJECT::GROUP::TARGET_ARMS_LARGE, it->pparam_))
		return -1;

	// effect パラメータ
	if (param->hit_effect_) {
		it->eparam_->group_ = eOBJECT::TARGET_ARMS_EFFECT;
		it->eparam_->img_divmax_ = param->hit_effect_img_divmax_;
		it->eparam_->img_divmin_ = param->hit_effect_img_divmin_;
		it->eparam_->extend_rate_ = param->hit_effect_img_extend_rate_;
		it->eparam_->img_id_ = param->hit_effect_img_id_;
		it->eparam_->img_interval_ = param->hit_effect_img_interval_;
	} else {
		it->hit_effect_ = false;
	}

	list_unused_.splice(list_wait_[eOBJECT::GROUP::TARGET_ARMS_LARGE].begin(), list_unused_, it);
	return 0;
}


/**
@brief 弾を全て削除する関数
@param group 削除するグループ
@return なし
@note
 group に TARGET_ARMS を指定したときは point も描画する。
**/
void ArmsManager::DeleteAll(eOBJECT::GROUP group)
{
	int imgfile_div = 0;			// 画像分割番号
	EffectParam1 eparam1;
	list<ArmsToken>::iterator it, sit;

	// target arms の座標に point を描する
	if (group == eOBJECT::GROUP::TARGET_ARMS_SMALL || group == eOBJECT::GROUP::TARGET_ARMS_LARGE) {
		if (8 < (list_used_[group].size() / 200)) {
			imgfile_div = 8;
		} else {
			imgfile_div = ((int)list_used_[group].size() / 200);
		}
		eparam1.extend_rate_ = 1.0;
		eparam1.group_ = eOBJECT::GROUP::TARGET_ARMS_EFFECT;
		eparam1.img_divmax_ = imgfile_div;
		eparam1.img_divmin_ = imgfile_div;
		eparam1.img_id_ = imgfile_point_;
		eparam1.img_interval_ = 50;
		for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
			PosManager::GetPosX(it->pparam_, &eparam1.x_);
			PosManager::GetPosY(it->pparam_, &eparam1.y_);
			EffectManager::Create(&eparam1);
		}
	}


	// ARMSオブジェクト全削除
	//while (!list_used_[group].empty()) {
	//	it = list_used_[group].begin();
	//	list_used_[group].splice(list_unused_.begin(), list_used_[group], it);
	//}
	// *******************************************************
	//  上記コードが動作しないため，下記コードで代用する...
	// *******************************************************
	while (list_used_[group].begin() != list_used_[group].end())
		list_used_[group].splice(list_unused_.begin(), list_used_[group], list_used_[group].begin());
	while (list_wait_[group].begin() != list_wait_[group].end())
		list_wait_[group].splice(list_unused_.begin(), list_wait_[group], list_wait_[group].begin());

	// 対応するPOSオブジェクト全削除
	PosManager::Delete(group);

	//DesignManager::AddClockRank(point);
}

