#include <tuple>
#include "HNLIB.h"
#include "TeemoLock.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "TeemoMark2.h"

#define __DEBUG__

using namespace std;
using namespace HNLIB;

//*************************************
// Act1(), Draw1() Ç≈égÇ§ÉNÉâÉX
//*************************************

TeemoDevice211::TeemoDevice211()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 2;
	TeemoFactory::TargetAttackPurple3(dpx_, device_gpx_, epx_, effect_gpx_);
}

TeemoDevice211::~TeemoDevice211()
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

TeemoDevice212::TeemoDevice212()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 11;
	TeemoFactory::TargetAttackOrange1(dpx_, device_gpx_, epx_, effect_gpx_);
}

TeemoDevice212::~TeemoDevice212()
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

TeemoCube21::TeemoCube21()
{
	device_gap_angle_ = 40;
	lock_ = new TeemoLock(eLOCK::CUBE);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetCube(gpx_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoCube21::~TeemoCube21()
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

//**********************************
// Act2(), Draw2() Ç≈égÇ§ÉNÉâÉX
//**********************************
TeemoDevice221::TeemoDevice221()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 5;
	TeemoFactory::TargetAttackPurple2(dpx_, device_gpx_, epx_, effect_gpx_);
}

TeemoDevice221::~TeemoDevice221()
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

TeemoDevice222::TeemoDevice222()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 7;
	TeemoFactory::TargetAttackOrange3(dpx_, device_gpx_, epx_, effect_gpx_);
}

TeemoDevice222::~TeemoDevice222()
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

TeemoDevice223::TeemoDevice223()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 7;
	TeemoFactory::TargetAttackOrange3(dpx_, device_gpx_, epx_, effect_gpx_);
}

TeemoDevice223::~TeemoDevice223()
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

