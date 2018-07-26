#include "HNLIB.h"
#include "Target1Dictyoglomi.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "TeemoLock.h"

using namespace HNLIB;

Target1DictyoglomiMainDevice::Target1DictyoglomiMainDevice()
{
	dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 4;
	TeemoFactory::TargetAttackOrange2(dpx_, gadget_gpx_, epx_, effect_gpx_);

}

Target1DictyoglomiMainDevice::~Target1DictyoglomiMainDevice()
{
	NyaGraphic::Delete(&gadget_gpx_->file_);
	NyaGraphic::Delete(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

Target1DictyoglomiMain::Target1DictyoglomiMain() : exp_(5000), health_max_(10)
{
	lock_ = new TeemoLock(eLOCK::DICTYOGLOMI);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(4, 1, "img/target/main_dictyoglomi.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 6;
	phandle_->health_ = health_max_;
}

Target1DictyoglomiMain::~Target1DictyoglomiMain()
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

Target1Dictyoglomi::Target1Dictyoglomi(int x, int y, int move_max_x, int move_max_y)
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
	move_max_x_ = move_max_x;
	move_max_y_ = move_max_y;
}

Target1Dictyoglomi::~Target1Dictyoglomi()
{

}

void Target1Dictyoglomi::Act(void)
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

	count_frame_++;
}

void Target1Dictyoglomi::Draw(void)
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

void Target1Dictyoglomi::Act1(void)
{
	PositionHandle phandle_user;
	
	// ‰ŠúˆÊ’u‚ÖˆÚ“®
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, move_max_x_, move_max_y_, FPS_MAX * 2);

	if (!NyaPosition::InScreen(main_.phandle_))
		return;

	// Õ“Ë”»’è@Õ“Ëƒ_ƒ[ƒW‚¾‚¯ŒoŒ±’l‚ð’Ç‰Á
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;

	if (count_frame_ == FPS_MAX * 2)
	{	// UŒ‚ˆ—
		main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaPosition::FindHandle("user", &phandle_user);
		double attack_angle = NyaPosition::Angle(main_.phandle_, &phandle_user) + NyaInput::GetRand(-2, 2);

		main_.device_.dpx_->delay_time_frame_ = 0;
		main_.device_.dpx_->move_angle_deg_ =  attack_angle - 5;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->move_angle_deg_ = attack_angle;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->move_angle_deg_ = attack_angle + 5;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}
	
	if (count_frame_ == FPS_MAX * 3)
	{	// user‘_‚¢‚ÌˆÚ“®ˆ—
		NyaPosition::FindHandle("user", &phandle_user);
		move_angle_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
		NyaPosition::MoveSpeedMode(main_.phandle_, move_angle_, 5, FPS_MAX * 5);
	}
}

void Target1Dictyoglomi::Draw1(void)
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
	{	// ”š”­•`‰æ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);

	}

}
