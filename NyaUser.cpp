#include "NyaUser.h"
using namespace HNLIB;

/**
@brief �~�b�V�����ł̏������`����֐�
@return �Ȃ�
@note
 �C�x���g��eEVENT::MISSION_RUN��eEVENT::MISSION_REPLAY_RUN�̂Ƃ����s�����
**/
void NyaUser::Run(eEVENT check_event)
{
	switch (check_event)
	{
	case eEVENT::MISSION_RUN:
	case eEVENT::MISSION_REPLAY_RUN:
		Act();
		Draw();
		break;
	case eEVENT::MISSION_CLEAR:
	case eEVENT::MISSION_COMPLETE:
	case eEVENT::MISSION_REPLAY_END:
	case eEVENT::MISSION_REPLAY_CLEAR:
	case eEVENT::MISSION_REPLAY_COMPLETE:
		Draw();
		break;
	}
}
