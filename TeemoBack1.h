#pragma once
#include "NyaBack.h"

namespace HNLIB
{
	class GraphicPropertyX1;
}

class TeemoBack1 : public HNLIB::NyaBack
{
public:
	TeemoBack1();
	~TeemoBack1();
private:
	HNLIB::GraphicPropertyX1* gpx_;
	void Act(void);
	void Draw(void);
};

