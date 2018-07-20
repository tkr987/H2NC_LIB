#include <cmath>
#include <deque>
#include <tuple>
#include "NyaEnum.h"
#include "NyaPosition.h"

using namespace std;
using namespace HNLIB;

vector<pair<eOBJECT, eOBJECT>> NyaPosition::collision_pair_collection_;
vector<PositionHandle*> NyaPosition::collision_collection_[static_cast<int>(eOBJECT::sizeof_enum)];
list<PositionHandle*> NyaPosition::handle_collection_;
list<PositionMove> NyaPosition::move_collection_;

double HNLIB::NyaPosition::Angle(PositionHandle* handle1, PositionHandle* handle2)
{
	return RadToAngle(atan2(handle2->grid_y_ - handle1->grid_y_, handle2->grid_x_ - handle1->grid_x_));
}

/**
 @brief 衝突判定処理するハンドルを登録する関数
 @param phandle 衝突判定処理するハンドル
 @param type 衝突判定するハンドルのオブジェクトのタイプ
 @note
  phandleをgroupとして登録し、衝突判定処理を実行する
  なお、登録されたハンドルはフレーム毎にクリアされるので、
  判定処理をし続けたいときは１フレーム毎にCollision()で登録し直す必要がある
**/
void NyaPosition::Collide(PositionHandle* handle, eOBJECT type)
{
	collision_collection_[static_cast<int>(type)].push_back(handle);
}

/**
 @brief 衝突判定をするオブジェクトの組み合わせを設定する関数
 @param type1 衝突判定をするオブジェクトのタイプ１
 @param type2 衝突判定をするオブジェクトのタイプ２
 @note
  この関数の引数を使って設定すると、
  group1のオブジェクトとgroup2のオブジェクト同士で衝突判定をするようになる
**/
void NyaPosition::CollisionPair(eOBJECT type1, eOBJECT type2)
{
	pair<eOBJECT, eOBJECT> set;

	// すでに同じオブジェクトグループが設定されてたら何もしないで終了
	for (auto& e : collision_pair_collection_) {
		if (e.first == type1 && e.second == type2)
			return;
		if (e.first == type2 && e.second == type1)
			return;
	}

	set.first = type1;
	set.second = type2;
	collision_pair_collection_.push_back(set);
}

/**
@brief ハンドル新規作成関数
@note
 新規作成したハンドルを返す
**/
PositionHandle* NyaPosition::CreateHandle(void)
{
	PositionHandle* new_handle = new PositionHandle;

	handle_collection_.push_back(new_handle);

	return new_handle;
}

/**
@brief ハンドル新規作成関数
@note
 動的生成したhandleを引数から渡して登録する方法で新規作成するときに使う
 nullptrのポインタを渡したときはハンドルを新規に作成して引数に格納される
**/
void NyaPosition::CreateHandle(PositionHandle* new_handle)
{
	if (new_handle == nullptr)
		new_handle = new PositionHandle;

	handle_collection_.push_back(new_handle);
}

/**
@brief ハンドル削除関数
@note
 引数で指定されたハンドルを削除する
**/
void HNLIB::NyaPosition::DeleteHandle(PositionHandle* delete_handle)
{
	handle_collection_.remove(delete_handle);
	delete delete_handle;
	delete_handle = nullptr;
}

/**
@brief ハンドル検索関数
@param name 検索する名前
@param handle 検索結果を格納する
@retval 1 見つかった
@retval 0 見つからなかった
@note
 見つからなかったときは何もしない
**/
int NyaPosition::FindHandle(std::string name, PositionHandle* handle)
{
	for (auto& e : handle_collection_)
	{
		if (e->name_ == name)
		{
			*handle = *e;
			return 1;
		}
	}

	return 0;
}

/**
@brief ハンドル検索関数
@param name 検索する名前
@param handle 検索結果を格納する
@return 見つかったハンドルの数
@note
 見つからなかったときは何もしない
**/
int NyaPosition::FindHandle(string name, vector<PositionHandle>* handle_collection)
{
	int find = 0;
	for (auto& e : handle_collection_)
	{
		if (e->name_ == name)
		{
			handle_collection->push_back(*e);
			find++;
		}
	}

	return find;
}

/**
@brief 移動関数
@param handle 移動させるハンドル
@param angle 移動角度
@param max_frame 移動時間(フレーム単位)
@param length 移動距離
@note
 handleを角度angleでmax_frameかけてlengthだけ移動させる
**/
void NyaPosition::MoveGridMode(PositionHandle* handle, double end_x,  double end_y, unsigned int max_frame)
{
	PositionMove new_move;

	new_move.frame_ = 0;
	new_move.max_frame_ = max_frame;
	new_move.handle_ = handle;
	new_move.move_x_ = (end_x - handle->grid_x_) / (double)max_frame;
	new_move.move_y_ = (end_y - handle->grid_y_) / (double)max_frame;
	move_collection_.push_back(new_move);
}

