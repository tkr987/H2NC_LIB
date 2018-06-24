#include <cmath>
#include <deque>
#include <tuple>
#include "NyaEnum.h"
#include "NyaPosition.h"

using namespace std;
using namespace H2NLIB;

vector<pair<eOBJECT, eOBJECT>> NyaPosition::collision_pair_collection_;
vector<PositionHandle*> NyaPosition::collision_collection_[static_cast<int>(eOBJECT::sizeof_enum)];
list<PositionMove> NyaPosition::move_collection_;

/**
 @brief �Փ˔��菈������n���h����o�^����֐�
 @param phandle �Փ˔��菈������n���h��
 @param type �Փ˔��肷��n���h���̃I�u�W�F�N�g�̃^�C�v
 @note
  phandle��group�Ƃ��ēo�^���A�Փ˔��菈�������s����
  �Ȃ��A�o�^���ꂽ�n���h���̓t���[�����ɃN���A�����̂ŁA
  ���菈���������������Ƃ��͂P�t���[������Collision()�œo�^�������K�v������
**/
void NyaPosition::Collide(PositionHandle* phandle, eOBJECT type)
{
	collision_collection_[static_cast<int>(type)].push_back(phandle);
}

/**
 @brief �Փ˔��������I�u�W�F�N�g�̑g�ݍ��킹��ݒ肷��֐�
 @param type1 �Փ˔��������I�u�W�F�N�g�̃^�C�v�P
 @param type2 �Փ˔��������I�u�W�F�N�g�̃^�C�v�Q
 @note
  ���̊֐��̈������g���Đݒ肷��ƁA
  group1�̃I�u�W�F�N�g��group2�̃I�u�W�F�N�g���m�ŏՓ˔��������悤�ɂȂ�
**/
void NyaPosition::CollisionPair(eOBJECT type1, eOBJECT type2)
{
	pair<eOBJECT, eOBJECT> set;

	// ���łɓ����I�u�W�F�N�g�O���[�v���ݒ肳��Ă��牽�����Ȃ��ŏI��
	for (auto& e : collision_pair_collection_) {
		if (e.first == type1 && e.second == type2)
			return;
		if (e.first == type2 && e.second == type1)
			return;
	}

	set.first = type1;
	set.second = type2;
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
void NyaPosition::MoveAngleMode(PositionHandle* handle, double angle, int length, unsigned int max_frame)
{
	PositionMove new_move;

	new_move.frame_ = 0;
	new_move.max_frame_ = max_frame;
	new_move.handle_ = handle;
	new_move.move_x_ = length * cos(AngleToRad(angle)) / max_frame;
	new_move.move_y_ = length * sin(AngleToRad(angle)) / max_frame;
	move_collection_.push_back(new_move);
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
void NyaPosition::MoveGridMode(PositionHandle* handle, int end_x,  int end_y, unsigned int max_frame)
{
	PositionMove new_move;

	new_move.frame_ = 0;
	new_move.max_frame_ = max_frame;
	new_move.handle_ = handle;
	new_move.move_x_ = ((double)end_x - (double)handle->grid_x_) / (double)max_frame;
	new_move.move_y_ = ((double)end_y - (double)handle->grid_y_) / (double)max_frame;
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
bool NyaPosition::InScreen(PositionHandle* phandle, int gap)
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
		JudgeCollision(e.first, e.second);

	// ���t���[���o�^���ꂽCollisionHandleSet�̃N���A������
	for (eOBJECT type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; ++type)
		collision_collection_[static_cast<int>(type)].clear();

	// �ړ��������w�肳�ꂽ�n���h���ɑ΂��č��W�̌v�Z�������Ȃ�
	CalculateMove();
}

void H2NLIB::NyaPosition::CalculateMove(void)
{
	list<PositionMove>::iterator remove_it;
	deque<list<PositionMove>::iterator> gabage_collection;

	for (auto it = move_collection_.begin(); it != move_collection_.end(); ++it)
	{
		it->handle_->grid_x_ += it->move_x_;
		it->handle_->grid_y_ += it->move_y_;
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

void NyaPosition::ClearCollisionHit(eOBJECT type)
{
	for (auto& e : collision_collection_[static_cast<int>(type)])
	{
		e->collision_hit_damage_ = 0;
		e->collision_hit_x_ = -1000;
		e->collision_hit_y_ = -1000;
	}
}


/**
 @brief �Փ˔�������s����֐�
**/
void NyaPosition::JudgeCollision(eOBJECT type1, eOBJECT type2)
{
	for (auto& e1 : collision_collection_[static_cast<int>(type1)])
	{	
		for (auto& e2 : collision_collection_[static_cast<int>(type2)])
		{
			// �Q�悵�Ă�̂�abs�s�v
			if ((e1->grid_x_ - e2->grid_x_) * (e1->grid_x_ - e2->grid_x_) + (e1->grid_y_ - e2->grid_y_) * (e1->grid_y_ - e2->grid_y_) 
				< (e1->collision_range_ + e2->collision_range_) * (e1->collision_range_ + e2->collision_range_))
			{
				e1->collision_hit_damage_ += e2->collision_power_;
				e2->collision_hit_damage_ += e1->collision_power_;
				e1->collision_hit_x_ = e1->grid_x_;
				e1->collision_hit_y_ = e1->grid_y_;
				e1->health_ -= e2->collision_power_;
				e2->health_ -= e1->collision_power_;
			}
		}
	}
}



