#include <cmath>
#include <tuple>
#include "NyaEnum.h"
#include "NyaPosition.h"

using namespace std;
using namespace H2NLIB;

vector<pair<eOBJECT, eOBJECT>> NyaPosition::collision_group_combination_;
vector<CollisionHandleSet> NyaPosition::collision_collection_(static_cast<int>(eOBJECT::sizeof_enum));

/**
 @brief �Փ˔��菈������n���h����o�^����֐�
 @param phandle �Փ˔��菈������n���h��
 @param group �Փ˔��肷��n���h���̃I�u�W�F�N�g�O���[�v
 @note
  phandle��group�Ƃ��ēo�^���A�Փ˔��菈�������s����
  �Ȃ��A�o�^���ꂽ�n���h���̓t���[�����ɃN���A�����̂ŁA
  ���菈���������������Ƃ��͂P�t���[������Collision()�œo�^�������K�v������
**/
void NyaPosition::Collision(PositionHandle1* phandle, eOBJECT group)
{
	phandle->collision_hit_ = false;
	collision_collection_[static_cast<int>(group)].handle1_collection_.push_back(phandle);
}

/**
 @brief �Փ˔��������I�u�W�F�N�g�̑g�ݍ��킹��ݒ肷��֐�
 @param group1 �Փ˔��������I�u�W�F�N�g�̃O���[�v�P
 @param group2 �Փ˔��������I�u�W�F�N�g�̃O���[�v�Q
 @note
  ���̊֐��̈������g���Đݒ肷��ƁA
  group1�̃I�u�W�F�N�g��group2�̃I�u�W�F�N�g���m�ŏՓ˔��������悤�ɂȂ�
**/
void NyaPosition::CollisionSetting(eOBJECT group1, eOBJECT group2)
{
	pair<eOBJECT, eOBJECT> set;

	// ���łɓ����I�u�W�F�N�g�O���[�v���ݒ肳��Ă��牽�����Ȃ��ŏI��
	for (auto& e : collision_group_combination_) {
		if (e.first == group1 && e.second == group2)
			return;
		if (e.first == group2 && e.second == group1)
			return;
	}

	set.first = group1;
	set.second = group2;
	collision_group_combination_.push_back(set);
}

/**
 @brief ��ʗ̈�����ǂ������ׂ�֐�
 @param phandle ��ʓ����ǂ������ׂ�n���h��
 @param gap ��ʗ̈�̃M���b�v
 @note
  phandle����ʗ̈���ɂ��邩�ǂ������ׂ邱�Ƃ��ł���
  gap�ɐ��̒l���w�肷��Ɣ��肷���ʗ̈���g��ł���
  gap�ɕ��̒l���w�肷��Ɣ��肷���ʗ̈���k���ł���
**/
bool NyaPosition::InScreen(PositionHandle1* phandle, int gap)
{
	if (phandle->grid_x_ < SCREEN_MIN_X - gap)
		return false;
	if (SCREEN_MAX_X + gap < phandle->grid_x_)
		return false;
	if (phandle->grid_y_ < SCREEN_MIN_Y - gap)
		return false;
	if (SCREEN_MAX_Y + gap < phandle->grid_y_)
		return false;

	return true;
}

/**
 @brief ���s�֐�
 @note
  ���C�u������NyaWindow�N���X���Ŏ����I�ɌĂ΂��̂ŁA���C�u�����g�p�҂��ĂԕK�v�͂Ȃ�
**/
void NyaPosition::Run(void)
{
	// CollisionSetting�Őݒ肵���I�u�W�F�N�g�O���[�v�̑g�ݍ��킹�ŏՓ˔���������Ȃ�
	for (auto& e : collision_group_combination_)
		JudgeCollision1(e.first, e.second);

	// ���t���[��CollisionHandleSet�̃N���A������
	for (auto& e : collision_collection_) 
		e.handle1_collection_.clear();
}

/**
 @brief �Փ˔�������s����֐��P
 @note
  �ȈՓI�ȏՓ˔��菈��������
**/
void NyaPosition::JudgeCollision1(eOBJECT object_group1, eOBJECT object_group2)
{
	for (auto& e1 : collision_collection_[static_cast<int>(object_group1)].handle1_collection_)
	{	
		for (auto& e2 : collision_collection_[static_cast<int>(object_group2)].handle1_collection_)
		{
			// �Q�悵�Ă�̂�abs�s�v
			if ((e1->grid_x_ - e2->grid_x_) * (e1->grid_x_ - e2->grid_x_) + (e1->grid_y_ - e2->grid_y_) * (e1->grid_y_ - e2->grid_y_) 
				< (e1->collision_range_ + e2->collision_range_) * (e1->collision_range_ + e2->collision_range_))
			{
				e1->health_now_ -= e2->collision_damage_;
				e2->health_now_ -= e1->collision_damage_;
				e1->collision_hit_ = true;
				e2->collision_hit_ = true;
			}
		}
	}
}

/**
 @brief �Փ˔�������s����֐��Q
 @note
  ������
**/
void NyaPosition::JudgeCollision2(eOBJECT object_group1, eOBJECT object_group2)
{
	//double a, b, c;
	//double distance;

	//for (auto it1 = collision_vector2_[static_cast<int>(object_group1)].begin(); it1 != collision_vector2_[static_cast<int>(object_group1)].end(); ++it1) {	
	//	for (auto it2 = collision_vector2_[static_cast<int>(object_group2)].begin(); it2 != collision_vector2_[static_cast<int>(object_group2)].end(); ++it2) {

	//		a = ((*it1)->grid_y_ - (*it1)->grid_y_pre_) /  ((*it1)->grid_x_ - (*it1)->grid_x_pre_);
	//		b = -1;
	//		c = (*it1)->grid_y_pre_ - ((*it1)->grid_x_pre_ * ((*it1)->grid_y_ - (*it1)->grid_y_pre_)) / ((*it1)->grid_x_ - (*it1)->grid_x_pre_);

	//		distance = abs(((a * (*it2)->grid_x_) + (b * (*it2)->grid_y_) + c)) / sqrt(pow(a,2) + pow(b,2));


	//		if ((*it2)->grid_x_ < (*it1)->grid_x_ && (*it2)->grid_x_ < (*it1)->grid_x_pre_)
	//			continue;
	//		if ((*it1)->grid_x_ < (*it2)->grid_x_ && (*it1)->grid_x_pre_ < (*it2)->grid_x_)
	//			continue;
	//		if ((*it2)->grid_y_ < (*it1)->grid_y_ && (*it2)->grid_y_ < (*it1)->grid_y_pre_)
	//			continue;
	//		if ((*it1)->grid_y_ < (*it2)->grid_y_ && (*it1)->grid_y_pre_ < (*it2)->grid_y_)
	//			continue;

	//		if(distance < (*it1)->collision_range_+ (*it2)->collision_range_) {
	//
	//			(*it1)->health_now_ -= (*it2)->collision_pow_;
	//			(*it2)->health_now_ -= (*it1)->collision_pow_;
	//		}
	//	}
	//}
}

