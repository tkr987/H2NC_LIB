#pragma once


#include <string>
#include <utility>
#include <vector>
#include "NyaEnum.h"


namespace H2NLIB
{
	class NyaBackground;
	class NyaTarget;
	class NyaUser;

	// ***************************************************************************************
	// class MissionTarget
	// NyaMission::AddChTarget()�œo�^���ꂽ���e���i�[���邽�߂ɐ錾���ꂽ�N���X
	// start_time��end_time���ۑ�����Ă���̂ŁANyaMission::Run()�ŏ������邱�Ƃ��ł���
	// ***************************************************************************************
	class MissionTarget
	{		
	public:
		unsigned int start_frame_;
		unsigned int end_frame_;
		NyaTarget* target_;
	};

	class NyaMission
	{
	public:
		NyaMission();
		virtual ~NyaMission();
		virtual void Create(void) = 0;		// eEVENT::MISSION_CLEATE�Ŏ��s�����
		virtual void Delete(void){}			// eEVENT::MISSION_DELETE�Ŏ��s�����
		void AddChild(NyaBackground* background);
		void AddChild(int start_time_sec, int end_time_sec, NyaTarget* target, unsigned int id);
		void AddChild(NyaUser* user);
		void DeleteBackground(void);
		void DeleteTarget(void);
		void DeleteUser(void);
		void Run(eEVENT check_event);
	private:
		// eEVENT::MISSION_RUN�̏�Ԃ̃t���[�������J�E���g����
		// UINT_MAX�𒴂���~�b�V�����͐��퓮�삵�Ȃ��̂Œ���
		unsigned int count_frame_;
		static NyaBackground* background_;
		static NyaUser* user_;
		static std::vector<MissionTarget*> mission_target_collection_;
	};

}
