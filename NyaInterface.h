#pragma once

#include <array>
#include <limits>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include "NyaEnum.h"


namespace HNLIB
{
	class SoundPropertyX;

	/**
	@brief mission clear ����N���X
	@note
	 �ϐ�valid_��true�ɂ����mission complete��\������
	**/
	class InterfaceHandleClear
	{
	public:
		bool valid_;		//!< clear��ʕ\���̗L����
		void Clear();
	};

	/**
	@brief mission complete ����N���X
	@note
	 �ϐ�valid_��true�ɂ����mission complete��\������
	**/
	class InterfaceHandleComplete
	{
	public:
		bool valid_;		//!< complete��ʕ\���̗L����
		void Clear();
	};

	/**
	@brief continue ����N���X
	@note
	 ���C�u�����g�p�҂�valid_��recovery_�ȊO�̃����o�ϐ����g���K�v�͂Ȃ��B
	 - recovery_:
	 �l��ݒ肷��ƃR���e�j���[��ʂ���߂����Ƃ����C�t���ɔ��f�����B
	 �f�t�H���g�ł͒l1�ɐݒ肳��Ă���B
	 - valid_:
	 true�ɂ���ƃR���e�j���[��ʂ�\������B
	 [enter]�L�[�őI������ƃR���e�j���[��ʂ͎����I�ɕ�����B
	 - cnum_:
	 0�Ȃ�MISSION_COMPLETE���Ƀ��v���C���Z�[�u����C�x���g�Ɉڍs�B
	 0�ȊO�Ȃ�MISSION_COMPLETE���Ƀ��v���C���Z�[�u���Ȃ��B
	 �R���e�j���[��ʂɕ\�������I������2�Ȃ̂ŁA�����o�ϐ�select_�̒l��[0,1]�̂݁B
	 �����oselect_�̒l��[0,1]�ȊO�ɂ���ƑI���ł��Ȃ��Ȃ�B
	**/
	class InterfaceHandleContinue
	{
	public:
		unsigned int cnum_;				//!< continue��
		unsigned int recovery_;			//!< continue����߂����Ƃ��̃��C�t��
		int select_;					//!< continue��ʂŌ��ݑI�����Ă��鍀��
		bool valid_;					//!< continue��ʕ\���̗L����
		void Clear();
	};

	/**
	@brief replay end ����N���X
	@note
	 �ϐ�valid_��true�ɂ����replay end��\������
	**/
	class InterfaceHandleEnd
	{
	public:
		bool valid_;		//!< replay end ��ʕ\���̗L����
		void Clear();
	};

	class InterfaceHandleHealth
	{
	public:
		bool valid_;
		double value_;
		void Clear();
	};

	/**
	@brief ���C�t����N���X
	@note
	 �����ovalue_�ɂ�[0-8]�̒l��ݒ肷�邱�Ƃ��ł���B
	 0�����̒l��ݒ肵���Ƃ��͎��t���[���܂ł�0�̒l�Ɏ����I�ɕύX�����B
	 9�ȏ�̒l��ݒ肵���Ƃ��͎��t���[���܂ł�8�̒l�Ɏ����I�ɕύX�����B
	**/
	class InterfaceHandleLife
	{
	public:
		int value_;		//!< ���C�t��
	};

	class InterfaceHandleSkill
	{
	public:
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv1_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv2_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv3_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv4_exp_;
		std::array<std::string, static_cast<int>(eSKILL::sizeof_enum)> name_;
		eSKILL select_;									// ���ݑI�����Ă���X�L��
		InterfaceHandleSkill();
		void AddExp(unsigned int value);
		void Clear(void);
	};

	class InterfaceHandleWarning
	{
	public:
		unsigned int draw_frame_;
		unsigned int draw_frame_max_;
		int draw_grid_x_;
		int draw_grid_y_;
		bool draw_valid_;
		SoundPropertyX* spx_;
		bool sound_valid_;
		void LoadSound(std::string file_pass, unsigned int volume = 100);
		void DeleteSound(void);
		InterfaceHandleWarning();
		~InterfaceHandleWarning();
	};



	class InterfaceHandleTitle
	{
	public:
		std::stringstream name_;
		InterfaceHandleTitle();
	};


	class NyaInterface {
	public:
		NyaInterface();
		~NyaInterface();
		static void Init(void);
		static void Run(eEVENT event_check);
		static InterfaceHandleClear* GetHandleClear(void) { return &handle_clear_; }
		static InterfaceHandleComplete* GetHandleComplete(void) { return &handle_complete_; }
		static InterfaceHandleContinue* GetHandleContinue(void) { return &handle_continue_; }
		static InterfaceHandleEnd* GetHandleEnd(void) { return &handle_end_; }
		static InterfaceHandleHealth* GetHandleHealth (void) { return &handle_health_; }
		static InterfaceHandleLife* GetHandleLife(void) { return &handle_life_; }
		static InterfaceHandleSkill* GetHandleSkill(void) { return &handle_skill_; }
		static InterfaceHandleTitle* GetHandleTitle(void) { return &handle_title_; }
		static InterfaceHandleWarning* GetHandleWarning(void) { return &handle_warning_; }
	private:
		static InterfaceHandleClear handle_clear_;
		static InterfaceHandleComplete handle_complete_;
		static InterfaceHandleContinue handle_continue_;
		static InterfaceHandleEnd handle_end_;
		static InterfaceHandleHealth handle_health_;
		static InterfaceHandleLife handle_life_;
		static InterfaceHandleSkill handle_skill_;
		static InterfaceHandleTitle handle_title_;
		static InterfaceHandleWarning handle_warning_;
		static void DrawBlack(int x, int y, int x2, int y2);
		static void DrawClear(int x, int y);
		static void DrawComplete(int x, int y);
		static void DrawContinue(int x, int y, eEVENT event_check);
		static void DrawEnd(int x, int y);
		static void DrawLIB(int x, int y);
		static void DrawHealth(void);
		static void DrawTitle(int x, int y);
		static void DrawInput(int x, int y);
		static void DrawLife(int x, int y);
		static void DrawSkill(int x, int y);
		static void DrawWarning(void);
	};

}

