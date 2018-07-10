#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaInterface.h"
#include "NyaPosition.h"
#include "TeemoEnum.h"
#include "TeemoTargetEx3.h"

using namespace std;
using namespace HNLIB;

//*************************************
// Act1(), Draw1() �Ŏg���N���X
//*************************************

TeemoExDevice311::TeemoExDevice311()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_BLUE2;
	dpx_->move_speed_ = 10;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue2.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice311::~TeemoExDevice311()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExCube31::TeemoExCube31()
{
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoExCube31::~TeemoExCube31()
{
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

//*************************************
// Act2(), Draw2() �Ŏg���N���X
//*************************************

TeemoExDevice321::TeemoExDevice321()
{
	dpx_ = new DevicePropertyX3;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_BLUE2;
	dpx_->move_speed_ = 0.1;
	dpx_->move_speed_accel_ = 0.02;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue2.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice321::~TeemoExDevice321()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExDevice322::TeemoExDevice322()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 8;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice322::~TeemoExDevice322()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExCube32::TeemoExCube32()
{
	death_epx_ = new EffectPropertyX1;
	death_epx_->interval_time_frame_ = 3;
	death_gpx_ = new GraphicPropertyX4;
	death_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &death_gpx_->file_);
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.01;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoExCube32::~TeemoExCube32()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

//*************************************
// Act3(), Draw3() �Ŏg���N���X
//*************************************

TeemoExDevice331::TeemoExDevice331()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_BLUE2;
	dpx_->move_speed_ = 8;
	way1_angle_ = 0;
	way2_angle_ = 180;
	way3_angle_ = 0;
	way4_angle_ = 180;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue2.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice331::~TeemoExDevice331()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExDevice332::TeemoExDevice332()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 3;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice332::~TeemoExDevice332()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

TeemoExCube33::TeemoExCube33()
{
	death_epx_ = new EffectPropertyX1;
	death_epx_->interval_time_frame_ = 3;
	death_gpx_ = new GraphicPropertyX4;
	death_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &death_gpx_->file_);
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.4;
	NyaGraphic::LoadGraphicFile(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoExCube33::~TeemoExCube33()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

//*****************
// TeemoEx3Main
//*****************

TeemoEx3Main::TeemoEx3Main() : health_max_(26000)
{
	death1_epx_ = new EffectPropertyX1;
	death1_epx_->interval_time_frame_ = 3;
	death1_gpx_ = new GraphicPropertyX4;
	death1_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &death1_gpx_->file_);

	death2_epx_ = new EffectPropertyX1;
	death2_epx_->interval_time_frame_ = 3;
	death2_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile(8, 8, "img/target/death2.png", &death2_gpx_->file_);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/teemo_ex3.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->health_ = health_max_;
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -100;
}

TeemoEx3Main::~TeemoEx3Main()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
	delete phandle_;
	phandle_ = nullptr;
}

//***********************************************
// TeemoTargetEx �R���X�g���N�^�E�f�X�g���N�^
//***********************************************

TeemoTargetEx3::TeemoTargetEx3()
{
	// �����o�ϐ�������
	count_frame_ = 0;
	mode_ = 1;

	// interface ������
	NyaInterface::GetHandleWarning()->LoadSound("sound/warning.wav", 20);
}


TeemoTargetEx3::~TeemoTargetEx3()
{
	NyaInterface::GetHandleWarning()->DeleteSound();
}

//***************************
// TeemoTargetEx �����o�֐�
//***************************

void TeemoTargetEx3::Act(void)
{
	switch (mode_)
	{
	case 1:
		Act1();
		break;
	case 2:
		Act2();
		break;
	case 3:
		Act3();
		break;
	case 4:
		if (count_frame_ == FPS_MAX * 8)
			NyaInterface::GetHandleComplete()->valid_ = true;
		break;
	}

	count_frame_++;

#ifdef __DEBUG__
		NyaString::Write("design_fps_font", white, 50, 90, "[50, 90] count_frame = %u", count_frame_);
#endif
}

void TeemoTargetEx3::Draw(void)
{
	switch (mode_)
	{
	case 1:
		Draw1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 70)
		{
			count_frame_ = 0;
			mode_ = 2;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
		}
		break;
	case 2:
		Draw2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 20)
		{
			count_frame_ = 0;
			mode_ = 3;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
		}
		break;
	case 3:
		Draw3();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= 0)
		{
			count_frame_ = 0;
			mode_ = 4;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
		}
		break;
	case 4:
		Draw4();
		break;
	}
}

