#include "DxLib.h"
#include "DefineNH.h"
#include "DesignManager.h"
#include "FpsManager.h"
#include "ImgManager.h"
#include "PosManager.h"
#include "SoundManager.h"
#include "Target.h"

using namespace NH2;
using namespace NH2T;

Target::Target(double x, double y, double range)
{
	collision_interval_img_ = -1;
	collision_interval_sound_ = -1;
	iparam_ = new ImgParam4;
	iparam_collision_ = new ImgParam4;
	pparam_ = new PosParam1;
	// 描画固定パラメータ
	iparam_->flag_trans_ = true;
	iparam_->flag_turn_ = false;
	iparam_->group_type_ = eOBJECT::GROUP::TARGET_READY;
	// 描画固定パラメータ
	iparam_collision_->draw_angle_ = 0;
	iparam_collision_->extend_rate_ = 1.0;
	iparam_collision_->flag_trans_ = true;
	iparam_collision_->flag_turn_ = false;
	iparam_collision_->group_type_ = eOBJECT::GROUP::TARGET_EFFECT;
	// POSパラメータ＆オブジェクト生成
	pparam_->SetPow(1);
	pparam_->SetRange(range);
	pparam_->SetStartX(x);
	pparam_->SetStartY(y);
	PosManager::Generate(eOBJECT::TARGET_READY, pparam_);
}


Target::~Target(void)
{
	PosManager::Delete(pparam_);
	delete iparam_;
	delete iparam_collision_;
	delete pparam_;
}


/*!
@brief オブジェクト間の角度を求める関数
@param group 対象オブジェクトのグループ
@param name 対象オブジェクトの名前
@param angle 計算結果に追加する角度(オプション)
@return 計算結果(ラジアン)
@note
 自身と対象オブジェクト間の角度を計算して結果を返す。
 第三引数に指定があった場合、計算結果に第三引数の角度を加える。
*/
double Target::GetAtan(eOBJECT::GROUP group, std::string name, double angle)
{
	double return_value;

	return_value = PosManager::GetAtan(pparam_, group, name);
	return_value += CalcRAD(angle);

	return return_value;
}


double Target::Collision(double extension)
{
	if (InsidePanel(extension)) {
		PosManager::GetHit(pparam_, &hit_);
	} else {
		hit_ = 0;
	}

	return hit_;
}


void Target::CollisionImg(int imgfile, int imgdiv, int interval)
{
	if (collision_interval_img_ == -1) {
		if (hit_ != 0) {
			collision_interval_img_ = 0;
		}
	} else {
		PosManager::GetPosX(pparam_, &iparam_collision_->pos_cx_);
		PosManager::GetPosY(pparam_, &iparam_collision_->pos_cy_);
		ImgManager::Draw(imgfile, imgdiv, iparam_collision_);
		if (hit_ != 0) {
			collision_interval_img_ = 0;
		}
		else {
			collision_interval_img_++;
		}
		if (interval <= collision_interval_img_)
			collision_interval_img_ = -1;
	}
}


void Target::CollisionSound(int soundfile, int interval)
{
	if (collision_interval_sound_ == -1) {
		if (hit_ != 0) {
			SoundManager::Play(soundfile, DX_PLAYTYPE_BACK);
			collision_interval_sound_ = 0;
		}
	}
	else {
		if (hit_ != 0) {
			collision_interval_sound_ = 0;
		}
		else {
			collision_interval_sound_++;
		}
		if (interval <= collision_interval_sound_)
			collision_interval_sound_ = -1;
	}

}


void Target::DeleteData(double add_alv)
{
	double distance;

	distance = PosManager::CalcDiffDistance(pparam_, eOBJECT::GROUP::USER, "UserPos");
	if (distance < 100) {
		DesignManager::AddAttackLV(add_alv * 3);
	} else if (distance < 200) {
		DesignManager::AddAttackLV(add_alv * 2);
	} else {
		DesignManager::AddAttackLV(add_alv);
	}
	PosManager::Delete(pparam_);
}


