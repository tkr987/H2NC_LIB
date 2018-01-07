#pragma once

#include <string>
using namespace std;

// no bug

namespace H2NLIB {

	class NyaString;

	class NyaDesign {
	private:
		static unsigned int user_exp_;
		static unsigned int user_lv_;
		static unsigned int skill_exp_[4];
		static unsigned int skill_lv_[4];
		static string skill_name_[4];
		static unsigned int skill_select_;
		static NyaString* nya_string_;
		void DrawSkill(int, int);
	public:
		NyaDesign();
		~NyaDesign();
		void AddEXP(int);
		void Run(void);
		void SetSkillName(int, string);
		void SetSkillSelect(int);
		unsigned int GetSkillSelect(void) { return skill_select_; }
	};

}

