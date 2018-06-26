#pragma once

#include <list>
#include <vector>
#include <utility>

namespace H2NLIB
{
	enum class eOBJECT;

	//**********************************************************
	// class PositionHandle
	// ���̃N���X���g���ƏՓ˔�������邱�Ƃ��ł���
	//**********************************************************
	class PositionHandle
	{
	public:
		int collision_hit_damage_;		// �Փ˔���true�ɂȂ����Ƃ��Ɏ󂯂��_���[�W(1�t���[������0�N���A�����)
		double collision_hit_x_;		// �Փ˔���true�ɂȂ����Ƃ���x���W(1�t���[������0�N���A�����)
		double collision_hit_y_;		// �Փ˔���true�ɂȂ����Ƃ���y���W(1�t���[������0�N���A�����)
		int collision_power_;			// �Փ˔���true�ɂȂ����Ƃ��ɗ^����_���[�W
		int collision_range_;			// �Փ˔͈�
		int health_;					// ���݂̃w���X
		double grid_x_;					// �I�u�W�F�N�g�i�n���h���j��X���W
		double grid_y_;					// �I�u�W�F�N�g�i�n���h���j��Y���W
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

