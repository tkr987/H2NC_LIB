#include <cmath>
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;

vector<tuple<int, eOBJECT::GROUP, eOBJECT::GROUP>> NyaPosition::collision_group_vector_;
vector<PositionPropertyX*> NyaPosition::collision_vector_[eOBJECT::GROUP::sizeof_enum];
list<PositionPropertyX> NyaPosition::create_list_;

NyaPosition::NyaPosition()
{

}


NyaPosition::~NyaPosition()
{

}


void NyaPosition::Collide(PositionPropertyX* ppx)
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
	for (auto it = collision_group_vector_.begin(); it != collision_group_vector_.end(); ++it) {
		if (get<0>(*it) == 1) {
			CollisionType1(get<1>(*it), get<2>(*it));
		} else if (get<0>(*it) == 2) {
		
		} else if (get<0>(*it) == 3) {
		
		}
	}	
}

/**
 �Փ˔���ݒ�֐�
 @param collision_type �Փ˔��菈���̎��
 @param group1 �Z�b�g����l�P
 @param group2 �Z�b�g����l�Q
 @note
 �ǂ̃I�u�W�F�N�g�O���[�v���m�ŏՓ˔��菈��������̂��ݒ肷�邽�߂Ɏg�p����֐��B
 �Փ˔��菈���̎�ނ�
 1 �O�����̏Փ˔��菈��
 2 �ȗ������ꂽ�����Փ˔��菈��
 �Ⴆ�΁AeOBJECT::GROUP::USER��eOBJECT::GROUP::TARGET_ATTACK�������Ŏw�肵�Ă����΁A
 NyaPosition::Run()�ɂ�USER��TARGET_ATTACK�̃I�u�W�F�N�g���m�̏Փ˔�������s����悤�ɂȂ�B
**/
void NyaPosition::SettingCollision(int collision_type, eOBJECT::GROUP group1, eOBJECT::GROUP group2)
{
	tuple<int, eOBJECT::GROUP, eOBJECT::GROUP> set;

	// ���łɓ����I�u�W�F�N�g�O���[�v���ݒ肳��Ă��牽�����Ȃ��ŏI��
	for (auto it = collision_group_vector_.begin(); it != collision_group_vector_.end(); ++it) {
		if (get<1>(*it) == group1 && get<2>(*it) == group2)
			return;
		if (get<1>(*it) == group2 && get<2>(*it) == group1)
			return;
	}

	// �I�u�W�F�N�g�O���[�v���Z�b�g����
	get<0>(set) = collision_type;
	get<1>(set) = group1;
	get<1>(set) = group2;
	collision_group_vector_.push_back(set);
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


