#include "NyaEnum.h"
#include "NyaTarget.h"

using namespace H2NLIB;

/**
@brief ���s�֐�
@note
 ���C�u������NyaWindow�N���X���Ŏ����I�ɌĂ΂��̂ŁA���C�u�����g�p�҂��ĂԕK�v�͂Ȃ��B
**/
void NyaTarget::Run(eEVENT check_event)
{
	switch (check_event)
	{
	case eEVENT::MISSION_RUN:
	case eEVENT::MISSION_REPLAY_RUN:
		MissionRun();
		break;
	case eEVENT::MISSION_CONTINUE:
		MissionContinue();
		break;
	case eEVENT::MISSION_CLEAR:
	case eEVENT::MISSION_ALL_CLEAR:
	case eEVENT::MISSION_REPLAY_CLEAR:
	case eEVENT::MISSION_REPLAY_ALL_CLEAR:
		MissionClear();
		break;
	}
}

