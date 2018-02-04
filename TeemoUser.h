#pragma once

#include "NyaUser.h"

namespace H2NLIB {
	struct DevicePropertyX;
	struct EffectPropertyX;
	struct GraphicPropertyX4;
	struct PositionHandleX;
	class NyaDevice;
	class NyaEffect;
	class NyaGraphic;
	class NyaPosition;
	class NyaString;
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
	H2NLIB::DevicePropertyX* dpx_teemo_;
	H2NLIB::EffectPropertyX* epx_teemo_;
	H2NLIB::GraphicPropertyX4* gpx4_teemo_;
	H2NLIB::PositionHandleX* phx_teemo_;
};

