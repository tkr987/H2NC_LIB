#include "HNLIB.h"
#include "Target2Polyoma.h"
#include "TeemoLock.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"

using namespace HNLIB;

Target2PolyomaDevice::Target2PolyomaDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 5;
	TeemoFactory::TargetAttackOrange3(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target2PolyomaDevice::~Target2PolyomaDevice()
{
	NyaGraphic::Delete(&device_gpx_->file_);

	delete dpx_;
	dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

Target2PolyomaMain::Target2PolyomaMain() : exp_(2000), health_max_(50)
{
	lock_ = new TeemoLock(eLOCK::POLYOMA);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);
	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, TARGET_DEATH1_SOUND_VOLUME);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(2, 1, "img/target/main_polyoma.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->health_ = health_max_;
}

Target2PolyomaMain::~Target2PolyomaMain()
{
	NyaGraphic::Delete(&gpx_->file_);
	NyaSound::Delete(&death_spx_->file_);

	delete lock_;
	lock_ = nullptr;
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete death_spx_;
	death_spx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

Target2Polyoma::Target2Polyoma(int x, int y, bool turn)
{
	count_frame_ = 0;
	mode_ = 1;
	main_.gpx_->flag_turn_ = turn;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
}


Target2Polyoma::~Target2Polyoma()
{

}

void Target2Polyoma::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		break;
	case 2:
		Act2();
		break;
	};
}

void Target2Polyoma::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if (NyaPosition::InScreen(main_.phandle_))
		{
			count_frame_ = 0;
			mode_ = 2;
		}
		break;
	case 2:
		Draw2();
		if (main_.phandle_->health_ <= 0)
		{
			mode_ = 3;
			NyaInterface::GetHandleSkill()->AddExp(main_.exp_);
			NyaSound::Play(main_.death_spx_);
		}
		if (!NyaPosition::InScreen(main_.phandle_))
			mode_ = 3;
		break;
	};

	count_frame_++;
}

void Target2Polyoma::Act1(void)
{
	if (count_frame_ == 1 && main_.gpx_->flag_turn_)
		NyaPosition::MoveSpeedMode(main_.phandle_, 180, 6, FPS_MAX * 10);
	else if (count_frame_ == 1 && !main_.gpx_->flag_turn_)
		NyaPosition::MoveSpeedMode(main_.phandle_, 0, 6, FPS_MAX * 10);
}

void Target2Polyoma::Act2(void)
{
	// �Փ˔���@�Փ˃_���[�W�����o���l��ǉ�
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;

	if (count_frame_ % 30 == 0)
	{	// main �U������
		PositionHandle phandle_user;
		main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) + NyaInput::GetRand(-2.0, 2.0);
		main_.device_.dpx_->delay_time_frame_ = 0;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->delay_time_frame_ = 5;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->delay_time_frame_ = 10;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}
}

void Target2Polyoma::Draw1(void)
{
	// main �`��
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ���b�N�`��
	main_.lock_->Run(main_.phandle_);

	if (main_.phandle_->health_ <= 0)
	{	// main �����`��
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
	}
}

void Target2Polyoma::Draw2(void)
{
	// main �`��
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ���b�N�`��
	main_.lock_->Run(main_.phandle_);

	if (main_.phandle_->health_ <= 0)
	{	// main �����`��
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
	}
}

