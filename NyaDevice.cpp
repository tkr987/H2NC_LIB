#include <cmath>
#include <deque>
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaString.h"

using namespace std;
using namespace H2NLIB;


list<DeviceGadget14> NyaDevice::dg14_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget14> NyaDevice::dg14_wait_list_(DEVICE_GADGET_MAX_DEFAULT);
list<DeviceGadget1414> NyaDevice::dg1414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget1414> NyaDevice::dg1414_wait_list_(DEVICE_GADGET_MAX_DEFAULT);
list<DeviceGadget2414> NyaDevice::dg2414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget2414> NyaDevice::dg2414_wait_list_(DEVICE_GADGET_MAX_DEFAULT);

DeviceGadget14::DeviceGadget14()
{
	gadget_dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	gadget_phandle_ = new PositionHandle1;
}

DeviceGadget14::~DeviceGadget14()
{
	delete gadget_dpx_;
	delete gadget_gpx_;
	delete gadget_phandle_;
}

DeviceGadget1414::DeviceGadget1414()
{
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	gadget_phandle_ = new PositionHandle1;
}

DeviceGadget1414::~DeviceGadget1414()
{
	delete effect_epx_;
	delete effect_gpx_;
	delete gadget_dpx_;
	delete gadget_gpx_;
	delete gadget_phandle_;
}

