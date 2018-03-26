#include <cmath>
#include <deque>
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;

#define DEVICE_GADGET_MAX_DEFAULT 10000


int NyaDevice::count_instance_ = 0;
list<DeviceGadget14> NyaDevice::dg14_attack_list_[eOBJECT::NUM::sizeof_enum];
list<DeviceGadget14> NyaDevice::dg14_wait_list_;
list<DeviceGadget1414> NyaDevice::dg1414_attack_list_[eOBJECT::NUM::sizeof_enum];
list<DeviceGadget1414> NyaDevice::dg1414_wait_list_;
list<DeviceGadget2414> NyaDevice::dg2414_attack_list_[eOBJECT::NUM::sizeof_enum];
list<DeviceGadget2414> NyaDevice::dg2414_wait_list_;

DeviceGadget14::DeviceGadget14()
{
	main_dp_ = new DeviceProperty1;
	main_gp_ = new GraphicProperty4;
	main_ph_ = new PositionHandle1;
}

DeviceGadget14::~DeviceGadget14()
{
	delete main_dp_;
	delete main_gp_;
	delete main_ph_;
}

DeviceGadget1414::DeviceGadget1414()
{
	effect_ep_ = new EffectProperty1;
	effect_gp_ = new GraphicProperty4;
	main_dp_ = new DeviceProperty1;
	main_gp_ = new GraphicProperty4;
	main_ph_ = new PositionHandle1;
}

DeviceGadget1414::~DeviceGadget1414()
{
	delete effect_ep_;
	delete effect_gp_;
	delete main_dp_;
	delete main_gp_;
	delete main_ph_;
}

NyaDevice::NyaDevice()
{
	nya_effect_ = new NyaEffect;
	nya_position_ = new NyaPosition;


	// gadget �ő���̓f�t�H���g��10000��
	if (count_instance_ == 0)
		dg14_wait_list_.resize(DEVICE_GADGET_MAX_DEFAULT);

	count_instance_++;
}


NyaDevice::~NyaDevice()
{
	delete nya_effect_;
	delete nya_position_;
	count_instance_--;
}

/**
@brief �U���֐�
@param dpx �f�o�C�X�v���p�e�B
@param gadget_gpx4 �K�W�F�b�g�O���t�B�b�N�v���p�e�B
@note
 �I�u�W�F�N�g�̍ő����10000�B
 ���̊֐��ł͉��L�����o�ϐ��𗘗p����̂ŁA�K���l��ݒ肷�邱�ƁB
 gadget_dp->collision_pow_;			// gadget �ՓˍU����
 gadget_dp->collision_range_;		// gadget �Փ˔͈�
 gadget_dp->create_grid_x_;			// gadget ����x���W
 gadget_dp->create_grid_y_;			// gadget ����y���W
 gadget_dp->move_angle_deg_;		// gadget �ړ��p�x
 gadget_dp->move_speed_;			// gadget �ړ����x
 gadget_gp->graphic_file_;			// gadget �O���t�B�b�N�t�@�C��
 gadget_gp->file_div_;				// gadget �O���t�B�b�N�����C���f�b�N�X
 gadget_gp->draw_angle_;			// gadget �`��p�x
 gadget_gp->extend_rate_;			// gadget �`��g�嗦
 gadget_gp->flag_turn_;				// gadget �`�攽�]�t���O
 gadget_gp->flag_trans_;			// gadget �`�擧�߃t���O
 ���̊֐��ł͉��L�����o�ϐ��͗��p���Ȃ����߁A�l��ݒ肵�Ă����������B
 gadget_gp->pos_cx_; gadget_gp->pos_cy_;
**/
void NyaDevice::Attack14(const DeviceProperty1* const gadget_dp, const GraphicProperty4* const gadget_gp, eOBJECT::NUM gadget_type)
{
	static list<DeviceGadget14>::iterator it_from, it_to;

	// �ő���܂Ő�������Ă���Ƃ��͉������Ȃ�
	if (dg14_wait_list_.begin() == dg14_wait_list_.end())
		return;

	it_from = dg14_wait_list_.begin();
	*it_from->main_dp_ = *gadget_dp;
	*it_from->main_gp_ = *gadget_gp;
	it_from->move_angle_rad_ = AngleToRad(gadget_dp->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dp->move_speed_;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dp->move_speed_;
	it_from->main_ph_->collision_hit_ = false;
	it_from->main_ph_->collision_pow_ = gadget_dp->collision_pow_;
	it_from->main_ph_->collision_range_ = gadget_dp->collision_range_;
	it_from->main_ph_->grid_x_ = gadget_dp->create_grid_x_;
	it_from->main_ph_->grid_y_ = gadget_dp->create_grid_y_;
	it_from->main_ph_->health_max_ = 1;
	it_from->main_ph_->health_now_ = 1;

	it_to = dg14_attack_list_[gadget_type].begin();
	dg14_attack_list_[gadget_type].splice(it_to, move(dg14_wait_list_), it_from);
}

void NyaDevice::Attack1414(DeviceProperty1* gadget_dp, GraphicProperty4* gadget_gp, EffectProperty1* effect_ep, GraphicProperty4* effect_gp)
{

}

void NyaDevice::Attack2414(DeviceProperty2* gadget_dp, GraphicProperty4* gadget_gp, EffectProperty1* effect_ep, GraphicProperty4* effect_gp)
{

}

void NyaDevice::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (int group = eOBJECT::NUM::enum_zero; group != eOBJECT::NUM::sizeof_enum; group++)
		MoveGadget((eOBJECT::NUM)group);


	NyaString::Write("debug_font", white, 50, 190, "[50, 190] attack list size = %d", (int)dg14_attack_list_[eOBJECT::NUM::USER_ATTACK1].size());
	NyaString::Write("debug_font", white, 50, 210, "[50, 210] wait list size = %d", (int)dg14_wait_list_.size());
}


