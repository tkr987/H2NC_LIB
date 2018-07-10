#pragma once

#include "NyaOpening.h"

namespace HNLIB
{
	class GraphicPropertyX1;
}

class TeemoOpening : public HNLIB::NyaOpening
{
public:	
	TeemoOpening();
	~TeemoOpening();
	void Load(void);
	void Run(void);
	void Delete(void);
private:
	HNLIB::GraphicPropertyX1* gpx_;
};

