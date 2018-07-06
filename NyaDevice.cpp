#include <cmath>
#include <deque>
#include "NyaPosition.h"
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaString.h"

#define __DEBUG__

using namespace std;
using namespace H2NLIB;


list<DeviceGadget14> NyaDevice::gadget14_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget14> NyaDevice::gadget14_wait_list_;
list<DeviceGadget24> NyaDevice::gadget24_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget24> NyaDevice::gadget24_wait_list_;
list<DeviceGadget34> NyaDevice::gadget34_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget34> NyaDevice::gadget34_wait_list_;
list<DeviceGadget1414> NyaDevice::gadget1414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget1414> NyaDevice::gadget1414_wait_list_;
list<DeviceGadget1424> NyaDevice::gadget1424_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget1424> NyaDevice::gadget1424_wait_list_;
list<DeviceGadget2414> NyaDevice::gadget2414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget2414> NyaDevice::gadget2414_wait_list_;
list<DeviceGadget3414> NyaDevice::gadget3414_attack_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<DeviceGadget3414> NyaDevice::gadget3414_wait_list_;

//***************************
// class DevicePropertyX
//***************************

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

DevicePropertyX3::DevicePropertyX3()
{
	collision_power_ = 1;
	collision_range_ = 1;
	delay_time_frame_ = 0;
	draw_angle_deg_ = 0;
	draw_angle_speed_deg_ = 0;
	move_angle_deg_ = 0;
	move_speed_ = 1;
	move_speed_accel_ = 0;
}

//**********************
// class DeviceGadget
//**********************

DeviceGadget14::DeviceGadget14()
{
	gadget_dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{	// �f�X�g���N�^�̏����Ɠ��ꂳ���邽��new���Z�q�œ��I��������
		gadget_phandle_collection_[i] = new PositionHandle;
		NyaPosition::CreateHandle(gadget_phandle_collection_[i]);
	}
}