DevicePropertyX1::DevicePropertyX1()
{
	collision_power_ = 1;				//!< �Փ˗�
	collision_range_ = 1;				//!< �Փ˔͈�
	move_angle_deg_ = 0;				//!< �ړ��p�x
	move_speed_ = 1;					//!< �ړ����x
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
 gadget_gp->file_;			// gadget �O���t�B�b�N�t�@�C��
 gadget_gp->file_div_;				// gadget �O���t�B�b�N�����C���f�b�N�X
 gadget_gp->draw_angle_;			// gadget �`��p�x
 gadget_gp->extend_rate_;			// gadget �`��g�嗦
 gadget_gp->flag_turn_;				// gadget �`�攽�]�t���O
 gadget_gp->flag_trans_;			// gadget �`�擧�߃t���O
 ���̊֐��ł͉��L�����o�ϐ��͗��p���Ȃ����߁A�l��ݒ肵�Ă����������B
 gadget_gp->pos_cx_; gadget_gp->pos_cy_;
**/
void NyaDevice::Attack14(const DevicePropertyX1* const gadget_dp, const GraphicPropertyX4* const gadget_gp, eOBJECT gadget_type)
{
	static list<DeviceGadget14>::iterator it_from, it_to;

	// �ő���܂Ő�������Ă���Ƃ��͉������Ȃ�
	if (dg14_wait_list_.begin() == dg14_wait_list_.end())
		return;

	it_from = dg14_wait_list_.begin();
	it_from->clear_ = false;
	it_from->move_angle_rad_ = AngleToRad(gadget_dp->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dp->move_speed_;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dp->move_speed_;
	*it_from->gadget_dpx_ = *gadget_dp;
	*it_from->gadget_gpx_ = *gadget_gp;
	it_from->gadget_phandle_->collision_hit_ = 0;
	it_from->gadget_phandle_->collision_power_ = gadget_dp->collision_power_;
	it_from->gadget_phandle_->collision_range_ = gadget_dp->collision_range_;
	it_from->gadget_phandle_->grid_x_ = gadget_dp->create_x_;
	it_from->gadget_phandle_->grid_y_ = gadget_dp->create_y_;
	it_from->gadget_phandle_->health_ = 1;

	it_to = dg14_attack_list_[static_cast<int>(gadget_type)].begin();
	dg14_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(dg14_wait_list_), it_from);
}

void NyaDevice::Attack1414(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type)
{
	static list<DeviceGadget1414>::iterator it_from, it_to;

	// �ő���܂Ő�������Ă���Ƃ��͉������Ȃ�
	if (dg1414_wait_list_.begin() == dg1414_wait_list_.end())
		return;

	it_from = dg1414_wait_list_.begin();
	it_from->clear_ = false;
	it_from->effect_type_ = effect_type;
	it_from->move_angle_rad_ = AngleToRad(gadget_dpx->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	*it_from->effect_epx_ = *effect_epx;
	*it_from->effect_gpx_ = *effect_gpx;
	*it_from->gadget_dpx_ = *gadget_dpx;
	*it_from->gadget_gpx_ = *gadget_gpx;
	it_from->gadget_phandle_->collision_hit_ = 0;
	it_from->gadget_phandle_->collision_power_ = gadget_dpx->collision_power_;
	it_from->gadget_phandle_->collision_range_ = gadget_dpx->collision_range_;
	it_from->gadget_phandle_->grid_x_ = gadget_dpx->create_x_;
	it_from->gadget_phandle_->grid_y_ = gadget_dpx->create_y_;
	it_from->gadget_phandle_->health_ = 1;

	it_to = dg1414_attack_list_[static_cast<int>(gadget_type)].begin();
	dg1414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(dg1414_wait_list_), it_from);
}

void NyaDevice::Attack2414(DevicePropertyX2* gadget_dpx, GraphicPropertyX4* gadget_gpx, EffectPropertyX1* effect_epx, GraphicPropertyX4* effect_gpx)
{

}

void NyaDevice::Clear(eOBJECT type)
{
	for (auto& e : dg14_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : dg1414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
}


void NyaDevice::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (eOBJECT type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; ++type)
		MoveGadget(type);


	NyaString::Write("debug_font", white, 50, 190, "[50, 190] attack list size = %d", (int)dg14_attack_list_[static_cast<int>(eOBJECT::USER_ATTACK1)].size());
	NyaString::Write("debug_font", white, 50, 210, "[50, 210] wait list size = %d", (int)dg14_wait_list_.size());
}


void NyaDevice::MoveGadget(eOBJECT type)
{
	static GraphicPropertyX4 gp;
	static deque<list<DeviceGadget14>::iterator> dg14_delete_deque;
	static deque<list<DeviceGadget1414>::iterator> dg1414_delete_deque;


	//***********************
	// Gadget14 �폜����
	//***********************
	for (auto it = dg14_attack_list_[static_cast<int>(type)].begin(); it != dg14_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �\���̈�̌��E�𒴂���
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		// (�����I�Ƀ_���[�W��^������Ȃǂ���)�w���X��0�ȉ��ɂȂ���
		if (!NyaPosition::InScreen(it->gadget_phandle_))
		{
			dg14_delete_deque.push_back(it);
		}
		else if (it->gadget_phandle_->collision_hit_ != 0)
		{
			dg14_delete_deque.push_back(it);
		}
		else if (it->clear_)
		{
			dg14_delete_deque.push_back(it);
		}
	}
	while (!dg14_delete_deque.empty())
	{
		dg14_wait_list_.splice(dg14_wait_list_.begin(), move(dg14_attack_list_[static_cast<int>(type)]), dg14_delete_deque.front());
		dg14_delete_deque.pop_front();
	}

	//*******************************************
	// Gadget1414 �폜����
	// �폜����Ƃ��ɃG�t�F�N�g�`��������Ȃ�
	//*******************************************
	for (auto it = dg1414_attack_list_[static_cast<int>(type)].begin(); it != dg1414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �\���̈�̌��E�𒴂���
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_))
		{
			dg1414_delete_deque.push_back(it);
		}
		else if (it->gadget_phandle_->collision_hit_ != 0)
		{
			it->effect_epx_->grid_x_ = (int)it->gadget_phandle_->grid_x_;
			it->effect_epx_->grid_y_ = (int)it->gadget_phandle_->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			dg1414_delete_deque.push_back(it);
		}
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = (int)it->gadget_phandle_->grid_x_;
			it->effect_epx_->grid_y_ = (int)it->gadget_phandle_->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			dg1414_delete_deque.push_back(it);
		}
	}
	while (!dg1414_delete_deque.empty())
	{
		dg1414_wait_list_.splice(dg1414_wait_list_.begin(), move(dg1414_attack_list_[static_cast<int>(type)]), dg1414_delete_deque.front());
		dg1414_delete_deque.pop_front();
	}

	//****************************
	// gadget14 �폜�ȊO�̏���
	//****************************
	for (auto& e : dg14_attack_list_[static_cast<int>(type)])
	{
		// �ړ�����
		e.gadget_phandle_->grid_x_ += e.move_x_;
		e.gadget_phandle_->grid_y_ += e.move_y_;
		
		// �`�揈��
		e.gadget_gpx_->draw_grid_cx_ = (int)e.gadget_phandle_->grid_x_;
		e.gadget_gpx_->draw_grid_cy_ = (int)e.gadget_phandle_->grid_y_;
		NyaGraphic::Draw(e.gadget_gpx_, type);

		// �Փ˔��菈��
		NyaPosition::Collide(e.gadget_phandle_, type);
	}

	//****************************
	// gadget1414 �폜�ȊO�̏���
	//****************************
	for (auto& e : dg1414_attack_list_[static_cast<int>(type)])
	{
		// �ړ�����
		e.gadget_phandle_->grid_x_ += e.move_x_;
		e.gadget_phandle_->grid_y_ += e.move_y_;
		
		// �`�揈��
		e.gadget_gpx_->draw_grid_cx_ = (int)e.gadget_phandle_->grid_x_;
		e.gadget_gpx_->draw_grid_cy_ = (int)e.gadget_phandle_->grid_y_;
		NyaGraphic::Draw(e.gadget_gpx_, type);

		// �Փ˔��菈��
		NyaPosition::Collide(e.gadget_phandle_, type);
	}

}


