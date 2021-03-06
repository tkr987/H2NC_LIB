#include "HNLIB.h"
#include "Target2Adeno.h"
#include "TeemoLock.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"

using namespace HNLIB;

Target2AdenoCubeDevice::Target2AdenoCubeDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 6;
	dpx_->move_angle_deg_ = 90;
	TeemoFactory::TargetAttackBlue7(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target2AdenoCubeDevice::~Target2AdenoCubeDevice()
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

Target2AdenoCube::Target2AdenoCube()
{
	lock_ = new TeemoLock;
	lock_->LoadGraphic("img/target/lock_cube.png");

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetCubeBlue(gpx_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

Target2AdenoCube::~Target2AdenoCube()
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

Target2AdenoDevice::Target2AdenoDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 4;
	TeemoFactory::TargetAttackOrange3(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target2AdenoDevice::~Target2AdenoDevice()
{
	NyaGraphic::Delete(&device_gpx_->file_);

	delete dpx_;
	dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

Target2AdenoMain::Target2AdenoMain() : exp_(20000), health_max_(6000)
{
	lock_ = new TeemoLock(eLOCK::ADENO);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath2(death_epx_, death_gpx_);
	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death2.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, TARGET_DEATH2_SOUND_VOLUME);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(4, 1, "img/target/main_adeno.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
	phandle_->health_ = health_max_;
}

Target2AdenoMain::~Target2AdenoMain()
{
	NyaGraphic::Delete(&gpx_->file_);
	NyaSound::Delete(&death_spx_->file_);

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

Target2Adeno::Target2Adeno(int x, int y)
{
	count_frame_ = 0;
	mode_ = 1;
	cube_collection_[0].phandle_->grid_x_ = x - 100;
	cube_collection_[0].phandle_->grid_y_ = y - 50;
	cube_collection_[1].phandle_->grid_x_ = x + 100;
	cube_collection_[1].phandle_->grid_y_ = y - 50;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
}


Target2Adeno::~Target2Adeno()
{

}

void Target2Adeno::Act(void)
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
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaInterface::GetHandleSkill()->AddExp(main_.exp_);
			NyaSound::Play(main_.death_spx_);
		}
		break;
	case 3:
		return;
	};

	main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
	count_frame_++;
}

void Target2Adeno::Draw(void)
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
		break;
	case 3:
		return;
	};
}

void Target2Adeno::Act1(void)
{
	// cube zu
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;
}

void Target2Adeno::Act2(void)
{
	// cube zu
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;

	// ÕË»è@ÕË_[W¾¯o±lðÇÁ
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

	if (count_frame_ % 30 == 0)
	{	// main U
		PositionHandle phandle_user;
		main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device_.dpx_->delay_time_frame_ = 0;
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) - 8;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) + 8;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->delay_time_frame_ = 4;
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) - 8;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) + 8;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}

	if (count_frame_ % FPS_MAX == 0)
	{	// cube U
		DevicePropertyX1* dpx;
		GraphicPropertyX4* gadget_gpx;
		EffectPropertyX1* epx;
		GraphicPropertyX4* effect_gpx;
		for (int delay = 0; delay < 10; delay++)
		{
			dpx = cube_collection_[0].device_.dpx_;
			gadget_gpx = cube_collection_[0].device_.device_gpx_;
			epx = cube_collection_[0].device_.epx_;
			effect_gpx = cube_collection_[0].device_.effect_gpx_;
			dpx->create_x_ = cube_collection_[0].phandle_->grid_x_;
			dpx->create_y_ = cube_collection_[0].phandle_->grid_y_;
			dpx->delay_time_frame_ = 4 * delay;
			NyaDevice::Attack1414(dpx, gadget_gpx, epx, effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			dpx = cube_collection_[1].device_.dpx_;
			gadget_gpx = cube_collection_[1].device_.device_gpx_;
			epx = cube_collection_[1].device_.epx_;
			effect_gpx = cube_collection_[1].device_.effect_gpx_;
			dpx->create_x_ = cube_collection_[1].phandle_->grid_x_;
			dpx->create_y_ = cube_collection_[1].phandle_->grid_y_;
			dpx->delay_time_frame_ = 4 * delay;
			NyaDevice::Attack1414(dpx, gadget_gpx, epx, effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);

		}
	}
}

void Target2Adeno::Draw1(void)
{
	// main `æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main bN`æ
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube_collection_)
	{	// cube`æ
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube bN`æ
		e.lock_->Run(e.phandle_);
	}

	if (main_.phandle_->health_ <= 0)
	{
		// main ­`æ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaGraphic::Swing();

		for (auto& e : cube_collection_)
		{	// cube ­`æ
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void Target2Adeno::Draw2(void)
{
	// main `æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main bN`æ
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube_collection_)
	{	// cube`æ
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube bN`æ
		e.lock_->Run(e.phandle_);
	}


	if (main_.phandle_->health_ <= 0)
	{
		// main ­`æ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);

		for (auto& e : cube_collection_)
		{	// cube ­`æ
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}
