#include "NyaDesign.h"
#include "TeemoDesign.h"


using namespace H2NLIB;

// no bug

TeemoDesign::TeemoDesign()
{
	nya_design_ = new NyaDesign;
}


TeemoDesign::~TeemoDesign()
{
	delete nya_design_;
}

void TeemoDesign::Create(void)
{
	nya_design_->SetSkillName(0, "Skill Z (power)");
	nya_design_->SetSkillName(1, "Skill X (bit)");
	nya_design_->SetSkillName(2, "Skill C (bomb)");
	nya_design_->SetSkillName(3, "Skill V (wave)");
}