DeviceGadget14::~DeviceGadget14()
{
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{	// �R���X�g���N�^�̏����Ɠ��ꂷ�邽��NyaPosition::DeleteHandle(PositionHandle*)�łȂ�delete���g��
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}

DeviceGadget24::DeviceGadget24()
{
	gadget_dpx_ = new DevicePropertyX2;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{	// �f�X�g���N�^�̏����Ɠ��ꂳ���邽��new���Z�q�œ��I��������
		gadget_phandle_collection_[i] = new PositionHandle;
		NyaPosition::CreateHandle(gadget_phandle_collection_[i]);
	}
}

DeviceGadget24::~DeviceGadget24()
{
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{	// �R���X�g���N�^�̏����Ɠ��ꂷ�邽��NyaPosition::DeleteHandle(PositionHandle*)�łȂ�delete���g��
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}

DeviceGadget34::DeviceGadget34()
{
	gadget_dpx_ = new DevicePropertyX3;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{	// �f�X�g���N�^�̏����Ɠ��ꂳ���邽��new���Z�q�œ��I��������
		gadget_phandle_collection_[i] = new PositionHandle;
		NyaPosition::CreateHandle(gadget_phandle_collection_[i]);
	}
}

DeviceGadget34::~DeviceGadget34()
{
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{	// �R���X�g���N�^�̏����Ɠ��ꂷ�邽��NyaPosition::DeleteHandle(PositionHandle*)�łȂ�delete���g��
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
	{	// �f�X�g���N�^�̏����Ɠ��ꂳ���邽��new���Z�q�œ��I��������
		gadget_phandle_collection_[i] = new PositionHandle;
		NyaPosition::CreateHandle(gadget_phandle_collection_[i]);
	}
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
	{	// �R���X�g���N�^�̏����Ɠ��ꂷ�邽��NyaPosition::DeleteHandle(PositionHandle*)�łȂ�delete���g��
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}

DeviceGadget1424::DeviceGadget1424()
{
	effect_epx_ = new EffectPropertyX2;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{	// �f�X�g���N�^�̏����Ɠ��ꂳ���邽��new���Z�q�œ��I��������
		gadget_phandle_collection_[i] = new PositionHandle;
		NyaPosition::CreateHandle(gadget_phandle_collection_[i]);
	}
}

DeviceGadget1424::~DeviceGadget1424()
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
	{	// �R���X�g���N�^�̏����Ɠ��ꂷ�邽��NyaPosition::DeleteHandle(PositionHandle*)�łȂ�delete���g��
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}


DeviceGadget2414::DeviceGadget2414()
{
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX2;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{	// �f�X�g���N�^�̏����Ɠ��ꂳ���邽��new���Z�q�œ��I��������
		gadget_phandle_collection_[i] = new PositionHandle;
		NyaPosition::CreateHandle(gadget_phandle_collection_[i]);
	}
}

DeviceGadget2414::~DeviceGadget2414()
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
	{	// �R���X�g���N�^�̏����Ɠ��ꂷ�邽��NyaPosition::DeleteHandle(PositionHandle*)�łȂ�delete���g��
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}

DeviceGadget3414::DeviceGadget3414()
{
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX3;
	gadget_gpx_ = new GraphicPropertyX4;
	for (int i = 0; i < DEVICE_COLLISION_MAX_ACCURACY; i++)
	{	// �f�X�g���N�^�̏����Ɠ��ꂳ���邽��new���Z�q�œ��I��������
		gadget_phandle_collection_[i] = new PositionHandle;
		NyaPosition::CreateHandle(gadget_phandle_collection_[i]);
	}
}

DeviceGadget3414::~DeviceGadget3414()
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
	{	// �R���X�g���N�^�̏����Ɠ��ꂷ�邽��NyaPosition::DeleteHandle(PositionHandle*)�łȂ�delete���g��
		delete gadget_phandle_collection_[i];
		gadget_phandle_collection_[i] = nullptr;
	}
}

//***************************
// NyaDevice �����o�֐�
//***************************

/**
@brief �U��14�֐�
@param gadget_dpx �K�W�F�b�g�p�f�o�C�X�v���p�e�B
@param gadget_gpx �K�W�F�b�g�p�O���t�B�b�N�v���p�e�B
@param gadget_type �K�W�F�b�g�̃I�u�W�F�N�g�^�C�v
@param collision_accuracy �Փ˔���̐��x
@note
 �Փ˔���̐��x��[1-9]�̒l�Ŏw��A�傫���l�قǍ����x�ɂȂ�
 ���ꂼ��̈����Ŏw�肵���v���p�e�B�̃����o�̒��Ŏg�p���Ȃ��l�͐ݒ肵�Ă����������
**/
void NyaDevice::Attack14(const DevicePropertyX1* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type,  unsigned int collision_accuracy)
{
	static list<DeviceGadget14>::iterator it_from, it_to;

	// �����ł��Ȃ��Ƃ��̓T�C�Y�𑝂₷
	if (gadget14_wait_list_.begin() == gadget14_wait_list_.end())
		gadget14_wait_list_.resize(1);

	// �Փː��x�̒l���͈͊O�̂Ƃ��͖�����
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget14_wait_list_.begin();
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

	it_to = gadget14_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget14_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget14_wait_list_), it_from);
}

/**
@brief �U��24�֐�
@param gadget_dpx �K�W�F�b�g�p�f�o�C�X�v���p�e�B
@param gadget_gpx �K�W�F�b�g�p�O���t�B�b�N�v���p�e�B
@param gadget_type �K�W�F�b�g�̃I�u�W�F�N�g�^�C�v
@param collision_accuracy �Փ˔���̐��x
@note
 �Փ˔���̐��x��[1-9]�̒l�Ŏw��A�傫���l�قǍ����x�ɂȂ�
 ���ꂼ��̈����Ŏw�肵���v���p�e�B�̃����o�̒��Ŏg�p���Ȃ��l�͐ݒ肵�Ă����������
**/
void NyaDevice::Attack24(const DevicePropertyX2* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type,  unsigned int collision_accuracy)
{
	static list<DeviceGadget24>::iterator it_from, it_to;

	// �����ł��Ȃ��Ƃ��̓T�C�Y�𑝂₷
	if (gadget24_wait_list_.begin() == gadget24_wait_list_.end())
		gadget24_wait_list_.resize(1);

	// �Փː��x�̒l���͈͊O�̂Ƃ��͖�����
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget24_wait_list_.begin();
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

	it_to = gadget24_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget24_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget24_wait_list_), it_from);
}

