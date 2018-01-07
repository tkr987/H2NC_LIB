#include "NyaDesign.h"
#include "NyaString.h"

using namespace H2NLIB;

NyaDesign::NyaDesign()
{
	unsigned int user_exp_ = 0;
	unsigned int user_lv_ = 0;
	unsigned int skill_exp_[4] = {};
	unsigned int skill_lv_[4] = {};
	unsigned int skill_select_ = 0;
	nya_string_ = new NyaString();
	nya_string_->Init("design_font", 40, 2);
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
	nya_string_->Write("design_font", 100, 100, "Åô");
}

void NyaDesign::SetSkillSelect(int n)
{
	skill_select_ = n;
}

void NyaDesign::SetSkillName(int n, string name)
{
	skill_name_[n] = name;
}

