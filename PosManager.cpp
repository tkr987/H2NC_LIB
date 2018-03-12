#include <math.h>
#include <utility>
#include <stdexcept>
#include "PosManager.h"
#include "DebugPrint.h"

#define POS_TOKEN_MAXSIZE 16384

using namespace NH2;
using namespace std;
double PosManager::axis_x_;
double PosManager::axis_y_;
double PosManager::move_axis_x_;
double PosManager::move_axis_y_;
int PosManager::swing_scale_y_;
int PosManager::swing_time_y_;
list<PosToken> PosManager::list_unused_;
list<PosToken> PosManager::list_used_[eOBJECT::NUM::sizeof_enum];


void PosManager::Clear(void)
{
	PosToken ptoken;

	axis_x_ = 0;
	axis_y_ = 0;
	move_axis_x_ = 0;
	move_axis_y_ = 0;
	swing_scale_y_ = 0;
	swing_time_y_ = 0;

	// ���X�g�̗v�f�S����
	list_unused_.clear();
	for (int group = eOBJECT::NUM::enum_zero; group != eOBJECT::NUM::sizeof_enum; group++)
		list_used_[group].clear();

	// �V�K���X�g����
	for (int n = 0; n < POS_TOKEN_MAXSIZE; n++) {
		ptoken.id_ = n;
		list_unused_.push_back(ptoken);
	}
}

void PosManager::End(void) {
	list_unused_.clear();
	for (int group = 0; group != eOBJECT::NUM::sizeof_enum; group++)
		list_used_[group].clear();
}


/**
@brief PosToken�����֐�
@param set_group �O���[�v�w��
@param *param �p�����[�^�w��
@retval true ����
@retval false ���s
@note
 �����������E�l�̂Ƃ��͉������Ȃ��B
**/
bool PosManager::Generate(eOBJECT::GROUP set_group, PosParam1* param)
{
	list<PosToken>::iterator it;

	// �����������E
	if (list_unused_.size() == 0)
		return false;

	it = list_unused_.begin();
	it->hit_ = 0;
	it->pow_ = param->pow_;
	it->range_ = param->range_;
	it->x_ = param->start_x_;
	it->y_ = param->start_y_;
	param->group_ = set_group;
	param->it_ = it;
	list_unused_.splice(list_used_[set_group].begin(), list_unused_, it);

	return true;
}

/**
@brief PosToken�����֐�
@param *param �p�����[�^�w��
@param name �ݒ肷�閼�O
@retval true ����
@retval false ���s
@note
 �����������E�l�̂Ƃ��͉������Ȃ��B
 �����Ɠ����� pos token �ɓ��ʂȖ��O�����邱�Ƃ��ł���B
**/
bool PosManager::Generate(eOBJECT::GROUP set_group, PosParam1* param, std::string name)
{
	list<PosToken>::iterator it;

	// �����������E
	if (list_unused_.size() == 0)
		return false;

	it = list_unused_.begin();
	it->hit_ = 0;
	it->name_ = name;
	it->pow_ = param->pow_;
	it->range_ = param->range_;
	it->x_ = param->start_x_;
	it->y_ = param->start_y_;
	param->group_ = set_group;
	param->it_ = it;
	list_unused_.splice(list_used_[set_group].begin(), list_unused_, it);

	return true;
}

/**
@brief �폜�֐�
@param group �w��O���[�v
@note
 �����Ŏw�肵���O���[�v�� pos token ��S�č폜����B
 �������x�͐�������Ă��� pos token �̐��Ɉˑ�����B
**/
void PosManager::Delete(eOBJECT::GROUP group)
{
	list<int>::iterator it;

	//	while (!list_used_[group].empty()) {
	//		it = list_used_[group].begin();
	//		list_used_[group].splice(list_unused_.begin(), list_used_[group], it);
	//	}
	//	��L�R�[�h�͂��܂������Ȃ�����
	while (list_used_[group].begin() != list_used_[group].end())
		list_used_[group].splice(list_unused_.begin(), list_used_[group], list_used_[group].begin());
}

/**
@brief �폜�֐�
@param *param �폜���� pos token �̃p�����[�^
@note
 �폜�ς݂��ǂ����̌������ȗ����č������B
 ���ȐӔC�ŌĂяo�����ƁB
**/
void PosManager::Delete(PosParam1 *param)
{
	static eOBJECT::GROUP group = param->group_;

	list_used_[group].splice(list_unused_.begin(), list_used_[group], param->it_);
}

/**
@brief �폜�֐�
@param *param �폜���� pos token �̃p�����[�^
@retval  1 ����
@retval -1 ���s
@note
 �������x�͐�������Ă��� pos token �̐��Ɉˑ�����B
**/
int PosManager::Delete_s(PosParam1 *param)
{
	static list<PosToken>::iterator it;
	static eOBJECT::GROUP group = param->group_;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		if (it->id_ == param->it_->id_) {
			list_used_[group].splice(list_unused_.begin(), list_used_[group], it);
			return 1;
		}
	}

	return -1;
}

