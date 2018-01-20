#include <tuple>
#include "NyaDesign.h"
#include "NyaInput.h"
#include "NyaString.h"

using namespace H2NLIB;

int NyaDesign::user_exp_;
int NyaDesign::user_lv_;
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

	// èâä˙âªÇ∑ÇÈÇÃÇÕ1âÒÇæÇØ
	if (first_call) {
		user_exp_ = 0;
		user_lv_ = 123;
		skill_name_[0] = "Skill Z";
		skill_name_[1] = "Skill X";
		skill_name_[2] = "Skill C";
		skill_name_[3] = "Skill V";
		skill_select_ = 0;
		NyaString::SettingFont("design_exp_font", 18, 2);
		NyaString::SettingFont("design_lv_font", 60, 6);
		NyaString::SettingFont("design_skill_font", 30, 2);
		NyaString::SettingFont("design_input_font", 50, 2);
		first_call = false;
	}
}


NyaDesign::~NyaDesign()
{

}

void NyaDesign::AddEXP(int x)
{
	user_exp_ += x;
	skill_exp_[skill_select_] += x;
}

void NyaDesign::Run(void)
{
	DrawSkill(875, 110);
	DrawLv(875, 515);
	DrawInput(875, 600);
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

	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::Q))
		NyaString::Write("design_input_font", red, x, y, "Å°");
	NyaString::Write("design_input_font", white, x, y, "Å†");
	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::W))
		NyaString::Write("design_input_font", red, x + 50, y, "Å°");
	NyaString::Write("design_input_font", white, x + 50, y, "Å†");
	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::E))
		NyaString::Write("design_input_font", red, x + 100, y, "Å°");
	NyaString::Write("design_input_font", white, x + 100, y, "Å†");
	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::R))
		NyaString::Write("design_input_font", red, x + 150, y, "Å°");
	NyaString::Write("design_input_font", white, x + 150, y, "Å†");
	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::SPACE))
		NyaString::Write("design_input_font", red, x + 200, y, "Å°");
	NyaString::Write("design_input_font", white, x + 200, y, "Å†");

	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::UP))
		NyaString::Write("design_input_font", red, x + 275, y -120, "Å°");
	NyaString::Write("design_input_font", white, x + 275, y - 120, "Å†");
	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::RIGHT))
		NyaString::Write("design_input_font", red, x + 325, y - 70, "Å°");
	NyaString::Write("design_input_font", white, x + 325, y - 70, "Å†");
	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::DOWN))
		NyaString::Write("design_input_font", red, x + 275, y - 20, "Å°");
	NyaString::Write("design_input_font", white, x + 275, y -20, "Å†");
	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::LEFT))
		NyaString::Write("design_input_font", red, x + 225, y - 70, "Å°");
	NyaString::Write("design_input_font", white, x + 225, y - 70, "Å†");
}

void NyaDesign::DrawLv(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	NyaString::Write("design_lv_font", white, x, y, "Lv.%d", user_lv_);
}

void NyaDesign::DrawSkill(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (int i = 0; i < 4; i++) {
		NyaString::Write("design_skill_font", white, x, y + 90 * i, "Åô");
		NyaString::Write("design_skill_font", white, x + 50, y + 90 * i, skill_name_[i]);
	}
	for (int i = 0; i < 4; i++) {
		NyaString::Write("design_skill_font", white, x, y + 90 * i + 45, "Å†Å†Å†Å†");
		NyaString::Write("design_exp_font", white, x + 150, y + 90 * i + 40, "Exp : %d pt", skill_exp_[i]);
		NyaString::Write("design_exp_font", white, x + 150, y + 90 * i + 60, "Next: %d pt", skill_exp_next_[i][0]);
	}
}

