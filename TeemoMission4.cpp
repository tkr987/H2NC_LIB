#include "TeemoMission4.h"
#include "TeemoTargetEx4.h"
#include "UserAI.h"

TeemoMission4::TeemoMission4()
{
}


TeemoMission4::~TeemoMission4()
{
}

void TeemoMission4::Create(void)
{
	//*******************************************
	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*******************************************
	AddTarget(3, 3600, new TeemoTargetEx4);
}

void TeemoMission4::Delete(void)
{
	ClearTarget();
	ClearUser();
}