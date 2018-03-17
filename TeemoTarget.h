#pragma once

#include "NyaTarget.h"


namespace H2NLIB {
	class NyaDevice;
	class NyaGraphic;
	class NyaPosition;
	class NyaString;
	class DevicePropertyX1;
	class GraphicPropertyX4;
	class PositionHandleX;
}


class TeemoTarget : public H2NLIB::NyaTarget {
public:
	TeemoTarget();
	~TeemoTarget();
	void Act(void);
	void Draw(void);
private:
	long count_;
	H2NLIB::NyaDevice* nya_device_;
	H2NLIB::NyaGraphic* nya_graphic_;
	H2NLIB::NyaPosition* nya_position_;
	H2NLIB::DevicePropertyX1* teemo_dpx1_;
	H2NLIB::GraphicPropertyX4* teemo_gpx4_;
	H2NLIB::PositionHandleX* teemo_phx_;
};

