#pragma once

#include "NyaTarget.h"


namespace H2NLIB {
	class NyaDevice;
	class NyaGraphic;
	class NyaPosition;
	class NyaString;
	class DevicePropertyX;
	class GraphicPropertyX4;
	class PositionHandleX;
}


class TeemoTarget : public H2NLIB::NyaTarget {
public:
	TeemoTarget();
	~TeemoTarget();
	void Act(void);
	void Draw(void);
	void End(void){}
	void Init(void);
private:
	long count_;
	H2NLIB::NyaDevice* nya_device_;
	H2NLIB::NyaGraphic* nya_graphic_;
	H2NLIB::NyaPosition* nya_position_;
	H2NLIB::DevicePropertyX* dpx_;
	H2NLIB::GraphicPropertyX4* gpx4_teemo_;
	H2NLIB::PositionHandleX* phx_teemo_;
};

