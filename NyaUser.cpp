#include "NyaUser.h"
using namespace HNLIB;

/**
@brief ミッションでの処理を定義する関数
@return なし
@note
 イベントがeEVENT::MISSION_RUNやeEVENT::MISSION_REPLAY_RUNのとき実行される
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
	}
}
