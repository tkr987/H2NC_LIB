#include <cmath>
#include <tuple>
#include "NyaEnum.h"
#include "NyaPosition.h"

using namespace std;
using namespace H2NLIB;

vector<pair<eOBJECT, eOBJECT>> NyaPosition::collision_group_combination_;
vector<CollisionHandleSet> NyaPosition::collision_collection_(static_cast<int>(eOBJECT::sizeof_enum));

/**
 @brief 衝突判定処理するハンドルを登録する関数
 @param phandle 衝突判定処理するハンドル
 @param group 衝突判定するハンドルのオブジェクトグループ
 @note
  phandleをgroupとして登録し、衝突判定処理を実行する
  なお、登録されたハンドルはフレーム毎にクリアされるので、
  判定処理をし続けたいときは１フレーム毎にCollision()で登録し直す必要がある
**/
void NyaPosition::Collision(PositionHandle1* phandle, eOBJECT group)
{
	phandle->collision_hit_ = false;
	collision_collection_[static_cast<int>(group)].handle1_collection_.push_back(phandle);
}

/**
 @brief 衝突判定をするオブジェクトの組み合わせを設定する関数
 @param group1 衝突判定をするオブジェクトのグループ１
 @param group2 衝突判定をするオブジェクトのグループ２
 @note
  この関数の引数を使って設定すると、
  group1のオブジェクトとgroup2のオブジェクト同士で衝突判定をするようになる
**/
void NyaPosition::CollisionSetting(eOBJECT group1, eOBJECT group2)
{
	pair<eOBJECT, eOBJECT> set;

	// すでに同じオブジェクトグループが設定されてたら何もしないで終了
	for (auto& e : collision_group_combination_) {
		if (e.first == group1 && e.second == group2)
			return;
		if (e.first == group2 && e.second == group1)
			return;
	}

	set.first = group1;
	set.second = group2;
	collision_group_combination_.push_back(set);
}

/**
 @brief 画面領域内かどうか調べる関数
 @param phandle 画面内かどうか調べるハンドル
 @param gap 画面領域のギャップ
 @note
  phandleが画面領域内にあるかどうか調べることができる
  gapに正の値を指定すると判定する画面領域を拡大できる
  gapに負の値を指定すると判定する画面領域を縮小できる
**/
bool NyaPosition::InScreen(PositionHandle1* phandle, int gap)
{
	if (phandle->grid_x_ < SCREEN_MIN_X - gap)
		return false;
	if (SCREEN_MAX_X + gap < phandle->grid_x_)
		return false;
	if (phandle->grid_y_ < SCREEN_MIN_Y - gap)
		return false;
	if (SCREEN_MAX_Y + gap < phandle->grid_y_)
		return false;

	return true;
}

/**
 @brief 実行関数
 @note
  ライブラリのNyaWindowクラス内で自動的に呼ばれるので、ライブラリ使用者が呼ぶ必要はない
**/
void NyaPosition::Run(void)
{
	// CollisionSettingで設定したオブジェクトグループの組み合わせで衝突判定をおこなう
	for (auto& e : collision_group_combination_)
		JudgeCollision1(e.first, e.second);

	// 毎フレームCollisionHandleSetのクリアをする
	for (auto& e : collision_collection_) 
		e.handle1_collection_.clear();
}

/**
 @brief 衝突判定を実行する関数１
 @note
  簡易的な衝突判定処理をする
**/
void NyaPosition::JudgeCollision1(eOBJECT object_group1, eOBJECT object_group2)
{
	for (auto& e1 : collision_collection_[static_cast<int>(object_group1)].handle1_collection_)
	{	
		for (auto& e2 : collision_collection_[static_cast<int>(object_group2)].handle1_collection_)
		{
			// ２乗してるのでabs不要
			if ((e1->grid_x_ - e2->grid_x_) * (e1->grid_x_ - e2->grid_x_) + (e1->grid_y_ - e2->grid_y_) * (e1->grid_y_ - e2->grid_y_) 
				< (e1->collision_range_ + e2->collision_range_) * (e1->collision_range_ + e2->collision_range_))
			{
				e1->health_now_ -= e2->collision_damage_;
				e2->health_now_ -= e1->collision_damage_;
				e1->collision_hit_ = true;
				e2->collision_hit_ = true;
			}
		}
	}
}

/**
 @brief 衝突判定を実行する関数２
 @note
  未完成
**/
void NyaPosition::JudgeCollision2(eOBJECT object_group1, eOBJECT object_group2)
{
	//double a, b, c;
	//double distance;

	//for (auto it1 = collision_vector2_[static_cast<int>(object_group1)].begin(); it1 != collision_vector2_[static_cast<int>(object_group1)].end(); ++it1) {	
	//	for (auto it2 = collision_vector2_[static_cast<int>(object_group2)].begin(); it2 != collision_vector2_[static_cast<int>(object_group2)].end(); ++it2) {

	//		a = ((*it1)->grid_y_ - (*it1)->grid_y_pre_) /  ((*it1)->grid_x_ - (*it1)->grid_x_pre_);
	//		b = -1;
	//		c = (*it1)->grid_y_pre_ - ((*it1)->grid_x_pre_ * ((*it1)->grid_y_ - (*it1)->grid_y_pre_)) / ((*it1)->grid_x_ - (*it1)->grid_x_pre_);

	//		distance = abs(((a * (*it2)->grid_x_) + (b * (*it2)->grid_y_) + c)) / sqrt(pow(a,2) + pow(b,2));


	//		if ((*it2)->grid_x_ < (*it1)->grid_x_ && (*it2)->grid_x_ < (*it1)->grid_x_pre_)
	//			continue;
	//		if ((*it1)->grid_x_ < (*it2)->grid_x_ && (*it1)->grid_x_pre_ < (*it2)->grid_x_)
	//			continue;
	//		if ((*it2)->grid_y_ < (*it1)->grid_y_ && (*it2)->grid_y_ < (*it1)->grid_y_pre_)
	//			continue;
	//		if ((*it1)->grid_y_ < (*it2)->grid_y_ && (*it1)->grid_y_pre_ < (*it2)->grid_y_)
	//			continue;

	//		if(distance < (*it1)->collision_range_+ (*it2)->collision_range_) {
	//
	//			(*it1)->health_now_ -= (*it2)->collision_pow_;
	//			(*it2)->health_now_ -= (*it1)->collision_pow_;
	//		}
	//	}
	//}
}

