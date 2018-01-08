#include "NyaDesign.h"


using namespace H2NLIB;

// no bug

void TeemoDesign() {
	NyaDesign* nya_design = new NyaDesign;

	nya_design->SetSkillName(0, "Skill Z (power)");
	nya_design->SetSkillName(1, "Skill X (bit)");
	nya_design->SetSkillName(2, "Skill C (bomb)");
	nya_design->SetSkillName(3, "Skill V (wave)");
	delete nya_design;
}