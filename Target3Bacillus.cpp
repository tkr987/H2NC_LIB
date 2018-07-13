#include "HNLIB.h"
#include "TeemoEnum.h"
#include "Target3Bacillus.h"

using namespace HNLIB;

Target3BacillusDevice::Target3BacillusDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_ORANGE1;
	dpx_->move_speed_ = 4;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_orange1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);

}

Target3BacillusDevice::~Target3BacillusDevice()
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

Target3BacillusMain::Target3BacillusMain()
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
	NyaGraphic::LoadGraphicFile(4, 1, "img/target/target_bacillus.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 6;
	phandle_->health_ = 100;

	lock_.LoadGraphic("img/target/lock_pantoea.png");
}

Target3BacillusMain::~Target3BacillusMain()
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

Target3Bacillus::Target3Bacillus(int x, int y, int move_max_x, int move_max_y)
{
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
	move_max_x_ = move_max_x;
	move_max_y_ = move_max_y;
}

Target3Bacillus::~Target3Bacillus()
{

}

void Target3Bacillus::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		break;
	};

	count_frame_++;
}

void Target3Bacillus::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if (main_.phandle_->health_ < 0)
			mode_ = 2;
		break;
	};
}

void Target3Bacillus::Act1(void)
{
	PositionHandle phandle_user;

	if (count_frame_ == 0)
	{
		int rand_x = NyaInput::GetRand(-100, 100);
		int rand_y = NyaInput::GetRand(-100, 100);
		main_.phandle_->grid_x_ += rand_x;
		main_.phandle_->grid_y_ += rand_y;
		move_max_x_ += rand_x;
		move_max_y_ += NyaInput::GetRand(-100, 100);
		move_start_time_ = NyaInput::GetRand(1, FPS_MAX);
	}

	if (count_frame_ == move_start_time_)
		NyaPosition::MoveGridMode(main_.phandle_, move_max_x_, move_max_y_, FPS_MAX * 3);

	// Õ“Ë”»’è@Õ“Ëƒ_ƒ[ƒW‚¾‚¯ŒoŒ±’l‚ð’Ç‰Á
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;

	// UŒ‚ˆ—
	if (count_frame_ % 20 == 10)
	{
		if (NyaPosition::InScreen(main_.phandle_))
		{
			device_.dpx_->create_x_ = main_.phandle_->grid_x_;
			device_.dpx_->create_y_ = main_.phandle_->grid_y_;
			NyaPosition::FindHandle("user", &phandle_user);

			device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) - 5;
			NyaDevice::Attack1414(device_.dpx_, device_.gadget_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);

			device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
			NyaDevice::Attack1414(device_.dpx_, device_.gadget_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);

			device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) + 5;
			NyaDevice::Attack1414(device_.dpx_, device_.gadget_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}
	
	if (count_frame_ == FPS_MAX * 4 + 30)
	{
		NyaPosition::FindHandle("user", &phandle_user);
		move_angle_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
		NyaPosition::MoveLengthMode(main_.phandle_, move_angle_, 1000, FPS_MAX * 3);
	}

}

void Target3Bacillus::Draw1(void)
{
	// main •`‰æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (count_frame_ % 30 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % 4;	
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	main_.lock_.Run(main_.phandle_);

	if (main_.phandle_->health_ < 0)
	{	// ”š”­•`‰æ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaSound::Play(main_.death_spx_);
		NyaInterface::GetHandleSkill()->AddExp(9000);
	}

}
