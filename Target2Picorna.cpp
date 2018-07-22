#include "HNLIB.h"
#include "Target2Picorna.h"
#include "TeemoLock.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"

using namespace HNLIB;

Target2PicornaCubeDevice::Target2PicornaCubeDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->move_speed_ = 3;
	gadget_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetAttackOrange3(dpx_, gadget_gpx_, epx_, effect_gpx_);
}

Target2PicornaCubeDevice::~Target2PicornaCubeDevice()
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

Target2PicornaCube::Target2PicornaCube()
{
	lock_ = new TeemoLock(eLOCK::ECTROMELIA);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetCube(gpx_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

Target2PicornaCube::~Target2PicornaCube()
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

Target2PicornaDevice::Target2PicornaDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->move_speed_ = 6;
	gadget_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetAttackBlue2(dpx_, gadget_gpx_, epx_, effect_gpx_);
}

Target2PicornaDevice::~Target2PicornaDevice()
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

Target2PicornaMain::Target2PicornaMain() : health_max_(25000)
{
	lock_ = new TeemoLock(eLOCK::ECTROMELIA);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath2(death_epx_, death_gpx_);

	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death2.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 50);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(2, 1, "img/target/main_picorna.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 10;
	phandle_->health_ = health_max_;
}

Target2PicornaMain::~Target2PicornaMain()
{
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

Target2Picorna::Target2Picorna(int x, int y)
{
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
	cube_collection_[0].phandle_->grid_x_ = x - 240;
	cube_collection_[0].phandle_->grid_y_ = y - 60;
	cube_collection_[1].phandle_->grid_x_ = x - 80;
	cube_collection_[1].phandle_->grid_y_ = y - 60;
	cube_collection_[2].phandle_->grid_x_ = x + 80;
	cube_collection_[2].phandle_->grid_y_ = y - 60;
	cube_collection_[3].phandle_->grid_x_ = x + 240;
	cube_collection_[3].phandle_->grid_y_ = y - 60;
}


Target2Picorna::~Target2Picorna()
{

}

void Target2Picorna::Act(void)
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
}

void Target2Picorna::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		count_frame_ = 0;
		mode_ = 2;
		NyaInterface::GetHandleHealth()->valid_ = true;
		break;
	case 2:
		Draw2();
		if (main_.phandle_->health_ <= 0)
		{
			mode_ = 3;
			NyaInterface::GetHandleHealth()->valid_ = false;
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
			NyaSound::Play(main_.death_spx_);
			NyaInterface::GetHandleSkill()->AddExp(30000);

		}
		if (FPS_MAX * 3 <= count_frame_ && !NyaPosition::InScreen(main_.phandle_))
			mode_ = 3;
		break;
	};

	count_frame_++;
}

void Target2Picorna::Act1(void)
{
	NyaPosition::MoveGridMode(main_.phandle_, main_.phandle_->grid_x_, 200, FPS_MAX * 2);
}

void Target2Picorna::Act2(void)
{
	// cube ”z’u
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 240;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ - 80;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;
	cube_collection_[2].phandle_->grid_x_ = main_.phandle_->grid_x_ + 80;
	cube_collection_[2].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;
	cube_collection_[3].phandle_->grid_x_ = main_.phandle_->grid_x_ + 240;
	cube_collection_[3].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;

	// Õ“Ë”»’è@Õ“Ëƒ_ƒ[ƒW‚¾‚¯ŒoŒ±’l‚ð’Ç‰Á
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

	if (count_frame_ % 40 == 0)
	{
		main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device_.dpx_->delay_time_frame_ = 0;
		main_.device_.dpx_->move_angle_deg_ += (90 + 10);
		for (int way = 0; way < 8; way++)
		{
			NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			main_.device_.dpx_->delay_time_frame_ += 4;
		}
		main_.device_.dpx_->delay_time_frame_ = 0;
		main_.device_.dpx_->move_angle_deg_ += 90;
		for (int way = 0; way < 8; way++)
		{
			NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			main_.device_.dpx_->delay_time_frame_ += 4;
		}
		main_.device_.dpx_->delay_time_frame_ = 0;
		main_.device_.dpx_->move_angle_deg_ += 90;
		for (int way = 0; way < 8; way++)
		{
			NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			main_.device_.dpx_->delay_time_frame_ += 4;
		}
		main_.device_.dpx_->delay_time_frame_ = 0;
		main_.device_.dpx_->move_angle_deg_ += 90;
		for (int way = 0; way < 8; way++)
		{
			NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			main_.device_.dpx_->delay_time_frame_ += 4;
		}
	}

	if (count_frame_ % 25 == 0)
	{
		for (auto& e : cube_collection_)
		{	// cube UŒ‚ˆ—
			DevicePropertyX1* cube_dpx = e.device_.dpx_;
			GraphicPropertyX4* cube_gadget_gpx = e.device_.gadget_gpx_;
			EffectPropertyX1* cube_epx = e.device_.epx_;
			GraphicPropertyX4* cube_effect_gpx = e.device_.effect_gpx_;
			cube_dpx->create_x_ = e.phandle_->grid_x_;
			cube_dpx->create_y_ = e.phandle_->grid_y_;
			cube_dpx->delay_time_frame_ = 0;
			for (int way = 0; way < 4; way++)
			{
				cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
				cube_dpx->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
				cube_dpx->delay_time_frame_ += 5;
			}
		}
	}

	if (count_frame_ == FPS_MAX * 22)
		NyaPosition::MoveSpeedMode(main_.phandle_, -90, 3, FPS_MAX * 10);
}

void Target2Picorna::Draw1(void)
{
	// ‰½‚à‚µ‚È‚¢
}

void Target2Picorna::Draw2(void)
{
	// main •`‰æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ƒƒbƒN•`‰æ
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube_collection_)
	{	// cube•`‰æ
		if (count_frame_ % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube ƒƒbƒN•`‰æ
		e.lock_->Run(e.phandle_);
	}
	
	// ƒwƒ‹ƒX•\Ž¦
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	if (main_.phandle_->health_ <= 0)
	{	// ”š”­•`‰æ
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
		for (auto& e : cube_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}

}
