#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <tuple>
#include "DxLib.h"
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaEnding.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaInterface.h"
#include "NyaMission.h"
#include "NyaOpening.h"
#include "NyaPosition.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "NyaUser.h"
#include "NyaWindow.h"

#define __DEBUG__

using namespace std;
using namespace std::experimental::filesystem;
using namespace HNLIB;


WindowChild::WindowChild()
{
	mission_index_ = 0;
	ending_ = nullptr;
	opening_ = nullptr;
}

NyaWindow::NyaWindow(string title)
{
	//******************
	// DXLIB������
	//******************
	SetMainWindowText("happy 2 nya C++ DXLIB STG wrapper v78");		// �^�C�g��
	ChangeWindowMode(true);											// �E�B���h�E���[�h
	SetGraphMode(1280, 720, 32);									// ��ʃT�C�Y, �F��
	DxLib_Init();													// ������
	SetAlwaysRunFlag(true);											// ��A�N�e�B�u��Ԃł����삳����
	SetUseDivGraphFlag(false);										// �O���t�B�b�N�`�敪�����@
	SetDrawScreen(DX_SCREEN_BACK);									// �`���O���t�B�b�N�̈�̎w��

	// �f�B���N�g���쐬
	create_directory("replay");

	// �e�N���X����DXLIB�֐��𗘗p����\��������̂�
	// DXLIB���������Init()���Ăяo���K�v������B
	// �C���^�[�t�F�[�X�̏�����������
	NyaInterface::Init();
	NyaInterface::GetHandleTitle()->name_ << title;
	
	// �t�H���g�ݒ�
	NyaString::SettingFont("fps_font", 14, 2);
	NyaString::SettingFont("window_title_font", 30, 4);
	NyaString::SettingFont("debug_font", 10, 2);

	// �����o�ϐ��̏�����
	event_ = eEVENT::TITLE;
	event_next_ = eEVENT::enum_zero;
}


NyaWindow::~NyaWindow(void)
{
	// �e�I�u�W�F�N�g��NyaWindow��j������Ƃ��Ɏq�I�u�W�F�N�g��j������
	delete child_.opening_;
	child_.opening_ = nullptr;
	for (auto& e : child_.mission_collection_)
	{
		delete e;
		e = nullptr;
	}
	delete child_.ending_;
	child_.ending_ = nullptr;

	DxLib_End();
}

/**
@brief �~�b�V������ǉ�����֐�
@param mission �ǉ�����~�b�V����
@note
 NyaWindow�̎q�I�u�W�F�N�g�Ƃ��ă~�b�V�������ǉ������B
**/
void NyaWindow::Child(NyaMission* mission)
{
	child_.mission_collection_.push_back(mission);
}

void NyaWindow::Child(NyaOpening* opening)
{
	child_.opening_ = opening;
}

void NyaWindow::Child(NyaEnding* ending)
{
	child_.ending_ = ending;
}


/**
 @brief ���s�֐�
 @note
  ���C�u�����̑S�Ă̏��������s�����
  ����āA���C�u�����g�p�҂�main�֐��ŕK���Ăяo���K�v������
**/
void NyaWindow::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	std::chrono::system_clock::time_point debug_time_start, debug_time_end;
	long long debug_time_msec;

	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1 && event_ != eEVENT::WINDOW_CLOSE)
	{

		// TODO
		// �A���Ń��v���C�Đ������Ƃ��̃o�O
		// �^�C�g����PositionHandle�̃N���A������

		//*********************************************************************
		// �C�x���g�̍X�V�Ɏg���ϐ���enum_zero�ŏ��������Ă���
		// NyaWindow�̃����o�֐���event_next_�̒l��enum_zero�ȊO�ɂ����Ƃ�
		// Run()�̍Ō�ɃC�x���g���X�V���鏈���������Ȃ�
		//*********************************************************************
		event_next_ = eEVENT::enum_zero;

		//******************************************************
		// ���C�u�����̏���
		// �����Ȃ��̊֐��͏�Ɏ��s�����
		// event�������Ɏ��֐��̓C�x���g�ɂ���ď������ς��
		//*******************************************************

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaDevice::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 620, "[600, 620] NyaDevice::Run() %d msec", (int)debug_time_msec);
#else 
		NyaDevice::Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaEffect::Run(event_);
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 640, "[600, 640] NyaEffect::Run() %d msec", (int)debug_time_msec);
#else 
		NyaEffect::Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaGraphic::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 660, "[600, 660] NyaGraphic::Run() %d msec", (int)debug_time_msec);
