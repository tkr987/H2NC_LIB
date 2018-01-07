#pragma once

// no bug

namespace H2NLIB
{
	class NyaDesign;
}

class TeemoDesign {
public:
	TeemoDesign();
	~TeemoDesign();
	void Create(void);
private:
	H2NLIB::NyaDesign* nya_design_;
};

