#include "HNLIB.h"
#include "Target3Vibrio.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"

using namespace HNLIB;

Target3VibrioDevice::Target3VibrioDevice()
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

Target3VibrioDevice::~Target3VibrioDevice()
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

Target3VibrioDeathDevice::Target3VibrioDeathDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->move_speed_ = 4;
	gadget_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetAttackOrange5(dpx_, gadget_gpx_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

Target3VibrioDeathDevice::~Target3VibrioDeathDevice()
{
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

Target3VibrioMain::Target3VibrioMain()
{
	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	death_spx_ = new SoundPropertyX;
	NyaSound::LoadFile("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 50);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::LoadGraphicFile(2, 1, "img/target/main_vibrio.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->health_ = 500;

	lock_.LoadGraphic("img/target/lock_vibrio.png");
}

Target3VibrioMain::~Target3VibrioMain()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaSound::DeleteSoundFile(&death_spx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);

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

Target3Vibrio::Target3Vibrio(int x, int y, int max_x, int max_y)
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
	move_max_x_ = max_x;
	move_max_y_ = max_y;
}

Target3Vibrio::~Target3Vibrio()
{

}

void Target3Vibrio::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		break;
	};

	count_frame_++;
}

void Target3Vibrio::Draw(void)
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

void Target3Vibrio::Act1(void)
{
	// 初期位置へ移動
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, move_max_x_, move_max_y_, FPS_MAX * 2);

	if (count_frame_ == FPS_MAX * 2)
	{	// 攻撃処理
		device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 360 / 8; way++)
		{
			device_.dpx_->move_angle_deg_ += 8;
			NyaDevice::Attack1414(device_.dpx_, device_.gadget_gpx_, device_.epx_, device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;

	if (main_.phandle_->health_ < 0)
	{	// 打ち返し攻撃
		double dpx_angle;
		PositionHandle phandle_user;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device2_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device2_.dpx_->create_y_ = main_.phandle_->grid_y_;
		dpx_angle = NyaPosition::Angle(main_.phandle_, &phandle_user) + NyaInput::GetRand(-1.0, 1.0);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle - 5;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.gadget_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.gadget_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->move_angle_deg_ = dpx_angle + 5;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.gadget_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}

	// Uターン移動
	if (count_frame_ == FPS_MAX * 10)
		NyaPosition::MoveGridMode(main_.phandle_, move_max_x_, -100, FPS_MAX * 2);
}

void Target3Vibrio::Draw1(void)
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


