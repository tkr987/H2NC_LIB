#include "HNLIB.h"
#include "Target2Ectromelia.h"
#include "TeemoLock.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"

using namespace HNLIB;

Target2EctromeliaDevice::Target2EctromeliaDevice()
{
	dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 2;
	TeemoFactory::TargetAttackOrange3(dpx_, gadget_gpx_, epx_, effect_gpx_);
}

Target2EctromeliaDevice::~Target2EctromeliaDevice()
{
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

Target2EctromeliaMain::Target2EctromeliaMain() : health_max_(6) 
{
	lock_ = new TeemoLock(eLOCK::ECTROMELIA);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(4, 1, "img/target/main_ectromelia.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 10;
	phandle_->health_ = health_max_;
}

Target2EctromeliaMain::~Target2EctromeliaMain()
{
	NyaGraphic::Delete(&gpx_->file_);

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

Target2Ectromelia::Target2Ectromelia(int x, int y)
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
}


Target2Ectromelia::~Target2Ectromelia()
{

}

void Target2Ectromelia::Act(void)
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

void Target2Ectromelia::Draw(void)
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
			NyaInterface::GetHandleSkill()->AddExp(10000);
			NyaSound::Play(main_.death_spx_);
		}
		break;
	};

	count_frame_++;
}

void Target2Ectromelia::Act1(void)
{
	if (count_frame_ == 1)
		NyaPosition::MoveSpeedMode(main_.phandle_, 270, 7, FPS_MAX * 10);
}

void Target2Ectromelia::Act2(void)
{
	// Õ“Ë”»’è@Õ“Ëƒ_ƒ[ƒW‚¾‚¯ŒoŒ±’l‚ð’Ç‰Á
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;

	if (main_.phandle_->health_ <= 0)
	{	// main UŒ‚ˆ—
		PositionHandle phandle_user;
		main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}
}

void Target2Ectromelia::Draw1(void)
{
	// main •`‰æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ƒƒbƒN•`‰æ
	main_.lock_->Run(main_.phandle_);

	if (main_.phandle_->health_ <= 0)
	{	// main ”š”­•`‰æ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
	}
}

void Target2Ectromelia::Draw2(void)
{
	// main •`‰æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ƒƒbƒN•`‰æ
	main_.lock_->Run(main_.phandle_);

	if (main_.phandle_->health_ <= 0)
	{	// main ”š”­•`‰æ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
	}
}

