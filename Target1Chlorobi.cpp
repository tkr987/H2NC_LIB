#include "HNLIB.h"
#include "Target1Chlorobi.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "TeemoLock.h"

using namespace HNLIB;

Target1ChlorobiMainDeathDevice::Target1ChlorobiMainDeathDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 4;
	TeemoFactory::TargetAttackWhite6(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target1ChlorobiMainDeathDevice::~Target1ChlorobiMainDeathDevice()
{
	delete dpx_;
	dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

Target1ChlorobiMain::Target1ChlorobiMain() : exp_(5000), health_max_(10)
{
	lock_ = new TeemoLock(eLOCK::CHLOROBI);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);
	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 50);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load("img/target/main_chlorobi.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 16;
	phandle_->health_ = health_max_;
}

Target1ChlorobiMain::~Target1ChlorobiMain()
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

Target1Chlorobi::Target1Chlorobi()
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = -200;
	main_.phandle_->grid_y_ = -200;
	mode_ = 1;
}

Target1Chlorobi::~Target1Chlorobi()
{

}

void Target1Chlorobi::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		if (main_.phandle_->health_ <= 0)
		{
			NyaSound::Play(main_.death_spx_);
			NyaInterface::GetHandleSkill()->AddExp(main_.exp_);
		}
		break;
	case 2:
		return;
	};

	main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
	count_frame_++;
}

void Target1Chlorobi::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if (main_.phandle_->health_ <= 0)
			mode_ = 2;
		if (FPS_MAX * 10 < count_frame_)
			mode_ = 2;
		break;
	case 2:
		return;
	};
}

void Target1Chlorobi::Act1(void)
{
	if (count_frame_ == 1)
	{
		main_.phandle_->grid_x_ = NyaInput::GetRand(50, SCREEN_MAX_X - 50);
		main_.phandle_->grid_y_ = NyaInput::GetRand(-200, -100);
		NyaPosition::MoveSpeedMode(main_.phandle_, 90, 3, FPS_MAX * 8);
	}

	if (!NyaPosition::InScreen(main_.phandle_))
		return;

	// Õ“Ë”»’è@Õ“Ëƒ_ƒ[ƒW‚¾‚¯ŒoŒ±’l‚ð’Ç‰Á
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;

	if (main_.phandle_->health_ <= 0)
	{	// UŒ‚ˆ—
		PositionHandle phandle_user;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device_death_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device_death_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device_death_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) + NyaInput::GetRand(-3.0, 3.0);
		NyaDevice::Attack1414(main_.device_death_.dpx_, main_.device_death_.device_gpx_, main_.device_death_.epx_, main_.device_death_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}
}

void Target1Chlorobi::Draw1(void)
{
	// main •`‰æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	main_.gpx_->draw_angle_deg_ += 2;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ƒƒbƒN•`‰æ
	main_.lock_->Run(main_.phandle_);

	if (main_.phandle_->health_ <= 0)
	{	// ”š”­•`‰æ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);

	}

}
