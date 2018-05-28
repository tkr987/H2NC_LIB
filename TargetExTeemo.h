#pragma once

#include "NyaTarget.h"

namespace H2NLIB 
{
	class NyaDesign;
	class NyaDevice;
	class NyaGraphic;
	class NyaPosition;
	class NyaSound;
	class NyaString;
	class DeviceProperty1;
	class GraphicProperty4;
	class PositionHandle1;
}

class TargetExTeemoMain
{
public:
	H2NLIB::GraphicProperty4* gp_;
	H2NLIB::PositionHandle1* ph_;
	TargetExTeemoMain();
	~TargetExTeemoMain();
};

class TargetExTeemo : public H2NLIB::NyaTarget
{
public:
	TargetExTeemo();
	~TargetExTeemo();
	void Act(void);
	void Draw(void);
private:
	int count_;
	H2NLIB::NyaDesign* nya_design_;
	H2NLIB::NyaGraphic* nya_graphic_;
	H2NLIB::NyaPosition* nya_position_;
	H2NLIB::NyaSound* nya_sound_;
	TargetExTeemoMain main_;
};