TeemoCube22::TeemoCube22()
{
	death_epx_ = new EffectPropertyX1;
	death_epx_->interval_time_frame_ = 3;
	death_gpx_ = new GraphicPropertyX4;
	death_gpx_->extend_rate_ = 0.5;
	NyaGraphic::Load(4, 2, "img/target/death1.png", &death_gpx_->file_);
	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 0.01;
	NyaGraphic::Load(5, 1, "img/target/cube_orange.png", &gpx_->file_);
	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoCube22::~TeemoCube22()
{
	NyaGraphic::Delete(&death_gpx_->file_);
	NyaGraphic::Delete(&gpx_->file_);
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

//*************************************
// Act3(), Draw3() Ç≈égÇ§ÉNÉâÉX
//*************************************

TeemoDevice231::TeemoDevice231()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 6;
	TeemoFactory::TargetAttackPurple1(dpx_, device_gpx_, epx_, effect_gpx_);
}

TeemoDevice231::~TeemoDevice231()
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

TeemoDevice232::TeemoDevice232()
{
	dpx_ = new DevicePropertyX1;
	device_gpx_ = new GraphicPropertyX4;
	epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
	dpx_->move_speed_ = 10;
	TeemoFactory::TargetAttackOrange1(dpx_, device_gpx_, epx_, effect_gpx_);
}

TeemoDevice232::~TeemoDevice232()
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

TeemoCube23::TeemoCube23()
{
	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetCube(gpx_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

TeemoCube23::~TeemoCube23()
{
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

//*****************
// TeemoMain
//*****************

TeemoMain2::TeemoMain2() : exp_(50000), health_max_(140000)
{
	lock_ = new TeemoLock(eLOCK::TEEMO_MARK2);

	death1_epx_ = new EffectPropertyX1;
	death1_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death1_epx_, death1_gpx_);
	death1_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death1.wav", &death1_spx_->file_);
	NyaSound::ChangeVolume(&death1_spx_->file_, TARGET_DEATH1_SOUND_VOLUME);

	death2_epx_ = new EffectPropertyX1;
	death2_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath2(death2_epx_, death2_gpx_);
	death2_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death2.wav", &death2_spx_->file_);
	NyaSound::ChangeVolume(&death2_spx_->file_, TARGET_DEATH2_SOUND_VOLUME);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/teemo_mark2.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = SCREEN_MAX_X / 2;
	phandle_->grid_y_ = -100;
	phandle_->health_ = health_max_;
}

TeemoMain2::~TeemoMain2()
{
	NyaGraphic::Delete(&gpx_->file_);
	NyaSound::Delete(&death1_spx_->file_);
	NyaSound::Delete(&death2_spx_->file_);

	delete lock_;
	lock_ = nullptr;
	delete death1_epx_;
	death1_epx_ = nullptr;
	delete death1_gpx_;
	death1_gpx_ = nullptr;
	delete death1_spx_;
	death1_spx_ = nullptr;
	delete death2_epx_;
	death2_epx_ = nullptr;
	delete death2_gpx_;
	death2_gpx_ = nullptr;
	delete death2_spx_;
	death2_spx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

//*****************
// TeemoMark2
//*****************

TeemoMark2::TeemoMark2(void)
{
	count_frame_ = 0;
	mode_ = 1;
	warning_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/warning.wav", &warning_spx_->file_);
	NyaSound::ChangeVolume(&warning_spx_->file_, 20);
}

TeemoMark2::~TeemoMark2(void)
{
	delete warning_spx_;
	warning_spx_ = nullptr;
}

//***************************
// TeemoMark2 ÉÅÉìÉoä÷êî
//***************************

void TeemoMark2::Act(void)
{
	switch (mode_)
	{
	case 1:
		Act1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK2_MODE1_HEALTH)
		{
			count_frame_ = 0;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
			NyaSound::Play(main_.death1_spx_);
		}
		break;
	case 2:
		Act2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK2_MODE2_HEALTH)
		{
			count_frame_ = 0;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
			NyaSound::Play(main_.death1_spx_);
		}
		break;
	case 3:
		Act3();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_MARK2_MODE3_HEALTH)
		{
			count_frame_ = 0;
			NyaInterface::GetHandleSkill()->AddExp((unsigned int)NyaDevice::Size(eOBJECT::TARGET_ATTACK1) * 1000);
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaSound::Play(main_.death1_spx_);
		}
		break;
	case 4:
		if (count_frame_ == 30 * 8)
		{
			NyaInterface::GetHandleLife()->value_ += 1;
			NyaInterface::GetHandleSkill()->AddExp(main_.exp_);
			NyaSound::Play(main_.death2_spx_);
		}
		if (count_frame_ == 30 * 18)
			NyaInterface::GetHandleClear()->valid_ = true;
		break;
	}

	if (FPS_MAX * 60 * 4 < count_frame_)
		NyaInterface::GetHandleLife()->value_ = 0;
	count_frame_++;
}

void TeemoMark2::Draw(void)
{
	switch (mode_)
	{
	case 1:
		Draw1();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK2_MODE1_HEALTH)
			mode_ = 2;
		break;
	case 2:
		Draw2();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK2_MODE2_HEALTH)
			mode_ = 3;
		break;
	case 3:
		Draw3();
		if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_MARK2_MODE3_HEALTH)
			mode_ = 4;
		break;
	case 4:
		Draw4();
		break;
	}
}

