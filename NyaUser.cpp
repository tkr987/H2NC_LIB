#include "NyaEnum.h"
#include "NyaInput.h"
#include "NyaUser.h"

using namespace H2NLIB;


/**
@brief 実行関数
@note
 ライブラリのNyaMissionクラス内で自動的に呼ばれるので、ライブラリ使用者が呼ぶ必要はない
**/
void NyaUser::Run(const eEVENT check_event)
{

	switch (check_event)
	{
	case eEVENT::MISSION_RUN:
	case eEVENT::MISSION_REPLAY_RUN:
		MissionRun();
		break;
	case eEVENT::MISSION_CONTINUE:
		break;
	case eEVENT::MISSION_CLEAR:
	case eEVENT::MISSION_ALL_CLEAR:
	case eEVENT::MISSION_REPLAY_CLEAR:
	case eEVENT::MISSION_REPLAY_ALL_CLEAR:
		break;
	}
}

