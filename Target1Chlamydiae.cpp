#include <tuple>
#include "HNLIB.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "Target1Chlamydiae.h"
#include "TeemoLock.h"

using namespace std;
using namespace HNLIB;

Target1ChlamydiaeCubeDevice::Target1ChlamydiaeCubeDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 7;
	TeemoFactory::TargetAttackOrange1(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target1ChlamydiaeCubeDevice::~Target1ChlamydiaeCubeDevice()
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

Target1ChlamydiaeCube::Target1ChlamydiaeCube()
{
	lock_ = new TeemoLock(eLOCK::CUBE);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetCube(gpx_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

Target1ChlamydiaeCube::~Target1ChlamydiaeCube()
{
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

Target1ChlamydiaeMainDevice::Target1ChlamydiaeMainDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 5;
	TeemoFactory::TargetAttackBlue2(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target1ChlamydiaeMainDevice::~Target1ChlamydiaeMainDevice()
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

Target1ChlamydiaeMain::Target1ChlamydiaeMain() : exp_(20000), health_max_(1900)
{
	lock_ = new TeemoLock(eLOCK::CHLAMYDIAE);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath2(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(2, 1, "img/target/main_chlamydiae.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -200;
	phandle_->health_ = health_max_;
}

Target1ChlamydiaeMain::~Target1ChlamydiaeMain()
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

Target1Chlamydiae::Target1Chlamydiae(int x, int y)
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
}

Target1Chlamydiae::~Target1Chlamydiae()
{

}

//********************************
// Target1Chlamydiae ƒƒ“ƒoŠÖ”
//********************************

void Target1Chlamydiae::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		if (main_.phandle_->health_ <= 0)
		{
			NyaInterface::GetHandleHealth()->valid_ = false;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaInterface::GetHandleSkill()->AddExp(main_.exp_);
			NyaSound::Play(main_.death_spx_);
		}
		break;
	case 2:
		return;
	}

	count_frame_++;
}

void Target1Chlamydiae::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if (main_.phandle_->health_ <= 0)
			mode_ = 2;
		if (FPS_MAX * 30 < count_frame_)
			mode_ = 2;
		break;
	case 2:
		return;
	}
}

void Target1Chlamydiae::Act1(void)
{
	if (count_frame_ == 1)
	{
		main_.device1_.dpx_->move_angle_deg_ = -90;
		main_.device2_.dpx_->move_angle_deg_ = -90;
		NyaInterface::GetHandleHealth()->valid_ = true;
		NyaPosition::MoveGridMode(main_.phandle_, main_.phandle_->grid_x_, 150, FPS_MAX * 2);
	}

	// cube ”z’u
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 200;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;
	cube_collection_[2].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube_collection_[2].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;
	cube_collection_[3].phandle_->grid_x_ = main_.phandle_->grid_x_ + 200;
	cube_collection_[3].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;

	if (!NyaPosition::InScreen(main_.phandle_))
		return;

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

	if (count_frame_ < FPS_MAX * 3)
		return;

	if (count_frame_ % 20 == 0)
	{	// cube UŒ‚
		int cube_index = 0;
		DevicePropertyX1* cube_dpx = cube_collection_[cube_index].device_.dpx_;
		GraphicPropertyX4* cube_gadget_gpx = cube_collection_[cube_index].device_.device_gpx_;
		EffectPropertyX1* cube_epx = cube_collection_[cube_index].device_.epx_;
		GraphicPropertyX4* cube_effect_gpx = cube_collection_[cube_index].device_.effect_gpx_;
		cube_dpx->create_x_ = cube_collection_[cube_index].phandle_->grid_x_;
		cube_dpx->create_y_ = cube_collection_[cube_index].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ += 10;
		for (int way = 0; way < 4; way++)
		{
			cube_dpx->delay_time_frame_ = 0;
			for (int n = 0; n < 4; n++)
			{
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
				cube_dpx->delay_time_frame_ += 3;
			}
			cube_dpx->move_angle_deg_ += 90;	
		}
		cube_index = 1;
		cube_dpx = cube_collection_[cube_index].device_.dpx_;
		cube_gadget_gpx = cube_collection_[cube_index].device_.device_gpx_;
		cube_epx = cube_collection_[cube_index].device_.epx_;
		cube_effect_gpx = cube_collection_[cube_index].device_.effect_gpx_;
		cube_dpx->create_x_ = cube_collection_[cube_index].phandle_->grid_x_;
		cube_dpx->create_y_ = cube_collection_[cube_index].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ += 10;
		for (int way = 0; way < 4; way++)
		{
			cube_dpx->delay_time_frame_ = 0;
			for (int n = 0; n < 4; n++)
			{
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
				cube_dpx->delay_time_frame_ += 3;
			}
			cube_dpx->move_angle_deg_ += 90;	
		}
		cube_index = 2;
		cube_dpx = cube_collection_[cube_index].device_.dpx_;
		cube_gadget_gpx = cube_collection_[cube_index].device_.device_gpx_;
		cube_epx = cube_collection_[cube_index].device_.epx_;
		cube_effect_gpx = cube_collection_[cube_index].device_.effect_gpx_;
		cube_dpx->create_x_ = cube_collection_[cube_index].phandle_->grid_x_;
		cube_dpx->create_y_ = cube_collection_[cube_index].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ -= 10;
		for (int way = 0; way < 4; way++)
		{
			cube_dpx->delay_time_frame_ = 0;
			for (int n = 0; n < 4; n++)
			{
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
				cube_dpx->delay_time_frame_ += 3;
			}
			cube_dpx->move_angle_deg_ += 90;	
		}
		cube_index = 3;
		cube_dpx = cube_collection_[cube_index].device_.dpx_;
		cube_gadget_gpx = cube_collection_[cube_index].device_.device_gpx_;
		cube_epx = cube_collection_[cube_index].device_.epx_;
		cube_effect_gpx = cube_collection_[cube_index].device_.effect_gpx_;
		cube_dpx->create_x_ = cube_collection_[cube_index].phandle_->grid_x_;
		cube_dpx->create_y_ = cube_collection_[cube_index].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ -= 10;
		for (int way = 0; way < 4; way++)
		{
			cube_dpx->delay_time_frame_ = 0;
			for (int n = 0; n < 4; n++)
			{
				NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
				cube_dpx->delay_time_frame_ += 3;
			}
			cube_dpx->move_angle_deg_ += 90;	
		}
	}

	if (count_frame_ % 20 == 0)
	{	// main UŒ‚
		main_.device1_.dpx_->create_x_ = main_.phandle_->grid_x_ - 10;
		main_.device1_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device1_.dpx_->delay_time_frame_ = 0;
		NyaDevice::Attack1414(main_.device1_.dpx_, main_.device1_.device_gpx_, main_.device1_.epx_, main_.device1_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device1_.dpx_->delay_time_frame_ = 3;
		NyaDevice::Attack1414(main_.device1_.dpx_, main_.device1_.device_gpx_, main_.device1_.epx_, main_.device1_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device1_.dpx_->delay_time_frame_ = 6;
		NyaDevice::Attack1414(main_.device1_.dpx_, main_.device1_.device_gpx_, main_.device1_.epx_, main_.device1_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->create_x_ = main_.phandle_->grid_x_ + 10;
		main_.device2_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device2_.dpx_->delay_time_frame_ = 0;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.device_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->delay_time_frame_ = 3;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.device_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device2_.dpx_->delay_time_frame_ = 6;
		NyaDevice::Attack1414(main_.device2_.dpx_, main_.device2_.device_gpx_, main_.device2_.epx_, main_.device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device1_.dpx_->move_angle_deg_ -= 10;
		main_.device2_.dpx_->move_angle_deg_ += 10;
	}

	if (count_frame_ == FPS_MAX * 18)
		NyaPosition::MoveGridMode(main_.phandle_, main_.phandle_->grid_x_, -200, FPS_MAX * 2);
}

void Target1Chlamydiae::Draw1(void)
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
	{	// cube •`‰æ
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
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
	{	// cube ”š”­
		for (auto& e : cube_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
		// main ‘å”š”­
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaGraphic::Swing();
	}
}

