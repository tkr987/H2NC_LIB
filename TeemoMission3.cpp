#include "TeemoMission3.h"
#include "TeemoTargetEx3.h"
#include "UserAI.h"


void TeemoMission3::Create(void)
{
	//*******************************************
	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*******************************************
	AddTarget(1, 600, new TeemoTargetEx3);

	//**************************************
	// ���[�U�[���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//**************************************
	AddUser(new UserAi);
}

void TeemoMission3::Delete(void)
{
	ClearTarget();
}
