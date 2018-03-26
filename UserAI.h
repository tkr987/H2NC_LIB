#pragma once

#include "NyaUser.h"
#include <utility>

namespace H2NLIB
{
	class NyaDesign;
	class NyaDevice;
	class NyaEffect;
	class NyaGraphic;
	class NyaPosition;
	class DeviceProperty1;
	class EffectProperty1;
	class GraphicProperty4;
	class PositionHandle1;
	class DeviceOption;
	class EffectOption;
}

class UserAiDevice
{
public:
	H2NLIB::DeviceProperty1* dp_;
	H2NLIB::GraphicProperty4* gp_;
	UserAiDevice();
	~UserAiDevice();
};

struct UserAiEffectTest
{
public:
	H2NLIB::EffectProperty1* ep_;
	H2NLIB::GraphicProperty4* gp_;
	UserAiEffectTest();
	~UserAiEffectTest();
};


struct UserAiMain
{
public:
	H2NLIB::GraphicProperty4* gp_;
	H2NLIB::PositionHandle1* ph_;
	UserAiMain();
	~UserAiMain();
};


class UserAI : public H2NLIB::NyaUser {
public:
	UserAI();
	~UserAI();
	void Act(void);
	void Draw(void);
	void Init(void);
private:
	long count_;
	H2NLIB::NyaDesign* nya_design_;
	H2NLIB::NyaDevice* nya_device_;
	H2NLIB::NyaEffect* nya_effect_;
	H2NLIB::NyaGraphic* nya_graphic_;
	H2NLIB::NyaPosition* nya_position_;
	UserAiDevice ai_device_;
	UserAiEffectTest ai_effect_test_;
	UserAiMain ai_main_;
	std::pair<H2NLIB::DeviceOption*, int> device_option_pair_;
	std::pair<H2NLIB::EffectOption*, int> effect_option_pair_;
};

