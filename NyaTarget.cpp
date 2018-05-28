#include "NyaEnum.h"
#include "NyaTarget.h"

using namespace H2NLIB;

/**
@brief 実行関数
@note
 ライブラリのNyaWindowクラス内で自動的に呼ばれるので、ライブラリ使用者が呼ぶ必要はない。
**/
void NyaTarget::Run(eEVENT check_event)
{
	switch (check_event)
	{
	case eEVENT::MISSION_CREATE:
		MissionCreate();
		break;
	case eEVENT::MISSION_RUN:
		MissionRun();
		break;
	case eEVENT::MISSION_CONTINUE:
		MissionContinue();
		break;
	case eEVENT::MISSION_CLEAR:
		MissionClear();
		break;
	case eEVENT::MISSION_DELETE:
		MissionDelete();
		break;
	}
}

