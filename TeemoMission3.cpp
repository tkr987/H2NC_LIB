#include "TeemoMission3.h"
#include "TeemoTargetEx3b.h"


void TeemoMission3::Create(void)
{
	unsigned int id = 0;

	//*******************************************
	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*******************************************
	AddChild(5, 600, new TeemoTargetEx3b, id++);
}
