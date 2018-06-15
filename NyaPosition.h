#pragma once

#include <vector>
#include <utility>

namespace H2NLIB
{
	enum class eOBJECT;

	//**********************************************************
	// class PositionHandle1
	// このクラスを使うと簡易的な衝突判定をすることができる
	//**********************************************************
	class PositionHandle1 
	{
	public:
		int collision_hit_;			// 衝突したときに与えられたダメージ(1フレーム毎に0クリアされる)
		int collision_power_;		// 衝突したときに与えるダメージ
		int collision_range_;		// 衝突範囲
		int health_;				// 現在のヘルス
		double grid_x_;				// オブジェクト（ハンドル）のX座標
		double grid_y_;				// オブジェクト（ハンドル）のY座標
		PositionHandle1()
		{
			collision_hit_ = 0;
			collision_power_ = 1;
			collision_range_ = 10;
			health_ = 1;
			grid_x_ = 0;
			grid_y_ = 0;
		}
	};

	//**********************************************************
	// class PositionHandle2
	// 未完成
	//**********************************************************
	class PositionHandle2 
	{
	public:
		bool collision_hit_;
		double collision_pow_;
		double collision_range_;
		double health_;
		double grid_x_;
		double grid_x_pre_;
		double grid_y_;
		double grid_y_pre_;
		PositionHandle2()
		{
			collision_hit_ = false;
			collision_pow_ = 1;
			collision_range_ = 10;
			health_ = 1;
			grid_x_ = 0;
			grid_x_pre_ = 0;
			grid_y_ = 0;
			grid_y_pre_ = 0;
		}
	};

	//**********************************************************
	// class CollisionHandleSet
	//**********************************************************
	class CollisionHandleSet
	{
	public:
		std::vector<PositionHandle1*> handle1_collection_;
		std::vector<PositionHandle2*> handle2_collection_;
	};

	//**********************************************************
	// class NyaPosition
	//**********************************************************
	class NyaPosition {
	public:
		static void Collision(PositionHandle1* handle, eOBJECT group);
		static void CollisionSetting(eOBJECT group1, eOBJECT group2);
		static bool InScreen(PositionHandle1* phx, int gap = 0);
		static void Run(void);
	private:
		static std::vector<std::pair<eOBJECT, eOBJECT>> collision_group_combination_;
		static std::vector<CollisionHandleSet> collision_collection_;
		static void ClearCollisionHit(eOBJECT object_type);
		static void JudgeCollision1(eOBJECT, eOBJECT);
		static void JudgeCollision2(eOBJECT, eOBJECT);
	};


}

