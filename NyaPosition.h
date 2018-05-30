#pragma once

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
		bool collision_hit_;		// �Փ˂������ǂ���
		double collision_damage_;	// �Փ˂����Ƃ��ɗ^����_���[�W
		double collision_range_;	// �Փ˔͈�
		double health_max_;			// �w���X�ő�l
		double health_now_;			// ���݂̃w���X
		double grid_x_;				// �I�u�W�F�N�g�i�n���h���j��X���W
		double grid_y_;				// �I�u�W�F�N�g�i�n���h���j��Y���W
		PositionHandle1()
		{
			collision_hit_ = false;
			collision_damage_ = 1;
			collision_range_ = 10;
			health_max_ = 1;
			health_now_ = 1;
			grid_x_ = 0;
			grid_y_ = 0;
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
		double health_max_;
		double health_now_;
		double grid_x_;
		double grid_x_pre_;
		double grid_y_;
		double grid_y_pre_;
		PositionHandle2()
		{
			collision_hit_ = false;
			collision_pow_ = 1;
			collision_range_ = 10;
			health_max_ = 1;
			health_now_ = 1;
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
		static void JudgeCollision1(eOBJECT, eOBJECT);
		static void JudgeCollision2(eOBJECT, eOBJECT);
	};


}

