#include "NyaBack.h"
#include "NyaEnum.h"

using namespace HNLIB;


/**
@brief ���s�֐�
@note
 ���C�u������NyaMission�N���X���Ŏ����I�ɌĂ΂��̂ŁA���C�u�����g�p�҂��ĂԕK�v�͂Ȃ�
**/
void NyaBack::Run(const eEVENT check_event)
{
	switch (check_event)
	{
	case eEVENT::MISSION_RUN:
	case eEVENT::MISSION_REPLAY_RUN:
		Act();
		Draw();
		break;
	case eEVENT::MISSION_CONTINUE:
	case eEVENT::MISSION_CLEAR:
	case eEVENT::MISSION_COMPLETE:
	case eEVENT::MISSION_REPLAY_END:
	case eEVENT::MISSION_REPLAY_CLEAR:
	case eEVENT::MISSION_REPLAY_COMPLETE:	
		Draw();
		break;
	}
}