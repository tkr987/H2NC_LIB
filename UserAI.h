#pragma once
#include <array>
#include <utility>
#include "HNLIB.h"

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class EffectPropertyX2;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class UserAiBarrier
{
public:
	int count_frame_;
	bool valid_;
	HNLIB::GraphicPropertyX4* gpx_;
	UserAiBarrier();
	~UserAiBarrier();
};

class UserAiRange
{
public:
	HNLIB::GraphicPropertyX4* gpx_;
	UserAiRange();
	~UserAiRange();
};

class UserAiDevice
{
public:
	int sound_index_;
	HNLIB::GraphicPropertyX4* bit_gpx_;
	HNLIB::DevicePropertyX1* gadget_dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX2* effect_epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	std::array<HNLIB::SoundPropertyX*, 6> spx_collection_;
	UserAiDevice();
	~UserAiDevice();
};

class UserAiDeviceEx
{
public:
	int count_ult_frame_;
	int sound_index_;
	bool valid_;
	HNLIB::GraphicPropertyX4* bit_gpx_;
	HNLIB::DevicePropertyX1* gadget_dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX2* effect_epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	std::array<HNLIB::SoundPropertyX*, 6> spx_collection_;
	UserAiDeviceEx();
	~UserAiDeviceEx();
};

struct UserAiMain
{
public:
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	HNLIB::EffectPropertyX2* ult_epx_;
	HNLIB::GraphicPropertyX4* ult_gpx_;
	std::array<HNLIB::SoundPropertyX*, 4> ult_spx_collection_;
	UserAiMain();
	~UserAiMain();
};

class UserSkill
{
public:
	HNLIB::SoundPropertyX* spx_q_;
	HNLIB::SoundPropertyX* spx_w_;
	HNLIB::SoundPropertyX* spx_e_;
	HNLIB::SoundPropertyX* spx_r_;
	HNLIB::GraphicPropertyX4* gpx_q_;
	HNLIB::GraphicPropertyX4* gpx_w_;
	HNLIB::GraphicPropertyX4* gpx_e_;
	HNLIB::GraphicPropertyX4* gpx_r_;
	UserSkill();
	~UserSkill();
};

class UserAi : public HNLIB::NyaUser {
public:
	UserAi();
	~UserAi();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	UserAiBarrier barrier_;
	UserAiDevice device_;
	UserAiDeviceEx device_ex_;
	UserAiMain main_;
	UserAiRange range_;
	UserSkill skill_;
	void Act_Attack(void);
	void Act_AttackEx(void);
	void Act_ChangeSkill(void);
	void Act_Collide(void);
	void Act_Move(void);
	void Act_Ult(void);
};