void TeemoMark2::Act1(void)
{
	PositionHandle phandle_user;

	if (count_frame_ == 1)
	{	// çsìÆäJén1ÉtÉåÅ[ÉÄñ⁄
		NyaInterface::GetHandleHealth()->valid_ = true;
		NyaInterface::GetHandleWarning()->valid_ = true;
		NyaSound::Play(warning_spx_);
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 3);
	}

	if (count_frame_ == FPS_MAX * 3)
	{	// cubeÇèâä˙à íuÇ÷îzíu
		cube21_collection_[0].phandle_->grid_x_ = 50;
		cube21_collection_[0].phandle_->grid_y_ = 50;
		cube21_collection_[1].phandle_->grid_x_ = SCREEN_MAX_X - 50;
		cube21_collection_[1].phandle_->grid_y_ = 50;
		cube21_collection_[2].phandle_->grid_x_ = SCREEN_MAX_X - 50;
		cube21_collection_[2].phandle_->grid_y_ = SCREEN_MAX_Y - 60;
		cube21_collection_[3].phandle_->grid_x_ = 50;
		cube21_collection_[3].phandle_->grid_y_ = SCREEN_MAX_Y - 60;
	}

	// è’ìÀîªíËÅ@è’ìÀÉ_ÉÅÅ[ÉWÇæÇØåoå±ílÇí«â¡
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube21_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
	}

	if (count_frame_ < FPS_MAX * 4)
		return;

	// ÉwÉãÉXå∏è≠
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (auto& e: cube21_collection_)
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;

	if (count_frame_ % (FPS_MAX * 3) == FPS_MAX)
	{	// mainà⁄ìÆèàóù
		int move_end_x = (int)main_.phandle_->grid_x_ + NyaInput::GetRand(-50, 50);
		if (250 <= move_end_x  && move_end_x < SCREEN_MAX_X - 250)
			NyaPosition::MoveGridMode(main_.phandle_, move_end_x, main_.phandle_->grid_y_, FPS_MAX);
	}

	if (count_frame_ % 30 == 0)
	{	// mainçUåÇèàóù
		main_.device211_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device211_.dpx_->create_y_ = main_.phandle_->grid_y_;
		for (int way = 0; way < 16; way++)
		{
			main_.device211_.dpx_->move_angle_deg_ += 5;
			NyaDevice::Attack1414(main_.device211_.dpx_, main_.device211_.device_gpx_, main_.device211_.epx_, main_.device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device211_.dpx_->move_angle_deg_ += (180 - 80);
		for (int way = 0; way < 16; way++)
		{
			main_.device211_.dpx_->move_angle_deg_ += 5;
			NyaDevice::Attack1414(main_.device211_.dpx_, main_.device211_.device_gpx_, main_.device211_.epx_, main_.device211_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		main_.device211_.dpx_->move_angle_deg_ += (180 - 80 - 32);
	}

	if (count_frame_ % 4 == 0 && count_frame_ % (FPS_MAX * 8) < FPS_MAX * 3)
	{	// cubeçUåÇèàóù
		for (int cube_index = 0; cube_index < 4; cube_index++)
		{
			NyaPosition::FindHandle("user", &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
			cube21_collection_[cube_index].device212_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ += cube21_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.device_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ -= cube21_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.device_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			if (6 < cube21_collection_[cube_index].device_gap_angle_)
				cube21_collection_[cube_index].device_gap_angle_--;
		}
	}
	else if (count_frame_ % 4 == 0 && FPS_MAX * 3 <= count_frame_ % (FPS_MAX * 8))
	{	// cubeçUåÇèàóù
		for (int cube_index = 0; cube_index < 4; cube_index++)
		{
			NyaPosition::FindHandle("user", &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->create_x_ = cube21_collection_[cube_index].phandle_->grid_x_;
			cube21_collection_[cube_index].device212_.dpx_->create_y_ = cube21_collection_[cube_index].phandle_->grid_y_;
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ += cube21_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.device_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube21_collection_[cube_index].phandle_, &phandle_user);
			cube21_collection_[cube_index].device212_.dpx_->move_angle_deg_ -= cube21_collection_[cube_index].device_gap_angle_;
			NyaDevice::Attack1414(cube21_collection_[cube_index].device212_.dpx_, cube21_collection_[cube_index].device212_.device_gpx_, cube21_collection_[cube_index].device212_.epx_, cube21_collection_[cube_index].device212_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			if (cube21_collection_[cube_index].device_gap_angle_ < 40)
				cube21_collection_[cube_index].device_gap_angle_ ++;
		}
	}
}

void TeemoMark2::Act2(void)
{
	// mainÇèâä˙à íuÇ…à⁄ìÆÇ≥ÇπÇÈ
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 2);

	if (count_frame_ == FPS_MAX * 3)
	{	// cubeÇèâä˙à íuÇ…à⁄ìÆÇ≥ÇπÇÈ
		cube22_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_;
		cube22_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_;
		cube22_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_;
		cube22_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_;
		NyaPosition::MoveGridMode(cube22_collection_[0].phandle_, main_.phandle_->grid_x_ - 100, main_.phandle_->grid_y_ - 50, FPS_MAX * 2);
		NyaPosition::MoveGridMode(cube22_collection_[1].phandle_, main_.phandle_->grid_x_ + 100, main_.phandle_->grid_y_ - 50, FPS_MAX * 2);
	}

	// è’ìÀîªíËÅ@è’ìÀÉ_ÉÅÅ[ÉWÇæÇØåoå±ílÇí«â¡
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube22_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
	}

	if (count_frame_ < FPS_MAX * 5)
		return;

	// ÉwÉãÉXå∏è≠
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (auto& e : cube22_collection_)
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;

	if (count_frame_ % (FPS_MAX * 3) == FPS_MAX)
	{	// mainà⁄ìÆèàóù
		int move_end_x = (int)main_.phandle_->grid_x_ + NyaInput::GetRand(-50, 50);
		if (250 <= move_end_x  && move_end_x < SCREEN_MAX_X - 250)
			NyaPosition::MoveGridMode(main_.phandle_, move_end_x, main_.phandle_->grid_y_, FPS_MAX);
	}

	// cubeç¿ïWçXêV
	cube22_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube22_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ -  50;
	cube22_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube22_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ -  50;

	if (count_frame_ % (FPS_MAX * 3) == 0)
	{	// mainçUåÇèàóù
		main_.device221_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device221_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device221_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		for (int way = 0; way < 60; way++)
		{
			main_.device221_.dpx_->move_angle_deg_ += 6;
			NyaDevice::Attack1414(main_.device221_.dpx_, main_.device221_.device_gpx_, main_.device221_.epx_, main_.device221_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}

	if (count_frame_ % 20 == 0)
	{	// cubeçUåÇèàóù
		for (int way = 0; way < 4; way ++)
		{
			double gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ - 90));
			double gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ - 90));
			cube22_collection_[0].device222_.dpx_->create_x_ = cube22_collection_[0].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[0].device222_.dpx_->create_y_ = cube22_collection_[0].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 4; delay++)
			{
				cube22_collection_[0].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[0].device222_.dpx_, cube22_collection_[0].device222_.device_gpx_, cube22_collection_[0].device222_.epx_, cube22_collection_[0].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ + 90));
			gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ + 90));
			cube22_collection_[0].device222_.dpx_->create_x_ = cube22_collection_[0].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[0].device222_.dpx_->create_y_ = cube22_collection_[0].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 4; delay++)
			{
				cube22_collection_[0].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[0].device222_.dpx_, cube22_collection_[0].device222_.device_gpx_, cube22_collection_[0].device222_.epx_, cube22_collection_[0].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube22_collection_[0].device222_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		}
		for (int way = 0; way < 4; way ++)
		{
			double gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ - 90));
			double gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ - 90));
			cube22_collection_[1].device222_.dpx_->create_x_ = cube22_collection_[1].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[1].device222_.dpx_->create_y_ = cube22_collection_[1].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 4; delay++)
			{
				cube22_collection_[1].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[1].device222_.dpx_, cube22_collection_[1].device222_.device_gpx_, cube22_collection_[1].device222_.epx_, cube22_collection_[1].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ + 90));
			gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ + 90));
			cube22_collection_[1].device222_.dpx_->create_x_ = cube22_collection_[1].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[1].device222_.dpx_->create_y_ = cube22_collection_[1].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 4; delay++)
			{
				cube22_collection_[1].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[1].device222_.dpx_, cube22_collection_[1].device222_.device_gpx_, cube22_collection_[1].device222_.epx_, cube22_collection_[1].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube22_collection_[1].device222_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		}
	}
	if (count_frame_ % 20 == 10)
	{	// cubeçUåÇèàóù
		for (int way = 0; way < 4; way ++)
		{
			double gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ - 90));
			double gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ - 90));
			cube22_collection_[0].device222_.dpx_->create_x_ = cube22_collection_[0].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[0].device222_.dpx_->create_y_ = cube22_collection_[0].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 4; delay++)
			{
				cube22_collection_[0].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[0].device222_.dpx_, cube22_collection_[0].device222_.device_gpx_, cube22_collection_[0].device222_.epx_, cube22_collection_[0].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ + 90));
			gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[0].device222_.dpx_->move_angle_deg_ + 90));
			cube22_collection_[0].device222_.dpx_->create_x_ = cube22_collection_[0].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[0].device222_.dpx_->create_y_ = cube22_collection_[0].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 4; delay++)
			{
				cube22_collection_[0].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[0].device222_.dpx_, cube22_collection_[0].device222_.device_gpx_, cube22_collection_[0].device222_.epx_, cube22_collection_[0].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube22_collection_[0].device222_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		}
		for (int way = 0; way < 4; way ++)
		{
			double gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ - 90));
			double gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ - 90));
			cube22_collection_[1].device222_.dpx_->create_x_ = cube22_collection_[1].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[1].device222_.dpx_->create_y_ = cube22_collection_[1].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 4; delay++)
			{
				cube22_collection_[1].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[1].device222_.dpx_, cube22_collection_[1].device222_.device_gpx_, cube22_collection_[1].device222_.epx_, cube22_collection_[1].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			gap_grid_x = 10 * cos(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ + 90));
			gap_grid_y = 10 * sin(NyaInput::AngleToRad(cube22_collection_[1].device222_.dpx_->move_angle_deg_ + 90));
			cube22_collection_[1].device222_.dpx_->create_x_ = cube22_collection_[1].phandle_->grid_x_ + gap_grid_x;
			cube22_collection_[1].device222_.dpx_->create_y_ = cube22_collection_[1].phandle_->grid_y_ + gap_grid_y;
			for (int delay = 0; delay < 4; delay++)
			{
				cube22_collection_[1].device222_.dpx_->delay_time_frame_ = 3 * delay;
				NyaDevice::Attack1414(cube22_collection_[1].device222_.dpx_, cube22_collection_[1].device222_.device_gpx_, cube22_collection_[1].device222_.epx_, cube22_collection_[1].device222_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
			}
			cube22_collection_[1].device222_.dpx_->move_angle_deg_ = NyaInput::GetRand(0, 360);
		}
	}
}

