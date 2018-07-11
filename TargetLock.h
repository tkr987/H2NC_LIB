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
	void LoadGraphic(std::string);
	void Run(const HNLIB::PositionHandle* phandle);
	TargetLock();
	~TargetLock();
private:
	HNLIB::GraphicPropertyX4* gpx_;
	unsigned int lock_frame_;
	HNLIB::SoundPropertyX* spx_;
	static unsigned int played_sound_frame_;
};


