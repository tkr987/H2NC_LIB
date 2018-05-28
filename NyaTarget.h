#pragma once


namespace H2NLIB 
{
	enum class eEVENT;

	//****************************************************************************************
	// class NyaTarget
	// �����Ă��̏ꍇ�AMissionCreate(), MissionRun()�͕K�{�Ȃ̂ŏ������z�֐��ɂȂ��Ă���B
	// ���̉��z�֐��͕K�v�ɉ����Ē�`���邱�ƁB
	//****************************************************************************************
	class NyaTarget {
	public:
		NyaTarget(){}
		virtual ~NyaTarget(){}
		virtual void MissionClear(void){}
		virtual void MissionContinue(void){}
		virtual void MissionCreate(void) = 0;
		virtual void MissionDelete(void){}
		virtual void MissionRun(void) = 0;
		void Run(eEVENT check_event);
	};
}

