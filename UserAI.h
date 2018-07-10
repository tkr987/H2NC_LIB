#pragma once

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
	HNLIB::GraphicPropertyX4* bit_gpx_;
	HNLIB::DevicePropertyX1* gadget_dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX2* effect_epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	HNLIB::SoundPropertyX* spx_[6];
	HNLIB::SoundPropertyX* spx_ex_[6];
	UserAiDevice();
	~UserAiDevice();
};

class UserAiDeviceEx
{
public:
	bool valid_;
	int count_ult_frame_;
	HNLIB::GraphicPropertyX4* bit_gpx_;
	HNLIB::DevicePropertyX1* gadget_dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX2* effect_epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	UserAiDeviceEx();
	~UserAiDeviceEx();
};

struct UserAiMain
{
public:
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	UserAiMain();
	~UserAiMain();
};


class UserAi : public HNLIB::NyaUser {
public:
	UserAi();
	~UserAi();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	UserAiDevice device_;
	UserAiDeviceEx device_ex_;
	UserAiMain main_;
	UserAiRange range_;
	void Act_Attack(void);
	void Act_AttackEx(void);
	void Act_Move(void);
	void Act_Ult(void);
};

