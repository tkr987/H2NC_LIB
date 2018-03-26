#pragma once

#include "NyaTarget.h"

namespace H2NLIB
{
	class NyaDevice;
	class NyaDesign;
	class NyaGraphic;
	class NyaPosition;
	class NyaString;
	class DevicePropertyX;
	class GraphicProperty4;
	class PositionHandle1;
}

class TeemoTargetEx : public H2NLIB::NyaTarget
{
public:
	TeemoTargetEx();
	~TeemoTargetEx();
	void Act(void);
	void Draw(void);
private:
	int count_;
	H2NLIB::NyaDesign* nya_design_;
	H2NLIB::NyaGraphic* nya_graphic_;
	H2NLIB::NyaPosition* nya_position_;
	H2NLIB::GraphicProperty4* teemo_gp4_;
	H2NLIB::PositionHandle1* teemo_ph1_;
};

