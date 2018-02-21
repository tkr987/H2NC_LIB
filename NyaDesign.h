#pragma once

#include <string>
#include <vector>
#include <utility>
#include "NyaDefine.h"


namespace H2NLIB {

	class NyaTarget;
	class NyaUser;

	class NyaDesign {
	public:
		NyaDesign();
		~NyaDesign();
		void AddEXP(int);
		ePROCESS::NUM GetProcess(void);
		void Run(void);
		void SetProcess(ePROCESS::NUM);
		void SetSkillName(int, std::string);
		void SetSkillSelect(int);
		unsigned int GetSkillSelect(void) { return skill_select_; }
	private:
		static int count_mission_frame_;
		static int user_exp_;
		static int user_lv_;
		static int skill_exp_[4];
		static int skill_exp_next_[4][4];
		static unsigned int skill_lv_[4];
		static unsigned int skill_select_;
		static ePROCESS::NUM process_;
		static std::string skill_name_[4];
		void DrawBlack(int x, int y, int x2, int y2);
		void DrawLv(int x, int y);
		void DrawSkill(int x, int y);
		void DrawInput(int x, int y);
		void UpdateFPS(int x, int y);

	};

}

