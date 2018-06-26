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
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
		gadget_phandle_collection_[i] = new PositionHandle;
}

DeviceGadget14::~DeviceGadget14()
{
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}

DeviceGadget1414::DeviceGadget1414()
{
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
		gadget_phandle_collection_[i] = new PositionHandle;
}

DeviceGadget1414::~DeviceGadget1414()
{
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}


H2NLIB::DeviceGadget2414::DeviceGadget2414()
{
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX2;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
		gadget_phandle_collection_[i] = new PositionHandle;
}

H2NLIB::DeviceGadget2414::~DeviceGadget2414()
{
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}

DevicePropertyX1::DevicePropertyX1()
{
	collision_power_ = 1;
	collision_range_ = 1;
	delay_time_frame_ = 0;
	draw_angle_deg_ = 0;
	move_angle_deg_ = 0;
	move_speed_ = 1;
}

DevicePropertyX2::DevicePropertyX2()
{
	collision_power_ = 1;
	collision_range_ = 1;
	delay_time_frame_ = 0;
	draw_angle_deg_ = 0;
	draw_angle_speed_deg_ = 0;
	move_angle_deg_ = 0;
	move_angle_speed_deg_ = 0;
	move_speed_ = 1;
}

/**
@brief �U��type14�֐�
@param gadget_dpx �K�W�F�b�g�p�f�o�C�X�v���p�e�B
@param gadget_gpx �K�W�F�b�g�p�O���t�B�b�N�v���p�e�B
@param gadget_type �K�W�F�b�g�̃I�u�W�F�N�g�^�C�v
@param collision_accuracy �Փ˔���̐��x
@note
 �I�u�W�F�N�g�̍ő����10000�B
 �Փ˔���̐��x��[1-10]�̒l�Ŏw��A�傫���l�قǍ����x�ɂȂ�B
 ���ꂼ��̈����Ŏw�肵���v���p�e�B�̃����o�̒��Ŏg�p���Ȃ��l�͐ݒ肵�Ă����������
**/
void NyaDevice::Attack14(const DevicePropertyX1* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type,  unsigned int collision_accuracy)
{
	static list<DeviceGadget14>::iterator it_from, it_to;

	// �ő���܂Ő�������Ă���Ƃ��͉������Ȃ�
	if (dg14_wait_list_.begin() == dg14_wait_list_.end())
		return;

	// �Փː��x�̒l���͈͊O�̂Ƃ��͖�����
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = dg14_wait_list_.begin();
	it_from->clear_ = false;
	it_from->collision_accuracy_ = collision_accuracy;
	it_from->count_frame_ = 0;
	it_from->move_angle_deg_ = gadget_dpx->move_angle_deg_;
	it_from->move_angle_rad_ = AngleToRad(gadget_dpx->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_x_ /= collision_accuracy;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_y_ /= collision_accuracy;
	*it_from->gadget_dpx_ = *gadget_dpx;
	*it_from->gadget_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->gadget_phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->gadget_phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->gadget_phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->gadget_phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->gadget_phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->gadget_phandle_collection_[i]->health_ = 1;
	}

	it_to = dg14_attack_list_[static_cast<int>(gadget_type)].begin();
	dg14_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(dg14_wait_list_), it_from);
}

