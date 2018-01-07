#pragma once
#include "DefineNH.h"

namespace NH2 {
	struct ImgParam1;
	struct PosParam;
}

class StageContinue {
public:
	void DataLoad(void);
	void Run(eGEVENT::TYPE *type);
	StageContinue();
	~StageContinue();
private:
	int select_;
	int imgfile_no_;
	int imgfile_yes_;
	NH2::ImgParam1 *iparam1_;
};
