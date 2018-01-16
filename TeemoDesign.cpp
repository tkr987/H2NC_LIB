#include "NyaDesign.h"


using namespace H2NLIB;


void TeemoDesign() {
	NyaDesign* nya_design = new NyaDesign;

	nya_design->SetSkillName(0, "Skill Q (power)");
	nya_design->SetSkillName(1, "Skill W (wave)");
	nya_design->SetSkillName(2, "Skill E (bit)");
	nya_design->SetSkillName(3, "Skill R (bomb)");
	delete nya_design;
}