/**
@brief �O���[�v�ݒ�֐�
@param *param �ݒ肵���� PosToken �̃p�����[�^
@param group �ݒ肷��O���[�v
@note
 ����: �������ĂȂ� PosToken �̃O���[�v�͐ݒ�ł��Ȃ��B
**/
void PosManager::SetGroup(PosParam1 *param, eOBJECT::GROUP set_group)
{
	static list<PosToken>::iterator it;
	static eOBJECT::GROUP group;
	
	group = param->group_;
	it = param->it_;
	list_used_[group].splice(list_used_[set_group].begin(), list_used_[group], it);
	param->group_ = set_group;
}


/**
@brief ���O�ݒ�֐�
@param *param �ݒ肵���� pos token �̃p�����[�^
@param name �ݒ肷�閼�O
@note
 �������Ŏw�肵�� pos token �ɓ��ʂȖ��O��ݒ�ł���B
 �ݒ肵�����O�͍����p�x�̌v�Z(CalcDiffAngle)�ȂǂɎg����B
**/
void PosManager::SetName(PosParam1 *param, string name)
{
	param->it_->name_ = name;
}


/**
@brief ���W�ݒ�֐�A
@param *param ���W���Z�b�g���� pos token �̃p�����[�^
@param *x �Z�b�g����x���W
@param *y �Z�b�g����y���W
@note
 x���W�܂���y���W��null���w�肵���ꍇ�́C���̒l��ύX���Ȃ��B
**/
void PosManager::SetPosA(PosParam1 *param, double *x, double *y)
{
	static list<PosToken>::iterator it;

	it = param->it_;
	if (x != NULL)
		it->x_ = *x;
	if (y != NULL)
		it->y_ = *y;
}


/**
@brief ���W�ݒ�֐�B
@param group ���W���Z�b�g���� pos token �̃O���[�v
@param *x �Z�b�g����x���W
@param *y �Z�b�g����y���W
@note
�������Ŏw�肵���O���[�v���̑S�Ă� pos token �ɑ΂��Ēl��������B
x���W�܂���y���W��null���w�肵���ꍇ�́C���̒l��ύX���Ȃ��B
**/
void PosManager::SetPosB(eOBJECT::GROUP group, double *x, double *y)
{
	static list<PosToken>::iterator it;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {

		if (x != NULL)
			it->x_ = *x;
		if (y != NULL)
			it->y_ = *y;
	}
}


/**
@brief �����蔻��ݒ�֐�
@param *param ���W���Z�b�g���� pos token �̃p�����[�^
@param *x �Z�b�g���铖���蔻��͈̔�
**/
void PosManager::SetRange(PosParam1 *param, double set_value)
{
	static list<PosToken>::iterator it;
	
	it = param->it_;
	it->range_ = set_value;
}


/**
@brief X���ړ��֐�
@param move_value �ړ���
@return �ړ�������
@note
 ���̈ړ��͈͂ɐ�������B
**/
double PosManager::MoveAxisX(double move_value)
{
	if (axis_x_ + move_value < -100) {
		move_axis_x_ = 0;
	} else if (100 < axis_x_ + move_value) {
		move_axis_x_ = 0;
	} else {
		move_axis_x_ = move_value;
	}

	return move_axis_x_;
}

/**
@brief Y���ړ��֐�
@param move_value �ړ���
@return 0
@note
 �g��Ȃ��̂Ŗ������B
**/
double PosManager::MoveAxisY(double move_value)
{
	return 0;
}


/**
@brief ���W�ړ��֐�A
@param *param ���W���ړ������� pos token �̃p�����[�^
@param *add_x �ړ�(���Z)����x���W
@param *add_y �ړ�(���Z)����y���W
@note
 ���݂̍��W�Ɉ����Ŏw�肵���l�����Z����B
 x���W�܂���y���W�� null ���w�肵���ꍇ�́C���̒l��ύX���Ȃ��B
**/
void PosManager::MovePosA(PosParam1 *param, double *add_x, double *add_y)
{
	static list<PosToken>::iterator it;

	it = param->it_;
	if (add_x != NULL)
		it->x_+= *add_x;
	if (add_y != NULL)
		it->y_ += *add_y;
}

/**
@brief ���W�ړ��֐�B
@param *param ���W���ړ������� pos token �̃p�����[�^
@param angle �p�x(���W�A���w��)
@param dist �ړ�����
@note
 �p�x�Ƌ������w�肵�č��W���ړ�������B
**/
void PosManager::MovePosB(PosParam1 *param, double angle, double dist)
{
	static list<PosToken>::iterator it;

	it = param->it_;
	it->x_ += (cos(angle) * dist);
	it->y_ += (sin(angle) * dist);
}