/**
@brief 移動関数
@param handle 移動させるハンドル
@param angle 移動角度
@param length 移動距離
@param max_frame 移動時間(フレーム単位)
@note
 handleを角度angleでmax_frameかけてlengthだけ移動させる
**/
void NyaPosition::MoveLengthMode(PositionHandle* handle, double angle, double length, unsigned int max_frame)
{
	PositionMove new_move;

	new_move.frame_ = 0;
	new_move.max_frame_ = max_frame;
	new_move.handle_ = handle;
	new_move.move_x_ = length * cos(AngleToRad(angle)) / max_frame;
	new_move.move_y_ = length * sin(AngleToRad(angle)) / max_frame;
	move_collection_.push_back(new_move);
}

/**
@brief 移動関数
@param handle 移動させるハンドル
@param angle 移動角度
@param speed 移動速度
@param max_frame 移動時間(フレーム単位)
@note
 handleを角度angleでmax_frameかけて速度speedで移動させる
**/
void NyaPosition::MoveSpeedMode(PositionHandle* handle, double angle, double speed, unsigned int max_frame)
{
	PositionMove new_move;

	new_move.frame_ = 0;
	new_move.max_frame_ = max_frame;
	new_move.handle_ = handle;
	new_move.move_x_ = speed * cos(AngleToRad(angle));
	new_move.move_y_ = speed * sin(AngleToRad(angle));
	move_collection_.push_back(new_move);
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
bool NyaPosition::InScreen(PositionHandle* phandle, int gap)
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
void NyaPosition::Run(eEVENT check_event)
{

	switch(check_event)
	{
	case eEVENT::MISSION_CREATE:
	case eEVENT::MISSION_REPLAY_CREATE:
		for (eOBJECT type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; ++type)
			collision_collection_[static_cast<int>(type)].clear();
		move_collection_.clear();
		break;
	case eEVENT::MISSION_RUN:
	case eEVENT::MISSION_REPLAY_RUN:
		// 衝突判定をする前に衝突ダメージを0クリアしておく
		ClearCollisionHit();
		// CollisionSettingで設定したオブジェクトグループの組み合わせで衝突判定をおこなう
		for (auto& e : collision_pair_collection_)
			JudgeCollision(e.first, e.second);
		// 毎フレーム登録されたCollisionHandleSetのクリアをする
		for (eOBJECT type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; ++type)
			collision_collection_[static_cast<int>(type)].clear();
		// 移動処理を指定されたハンドルに対して座標の計算をおこなう
		CalculateMove();
		break;
	}
}

void NyaPosition::CalculateMove(void)
{
	list<PositionMove>::iterator remove_it;
	deque<list<PositionMove>::iterator> gabage_collection;

	for (auto it = move_collection_.begin(); it != move_collection_.end(); ++it)
	{
		it->handle_->grid_x_ += it->move_x_;
		it->handle_->grid_y_ += it->move_y_;
		it->frame_++;
		if (it->max_frame_ <= it->frame_)
			gabage_collection.push_back(it);
	}

	while (!gabage_collection.empty())
	{
		remove_it = gabage_collection.front();
		move_collection_.erase(remove_it);
		gabage_collection.pop_front();
	}
}

void NyaPosition::ClearCollisionHit(void)
{
	for (auto& e : handle_collection_)
	{
		e->collision_hit_damage_ = 0;
		e->collision_hit_x_ = -1000;
		e->collision_hit_y_ = -1000;
	}
}

/**
 @brief 衝突判定を実行する関数
**/
void NyaPosition::JudgeCollision(eOBJECT type1, eOBJECT type2)
{
	for (auto& e1 : collision_collection_[static_cast<int>(type1)])
	{	
		for (auto& e2 : collision_collection_[static_cast<int>(type2)])
		{
			// ２乗してるのでabs不要
			if ((e1->grid_x_ - e2->grid_x_) * (e1->grid_x_ - e2->grid_x_) + (e1->grid_y_ - e2->grid_y_) * (e1->grid_y_ - e2->grid_y_) 
				< (e1->collision_range_ + e2->collision_range_) * (e1->collision_range_ + e2->collision_range_))
			{
				e1->collision_hit_damage_ += e2->collision_power_;
				e2->collision_hit_damage_ += e1->collision_power_;
				e1->collision_hit_handle_ = e2;
				e2->collision_hit_handle_ = e1;
				e1->collision_hit_x_ = e1->grid_x_;
				e1->collision_hit_y_ = e1->grid_y_;
			}
		}
	}
}



