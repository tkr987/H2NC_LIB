#include <cmath>
#include <tuple>
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;

int NyaPosition::d_ = 0;
vector<pair<eOBJECT::GROUP, eOBJECT::GROUP>> NyaPosition::collision_group_vector_;
vector<eOBJECT::GROUP> NyaPosition::collision_high_accuracy_group_vector_;
vector<PositionHandleX*> NyaPosition::collision_vector_[eOBJECT::GROUP::sizeof_enum];
list<PositionHandleX> NyaPosition::create_list_;

NyaPosition::NyaPosition()
{
	static bool first_call = true;

	if (first_call) {
		NyaString::SettingFont("debug", 10, 2);
		first_call = false;
	}
}


NyaPosition::~NyaPosition()
{

}


void NyaPosition::Collision(PositionHandleX* phx, eOBJECT::GROUP group)
{
	collision_vector_[group].push_back(phx);
}


PositionHandleX* NyaPosition::Create(void) 
{
	static PositionHandleX phx;

	create_list_.insert(create_list_.begin(), phx);

	return &(*create_list_.begin());
}

void NyaPosition::Run(void)
{
	vector<eOBJECT::GROUP>::iterator find_it1;
	vector<eOBJECT::GROUP>::iterator find_it2;
	tuple<int, int, int> color = make_tuple(255, 255, 255);

	NyaString::Write("debug", color, 50, 150, "[50, 150] collision_group_vector = %d", (int)collision_group_vector_.size());
	NyaString::Write("debug", color, 50, 170, "[50, 170] collision_vector[TARGET_ATTACK1] = %d", (int)collision_vector_[eOBJECT::GROUP::TARGET_ATTACK1].size());
	NyaString::Write("debug", color, 50, 190, "[50, 190] collision_vector[USER1] = %d", (int)collision_vector_[eOBJECT::GROUP::USER1].size());

	// 衝突判定
	//d_ = 0;
	//for (auto it = collision_group_vector_.begin(); it != collision_group_vector_.end(); ++it) {

	//	find_it1 = find(collision_high_accuracy_group_vector_.begin(), collision_high_accuracy_group_vector_.end(), it->first);
	//	find_it2 = find(collision_high_accuracy_group_vector_.begin(), collision_high_accuracy_group_vector_.end(), it->second);
	//	if (find_it1 != collision_high_accuracy_group_vector_.end()) {
	//	//	JudgeCollisionHighAccuracy(it->first, it->second);		
	//	} else if (find_it2 != collision_high_accuracy_group_vector_.end()){
	//	//	JudgeCollisionHighAccuracy(it->second, it->first);
	//	}else{
	//		JudgeCollision(it->first, it->second);
	//	}
	//}
	JudgeCollision(eOBJECT::GROUP::USER1, eOBJECT::GROUP::TARGET_ATTACK1);
	NyaString::Write("debug", color, 50, 210, "[50, 210] NyaPosition::d_ = %d", d_);

	// 配列のクリア
	for (auto it = collision_group_vector_.begin(); it != collision_group_vector_.end(); ++it) {
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
 例えば、eOBJECT::GROUP::USER1とeOBJECT::GROUP::TARGET_ATTACK1を引数で指定しておけば、
 NyaPosition::Run()にてUSER1とTARGET_ATTACK1のオブジェクト同士の衝突判定を実行するようになる。
**/
void NyaPosition::SettingCollision(eOBJECT::GROUP group1, eOBJECT::GROUP group2)
{
	pair<eOBJECT::GROUP, eOBJECT::GROUP> set;

	// すでに同じオブジェクトグループが設定されてたら何もしないで終了
	for (auto it = collision_group_vector_.begin(); it != collision_group_vector_.end(); ++it) {
		if (it->first == group1 && it->second == group2)
			return;
		if (it->first == group2 && it->second == group1)
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
 例えば、eOBJECT::GROUP::USER1とeOBJECT::GROUP::TARGET_ATTACK1を引数で指定しておけば、
 NyaPosition::Run()にてUSER1とTARGET_ATTACK1のオブジェクト同士の衝突判定を実行するようになる。
**/
void NyaPosition::SettingCollisionHighAccuracy(eOBJECT::GROUP group)
{
	vector<eOBJECT::GROUP>::iterator find_it;

	// すでに同じオブジェクトグループが設定されてたら何もしないで終了
	find_it = find(collision_high_accuracy_group_vector_.begin(), collision_high_accuracy_group_vector_.end(), group);
	if (find_it != collision_high_accuracy_group_vector_.end())
		return;

	collision_high_accuracy_group_vector_.push_back(group);
}

void NyaPosition::JudgeCollision(eOBJECT::GROUP object_group1, eOBJECT::GROUP object_group2)
{

	for (auto it1 = collision_vector_[object_group1].begin(); it1 != collision_vector_[object_group1].end(); ++it1) {	
		for (auto it2 = collision_vector_[object_group2].begin(); it2 != collision_vector_[object_group2].end(); ++it2) {
			
			// pow()してるのでabs()は不要
			if (pow((*it1)->x_ - (*it2)->x_, 2.0) + pow((*it1)->y_ - (*it2)->y_, 2.0) < pow((*it1)->range_ + (*it2)->range_, 2.0)) {
				//(*it1)->health_now_ -= (*it2)->pow_;
				//(*it2)->health_now_ -= (*it1)->pow_;
				(*it1)->health_now_ -= 1.0;
				(*it2)->health_now_ -= 1;

				d_ ++;
			}
		}
	}
}


void NyaPosition::JudgeCollisionHighAccuracy(eOBJECT::GROUP object_group1, eOBJECT::GROUP object_group2)
{
	double a, b, c;
	double distance;

	for (auto it1 = collision_vector_[object_group1].begin(); it1 != collision_vector_[object_group1].end(); ++it1) {	
		for (auto it2 = collision_vector_[object_group2].begin(); it2 != collision_vector_[object_group2].end(); ++it2) {

			a = ((*it1)->y_ - (*it1)->y_pre_) /  ((*it1)->x_ - (*it1)->x_pre_);
			b = -1;
			c = (*it1)->y_pre_ - ((*it1)->x_pre_ * ((*it1)->y_ - (*it1)->y_pre_)) / ((*it1)->x_ - (*it1)->x_pre_);

			distance = abs(((a * (*it2)->x_) + (b * (*it2)->y_) + c)) / sqrt(pow(a,2) + pow(b,2));


			if ((*it2)->x_ < (*it1)->x_ && (*it2)->x_ < (*it1)->x_pre_)
				continue;
			if ((*it1)->x_ < (*it2)->x_ && (*it1)->x_pre_ < (*it2)->x_)
				continue;
			if ((*it2)->y_ < (*it1)->y_ && (*it2)->y_ < (*it1)->y_pre_)
				continue;
			if ((*it1)->y_ < (*it2)->y_ && (*it1)->y_pre_ < (*it2)->y_)
				continue;

			if(distance < (*it1)->range_+ (*it2)->range_) {
	
				(*it1)->health_now_ -= (*it2)->pow_;
				(*it2)->health_now_ -= (*it1)->pow_;
			}
		}
	}
	collision_vector_[object_group1].clear();
	collision_vector_[object_group2].clear();
}

