#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "TeemoBackgroundMission1.h"
#include "TeemoMission1.h"
#include "TeemoTarget.h"
#include "TargetExTeemo.h"

using namespace H2NLIB;

void TeemoMission1::Load(void) 
{
	NyaBackground* background_mission1_teemo = new TeemoBackgroundMission1;
	NyaDesign* nya_design_ = new NyaDesign;
	//NyaTarget* teemo_target = new TeemoTarget;
	NyaTarget* target_ex_teemo = new TargetExTeemo;

	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//AddChTarget(1, 30, teemo_target);
	AddChTarget(5, 600, target_ex_teemo);

	// �X�N���[������w�i���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	AddChBackground(background_mission1_teemo);

	// ���Ƃ�user�֐��Őݒ肷��悤�Ɉڂ��\������
	nya_design_->SetSkillName(eSKILL::Q, "Skill Q (power)");
	nya_design_->SetSkillName(eSKILL::W, "Skill W (wave)");
	nya_design_->SetSkillName(eSKILL::E, "Skill E (bit)");
	nya_design_->SetSkillName(eSKILL::R, "Skill R (bomb)");

	delete nya_design_;
}