#else 
		NyaGraphic::Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaPosition::Run(event_);
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 680, "[600, 680] NyaPosition::Run() %d msec", (int)debug_time_msec);
#else 
		NyaPosition::Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaInput::Run(event_);
		NyaInterface::Run(event_);
		NyaSound::Run();
		NyaString::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 700, "[600, 700] Nya*****::Run() %d msec", (int)debug_time_msec);
#else
		NyaInput::Run(event_);
		NyaInterface::Run();
		NyaSound::Run();
		NyaString::Run();
#endif

		//***********************
		// NyaWindow �����o�֐�
		// �^�C�g�����
		// �I�[�v�j���O����
		// �~�b�V��������
		// �G���f�B���O����
		// ���v���C�ۑ�
		//***********************
		Title();
		Opening();
		Mission();
		Ending();
		SaveReplay();
		NotSaveReplay();

		//*****************************
		// ��ʍX�V
		// �t���[�����[�g�̏���
		//*****************************
		ScreenFlip();
		ClearDrawScreen();
		WaitFPS(1010, 695);

		//*******************************************************************************
		// enum_zero�łȂ��Ȃ�NyaWindow�̃����o�֐���event_next_��ύX�����Ƃ�������
		// enum_zero�łȂ��Ȃ�C�x���g�̍X�V������
		//*******************************************************************************
		if (event_next_ != eEVENT::enum_zero)
			event_ = event_next_;
	}

}

/**
@brief �G���f�B���O�̏���������֐�
@note
 �G���f�B���O���o�^����ĂȂ��Ƃ��͉����������̃C�x���g�ɑJ�ڂ���
**/
void NyaWindow::Ending(void)
{
	switch(event_)
	{
	case eEVENT::ENDING_LOAD:
		if (NyaInterface::GetHandleContinue()->cnum_ != 0)
			event_next_ = eEVENT::NOT_REPLAY_SAVE;
		else
		{
			if (child_.ending_ == nullptr)
				event_next_ = eEVENT::REPLAY_SAVE;
			else
			{
				child_.ending_->Load();
				event_next_ = eEVENT::ENDING_RUN;
			}
		}
		break;
	case eEVENT::ENDING_RUN:
		child_.ending_->Run();
	if (NyaInput::IsPressKey(eINPUT::ENTER))
		event_next_ = eEVENT::ENDING_DELETE;
		break;
	case eEVENT::ENDING_DELETE:
		child_.ending_->Delete();
		NyaInterface::Init();
		event_next_ = eEVENT::REPLAY_SAVE;
		break;
	}
}


