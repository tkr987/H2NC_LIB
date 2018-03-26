#include "DxLib.h"
#include "NyaDefine.h"
#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "NyaMission.h"
#include "NyaString.h"
#include "NyaTarget.h"

using namespace std;
using namespace H2NLIB;


MissionBack::MissionBack()
{
	gp_ = new GraphicProperty1;
	valid_ = false;
}

MissionBack::~MissionBack()
{
	delete gp_;
}

NyaMission::NyaMission()
{
	nya_design_ = new NyaDesign;
	nya_graphic_ = new NyaGraphic;

	// ïœêîèâä˙âª
	count_ = 0;
}

NyaMission::~NyaMission()
{
	delete nya_design_;
	delete nya_graphic_;
}


void NyaMission::AddChTarget(int start_time_sec, int end_time_sec, NyaTarget* target)
{
	static MissionTarget mission_target;

	mission_target.start_frame_ = FPS_MAX * start_time_sec;
	mission_target.end_frame_ = FPS_MAX * end_time_sec;
	mission_target.target_ = target;
	mission_target_vector_.push_back(mission_target);
}

void NyaMission::LoadBack(GraphicProperty1* gp, eOBJECT::NUM draw_layer, int start_grid_x, int start_grid_y, int scroll_max_size, int scroll_max_time_sec)
{
	if (mission_back_.valid_)
		return;

	// îwåiÇÃÉçÅ[Éh
	mission_back_.valid_ = true;
	mission_back_.grid_x_ = (double)start_grid_x;
	mission_back_.grid_y_ = (double)start_grid_y;
	mission_back_.scroll_limit_frame_time_ = scroll_max_time_sec * FPS_MAX;
	mission_back_.scroll_size_per_frame_ = (double)scroll_max_size / (double)(scroll_max_time_sec * FPS_MAX);
	*mission_back_.gp_ = *gp;
	mission_back_.draw_layer_ = draw_layer;
}

void NyaMission::LoadSound()
{

}

void NyaMission::LoadSoundEx()
{

}

void NyaMission::ProcessMissionContinue(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	// targetÇÃèàóù
	for (auto& it : mission_target_vector_)
	{
		if (it.start_frame_ <= count_ && count_ < it.end_frame_)
			it.target_->Draw();
	}
	
	// îwåièàóù
	if (mission_back_.valid_)
	{
		mission_back_.gp_->draw_grid_x_ = (int)mission_back_.grid_x_;
		mission_back_.gp_->draw_grid_y_ = (int)mission_back_.grid_y_;
		nya_graphic_->Draw(mission_back_.gp_, mission_back_.draw_layer_);
	}
}

void NyaMission::ProcessMissionDelete(void)
{
	count_ = 0;
	for (auto& e : mission_target_vector_)
		delete e.target_;
	mission_back_.valid_ = false;
}

void NyaMission::ProcessMissionRun(void)
{
	// targetÇÃèàóù
	for (auto& e : mission_target_vector_)
	{
		if (e.start_frame_ <= count_ && count_ < e.end_frame_)
		{
			e.target_->Act();
			e.target_->Draw();
		}
	}
	
	// îwåièàóù
	if (mission_back_.valid_)
	{
		mission_back_.gp_->draw_grid_x_ = (int)mission_back_.grid_x_;
		mission_back_.gp_->draw_grid_y_ = (int)mission_back_.grid_y_;
		nya_graphic_->Draw(mission_back_.gp_, mission_back_.draw_layer_);
		if (count_ < mission_back_.scroll_limit_frame_time_)
			mission_back_.grid_y_ += mission_back_.scroll_size_per_frame_;
	}

	count_++;
}