void TeemoTargetEx3::Act1(void)
{
	static int cube_index = 0;

	// �s���J�n1�t���[����
	// mission ex ���[�h��true�ɂ���
	// mission warning �\�������s����
	// �����ʒu�ֈړ�����
	if (count_frame_ == 1)
	{
		NyaInterface::GetHandleHealth()->valid_ = true;
		NyaInterface::GetHandleWarning()->draw_valid_ = true;
		NyaInterface::GetHandleWarning()->sound_valid_ = true;
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);
	}

	// �Փ˔���@�Փ˃_���[�W�����o���l��ǉ�
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube31_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 5)
		return;

	if (count_frame_ % 5 == 0)
	{
		cube31_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_;
		cube31_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_;
		NyaPosition::MoveSpeedMode(cube31_collection_[cube_index].phandle_, NyaInput::GetRand(0, 360), 6, FPS_MAX * 4);
		cube_index = ++cube_index % 100;
	}

	if (count_frame_ % 5 == 0)
	{
		main_.device311_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device311_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 8; way++)
		{
			main_.device311_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
			NyaDevice::Attack1414(main_.device311_.dpx_, main_.device311_.gadget_gpx_, main_.device311_.epx_, main_.device311_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
	}
}

void TeemoTargetEx3::Act2(void)
{
	// �����ʒu�ֈړ�����
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);

	if (count_frame_ == FPS_MAX * 3)
	{
		for (int cube_index = 0; cube_index < cube32_collection_.size(); cube_index++)
		{	// cube�������ʒu�ֈړ�������
			cube32_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_;
			cube32_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_;
			NyaPosition::MoveGridMode(cube32_collection_[cube_index].phandle_, main_.phandle_->grid_x_ - 375 + (cube_index * 150) , 170, FPS_MAX * 2);
		}
	}

	// �Փ˔���@�Փ˃_���[�W�����o���l��ǉ�
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube32_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 5)
		return;

	if (count_frame_ % 4 == 0 && FPS_MAX * 5 < count_frame_ % (FPS_MAX * 15))
	{	// cube�U������
		DevicePropertyX1* cube_dpx;
		GraphicPropertyX4* cube_gadget_gpx;
		EffectPropertyX1* cube_epx;
		GraphicPropertyX4* cube_effect_gpx;
		PositionHandle phandle_user;
		int mod_frame = count_frame_ % (FPS_MAX * 15);
		for (auto& e : cube32_collection_)
		{
			cube_dpx = e.device322_.dpx_;
			cube_gadget_gpx = e.device322_.gadget_gpx_;
			cube_epx = e.device322_.epx_;
			cube_effect_gpx = e.device322_.effect_gpx_;
			cube_dpx->create_x_ = e.phandle_->grid_x_;
			cube_dpx->create_y_ = e.phandle_->grid_y_;
			if (FPS_MAX * 5 <= mod_frame && mod_frame < FPS_MAX * 7)
				cube_dpx->move_angle_deg_ = 90;
			else if (FPS_MAX * 7 <= mod_frame && mod_frame < FPS_MAX * 9)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-0.5, 0.5);
			else if (FPS_MAX * 9 <= mod_frame && mod_frame < FPS_MAX * 11)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-1.5, 1.5);
			else if (FPS_MAX * 11 <= mod_frame && mod_frame < FPS_MAX * 13)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-10, 10);
			else if (FPS_MAX * 13 <= mod_frame && mod_frame < FPS_MAX * 15)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-20, 20);
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			if (FPS_MAX * 5 <= mod_frame && mod_frame < FPS_MAX * 7)
				cube_dpx->move_angle_deg_ = 90;
			else if (FPS_MAX * 7 <= mod_frame && mod_frame < FPS_MAX * 9)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-5, 5);
			else if (FPS_MAX * 9 <= mod_frame && mod_frame < FPS_MAX * 11)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-10, 10);
			else if (FPS_MAX * 11 <= mod_frame && mod_frame < FPS_MAX * 13)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-15, 15);
			else if (FPS_MAX * 13 <= mod_frame && mod_frame < FPS_MAX * 15)
				cube_dpx->move_angle_deg_ = 90 + NyaInput::GetRand(-20, 20);
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
	}

	if (FPS_MAX * 12 < count_frame_ && count_frame_ % (FPS_MAX * 15) == FPS_MAX * 14)
	{	// main�U������
		main_.device321_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device321_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device321_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		for (int way = 0; way < 72; way++)
		{
			main_.device321_.dpx_->move_angle_deg_ += 5;
			NyaDevice::Attack3414(main_.device321_.dpx_, main_.device321_.gadget_gpx_, main_.device321_.epx_, main_.device321_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
	}

}

void TeemoTargetEx3::Act3(void)
{
	// �s���J�n1�t���[����
	// �����ʒu�ֈړ�����
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);

	// �Փ˔���@�Փ˃_���[�W�����o���l��ǉ�
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube33_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ == FPS_MAX * 3)
	{
		for (int cube_index = 0; cube_index < 4; cube_index++)
		{
			cube33_collection_[cube_index].phandle_->grid_x_ = main_.phandle_->grid_x_;
			cube33_collection_[cube_index].phandle_->grid_y_ = main_.phandle_->grid_y_;
		}
		NyaPosition::MoveGridMode(cube33_collection_[0].phandle_, main_.phandle_->grid_x_ - 300, 90, FPS_MAX * 2);
		NyaPosition::MoveGridMode(cube33_collection_[1].phandle_, main_.phandle_->grid_x_ - 150, 90, FPS_MAX * 2);
		NyaPosition::MoveGridMode(cube33_collection_[2].phandle_, main_.phandle_->grid_x_ + 150, 90, FPS_MAX * 2);
		NyaPosition::MoveGridMode(cube33_collection_[3].phandle_, main_.phandle_->grid_x_ + 300, 90, FPS_MAX * 2);
	}

	if (count_frame_ < FPS_MAX * 5)
		return;

	if (count_frame_ % 20 == 0)
	{	// main�U������
		main_.device331_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device331_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device331_.dpx_->move_angle_deg_ = main_.device331_.way1_angle_;
		main_.device331_.way1_angle_ += 10;
		for (int delay = 0; delay < 8; delay++)
		{
			main_.device331_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(main_.device331_.dpx_, main_.device331_.gadget_gpx_, main_.device331_.epx_, main_.device331_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device331_.dpx_->move_angle_deg_ = main_.device331_.way2_angle_;
		main_.device331_.way2_angle_ += 10;
		for (int delay = 0; delay < 8; delay++)
		{
			main_.device331_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(main_.device331_.dpx_, main_.device331_.gadget_gpx_, main_.device331_.epx_, main_.device331_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device331_.dpx_->move_angle_deg_ = main_.device331_.way3_angle_;
		main_.device331_.way3_angle_ -= 10;
		for (int delay = 0; delay < 8; delay++)
		{
			main_.device331_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(main_.device331_.dpx_, main_.device331_.gadget_gpx_, main_.device331_.epx_, main_.device331_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device331_.dpx_->move_angle_deg_ = main_.device331_.way4_angle_;
		main_.device331_.way4_angle_ -= 10;
		for (int delay = 0; delay < 8; delay++)
		{
			main_.device331_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(main_.device331_.dpx_, main_.device331_.gadget_gpx_, main_.device331_.epx_, main_.device331_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}

	if (count_frame_ % 15 == 0)
	{	// cube�U������
		DevicePropertyX1* cube_dpx;
		GraphicPropertyX4* cube_gadget_gpx;
		EffectPropertyX1* cube_epx;
		GraphicPropertyX4* cube_effect_gpx;
		PositionHandle phandle_user;
		NyaPosition::FindHandle("user_main_handle", &phandle_user);
		for (int i = 0; i < 4; i++)
		{
			cube_dpx = cube33_collection_[i].device332_.dpx_;
			cube_gadget_gpx = cube33_collection_[i].device332_.gadget_gpx_;
			cube_epx = cube33_collection_[i].device332_.epx_;
			cube_effect_gpx = cube33_collection_[i].device332_.effect_gpx_;
			cube_dpx->create_x_ = cube33_collection_[i].phandle_->grid_x_;
			cube_dpx->create_y_ = cube33_collection_[i].phandle_->grid_y_;
			cube_dpx->move_angle_deg_ = NyaPosition::Angle(cube33_collection_[i].phandle_, &phandle_user);
			cube_dpx->move_angle_deg_ += (NyaInput::GetRand(-25, 25) - 2);
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			cube_dpx->move_angle_deg_++;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			cube_dpx->move_angle_deg_++;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			cube_dpx->move_angle_deg_++;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			cube_dpx->move_angle_deg_++;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}
}

void TeemoTargetEx3::Draw1(void)
{
	// main�`��
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// �w���X�o�[(%)�̕\��������
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	for (auto& e : cube31_collection_)
	{	// cube�`��
		if (count_frame_ % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % 5;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 70)
	{	// cube����
		for (auto& e : cube32_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void TeemoTargetEx3::Draw2(void)
{
	// main�`��
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// �w���X�o�[(%)�̕\��������
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	if (count_frame_ < FPS_MAX * 3)
		return;

	for (auto& e : cube32_collection_)
	{	// cube�`��
		if (e.gpx_->extend_rate_ < 0.4)
			e.gpx_->extend_rate_ += 0.01;
		if (count_frame_ % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % 5;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < 20)
	{	// cube����
		for (auto& e : cube32_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void TeemoTargetEx3::Draw3(void)
{
	// main�`��
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);


	// �w���X�o�[(%)�̕\��������
	// �������A�w���X0�ȉ��̂Ƃ��Q�[�W0(%)�Ƃ��ĕ\������
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
	else
		NyaInterface::GetHandleHealth()->value_ = 0;

	if (count_frame_ < FPS_MAX * 3)
		return;

	for (auto& e : cube33_collection_)
	{	// cube�`��
		if (count_frame_ % 5 == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % 5;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
	}

	
	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= 0)
	{	// cube����
		for (auto& e : cube33_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void TeemoTargetEx3::Draw4(void)
{
	if (count_frame_ < 30 * 7)
	{
		if (count_frame_ % 30 == 0)
		{	//����������
			main_.death1_epx_->grid_x_ = main_.phandle_->grid_x_ + NyaInput::GetRand(-30, 30);
			main_.death1_epx_->grid_y_ = main_.phandle_->grid_y_ + NyaInput::GetRand(-30, 30);
			NyaEffect::Draw(main_.death1_epx_, main_.death1_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}

	if (count_frame_ == 30 * 8)
	{	// �唚������
		main_.death2_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death2_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death2_epx_, main_.death2_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaGraphic::Swing();
	}

	if (count_frame_ < 30 * 10)
	{	// main�`��
		main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
		main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
		NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	}

	// �w���X�o�[(%)�̕\��������
	// �������A�w���X0�ȉ��̂Ƃ��Q�[�W0(%)�Ƃ��ĕ\������
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
	else
		NyaInterface::GetHandleHealth()->value_ = 0;
}
