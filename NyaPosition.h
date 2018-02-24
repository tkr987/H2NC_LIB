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
	};

	class NyaPosition {
	public:
		NyaPosition();
		~NyaPosition();
		void Collision(PositionHandleX* phx, eOBJECT::GROUP group);
		PositionHandleX* Create(void);
		void SettingCollision(eOBJECT::GROUP group1, eOBJECT::GROUP group2);
		void SettingCollisionHighAccuracy(eOBJECT::GROUP group);
		void Run(void);
	private:
		static std::vector<std::pair<eOBJECT::GROUP, eOBJECT::GROUP>> collision_group_vector_;
		static std::vector<eOBJECT::GROUP> collision_high_accuracy_group_vector_;
		static std::vector<PositionHandleX*> collision_vector_[eOBJECT::GROUP::sizeof_enum];
		static std::list<PositionHandleX> create_list_;
		void JudgeCollision(eOBJECT::GROUP, eOBJECT::GROUP);
		void JudgeCollisionHighAccuracy(eOBJECT::GROUP, eOBJECT::GROUP);
	};


}

