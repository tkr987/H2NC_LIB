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
	gpx1_back_ = new GraphicPropertyX1;

	// •Ï”‰Šú‰»
	count_ = 0;
	back_pair_.first = false;
}

NyaMission::~NyaMission()
{
	delete nya_design_;
	delete nya_graphic_;
	delete gpx1_back_;
}


void NyaMission::AddChTarget(int start_time_sec, int end_time_sec, NyaTarget* target)
{
	static MissionTarget mission_target;

	mission_target.start_frame_ = FPS_MAX * start_time_sec;
	mission_target.end_frame_ = FPS_MAX * end_time_sec;
	mission_target.target_ = target;
	nya_target_vector_.push_back(mission_target);
}

void NyaMission::End(void)
{
	count_ = 0;
	for (vector<MissionTarget>::iterator it = nya_target_vector_.begin(); it != nya_target_vector_.end(); ++it)
		delete it->target_;
}

void NyaMission::LoadBack(std::string file_pass, int start_grid_x, int start_grid_y, int scroll_max_size, int scroll_max_time_sec)
{
	// ”wŒi‚Ìƒ[ƒh
	back_pair_.first = true;
	back_pair_.second.img_ = nya_graphic_->LoadFile(file_pass);
	back_pair_.second.scroll_limit_frame_time_ = scroll_max_time_sec * FPS_MAX;
	back_pair_.second.scroll_size_per_frame_ = (double)scroll_max_size / (double)(scroll_max_time_sec * FPS_MAX);
	back_pair_.second.grid_x_ = start_grid_x;
	back_pair_.second.grid_y_ = start_grid_y;
	// ”wŒi—pgpx‚Ìİ’è‚ğ‚·‚é
	gpx1_back_->file_div_ = 0;
	gpx1_back_->file_id_ = back_pair_.second.img_;
	gpx1_back_->flag_trans_ = true;
	gpx1_back_->object_group_ = eOBJECT::NUM::MAP1;
}

void NyaMission::LoadSound()
{

}

void NyaMission::LoadSoundEx()
{

}

void NyaMission::Run(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	// target‚Ìˆ—
	for (auto& it : nya_target_vector_)
	{
		if (it.start_frame_ <= count_ && count_ < it.end_frame_)
		{
			it.target_->Act();
			it.target_->Draw();
		}
	}
	
	// ”wŒiˆ—
	if (back_pair_.first)
	{ 
		gpx1_back_->pos_x_ = (int)back_pair_.second.grid_x_;
		gpx1_back_->pos_y_ = (int)back_pair_.second.grid_y_;
		nya_graphic_->Draw(gpx1_back_);
	}
	if (count_ < back_pair_.second.scroll_limit_frame_time_)
		back_pair_.second.grid_y_ += back_pair_.second.scroll_size_per_frame_;


	count_++;
}


void NyaMission::Stop(void)
{
	// target‚Ìˆ—
	for (auto& it : nya_target_vector_)
	{ 
		if (count_ <= it.start_frame_ && it.end_frame_ < count_)
			it.target_->Draw();
	}
	// ”wŒiˆ—
	if (back_pair_.first)
		nya_graphic_->Draw(gpx1_back_);
}