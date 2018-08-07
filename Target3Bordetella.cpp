#include "HNLIB.h"
#include "Target3Bordetella.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "TeemoLock.h"

using namespace HNLIB;

Target3BordetellaCubeDevice::Target3BordetellaCubeDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 6;
	TeemoFactory::TargetAttackOrange2(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target3BordetellaCubeDevice::~Target3BordetellaCubeDevice()
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

Target3BordetellaCube::Target3BordetellaCube()
{
	lock_ = new TeemoLock(eLOCK::CUBE);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetCube(gpx_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

Target3BordetellaCube::~Target3BordetellaCube()
{
	delete lock_;
	lock_ = nullptr;
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

Target3BordetellaDevice::Target3BordetellaDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 4;
	TeemoFactory::TargetAttackBlue3(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target3BordetellaDevice::~Target3BordetellaDevice()
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

Target3BordetellaMain::Target3BordetellaMain(): exp_(20000), health_max_(15000)
{
	lock_ = new TeemoLock(eLOCK::BORDETELLA);
	
	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath2(death_epx_, death_gpx_);

	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death2.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, TARGET_DEATH2_SOUND_VOLUME);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(4, 1, "img/target/main_bordetella.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
	phandle_->health_ = health_max_;
}

Target3BordetellaMain::~Target3BordetellaMain()
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

Target3Bordetella::Target3Bordetella(int x, int y)
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
	cube_collection_[0].phandle_->grid_x_ = x - 100;
	cube_collection_[0].phandle_->grid_y_ = y - 60;
	cube_collection_[1].phandle_->grid_x_ = x + 100;
	cube_collection_[1].phandle_->grid_y_ = y - 60;
}


Target3Bordetella::~Target3Bordetella()
{

}

void Target3Bordetella::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
		if (NyaPosition::InScreen(main_.phandle_))
			count_frame_ = 0;
		break;
	case 2:
		Act2();
		main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
		if (main_.phandle_->health_ <= 0)
		{
			NyaInterface::GetHandleHealth()->valid_ = false;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaSound::Play(main_.death_spx_);
			NyaInterface::GetHandleSkill()->AddExp(main_.exp_);
		}
		break;
	case 3:
		return;
	};

	count_frame_++;
}

void Target3Bordetella::Draw(void)
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
		if (FPS_MAX * 30 < count_frame_)
			mode_ = 3;
		break;
	case 3:
		return;
	};
}

void Target3Bordetella::Act1(void)
{
	// cube 配置
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;
}

void Target3Bordetella::Act2(void)
{
	if (count_frame_ == 1)
		NyaInterface::GetHandleHealth()->valid_ = true;

	// cube 配置
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (auto& e : cube_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 2)
		return;

	if (count_frame_ < FPS_MAX * 6 || FPS_MAX * 9 < count_frame_)
	{
		if (count_frame_ % 120 == 0 || count_frame_ % 120 == 20 || count_frame_ % 120 == 40)
		{
			main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
			main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
			main_.device_.dpx_->move_angle_deg_ = 0;
			for (int way = 0; way < 360 / 6; way++)
			{
				main_.device_.dpx_->move_angle_deg_ += 6;
				NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
		if (count_frame_ % 120 == 60 || count_frame_ % 120 == 80 || count_frame_ % 120 == 100)
		{
			main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
			main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
			main_.device_.dpx_->move_angle_deg_ = 3;
			for (int way = 0; way < 360 / 6; way++)
			{
				main_.device_.dpx_->move_angle_deg_ += 6;
				NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
	}

	if (FPS_MAX * 7 < count_frame_ &&  count_frame_ < FPS_MAX * 9 && count_frame_ % 40 == 0)
	{
		PositionHandle phandle_user;
		NyaPosition::FindHandle("user", &phandle_user);
		NyaPosition::Angle(cube_collection_[0].phandle_, &phandle_user);
		DevicePropertyX1* cube_dpx = cube_collection_[0].device_.dpx_;
		GraphicPropertyX4* cube_gadget_gpx = cube_collection_[0].device_.device_gpx_;
		EffectPropertyX1* cube_epx = cube_collection_[0].device_.epx_;
		GraphicPropertyX4* cube_effect_gpx = cube_collection_[0].device_.effect_gpx_;
		cube_dpx->create_x_ = cube_collection_[0].phandle_->grid_x_;
		cube_dpx->create_y_ = cube_collection_[0].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaPosition::Angle(cube_collection_[0].phandle_, &phandle_user);
		for (int delay = 0; delay < 21; delay += 3)
		{
			cube_dpx->delay_time_frame_ = delay;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}
	if (FPS_MAX * 7 < count_frame_ &&  count_frame_ < FPS_MAX * 9 && count_frame_ % 40 == 20)
	{
		PositionHandle phandle_user;
		NyaPosition::FindHandle("user", &phandle_user);
		NyaPosition::Angle(cube_collection_[1].phandle_, &phandle_user);
		DevicePropertyX1* cube_dpx = cube_collection_[1].device_.dpx_;
		GraphicPropertyX4* cube_gadget_gpx = cube_collection_[1].device_.device_gpx_;
		EffectPropertyX1* cube_epx = cube_collection_[1].device_.epx_;
		GraphicPropertyX4* cube_effect_gpx = cube_collection_[1].device_.effect_gpx_;
		cube_dpx->create_x_ = cube_collection_[1].phandle_->grid_x_;
		cube_dpx->create_y_ = cube_collection_[1].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ = NyaPosition::Angle(cube_collection_[1].phandle_, &phandle_user);
		for (int delay = 0; delay < 21; delay += 3)
		{
			cube_dpx->delay_time_frame_ = delay;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}

	if (count_frame_ == FPS_MAX * 18)
		NyaPosition::MoveSpeedMode(main_.phandle_, -90, 3, FPS_MAX * 10);
}

void Target3Bordetella::Draw1(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (count_frame_ % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % 4;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);
}

void Target3Bordetella::Draw2(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube_collection_)
	{	// cube 描画
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube ロック描画
		e.lock_->Run(e.phandle_);
	}
	
	// ヘルス表示更新
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;


	if (main_.phandle_->health_ <= 0)
	{	// 爆発描画
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaGraphic::Swing();
	}

}
