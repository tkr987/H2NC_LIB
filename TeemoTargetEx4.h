#pragma once

#include "NyaTarget.h"
#include <array>

namespace H2NLIB 
{
	class DevicePropertyX1;
	class GraphicPropertyX4;
	class PositionHandle1;
	class SoundPropertyX;
}

class TeemoEx4Cube
{
public:
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle1* phandle_;
	TeemoEx4Cube();
	~TeemoEx4Cube();
};


class TeemoEx4Main
{
public:
	const int health_max_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle1* phandle_;
	TeemoEx4Main();
	~TeemoEx4Main();
};

class TeemoTargetEx4 : public H2NLIB::NyaTarget
{
public:
	TeemoTargetEx4();
	~TeemoTargetEx4();
	void MissionRun(void);
private:
	unsigned int count_frame_;
	TeemoEx4Main main_;
	std::array<TeemoEx4Cube, 8> cube1_collection_;
	H2NLIB::SoundPropertyX* warning_spx_;
	void Act1(void);
	void Draw1(void);
};

