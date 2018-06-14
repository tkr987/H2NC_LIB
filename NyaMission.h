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
		void AddChild(NyaBackground* background);
		void AddChild(int start_time_sec, int end_time_sec, NyaTarget* target, unsigned int id);
		void AddChild(NyaUser* user);
		void ClearBackground(void);
		void ClearTarget(void);
		void ClearUser(void);
		void Run(eEVENT check_event);
		/**
		 @brief �~�b�V�����쐬�C�x���g�Ŏ��s���鏈�����`����֐�
		 @note
		  eEVENT::MISSION_CREATE�Ŏ��s�����
		**/
		virtual void Create(void) = 0;
		/**
		 @brief �~�b�V�����폜�C�x���g�Ŏ��s���鏈�����`����֐�
		 @note
		  eEVENT::MISSION_DELETE�Ŏ��s�����
		  Delete()�̒�`�ŏ��������������Ȃ������ꍇ�A�O�̃~�b�V�����̃f�[�^�������p�����
		**/
		virtual void Delete(void) = 0;
	private:
		// eEVENT::MISSION_RUN�̏�Ԃ̃t���[�������J�E���g����
		// UINT_MAX�𒴂���~�b�V�����͐��퓮�삵�Ȃ��̂Œ���
		unsigned int count_frame_;
		static NyaBackground* background_;
		static NyaUser* user_;
		static std::vector<MissionTarget*> mission_target_collection_;
	};

}
