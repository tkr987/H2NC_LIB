#pragma once
#include "NyaEnding.h"

namespace HNLIB
{
	class GraphicPropertyX1;
}

class TeemoEnding : public HNLIB::NyaEnding
{
public:	
	TeemoEnding();
	~TeemoEnding();
	void Load(void);
	void Run(void);
	void Delete(void);
private:
	HNLIB::GraphicPropertyX1* gpx_;
};


