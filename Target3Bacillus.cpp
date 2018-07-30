#include "HNLIB.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "Target3Bacillus.h"

using namespace HNLIB;

Target3BacillusDevice::Target3BacillusDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 4;
	device_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/attack_red1.png", &device_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/point.png", &effect_gpx_->file_);

}

Target3BacillusDevice::~Target3BacillusDevice()
{
	NyaGraphic::Delete(&device_gpx_->file_);
	NyaGraphic::Delete(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

Target3BacillusDeathDevice::Target3BacillusDeathDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 4;
	TeemoFactory::TargetAttackWhite5(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target3BacillusDeathDevice::~Target3BacillusDeathDevice()
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

Target3BacillusMain::Target3BacillusMain()
{
	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 50);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(4, 1, "img/target/target_bacillus.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 6;
	phandle_->health_ = 100;

	lock_.LoadGraphic("img/target/lock_bacillus.png");
}

Target3BacillusMain::~Target3BacillusMain()
{
	NyaGraphic::Delete(&death_gpx_->file_);
	NyaSound::Delete(&death_spx_->file_);
	NyaGraphic::Delete(&gpx_->file_);

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
	int rand_x = NyaInput::GetRand(-50, 50);
	int rand_y = NyaInput::GetRand(-50, 50);
	count_frame_ = 0;
	main_.phandle_->grid_x_ = x + rand_x;
	main_.phandle_->grid_y_ = y + rand_y;
	mode_ = 1;
	move_max_x_ = move_max_x + rand_x;
	move_max_y_ = move_max_y + rand_y;
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
	
	// ‰ŠúˆÊ’u‚ÖˆÚ“®
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, move_max_x_, move_max_y_, FPS_MAX * 2);

	// Õ“Ë”»’è@Õ“Ëƒ_ƒ[ƒW‚¾‚¯ŒoŒ±’l‚ð’Ç‰Á
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;

	if (count_frame_ == FPS_MAX * 2)
	{	// UŒ‚ˆ—
		device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaPosition::FindHandle("user", &phandle_user);
		double attack_angle = NyaPosition::Angle(main_.phandle_, &phandle_user) + NyaInput::GetRand(-2, 2);

		device_.dpx_->delay_time_frame_ = 0;
		device_.dpx_->move_angle_deg_ =  attack_angle - 5;
		NyaDevice::Attack1414(device_.dpx_, device_.device_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		device_.dpx_->move_angle_deg_ = attack_angle;
		NyaDevice::Attack1414(device_.dpx_, device_.device_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		device_.dpx_->move_angle_deg_ = attack_angle + 5;
		NyaDevice::Attack1414(device_.dpx_, device_.device_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		device_.dpx_->delay_time_frame_ = 10;
		device_.dpx_->move_angle_deg_ =  attack_angle - 5;
		NyaDevice::Attack1414(device_.dpx_, device_.device_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		device_.dpx_->move_angle_deg_ = attack_angle;
		NyaDevice::Attack1414(device_.dpx_, device_.device_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		device_.dpx_->move_angle_deg_ = attack_angle + 5;
		NyaDevice::Attack1414(device_.dpx_, device_.device_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}
	
	if (count_frame_ == FPS_MAX * 3)
	{	// user‘_‚¢‚ÌˆÚ“®ˆ—
		NyaPosition::FindHandle("user", &phandle_user);
		move_angle_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
		NyaPosition::MoveSpeedMode(main_.phandle_, move_angle_, 5, FPS_MAX * 10);
	}

	if (main_.phandle_->health_ < 0)
	{	// ‘Å‚¿•Ô‚µUŒ‚
		PositionHandle phandle_user;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device2_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device2_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device2_.dpx_->delay_time_frame_ = 0;
		for (int i = 0; i < 5; i++)
		{
			main_.device2_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) + NyaInput::GetRand(-5.0, 5.0);
			NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.device_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			main_.device2_.dpx_->delay_time_frame_ += 4;
		}
	}
}

void Target3Bacillus::Draw1(void)
{
	// main •`‰æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (count_frame_ % 30 == 0)
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
		NyaInterface::GetHandleSkill()->AddExp(9000);
	}

}
