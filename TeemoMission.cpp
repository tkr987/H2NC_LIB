#include "TeemoMission.h"
#include "TeemoTarget.h"
#include "TeemoUser.h"

using namespace HNLIB;

void TeemoMission::Create(void)
{
//	AddTarget(1, 100, new TeemoTarget);
//	AddUser(new TeemoUser);
}

void TeemoMission::Delete(void)
{
	ClearTarget();
	ClearUser();
}
