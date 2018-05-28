#include "DxLib.h"
#include "NyaBackground.h"
#include "NyaEnum.h"
#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaMission.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "NyaUser.h"

using namespace std;
using namespace H2NLIB;

NyaBackground* NyaMission::background_;
NyaUser* NyaMission::user_;
std::vector<MissionTarget*> NyaMission::mission_target_collection_;


NyaMission::NyaMission()
{

}

NyaMission::~NyaMission()
{
	// 親オブジェクトであるNyaMissionが破棄されるときに
	// 子オブジェクトも破棄する
	DeleteBackground();
	DeleteTarget();
	DeleteUser();
}

/**
@brief Backgroundを子オブジェクトとして追加する関数
@param background 加えたいbackgroundを定義したクラス
@note
 既に前ミッションで追加された内容がある場合、それらは破棄されて新規に内容が追加される。
**/
void NyaMission::AddChild(NyaBackground* background)
{
	DeleteBackground();
	background_ = background;
}

/**
@brief targetを子オブジェクトとして追加する関数
@param start_time_sec targetの行動開始時間
@param end_time_sec targetの行動終了時間
@param target 加えたいtargetを定義したクラス
@param id targetの識別番号ID
@note
 start_time_secからend_time_secまでの時間行動するtargetを識別番号IDとして追加する。
 既に前ミッションで追加された内容がある場合、それらは破棄されて新規に内容が追加される。
**/
void NyaMission::AddChild(int start_time_sec, int end_time_sec, NyaTarget* target, unsigned int id)
{
	std::vector<MissionTarget*> temp_collection;
	size_t size = mission_target_collection_.size();

	//************************************************************************************************************
	// C++ 日本語リファレンスによると
	// C++17以降
	// もしszが現在のコンテナのsize()より小さい場合、後ろからsize() - sz個の要素を削除する
	// そうでなければ、sz - size()個だけオブジェクトcのコピーを追加する。
	// https://cpprefjp.github.io/reference/vector/resize.html
	// size以下の値についての挙動に自信がないので、size以下の内容をtempにコピーしてからリサイズすることにした
	//************************************************************************************************************
	if (size < id + 1)
	{
		temp_collection.resize(mission_target_collection_.size());
		copy(mission_target_collection_.begin(), mission_target_collection_.end(), temp_collection.begin());
		mission_target_collection_.resize(id);
		copy(temp_collection.begin(), temp_collection.end(), mission_target_collection_.begin());
		
		// targetを登録する
		mission_target_collection_[id] = new MissionTarget;
		mission_target_collection_[id]->start_frame_ = start_time_sec * FPS_MAX;
		mission_target_collection_[id]->end_frame_ = end_time_sec * FPS_MAX;
		mission_target_collection_[id]->target_ = target;
	}
	else
	{
		delete mission_target_collection_[id]->target_;
		mission_target_collection_[id]->target_ = nullptr;
		mission_target_collection_[id]->start_frame_ = FPS_MAX * start_time_sec;
		mission_target_collection_[id]->end_frame_ = FPS_MAX * end_time_sec;
		mission_target_collection_[id]->target_ = target;
	}

}

/**
@brief userを子オブジェクトとして追加する関数
@param user 加えたいuserを定義したクラス
@note
 既に前ミッションで追加された内容がある場合、それらは破棄されて新規に内容が追加される。
**/
void NyaMission::AddChild(NyaUser* user)
{
	DeleteUser();
	user_ = user;
}

void NyaMission::DeleteBackground(void)
{
	delete background_;
	background_ = nullptr;
}

void NyaMission::DeleteTarget(void)
{
	for (auto& e : mission_target_collection_)
	{ 
		delete e->target_;
		e->target_ = nullptr;
	}
	mission_target_collection_.clear();
}

void NyaMission::DeleteUser(void)
{
	delete user_;
	user_ = nullptr;
}

void NyaMission::Run(eEVENT check_event)
{
	switch (check_event)
	{
	case eEVENT::MISSION_CREATE:
		count_frame_ = 0;
		Create();
		break;
	case eEVENT::MISSION_RUN:
		count_frame_++;
	case eEVENT::MISSION_CONTINUE:
	case eEVENT::MISSION_CLEAR:
	case eEVENT::MISSION_ALL_CLEAR:
		//background_->Run(check_event);
		user_->Run(check_event);
		for (auto& e : mission_target_collection_)
		{
			if (e->start_frame_ <= count_frame_ && count_frame_ < e->end_frame_)
			{
				e->target_->Run(check_event);
			}

		}
		break;
	case eEVENT::MISSION_DELETE:
		Delete();
		break;
	case eEVENT::MISSION_FINALIZE:
	case eEVENT::MISSION_REPLAY_FINALIZE:
		NyaDesign::Init();
		NyaGraphic::Clear();
		NyaPosition::Init();
		break;
	}

}