/**
@brief �U��type1414�֐�
@param gadget_dpx �K�W�F�b�g�p�f�o�C�X�v���p�e�B
@param gadget_gpx �K�W�F�b�g�p�O���t�B�b�N�v���p�e�B
@param effect_dpx �G�t�F�N�g�p�f�o�C�X�v���p�e�B
@param effect_gpx �G�t�F�N�g�p�O���t�B�b�N�v���p�e�B
@param gadget_type �K�W�F�b�g�̃I�u�W�F�N�g�^�C�v
@param effect_type �G�t�F�N�g�̃I�u�W�F�N�g�^�C�v
@param collision_accuracy �Փ˔���̐��x
@note
 �G�t�F�N�g�t���U���֐��B
 �K�W�F�b�g�̍ő����10000�B
 �Փ˔���̐��x��[1-10]�̒l�Ŏw��A�傫���l�قǍ����x�ɂȂ�B
 ���ꂼ��̈����Ŏw�肵���v���p�e�B�̃����o�̒��Ŏg�p���Ȃ��l�͐ݒ肵�Ă����������B
**/
void NyaDevice::Attack1414(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget1414>::iterator it_from, it_to;

	// �ő���܂Ő�������Ă���Ƃ��͉������Ȃ�
	if (dg1414_wait_list_.begin() == dg1414_wait_list_.end())
		return;

	// �Փː��x�̒l���͈͊O�̂Ƃ��͖�����
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = dg1414_wait_list_.begin();
	it_from->clear_ = false;
	it_from->collision_accuracy_ = collision_accuracy;
	it_from->count_frame_ = 0;
	it_from->effect_type_ = effect_type;
	it_from->move_angle_deg_ = gadget_dpx->move_angle_deg_;
	it_from->move_angle_rad_ = AngleToRad(gadget_dpx->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_x_ /= collision_accuracy;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_y_ /= collision_accuracy;
	*it_from->effect_epx_ = *effect_epx;
	*it_from->effect_gpx_ = *effect_gpx;
	*it_from->gadget_dpx_ = *gadget_dpx;
	*it_from->gadget_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->gadget_phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->gadget_phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->gadget_phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->gadget_phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->gadget_phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->gadget_phandle_collection_[i]->health_ = 1;
	}
	it_to = dg1414_attack_list_[static_cast<int>(gadget_type)].begin();
	dg1414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(dg1414_wait_list_), it_from);
}

/**
@brief �U��type2414�֐�
@param gadget_dpx �K�W�F�b�g�p�f�o�C�X�v���p�e�B
@param gadget_gpx �K�W�F�b�g�p�O���t�B�b�N�v���p�e�B
@param effect_dpx �G�t�F�N�g�p�f�o�C�X�v���p�e�B
@param effect_gpx �G�t�F�N�g�p�O���t�B�b�N�v���p�e�B
@param gadget_type �K�W�F�b�g�̃I�u�W�F�N�g�^�C�v
@param effect_type �G�t�F�N�g�̃I�u�W�F�N�g�^�C�v
@param collision_accuracy �Փ˔���̐��x
@note
 �G�t�F�N�g�Ɗp���x���w��ł���U���֐��B
 �K�W�F�b�g�̍ő����10000�B
 �Փ˔���̐��x��[1-10]�̒l�Ŏw��A�傫���l�قǍ����x�ɂȂ�B
 ���ꂼ��̈����Ŏw�肵���v���p�e�B�̃����o�̒��Ŏg�p���Ȃ��l�͐ݒ肵�Ă����������B
**/

void NyaDevice::Attack2414(const DevicePropertyX2* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget2414>::iterator it_from, it_to;

		// �ő���܂Ő�������Ă���Ƃ��͉������Ȃ�
	if (dg2414_wait_list_.begin() == dg2414_wait_list_.end())
		return;

	// �Փː��x�̒l���͈͊O�̂Ƃ��͖�����
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = dg2414_wait_list_.begin();
	it_from->clear_ = false;
	it_from->collision_accuracy_ = collision_accuracy;
	it_from->count_frame_ = 0;
	it_from->effect_type_ = effect_type;
	it_from->move_angle_deg_ = gadget_dpx->move_angle_deg_;
	it_from->move_angle_rad_ = AngleToRad(gadget_dpx->move_angle_deg_);
	it_from->move_x_ = cos(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_x_ /= collision_accuracy;
	it_from->move_y_ = sin(it_from->move_angle_rad_) * gadget_dpx->move_speed_;
	it_from->move_y_ /= collision_accuracy;
	*it_from->effect_epx_ = *effect_epx;
	*it_from->effect_gpx_ = *effect_gpx;
	*it_from->gadget_dpx_ = *gadget_dpx;
	*it_from->gadget_gpx_ = *gadget_gpx;
	for (unsigned int i = 0; i < collision_accuracy; i++)
	{
		it_from->gadget_phandle_collection_[i]->collision_hit_damage_ = 0;
		it_from->gadget_phandle_collection_[i]->collision_power_ = gadget_dpx->collision_power_;
		it_from->gadget_phandle_collection_[i]->collision_range_ = gadget_dpx->collision_range_;
		it_from->gadget_phandle_collection_[i]->grid_x_ = gadget_dpx->create_x_;
		it_from->gadget_phandle_collection_[i]->grid_y_ = gadget_dpx->create_y_;
		it_from->gadget_phandle_collection_[i]->health_ = 1;
	}

	it_to = dg2414_attack_list_[static_cast<int>(gadget_type)].begin();
	dg2414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(dg2414_wait_list_), it_from);
}

