#include "TeemoBack1.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"
#include "TeemoMark1.h"
#include "UserAI.h"

using namespace HNLIB;

void TeemoMission1::Create(void) 
{
	unsigned int ctime = 0;
	InterfaceHandleSkill* ihandle_mission_skill;

	//*****************************************************
	// �X�N���[������w�i��BGM���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*****************************************************
	AddBack(new TeemoBack1);

	//*******************************************
	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*******************************************
	ctime = 2;
	AddTarget(ctime, 600, new TeemoMark1);

	//**************************************
	// ���[�U�[���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//**************************************
	AddUser(new UserAi);

	//******************
	// interface �ݒ�
	//******************
	/*
	ihandle_mission_skill = NyaInterface::GetHandleSkill();
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::Q)] = "Skill Q (power)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::W)] = "Passive W (bit)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::E)] = "Passive E (speed)";
	ihandle_mission_skill->name_[static_cast<unsigned int>(eSKILL::R)] = "Skill R (ult)";
	*/
}

void TeemoMission1::Delete(void)
{
	// user�ȊO�͎��̃~�b�V�����Ɉ����p���Ȃ��̂ŏ��������Ă���
	ClearBackground();
	ClearTarget();
}

