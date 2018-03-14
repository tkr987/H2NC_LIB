#include <cmath>
#include <tuple>
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;

vector<pair<eOBJECT::NUM, eOBJECT::NUM>> NyaPosition::collision_group_vector_;
vector<eOBJECT::NUM> NyaPosition::collision_high_accuracy_group_vector_;
vector<PositionHandleX*> NyaPosition::collision_vector_[eOBJECT::NUM::sizeof_enum];
list<PositionHandleX> NyaPosition::create_list_;

NyaPosition::NyaPosition()
{

}


NyaPosition::~NyaPosition()
{

}


void NyaPosition::Collision(PositionHandleX* phx, eOBJECT::NUM group)
{
	collision_vector_[group].push_back(phx);
}


PositionHandleX* NyaPosition::Create(void) 
{
	PositionHandleX phx;

	create_list_.insert(create_list_.begin(), phx);

	return &(*create_list_.begin());
}

bool NyaPosition::InScreen(PositionHandleX* phx, int gap)
{
	if (0 - gap < phx->grid_x_ && phx->grid_x_ < SCREEN_MAX_X + gap)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void NyaPosition::Run(void)
{
	vector<eOBJECT::NUM>::iterator find_it1;
	vector<eOBJECT::NUM>::iterator find_it2;

	// 衝突判定
	for (auto it = collision_group_vector_.begin(); it != collision_group_vector_.end(); ++it)
	{
		find_it1 = find(collision_high_accuracy_group_vector_.begin(), collision_high_accuracy_group_vector_.end(), it->first);
		find_it2 = find(collision_high_accuracy_group_vector_.begin(), collision_high_accuracy_group_vector_.end(), it->second);
		if (find_it1 != collision_high_accuracy_group_vector_.end()) {
			JudgeCollisionHighAccuracy(it->first, it->second);		
		} else if (find_it2 != collision_high_accuracy_group_vector_.end()){
			JudgeCollisionHighAccuracy(it->second, it->first);
		}else{
			JudgeCollision(it->first, it->second);
		}
	}

	// 配列のクリア
	for (auto it = collision_group_vector_.begin(); it != collision_group_vector_.end(); ++it) 
	{
		collision_vector_[it->first].clear();
		collision_vector_[it->second].clear();
	}


}

/**
 衝突判定設定関数
 @param group1 セットする値１
 @param group2 セットする値２
 @note
 どのオブジェクトグループ同士で衝突判定処理をするのか設定するために使用する関数。
 例えば、eOBJECT::NUM::USER1とeOBJECT::NUM::TARGET_ATTACK1を引数で指定しておけば、
 NyaPosition::Run()にてUSER1とTARGET_ATTACK1のオブジェクト同士の衝突判定を実行するようになる。
**/
void NyaPosition::SettingCollision(eOBJECT::NUM group1, eOBJECT::NUM group2)
{
	pair<eOBJECT::NUM, eOBJECT::NUM> set;

	// すでに同じオブジェクトグループが設定されてたら何もしないで終了
	for (auto& it : collision_group_vector_) {
		if (it.first == group1 && it.second == group2)
			return;
		if (it.first == group2 && it.second == group1)
			return;
	}

	set.first = group1;
	set.second = group2;
	collision_group_vector_.push_back(set);
}


/**
 高精度衝突判定設定関数
 @param group1 セットする値１
 @note
 どのオブジェクトグループ同士で衝突判定処理をするのか設定するために使用する関数。
 例えば、eOBJECT::NUM::USER1とeOBJECT::NUM::TARGET_ATTACK1を引数で指定しておけば、
 NyaPosition::Run()にてUSER1とTARGET_ATTACK1のオブジェクト同士の衝突判定を実行するようになる。
**/
void NyaPosition::SettingCollisionHighAccuracy(eOBJECT::NUM group)
{
	vector<eOBJECT::NUM>::iterator find_it;

	// すでに同じオブジェクトグループが設定されてたら何もしないで終了
	find_it = find(collision_high_accuracy_group_vector_.begin(), collision_high_accuracy_group_vector_.end(), group);
	if (find_it != collision_high_accuracy_group_vector_.end())
		return;

	collision_high_accuracy_group_vector_.push_back(group);
}

void NyaPosition::JudgeCollision(eOBJECT::NUM object_group1, eOBJECT::NUM object_group2)
{
	for (auto& it1 : collision_vector_[object_group1])
		it1->collision_hit_ = false;

	for (auto it2 : collision_vector_[object_group2])
		it2->collision_hit_ = false;

	for (auto& it1 : collision_vector_[object_group1])
	{	
		for (auto it2 : collision_vector_[object_group2])
		{
			// pow()してるのでabs()は不要
			if (pow(it1->grid_x_ - it2->grid_x_, 2.0) + pow(it1->grid_y_ - it2->grid_y_, 2.0) < pow(it1->collision_range_ + it2->collision_range_, 2.0))
			{
				it1->health_now_ -= it2->collision_pow_;
				it2->health_now_ -= it1->collision_pow_;
				it1->collision_hit_ = true;
				it2->collision_hit_ = true;
			}
		}
	}
}


void NyaPosition::JudgeCollisionHighAccuracy(eOBJECT::NUM object_group1, eOBJECT::NUM object_group2)
{
	double a, b, c;
	double distance;

	for (auto it1 = collision_vector_[object_group1].begin(); it1 != collision_vector_[object_group1].end(); ++it1) {	
		for (auto it2 = collision_vector_[object_group2].begin(); it2 != collision_vector_[object_group2].end(); ++it2) {

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
	collision_vector_[object_group1].clear();
	collision_vector_[object_group2].clear();
}