void Target::DeleteData(double add_alv, double add_rank)
{
	double distance;

	distance = PosManager::CalcDiffDistance(pparam_, eOBJECT::GROUP::USER, "UserPos");
	if (distance < 100) {
		DesignManager::AddAttackLV(add_alv * 3);
		DesignManager::AddClockRank(add_rank * 3);
	}
	else if (distance < 200) {
		DesignManager::AddAttackLV(add_alv * 2);
		DesignManager::AddClockRank(add_rank * 2);	}
	else {
		DesignManager::AddAttackLV(add_alv * 1);
		DesignManager::AddClockRank(add_rank * 1);	}
	PosManager::Delete(pparam_);
}


void Target::DeleteData(double add_alv, double add_exarms, double add_rank, long add_score)
{
	double distance;

	distance = PosManager::CalcDiffDistance(pparam_, eOBJECT::GROUP::USER, "UserPos");
	if (distance < 100) {
		DesignManager::AddAttackLV(add_alv * 3);
		DesignManager::AddExArms(add_exarms * 3);
		DesignManager::AddClockRank(add_rank * 3);
		DesignManager::AddScore(add_score * 3);
	} else if (distance < 200) {
		DesignManager::AddAttackLV(add_alv * 2);
		DesignManager::AddExArms(add_exarms * 2);
		DesignManager::AddClockRank(add_rank * 2);
		DesignManager::AddScore(add_score * 2);
	} else {
		DesignManager::AddAttackLV(add_alv * 1);
		DesignManager::AddExArms(add_exarms * 1);
		DesignManager::AddClockRank(add_rank * 1);
		DesignManager::AddScore(add_score * 1);
	}
	PosManager::Delete(pparam_);
}


void Target::Draw(unsigned int imgfile, double angle)
{
	iparam_->draw_angle_ = angle;
	PosManager::GetPosX(pparam_, &iparam_->pos_cx_);
	PosManager::GetPosY(pparam_, &iparam_->pos_cy_);
	ImgManager::Draw(imgfile, 0, iparam_);
}


void Target::Draw(unsigned int imgfile, unsigned int imgdiv, double angle)
{
	iparam_->draw_angle_ = angle;
	iparam_->extend_rate_ = 1.0;
	PosManager::GetPosX(pparam_, &iparam_->pos_cx_);
	PosManager::GetPosY(pparam_, &iparam_->pos_cy_);
	ImgManager::Draw(imgfile, imgdiv, iparam_);
}


void Target::Draw(unsigned int imgfile, unsigned int imgdiv, double exrate, double angle)
{
	iparam_->draw_angle_ = angle;
	iparam_->extend_rate_ = exrate;
	PosManager::GetPosX(pparam_, &iparam_->pos_cx_);
	PosManager::GetPosY(pparam_, &iparam_->pos_cy_);
	ImgManager::Draw(imgfile, imgdiv, iparam_);
}


void Target::GetPos(int *x, int *y)
{
	if (x != NULL)
		PosManager::GetPosX(pparam_, x);
	if (y != NULL)
		PosManager::GetPosY(pparam_, y);
}

void Target::GetPos(double *x, double *y)
{
	if (x != NULL)
		PosManager::GetPosX(pparam_, x);
	if (y != NULL)
		PosManager::GetPosY(pparam_, y);
}


bool Target::InsidePanel(double extension) {
	double x, y;
	double panel_max_x, panel_max_y;
	double panel_min_x, panel_min_y;

	PosManager::GetPosX(pparam_, &x);
	PosManager::GetPosY(pparam_, &y);
	PosManager::GetAbsolutePanelMaxX(&panel_max_x);
	PosManager::GetAbsolutePanelMaxY(&panel_max_y);
	PosManager::GetAbsolutePanelMinX(&panel_min_x);
	PosManager::GetAbsolutePanelMinY(&panel_min_y);
	if (x < panel_min_x - extension || panel_max_x + extension < x) {
		return false;
	} else if (y < panel_min_y - extension || panel_max_y + extension < y) {
		return false;
	}

	return true;
}


void Target::MoveA(double *add_x, double *add_y)
{
	PosManager::MovePosA(pparam_, add_x, add_y);
}


void Target::MoveB(double angle, double dist)
{
	PosManager::MovePosB(pparam_, angle, dist);
}


void Target::SetPos(double *x, double *y)
{
	PosManager::SetPosA(pparam_, x, y);
}


void Target::SetGroup(eOBJECT::GROUP set_group)
{
	iparam_->group_type_ = set_group;
	PosManager::SetGroup(pparam_, set_group);
}

