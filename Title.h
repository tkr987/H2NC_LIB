#pragma once
#include "DefineNH.h"

namespace NH2 {
	struct ImgParam1;
}

class Title {
public:
	void End(void);
	void Init(void);
	void Run(eGEVENT::TYPE *type);
	Title(void) {}
	~Title(void) {}
private:
	int imgfile_main_[7];
	int imgfile_help_;
	int select_;
	bool help_;
	NH2::ImgParam1 *iparam1_main_;
	NH2::ImgParam1 *iparam1_help_;
	void Draw(void);
	void KeyUpdate(eGEVENT::TYPE *type);
};

