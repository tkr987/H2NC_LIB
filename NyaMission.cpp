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
	back_pair_.first = false;
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
	nya_target_vector_.push_back(mission_target);
}

void NyaMission::LoadBack(std::string file_pass, int start_grid_x, int start_grid_y, int scroll_max_size, int scroll_max_time_sec)
{
	back_pair_.first = true;
	back_pair_.second.img_ = nya_graphic_->LoadFile(file_pass);
	back_pair_.second.scroll_limit_frame_time_ = scroll_max_time_sec * FPS_MAX;
	back_pair_.second.scroll_size_per_frame_ = (double)scroll_max_size / (double)(scroll_max_time_sec * FPS_MAX);
	back_pair_.second.grid_x_ = start_grid_x;
	back_pair_.second.grid_y_ = start_grid_y;
}

void NyaMission::LoadSound()
{

}

void NyaMission::LoadSoundEx()
{

}

void NyaMission::Run(void)
{
	static GraphicPropertyX1 gpx1_back;
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	switch(nya_design_->GetProcess()) {
	case ePROCESS::MISSION_LOAD:
		count_ = 0;
		if (back_pair_.first) 
		{
			gpx1_back.file_div_ = 0;
			gpx1_back.file_id_ = back_pair_.second.img_;
			gpx1_back.flag_trans_ = true;
			gpx1_back.object_group_ = eOBJECT::NUM::MAP1;
			gpx1_back.pos_x_ = (int)back_pair_.second.grid_x_;
			gpx1_back.pos_y_ = (int)back_pair_.second.grid_y_;
		}
		break;
	case ePROCESS::MISSION_RUN:
		// target
		for (auto& it : nya_target_vector_)
		{
			if (it.start_frame_ <= count_ && count_ < it.end_frame_)
			{
				it.target_->Action();
				it.target_->Draw();
			}
		}
		// ”wŒi•`‰æ
		if (back_pair_.first)
		{ 
			gpx1_back.pos_x_ = (int)back_pair_.second.grid_x_;
			gpx1_back.pos_y_ = (int)back_pair_.second.grid_y_;
			nya_graphic_->Draw(&gpx1_back);
		}
		if (count_ < back_pair_.second.scroll_limit_frame_time_)
			back_pair_.second.grid_y_ += back_pair_.second.scroll_size_per_frame_;
		// ‚»‚Ì‘¼‚Ìˆ—
		count_++;
		break;
	case ePROCESS::MISSION_STOP:
		// target
		for (auto& it : nya_target_vector_)
			if (count_ <= it.start_frame_ && it.end_frame_ < count_)
				it.target_->Draw();
		// ”wŒi•`‰æ
		if (back_pair_.first)
			nya_graphic_->Draw(&gpx1_back);
		break;
	}
}
