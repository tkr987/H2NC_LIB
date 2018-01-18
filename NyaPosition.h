#pragma once

#include <list>
#include <tuple>
#include <vector>
#include "NyaDefine.h"

namespace H2NLIB {

	class NyaPosition;

	struct PositionPropertyX {
		double health_now_;
		double health_max_;
		double pow_;
		double range_;
		double x_;
		double y_;
		eOBJECT::GROUP object_group_;
	};

	class NyaPosition {
	public:
		NyaPosition();
		~NyaPosition();
		void Collide(PositionPropertyX*);
		PositionPropertyX* Create(void);
		void Delete(PositionPropertyX*);
		void SettingCollision(int collision_type, eOBJECT::GROUP group1, eOBJECT::GROUP group2);
		void Run(void);
	private:
		static std::vector<std::tuple<int, eOBJECT::GROUP, eOBJECT::GROUP>> collision_group_vector_;
		static std::vector<PositionPropertyX*> collision_vector_[eOBJECT::GROUP::sizeof_enum];
		static std::list<PositionPropertyX> create_list_;
		void CollisionType1(eOBJECT::GROUP, eOBJECT::GROUP);
	};


}

