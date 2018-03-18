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
	GraphicPropertyX1* back_gpx1_ = new GraphicPropertyX1;
	NyaTarget* teemo_target = new TeemoTarget;
	//NyaTarget* teemo_target_ex = new TeemoTargetEx;

	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//AddChTarget(1, 30, teemo_target);
	//AddChTarget(60, 6000, teemo_target_ex);

	// �w�i��ǂݍ���
	nya_graphic_->LoadGraphicFile("img/back1.png", &back_gpx1_->graphic_file_);
	back_gpx1_->object_group_ = eOBJECT::NUM::MAP1;
	LoadBack(back_gpx1_, 0, -2560 + 720, 2560 - 720, 180);


	nya_design_->SetSkillName(eSKILL::NUM::Q, "Skill Q (power)");
	nya_design_->SetSkillName(eSKILL::NUM::W, "Skill W (wave)");
	nya_design_->SetSkillName(eSKILL::NUM::E, "Skill E (bit)");
	nya_design_->SetSkillName(eSKILL::NUM::R, "Skill R (bomb)");

	delete nya_design_;
	delete nya_graphic_;
	delete back_gpx1_;
}

