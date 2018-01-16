#pragma once

#include <string>
using namespace std;


namespace H2NLIB {

	class NyaInput;
	class NyaString;

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
		static unsigned int user_exp_;
		static unsigned int user_lv_;
		static int skill_exp_[4];
		static int skill_exp_next_[4][4];
		static unsigned int skill_lv_[4];
		static unsigned int skill_select_;
		static string skill_name_[4];
		NyaString* nya_string_;
		NyaInput* nya_input_;
		void DrawSkill(int, int);
		void DrawInput(int, int);
	};

}