void TeemoMark2::Act3(void)
{
	PositionHandle phandle_user;

	// mainèâä˙à íuÇ÷à⁄ìÆ
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 2);

	if (count_frame_ == FPS_MAX * 3)
	{	// cubeèâä˙à íuÇ÷à⁄ìÆ
		for (auto& e : cube23_collection_)
		{
			e.phandle_->grid_x_ = main_.phandle_->grid_x_;
			e.phandle_->grid_y_ = main_.phandle_->grid_y_;
		}
		for (int i = 0; i < 5; i++)
			NyaPosition::MoveGridMode(cube23_collection_[i].phandle_, main_.phandle_->grid_x_ - (5 - i) * 70, 80, FPS_MAX * 2);
		for (int i = 5; i < 10; i++)
			NyaPosition::MoveGridMode(cube23_collection_[i].phandle_, main_.phandle_->grid_x_ + (i - 4) * 70, 80, FPS_MAX * 2);
	}

	// è’ìÀîªíËÅ@è’ìÀÉ_ÉÅÅ[ÉWÇæÇØåoå±ílÇí«â¡
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	for (auto& e : cube23_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
	}

	if (count_frame_ < FPS_MAX * 5)
		return;

	// ÉwÉãÉXå∏è≠
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (auto& e : cube23_collection_)
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;

	if (count_frame_ % FPS_MAX == 0)
	{	// mainà⁄ìÆèàóù
		int move_end_x = (int)main_.phandle_->grid_x_ + NyaInput::GetRand(-20, 20);
		int move_end_y = (int)main_.phandle_->grid_y_ + NyaInput::GetRand(-20, 20);
		if (SCREEN_MIN_X + 250 < move_end_x  && move_end_x < SCREEN_MAX_X - 250 && SCREEN_MIN_Y + 140 < move_end_y && move_end_y < SCREEN_MIN_Y + 200)
		NyaPosition::MoveGridMode(main_.phandle_, move_end_x, move_end_y, FPS_MAX - 3);
	}

	if (count_frame_ % 8 == 0)
	{
		main_.device231_.dpx_->create_x_ = main_.phandle_->grid_x_;
		main_.device231_.dpx_->create_y_ = main_.phandle_->grid_y_;
		main_.device231_.dpx_->move_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1414(main_.device231_.dpx_, main_.device231_.device_gpx_, main_.device231_.epx_, main_.device231_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device231_.dpx_->move_angle_deg_ += 2;
		NyaDevice::Attack1414(main_.device231_.dpx_, main_.device231_.device_gpx_, main_.device231_.epx_, main_.device231_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device231_.dpx_->move_angle_deg_ += 2;
		NyaDevice::Attack1414(main_.device231_.dpx_, main_.device231_.device_gpx_, main_.device231_.epx_, main_.device231_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device231_.dpx_->move_angle_deg_ += 2;
		NyaDevice::Attack1414(main_.device231_.dpx_, main_.device231_.device_gpx_, main_.device231_.epx_, main_.device231_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		main_.device231_.dpx_->move_angle_deg_ += 2;
		NyaDevice::Attack1414(main_.device231_.dpx_, main_.device231_.device_gpx_, main_.device231_.epx_, main_.device231_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}

	if (count_frame_ % FPS_MAX * 2 == 0)
	{	
		// cubeçUåÇèàóù
		int cube_index = 3;
		NyaPosition::FindHandle("user", &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 5; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.device_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 6;
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 5; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.device_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cubeà⁄ìÆèàóù
		double move_x, move_y;
		cube_index = 0;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 9;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24)
	{
		// cubeçUåÇèàóù
		int cube_index = 4;
		NyaPosition::FindHandle("user", &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 5; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.device_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 5;
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 5; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.device_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cubeà⁄ìÆèàóù
		double move_x, move_y;
		cube_index = 1;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 8;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 2)
	{
		// cubeçUåÇèàóù
		int cube_index = 0;
		NyaPosition::FindHandle("user", &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 5; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.device_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 9;
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 5; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.device_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cubeà⁄ìÆèàóù
		double move_x, move_y;
		cube_index = 2;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 7;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 3)
	{
		// cubeçUåÇèàóù
		int cube_index = 1;
		NyaPosition::FindHandle("user", &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 5; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.device_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 8;
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 5; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.device_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cubeà⁄ìÆèàóù
		double move_x, move_y;
		cube_index = 3;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 6;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
	else if (count_frame_ % FPS_MAX * 2 == 24 * 4)
	{
		// cubeçUåÇèàóù
		int cube_index = 2;
		NyaPosition::FindHandle("user", &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 5; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.device_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		cube_index = 7;
		cube23_collection_[cube_index].device232_.dpx_->move_angle_deg_ =  NyaPosition::Angle(cube23_collection_[cube_index].phandle_, &phandle_user);
		cube23_collection_[cube_index].device232_.dpx_->create_x_ = cube23_collection_[cube_index].phandle_->grid_x_;
		cube23_collection_[cube_index].device232_.dpx_->create_y_ = cube23_collection_[cube_index].phandle_->grid_y_;
		for (int delay = 0; delay < 5; delay++)
		{
			cube23_collection_[cube_index].device232_.dpx_->delay_time_frame_ = delay * 2;
			NyaDevice::Attack1414(cube23_collection_[cube_index].device232_.dpx_, cube23_collection_[cube_index].device232_.device_gpx_, cube23_collection_[cube_index].device232_.epx_, cube23_collection_[cube_index].device232_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1, 2);
		}
		// cubeà⁄ìÆèàóù
		double move_x, move_y;
		cube_index = 4;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
		cube_index = 5;
		move_x = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_x_ - 150, cube23_collection_[cube_index].phandle_->grid_x_ + 150);
		move_y = NyaInput::GetRand(cube23_collection_[cube_index].phandle_->grid_y_ - 100, cube23_collection_[cube_index].phandle_->grid_y_ + 100);
		move_x = (move_x < 80) ? 80 : (SCREEN_MAX_X - 80 < move_x) ? SCREEN_MAX_X - 80 : move_x;
		move_y = (move_y < 100) ? 100 : (300 < move_y) ? 300 : move_y;
		NyaPosition::MoveGridMode(cube23_collection_[cube_index].phandle_, move_x, move_y, 16);
	}
}

void TeemoMark2::Draw1(void)
{
	// mainï`âÊ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ÉçÉbÉNï`âÊ
	main_.lock_->Run(main_.phandle_);

	for (auto& e : cube21_collection_)
	{
		// cubeägëÂ
		if (e.gpx_->extend_rate_ < 0.4)
			e.gpx_->extend_rate_ += 0.01;
		// cubeï`âÊ
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube ÉçÉbÉNï`âÊ
		e.lock_->Run(e.phandle_);
	}

	// ÉwÉãÉXï\é¶
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK2_MODE1_HEALTH)
	{	// cubeîöî≠
		for (auto& e : cube21_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void TeemoMark2::Draw2(void)
{
	// mainï`âÊ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// ÉwÉãÉXï\é¶
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	if (count_frame_ < FPS_MAX * 3)
		return;

	for (auto& e : cube22_collection_)
	{
		// cubeägëÂ
		if (e.gpx_->extend_rate_ < 0.4)
			e.gpx_->extend_rate_ += 0.01;
		// cubeï`âÊ
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 < TEEMO_MARK2_MODE2_HEALTH)
	{	// cubeîöî≠
		for (auto& e : cube22_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void TeemoMark2::Draw3(void)
{
	// mainï`âÊ
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// ÉwÉãÉXï\é¶
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;

	for (auto& e : cube23_collection_)
	{	// cubeï`âÊ
		if (NyaInput::GetFrameCount() % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
	}

	if ((double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0 <= TEEMO_MARK2_MODE3_HEALTH)
	{	// cubeîöî≠
		for (auto& e : cube23_collection_)
		{
			e.death_epx_->grid_x_ = e.phandle_->grid_x_;
			e.death_epx_->grid_y_ = e.phandle_->grid_y_;
			NyaEffect::Draw(e.death_epx_, e.death_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}
}

void TeemoMark2::Draw4(void)
{
	if (count_frame_ < 30 * 7)
	{
		if (count_frame_ % 30 == 0)
		{	//è¨îöî≠èàóù
			main_.death1_epx_->grid_x_ = main_.phandle_->grid_x_ + NyaInput::GetRand(-30, 30);
			main_.death1_epx_->grid_y_ = main_.phandle_->grid_y_ + NyaInput::GetRand(-30, 30);
			NyaEffect::Draw(main_.death1_epx_, main_.death1_gpx_, eOBJECT::TARGET_EFFECT1);
		}
	}

	if (count_frame_ == 30 * 8)
	{	// ëÂîöî≠èàóù
		main_.death2_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death2_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death2_epx_, main_.death2_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaGraphic::Swing();
	}

	if (count_frame_ < 30 * 10)
	{	// mainï`âÊ
		main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
		main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
		NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	}

	// ÉwÉãÉXï\é¶
	NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
}
