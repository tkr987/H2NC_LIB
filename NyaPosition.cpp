#include <cmath>
#include <tuple>
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;

vector<pair<eOBJECT, eOBJECT>> NyaPosition::collision_group_vector_;
vector<PositionHandle1*> NyaPosition::collision_vector1_[static_cast<int>(eOBJECT::sizeof_enum)];
vector<PositionHandle2*> NyaPosition::collision_vector2_[static_cast<int>(eOBJECT::sizeof_enum)];
list<PositionHandle1*> NyaPosition::regist_list1_;
list<PositionHandle2*> NyaPosition::regist_list2_;

NyaPosition::NyaPosition()
{

}


NyaPosition::~NyaPosition()
{

}


void NyaPosition::Collision(PositionHandle1* phx, eOBJECT group)
{
	phx->collision_hit_ = false;
	collision_vector1_[static_cast<int>(group)].push_back(phx);
}


void NyaPosition::Regist(PositionHandle1* handle) 
{
	regist_list1_.insert(regist_list1_.begin(), handle);
}

void NyaPosition::Regist(PositionHandle2* handle) 
{
	regist_list2_.insert(regist_list2_.begin(), handle);
}

void NyaPosition::Delete(PositionHandle1* handle) 
{

}

void NyaPosition::Delete(PositionHandle2* handle) 
{

}

void NyaPosition::Init(void)
{
	collision_group_vector_.clear();
	for (auto& e : collision_vector1_)
		e.clear();
	for (auto& e : collision_vector2_)
		e.clear();
	regist_list1_.clear();
	regist_list2_.clear();
}

bool NyaPosition::InScreen(PositionHandle1* phx, int gap)
{
	if (phx->grid_x_ < SCREEN_MIN_X - gap)
		return false;
	if (SCREEN_MAX_X + gap < phx->grid_x_)
		return false;
	if (phx->grid_y_ < SCREEN_MIN_Y - gap)
		return false;
	if (SCREEN_MAX_Y + gap < phx->grid_y_)
		return false;

	return true;
}

void NyaPosition::Run(void)
{
	// 衝突判定
	for (auto& e : collision_group_vector_)
		JudgeCollision1(e.first, e.second);

	// 配列のクリア
	for (auto& e : collision_group_vector_) 
	{
		collision_vector1_[static_cast<int>(e.first)].clear();
		collision_vector1_[static_cast<int>(e.second)].clear();
	}


}

/**
 衝突判定設定関数
 @param group1 セットする値１
 @param group2 セットする値２
 @note
 どのオブジェクトグループ同士で衝突判定処理をするのか設定するために使用する関数。
 例えば、eOBJECT::USER1とeOBJECT::TARGET_ATTACK1を引数で指定しておけば、
 NyaPosition::Run()にてUSER1とTARGET_ATTACK1のオブジェクト同士の衝突判定を実行するようになる。
**/
void NyaPosition::SettingCollision(eOBJECT group1, eOBJECT group2)
{
	pair<eOBJECT, eOBJECT> set;

	// すでに同じオブジェクトグループが設定されてたら何もしないで終了
	for (auto& e : collision_group_vector_) {
		if (e.first == group1 && e.second == group2)
			return;
		if (e.first == group2 && e.second == group1)
			return;
	}

	set.first = group1;
	set.second = group2;
	collision_group_vector_.push_back(set);
}

void NyaPosition::JudgeCollision1(eOBJECT object_group1, eOBJECT object_group2)
{
	for (auto& e1 : collision_vector1_[static_cast<int>(object_group1)])
	{	
		for (auto& e2 : collision_vector1_[static_cast<int>(object_group2)])
		{
			// pow()してるのでabs()は不要
			if (pow(e1->grid_x_ - e2->grid_x_, 2.0) + pow(e1->grid_y_ - e2->grid_y_, 2.0) < pow(e1->collision_range_ + e2->collision_range_, 2.0))
			{
				e1->health_now_ -= e2->collision_pow_;
				e2->health_now_ -= e1->collision_pow_;
				e1->collision_hit_ = true;
				e2->collision_hit_ = true;
			}
		}
	}
}


void NyaPosition::JudgeCollision2(eOBJECT object_group1, eOBJECT object_group2)
{
	double a, b, c;
	double distance;

	for (auto it1 = collision_vector2_[static_cast<int>(object_group1)].begin(); it1 != collision_vector2_[static_cast<int>(object_group1)].end(); ++it1) {	
		for (auto it2 = collision_vector2_[static_cast<int>(object_group2)].begin(); it2 != collision_vector2_[static_cast<int>(object_group2)].end(); ++it2) {

			a = ((*it1)->grid_y_ - (*it1)->grid_y_pre_) /  ((*it1)->grid_x_ - (*it1)->grid_x_pre_);
			b = -1;
			c = (*it1)->grid_y_pre_ - ((*it1)->grid_x_pre_ * ((*it1)->grid_y_ - (*it1)->grid_y_pre_)) / ((*it1)->grid_x_ - (*it1)->grid_x_pre_);

			distance = abs(((a * (*it2)->grid_x_) + (b * (*it2)->grid_y_) + c)) / sqrt(pow(a,2) + pow(b,2));


			if ((*it2)->grid_x_ < (*it1)->grid_x_ && (*it2)->grid_x_ < (*it1)->grid_x_pre_)
				continue;
			if ((*it1)->grid_x_ < (*it2)->grid_x_ && (*it1)->grid_x_pre_ < (*it2)->grid_x_)
				continue;
			if ((*it2)->grid_y_ < (*it1)->grid_y_ && (*it2)->grid_y_ < (*it1)->grid_y_pre_)
				continue;
			if ((*it1)->grid_y_ < (*it2)->grid_y_ && (*it1)->grid_y_pre_ < (*it2)->grid_y_)
				continue;

			if(distance < (*it1)->collision_range_+ (*it2)->collision_range_) {
	
				(*it1)->health_now_ -= (*it2)->collision_pow_;
				(*it2)->health_now_ -= (*it1)->collision_pow_;
			}
		}
	}
	collision_vector2_[static_cast<int>(object_group1)].clear();
	collision_vector2_[static_cast<int>(object_group2)].clear();
}

