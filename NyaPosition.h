#pragma once

#include <list>
#include <vector>
#include <utility>

namespace H2NLIB
{
	enum class eOBJECT;

	//**********************************************************
	// class PositionHandle
	// このクラスを使うと衝突判定をすることができる
	//**********************************************************
	class PositionHandle
	{
	public:
		int collision_hit_damage_;		// 衝突判定trueになったときに受けたダメージ(1フレーム毎に0クリアされる)
		double collision_hit_x_;		// 衝突判定trueになったときのx座標(1フレーム毎に0クリアされる)
		double collision_hit_y_;		// 衝突判定trueになったときのy座標(1フレーム毎に0クリアされる)
		int collision_power_;			// 衝突判定trueになったときに与えるダメージ
		int collision_range_;			// 衝突範囲
		int health_;					// 現在のヘルス
		double grid_x_;					// オブジェクト（ハンドル）のX座標
		double grid_y_;					// オブジェクト（ハンドル）のY座標
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
		static void Collide(PositionHandle* handle, eOBJECT group);
		static void CollisionPair(eOBJECT group1, eOBJECT group2);
		static bool InScreen(PositionHandle* phx, int gap = 0);
		static void MoveAngleMode(PositionHandle* handle, double angle, double length, unsigned int max_frame);
		static void MoveGridMode(PositionHandle* handle, double end_x, double end_y, unsigned int max_frame);
		static void Run(void);
	private:
		static std::vector<std::pair<eOBJECT, eOBJECT>> collision_pair_collection_;
		static std::vector<PositionHandle*> collision_collection_[static_cast<int>(eOBJECT::sizeof_enum)];
		static std::list<PositionMove> move_collection_;
		static void ClearCollisionHit(eOBJECT object_type);
		static void JudgeCollision(eOBJECT, eOBJECT);
		static void CalculateMove(void);
		static double AngleToRad(double x) { return (x * 3.14159265359 / 180.0); }

	};


}

