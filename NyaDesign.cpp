#include "NyaDesign.h"
#include "NyaString.h"

using namespace H2NLIB;

unsigned int NyaDesign::user_exp_;
unsigned int NyaDesign::user_lv_;
unsigned int NyaDesign::skill_exp_[4];
unsigned int NyaDesign::skill_lv_[4];
string NyaDesign::skill_name_[4];
unsigned int NyaDesign::skill_select_;
NyaString* NyaDesign::nya_string_;

// no bug

NyaDesign::NyaDesign()
{
	static bool first_call = true;

	// インスタンス
	nya_string_ = new NyaString();


	if (first_call) {
		user_exp_ = 0;
		user_lv_ = 0;
		skill_exp_[4] = {};
		skill_lv_[4] = {};
		skill_name_[0] = "Skill Z";
		skill_name_[1] = "Skill X";
		skill_name_[2] = "Skill C";
		skill_name_[3] = "Skill V";
		skill_select_ = 0;
		nya_string_->Init("design_font", 40, 2);
		first_call = false;
	}
}


NyaDesign::~NyaDesign()
{
	delete nya_string_;
}

void NyaDesign::DrawSkill(int x, int y)
{

	for (int i = 0; i < 4; i++) {
		nya_string_->Write("design_font", x, y + 50 * (i+1), "☆");
		nya_string_->Write("design_font", x + 50, y + 50 * (i+1), skill_name_[i]);
	}

}

void NyaDesign::AddEXP(int x)
{
	user_exp_ += x;
	skill_exp_[skill_select_] += x;
}

void NyaDesign::Run(void)
{
	DrawSkill(100, 100);
}

void NyaDesign::SetSkillSelect(int n)
{
	skill_select_ = n;
}

void NyaDesign::SetSkillName(int x, string name)
{
	skill_name_[x] = name;
}

