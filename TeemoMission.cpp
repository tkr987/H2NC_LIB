#include "TeemoMission.h"
#include "TeemoUser.h"

using namespace H2NLIB;

void TeemoMission::Create(void)
{
	AddUser(new TeemoUser);
}

void TeemoMission::Delete(void)
{
	ClearUser();
}
