#pragma once

#include "NyaTarget.h"

namespace H2NLIB 
{
	class DevicePropertyX1;
	class DevicePropertyX3;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
}

//********************************
// Act1(), Draw1() で使うクラス
//********************************

class TeemoExDevice211
{
public:
	H2NLIB::DevicePropertyX1* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice211();
	~TeemoExDevice211();
};

class TeemoExCube21
{
public:
	TeemoExDevice211 device211_;
	H2NLIB::EffectPropertyX1* death_epx_;
	H2NLIB::GraphicPropertyX4* death_gpx_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	TeemoExCube21();
	~TeemoExCube21();
};

//********************************
// Act1(), Draw1() で使うクラス
//********************************

class TeemoExDevice221
{
public:
	H2NLIB::DevicePropertyX3* dpx_;
	H2NLIB::GraphicPropertyX4* gadget_gpx_;
	H2NLIB::EffectPropertyX1* epx_;
	H2NLIB::GraphicPropertyX4* effect_gpx_;
	TeemoExDevice221();
	~TeemoExDevice221();
};

class TeemoExMain2
{
public:
	TeemoExDevice211 device211_;
	TeemoExDevice221 device221_;
	const unsigned int health_max_;
	H2NLIB::GraphicPropertyX4* gpx_;
	H2NLIB::PositionHandle* phandle_;
	TeemoExMain2();
	~TeemoExMain2();
};

class TeemoTargetEx2 : public H2NLIB::NyaTarget
{
public:
	TeemoTargetEx2();
	~TeemoTargetEx2();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	std::array<TeemoExCube21, 10> cube21_collection_;
	TeemoExMain2 main_;
	int mode_;
	void Act1(void);
	void Act2(void);
	void Draw1(void);
	void Draw2(void);
};

