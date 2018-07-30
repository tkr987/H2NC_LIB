#pragma once
#include "NyaTarget.h"

class TeemoLock;

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class Target1DictyoglomiMainDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target1DictyoglomiMainDevice();
	~Target1DictyoglomiMainDevice();
};

class Target1DictyoglomiMain
{
public:
	TeemoLock* lock_;
	Target1DictyoglomiMainDevice device_;
	const unsigned int exp_;
	const unsigned int health_max_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target1DictyoglomiMain();
	~Target1DictyoglomiMain();
};

class Target1Dictyoglomi : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target1Dictyoglomi(int x, int y, int move_max_x, int move_max_y);
	~Target1Dictyoglomi();
private:
	unsigned int count_frame_;
	Target1DictyoglomiMain main_;
	unsigned int mode_;
	double move_angle_;
	int move_max_x_;
	int move_max_y_;
	int move_start_time_;
	void Act1(void);
	void Draw1(void);
};


