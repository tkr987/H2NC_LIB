#include "DxLib.h"
#include "NyaBackground.h"
#include "NyaEnum.h"
#include "NyaMission.h"
#include "NyaTarget.h"
#include "NyaUser.h"

using namespace std;
using namespace H2NLIB;

NyaBackground* NyaMission::background_;
std::vector<MissionTarget> NyaMission::target_collection_;
NyaUser* NyaMission::user_;

/**
@brief background��ǉ�����֐�
@param background �ǉ�����background
**/
void NyaMission::AddBackground(NyaBackground* background)
{
	background_ = background;
}

/**
@brief target��ǉ�����֐�
@param start_time_sec target�̍s���J�n����
@param end_time_sec target�̍s���I������
@param target �ǉ�����target
@note
 start_time_sec����end_time_sec�܂ł̎��ԍs������target�ǉ�����B
**/
void NyaMission::AddTarget(int start_time_sec, int end_time_sec, NyaTarget* target)
{
	MissionTarget new_mission_target;

	new_mission_target.start_frame_ = start_time_sec * FPS_MAX;
	new_mission_target.end_frame_ = end_time_sec * FPS_MAX;
	new_mission_target.target_ = target;
	target_collection_.push_back(new_mission_target);
}

/**
@brief user��ǉ�����֐�
@param user �ǉ�����user
**/
void NyaMission::AddUser(NyaUser* user)
{
	user_ = user;
}

void NyaMission::ClearBackground(void)
{
	delete background_;
	background_ = nullptr;
}

void NyaMission::ClearTarget(void)
{
	for (auto& e : target_collection_)
	{ 
		delete e.target_;
		e.target_ = nullptr;
	}
	target_collection_.clear();
}

void NyaMission::ClearUser(void)
{
	delete user_;
	user_ = nullptr;
}

void NyaMission::Run(eEVENT check_event)
{
	switch (check_event)
	{
	case eEVENT::MISSION_CREATE:
	case eEVENT::MISSION_REPLAY_CREATE:
		count_frame_ = 0;
		Create();
		break;
	case eEVENT::MISSION_RUN:
	case eEVENT::MISSION_REPLAY_RUN:
	case eEVENT::MISSION_REPLAY_END:
		count_frame_++;
		break;
	case eEVENT::MISSION_DELETE:
	case eEVENT::MISSION_REPLAY_DELETE:
		Delete();
		break;
	}

	if (background_ != nullptr)
		background_->Run(check_event);


	if (user_ != nullptr)
		user_->Run(check_event);


	for (auto& e : target_collection_)
	{
		if (e.start_frame_ <= count_frame_ && count_frame_ < e.end_frame_)
			e.target_->Run(check_event);
	}

}


