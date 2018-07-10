#pragma once
#include "NyaUser.h"

namespace HNLIB 
{
	class GraphicPropertyX4;
}

class TeemoUser : public HNLIB::NyaUser
{
public:
	HNLIB::GraphicPropertyX4* gpx_;
	TeemoUser();
	~TeemoUser();
	void Act(void);
	void Draw(void);
};

