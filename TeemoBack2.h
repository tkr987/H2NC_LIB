#pragma once
#include "NyaGraphic.h"
#include "NyaBack.h"
#include "TeemoEnum.h"

namespace HNLIB
{
	class GraphicPropertyX1;
}

class TeemoBack2 : public HNLIB::NyaBack
{
public:
	TeemoBack2();
	~TeemoBack2();
private:
	HNLIB::GraphicPropertyX1* gpx_;
	void Act(void);
	void Draw(void);
};
