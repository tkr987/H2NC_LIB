#pragma once
#include "NyaTarget.h"


namespace HNLIB
{
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class SoundPropertyX;
}

class Target2Warning : public HNLIB::NyaTarget 
{
public:
	Target2Warning(int x, int y);
	~Target2Warning();
	void Act(void);
	void Draw(void);
private:
	unsigned int count_frame_;
	HNLIB::EffectPropertyX1* epx_;
	HNLIB::GraphicPropertyX4* effect_gpx_;
	HNLIB::SoundPropertyX* spx_;
};