/**
 @brief �~�b�V�����̏���������֐�
 @note
  �~�b�V�������o�^����ĂȂ��ꍇ�͉������Ȃ��Ń^�C�g���ɖ߂�
**/
void NyaWindow::Mission(void)
{
	if (child_.mission_collection_.size() == 0)
	{
		event_next_ = eEVENT::TITLE;
		return;
	}

	//***************************************************************
	// �C�x���g����
	// note: eEVENT::MISSION_CREATE��eEVENT::TITLE����J�ڂ��Ă���
	//***************************************************************
	switch (event_) 
	{
	// �~�b�V���������̏���
	// 1. NyaMission::Run()�̈�����eEVENT::MISSION_CREATE��n���ă~�b�V�����N���A���̏�����������
	// 2. eEVENT::MISSION_RUN�ɑJ�ڂ���
	case eEVENT::MISSION_CREATE:
		child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_CREATE);
		event_next_ = eEVENT::MISSION_RUN;
		break;
	// �~�b�V�������s�̏���
	// NyaMission::Run()�̈�����eEVENT::MISSION_RUN��n���ă~�b�V�������s���̏�����������
	// �܂��A�C���^�[�t�F�[�X�̃t���O�󋵂ɂ���đJ�ڐ�����߂�
	case eEVENT::MISSION_RUN:
		child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_RUN);
		if (NyaInterface::GetHandleContinue()->valid_)
			event_next_ = eEVENT::MISSION_CONTINUE;
		else if (NyaInterface::GetHandleClear()->valid_)
			event_next_ = eEVENT::MISSION_CLEAR;
		else if (NyaInterface::GetHandleComplete()->valid_)
			event_next_ = eEVENT::MISSION_COMPLETE;
		break;
	// �~�b�V�����R���e�j���[�̏���
	// - mission continue ��ʂ��\������Ă���Ƃ�
	// NyaMission::Run()�̈�����eEVENT::MISSION_CONTINUE��n���ăR���e�j���[��ʂ̏�����������
	// - mission continue ��ʂ̕\�����I������Ƃ�
	// continue �n���h���̒l�ɂ���đJ�ڐ�����߂�
	// -- �R���e�j���[����I���̂Ƃ�
	//  eEVENT::MISSION_RUN�ɑJ�ڂ���
	// -- �R���e�j���[���Ȃ��I���A���R���e�j���[�񐔂�0�̂Ƃ�
	//  1. NyaMission::Run()�̈�����eEVENT::MISSION_DELETE��n���ă~�b�V�������폜������
	//  2. eEVENT::REPLAY_SAVE�ɑJ�ڂ���
	// -- �R���e�j���[���Ȃ��I�������A�R���e�j���[�񐔂�0�łȂ��Ƃ�
	//  1. NyaMission::Run()�̈�����eEVENT::MISSION_DELETE��n���ă~�b�V�������폜������
	//  2. eEVENT::REPLAY_SAVE�ɑJ�ڂ���
	case eEVENT::MISSION_CONTINUE:
		if (NyaInterface::GetHandleContinue()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_CONTINUE);
		else
		{
			if (NyaInterface::GetHandleContinue()->select_ == 0)
				event_next_ = eEVENT::MISSION_RUN;
			if (NyaInterface::GetHandleContinue()->select_ == 1 && NyaInterface::GetHandleContinue()->cnum_ == 0)
			{
				child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_DELETE);
				event_next_ = eEVENT::REPLAY_SAVE;
			}
			if (NyaInterface::GetHandleContinue()->select_ == 1 && NyaInterface::GetHandleContinue()->cnum_ != 0)
			{
				child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_DELETE);
				event_next_ = eEVENT::NOT_REPLAY_SAVE;
			}
		}
		break;
	// �~�b�V�����N���A�̏���
	// - mission clear ��ʂ��\������Ă���Ƃ�
	// NyaMission::Run()�̈�����eEVENT::MISSION_CLEAR��n���ă~�b�V�����N���A���̏�����������
	// - mission clear ��ʂ̕\�����I������Ƃ�
	// 1. �L��������Ă���C���^�[�t�F�[�X�n���h���̖�����
	// 2. NyaMission::Run()�̈�����eEVENT::MISSION_DELETE��n���ă~�b�V�������폜������
	// 3. mission_index_���X�V����
	// 4. eEVENT::MISSION_CREATE�ɑJ�ڂ���
	case eEVENT::MISSION_CLEAR:
		if(NyaInterface::GetHandleClear()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_CLEAR);
		else 
		{
			NyaInterface::GetHandleHealth()->valid_ = false;
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_DELETE);
			child_.mission_index_++;
			event_next_ = eEVENT::MISSION_CREATE;
		}
		break;
	// �~�b�V�����R���v���[�g�̏���
	// - mission complete ��ʂ��\������Ă���Ƃ�
	// NyaMission::Run()�̈�����eEVENT::MISSION_COMPLETE��n���ă~�b�V�����R���v���[�g���̏�����������
	// - mission complete ��ʂ̕\�����I������Ƃ�
	// 1. �L��������Ă���C���^�[�t�F�[�X�n���h���̖�����
	// 2. NyaMission::Run()�̈�����eEVENT::MISSION_DELETE��n���ă~�b�V�������폜������
	// 3. eEVENT::ENDING_LOAD�ɑJ�ڂ���
	case eEVENT::MISSION_COMPLETE:
		if (NyaInterface::GetHandleComplete()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_COMPLETE);
		else
		{
			NyaInterface::GetHandleHealth()->valid_ = false;
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_DELETE);
			event_next_ = eEVENT::ENDING_LOAD;
		}
		break;
	// �~�b�V���������̏���(���v���C)
	// 1. NyaMission::Run()�̈�����eEVENT::MISSION_REPLAY_CREATE��n���ă~�b�V�����N���A���̏�����������
	// 2. eEVENT::MISSION_REPLAY_RUN�ɑJ�ڂ���
	case eEVENT::MISSION_REPLAY_CREATE:
		child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_REPLAY_CREATE);
		event_next_ = eEVENT::MISSION_REPLAY_RUN;
		break;
	// �~�b�V�������s�̏���(���v���C)
	// NyaMission::Run()�̈�����eEVENT::MISSION_REPLAY_RUN��n���ă~�b�V�������s���̏�����������
	// �܂��A�t���O�󋵂ɂ���đJ�ڐ�����߂�
	// - �c�@0�Ȃ�replay end flag��true�ɂ���eEVENT::MISSION_REPLAY_END�ɑJ�ڂ���
	// - mission clear flag��true�Ȃ�eEVENT::MISSION_REPLAY_CLEAR�ɑJ�ڂ���
	// - mission complete flag��true�Ȃ�eEVENT::MISSION_REPLAY_COMPLETE�ɑJ�ڂ���
	case eEVENT::MISSION_REPLAY_RUN:
		child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_REPLAY_RUN);
		if (NyaInterface::GetHandleLife()->value_ == 0)
		{
			NyaInterface::GetHandleEnd()->valid_ = true;
			event_next_ = eEVENT::MISSION_REPLAY_END;
		}
		else if (NyaInterface::GetHandleClear()->valid_)
			event_next_ = eEVENT::MISSION_REPLAY_CLEAR;
		else if (NyaInterface::GetHandleComplete()->valid_)
			event_next_ = eEVENT::MISSION_REPLAY_COMPLETE;
		break;
	// ���v���C�I���̏���
	// - replay end ��ʂ��\������Ă���Ƃ�
	// 1. NyaMission::Run()�̈�����eEVENT::MISSION_REPLAY_END��n���ă��v���C�I�����̏�����������
	// 2. ���v���C�I����ʂ̕\��������
	// - replay end ��ʂ̕\�����I������Ƃ�
	// 1. �C���^�[�t�F�[�X������������
	// 2. NyaMission::Run()�̈�����eEVENT::MISSION_DELETE��n���ă~�b�V�������폜������
	// 3. eEVENT::TITLE�ɑJ�ڂ���
	case eEVENT::MISSION_REPLAY_END:
		if (NyaInterface::GetHandleEnd()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_REPLAY_END);
		else
		{
			NyaInterface::Init();
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_DELETE);
			event_next_ = eEVENT::TITLE;
		}
		break;
	// �~�b�V�����N���A�̏���(���v���C)
	// - mission clear ��ʂ��\������Ă���Ƃ�
	// NyaMission::Run()�̈�����eEVENT::MISSION_REPLAY_CLEAR��n���ă��v���C�N���A���̏�����������
	// - mission clear ��ʂ̕\�����I������Ƃ�
	// 1. �L��������Ă���C���^�[�t�F�[�X�n���h���̖�����
	// 2. NyaMission::Run()�̈�����eEVENT::MISSION_DELETE��n���ă~�b�V�������폜������
	// 3. mission_index_���X�V����
	// 4. eEVENT::TITLE�ɑJ�ڂ���
	case eEVENT::MISSION_REPLAY_CLEAR:
		if (NyaInterface::GetHandleClear()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_REPLAY_CLEAR);
		else
		{
			NyaInterface::GetHandleHealth()->valid_ = false;
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_DELETE);
			child_.mission_index_++;
			event_next_ = eEVENT::MISSION_REPLAY_CREATE;
		}
		break;
	// �~�b�V�����R���v���[�g�̏���
	// - mission complete ��ʂ��\������Ă���Ƃ�
	// NyaMission::Run()�̈�����eEVENT::MISSION_COMPLETE��n���ă~�b�V�����R���v���[�g���̏�����������
	// - mission complete ��ʂ̕\�����I������Ƃ�
	// 1. �C���^�[�t�F�[�X�̏�����
	// 2. NyaMission::Run()�̈�����eEVENT::MISSION_DELETE��n���ă~�b�V�������폜������
	// 3. eEVENT::TITLE�ɑJ�ڂ���
	case eEVENT::MISSION_REPLAY_COMPLETE:
		if (NyaInterface::GetHandleComplete()->valid_)
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_REPLAY_COMPLETE);
		else
		{
			NyaInterface::Init();
			child_.mission_collection_[child_.mission_index_]->Run(eEVENT::MISSION_DELETE);
			event_next_ = eEVENT::TITLE;
		}
		break;
	}
}

