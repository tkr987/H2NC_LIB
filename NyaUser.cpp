#include "NyaPosition.h"
#include "NyaUser.h"

using namespace H2NLIB;

NyaUser::NyaUser()
{
	static bool first_call = true;

	if (first_call) {
		nya_position_ = new NyaPosition;

		ppx = nya_position_->Create();
		ppx->x_ = 100;
		ppx->y_ = 200;
	}
}


NyaUser::~NyaUser()
{

}

void NyaUser::Run(void)
{
	ppx->x_ += 1;
}

