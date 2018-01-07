#pragma once
#include <map>
#include "Stage.h"

namespace NH2 {
	struct ImgParam1;
	class PosParam1;
}

namespace NH2T {
	class TargetBase;
}

class Stage1 : public Stage {
public:
	Stage1();
	~Stage1();
	void Load(int lv, int rand, long frame = 0);
	void Run(void);
private:
	int continue_select_;
	int imgfile_continue_no_;
	int imgfile_continue_yes_;
	int imgfile_map_;
	int soundfile_bgm_boss_;
	int soundfile_bgm_stage_;
	NH2::ImgParam1* iparam1_continue_;
	NH2::ImgParam1b* iparam1b_map_;
	NH2::PosParam1* pparam1_map_;
	std::multimap<long, NH2T::TargetBase*> map_target_;
	void Phase10_Target(void);
	void Phase11_Target(void);
	void Phase11_Continue(eGEVENT::TYPE*);
	void RunMap(void);
	void RunTarget(eGEVENT::TYPE*);
};

