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
	// �e�I�u�W�F�N�g�ł���NyaMission���j�������Ƃ���
	// �q�I�u�W�F�N�g���j������
	DeleteBackground();
	DeleteTarget();
	DeleteUser();
}

/**
@brief Background���q�I�u�W�F�N�g�Ƃ��Ēǉ�����֐�
@param background ��������background���`�����N���X
@note
 ���ɑO�~�b�V�����Œǉ����ꂽ���e������ꍇ�A�����͔j������ĐV�K�ɓ��e���ǉ������B
**/
void NyaMission::AddChild(NyaBackground* background)
{
	DeleteBackground();
	background_ = background;
}

/**
@brief target���q�I�u�W�F�N�g�Ƃ��Ēǉ�����֐�
@param start_time_sec target�̍s���J�n����
@param end_time_sec target�̍s���I������
@param target ��������target���`�����N���X
@param id target�̎��ʔԍ�ID
@note
 start_time_sec����end_time_sec�܂ł̎��ԍs������target�����ʔԍ�ID�Ƃ��Ēǉ�����B
 ���ɑO�~�b�V�����Œǉ����ꂽ���e������ꍇ�A�����͔j������ĐV�K�ɓ��e���ǉ������B
**/
void NyaMission::AddChild(int start_time_sec, int end_time_sec, NyaTarget* target, unsigned int id)
{
	std::vector<MissionTarget*> temp_collection;
	size_t size = mission_target_collection_.size();

	//************************************************************************************************************
	// C++ ���{�ꃊ�t�@�����X�ɂ���
	// C++17�ȍ~
	// ����sz�����݂̃R���e�i��size()��菬�����ꍇ�A��납��size() - sz�̗v�f���폜����
	// �����łȂ���΁Asz - size()�����I�u�W�F�N�gc�̃R�s�[��ǉ�����B
	// https://cpprefjp.github.io/reference/vector/resize.html
	// size�ȉ��̒l�ɂ��Ă̋����Ɏ��M���Ȃ��̂ŁAsize�ȉ��̓��e��temp�ɃR�s�[���Ă��烊�T�C�Y���邱�Ƃɂ���
	//************************************************************************************************************
	if (size < id + 1)
	{
		temp_collection.resize(mission_target_collection_.size());
		copy(mission_target_collection_.begin(), mission_target_collection_.end(), temp_collection.begin());
		mission_target_collection_.resize(id);
		copy(temp_collection.begin(), temp_collection.end(), mission_target_collection_.begin());
		
		// target��o�^����
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
@brief user���q�I�u�W�F�N�g�Ƃ��Ēǉ�����֐�
@param user ��������user���`�����N���X
@note
 ���ɑO�~�b�V�����Œǉ����ꂽ���e������ꍇ�A�����͔j������ĐV�K�ɓ��e���ǉ������B
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


