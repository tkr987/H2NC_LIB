#pragma once

#include <string>
#include <vector>
#include <utility>
#include "NyaDefine.h"


namespace H2NLIB
{
	class NyaSound;
	class SoundPropertyX;

	class DesignHandleMissionClear
	{
	public:
		int draw_grid_x_;
		int draw_grid_y_;
		bool valid_;
		DesignHandleMissionClear()
		{
			draw_grid_x_ = 200;
			draw_grid_y_ = 200;
			valid_ = false;
		}
	};

	struct DesignHandleMissionEx
	{
	public:
		bool valid_;
		double value_;
		DesignHandleMissionEx()
		{
			valid_ = false;
			value_ = 100;
		}
	};

	class DesignHandleMissionWarning
	{
	public:
		int draw_grid_x_;
		int draw_grid_y_;
		SoundPropertyX* spx_;
		unsigned int time_frame_;
		bool valid_;
		DesignHandleMissionWarning()
		{
			draw_grid_x_ = 200;
			draw_grid_y_ = 200;
			spx_ = nullptr;
			time_frame_ = 0;
			valid_ = false;
		}
	};

	class DesignUserInfo
	{
	public:
		int exp_;
		int exp_next_;
		int lv_;
		DesignUserInfo()
		{
			exp_ = 0;
			exp_next_ = 2147483647;
			lv_ = 123;
		}
	};

	struct DesignSkillInfo
	{
		int exp_;
		int exp_next_[4];
		int lv_;
		bool select_;
		std::string name_;
	};

	class NyaDesign {
	public:
		NyaDesign();
		~NyaDesign();
		void AddEXP(int);
		DesignHandleMissionClear* GetHandleMissionClear(void) { return &handle_mission_clear_; }
		DesignHandleMissionEx* GetHandleMissionEx(void) { return &handle_mission_ex_; }
		DesignHandleMissionWarning* GetHandleMissionWarning(void) { return &handle_mission_warning_; }
		void Run(void);
		void SetSkillName(eSKILL::NUM skill, std::string set_name) { skill_info_[skill].name_ = set_name; }
	private:
		NyaSound* nya_sound_;
		static unsigned int count_;
		static DesignHandleMissionClear handle_mission_clear_;
		static DesignHandleMissionEx handle_mission_ex_;
		static DesignHandleMissionWarning handle_mission_warning_;
		static int instance_;
		static DesignSkillInfo skill_info_[4];
		static DesignUserInfo user_info_;
		static std::pair<bool, int> clear_pair_;
		void DrawBlack(int x, int y, int x2, int y2);
		void DrawLv(int x, int y);
		void DrawSkill(int x, int y);
		void DrawInput(int x, int y);
		void DrawMissionClear(void);
		void DrawMissionEx(void);
		void DrawMissionWarning(void);
	};

}

