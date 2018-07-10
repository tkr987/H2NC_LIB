#pragma once
#include <string>

namespace HNLIB
{
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

class TargetLock
{
public:
	HNLIB::GraphicPropertyX4* gpx_;
	unsigned int lock_frame_;
	HNLIB::SoundPropertyX* spx_;
	void LoadGraphic(std::string);
	void Run(const HNLIB::PositionHandle* phandle);
	TargetLock();
	~TargetLock();
};