/**
 @param ���v���C�̕ۑ�������֐�
 @note
  �t�H���g�̓^�C�g����ʂ𗬗p
**/
void NyaWindow::SaveReplay(void)
{
	string pass;
	int x, y;
	string date, seed, title;
	ifstream ifs;
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	tuple<int, int, int> red = make_tuple(255, 0, 0);
	static int select = 1;

	if (event_ != eEVENT::REPLAY_SAVE)
		return;

	// �܂��A�C���^�[�t�F�[�X�̏����������Ă���
	NyaInterface::Init();

	//************************************************
	// �J�[�\���L�[�̓��͂ɉ����Č��݂̑I�����X�V
	//************************************************
	if (NyaInput::IsPressKey(eINPUT::DOWN))
		select = (select == 5) ? 1 : select + 1;
	if (NyaInput::IsPressKey(eINPUT::UP))
		select = (select == 1) ? 5 : select - 1;
	x = 60;
	y = 100 + select * 100;
	NyaString::Write("window_title_font", red, x, y - 40, "��");

	//****************************
	// ���C�x���g�̖��O��\��
	//****************************
	x = 60;
	y = 100;
	NyaString::Write("window_title_font", white, x + 70, y - 40, "SAVE REPLAY");

	//*******************************************
	// ���v���C�t�H���_�ɂ���t�@�C���̕\��
	//*******************************************
	y += 100;
	ifs.open("replay/replay1.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay1");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		getline(ifs, title);
		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay1.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();
	y += 100;
	ifs.open("replay/replay2.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay2");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		getline(ifs, title);
		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay2.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();
	y += 100;
	ifs.open("replay/replay3.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay3");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		getline(ifs, title);
		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay3.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	y += 100;
	ifs.close();
	ifs.open("replay/replay4.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay4");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		getline(ifs, title);
		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay4.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();

	//**************************
	// �I���̑I������\��
	//**************************
	y += 100;
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "END");

	//****************************
	// �t�@�C���ւ̏�������
	//****************************
	if (NyaInput::IsPressKey(eINPUT::ENTER))
	{
		if (select == 1)
			NyaInput::OutputReplay("replay/replay1.rep");
		if (select == 2)
			NyaInput::OutputReplay("replay/replay2.rep");
		if (select == 3)
			NyaInput::OutputReplay("replay/replay3.rep");
		if (select == 4)
			NyaInput::OutputReplay("replay/replay4.rep");
	}

	//******************
	// �C�x���g�̍X�V
	//******************
	if (NyaInput::IsPressKey(eINPUT::ENTER) && select == 5)
		event_next_ = eEVENT::TITLE;
}

