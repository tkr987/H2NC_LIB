#include "NyaDesign.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"

using namespace H2NLIB;


void TeemoMission1::Load(void) 
{
	NyaDesign* nya_design_ = new NyaDesign;
	NyaTarget* teemo_target = new TeemoTarget;

	AddChTarget(1, teemo_target);

	nya_design_->SetSkillName(0, "Skill Q (power)");
	nya_design_->SetSkillName(1, "Skill W (wave)");
	nya_design_->SetSkillName(2, "Skill E (bit)");
	nya_design_->SetSkillName(3, "Skill R (bomb)");

	delete nya_design_;
}

