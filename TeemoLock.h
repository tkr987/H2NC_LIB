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
	AQUIFICAE, CHLOROBI, CHLAMYDIAE, DICTYOGLOMI, ECTROMELIA, FIRMICUTES, PANTOEA, PICORNA, TENERICUTES,
	CUBE, TEEMO_EX, TEEMO_MARK1, TEEMO_MARK2, 
	sizeof_enum,
};


class TeemoLock
{
public:
	void LoadGraphic(std::string);
	void Run(const HNLIB::PositionHandle* phandle);
	TeemoLock();
	TeemoLock(eLOCK type);
	~TeemoLock();
private:
	HNLIB::GraphicPropertyX4* gpx_;
	unsigned int lock_frame_;
	HNLIB::SoundPropertyX* spx_;
	static unsigned int played_sound_frame_;
	void LoadGraphic(eLOCK type);
};


