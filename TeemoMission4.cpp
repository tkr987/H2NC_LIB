#include "TeemoMission4.h"
#include "TeemoTargetEx4.h"

TeemoMission4::TeemoMission4()
{
}


TeemoMission4::~TeemoMission4()
{
}

void TeemoMission4::Create(void)
{
	unsigned int id = 0;

	//*******************************************
	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*******************************************
	AddChild(1, 3600, new TeemoTargetEx4, id++);
}

void TeemoMission4::Delete(void)
{
	ClearBackground();
	ClearTarget();
	ClearUser();
}