#pragma once

#include <string>
#include <vector>
#include <utility>
#include "NyaDefine.h"


namespace H2NLIB
{
	class NyaSound;

	struct DesignUserInfo
	{
		int exp_;
		int exp_next_;
		int lv_;
	};

	struct DesignSkillInfo
	{
		int exp_;
		int exp_next_[4];
		int lv_;
		bool select_;
		std::string name_;
	};

	struct DesignWarningString
	{
		int draw_start_frame_;
		int draw_end_frame_;
		int grid_x_;
		int grid_y_;
	};

	class NyaDesign {
	public:
		NyaDesign();
		~NyaDesign();
		void AddEXP(int);
		void Run(void);
		void Warning(int grid_x, int grid_y, int draw_time_sec);
		void SetProcess(ePROCESS::NUM set_process) { process_ = set_process; }
		void SetSkillName(eSKILL::NUM skill, std::string set_name) { skill_info_[skill].name_ = set_name; }
		ePROCESS::NUM GetProcess(void) { return process_; }
	private:
		NyaSound* nya_sound_;
		static int count_mission_frame_;
		static ePROCESS::NUM process_;
		static DesignSkillInfo skill_info_[4];
		static DesignUserInfo user_info_;
		static std::pair<bool, int> warning_sound_pair_;
		static std::pair<bool, DesignWarningString> warning_string_pair_;
		void DrawBlack(int x, int y, int x2, int y2);
		void DrawLv(int x, int y);
		void DrawSkill(int x, int y);
		void DrawInput(int x, int y);
		void DrawWarning(void);
		void UpdateFPS(int x, int y);

	};

}

