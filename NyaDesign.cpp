#include "NyaDesign.h"
#include "NyaString.h"

using namespace H2NLIB;

unsigned int NyaDesign::user_exp_;
unsigned int NyaDesign::user_lv_;
int NyaDesign::skill_exp_[4] = {};
int NyaDesign::skill_exp_next_[4][4] = {
	{2147483647, 2147483647, 2147483647, 2147483647},
	{2147483647, 2147483647, 2147483647, 2147483647},
	{2147483647, 2147483647, 2147483647, 2147483647},
	{2147483647, 2147483647, 2147483647, 2147483647},
};
unsigned int NyaDesign::skill_lv_[4] = {};
string NyaDesign::skill_name_[4];
unsigned int NyaDesign::skill_select_;
NyaString* NyaDesign::nya_string_exp_;
NyaString* NyaDesign::nya_string_skill_;

// no bug

NyaDesign::NyaDesign()
{
	static bool first_call = true;


	nya_string_exp_ = new NyaString();
	nya_string_skill_ = new NyaString();

	// ‰Šú‰»‚·‚é‚Ì‚Í1‰ñ‚¾‚¯
	if (first_call) {
		user_exp_ = 0;
		user_lv_ = 0;
		skill_name_[0] = "Skill Z";
		skill_name_[1] = "Skill X";
		skill_name_[2] = "Skill C";
		skill_name_[3] = "Skill V";
		skill_select_ = 0;
		nya_string_exp_->Init("design_exp_font", 18, 2);
		nya_string_skill_->Init("design_skill_font", 30, 2);
		first_call = false;
	}
}


NyaDesign::~NyaDesign()
{
	delete nya_string_exp_;
	delete nya_string_skill_;
}

void NyaDesign::DrawSkill(int x, int y)
{

	for (int i = 0; i < 4; i++) {
		nya_string_skill_->Write("design_skill_font", x, y + 90 * i, "™");
		nya_string_skill_->Write("design_skill_font", x + 50, y + 90 * i, skill_name_[i]);
	}
	for (int i = 0; i < 4; i++) {
		nya_string_skill_->Write("design_skill_font", x, y + 90 * i + 45, "    ");
		nya_string_exp_->Write("design_exp_font", x + 150, y + 90 * i + 40, "Exp : %d pt", skill_exp_[i]);
		nya_string_exp_->Write("design_exp_font", x + 150, y + 90 * i + 60, "Next: %d pt", skill_exp_next_[i][0]);
	}

}

void NyaDesign::AddEXP(int x)
{
	user_exp_ += x;
	skill_exp_[skill_select_] += x;
}

void NyaDesign::Run(void)
{
	DrawSkill(800, 100);
}

void NyaDesign::SetSkillSelect(int n)
{
	skill_select_ = n;
}

void NyaDesign::SetSkillName(int x, string name)
{
	skill_name_[x] = name;
}

