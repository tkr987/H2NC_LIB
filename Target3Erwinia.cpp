#include "HNLIB.h"
#include "Target3Erwinia.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"

using namespace HNLIB;


Target3ErwiniaDevice::Target3ErwiniaDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_ORANGE2;
	dpx_->move_speed_ = 9;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/attack_orange2.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/point.png", &effect_gpx_->file_);
}

Target3ErwiniaDevice::~Target3ErwiniaDevice()
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

Target3ErwiniaDeathDevice::Target3ErwiniaDeathDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->move_speed_ = 4;
	gadget_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetAttackWhite5(dpx_, gadget_gpx_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/point.png", &effect_gpx_->file_);
}

Target3ErwiniaDeathDevice::~Target3ErwiniaDeathDevice()
{
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

Target3ErwiniaMain::Target3ErwiniaMain()
{
	health_max_ = 500;
	lock_.LoadGraphic("img/target/lock_erwinia.png");

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 50);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load(2, 1, "img/target/target_erwinia.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 10;
	phandle_->health_ = health_max_;
}

Target3ErwiniaMain::~Target3ErwiniaMain()
{
	NyaGraphic::Delete(&death_gpx_->file_);
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

Target3Erwinia::Target3Erwinia()
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = NyaInput::GetRand(100, SCREEN_MAX_X - 50);
	main_.phandle_->grid_y_ = NyaInput::GetRand(-200, -100);
	mode_ = 1;
}

Target3Erwinia::Target3Erwinia(int x, int y)
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
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
		{
			count_frame_ = 0;
			mode_ = 2;
		}
		break;
	case 2:
		Act2();
		break;
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
		break;
	case 2:
		Draw2();
		if (main_.phandle_->health_ < 0)
			mode_ = 3;
		break;
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
			NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			main_.device_.dpx_->move_angle_deg_ += 3;
		}
	}

	if (main_.phandle_->health_ < 0)
	{	// 打ち返し攻撃
		double dpx_angle;
		PositionHandle phandle_user;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device2_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device2_.dpx_->create_y_ = main_.phandle_->grid_y_;
		dpx_angle = NyaPosition::Angle(main_.phandle_, &phandle_user) + NyaInput::GetRand(-1.0, 1.0);
		main_.device2_.dpx_->delay_time_frame_ = 0;
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle - 5;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.gadget_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.gadget_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle + 5;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.gadget_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->delay_time_frame_ = 10;
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle - 5;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.gadget_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.gadget_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle + 5;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.gadget_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}

}

void Target3Erwinia::Draw1(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (count_frame_ % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	main_.lock_.Run(main_.phandle_);
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
	main_.lock_.Run(main_.phandle_);

	if (main_.phandle_->health_ < 0)
	{	// 爆発描画
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaSound::Play(main_.death_spx_);
		NyaInterface::GetHandleSkill()->AddExp(10000);
	}

}
