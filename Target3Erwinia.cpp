#include "HNLIB.h"
#include "Target3Erwinia.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "TeemoLock.h"

using namespace HNLIB;


Target3ErwiniaDevice::Target3ErwiniaDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 8;
	TeemoFactory::TargetAttackRed2(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target3ErwiniaDevice::~Target3ErwiniaDevice()
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

Target3ErwiniaDeathDevice::Target3ErwiniaDeathDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 4;
	TeemoFactory::TargetAttackWhite6(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target3ErwiniaDeathDevice::~Target3ErwiniaDeathDevice()
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

Target3ErwiniaMain::Target3ErwiniaMain(): exp_(2000), health_max_(500)
{
	lock_ = new TeemoLock(eLOCK::ERWINIA);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 50);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(2, 1, "img/target/main_erwinia.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
	phandle_->health_ = health_max_;
}

Target3ErwiniaMain::~Target3ErwiniaMain()
{
	NyaSound::Delete(&death_spx_->file_);
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

Target3Erwinia::Target3Erwinia()
{
	count_frame_ = 0;
	mode_ = 1;
	main_.phandle_->grid_x_ = NyaInput::GetRand(100, SCREEN_MAX_X - 50);
	main_.phandle_->grid_y_ = NyaInput::GetRand(-200, -100);
}

Target3Erwinia::Target3Erwinia(int x, int y)
{
	count_frame_ = 0;
	mode_ = 1;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
}


Target3Erwinia::~Target3Erwinia()
{

}

void Target3Erwinia::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		if (NyaPosition::InScreen(main_.phandle_))
			count_frame_ = 0;
		break;
	case 2:
		Act2();
		if (main_.phandle_->health_ <= 0)
		{
			count_frame_ = 0;
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

void Target3Erwinia::Draw(void)
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
			mode_ = 2;
		break;
	case 3:
		return;
	};
}

void Target3Erwinia::Act1(void)
{
	// 何もしない
}

void Target3Erwinia::Act2(void)
{

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;

	if (count_frame_ % (FPS_MAX * 4) == FPS_MAX * 2)
	{	// 左右への移動処理
		int move_x;
		if (NyaInput::GetRand(0, 1) == 0)
			move_x = -100;
		else
			move_x = 100;
		if (50 <= main_.phandle_->grid_x_ + move_x && main_.phandle_->grid_x_ + move_x < SCREEN_MAX_X - 50)
			NyaPosition::MoveGridMode(main_.phandle_, main_.phandle_->grid_x_ + move_x, main_.phandle_->grid_y_, FPS_MAX);
	}

	if (count_frame_ % (FPS_MAX * 4) == FPS_MAX * 3)
	{	// 攻撃処理
		main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device_.dpx_->move_angle_deg_ = 78;
		for (int way = 0; way < 9; way++)
		{
			NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			main_.device_.dpx_->move_angle_deg_ += 3;
		}
	}

	if (main_.phandle_->health_ <= 0)
	{	// 打ち返し攻撃
		double dpx_angle;
		PositionHandle phandle_user;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device2_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device2_.dpx_->create_y_ = main_.phandle_->grid_y_;
		dpx_angle = NyaPosition::Angle(main_.phandle_, &phandle_user) + NyaInput::GetRand(-1.0, 1.0);
		main_.device2_.dpx_->delay_time_frame_ = 0;
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle - 5;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.device_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.device_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle + 5;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.device_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->delay_time_frame_ = 10;
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle - 5;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.device_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.device_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle + 5;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.device_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}

}

void Target3Erwinia::Draw1(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);
}

void Target3Erwinia::Draw2(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);

	if (main_.phandle_->health_ <= 0)
	{	// 爆発描画
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
	}

}