/**
@brief �U��34�֐�
@param gadget_dpx �K�W�F�b�g�p�f�o�C�X�v���p�e�B
@param gadget_gpx �K�W�F�b�g�p�O���t�B�b�N�v���p�e�B
@param gadget_type �K�W�F�b�g�̃I�u�W�F�N�g�^�C�v
@param collision_accuracy �Փ˔���̐��x
@note
 �Փ˔���̐��x��[1-9]�̒l�Ŏw��A�傫���l�قǍ����x�ɂȂ�
 ���ꂼ��̈����Ŏw�肵���v���p�e�B�̃����o�̒��Ŏg�p���Ȃ��l�͐ݒ肵�Ă����������
**/
void NyaDevice::Attack34(const DevicePropertyX3* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type,  unsigned int collision_accuracy)
{
	static list<DeviceGadget34>::iterator it_from, it_to;

	// �����ł��Ȃ��Ƃ��̓T�C�Y�𑝂₷
	if (gadget34_wait_list_.begin() == gadget34_wait_list_.end())
		gadget34_wait_list_.resize(1);

	// �Փː��x�̒l���͈͊O�̂Ƃ��͖�����
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget34_wait_list_.begin();
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

	it_to = gadget34_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget34_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget34_wait_list_), it_from);
}

/**
@brief �U��1414�֐�
@param gadget_dpx �K�W�F�b�g�p�f�o�C�X�v���p�e�B
@param gadget_gpx �K�W�F�b�g�p�O���t�B�b�N�v���p�e�B
@param effect_dpx �G�t�F�N�g�p�f�o�C�X�v���p�e�B
@param effect_gpx �G�t�F�N�g�p�O���t�B�b�N�v���p�e�B
@param gadget_type �K�W�F�b�g�̃I�u�W�F�N�g�^�C�v
@param effect_type �G�t�F�N�g�̃I�u�W�F�N�g�^�C�v
@param collision_accuracy �Փ˔���̐��x
@note
 �G�t�F�N�g�t���U���֐�
 �Փ˔���̐��x��[1-9]�̒l�Ŏw��A�傫���l�قǍ����x�ɂȂ�
 ���ꂼ��̈����Ŏw�肵���v���p�e�B�̃����o�̒��Ŏg�p���Ȃ��l�͐ݒ肵�Ă����������
**/
void NyaDevice::Attack1414(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget1414>::iterator it_from, it_to;

	// �ő���܂Ő�������Ă���Ƃ��͉������Ȃ�
	if (gadget1414_wait_list_.begin() == gadget1414_wait_list_.end())
		gadget1414_wait_list_.resize(1);

	// �Փː��x�̒l���͈͊O�̂Ƃ��͖�����
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget1414_wait_list_.begin();
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
	it_from->effect_gpx_->file_.div_collection_ = gadget_gpx->file_.div_collection_;
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
	it_to = gadget1414_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget1414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget1414_wait_list_), it_from);
}

/**
@brief �U��1424�֐�
@param gadget_dpx �K�W�F�b�g�p�f�o�C�X�v���p�e�B
@param gadget_gpx �K�W�F�b�g�p�O���t�B�b�N�v���p�e�B
@param effect_dpx �G�t�F�N�g�p�f�o�C�X�v���p�e�B
@param effect_gpx �G�t�F�N�g�p�O���t�B�b�N�v���p�e�B
@param gadget_type �K�W�F�b�g�̃I�u�W�F�N�g�^�C�v
@param effect_type �G�t�F�N�g�̃I�u�W�F�N�g�^�C�v
@param collision_accuracy �Փ˔���̐��x
@note
 �G�t�F�N�g�t���U���֐�
 �Փ˔���̐��x��[1-9]�̒l�Ŏw��A�傫���l�قǍ����x�ɂȂ�
 ���ꂼ��̈����Ŏw�肵���v���p�e�B�̃����o�̒��Ŏg�p���Ȃ��l�͐ݒ肵�Ă����������
**/
void NyaDevice::Attack1424(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX2* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget1424>::iterator it_from, it_to;

	// �ő���܂Ő�������Ă���Ƃ��͉������Ȃ�
	if (gadget1424_wait_list_.begin() == gadget1424_wait_list_.end())
		gadget1424_wait_list_.resize(1);

	// �Փː��x�̒l���͈͊O�̂Ƃ��͖�����
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget1424_wait_list_.begin();
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
	it_from->effect_gpx_->file_.div_collection_ = gadget_gpx->file_.div_collection_;
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
	it_to = gadget1424_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget1424_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget1424_wait_list_), it_from);
}

