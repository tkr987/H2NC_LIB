#pragma once

#include <array>
#include "NyaTarget.h"

class TeemoLock;

namespace HNLIB
{
	class DevicePropertyX1;
	class DevicePropertyX3;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

//*************************************
// Act1(), Draw1() で使うクラス
//*************************************
class TeemoDevice311
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice311();
	~TeemoDevice311();
};

class TeemoCube31
{
public:
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoCube31();
	~TeemoCube31();
};

//*************************************
// Act2(), Draw2() で使うクラス
//*************************************
class TeemoDevice321
{
public:
	HNLIB::DevicePropertyX3* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice321();
	~TeemoDevice321();
};

class TeemoDevice322
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice322();
	~TeemoDevice322();
};

class TeemoCube32
{
public:
	TeemoDevice322 device322_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoCube32();
	~TeemoCube32();
};


//*************************************
// Act3(), Draw3() で使うクラス
//*************************************
class TeemoDevice331
{
public:
	double way1_angle_;
	double way2_angle_;
	double way3_angle_;
	double way4_angle_;
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice331();
	~TeemoDevice331();
};

class TeemoDevice332
{
public:
	HNLIB::DevicePropertyX1* dpx_;
	HNLIB::GraphicPropertyX4* device_gpx_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	TeemoDevice332();
	~TeemoDevice332();
};


class TeemoCube33
{
public:
	TeemoDevice332 device332_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death_epx_;
	HNLIB::GraphicPropertyX4* death_gpx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoCube33();
	~TeemoCube33();
};

class TeemoMain3
{
public:
	TeemoDevice311 device311_;
	TeemoDevice321 device321_;
	TeemoDevice331 device331_;
	const unsigned int exp_;
	const unsigned int health_max_;
	TeemoLock* lock_;
	HNLIB::EffectPropertyX1* death1_epx_;
	HNLIB::GraphicPropertyX4* death1_gpx_;
	HNLIB::SoundPropertyX* death1_spx_;
	HNLIB::EffectPropertyX1* death2_epx_;
	HNLIB::GraphicPropertyX4* death2_gpx_;
	HNLIB::SoundPropertyX* death2_spx_;
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TeemoMain3();
	~TeemoMain3();
};



class TeemoMark3 : public HNLIB::NyaTarget
{
public:
	TeemoMark3();
	~TeemoMark3();
	void Act(void);
	void Draw(void);
private:
	int count_frame_;
	int mode_;
	std::array<TeemoCube31, 100> cube31_collection_;
	std::array<TeemoCube32, 6> cube32_collection_;
	std::array<TeemoCube33, 4> cube33_collection_;
	TeemoMain3 main_;
	HNLIB::SoundPropertyX* warning_spx_;
	void Act1(void);
	void Act2(void);
	void Act3(void);
	void Draw1(void);
	void Draw2(void);
	void Draw3(void);
	void Draw4(void);
};

