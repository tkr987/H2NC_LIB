#pragma once
#include "NyaEnum.h"

namespace H2NLIB {

	//*************************************************************************
	// class NyaUser
	// �����Ă��̏ꍇ�ACreate(),Run()�͕K�{�Ȃ̂ŏ������z�֐��ɂȂ��Ă���B
	// ���̉��z�֐��͕K�v�ɉ����Ē�`���邱�ƁB
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