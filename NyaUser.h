#pragma once
#include "NyaEnum.h"

namespace H2NLIB {

	//*************************************************************************
	// class NyaUser
	// �����Ă��̏ꍇ�AMissionRun()�͕K�{�Ȃ̂ŏ������z�֐��ɂȂ��Ă���B
	// ���̉��z�֐��͕K�v�ɉ����Ē�`���邱�ƁB
	//*************************************************************************
	class NyaUser {
	public:
		NyaUser(){}
		virtual ~NyaUser(){}
		void Run(const eEVENT check_event);
		virtual void MissionClear(void){}
		virtual void MissionContinue(void){}
		/**
		 @brief �C�x���gMISSION_RUN�ł̏������`����֐�
		**/
		virtual void MissionRun(void) = 0;
	};

}