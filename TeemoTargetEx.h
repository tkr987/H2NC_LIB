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
	class GraphicPropertyX4;
	class PositionHandleX;
}

class TeemoTargetEx : public H2NLIB::NyaTarget
{
public:
	TeemoTargetEx();
	~TeemoTargetEx();
	void Act(void);
	void Draw(void);
	void End(void){}
private:
	int count_;
	H2NLIB::NyaDesign* nya_design_;
	H2NLIB::NyaGraphic* nya_graphic_;
	H2NLIB::NyaPosition* nya_position_;
	H2NLIB::GraphicPropertyX4* gpx4_teemo_;
	H2NLIB::PositionHandleX* phx_teemo_;
};

