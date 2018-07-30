#include "HNLIB.h"
#include "TeemoEnum.h"
#include "Target3Kluyvera.h"

using namespace HNLIB;

Target3KluyveraDevice::Target3KluyveraDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_ORANGE1;
	dpx_->move_speed_ = 5;
	device_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/attack_orange1.png", &device_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/point.png", &effect_gpx_->file_);

}

Target3KluyveraDevice::~Target3KluyveraDevice()
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

Target3KluyveraMain::Target3KluyveraMain()
{
	death_epx_ = new EffectPropertyX1;
	death_epx_->interval_time_frame_ = 3;

	death_gpx_ = new GraphicPropertyX4;
	death_gpx_->extend_rate_ = 0.5;
	NyaGraphic::Load(4, 2, "img/target/death1.png", &death_gpx_->file_);

	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 50);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load(3, 1, "img/target/target_pantoea.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;

	lock_.LoadGraphic("img/target/lock_pantoea.png");
}

Target3KluyveraMain::~Target3KluyveraMain()
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

Target3Kluyvera::Target3Kluyvera(int x, int y, bool turn)
{
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	main_.phandle_->health_ = 30;
	mode_ = 1;
	turn_ = turn;
}

Target3Kluyvera::~Target3Kluyvera()
{

}

void Target3Kluyvera::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		break;
	};

	// mapにシンクロさせる
	main_.phandle_->grid_y_ += 0.2;

	count_frame_++;
}

void Target3Kluyvera::Draw(void)
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

void Target3Kluyvera::Act1(void)
{
	PositionHandle phandle_user;

	if (count_frame_ == 0)
	{
		main_.phandle_->grid_x_ += NyaInput::GetRand(-10, 10);
		main_.phandle_->grid_y_ += NyaInput::GetRand(-30, 30);
		count_frame_ = NyaInput::GetRand(1, FPS_MAX);
	}

	// 移動処理
	if (!turn_)
		main_.phandle_->grid_x_ += 3;
	else
		main_.phandle_->grid_x_ -= 3;

	// 攻撃処理
	if (count_frame_ % FPS_MAX == 0)
	{
		if (NyaPosition::InScreen(main_.phandle_))
		{
			device_.dpx_->create_x_ = main_.phandle_->grid_x_;
			device_.dpx_->create_y_ = main_.phandle_->grid_y_;
			NyaPosition::FindHandle("user", &phandle_user);
			device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
			for (int delay = 0; delay < 10; delay+= 2)
			{
				device_.dpx_->delay_time_frame_ = delay;
				NyaDevice::Attack1414(device_.dpx_, device_.device_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
	}


	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
}

void Target3Kluyvera::Draw1(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	main_.gpx_->flag_turn_ = turn_;
	if (count_frame_ % 30 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % 3;	
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	main_.lock_.Run(main_.phandle_);

	if (main_.phandle_->health_ < 0)
	{	// 爆発描画
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaSound::Play(main_.death_spx_);
		NyaInterface::GetHandleSkill()->AddExp(9000);
	}

}
