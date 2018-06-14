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

class UserAiDevice2
{
public:
	H2NLIB::DevicePropertyX1* gadget_dp_;
	H2NLIB::GraphicPropertyX4* gadget_gp_;
	H2NLIB::EffectProperty1* effect_ep_;
	H2NLIB::GraphicPropertyX4* effect_gp_;
	UserAiDevice2();
	~UserAiDevice2();
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


class UserAI : public H2NLIB::NyaUser {
public:
	UserAI();
	~UserAI();
	void MissionRun(void);
private:
	unsigned int count_frame_;
	H2NLIB::NyaDevice* nya_device_;
	H2NLIB::NyaEffect* nya_effect_;
	H2NLIB::NyaPosition* nya_position_;
	UserAiDevice2 ai_device2_;
	UserAiEffectTest ai_effect_test_;
	UserAiEffectTest ai_effect_test2_;
	UserAiMain main_;
	std::pair<H2NLIB::DeviceOption*, int> device_option_pair_;
	std::pair<H2NLIB::EffectOption*, int> effect_option_pair_;
	void Act(void);
	void Draw(void);
};

