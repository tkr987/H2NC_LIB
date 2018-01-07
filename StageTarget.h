#pragma once
#include <map>
#include "DefineNH.h"

namespace NH2T {
	class TargetBase;
}


class StageTarget {
public:
	StageTarget(void) {};
	~StageTarget(void) {};
	void MemoryEnd(void);
	void MemoryInit(void);
	void DataDelete(void);
	void DataLoad(eGEVENT::TYPE type, long start_frames);
	void Run(eGEVENT::TYPE *type);
private:
	int phase_;
	long frames_;
	std::multimap<long, NH2T::TargetBase*> map_target_;
	void CreateTarget1(int lv);
	void CreateTarget2(int lv);
	void CreateTarget3(int lv);
};
