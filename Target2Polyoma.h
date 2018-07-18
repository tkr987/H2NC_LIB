#pragma once
#include "NyaTarget.h"

class TargetLock;

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class Target2PolyomaDevice
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* gadget_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	Target2PolyomaDevice();
	~Target2PolyomaDevice();
};

class Target2PolyomaMain
{
public:
	Target2PolyomaDevice device_;
	unsigned int health_max_;
	TargetLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::SoundPropertyX* death_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	Target2PolyomaMain();
	~Target2PolyomaMain();
};


class Target2Polyoma : public HNLIB::NyaTarget
{
public:
	Target2Polyoma(int x, int y, bool turn);
	~Target2Polyoma();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	Target2PolyomaMain main_;
	unsigned int mode_;
	bool turn_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};



