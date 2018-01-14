#include <cmath>
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;

int NyaPosition::collision_type_[eOBJECT::GROUP::sizeof_enum] = {};
vector<PositionPropertyX*> NyaPosition::collision_vector_[eOBJECT::GROUP::sizeof_enum];
list<PositionPropertyX> NyaPosition::create_list_;

NyaPosition::NyaPosition()
{
	static bool first_call = true;

	if (first_call) {
		nya_string_ = new NyaString;
		nya_string_->Init("position-font", 10, 2);
		first_call = false;
	}
}


NyaPosition::~NyaPosition()
{
	delete nya_string_;
}


void NyaPosition::Collision(PositionPropertyX* ppx)
{
	collision_vector_->push_back(ppx);
}


PositionPropertyX* NyaPosition::Create(void) 
{
	static PositionPropertyX ppx;

	create_list_.insert(create_list_.begin(), ppx);

	return &(*create_list_.begin());
}

void NyaPosition::Delete(PositionPropertyX* ppx)
{


}


void NyaPosition::Run(void)
{
	auto it = create_list_.begin();
	nya_string_->Write("position-font", 50, 50, "posision_x = %d", (int)it->x_);
}



void NyaPosition::CollisionType1(eOBJECT::GROUP object_group1, eOBJECT::GROUP object_group2)
{
	PositionPropertyX* ppx1;
	PositionPropertyX* ppx2;

	for (auto it = collision_vector_[object_group1].begin(); it != collision_vector_[object_group1].end(); ++it) {	
		for (auto it = collision_vector_[object_group2].begin(); it != collision_vector_[object_group2].end(); ++it) {

			if (pow(ppx1->x_ - ppx2->x_, 2.0) + pow(ppx1->y_ - ppx2->y_, 2.0) < pow(ppx1->range_ + ppx2->range_, 2.0)) {
				ppx1->health_now_ -= ppx2->pow_;
				ppx2->health_now_ -= ppx1->pow_;
			}
		}
	}
}


