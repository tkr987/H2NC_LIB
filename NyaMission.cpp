#include "DxLib.h"
#include "NyaDefine.h"
#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "NyaMission.h"
#include "NyaString.h"
#include "NyaTarget.h"

using namespace std;
using namespace H2NLIB;


NyaMission::NyaMission()
{
	nya_design_ = new NyaDesign;
	nya_graphic_ = new NyaGraphic;
	mission_back_.gpx1_ = new GraphicPropertyX1;
	mission_back_.empty_ = true;

	// •Ï”‰Šú‰»
	count_ = 0;
}

NyaMission::~NyaMission()
{
	delete nya_design_;
	delete nya_graphic_;
	delete mission_back_.gpx1_;
}


void NyaMission::AddChTarget(int start_time_sec, int end_time_sec, NyaTarget* target)
{
	static MissionTarget mission_target;

	mission_target.start_frame_ = FPS_MAX * start_time_sec;
	mission_target.end_frame_ = FPS_MAX * end_time_sec;
	mission_target.target_ = target;
	mission_target_vector_.push_back(mission_target);
}

void NyaMission::LoadBack(GraphicPropertyX1* gpx1, int start_grid_x, int start_grid_y, int scroll_max_size, int scroll_max_time_sec)
{
	if (!mission_back_.empty_)
		return;

	// ”wŒi‚Ìƒ[ƒh
	mission_back_.empty_ = false;
	mission_back_.grid_x_ = (double)start_grid_x;
	mission_back_.grid_y_ = (double)start_grid_y;
	mission_back_.scroll_limit_frame_time_ = scroll_max_time_sec * FPS_MAX;
	mission_back_.scroll_size_per_frame_ = (double)scroll_max_size / (double)(scroll_max_time_sec * FPS_MAX);
	mission_back_.gpx1_->graphic_file_.div_vector_.resize(gpx1->file_div_);
	*mission_back_.gpx1_ = *gpx1;
}

void NyaMission::LoadSound()
{

}

void NyaMission::LoadSoundEx()
{

}

void NyaMission::MissionEnd(void)
{
	count_ = 0;
	for (auto& e : mission_target_vector_)
		delete e.target_;
	nya_graphic_->DeleteGraphicFile(mission_back_.gpx1_->graphic_file_);
	mission_back_.empty_ = true;
}

void NyaMission::MissionRun(void)
{
	// target‚Ìˆ—
	for (auto& it : mission_target_vector_)
	{
		if (it.start_frame_ <= count_ && count_ < it.end_frame_)
		{
			it.target_->Act();
			it.target_->Draw();
		}
	}
	
	// ”wŒiˆ—
	if (!mission_back_.empty_)
	{
		mission_back_.gpx1_->pos_x_ = (int)mission_back_.grid_x_;
		mission_back_.gpx1_->pos_y_ = (int)mission_back_.grid_y_;
		nya_graphic_->Draw(mission_back_.gpx1_);
		if (count_ < mission_back_.scroll_limit_frame_time_)
			mission_back_.grid_y_ += mission_back_.scroll_size_per_frame_;
	}

	count_++;
}


void NyaMission::MissionStop(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	// target‚Ìˆ—
	for (auto& it : mission_target_vector_)
	{
		if (it.start_frame_ <= count_ && count_ < it.end_frame_)
			it.target_->Draw();
	}
	
	// ”wŒiˆ—
	if (!mission_back_.empty_)
	{
		mission_back_.gpx1_->pos_x_ = (int)mission_back_.grid_x_;
		mission_back_.gpx1_->pos_y_ = (int)mission_back_.grid_y_;
		nya_graphic_->Draw(mission_back_.gpx1_);
	}
}
