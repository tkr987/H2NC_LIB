#pragma once

#include <string>
using namespace std;



namespace H2NLIB {

	class NyaString;

	class NyaDesign {
	private:
		unsigned int user_exp_;
		unsigned int user_lv_;
		unsigned int skill_exp_[4];
		unsigned int skill_lv_[4];
		string skill_name_[4];
		unsigned int skill_select_;
		NyaString* nya_string_;
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