/**
 @param ���v���C�̕ۑ������Ȃ��֐�
 @note
  �t�H���g�̓^�C�g����ʂ𗬗p
  �R���e�j���[���Ă�����S�Ẵ~�b�V�����N���A���NotSaveReplay()���Ă΂��B
**/
void NyaWindow::NotSaveReplay(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	if (event_ != eEVENT::NOT_REPLAY_SAVE)
		return;

	// �܂��A�C���^�[�t�F�[�X�̏����������Ă���
	NyaInterface::Init();

	NyaString::Write("window_title_font", white, 32, 100, "�R���e�j���[�����̂�");
	NyaString::Write("window_title_font", white, 32, 150, "���v���C�̕ۑ��͂ł��܂���");

	//**************************
	// �I���̑I������\��
	//**************************
	NyaString::Write("window_title_font", white, 32, 250, "PRESS ENTER");

	//******************
	// �C�x���g�̍X�V
	//******************
	if (NyaInput::IsPressKey(eINPUT::ENTER))
		event_next_ = eEVENT::TITLE;
}

/**
@brief �I�[�v�j���O�̏���������֐�
@note
 �I�[�v�j���O���o�^����ĂȂ��Ƃ��͉����������̃C�x���g�ɑJ�ڂ���
**/
void NyaWindow::Opening(void)
{
	switch(event_)
	{
		case eEVENT::OPENING_LOAD:
			if (child_.opening_ == nullptr)
				event_next_ = eEVENT::MISSION_CREATE;
			else
			{
				child_.opening_->Load();
				event_next_ = eEVENT::OPENING_RUN;
			}
			break;
		case eEVENT::OPENING_RUN:
			child_.opening_->Run();
		if (NyaInput::IsPressKey(eINPUT::ENTER))
			event_next_ = eEVENT::OPENING_DELETE;
			break;
		case eEVENT::OPENING_DELETE:
			child_.opening_->Delete();
			event_next_ = eEVENT::MISSION_CREATE;
			break;
	}
}


