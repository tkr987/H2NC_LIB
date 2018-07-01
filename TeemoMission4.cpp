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
	AddTarget(1, 3600, new TeemoTargetEx4);

	//**************************************
	// ���[�U�[���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//**************************************
	AddUser(new UserAi);
}

void TeemoMission4::Delete(void)
{
	ClearBackground();
	ClearTarget();
	ClearUser();
}