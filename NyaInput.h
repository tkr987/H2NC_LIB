#pragma once

#include <deque>
#include <random>
#include <sstream>
#include <string>
#include "NyaEnum.h"

namespace H2NLIB {

	class NyaInput {
	public:
		static double AngleToRad(double x) 
		{ 
			return (x * 3.14159265359 / 180.0);
		}
		/**
		 @brief ���݂̃L�[��Ԃ��擾����֐�
		**/
		static bool GetKeyStateNow(eINPUT key)
		{ 
			return state_now_[static_cast<int>(key)];
		}
		/**
		 @brief 1�t���[���O�̃L�[��Ԃ��擾����֐�
		**/
		static bool GetKeyStatePre(eINPUT key) 
		{ 
			return state_pre_[static_cast<int>(key)];
		}
		/**
		 @brief int�^�̗������擾����֐�
		 @param min �ŏ��l
		 @param max �ő�l
		 @note
		  min����max�܂ł͈̔͂ŗ������擾����
		**/
		static int GetRand(int min, int max)
		{
			std::uniform_int_distribution<int> rand_dist(min, max);
			return rand_dist(mt_rand_);
		}
		/**
		 @brief double�^�̗������擾����֐�
		 @param min �ŏ��l
		 @param max �ő�l
		 @note
		  min����max�܂ł͈̔͂ŗ������擾����
		**/
		static double GetRand(double min, double max)
		{
			std::uniform_real_distribution<double> rand_dist(min, max);
			return rand_dist(mt_rand_);
		}
		/**
		 @brief �L�[�����������Ă����Ԃ��ǂ������ʂ���֐�
		**/
		static bool IsHoldKey(eINPUT key)
		{ 
			return (state_pre_[static_cast<int>(key)] == true && state_now_[static_cast<int>(key)] == true) ? true : false; 
		}
		/**
		 @brief �L�[�����������ǂ������ʂ���֐�
		**/
		static bool IsPressKey(eINPUT key)
		{ 
			return (state_pre_[static_cast<int>(key)] == false && state_now_[static_cast<int>(key)] == true) ? true : false; 
		}
		static double RadToAngle(double x)
		{
			return (x * 180.0 / 3.14159265359);
		}
		static void Init(void);
		static void InputReplay(std::string file_name);
		static void OutputReplay(std::string file_name);
		static void Run(const eEVENT check_event);
	private:
		static std::stringstream output_date_;
		static std::stringstream output_seed_;
		static std::stringstream output_title_;
		static std::mt19937 mt_rand_;
		static std::deque<int> save_state_collection_;
		static bool state_now_[static_cast<int>(eINPUT::sizeof_enum)];
		static bool state_pre_[static_cast<int>(eINPUT::sizeof_enum)];

	};

}

