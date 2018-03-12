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
@brief 座標計算（更新）関数
@param group 指定GROUP
@return なし
@note
 指定したGROUPの座標をすべて更新する。
**/
void ArmsUpdater::Calculate(eOBJECT::GROUP group)
{
	list<ArmsToken>::iterator it;
	list<ArmsToken>::iterator it_delete;

	// 待機フレーム数の確認
	for (it = list_wait_[group].begin(); it != list_wait_[group].end(); ++it) {
		if (it->wait_frames_ == 0) {
			PosManager::SetRange(it->pparam_, it->pos_range_);
			it_delete = --it;
			list_wait_[group].splice(list_used_[group].begin(), list_wait_[group], ++it_delete);
		} else {
			it->wait_frames_--;
		}
	}
	// 座標を更新する
	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		PosManager::MovePosA(it->pparam_, &it->plus_x_, &it->plus_y_);

#ifdef __DEBUG__
	debug_shotnum++;
#endif

	}
}



/*!
@brief 描画関数
@param type 描画するARMS要素の種類
@return なし
*/
void ArmsUpdater::Draw(eOBJECT::GROUP group)
{
	ImgParam4 iparam;
	list<ArmsToken>::iterator it;

	// Arms Token 共通描画パラメータ
	iparam.extend_rate_ = 1.0;
	iparam.flag_trans_ = true;
	iparam.flag_turn_ = false;
	iparam.group_type_ = group;
	// ArmsToken 描画
	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		it->img_angle_ += it->img_rotate_;
		iparam.draw_angle_ = it->img_angle_;
		PosManager::GetPosX(it->pparam_, &iparam.pos_cx_);
		PosManager::GetPosY(it->pparam_, &iparam.pos_cy_);
		ImgManager::Draw(it->img_id_, 0, &iparam);
	}
}

/**
@brief target arms 削除関数
@note
 境界を越えた要素は unused_list に移動させる。
 衝突判定があるときは unused_list に移動させる。
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
@brief user arms 削除関数
@note
 境界を越えた要素は unused_list に移動させる。
 衝突判定があるときは unused_list に移動させる。
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
@brief 削除関数
@param group 指定GROUP
@note
 引数で指定したGROUPのArmsTokenに対して
 削除判定および削除処理をおこなう。
 境界を越えた要素は unused_list に移動させる。
 衝突判定があるときは unused_list に移動させる。
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

