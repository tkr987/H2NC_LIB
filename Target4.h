#pragma once
#include <map>
#include "DefineNH.h"

namespace NH2T {
	class TargetBase;
}

class Target4 {
public:
	Target4(void) {};
	~Target4(void) {};
	void End(void);
	void Init(int lv);
	eGEVENT::TYPE Run(void);
private:
	int phase_;
	long frames_;
	std::multimap<long, NH2T::TargetBase*> map_target_;
};

