#pragma once
#include <string>

namespace HNLIB
{
	class GraphicPropertyX4;
	class PositionHandle;
	class SoundPropertyX;
}

enum class eLOCK
{
	enum_zero,
	ECTROMELIA, PICORNA, 
};


class TargetLock
{
public:
	void LoadGraphic(std::string);
	void Run(const HNLIB::PositionHandle* phandle);
	TargetLock();
	TargetLock(eLOCK type);
	~TargetLock();
private:
	HNLIB::GraphicPropertyX4* gpx_;
	unsigned int lock_frame_;
	HNLIB::SoundPropertyX* spx_;
	static unsigned int played_sound_frame_;
	void LoadGraphic(eLOCK type);
};


