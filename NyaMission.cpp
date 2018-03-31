#include "DxLib.h"
#include "NyaDefine.h"
#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "NyaMission.h"
#include "NyaString.h"
#include "NyaTarget.h"

using namespace std;
using namespace H2NLIB;


MissionBackSc::MissionBackSc()
{
	gp_ = new GraphicProperty1;
	valid_ = false;
}

MissionBackSc::~MissionBackSc()
{
	delete gp_;
}

NyaMission::NyaMission()
{
	nya_design_ = new NyaDesign;
	nya_graphic_ = new NyaGraphic;

	// •Ï”‰Šú‰»
	count_ = 0;
}

NyaMission::~NyaMission()
{
	delete nya_design_;
	delete nya_graphic_;
}


void NyaMission::AddChTarget(int start_time_sec, int end_time_sec, NyaTarget* target)
{
	MissionTarget add_mission_target;

	add_mission_target.start_frame_ = FPS_MAX * start_time_sec;
	add_mission_target.end_frame_ = FPS_MAX * end_time_sec;
	add_mission_target.target_ = target;
	mission_target_vector_.push_back(add_mission_target);
}

void NyaMission::LoadBackSc(string file_pass, eOBJECT::NUM draw_layer, double start_grid_x, double start_grid_y, double end_grid_y, unsigned int scroll_max_time_sec)
{
	if (mission_back_sc_.valid_)
		return;

	// ”wŒi‚Ìƒ[ƒh
	mission_back_sc_.draw_layer_ = draw_layer;
	mission_back_sc_.gp_->draw_grid_x_ = start_grid_x;
	mission_back_sc_.gp_->draw_grid_y_ = start_grid_y;
	nya_graphic_->LoadGraphicFile(file_pass, &mission_back_sc_.gp_->graphic_file_);
	mission_back_sc_.end_grid_y_ = end_grid_y;
	mission_back_sc_.scroll_speed_per_frame_ = (double)mission_back_sc_.gp_->graphic_file_.size_y_ / (double)(scroll_max_time_sec * FPS_MAX);
	mission_back_sc_.valid_ = true;
}

void NyaMission::LoadSound()
{

}

void NyaMission::LoadSoundEx()
{

}

void NyaMission::MissionEnd(void)
{
	// target‚Ìˆ—
	for (auto& it : mission_target_vector_)
		it.target_->MissionEnd();

	for (auto& e : mission_target_vector_)
		delete e.target_;
	mission_target_vector_.clear();

	if (mission_back_sc_.valid_)
	{ 
		mission_back_sc_.valid_ = false;
		nya_graphic_->DeleteGraphicFile(&mission_back_sc_.gp_->graphic_file_);
	}
}

void NyaMission::MissionStart(void)
{
	count_ = 0;
	// target‚Ìˆ—
	for (auto& it : mission_target_vector_)
		it.target_->MissionStart();
}

void NyaMission::MissionRunClear(void)
{

}


void NyaMission::MissionRunContinue(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	// target‚Ìˆ—
	for (auto& it : mission_target_vector_)
	{
		if (it.start_frame_ <= count_ && count_ < it.end_frame_)
			it.target_->Draw();
	}
	
	// ”wŒiˆ—
	if (mission_back_sc_.valid_)
		nya_graphic_->Draw(mission_back_sc_.gp_, mission_back_sc_.draw_layer_);
}


void NyaMission::MissionRun(void)
{
	// target‚Ìˆ—
	for (auto& e : mission_target_vector_)
	{
		if (e.start_frame_ <= count_ && count_ < e.end_frame_)
		{
			e.target_->Act();
			e.target_->Draw();
		}
	}
	
	// ”wŒiˆ—
	if (mission_back_sc_.valid_)
	{
		nya_graphic_->Draw(mission_back_sc_.gp_, mission_back_sc_.draw_layer_);
		if (mission_back_sc_.gp_->draw_grid_y_ < mission_back_sc_.end_grid_y_)
			mission_back_sc_.gp_->draw_grid_y_ += mission_back_sc_.scroll_speed_per_frame_;
	}

	count_++;
}



