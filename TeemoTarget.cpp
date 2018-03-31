#include "NyaDefine.h"
#include "NyaDevice.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "TeemoTarget.h"

using namespace std;
using namespace H2NLIB;

TargetTeemoMain::TargetTeemoMain()
{
	gp_ = new GraphicProperty4;
	ph_ = new PositionHandle1;
}

TargetTeemoMain::~TargetTeemoMain()
{
	delete gp_;
	delete ph_;
}

void TeemoTarget::Act(void)
{	
	nya_position_->Collision(teemo_main_.ph_, eOBJECT::NUM::TARGET1);

	count_++;
}

void TeemoTarget::Draw(void)
{
	teemo_main_.gp_->draw_grid_cx_ = (int)teemo_main_.ph_->grid_x_;
	teemo_main_.gp_->draw_grid_cy_ = (int)teemo_main_.ph_->grid_y_;
	nya_graphic_->Draw(teemo_main_.gp_, eOBJECT::TARGET1);
}

void TeemoTarget::MissionEnd(void)
{
	nya_graphic_->DeleteGraphicFile(&teemo_main_.gp_->graphic_file_);

	delete nya_device_;
	delete nya_graphic_;
	delete nya_position_;
}

void TeemoTarget::MissionStart(void)
{
	count_ = 0;

	nya_device_ = new NyaDevice;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
	
	// target teemo main property
	nya_graphic_->LoadGraphicFile("img/target_teemo.png", &teemo_main_.gp_->graphic_file_);
	teemo_main_.ph_->health_max_ = 100;
	teemo_main_.ph_->health_now_ = 100;
	teemo_main_.ph_->collision_pow_ = 1;
	teemo_main_.ph_->collision_range_ = 20;
	teemo_main_.ph_->grid_x_ = 300;
	teemo_main_.ph_->grid_y_ = 200;
}
