#include "NyaInterface.h"
#include "NyaGraphic.h"
#include "TeemoBackgroundMission1.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx.h"
#include "UserAI.h"

using namespace H2NLIB;

void TeemoMission1::Create(void) 
{
	unsigned int id = 0;

	//*****************************************************
	// �X�N���[������w�i��BGM���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*****************************************************
	AddChild(new TeemoBackgroundMission1);

	//*******************************************
	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*******************************************
	AddChild(5, 600, new TargetExTeemo, id++);

	//**************************************
	// ���[�U�[���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//**************************************
	AddChild(new UserAI);

	//******************
	// interface �ݒ�
	//******************
	NyaInterface::SetSkillName(eSKILL::Q, "Skill Q (power)");
	NyaInterface::SetSkillName(eSKILL::W, "Skill W (wave)");
	NyaInterface::SetSkillName(eSKILL::E, "Skill E (bit)");
	NyaInterface::SetSkillName(eSKILL::R, "Skill R (bomb)");
}

void TeemoMission1::Delete(void)
{
	DeleteBackground();
	DeleteTarget();
}

