#include "Target3Kluyvera.h"
#include "Target3Pantoea.h"
#include "TeemoBackgroundMission1.h"
#include "TeemoMission3.h"
#include "TeemoTargetEx3.h"
#include "UserAI.h"


void TeemoMission3::Create(void)
{
	//*****************************************************
	// �X�N���[������w�i��BGM���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*****************************************************
	AddBackground(new TeemoBackgroundMission1);

	//*******************************************
	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*******************************************
	AddTarget(0, 60, new Target3Pantoea(SCREEN_MAX_X / 2 - 210, 350));
	AddTarget(0, 60, new Target3Pantoea(SCREEN_MAX_X / 2 - 70, 350));
	AddTarget(0, 60, new Target3Pantoea(SCREEN_MAX_X / 2 + 70, 350));
	AddTarget(0, 60, new Target3Pantoea(SCREEN_MAX_X / 2 + 210, 350));
	for (int i = 0; i < 8; i++)
	{
		AddTarget(2, 32, new Target3Kluyvera(-100 - (i * 100) + 40, 200, false));
		AddTarget(2, 32, new Target3Kluyvera(-100 - (i * 100), 200, false));
	}
	AddTarget(100, 600, new TeemoTargetEx3);

	//**************************************
	// ���[�U�[���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//**************************************
	AddUser(new UserAi);
}

void TeemoMission3::Delete(void)
{
	ClearTarget();
}
