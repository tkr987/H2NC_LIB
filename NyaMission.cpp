#include "DxLib.h"
#include "NyaBackground.h"
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

	// 変数初期化
	count_ = 0;
	background_ = nullptr;
}

NyaMission::~NyaMission()
{
	delete nya_design_;
	nya_design_ = nullptr;
	delete background_;
	background_ = nullptr;
}

void NyaMission::AddChBackground(NyaBackground* background)
{
	background_ = background;
}

void NyaMission::AddChTarget(int start_time_sec, int end_time_sec, NyaTarget* target)
{
	MissionTarget add_mission_target;

	add_mission_target.start_frame_ = FPS_MAX * start_time_sec;
	add_mission_target.end_frame_ = FPS_MAX * end_time_sec;
	add_mission_target.target_ = target;
	mission_target_collection_.push_back(add_mission_target);
}

void NyaMission::LoadSound()
{

}

void NyaMission::LoadSoundEx()
{

}





void NyaMission::Run(eEVENT check_event)
{
	switch (check_event)
	{
	case eEVENT::MISSION_LOAD:
		count_ = 0;
		Load();
		break;
	case eEVENT::MISSION_RUN:
	case eEVENT::MISSION_REPLAY_RUN:
		RunEvent();
		break;
	case eEVENT::MISSION_CONTINUE:
	case eEVENT::MISSION_REPLAY_OVER:
	case eEVENT::MISSION_CLEAR:
	case eEVENT::MISSION_REPLAY_CLEAR:
		ClearEvent();
	case eEVENT::MISSION_END:
	case eEVENT::MISSION_REPLAY_END:
		EndEvent();
		break;
	}

	count_++;
}

/**
@brief クリアイベントで処理する関数
@note
 コンテニューイベントでも使われる。
**/
void NyaMission::ClearEvent(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	// targetの処理
	for (auto& e : mission_target_collection_)
	{
		if (e.start_frame_ <= count_ && count_ < e.end_frame_)
			e.target_->Draw();
	}
	
	// 背景処理
	if (background_ != nullptr)
		background_->Draw();
}

void NyaMission::EndEvent(void)
{
		for (auto& e : mission_target_collection_)
			delete e.target_;
		mission_target_collection_.clear();
}

void NyaMission::RunEvent(void)
{
	// targetの処理
	for (auto& e : mission_target_collection_)
	{
		if (e.start_frame_ <= count_ && count_ < e.end_frame_)
		{
			e.target_->Act();
			e.target_->Draw();
		}
	}
	
	// 背景処理
	if (background_ != nullptr)
	{
		background_->Act();
		background_->Draw();
	}
}
