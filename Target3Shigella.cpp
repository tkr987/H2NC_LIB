#include "HNLIB.h"
#include "Target3Shigella.h"
#include "TeemoEnum.h"

using namespace HNLIB;

Target3ShigellaDevice::Target3ShigellaDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_ORANGE1;
	dpx_->move_speed_ = 2;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_orange1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

Target3ShigellaDevice::~Target3ShigellaDevice()
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

Target3ShigellaMain::Target3ShigellaMain()
{
	death_epx_ = new EffectPropertyX1;
	death_epx_->interval_time_frame_ = 3;

	death_gpx_ = new GraphicPropertyX4;
	death_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &death_gpx_->file_);

	death_spx_ = new SoundPropertyX;
	NyaSound::LoadFile("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 50);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile(10, 2, "img/target/target_shigella.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 10;
	phandle_->health_ = 90;

	lock_.LoadGraphic("img/target/lock_shigella.png");
}

Target3ShigellaMain::~Target3ShigellaMain()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaSound::DeleteSoundFile(&death_spx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);

	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

Target3Shigella::Target3Shigella(int x, int y)
{
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
		if (NyaPosition::InScreen(main_.phandle_))
			mode_ = 2;
		break;
	case 2:
		Act2();
		break;
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
		break;
	case 2:
		Draw2();
		if (main_.phandle_->health_ < 0)
			mode_ = 3;
		break;	
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
			NyaDevice::Attack1414(device_.dpx_, device_.gadget_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
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
	main_.lock_.Run(main_.phandle_);
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
	main_.lock_.Run(main_.phandle_);

	if (main_.phandle_->health_ < 0)
	{	// ”š”­•`‰æ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaSound::Play(main_.death_spx_);
		NyaInterface::GetHandleSkill()->AddExp(10000);
	}

}