/**
 @brief �^�C�g����ʂ̏���������֐�
**/
void NyaWindow::Title(void)
{
	int x, y;
	string date, seed, title;
	ifstream ifs;
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	tuple<int, int, int> red = make_tuple(255, 0, 0);
	static int select = 0;
	InterfaceHandleSkill* ihandle_mission_skill = NyaInterface::GetHandleSkill();

	if (event_ != eEVENT::TITLE)
		return;

	//******************
	// �I���̕\��
	//******************
	if (NyaInput::IsPressKey(eINPUT::DOWN))
		select = (select == 5) ? 0 : select + 1;
	if (NyaInput::IsPressKey(eINPUT::UP))
		select = (select == 0) ? 5 : select - 1;
	x = 60;
	y = (select + 1) * 100;
	if (select == 5)
		y += 40;
	NyaString::Write("window_title_font", red, x, y - 40, "��");

	//******************
	// �^�C�g���̕\��
	//******************
	x = 60;
	y = 100;
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "mission");
	NyaString::Write("window_title_font", white, x + 180, y - 40, "%s", "..." + NyaInterface::GetHandleTitle()->name_.str());

	//***********************
	// ���v���C�̗L����\��
	//***********************
	y += 100;
	ifs.open("replay/replay1.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay1");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		getline(ifs, title);
		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay1.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();
	y += 100;
	ifs.open("replay/replay2.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay2");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		getline(ifs, title);
		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay2.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();
	y += 100;
	ifs.open("replay/replay3.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay3");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		getline(ifs, title);
		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay3.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();
	y += 100;
	ifs.open("replay/replay4.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay4");
	if (ifs.is_open())
	{
		getline(ifs, seed);
		getline(ifs, date);
		getline(ifs, title);
		NyaString::Write("window_title_font", white, x + 180, y - 40, "..." + title);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay4.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();

	//******************
	// �I���̕\��
	//******************
	y += (100 + 40);
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "END");

	//***********************************************************************************
	// �I�������肳�ꂽ
	// �C�x���g��J�ڂ����邪�A�I���������v���C�t�@�C�������݂��Ȃ��Ƃ��͑J�ڂ��Ȃ�
	//***********************************************************************************
	if (NyaInput::IsPressKey(eINPUT::ENTER))
	{	
		// �X�L����UI���N���A
		// child_.mission_collection_[0]����~�b�V�����J�n
		ihandle_mission_skill->Clear();	
		child_.mission_index_ = 0;

		// �~�b�V�����̊J�n�Ȃ痐���̏������Ǝ����̎擾�������Ȃ�
		// ���v���C�̊J�n�Ȃ烊�v���C�t�@�C����ǂݍ���
		// (���v���C�t�@�C���ǂݍ��݊֐����ŗ����̏������������)
		// �C�x���g�̍X�V�������Ȃ�
		switch (select)
		{
		case 0:
			NyaInput::Init();	
			event_next_ = eEVENT::OPENING_LOAD;
			break;
		case 1:
			if (NyaInput::InputReplay("replay/replay1.rep"))
				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
			else
				event_next_ = eEVENT::TITLE;
			break;
		case 2:
			if (NyaInput::InputReplay("replay/replay2.rep"))
				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
			else
				event_next_ = eEVENT::TITLE;
			break;
		case 3:
			if (NyaInput::InputReplay("replay/replay3.rep"))
				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
			else
				event_next_ = eEVENT::TITLE;
			break;
		case 4:
			if (NyaInput::InputReplay("replay/replay4.rep"))
				event_next_ = eEVENT::MISSION_REPLAY_CREATE;
			else
				event_next_ = eEVENT::TITLE;
			break;
		case 5:
			event_next_ = eEVENT::WINDOW_CLOSE;
			break;
		}
	}
}




