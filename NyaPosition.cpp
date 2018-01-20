#include <cmath>
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;

vector<tuple<int, eOBJECT::GROUP, eOBJECT::GROUP>> NyaPosition::collision_group_vector_;
vector<PositionPropertyX*> NyaPosition::collision_vector_[eOBJECT::GROUP::sizeof_enum];
list<PositionPropertyX> NyaPosition::create_list_;

NyaPosition::NyaPosition()
{

}


NyaPosition::~NyaPosition()
{

}


void NyaPosition::Collide(PositionPropertyX* ppx)
{
	collision_vector_->push_back(ppx);
}


PositionPropertyX* NyaPosition::Create(void) 
{
	static PositionPropertyX ppx;

	create_list_.insert(create_list_.begin(), ppx);

	return &(*create_list_.begin());
}

void NyaPosition::Delete(PositionPropertyX* ppx)
{


}


void NyaPosition::Run(void)
{
	for (auto it = collision_group_vector_.begin(); it != collision_group_vector_.end(); ++it) {
		if (get<0>(*it) == 1) {
			CollisionType1(get<1>(*it), get<2>(*it));
		} else if (get<0>(*it) == 2) {
		
		} else if (get<0>(*it) == 3) {
		
		}
	}	
}

/**
 衝突判定設定関数
 @param collision_type 衝突判定処理の種類
 @param group1 セットする値１
 @param group2 セットする値２
 @note
 どのオブジェクトグループ同士で衝突判定処理をするのか設定するために使用する関数。
 衝突判定処理の種類は
 1 三平方の衝突判定処理
 2 簡略化された高速衝突判定処理
 例えば、eOBJECT::GROUP::USERとeOBJECT::GROUP::TARGET_ATTACKを引数で指定しておけば、
 NyaPosition::Run()にてUSERとTARGET_ATTACKのオブジェクト同士の衝突判定を実行するようになる。
**/
void NyaPosition::SettingCollision(int collision_type, eOBJECT::GROUP group1, eOBJECT::GROUP group2)
{
	tuple<int, eOBJECT::GROUP, eOBJECT::GROUP> set;

	// すでに同じオブジェクトグループが設定されてたら何もしないで終了
	for (auto it = collision_group_vector_.begin(); it != collision_group_vector_.end(); ++it) {
		if (get<1>(*it) == group1 && get<2>(*it) == group2)
			return;
		if (get<1>(*it) == group2 && get<2>(*it) == group1)
			return;
	}

	// オブジェクトグループをセットする
	get<0>(set) = collision_type;
	get<1>(set) = group1;
	get<1>(set) = group2;
	collision_group_vector_.push_back(set);
}


void NyaPosition::CollisionType1(eOBJECT::GROUP object_group1, eOBJECT::GROUP object_group2)
{

	for (auto it1 = collision_vector_[object_group1].begin(); it1 != collision_vector_[object_group1].end(); ++it1) {	
		for (auto it2 = collision_vector_[object_group2].begin(); it2 != collision_vector_[object_group2].end(); ++it2) {

			if (pow((*it1)->x_ - (*it2)->x_, 2.0) + pow((*it1)->y_ - (*it2)->y_, 2.0) < pow((*it1)->range_ + (*it2)->range_, 2.0)) {
				(*it1)->health_now_ -= (*it2)->pow_;
				(*it1)->health_now_ -= (*it2)->pow_;
			}
		}
	}
}