/**
@brief �U��2414�֐�
@param gadget_dpx �K�W�F�b�g�p�f�o�C�X�v���p�e�B
@param gadget_gpx �K�W�F�b�g�p�O���t�B�b�N�v���p�e�B
@param effect_dpx �G�t�F�N�g�p�f�o�C�X�v���p�e�B
@param effect_gpx �G�t�F�N�g�p�O���t�B�b�N�v���p�e�B
@param gadget_type �K�W�F�b�g�̃I�u�W�F�N�g�^�C�v
@param effect_type �G�t�F�N�g�̃I�u�W�F�N�g�^�C�v
@param collision_accuracy �Փ˔���̐��x
@note
 �G�t�F�N�g�Ɗp���x���w��ł���U���֐�
 �Փ˔���̐��x��[1-9]�̒l�Ŏw��A�傫���l�قǍ����x�ɂȂ�
 ���ꂼ��̈����Ŏw�肵���v���p�e�B�̃����o�̒��Ŏg�p���Ȃ��l�͐ݒ肵�Ă����������
**/

void NyaDevice::Attack2414(const DevicePropertyX2* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget2414>::iterator it_from, it_to;

	if (gadget2414_wait_list_.begin() == gadget2414_wait_list_.end())
		gadget2414_wait_list_.resize(1);

	// �Փː��x�̒l���͈͊O�̂Ƃ��͖�����
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget2414_wait_list_.begin();
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

	it_to = gadget2414_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget2414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget2414_wait_list_), it_from);
}

/**
@brief �U��2414�֐�
@param gadget_dpx �K�W�F�b�g�p�f�o�C�X�v���p�e�B
@param gadget_gpx �K�W�F�b�g�p�O���t�B�b�N�v���p�e�B
@param effect_dpx �G�t�F�N�g�p�f�o�C�X�v���p�e�B
@param effect_gpx �G�t�F�N�g�p�O���t�B�b�N�v���p�e�B
@param gadget_type �K�W�F�b�g�̃I�u�W�F�N�g�^�C�v
@param effect_type �G�t�F�N�g�̃I�u�W�F�N�g�^�C�v
@param collision_accuracy �Փ˔���̐��x
@note
 �G�t�F�N�g�Ɗp���x���w��ł���U���֐�
 �Փ˔���̐��x��[1-9]�̒l�Ŏw��A�傫���l�قǍ����x�ɂȂ�
 ���ꂼ��̈����Ŏw�肵���v���p�e�B�̃����o�̒��Ŏg�p���Ȃ��l�͐ݒ肵�Ă����������
**/
void NyaDevice::Attack3414(const DevicePropertyX3* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy)
{
	static list<DeviceGadget3414>::iterator it_from, it_to;

	if (gadget3414_wait_list_.begin() == gadget3414_wait_list_.end())
		gadget3414_wait_list_.resize(1);

	// �Փː��x�̒l���͈͊O�̂Ƃ��͖�����
	if (collision_accuracy < 1 && 10 < collision_accuracy)
		collision_accuracy = 1;

	it_from = gadget3414_wait_list_.begin();
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

	it_to = gadget3414_attack_list_[static_cast<int>(gadget_type)].begin();
	gadget3414_attack_list_[static_cast<int>(gadget_type)].splice(it_to, move(gadget3414_wait_list_), it_from);
}

