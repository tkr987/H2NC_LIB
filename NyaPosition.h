#pragma once

#include <list>
#include <vector>
#include <utility>
#include "NyaDefine.h"

namespace H2NLIB {


	class PositionHandle1 
	{
	public:
		bool collision_hit_;
		double collision_pow_;
		double collision_range_;
		double health_max_;
		double health_now_;
		double grid_x_;
		double grid_y_;
		PositionHandle1()
		{
			collision_hit_ = false;
			collision_pow_ = 1;
			collision_range_ = 10;
			health_max_ = 1;
			health_now_ = 1;
			grid_x_ = 0;
			grid_y_ = 0;
		}
	};

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

	class NyaPosition {
	public:
		NyaPosition();
		~NyaPosition();
		void Collision(PositionHandle1* handle, eOBJECT::NUM group);
		void Delete(PositionHandle1* handle);
		void Delete(PositionHandle2* handle);
		void Init(void);
		bool InScreen(PositionHandle1* phx, int gap = 0);
		void SettingCollision(eOBJECT::NUM group1, eOBJECT::NUM group2);
		void Regist(PositionHandle1* handle);
		void Regist(PositionHandle2* handle);
		void Run(void);
	private:
		static std::vector<std::pair<eOBJECT::NUM, eOBJECT::NUM>> collision_group_vector_;
		static std::vector<PositionHandle1*> collision_vector1_[eOBJECT::NUM::sizeof_enum];
		static std::vector<PositionHandle2*> collision_vector2_[eOBJECT::NUM::sizeof_enum];
		static std::list<PositionHandle1*> regist_list1_;
		static std::list<PositionHandle2*> regist_list2_;
		void JudgeCollision1(eOBJECT::NUM, eOBJECT::NUM);
		void JudgeCollision2(eOBJECT::NUM, eOBJECT::NUM);
	};


}

