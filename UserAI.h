#pragma once

#include "NyaUser.h"
#include <utility>

namespace H2NLIB
{
	class NyaDevice;
	class NyaEffect;
	class NyaPosition;
	class DevicePropertyX1;
	class EffectProperty1;
	class GraphicPropertyX4;
	class PositionHandle1;
	class DeviceOption;
	class EffectOption;
}

class UserAiDevice
{
public:
	H2NLIB::DevicePropertyX1* gadget_dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectProperty1* effect_epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	UserAiDevice();
	~UserAiDevice();
};

class UserAiEffectTest
{
public:
	H2NLIB::EffectProperty1* ep_;
	H2NLIB::GraphicPropertyX4* gp_;
	UserAiEffectTest();
	~UserAiEffectTest();
};

struct UserAiMain
{
public:
	H2NLIB::GraphicPropertyX4* gp_;
	H2NLIB::PositionHandle1* ph_;
	UserAiMain();
	~UserAiMain();
};


class UserAi : public H2NLIB::NyaUser {
public:
	UserAi();
	~UserAi();
	void MissionRun(void);
private:
	unsigned int count_frame_;
	H2NLIB::NyaDevice* nya_device_;
	H2NLIB::NyaEffect* nya_effect_;
	H2NLIB::NyaPosition* nya_position_;
	UserAiDevice user_device_;
	UserAiEffectTest ai_effect_test_;
	UserAiEffectTest ai_effect_test2_;
	UserAiMain main_;
	std::pair<H2NLIB::DeviceOption*, int> device_option_pair_;
	std::pair<H2NLIB::EffectOption*, int> effect_option_pair_;
	void Act(void);
	void Draw(void);
	void Act_Attack(void);
};

