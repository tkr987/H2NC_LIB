#pragma once

#include <list>
#include <vector>
#include <utility>

namespace H2NLIB
{
	enum class eOBJECT;

	//**********************************************************
	// class PositionHandle1
	// ���̃N���X���g���ƊȈՓI�ȏՓ˔�������邱�Ƃ��ł���
	//**********************************************************
	class PositionHandle1 
	{
	public:
		int collision_hit_;				// �Փ˂����Ƃ��ɗ^����ꂽ�_���[�W(1�t���[������0�N���A�����)
		int collision_power_;			// �Փ˂����Ƃ��ɗ^����_���[�W
		int collision_range_;			// �Փ˔͈�
		int health_;					// ���݂̃w���X
		double grid_x_;					// �I�u�W�F�N�g�i�n���h���j��X���W
		double grid_y_;					// �I�u�W�F�N�g�i�n���h���j��Y���W
		PositionHandle1()
		{
			collision_hit_ = 0;
			collision_power_ = 1;
			collision_range_ = 10;
			health_ = 1;
			grid_x_ = -1000;
			grid_y_ = -1000;
		}
	};

	//**********************************************************
	// class PositionHandle2
	// ������
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

	class PositionMove
	{
	public:
		unsigned int frame_;
		unsigned int max_frame_;
		double move_x_;
		double move_y_;
		PositionHandle1* handle1_;
		PositionHandle2* handle2_;
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
	class NyaPosition
	{
	public:
		static void Collide(PositionHandle1* handle, eOBJECT group);
		static void CollisionPair(eOBJECT group1, eOBJECT group2);
		static bool InScreen(PositionHandle1* phx, int gap = 0);
		static void Move(PositionHandle1* handle, double angle, unsigned int max_frame, int length);
		static void Run(void);
	private:
		static std::vector<std::pair<eOBJECT, eOBJECT>> collision_pair_collection_;
		static std::vector<CollisionHandleSet> collision_collection_;
		static std::list<PositionMove> move_collection_;
		static void ClearCollisionHit(eOBJECT object_type);
		static void JudgeCollision1(eOBJECT, eOBJECT);
		static void JudgeCollision2(eOBJECT, eOBJECT);
		static void CalculateMove(void);
		static double AngleToRad(double x) { return (x * 3.14159265359 / 180.0); }

	};


}

