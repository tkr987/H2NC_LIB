#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx.h"

using namespace H2NLIB;

void TeemoMission1::Load(void) 
{
	NyaDesign* nya_design_ = new NyaDesign;
	NyaGraphic* nya_graphic_ = new NyaGraphic;
	NyaTarget* teemo_target = new TeemoTarget;
	//NyaTarget* teemo_target_ex = new TeemoTargetEx;

	// ターゲットを子オブジェクトとして追加
	AddChTarget(1, 30, teemo_target);
	//AddChTarget(1, 600, teemo_target_ex);

	// スクロールする背景をロードする
	LoadBackSc("img/back1.png", eOBJECT::NUM::BACK_MAP1, 0, -2560 + 720, -10, 30);


	nya_design_->SetSkillName(eSKILL::NUM::Q, "Skill Q (power)");
	nya_design_->SetSkillName(eSKILL::NUM::W, "Skill W (wave)");
	nya_design_->SetSkillName(eSKILL::NUM::E, "Skill E (bit)");
	nya_design_->SetSkillName(eSKILL::NUM::R, "Skill R (bomb)");

	delete nya_design_;
	delete nya_graphic_;
}

