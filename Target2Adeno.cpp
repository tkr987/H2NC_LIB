#include "HNLIB.h"
#include "Target2Adeno.h"
#include "TargetLock.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"

using namespace HNLIB;

Target2AdenoCubeDevice::Target2AdenoCubeDevice()
{
	dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 6;
	dpx_->move_angle_deg_ = 90;
	TeemoFactory::TargetAttackBlue7(dpx_, gadget_gpx_, epx_, effect_gpx_);
}

Target2AdenoCubeDevice::~Target2AdenoCubeDevice()
{
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

Target2AdenoCube::Target2AdenoCube()
{
	lock_ = new TargetLock;
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
	gadget_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 4;
	TeemoFactory::TargetAttackOrange3(dpx_, gadget_gpx_, epx_, effect_gpx_);
}

Target2AdenoDevice::~Target2AdenoDevice()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);

	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

Target2AdenoMain::Target2AdenoMain()
{
	health_max_ = 30000;

	lock_ = new TargetLock;
	lock_->LoadGraphic("img/target/lock_adeno.png");

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath2(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::LoadGraphicFile(4, 1, "img/target/target_adeno.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 10;
	phandle_->health_ = health_max_;
}

Target2AdenoMain::~Target2AdenoMain()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);

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

Target2Adeno::Target2Adeno(int x, int y, int move_end_x, int move_end_y)
{
	cube_collection_[0].phandle_->grid_x_ = x - 100;
	cube_collection_[0].phandle_->grid_y_ = y - 50;
	cube_collection_[1].phandle_->grid_x_ = x + 100;
	cube_collection_[1].phandle_->grid_y_ = y - 50;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	main_.move_end_x_ = move_end_x;
	main_.move_end_y_ = move_end_y;
	mode_ = 1;
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
		break;
	case 2:
		Act2();
		break;
	};

	main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
}

void Target2Adeno::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if (NyaPosition::InScreen(main_.phandle_))
		{
			count_frame_ = 0;
			mode_ = 2;
		}
		break;
	case 2:
		Draw2();
		if (main_.phandle_->health_ <= 0)
		{
			mode_ = 3;
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
			NyaInterface::GetHandleSkill()->AddExp(50000);
			NyaSound::Play(main_.death_spx_);
		}
		break;
	};

	count_frame_++;
}

void Target2Adeno::Act1(void)
{
	// cube îzíu
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;

	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, main_.move_end_x_, main_.move_end_y_, FPS_MAX * 2);

}

void Target2Adeno::Act2(void)
{
	// cube îzíu
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;

	// è’ìÀîªíËÅ@è’ìÀÉ_ÉÅÅ[ÉWÇæÇØåoå±ílÇí«â¡
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
	{	// main çUåÇèàóù
		PositionHandle phandle_user;
		main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device_.dpx_->delay_time_frame_ = 0;
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) - 8;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) + 8;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->delay_time_frame_ = 4;
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) - 8;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user) + 8;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}

	if (count_frame_ % FPS_MAX == 0)
	{	// cube çUåÇèàóù
		DevicePropertyX1* dpx;
		GraphicPropertyX4* gadget_gpx;
		EffectPropertyX1* epx;
		GraphicPropertyX4* effect_gpx;
		for (int delay = 0; delay < 10; delay++)
		{
			dpx = cube_collection_[0].device_.dpx_;
			gadget_gpx = cube_collection_[0].device_.gadget_gpx_;
			epx = cube_collection_[0].device_.epx_;
			effect_gpx = cube_collection_[0].device_.effect_gpx_;
			dpx->create_x_ = cube_collection_[0].phandle_->grid_x_;
			dpx->create_y_ = cube_collection_[0].phandle_->grid_y_;
			dpx->delay_time_frame_ = 4 * delay;
			NyaDevice::Attack1414(dpx, gadget_gpx, epx, effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			dpx = cube_collection_[1].device_.dpx_;
			gadget_gpx = cube_collection_[1].device_.gadget_gpx_;
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
	// main ï`âÊ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ÉçÉbÉNï`âÊ
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube_collection_)
	{	// cubeï`âÊ
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube ÉçÉbÉNï`âÊ
		e.lock_->Run(e.phandle_);
	}

	if (main_.phandle_->health_ <= 0)
	{
		// main îöî≠ï`âÊ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);

		for (auto& e : cube_collection_)
		{	// cube îöî≠ï`âÊ
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}

		NyaSound::Play(main_.death_spx_);
		NyaInterface::GetHandleSkill()->AddExp(10000);
	}
}

void Target2Adeno::Draw2(void)
{
	// main ï`âÊ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ÉçÉbÉNï`âÊ
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube_collection_)
	{	// cubeï`âÊ
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube ÉçÉbÉNï`âÊ
		e.lock_->Run(e.phandle_);
	}


	if (main_.phandle_->health_ <= 0)
	{
		// main îöî≠ï`âÊ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);

		for (auto& e : cube_collection_)
		{	// cube îöî≠ï`âÊ
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}
