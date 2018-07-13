#pragma once
#include <array>
#include "NyaTarget.h"
#include "TargetLock.h"

namespace HNLIB
{
	class DevicePropertyX1;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class Target3PseudomonadMain
{
public:
	HNLIB::GraphicPropertyX4* gpx_;
	HNLIB::PositionHandle* phandle_;
	TargetLock lock_;
	Target3PseudomonadMain();
	~Target3PseudomonadMain();
};


class Target3Pseudomonad : public HNLIB::NyaTarget
{
public:
	void Act(void);
	void Draw(void);
	Target3Pseudomonad(int x, int y, int move_max_x, int move_max_y, bool turn);
	~Target3Pseudomonad();
private:
	unsigned int count_frame_;
	Target3PseudomonadMain main_;
	std::array<Target3PseudomonadMain, 9> main_collection_;
	unsigned int mode_;
	int move_max_x_;
	int move_max_y_;
	bool turn_;
	void Act1(void);
	void Draw1(void);
};

