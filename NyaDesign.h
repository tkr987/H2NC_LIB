#pragma once

#include <string>
#include <vector>
#include <utility>
#include "NyaDefine.h"


namespace H2NLIB
{
	class NyaSound;
	class SoundProperty;

	class DesignHandleMissionClear
	{
	public:
		int draw_grid_x_;
		int draw_grid_y_;
		bool valid_;
		DesignHandleMissionClear() { Init(); }
		void Init(void)
		{
			draw_grid_x_ = 225;
			draw_grid_y_ = 200;
			valid_ = false;
		}
	};

	struct DesignHandleMissionEx
	{
	public:
		bool valid_;
		double value_;
		DesignHandleMissionEx() { Init(); }
		void Init(void)
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
		unsigned int draw_time_frame_;
		unsigned int draw_time_max_frame_;
		bool draw_valid_;
		bool sound_valid_;
		SoundProperty* sp_;
		DesignHandleMissionWarning();
		~DesignHandleMissionWarning();
		void Init(void)
		{
			draw_grid_x_ = 225;
			draw_grid_y_ = 200;
			draw_time_frame_ = 0;
			draw_time_max_frame_ = 300;
			draw_valid_ = false;
			sound_valid_ = false;
		}
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
		void Init(void);
		void Run(void);
		void SetSkillName(eSKILL skill, std::string set_name) { skill_info_[static_cast<int>(skill)].name_ = set_name; }
	private:
		NyaSound* nya_sound_;
		static unsigned int count_;
		static DesignHandleMissionClear handle_mission_clear_;
		static DesignHandleMissionEx handle_mission_ex_;
		static DesignHandleMissionWarning handle_mission_warning_;
		static int instance_;
		static DesignSkillInfo skill_info_[static_cast<int>(eSKILL::sizeof_enum)];
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