/**
 @param FPS�X�V�֐�
 @note
  �t���[�����[�g�̏���������
**/
void NyaWindow::WaitFPS(int x, int y)
{

	static	int frame_ave_ = 0;					//�t���[�����[�g����
	static	int wtime_ave_ = 0;					//wait���ԕ���
	static	int ltime_ave_ = 0;					//loop���ԕ���
	static	int frame_[FPS_MAX] = {};			//�t���[�����[�g
	static	int ltime_[FPS_MAX] = {};			//loop����
	static	int wtime_[FPS_MAX] = {};			//wait����
	static	int prev_time_ = 0;					//1�t���[���O�̎���
	static	int frame_count_ = 0;				//���݂̃t���[��(0�`FPS_MAX-1)
	static unsigned int all_frame_count_ = 0;	//�t���[�������J�E���g��������ϐ�
	const tuple<int, int, int> white = make_tuple(255, 255, 255);



//#ifdef __DEBUG__
//	if (frame_ave_ != 0) 
//	{
//		NyaString::Write("fps_font", white, x, y, "fps[%.1f fps]", 1000.0 / (double)frame_ave_);
//		NyaString::Write("fps_font", white, x + 100, y, "loop[%d ms]", ltime_ave_);
//		NyaString::Write("fps_font", white, x + 180, y, "wait[%d ms]", wtime_ave_);
//	}
//#else
	if (frame_ave_ != 0)
		NyaString::Write("fps_font", white, x + 170, y, "fps[%.1f fps]", 1000.0 / (double)frame_ave_);
//#endif


	frame_count_ = ++all_frame_count_ % FPS_MAX;
	/*���ώZ�o*/
	if (frame_count_ == FPS_MAX - 1)
	{
		frame_ave_ = 0;
		ltime_ave_ = 0;
		wtime_ave_ = 0;
		for (int i = 0; i < FPS_MAX; i++)
		{
			frame_ave_ += frame_[i];
			ltime_ave_ += ltime_[i];
			wtime_ave_ += wtime_[i];
		}
		frame_ave_ = frame_ave_ / FPS_MAX;
		ltime_ave_ = ltime_ave_ / FPS_MAX;
		wtime_ave_ = wtime_ave_ / FPS_MAX;
	}

	ltime_[frame_count_] = GetNowCount() - prev_time_;
	/*wait����*/
	wtime_[frame_count_] = (1000 / FPS_MAX) - ltime_[frame_count_];
	if (0 < wtime_[frame_count_])
		Sleep(wtime_[frame_count_]);
	frame_[frame_count_] = GetNowCount() - prev_time_;
	prev_time_ = GetNowCount();
}


