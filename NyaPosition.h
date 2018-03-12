#pragma once

#include <list>
#include <vector>
#include <utility>
#include "NyaDefine.h"


namespace H2NLIB {


	class PositionHandleX {
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
		PositionHandleX()
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
		void Collision(PositionHandleX* phx, eOBJECT::NUM group);
		PositionHandleX* Create(void);
		void SettingCollision(eOBJECT::NUM group1, eOBJECT::NUM group2);
		void SettingCollisionHighAccuracy(eOBJECT::NUM group);
		void Run(void);
	private:
		static std::vector<std::pair<eOBJECT::NUM, eOBJECT::NUM>> collision_group_vector_;
		static std::vector<eOBJECT::NUM> collision_high_accuracy_group_vector_;
		static std::vector<PositionHandleX*> collision_vector_[eOBJECT::NUM::sizeof_enum];
		static std::list<PositionHandleX> create_list_;
		void JudgeCollision(eOBJECT::NUM, eOBJECT::NUM);
		void JudgeCollisionHighAccuracy(eOBJECT::NUM, eOBJECT::NUM);
	};


}

