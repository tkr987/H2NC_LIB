#include <tuple>
#include "NyaDesign.h"
#include "NyaInput.h"
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


NyaDesign::NyaDesign()
{
	static bool first_call = true;


	nya_string_ = new NyaString();
	nya_input_ = new NyaInput();

	// èâä˙âªÇ∑ÇÈÇÃÇÕ1âÒÇæÇØ
	if (first_call) {
		user_exp_ = 0;
		user_lv_ = 0;
		skill_name_[0] = "Skill Z";
		skill_name_[1] = "Skill X";
		skill_name_[2] = "Skill C";
		skill_name_[3] = "Skill V";
		skill_select_ = 0;
		nya_string_->SetFont("design_exp_font", 18, 2);
		nya_string_->SetFont("design_skill_font", 30, 2);
		nya_string_->SetFont("design_input_font", 50, 2);
		first_call = false;
	}
}


NyaDesign::~NyaDesign()
{
	delete nya_string_;
}

void NyaDesign::AddEXP(int x)
{
	user_exp_ += x;
	skill_exp_[skill_select_] += x;
}

void NyaDesign::Run(void)
{
	DrawSkill(900, 100);
	DrawInput(900, 600);
}

void NyaDesign::SetSkillSelect(int n)
{
	skill_select_ = n;
}

void NyaDesign::SetSkillName(int x, string name)
{
	skill_name_[x] = name;
}

void NyaDesign::DrawInput(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);
	static tuple<int, int, int> red = make_tuple(255, 0, 0);

	if (nya_input_->GetKeyFlagNow(eINPUT::KEY::Q))
		nya_string_->Write("design_input_font", red, x, y, "Å°");
	nya_string_->Write("design_input_font", white, x, y, "Å†");
	if (nya_input_->GetKeyFlagNow(eINPUT::KEY::W))
		nya_string_->Write("design_input_font", red, x + 50, y, "Å°");
	nya_string_->Write("design_input_font", white, x + 50, y, "Å†");
	if (nya_input_->GetKeyFlagNow(eINPUT::KEY::E))
		nya_string_->Write("design_input_font", red, x + 100, y, "Å°");
	nya_string_->Write("design_input_font", white, x + 100, y, "Å†");
	if (nya_input_->GetKeyFlagNow(eINPUT::KEY::R))
		nya_string_->Write("design_input_font", red, x + 150, y, "Å°");
	nya_string_->Write("design_input_font", white, x + 150, y, "Å†");
}

void NyaDesign::DrawSkill(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (int i = 0; i < 4; i++) {
		nya_string_->Write("design_skill_font", white, x, y + 90 * i, "Åô");
		nya_string_->Write("design_skill_font", white, x + 50, y + 90 * i, skill_name_[i]);
	}
	for (int i = 0; i < 4; i++) {
		nya_string_->Write("design_skill_font", white, x, y + 90 * i + 45, "Å†Å†Å†Å†");
		nya_string_->Write("design_exp_font", white, x + 150, y + 90 * i + 40, "Exp : %d pt", skill_exp_[i]);
		nya_string_->Write("design_exp_font", white, x + 150, y + 90 * i + 60, "Next: %d pt", skill_exp_next_[i][0]);
	}
}

