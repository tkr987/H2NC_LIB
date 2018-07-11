#pragma once

#include <list>
#include <string>
#include <vector>
#include <utility>

#include "NyaEnum.h"

namespace HNLIB
{
	//**********************************************************
	// class PositionHandle
	// このクラスを使うと衝突判定をすることができる
	//**********************************************************
	class PositionHandle
	{
	public:
		int collision_hit_damage_;					// 衝突判定trueになったときに受けたダメージ(1フレーム毎に0クリアされる)
		PositionHandle* collision_hit_handle_;		// 衝突判定trueになったときの相手のハンドル
		double collision_hit_x_;					// 衝突判定trueになったときのx座標(1フレーム毎に0クリアされる)
		double collision_hit_y_;					// 衝突判定trueになったときのy座標(1フレーム毎に0クリアされる)
		int collision_power_;						// 衝突判定trueになったときに与えるダメージ
		int collision_range_;						// 衝突範囲
		int health_;								// 現在のヘルス
		double grid_x_;								// オブジェクト（ハンドル）のX座標
		double grid_y_;								// オブジェクト（ハンドル）のY座標
		std::string name_;							// ハンドルの名前
		PositionHandle()
		{
			collision_hit_damage_ = 0;
			collision_hit_x_ = 0;
			collision_hit_y_ = 0;
			collision_power_ = 1;
			collision_range_ = 10;
			health_ = 1;
			grid_x_ = -1000;
			grid_y_ = -1000;
		}
	};

	class PositionMove
	{
	public:
		unsigned int frame_;
		unsigned int max_frame_;
		double move_x_;
		double move_y_;
		PositionHandle* handle_;
	};

	//**********************************************************
	// class NyaPosition
	//**********************************************************
	class NyaPosition
	{
	public:
		static double Angle(PositionHandle* handle1, PositionHandle* handle2);
		static void Collide(PositionHandle* handle, eOBJECT type);
		static void CollisionPair(eOBJECT type1, eOBJECT type2);
		static PositionHandle* CreateHandle(void);
		static void CreateHandle(PositionHandle* new_handle);
		static void DeleteHandle(PositionHandle* delete_handle);
		static int FindHandle(std::string name, PositionHandle* handle);
		static int FindHandle(std::string name, std::vector<PositionHandle>* handle_collection);
		static bool InScreen(PositionHandle* handle, int gap = 0);
		static void MoveGridMode(PositionHandle* handle, double end_x, double end_y, unsigned int max_frame);
		static void MoveLengthMode(PositionHandle* handle, double angle, double length, unsigned int max_frame);
		static void MoveSpeedMode(PositionHandle* handle, double angle, double speed, unsigned int max_frame);
		static void Run(eEVENT check_event);
	private:
		static std::vector<std::pair<eOBJECT, eOBJECT>> collision_pair_collection_;
		static std::vector<PositionHandle*> collision_collection_[static_cast<int>(eOBJECT::sizeof_enum)];
		static std::list<PositionHandle*> handle_collection_;
		static std::list<PositionMove> move_collection_;
		static void ClearCollisionHit(void);
		static void JudgeCollision(eOBJECT, eOBJECT);
		static void CalculateMove(void);
		static double AngleToRad(double x) { return (x * 3.14159265359 / 180.0); }
		static double RadToAngle(double x) { return (x * 180.0 / 3.14159265359); }
	};


}

