#pragma once

#include <map>

namespace NH2T {
	class TargetBase;
}


class Target3 {
public:
	Target3(void) {};
	~Target3(void) {};
	void End(void);
	void Init(int lv);
	eGEVENT::TYPE Run(void);
private:
	int phase_;
	long frames_;
	std::multimap<long, NH2T::TargetBase*> map_target_;
};

