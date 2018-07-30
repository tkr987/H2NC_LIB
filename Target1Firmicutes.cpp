#include "HNLIB.h"
#include "Target1Firmicutes.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "TeemoLock.h"

using namespace HNLIB;

Target1FirmicutesMainDevice::Target1FirmicutesMainDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 4;
	TeemoFactory::TargetAttackOrange2(dpx_, device_gpx_, epx_, effect_gpx_);

}

Target1FirmicutesMainDevice::~Target1FirmicutesMainDevice()
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

Target1FirmicutesMain::Target1FirmicutesMain() : exp_(5000), health_max_(50)
{
	lock_ = new TeemoLock(eLOCK::AQUIFICAE);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(10, 2, "img/target/main_firmicutes.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 16;
	phandle_->health_ = health_max_;
}

Target1FirmicutesMain::~Target1FirmicutesMain()
{
	NyaGraphic::Delete(&gpx_->file_);

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

Target1Firmicutes::Target1Firmicutes(int x, int y)
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
}

Target1Firmicutes::~Target1Firmicutes()
{

}

void Target1Firmicutes::Act(void)
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

void Target1Firmicutes::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if (main_.phandle_->health_ <= 0)
			mode_ = 2;
		if (FPS_MAX * 30 < count_frame_)
			mode_ = 2;
		break;
	case 2:
		return;
	};
}

void Target1Firmicutes::Act1(void)
{

	if (!NyaPosition::InScreen(main_.phandle_))
		return;

	// Õ“Ë”»’è@Õ“Ëƒ_ƒ[ƒW‚¾‚¯ŒoŒ±’l‚ð’Ç‰Á
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;

	if (main_.gpx_->file_div_== 1 && count_frame_ % 5 == 0)
	{	// UŒ‚ˆ—
		PositionHandle phandle_user;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) + NyaInput::GetRand(-3.0, 3.0);
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}
}

void Target1Firmicutes::Draw1(void)
{
	// main •`‰æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 5 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;	
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
