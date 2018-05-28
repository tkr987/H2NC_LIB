#include "NyaEnum.h"
#include "NyaInput.h"
#include "NyaUser.h"

using namespace H2NLIB;


/**
@brief 実行関数
@note
 ライブラリのNyaWindowクラス内で自動的に呼ばれるので、ライブラリ使用者が呼ぶ必要はない。
**/
void NyaUser::Run(const eEVENT check_event)
{
	// (init) -> create -> run ->
	// run -> (clear) -> (delete) -> create -> run -> (clear) -> (delete) -> 
	// run -> (continue) yes -> init ->
	// run -> (continue) no -> (finalize) ->

	switch (check_event)
	{
	case eEVENT::MISSION_INITIALIZE:
		MissionInitialize();
		break;
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
	case eEVENT::MISSION_FINALIZE:
		MissionFinalize();
		break;
	}
}