/**
 @brief �N���A�֐�
 @param type �N���A����I�u�W�F�N�g�^�C�v
 @note
  �����Ŏw�肵��type��gadget��S�ăN���A����
**/
void NyaDevice::Clear(eOBJECT type)
{
	for (auto& e : gadget14_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget24_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget34_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget1414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget2414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
	for (auto& e : gadget3414_attack_list_[static_cast<int>(type)])
		e.clear_ = true;
}

void NyaDevice::Run(void)
{
	for (eOBJECT type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; ++type)
		CalculateGadget(type);

#ifdef __DEBUG__
	size_t wait_size = 0;
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	wait_size += gadget14_wait_list_.size();
	wait_size += gadget24_wait_list_.size();
	wait_size += gadget34_wait_list_.size();
	wait_size += gadget1414_wait_list_.size();
	wait_size += gadget2414_wait_list_.size();
	wait_size += gadget3414_wait_list_.size();
	NyaString::Write("debug_font", white, 50, 210, "[50, 210] device_wait_list size = %u", (unsigned int)wait_size);
#endif
}

size_t NyaDevice::Size(eOBJECT type)
{
	size_t attack_size = 0;

	attack_size += gadget14_attack_list_[static_cast<int>(type)].size();
	attack_size += gadget24_attack_list_[static_cast<int>(type)].size();
	attack_size += gadget34_attack_list_[static_cast<int>(type)].size();
	attack_size += gadget1414_attack_list_[static_cast<int>(type)].size();
	attack_size += gadget2414_attack_list_[static_cast<int>(type)].size();
	attack_size += gadget3414_attack_list_[static_cast<int>(type)].size();

	return attack_size;
}


void NyaDevice::CalculateGadget(eOBJECT type)
{
	deque<list<DeviceGadget14>::iterator> gadget14_delete_deque;
	deque<list<DeviceGadget24>::iterator> gadget24_delete_deque;
	deque<list<DeviceGadget34>::iterator> gadget34_delete_deque;
	deque<list<DeviceGadget1414>::iterator> gadget1414_delete_deque;
	deque<list<DeviceGadget1424>::iterator> gadget1424_delete_deque;
	deque<list<DeviceGadget2414>::iterator> gadget2414_delete_deque;
	deque<list<DeviceGadget3414>::iterator> gadget3414_delete_deque;

	//***********************
	// Gadget14 �폜����
	//***********************
	for (auto it = gadget14_attack_list_[static_cast<int>(type)].begin(); it != gadget14_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �t���[���J�E���g���x�����ԂɒB���Ă��Ȃ��Ȃ牽�����Ȃ�
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// �\���̈�̌��E�𒴂���
		// �N���A���w�肳�ꂽ
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			gadget14_delete_deque.push_back(it);
		else if (it->clear_)
			gadget14_delete_deque.push_back(it);
		else
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->gadget_phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					gadget14_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget14_delete_deque.empty())
	{
		gadget14_wait_list_.splice(gadget14_wait_list_.begin(), move(gadget14_attack_list_[static_cast<int>(type)]), gadget14_delete_deque.front());
		gadget14_delete_deque.pop_front();
	}

	//****************************
	// gadget14 �폜�ȊO�̏���
	//****************************
	for (auto& e : gadget14_attack_list_[static_cast<int>(type)])
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
			e.gadget_phandle_collection_[i]->grid_y_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.gadget_phandle_collection_[i], type);
		}
		
		// �`�揈��
		e.gadget_gpx_->draw_grid_cx_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.gadget_gpx_->draw_grid_cy_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.gadget_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.gadget_gpx_, type);
	}

	//***********************
	// Gadget24 �폜����
	//***********************
	for (auto it = gadget24_attack_list_[static_cast<int>(type)].begin(); it != gadget24_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �t���[���J�E���g���x�����ԂɒB���Ă��Ȃ��Ȃ牽�����Ȃ�
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// �\���̈�̌��E�𒴂���
		// �N���A���w�肳�ꂽ
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			gadget24_delete_deque.push_back(it);
		else if (it->clear_)
			gadget24_delete_deque.push_back(it);
		else
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->gadget_phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					gadget24_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget24_delete_deque.empty())
	{
		gadget24_wait_list_.splice(gadget24_wait_list_.begin(), move(gadget24_attack_list_[static_cast<int>(type)]), gadget24_delete_deque.front());
		gadget24_delete_deque.pop_front();
	}

	//****************************
	// gadget24 �폜�ȊO�̏���
	//****************************
	for (auto& e : gadget24_attack_list_[static_cast<int>(type)])
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
			e.gadget_phandle_collection_[i]->grid_y_ = e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_ + e.move_y_ * (i + 1);
			NyaPosition::Collide(e.gadget_phandle_collection_[i], type);
		}
		
		// �`�揈��
		e.gadget_gpx_->draw_grid_cx_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_x_;
		e.gadget_gpx_->draw_grid_cy_ = (int)e.gadget_phandle_collection_[e.collision_accuracy_ - 1]->grid_y_;
		e.gadget_gpx_->draw_angle_deg_ = e.gadget_dpx_->draw_angle_deg_;
		NyaGraphic::Draw(e.gadget_gpx_, type);
	}

	//***********************
	// Gadget34 �폜����
	//***********************
	for (auto it = gadget34_attack_list_[static_cast<int>(type)].begin(); it != gadget34_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �t���[���J�E���g���x�����ԂɒB���Ă��Ȃ��Ȃ牽�����Ȃ�
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// �\���̈�̌��E�𒴂���
		// �N���A���w�肳�ꂽ
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			gadget34_delete_deque.push_back(it);
		else if (it->clear_)
			gadget34_delete_deque.push_back(it);
		else
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->gadget_phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					gadget34_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget34_delete_deque.empty())
	{
		gadget34_wait_list_.splice(gadget34_wait_list_.begin(), move(gadget34_attack_list_[static_cast<int>(type)]), gadget34_delete_deque.front());
		gadget34_delete_deque.pop_front();
	}

	//****************************
	// gadget34 �폜�ȊO�̏���
	//****************************
	for (auto& e : gadget34_attack_list_[static_cast<int>(type)])
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
		// �����x�̏���
		e.gadget_dpx_->move_speed_ += e.gadget_dpx_->move_speed_accel_;
		e.move_x_ = cos(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_x_ /= e.collision_accuracy_;
		e.move_y_ = sin(e.move_angle_rad_) * e.gadget_dpx_->move_speed_;
		e.move_y_ /= e.collision_accuracy_;

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
	for (auto it = gadget1414_attack_list_[static_cast<int>(type)].begin(); it != gadget1414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �t���[���J�E���g���x�����ԂɒB���Ă��Ȃ��Ȃ牽�����Ȃ�
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// �\���̈�̌��E�𒴂���
		// �N���A���w�肳�ꂽ
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			gadget1414_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			gadget1414_delete_deque.push_back(it);
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
					gadget1414_delete_deque.push_back(it);
					break;
				}
			}
		}

	}
	while (!gadget1414_delete_deque.empty())
	{
		gadget1414_wait_list_.splice(gadget1414_wait_list_.begin(), move(gadget1414_attack_list_[static_cast<int>(type)]), gadget1414_delete_deque.front());
		gadget1414_delete_deque.pop_front();
	}

	//****************************
	// gadget1414 �폜�ȊO�̏���
	//****************************
	for (auto& e : gadget1414_attack_list_[static_cast<int>(type)])
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
	// Gadget1424 �폜����
	// �폜����Ƃ��ɃG�t�F�N�g�`��������Ȃ�
	//*******************************************
	for (auto it = gadget1424_attack_list_[static_cast<int>(type)].begin(); it != gadget1424_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �t���[���J�E���g���x�����ԂɒB���Ă��Ȃ��Ȃ牽�����Ȃ�
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// �\���̈�̌��E�𒴂���
		// �N���A���w�肳�ꂽ
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			gadget1424_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = &it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = &it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			gadget1424_delete_deque.push_back(it);
		}
		else 
		{
			for (unsigned int i = 0; i < it->collision_accuracy_; i++)
			{
				if (it->gadget_phandle_collection_[i]->collision_hit_damage_ != 0)
				{
					it->effect_epx_->gap_x_ = it->gadget_phandle_collection_[i]->collision_hit_handle_->grid_x_ - it->gadget_phandle_collection_[i]->collision_hit_x_;
					it->effect_epx_->gap_y_ = it->gadget_phandle_collection_[i]->collision_hit_y_ - it->gadget_phandle_collection_[i]->collision_hit_handle_->grid_y_;
					it->effect_epx_->grid_x_ = &it->gadget_phandle_collection_[i]->collision_hit_handle_->grid_x_;
					it->effect_epx_->grid_y_ = &it->gadget_phandle_collection_[i]->collision_hit_handle_->grid_y_;
					NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
					gadget1424_delete_deque.push_back(it);
					break;
				}
			}
		}

	}
	while (!gadget1424_delete_deque.empty())
	{
		gadget1424_wait_list_.splice(gadget1424_wait_list_.begin(), move(gadget1424_attack_list_[static_cast<int>(type)]), gadget1424_delete_deque.front());
		gadget1424_delete_deque.pop_front();
	}

	//****************************
	// gadget1424 �폜�ȊO�̏���
	//****************************
	for (auto& e : gadget1424_attack_list_[static_cast<int>(type)])
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
	for (auto it = gadget2414_attack_list_[static_cast<int>(type)].begin(); it != gadget2414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �t���[���J�E���g���x�����ԂɒB���Ă��Ȃ��Ȃ牽�����Ȃ�
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// �\���̈�̌��E�𒴂���
		// �N���A���w�肳�ꂽ
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			gadget2414_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			gadget2414_delete_deque.push_back(it);
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
					gadget2414_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget2414_delete_deque.empty())
	{
		gadget2414_wait_list_.splice(gadget2414_wait_list_.begin(), move(gadget2414_attack_list_[static_cast<int>(type)]), gadget2414_delete_deque.front());
		gadget2414_delete_deque.pop_front();
	}

	//****************************
	// gadget2414 �폜�ȊO�̏���
	//****************************
	for (auto& e : gadget2414_attack_list_[static_cast<int>(type)])
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

	//*******************************************
	// gadget3414 �폜����
	// �폜����Ƃ��ɃG�t�F�N�g�`��������Ȃ�
	//*******************************************
	for (auto it = gadget3414_attack_list_[static_cast<int>(type)].begin(); it != gadget3414_attack_list_[static_cast<int>(type)].end(); ++it)
	{
		// �t���[���J�E���g���x�����ԂɒB���Ă��Ȃ��Ȃ牽�����Ȃ�
		if (it->count_frame_ < it->gadget_dpx_->delay_time_frame_)
			continue;

		// �\���̈�̌��E�𒴂���
		// �N���A���w�肳�ꂽ
		// ���̃I�u�W�F�N�g�ƏՓ˂���
		if (!NyaPosition::InScreen(it->gadget_phandle_collection_[it->collision_accuracy_ - 1]))
			gadget3414_delete_deque.push_back(it);
		else if (it->clear_)
		{
			it->effect_epx_->grid_x_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_x_;
			it->effect_epx_->grid_y_ = (int)it->gadget_phandle_collection_[it->collision_accuracy_ - 1]->grid_y_;
			NyaEffect::Draw(it->effect_epx_, it->effect_gpx_, it->effect_type_);
			gadget3414_delete_deque.push_back(it);
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
					gadget3414_delete_deque.push_back(it);
					break;
				}
			}
		}
	}
	while (!gadget3414_delete_deque.empty())
	{
		gadget3414_wait_list_.splice(gadget3414_wait_list_.begin(), move(gadget3414_attack_list_[static_cast<int>(type)]), gadget3414_delete_deque.front());
		gadget3414_delete_deque.pop_front();
	}

	//****************************
	// gadget3414 �폜�ȊO�̏���
	//****************************
	for (auto& e : gadget3414_attack_list_[static_cast<int>(type)])
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
		// �����x�̏���
		e.gadget_dpx_->move_speed_ += e.gadget_dpx_->move_speed_accel_;
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