/**
 @brief �N���A�֐�
 @param type �N���A����I�u�W�F�N�g�^�C�v
 @note
  �����Ŏw�肵��type��gadget��S�ăN���A����
**/
void NyaDevice::Clear(eOBJECT type)
{
	for (auto& e : dg14_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : dg1414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : dg2414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
}


void NyaDevice::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (eOBJECT type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; ++type)
		CalculateGadget(type);


	NyaString::Write("debug_font", white, 50, 190, "[50, 190] attack list size = %d", 10000 - (int)dg1414_wait_list_.size());
	NyaString::Write("debug_font", white, 50, 210, "[50, 210] wait list size = %d", (int)dg1414_wait_list_.size());
}


void NyaDevice::CalculateGadget(eOBJECT type)
{
	GraphicPropertyX4 gp;
	deque<list<DeviceGadget14>::iterator> dg14_delete_deque;
	deque<list<DeviceGadget1414>::iterator> dg1414_delete_deque;
	deque<list<DeviceGadget2414>::iterator> dg2414_delete_deque;

	//***********************
	// Gadget14 �폜����
	//***********************
	for (auto it = dg14_attack_list_[static_cast<int>(type)].begin(); it != dg14_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �t���[���J�E���g���x�����ԂɒB���Ă��Ȃ��Ȃ牽�����Ȃ�
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// �\���̈�̌��E�𒴂���
		// �N���A���w�肳�ꂽ
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			dg14_delete_deque.push_back(it);
		else if (it->clear_)
			dg14_delete_deque.push_back(it);
		else
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->gadget_phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					dg14_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!dg14_delete_deque.empty())
	{
		dg14_wait_list_.splice(dg14_wait_list_.begin(), move(dg14_attack_list_[static_cast<int>(type)]), dg14_delete_deque.front());
		dg14_delete_deque.pop_front();
	}

	//****************************
	// gadget14 �폜�ȊO�̏���
	//****************************
	for (auto& e : dg14_attack_list_[static_cast<int>(type)])
	{
		// count_frame_�̏����l��0�ɂȂ��Ă���
		// delay_time_frame_��1�Ȃ�1�t���[���͉������Ȃ��悤�ɂ�����
		// ���������āA�C���N�������g���Ă��画�肵�Ă�̂�count_frame_ - 1�Ŕ�r
		e.count_frame_++;
		if (e.count_frame_ - 1 < e.gadget_dpx_->delay_time_frame_)
			continue;

		// �Փ˔��菈��
		for (unsigned int i = 0; i < e.collision_accuracy_; i++)
		{
			e.gadget_phandle_collection_[i]->grid_x_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.gadget_phandle_collection_[i]->grid_y_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.gadget_phandle_collection_[i], type);
		}
		
		// �`�揈��
		e.gadget_gpx_->draw_grid_cx_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.gadget_gpx_->draw_grid_cy_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.gadget_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.gadget_gpx_, type);
	}

	//*******************************************
	// Gadget1414 �폜����
	// �폜����Ƃ��ɃG�t�F�N�g�`��������Ȃ�
	//*******************************************
	for (auto it = dg1414_attack_list_[static_cast<int>(type)].begin(); it != dg1414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �t���[���J�E���g���x�����ԂɒB���Ă��Ȃ��Ȃ牽�����Ȃ�
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// �\���̈�̌��E�𒴂���
		// �N���A���w�肳�ꂽ
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			dg1414_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			dg1414_delete_deque.push_back(it);
		}
		else 
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->gadget_phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[i]->collision_hit_x_;
					it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[i]->collision_hit_y_;
					NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
					dg1414_delete_deque.push_back(it);
					break;
				}
			}
		}

	}
	while (!dg1414_delete_deque.empty())
	{
		dg1414_wait_list_.splice(dg1414_wait_list_.begin(), move(dg1414_attack_list_[static_cast<int>(type)]), dg1414_delete_deque.front());
		dg1414_delete_deque.pop_front();
	}

	//****************************
	// gadget1414 �폜�ȊO�̏���
	//****************************
	for (auto& e : dg1414_attack_list_[static_cast<int>(type)])
	{
		// count_frame_�̏����l��0�ɂȂ��Ă���
		// delay_time_frame_��1�Ȃ�1�t���[���͉������Ȃ��悤�ɂ�����
		// ���������āA�C���N�������g���Ă��画�肵�Ă�̂�count_frame_ - 1�Ŕ�r
		e.count_frame_++;
		if (e.count_frame_ - 1 < e.gadget_dpx_->delay_time_frame_)
			continue;

		// �ړ������ƏՓ˔��菈��
		for (unsigned int i = 0; i < e.collision_accuracy_; i++)
		{
			e.gadget_phandle_collection_[i]->grid_x_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.gadget_phandle_collection_[i]->grid_y_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.gadget_phandle_collection_[i], type);
		}
		
		// �`�揈��
		e.gadget_gpx_->draw_grid_cx_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.gadget_gpx_->draw_grid_cy_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.gadget_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.gadget_gpx_, type);
	}


	//*******************************************
	// gadget2414 �폜����
	// �폜����Ƃ��ɃG�t�F�N�g�`��������Ȃ�
	//*******************************************
	for (auto it = dg2414_attack_list_[static_cast<int>(type)].begin(); it != dg2414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �t���[���J�E���g���x�����ԂɒB���Ă��Ȃ��Ȃ牽�����Ȃ�
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// �\���̈�̌��E�𒴂���
		// �N���A���w�肳�ꂽ
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			dg2414_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			dg2414_delete_deque.push_back(it);
		}
		else 
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->gadget_phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[i]->collision_hit_x_;
					it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[i]->collision_hit_y_;
					NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
					dg2414_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!dg2414_delete_deque.empty())
	{
		dg2414_wait_list_.splice(dg2414_wait_list_.begin(), move(dg2414_attack_list_[static_cast<int>(type)]), dg2414_delete_deque.front());
		dg2414_delete_deque.pop_front();
	}

	//****************************
	// gadget2414 �폜�ȊO�̏���
	//****************************
	for (auto& e : dg2414_attack_list_[static_cast<int>(type)])
	{
		// count_frame_�̏����l��0�ɂȂ��Ă���
		// delay_time_frame_��1�Ȃ�1�t���[���͉������Ȃ��悤�ɂ�����
		// ���������āA�C���N�������g���Ă��画�肵�Ă�̂�count_frame_ - 1�Ŕ�r
		e.count_frame_++;
		if (e.count_frame_ - 1 < e.gadget_dpx_->delay_time_frame_)
			continue;

		// �ړ������ƏՓ˔��菈��
		for (unsigned int i = 0; i < e.collision_accuracy_; i++)
		{
			e.gadget_phandle_collection_[i]->grid_x_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_x_ * (i + 1);
			e.gadget_phandle_collection_[i]->grid_y_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.gadget_phandle_collection_[i], type);
		}

		// �p���x�̏���
		e.move_angle_deg_ += e.gadget_dpx_->move_angle_speed_deg_;
		e.move_angle_rad_ = AngleToRad(e.move_angle_deg_);
		e.move_x_ = cos(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_x_ /= e.collision_accuracy_;
		e.move_y_ = sin(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_y_ /= e.collision_accuracy_;
		
		// �`�揈��
		e.gadget_gpx_->draw_grid_cx_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.gadget_gpx_->draw_grid_cy_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.gadget_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.gadget_gpx_, type);
		e.gadget_dpx_->draw_angle_deg_ += e.gadget_dpx_->draw_angle_speed_deg_;
	}
}

