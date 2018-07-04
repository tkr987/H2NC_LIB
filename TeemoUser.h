#pragma once
#include "NyaUser.h"

namespace H2NLIB 
{
	class GraphicPropertyX4;
}

class TeemoUser : public H2NLIB::NyaUser
{
public:
	H2NLIB::GraphicPropertyX4* gpx_;
	TeemoUser();
	~TeemoUser();
	void Act(void);
	void Draw(void);
};

