#pragma once

#include <list>
#include <vector>
#include "NyaDefine.h"

namespace H2NLIB {

	class NyaPosition;
	class NyaString;

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
		void Collision(PositionPropertyX*);
		PositionPropertyX* Create(void);
		void Delete(PositionPropertyX*);
		void Run(void);
	private:
		static int collision_type_[eOBJECT::GROUP::sizeof_enum];
		static std::vector<PositionPropertyX*> collision_vector_[eOBJECT::GROUP::sizeof_enum];
		NyaString* nya_string_;
		static std::list<PositionPropertyX> create_list_;
		void CollisionType1(eOBJECT::GROUP, eOBJECT::GROUP);
	};


}

