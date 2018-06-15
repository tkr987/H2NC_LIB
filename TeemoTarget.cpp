#include "NyaEnum.h"
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
	gp_ = new GraphicPropertyX4;
	ph_ = new PositionHandle1;
}

TargetTeemoMain::~TargetTeemoMain()
{
	delete gp_;
	delete ph_;
}

void TeemoTarget::MissionClear(void)
{
	Draw();
}

void TeemoTarget::MissionCreate(void)
{
	count_frame_ = 0;

	nya_device_ = new NyaDevice;
	nya_position_ = new NyaPosition;
	
	// target teemo main property
	NyaGraphic::LoadGraphicFile("img/target_teemo.png", &teemo_main_.gp_->graphic_file_);
	teemo_main_.ph_->health_ = 100;
	teemo_main_.ph_->collision_power_ = 1;
	teemo_main_.ph_->collision_range_ = 20;
	teemo_main_.ph_->grid_x_ = 300;
	teemo_main_.ph_->grid_y_ = 200;
}

void TeemoTarget::MissionDelete(void)
{
	delete nya_device_;
	delete nya_position_;
}

void TeemoTarget::MissionRun(void)
{
	Act();
	Draw();
}

void TeemoTarget::Act(void)
{	
	nya_position_->Collision(teemo_main_.ph_, eOBJECT::TARGET1);
}

void TeemoTarget::Draw(void)
{
	teemo_main_.gp_->draw_grid_cx_ = (int)teemo_main_.ph_->grid_x_;
	teemo_main_.gp_->draw_grid_cy_ = (int)teemo_main_.ph_->grid_y_;
	NyaGraphic::Draw(teemo_main_.gp_, eOBJECT::TARGET1);
	count_frame_++;
}

