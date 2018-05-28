#pragma once
#include "NyaEnum.h"

namespace H2NLIB {

	//*************************************************************************
	// class NyaUser
	// たいていの場合、Create(),Run()は必須なので純粋仮想関数になっている。
	// 他の仮想関数は必要に応じて定義すること。
	//*************************************************************************
	class NyaUser {
	public:
		NyaUser(){}
		virtual ~NyaUser(){}
		void Run(const eEVENT check_event);
		virtual void MissionClear(void){}
		virtual void MissionContinue(void){}
		virtual void MissionCreate(void) = 0;
		virtual void MissionDelete(void){}
		virtual void MissionInitialize(void){}
		virtual void MissionRun(void) = 0;
		virtual void MissionFinalize(void){}
	};

}