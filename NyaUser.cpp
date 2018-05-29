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
		MissionRun();
		break;
	case eEVENT::MISSION_CONTINUE:
		MissionContinue();
		break;
	case eEVENT::MISSION_CLEAR:
		MissionClear();
		break;
	}
}

