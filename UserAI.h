#pragma once

#include <utility>
#include "h2nlib.h"

namespace H2NLIB
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
	H2NLIB::GraphicPropertyX4* gpx_;
	UserAiRange();
	~UserAiRange();
};

class UserAiDevice
{
public:
	H2NLIB::GraphicPropertyX4* bit_gpx_;
	H2NLIB::DevicePropertyX1* gadget_dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX2* effect_epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	H2NLIB::SoundPropertyX* spx_[6];
	H2NLIB::SoundPropertyX* spx_ex_[6];
	UserAiDevice();
	~UserAiDevice();
};

class UserAiDeviceEx
{
public:
	bool valid_;
	int count_ult_frame_;
	H2NLIB::GraphicPropertyX4* bit_gpx_;
	H2NLIB::DevicePropertyX1* gadget_dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX2* effect_epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	UserAiDeviceEx();
	~UserAiDeviceEx();
};

struct UserAiMain
{
public:
	H2NLIB::EffectPropertyX1* death_epx_;
	H2NLIB::GraphicPropertyX4* death_gpx_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	UserAiMain();
	~UserAiMain();
};


class UserAi : public H2NLIB::NyaUser {
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

