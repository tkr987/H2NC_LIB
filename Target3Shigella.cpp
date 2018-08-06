#include "HNLIB.h"
#include "Target3Shigella.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "TeemoLock.h"

using namespace HNLIB;

Target3ShigellaDevice::Target3ShigellaDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 2;
	TeemoFactory::TargetAttackBlue1(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target3ShigellaDevice::~Target3ShigellaDevice()
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

Target3ShigellaMain::Target3ShigellaMain(): exp_(2000), health_max_(100)
{
	lock_ = new TeemoLock(eLOCK::SHIGELLA);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, TARGET_DEATH1_SOUND_VOLUME);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(10, 2, "img/target/target_shigella.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 10;
	phandle_->health_ = health_max_;
}

Target3ShigellaMain::~Target3ShigellaMain()
{
	NyaSound::Delete(&death_spx_->file_);
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

Target3Shigella::Target3Shigella(int x, int y)
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
}

Target3Shigella::~Target3Shigella()
{

}

void Target3Shigella::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		break;
	case 2:
		Act2();
		if (main_.phandle_->health_ <= 0)
		{
			NyaSound::Play(main_.death_spx_);
			NyaInterface::GetHandleSkill()->AddExp(main_.exp_);
		}
		break;
	case 3:
		return;
	};

	main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
	count_frame_++;
}

void Target3Shigella::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if (NyaPosition::InScreen(main_.phandle_))
			mode_ = 2;
		break;
	case 2:
		Draw2();
		if (main_.phandle_->health_ <= 0)
			mode_ = 3;
		if (FPS_MAX * 40 < count_frame_)
			mode_ = 3;
		break;
	case 3:
		return;
	};
}

void Target3Shigella::Act1(void)
{
	// ‰½‚à‚µ‚È‚¢
}

void Target3Shigella::Act2(void)
{
	if (NyaInput::GetFrameCount() % 20 == 0 && main_.gpx_->file_div_ == 0)
	{	// UŒ‚ˆ—
		device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 360 / 6; way++)
		{
			device_.dpx_->move_angle_deg_ += 6;
			NyaDevice::Attack1414(device_.dpx_, device_.device_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}

	// Õ“Ë”»’è@Õ“Ëƒ_ƒ[ƒW‚¾‚¯ŒoŒ±’l‚ð’Ç‰Á
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
}

void Target3Shigella::Draw1(void)
{
	// main •`‰æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ƒƒbƒN•`‰æ
	main_.lock_->Run(main_.phandle_);
}

void Target3Shigella::Draw2(void)
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

