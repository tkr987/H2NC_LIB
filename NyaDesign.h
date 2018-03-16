#pragma once

#include <string>
#include <vector>
#include <utility>
#include "NyaDefine.h"


namespace H2NLIB
{
	class NyaSound;
	class SoundPropertyX;

	struct DesignExMode
	{
		bool flag_;
		double value_;
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

	class DesignWarning
	{
	public:
		int draw_frame_end_;
		int draw_frame_start_;
		bool sound_flag_;
		SoundPropertyX* spx_;
		DesignWarning()
		{
			draw_frame_end_ = -1;
			draw_frame_start_ = -1;
			sound_flag_ = false;
		}
	};

	class NyaDesign {
	public:
		NyaDesign();
		~NyaDesign();
		void AddEXP(int);
		void LoadWarningSound(std::string file_pass, int volume = 100);
		void Run(void);
		void Warning(int draw_time_sec);
		void ExMode(bool flag) { ex_mode_.flag_ = flag; }
		void SetExValue(double value) { ex_mode_.value_ = value; }
		void SetProcess(ePROCESS::NUM set_process) { process_ = set_process; }
		void SetSkillName(eSKILL::NUM skill, std::string set_name) { skill_info_[skill].name_ = set_name; }
		ePROCESS::NUM GetProcess(void) { return process_; }
	private:
		NyaSound* nya_sound_;
		static int count_;
		static DesignExMode ex_mode_;
		static int instance_;
		static DesignWarning warning_;
		static ePROCESS::NUM process_;
		static DesignSkillInfo skill_info_[4];
		static DesignUserInfo user_info_;
		static std::pair<bool, int> clear_pair_;
		void DrawBlack(int x, int y, int x2, int y2);
		void DrawLv(int x, int y);
		void DrawSkill(int x, int y);
		void DrawInput(int x, int y);
		void DrawMissionClear(int x, int y);
		void DrawMissionEx(void);
		void DrawMissionWarning(void);
		void UpdateFPS(int x, int y);

	};

}

