#include "NyaInterface.h"
#include "TeemoBackgroundMission1.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx.h"
#include "UserAI.h"

using namespace H2NLIB;

void TeemoMission1::Create(void) 
{
	unsigned int id = 0;
	InterfaceHandleMissionSkill* ihandle_mission_skill;

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
	AddChild(new UserAi);

	//******************
	// interface �ݒ�
	//******************
	ihandle_mission_skill = NyaInterface::GetHandleMissionSkill();
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::Q)] = "Skill Q (power)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::W)] = "Passive W (bit)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::E)] = "Passive E (speed)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::R)] = "Skill R (ult)";
}

void TeemoMission1::Delete(void)
{
	// user�ȊO�͎��̃~�b�V�����Ɉ����p���Ȃ��̂ŏ��������Ă���
	ClearBackground();
	ClearTarget();
}

