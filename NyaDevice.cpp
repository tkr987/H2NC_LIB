#include <cmath>
#include <deque>
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;

#define DEVICE_GADGET_MAX 10000
int NyaDevice::count_instance_ = 0;
list<DeviceGadget14> NyaDevice::dg14_attack_list_[eOBJECT::NUM::sizeof_enum];
list<DeviceGadget14> NyaDevice::dg14_wait_list_;


NyaDevice::NyaDevice()
{
	nya_effect_ = new NyaEffect;
	nya_position_ = new NyaPosition;


	// �e�I�u�W�F�N�g�̍ő����10000��
	if (count_instance_ == 0)
	{
		dg14_wait_list_.resize(DEVICE_GADGET_MAX);
		for (auto& it : dg14_wait_list_)
		{
			it.dpx1_ = new DevicePropertyX1;
			it.gadget_gpx4_ = new GraphicPropertyX4;
			it.phx_ = nya_position_->Create();
		}
	}

	count_instance_++;
}


NyaDevice::~NyaDevice()
{
	delete nya_effect_;
	delete nya_position_;

	if (count_instance_ == 1)
	{
		for (int group = eOBJECT::NUM::enum_zero; group != eOBJECT::NUM::sizeof_enum; group++)
		{
			for (auto& it : dg14_attack_list_[group])
			{
				delete it.dpx1_;
				delete it.gadget_gpx4_;
			}
		}
		for (auto& it : dg14_wait_list_)
		{
			delete it.dpx1_;
			delete it.gadget_gpx4_;
		}
	}
}

/**
@brief �U���֐�
@param dpx �f�o�C�X�v���p�e�B
@param gadget_gpx4 �K�W�F�b�g�O���t�B�b�N�v���p�e�B
@note
 �I�u�W�F�N�g�̍ő����10000�B
 ���̊֐��ł͉��L�����o�ϐ��𗘗p����̂ŁA�K���l��ݒ肷�邱�ƁB
 dpx->collision_pow_;			// �ՓˍU����
 dpx->collision_range_;			// �Փ˔͈�
 dpx->create_x_;				// ����x���W
 dpx->create_y_;				// ����y���W
 dpx->move_angle_deg_;			// �ړ��p�x
 dpx->move_speed_;				// �ړ����x
 dpx->object_group_;			// �I�u�W�F�N�g�O���[�v�ݒ�
 gadget_gpx4->graphic_file_;	// �K�W�F�b�g�p�O���t�B�b�N�t�@�C��
 gadget_gpx4->file_div_;		// �K�W�F�b�g�p�O���t�B�b�N�����C���f�b�N�X
 gadget_gpx4->draw_angle_;		// �K�W�F�b�g�p�`��p�x
 gadget_gpx4->extend_rate_;		// �K�W�F�b�g�p�`��g�嗦
 gadget_gpx4->flag_turn_;		// �K�W�F�b�g�p�`�攽�]�t���O
 gadget_gpx4->flag_trans_;		// �K�W�F�b�g�p�`�擧�߃t���O
 gadget_gpx4->object_group_;	// �K�W�F�b�g�p�`��I�u�W�F�N�g�O���[�v�ݒ�
 ���̊֐��ł͉��L�����o�ϐ��͗��p���Ȃ����߁A�l��ݒ肵�Ă����������B
 gadget_gpx4->pos_cx_; gadget_gpx4->pos_cy_;
**/
void NyaDevice::Attack(DevicePropertyX1* dpx, GraphicPropertyX4* gadget_gpx4)
{
	static list<DeviceGadget14>::iterator it;

	// �ő���܂Ő�������Ă���Ƃ��͉������Ȃ�
	if (dg14_wait_list_.begin() == dg14_wait_list_.end())
		return;

	it = dg14_wait_list_.begin();
	it->dpx1_ = dpx;
	it->gadget_gpx4_ = gadget_gpx4;
	it->move_angle_rad_ = AngleToRad(dpx->move_angle_deg_);
	it->move_x_ = cos(it->move_angle_rad_) * dpx->move_speed_;
	it->move_y_ = sin(it->move_angle_rad_) * dpx->move_speed_;

}


void NyaDevice::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (int group = eOBJECT::NUM::enum_zero; group != eOBJECT::NUM::sizeof_enum; group++)
		MoveGadget((eOBJECT::NUM)group);


	NyaString::Write("debug_font", white, 50, 190, "[50, 190] attack list size = %d", (int)dg14_attack_list_[eOBJECT::NUM::USER_ATTACK1].size());
	NyaString::Write("debug_font", white, 50, 210, "[50, 210] wait list size = %d", (int)dg14_wait_list_.size());
}


void NyaDevice::MoveGadget(eOBJECT::NUM group)
{
	static GraphicPropertyX4 gpx4;
	static deque<list<DeviceGadget14>::iterator> dg14_delete_deque;
	static deque<list<DeviceGadget1414>::iterator> dg1414_delete_deque;


	//***********************
	// Gadget14 �폜����
	//***********************
	for (auto it = dg14_attack_list_[group].begin(); it != dg14_attack_list_[group].end(); ++it)
	{
		// �\���̈�̌��E�𒴂���
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if ((int)it->phx_->grid_x_ < 0 || 1000 < (int)it->phx_->grid_x_ ||
			(int)it->phx_->grid_y_ < 0 || 700 < (int)it->phx_->grid_y_)
		{
			dg14_delete_deque.push_back(it);
		}
		else if (it->phx_->collision_hit_)
		{
			dg14_delete_deque.push_back(it);
		}
	}

	while (!dg14_delete_deque.empty())
	{
		dg14_wait_list_.splice(dg14_wait_list_.begin(), move(dg14_attack_list_[group]), dg14_delete_deque.front());
		dg14_delete_deque.pop_front();
	}

	//***********************
	// Gadget1414 �폜����
	//***********************
	for (auto it = dg1414_attack_list_[group].begin(); it != dg1414_attack_list_[group].end(); ++it)
	{
		// �\���̈�̌��E�𒴂���
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if ((int)it->phx_->grid_x_ < 0 || 1000 < (int)it->phx_->grid_x_ ||
			(int)it->phx_->grid_y_ < 0 || 700 < (int)it->phx_->grid_y_)
		{
			dg1414_delete_deque.push_back(it);
		}
		else if (it->phx_->collision_hit_)
		{
			it->epx1_->grid_x_ = it->phx_->grid_x_;
			it->epx1_->grid_y_ = it->phx_->grid_y_;
			nya_effect_->Draw(it->epx1_, it->effect_gpx4_);
			dg1414_delete_deque.push_back(it);
		}
	}

	//*********************************
	// gadget14 �폜�ȊO�̏���
	//*********************************
	for (auto& it : dg14_attack_list_[group])
	{
		// �ړ�����
		it.phx_->grid_x_pre_ = it.phx_->grid_x_;
		it.phx_->grid_y_pre_ = it.phx_->grid_y_;
		it.phx_->grid_x_ += it.move_x_;
		it.phx_->grid_y_ += it.move_y_;
		
		// �`�揈��
		it.gadget_gpx4_->pos_cx_ = (int)it.phx_->grid_x_;
		it.gadget_gpx4_->pos_cy_ = (int)it.phx_->grid_y_;
		nya_graphic_->Draw(it.gadget_gpx4_);

		// �Փ˔��菈��
		nya_position_->Collision(it.phx_, group);
	}

}


