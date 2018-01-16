#include <cmath>
#include <tuple>
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
		nya_string_->SetFont("position-font", 10, 2);
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
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	auto it = create_list_.begin();
	nya_string_->Write("position-font", white, 50, 50, "posision_x = %d", (int)it->x_);
}



void NyaPosition::CollisionType1(eOBJECT::GROUP object_group1, eOBJECT::GROUP object_group2)
{

	for (auto it1 = collision_vector_[object_group1].begin(); it1 != collision_vector_[object_group1].end(); ++it1) {	
		for (auto it2 = collision_vector_[object_group2].begin(); it2 != collision_vector_[object_group2].end(); ++it2) {

			if (pow((*it1)->x_ - (*it2)->x_, 2.0) + pow((*it1)->y_ - (*it2)->y_, 2.0) < pow((*it1)->range_ + (*it2)->range_, 2.0)) {
				(*it1)->health_now_ -= (*it2)->pow_;
				(*it1)->health_now_ -= (*it2)->pow_;
			}
		}
	}
}


