#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"
#include "TargetExTeemo.h"

using namespace H2NLIB;

void TeemoMission1::Load(void) 
{
	NyaDesign* nya_design_ = new NyaDesign;
	NyaGraphic* nya_graphic_ = new NyaGraphic;
	//NyaTarget* teemo_target = new TeemoTarget;
	NyaTarget* target_ex_teemo = new TargetExTeemo;

	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//AddChTarget(1, 30, teemo_target);
	AddChTarget(5, 600, target_ex_teemo);

	// �X�N���[������w�i�����[�h����
	LoadBackSc("img/back1.png", eOBJECT::NUM::BACK_MAP1, 0, -2560 + 720, -10, 30);


	nya_design_->SetSkillName(eSKILL::NUM::Q, "Skill Q (power)");
	nya_design_->SetSkillName(eSKILL::NUM::W, "Skill W (wave)");
	nya_design_->SetSkillName(eSKILL::NUM::E, "Skill E (bit)");
	nya_design_->SetSkillName(eSKILL::NUM::R, "Skill R (bomb)");

	delete nya_design_;
	delete nya_graphic_;
}

