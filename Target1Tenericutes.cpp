#include <tuple>
#include "HNLIB.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "Target1Tenericutes.h"
#include "TeemoLock.h"

using namespace std;
using namespace HNLIB;

Target1TenericutesCubeDevice::Target1TenericutesCubeDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 5;
	TeemoFactory::TargetAttackOrange9(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target1TenericutesCubeDevice::~Target1TenericutesCubeDevice()
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

Target1TenericutesCube::Target1TenericutesCube()
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

Target1TenericutesCube::~Target1TenericutesCube()
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

Target1TenericutesMainDevice::Target1TenericutesMainDevice()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 6;
	TeemoFactory::TargetAttackYellow2(dpx_, device_gpx_, epx_, effect_gpx_);
}

Target1TenericutesMainDevice::~Target1TenericutesMainDevice()
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

Target1TenericutesMain::Target1TenericutesMain() : health_max_(400), exp_(20000)
{
	lock_ = new TeemoLock(eLOCK::CHLAMYDIAE);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath2(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(4, 1, "img/target/main_tenericutes.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->health_ = health_max_;
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -200;
}

Target1TenericutesMain::~Target1TenericutesMain()
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

Target1Tenericutes::Target1Tenericutes(int x, int y)
{
	count_frame_ = 0;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
}

Target1Tenericutes::~Target1Tenericutes()
{

}

//********************************
// Target1Tenericutes ƒƒ“ƒoŠÖ”
//********************************

void Target1Tenericutes::Act(void)
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
			NyaSound::Play(main_.death_spx_);
		}
		break;
	case 2:
		return;
	}

	main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
	count_frame_++;
}

void Target1Tenericutes::Draw(void)
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

void Target1Tenericutes::Act1(void)
{
	if (count_frame_ == 1)
	{
		cube_collection_[0].device_.dpx_->move_angle_deg_ = -90;
		cube_collection_[1].device_.dpx_->move_angle_deg_ = -90;
		NyaPosition::MoveGridMode(main_.phandle_, main_.phandle_->grid_x_, 80, FPS_MAX * 2);
	}

	// cube ”z’u
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 70;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 70;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 50;

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

	if (count_frame_ < FPS_MAX * 3 || SCREEN_MAX_Y - 100 < main_.phandle_->grid_y_)
		return;

	if (count_frame_ % 10 == 0)
	{	// cube UŒ‚
		int cube_index = 0;
		DevicePropertyX1* cube_dpx = cube_collection_[cube_index].device_.dpx_;
		GraphicPropertyX4* cube_gadget_gpx = cube_collection_[cube_index].device_.device_gpx_;
		EffectPropertyX1* cube_epx = cube_collection_[cube_index].device_.epx_;
		GraphicPropertyX4* cube_effect_gpx = cube_collection_[cube_index].device_.effect_gpx_;
		cube_dpx->create_x_ = cube_collection_[cube_index].phandle_->grid_x_;
		cube_dpx->create_y_ = cube_collection_[cube_index].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ -= 10;
		NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		cube_index = 1;
		cube_dpx = cube_collection_[cube_index].device_.dpx_;
		cube_gadget_gpx = cube_collection_[cube_index].device_.device_gpx_;
		cube_epx = cube_collection_[cube_index].device_.epx_;
		cube_effect_gpx = cube_collection_[cube_index].device_.effect_gpx_;
		cube_dpx->create_x_ = cube_collection_[cube_index].phandle_->grid_x_;
		cube_dpx->create_y_ = cube_collection_[cube_index].phandle_->grid_y_;
		cube_dpx->move_angle_deg_ += 10;
		NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}

	if (count_frame_ % 20 == 0)
	{	// main UŒ‚
		PositionHandle phandle_user;
		main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaPosition::FindHandle("user", &phandle_user);
		main_.device_.dpx_->move_angle_deg_ = NyaPosition::Angle(main_.phandle_, &phandle_user);
		main_.device_.dpx_->delay_time_frame_ = 0;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->delay_time_frame_ = 3;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device_.dpx_->delay_time_frame_ = 6;
		NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.device_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}
}

void Target1Tenericutes::Draw1(void)
{
	// main •`‰æ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 30 == 0)
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

