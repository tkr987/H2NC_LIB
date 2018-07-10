#include "NyaEnum.h"
#include "NyaTarget.h"

using namespace HNLIB;

/**
@brief 実行関数
@note
 ライブラリのNyaWindowクラス内で自動的に呼ばれるので、ライブラリ使用者が呼ぶ必要はない。
**/
void NyaTarget::Run(eEVENT check_event)
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

