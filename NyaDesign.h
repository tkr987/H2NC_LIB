#pragma once

#include <string>
using namespace std;


namespace H2NLIB {

	class NyaDesign {
	public:
		NyaDesign();
		~NyaDesign();
		void AddEXP(int);
		void Run(void);
		void SetSkillName(int, string);
		void SetSkillSelect(int);
		unsigned int GetSkillSelect(void) { return skill_select_; }
	private:
		static int user_exp_;
		static int user_lv_;
		static int skill_exp_[4];
		static int skill_exp_next_[4][4];
		static unsigned int skill_lv_[4];
		static unsigned int skill_select_;
		static string skill_name_[4];
		void DrawBlack(int x, int y);
		void DrawLv(int x, int y);
		void DrawSkill(int x, int y);
		void DrawInput(int x, int y);
		void UpdateFPS(int x, int y);
	};

}

