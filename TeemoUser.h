#pragma once

#include "NyaUser.h"
#include <utility>

namespace H2NLIB {
	class NyaDevice;
	class NyaEffect;
	class NyaGraphic;
	class NyaPosition;
	class DevicePropertyX;
	class EffectPropertyX;
	class GraphicPropertyX4;
	class PositionHandleX;
	class DeviceOption;
	class EffectOption;
}


class TeemoUser : public H2NLIB::NyaUser {
public:
	TeemoUser();
	~TeemoUser();
	void Action(void);
	void Draw(void);
	void Init(void);
private:
	long count_;
	H2NLIB::NyaDevice* nya_device_;
	H2NLIB::NyaEffect* nya_effect_;
	H2NLIB::NyaGraphic* nya_graphic_;
	H2NLIB::NyaPosition* nya_position_;
	H2NLIB::DevicePropertyX* dpx_;
	H2NLIB::EffectPropertyX* epx_;
	H2NLIB::GraphicPropertyX4* gpx4_teemo_;
	H2NLIB::PositionHandleX* phx_teemo_;
	std::pair<H2NLIB::DeviceOption*, int> device_option_pair_;
	std::pair<H2NLIB::EffectOption*, int> effect_option_pair_;
};