/**
@brief ���W�ړ��֐�C
@param group ���W���ړ������� pos token �̃O���[�v
@param *add_x �ړ�(���Z)����x���W
@param *add_y �ړ�(���Z)����y���W
@note
 �������Ŏw�肵���O���[�v���̑S�Ă� pos token �ɑ΂��Ēl���X�V����B
 x���W�܂���y���W�� null ���w�肵���ꍇ�́C���̒l��ύX���Ȃ��B
**/
void PosManager::MovePosC(eOBJECT::GROUP group, double *add_x, double *add_y)
{
	static list<PosToken>::iterator it;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {

		if (add_x != NULL)
			it->x_ += *add_x;
		if (add_y != NULL)
			it->y_ += *add_y;
	}
}

/*!
@brief �I�u�W�F�N�g�Ԃ̊p�x�����߂�֐�
@param param �N�_�ƂȂ�I�u�W�F�N�g�̃p�����[�^
@param group �ΏۃI�u�W�F�N�g�̃O���[�v
@param name �ΏۃI�u�W�F�N�g�̖��O
@return �v�Z����(���W�A��)
@note
 �N�_�ƑΏۃI�u�W�F�N�g�Ԃ̊p�x���v�Z���Č��ʂ����W�A���ŕԂ��B
*/
double PosManager::GetAtan(PosParam1 *param, eOBJECT::GROUP group, string name)
{
	double x, y;
	double ret = 0;
	list<PosToken>::iterator it_start, it_end;

	it_start = param->it_;
	for (it_end = list_used_[group].begin(); it_end != list_used_[group].end(); ++it_end) {
		if (it_end->name_ == name) {
			x = it_end->x_ - it_start->x_;
			y = it_end->y_ - it_start->y_;
			ret = atan2(y, x);
			break;
		}
	}

	return ret;
}

/**
@brief ���������v�Z�֐�
@param *param �N�_�� pos token param
@param group �I�_�� pos token group
@param name �I�_�� pos token name
@return �v�Z����
@note
 �v�Z���x�͐�������Ă��� pos token �̐��Ɉˑ�����B
**/
double PosManager::CalcDiffDistance(PosParam1 *param, eOBJECT::GROUP group, string name)
{
	double x, y;
	double ret = 0;
	list<PosToken>::iterator it_start, it_end;

	it_start = param->it_;
	for (it_end = list_used_[group].begin(); it_end != list_used_[group].end(); ++it_end) {
		if (it_end->name_ == name) {
			x = it_end->x_ - it_start->x_;
			y = it_end->y_ - it_start->y_;
			ret = sqrt(x * x + y * y);
		}
	}

	return ret;
}

/**
@brief ���W�擾�֐�int�^(���O�w��)
@param group ���W�擾���� PosToken�̃O���[�v
@param name ���W�擾���� PosToken �̖��O
@param return_x �擾����x���W���i�[����
@param return_x �擾����y���W���i�[����
@note
 x���W�܂���y���W�� null ���w�肵���ꍇ�́C���̒l��ύX���Ȃ��B
**/
void PosManager::GetPos(eOBJECT::GROUP group, std::string name, int *return_x, int *return_y)
{
	list<PosToken>::iterator it;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		if (it->name_ == name) {
			if (return_x != NULL)
				*return_x = (int)it->x_;
			if (return_y != NULL)
				*return_y = (int)it->y_;
			return;
		}
	}
}

/**
@brief ���W�擾�֐�double�^(���O�w��)
@param group ���W�擾���� PosToken�̃O���[�v
@param name ���W�擾���� PosToken �̖��O
@param return_x �擾����x���W���i�[����
@param return_x �擾����y���W���i�[����
@note
 x���W�܂���y���W�� null ���w�肵���ꍇ�́C���̒l��ύX���Ȃ��B
**/
void PosManager::GetPos(eOBJECT::GROUP group, std::string name, double *return_x, double *return_y)
{
	list<PosToken>::iterator it;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		if (it->name_ == name) {
			if (return_x != NULL)
				*return_x = (int)it->x_;
			if (return_y != NULL)
				*return_y = (int)it->y_;
			return;
		}
	}
}

/**
@brief ���W�擾�֐�double�^
@param param ���W�擾���� PosToken�̃p�����[�^
@param name ���W�擾���� PosToken �̖��O
@param return_x �擾����x���W���i�[����
@param return_x �擾����y���W���i�[����
@note
 x���W�܂���y���W�� null ���w�肵���ꍇ�́C���̒l��ύX���Ȃ��B
**/
void PosManager::GetPos(PosParam1 *param, int *return_x, int *return_y)
{
	if (return_x != NULL)
		*return_x = (int)param->it_->x_;
	if (return_y != NULL)
		*return_y = (int)param->it_->y_;
}

/**
@brief ���W�擾�֐�double�^
@param param ���W�擾���� PosToken �̃p�����[�^
@param return_x �擾����x���W���i�[����
@param return_x �擾����y���W���i�[����
@note
 x���W�܂���y���W�� null ���w�肵���ꍇ�́C���̒l��ύX���Ȃ��B
**/
void PosManager::GetPos(PosParam1 *param, double *return_x, double *return_y)
{
	if (return_x != NULL)
		*return_x = param->it_->x_;
	if (return_y != NULL)
		*return_y = param->it_->y_;
}