void NyaDevice::MoveGadget(eOBJECT::NUM type)
{
	static GraphicProperty4 gp;
	static deque<list<DeviceGadget14>::iterator> dg14_delete_deque;
	static deque<list<DeviceGadget1414>::iterator> dg1414_delete_deque;


	//***********************
	// Gadget14 �폜����
	//***********************
	for (auto it = dg14_attack_list_[type].begin(); it != dg14_attack_list_[type].end(); ++it)
	{
		// �\���̈�̌��E�𒴂���
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if ((int)it->main_ph_->grid_x_ < 0 || 1000 < (int)it->main_ph_->grid_x_ ||
			(int)it->main_ph_->grid_y_ < 0 || 700 < (int)it->main_ph_->grid_y_)
		{
			dg14_delete_deque.push_back(it);
		}
		else if (it->main_ph_->collision_hit_)
		{
			dg14_delete_deque.push_back(it);
		}
	}

	while (!dg14_delete_deque.empty())
	{
		dg14_wait_list_.splice(dg14_wait_list_.begin(), move(dg14_attack_list_[type]), dg14_delete_deque.front());
		dg14_delete_deque.pop_front();
	}

	//***********************
	// Gadget1414 �폜����
	//***********************
	for (auto it = dg1414_attack_list_[type].begin(); it != dg1414_attack_list_[type].end(); ++it)
	{
		// �\���̈�̌��E�𒴂���
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if ((int)it->main_ph_->grid_x_ < 0 || 1000 < (int)it->main_ph_->grid_x_ ||
			(int)it->main_ph_->grid_y_ < 0 || 700 < (int)it->main_ph_->grid_y_)
		{
			dg1414_delete_deque.push_back(it);
		}
		else if (it->main_ph_->collision_hit_)
		{
			//it->epx1_->grid_x_ = (int)it->phx_->grid_x_;
			//it->epx1_->grid_y_ = (int)it->phx_->grid_y_;
			//nya_effect_->Draw(it->epx1_, it->effect_gpx4_);
			dg1414_delete_deque.push_back(it);
		}
	}

	//*********************************
	// gadget14 �폜�ȊO�̏���
	//*********************************
	for (auto it = dg14_attack_list_[type].begin(); it != dg14_attack_list_[type].end(); ++it)
	{
		// �ړ�����
		it->main_ph_->grid_x_ += it->move_x_;
		it->main_ph_->grid_y_ += it->move_y_;
		
		// �`�揈��
		it->main_gp_->draw_grid_cx_ = (int)it->main_ph_->grid_x_;
		it->main_gp_->draw_grid_cy_ = (int)it->main_ph_->grid_y_;
		nya_graphic_->Draw(it->main_gp_, type);

		// �Փ˔��菈��
		nya_position_->Collision(it->main_ph_, type);
	}

}


