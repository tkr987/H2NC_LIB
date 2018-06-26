#pragma once

#include "NyaOpening.h"

namespace H2NLIB
{
	class GraphicPropertyX1;
}

class TeemoOpening : public H2NLIB::NyaOpening
{
public:	
	TeemoOpening();
	~TeemoOpening();
	void Load(void);
	void Run(void);
	void Delete(void);
private:
	H2NLIB::GraphicPropertyX1* gpx_;
};

