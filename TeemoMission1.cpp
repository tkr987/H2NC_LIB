#include "NyaDesign.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx.h"

using namespace H2NLIB;

void TeemoMission1::Load(void) 
{
	NyaDesign* nya_design_ = new NyaDesign;
	NyaTarget* teemo_target = new TeemoTarget;
	//NyaTarget* teemo_target_ex = new TeemoTargetEx;

	AddChTarget(1, 30, teemo_target);
	//AddChTarget(60, 6000, teemo_target_ex);
	LoadBack("img/back1.png", 0, -2560 + 720, 2560 - 720, 180);

	nya_design_->SetSkillName(eSKILL::NUM::Q, "Skill Q (power)");
	nya_design_->SetSkillName(eSKILL::NUM::W, "Skill W (wave)");
	nya_design_->SetSkillName(eSKILL::NUM::E, "Skill E (bit)");
	nya_design_->SetSkillName(eSKILL::NUM::R, "Skill R (bomb)");

	delete nya_design_;
}

