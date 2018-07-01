#pragma once

#include "h2nlib.h"

class TeemoUser : public H2NLIB::NyaUser
{
public:
	H2NLIB::GraphicPropertyX4* gpx_;
	TeemoUser();
	~TeemoUser();
	void MissionRun(void);
};

