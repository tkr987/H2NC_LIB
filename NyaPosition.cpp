#include <cmath>
#include <deque>
#include <tuple>
#include "NyaEnum.h"
#include "NyaPosition.h"

using namespace std;
using namespace H2NLIB;

vector<pair<eOBJECT, eOBJECT>> NyaPosition::collision_pair_collection_;
vector<CollisionHandleSet> NyaPosition::collision_collection_(static_cast<int>(eOBJECT::sizeof_enum));
list<PositionMove> NyaPosition::move_collection_;

/**
 @brief �Փ˔��菈������n���h����o�^����֐�
 @param phandle �Փ˔��菈������n���h��
 @param group �Փ˔��肷��n���h���̃I�u�W�F�N�g�O���[�v
 @note
  phandle��group�Ƃ��ēo�^���A�Փ˔��菈�������s����
  �Ȃ��A�o�^���ꂽ�n���h���̓t���[�����ɃN���A�����̂ŁA
  ���菈���������������Ƃ��͂P�t���[������Collision()�œo�^�������K�v������
**/
void NyaPosition::Collide(PositionHandle1* phandle, eOBJECT group)
{
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
void NyaPosition::CollisionPair(eOBJECT group1, eOBJECT group2)
{
	pair<eOBJECT, eOBJECT> set;

	// ���łɓ����I�u�W�F�N�g�O���[�v���ݒ肳��Ă��牽�����Ȃ��ŏI��
	for (auto& e : collision_pair_collection_) {
		if (e.first == group1 && e.second == group2)
			return;
		if (e.first == group2 && e.second == group1)
			return;
	}

	set.first = group1;
	set.second = group2;
	collision_pair_collection_.push_back(set);
}

/**
@brief �ړ��֐�
@param handle �ړ�������n���h��
@param angle �ړ��p�x
@param max_frame �ړ�����(�t���[���P��)
@param length �ړ�����
@note
 handle���p�xangle��max_frame������length�����ړ�������
**/
void NyaPosition::Move(PositionHandle1* handle, double angle, unsigned int max_frame, int length)
{
	PositionMove new_move;

	new_move.frame_ = 0;
	new_move.max_frame_ = max_frame;
	new_move.handle1_ = handle;
	new_move.handle2_ = nullptr;
	new_move.move_x_ = length * cos(AngleToRad(angle)) / max_frame;
	new_move.move_y_ = length * sin(AngleToRad(angle)) / max_frame;
	move_collection_.push_back(new_move);
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
	// �Փ˔��������O�ɏՓ˃_���[�W��0�N���A���Ă���
	for (eOBJECT type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; ++type)
		ClearCollisionHit(type);

	// CollisionSetting�Őݒ肵���I�u�W�F�N�g�O���[�v�̑g�ݍ��킹�ŏՓ˔���������Ȃ�
	for (auto& e : collision_pair_collection_)
		JudgeCollision1(e.first, e.second);

	// ���t���[���o�^���ꂽCollisionHandleSet�̃N���A������
	for (auto& e : collision_collection_) 
		e.handle1_collection_.clear();

	// �ړ��������w�肳�ꂽ�n���h���ɑ΂��č��W�̌v�Z�������Ȃ�
	CalculateMove();
}

void H2NLIB::NyaPosition::CalculateMove(void)
{
	list<PositionMove>::iterator remove_it;
	deque<list<PositionMove>::iterator> gabage_collection;

	for (auto it = move_collection_.begin(); it != move_collection_.end(); ++it)
	{
		if (it->handle1_ != nullptr)
		{
			it->handle1_->grid_x_ += it->move_x_;
			it->handle1_->grid_y_ += it->move_y_;
		}
		else
		{
			it->handle2_->grid_x_ += it->move_x_;
			it->handle2_->grid_y_ += it->move_y_;
		}
		it->frame_++;
		if (it->max_frame_ <= it->frame_)
			gabage_collection.push_back(it);
	}

	while (!gabage_collection.empty())
	{
		remove_it = gabage_collection.front();
		move_collection_.erase(remove_it);
		gabage_collection.pop_front();
	}
}

void NyaPosition::ClearCollisionHit(eOBJECT object_type)
{
	for (auto& e : collision_collection_[static_cast<int>(object_type)].handle1_collection_)
		e->collision_hit_ = 0;
	for (auto& e : collision_collection_[static_cast<int>(object_type)].handle2_collection_)
		e->collision_hit_ = 0;
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
				e1->collision_hit_ += e2->collision_power_;
				e2->collision_hit_ += e1->collision_power_;
				e1->health_ -= e2->collision_power_;
				e2->health_ -= e1->collision_power_;
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



