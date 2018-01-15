#pragma once

#include "NyaUser.h"

namespace H2NLIB {
	struct AttackPropertyX;
}


class TeemoUser : public H2NLIB::NyaUser {
public:
	TeemoUser();
	~TeemoUser();
	void Run(void);
private:
	H2NLIB::AttackPropertyX* apx_;
};

