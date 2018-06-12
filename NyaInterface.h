#pragma once

#include <limits>
#include <string>
#include <vector>
#include <utility>
#include "NyaEnum.h"


namespace H2NLIB
{
	class SoundProperty;

	class InterfaceHandleMissionAllClear
	{
	public:
		int draw_grid_x_;
		int draw_grid_y_;
		bool valid_;						// trueならmission all clearと表示する
		InterfaceHandleMissionAllClear();
	};

	class InterfaceHandleMissionClear
	{
	public:
		int draw_grid_x_;
		int draw_grid_y_;
		bool valid_;						// trueならmission clearと表示する
		InterfaceHandleMissionClear();
	};

	class InterfaceHandleMissionEx
	{
	public:
		bool valid_;
		double value_;
		InterfaceHandleMissionEx();
	};

	class InterfaceHandleMissionWarning
	{
	public:
		int draw_grid_x_;
		int draw_grid_y_;
		unsigned int draw_time_frame_;
		unsigned int draw_time_max_frame_;
		bool draw_valid_;
		bool sound_valid_;
		SoundProperty* sp_;
		InterfaceHandleMissionWarning();
		~InterfaceHandleMissionWarning();
	};

	class DesignUserInfo
	{
	public:
		int exp_;
		int exp_next_;
		int lv_;
		DesignUserInfo() { Init(); }
		void Init(void)
		{
			exp_ = 0;
			exp_next_ = 2147483647;
			lv_ = 123;
		}
	};



	//*****************************************************
	// class SkillInterface
	// このクラスをn個用意するとn個のスキルを管理できる
	//*****************************************************
	class SkillInterface
	{
	public:
		unsigned int exp_;
		unsigned int lv_;
		std::string name_;
		unsigned int next_lv_exp_[INTERFACE_SKILL_MAX_LV];
		bool select_;		// falseなら他のスキルが選択されている
		SkillInterface()
		{
			exp_ = 0;
			lv_ = 0;
			for (int i = 0; i < INTERFACE_SKILL_MAX_LV; i++)
				next_lv_exp_[i] = UINT_MAX;
			select_ = false;
		}
	};

	class NyaInterface {
	public:
		NyaInterface();
		~NyaInterface();
		static void AddEXP(int);
		static void Init(void);
		static void Run(void);
		static InterfaceHandleMissionClear* GetHandleMissionClear(void)
		{
			return &handle_mission_clear_;
		}
		static InterfaceHandleMissionAllClear* GetHandleMissionAllClear(void)
		{
			return &handle_mission_all_clear_;
		}
		static InterfaceHandleMissionEx* GetHandleMissionEx(void)
		{
			return &handle_mission_ex_;
		}
		static InterfaceHandleMissionWarning* GetHandleMissionWarning(void)
		{ 
			return &handle_mission_warning_;
		}
		/**
		 @brief スキル名を設定する関数
		 @brief skill 設定するスキル
		 @brief set_name 設定するスキル名
		**/
		static void SetSkillName(eSKILL skill, std::string set_name) 
		{ 
			skill_collection_[static_cast<int>(skill)].name_ = set_name; 
		}
		/**
		 @brief レベルに到達するのに必要な経験値を設定する関数
		 @brief skill 経験値を設定するスキル
		 @brief lv 経験値を設定するレベル
		 @brief next_exp 必要な経験値
		 @note
		  skillがlvに到達するために必要な経験値をnext_expとして設定する
		**/
		static void SetSkillNextExp(eSKILL skill, unsigned int lv, unsigned int next_exp) 
		{ 
			skill_collection_[static_cast<int>(skill)].next_lv_exp_[lv] = next_exp; 
		}
	private:
		static unsigned int count_frame_;
		static InterfaceHandleMissionAllClear handle_mission_all_clear_;
		static InterfaceHandleMissionClear handle_mission_clear_;
		static InterfaceHandleMissionEx handle_mission_ex_;
		static InterfaceHandleMissionWarning handle_mission_warning_;
		static std::vector<SkillInterface> skill_collection_;
		static DesignUserInfo user_info_;
		static std::pair<bool, int> clear_pair_;
		static void DrawBlack(int x, int y, int x2, int y2);
		static void DrawLIB(int x, int y);
		static void DrawSkill(int x, int y);
		static void DrawInput(int x, int y);
		static void DrawMissionAllClear(void);
		static void DrawMissionClear(void);
		static void DrawMissionEx(void);
		static void DrawMissionWarning(void);
	};

}

