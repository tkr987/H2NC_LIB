#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <tuple>
#include "DxLib.h"
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaInterface.h"
#include "NyaMission.h"
#include "NyaPosition.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "NyaUser.h"
#include "NyaWindow.h"

#define __DEBUG__

using namespace std;
using namespace std::experimental::filesystem;
using namespace H2NLIB;


NyaWindow::NyaWindow()
{
	// �����o�ϐ��̏�����
	event_ = eEVENT::TITLE;
}


NyaWindow::~NyaWindow()
{
	// �e�I�u�W�F�N�g��NyaWindow��j������Ƃ��Ɏq�I�u�W�F�N�g��j������
	for (auto& e : child_mission_.mission_collection_)
		delete e;

	// nya class delete
	delete nya_position_;

	DxLib_End();
}

/**
 @brief �~�b�V������ǉ�����֐�
 @param mission �ǉ�����~�b�V����
 @note
  NyaWindow�̎q�I�u�W�F�N�g�Ƃ��ă~�b�V�������ǉ������B
**/
void NyaWindow::AddChild(NyaMission* mission)
{
	child_mission_.valid_ = true;
	child_mission_.mission_collection_.push_back(mission);
}


/**
 @brief �������֐�
 @param name �^�C�g���̐ݒ�
 @note
  �K���ŏ��Ɉ�x�Ăяo������
**/
int NyaWindow::Init(string title)
{
	// *****************
	//  dxlib������
	// *****************
	SetMainWindowText("Happy 2 Nya C++ DXLIB wrapper v68");		// �^�C�g��
	ChangeWindowMode(true);										// �E�B���h�E���[�h
	SetGraphMode(1280, 720, 32);								// ��ʃT�C�Y, �F��
	if (DxLib_Init() == -1)										// ������
		return -1;												//
	SetAlwaysRunFlag(true);										// ��A�N�e�B�u��Ԃł����삳����
	SetUseDivGraphFlag(false);									// �O���t�B�b�N�`�敪�����@
	SetDrawScreen(DX_SCREEN_BACK);								// �`���O���t�B�b�N�̈�̎w��

	// �f�B���N�g���쐬
	create_directory("replay");

	// �R���X�g���N�^��DXLIB�֐��𗘗p����\��������̂�
	// DXLIB��������ɃC���X�^���X�𐶐�����K�v������B
	NyaInterface::Init();
	nya_position_ = new NyaPosition;
	
	// NyaWindow�̊e��ݒ�
	title_ = title;
	NyaString::SettingFont("window_title_font", 30, 4);
	NyaString::SettingFont("debug_font", 10, 2);

	return 0;
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

		//*********************************************************************
		// �C�x���g�̍X�V�Ɏg���ϐ���enum_zero�ŏ��������Ă���
		// NyaWindow�̃����o�֐���event_next_�̒l��enum_zero�ȊO�ɂ����Ƃ�
		// Run()�̍Ō�ɃC�x���g���X�V���鏈���������Ȃ�
		//*********************************************************************
		event_next_ = eEVENT::enum_zero;

		//***********************
		// NyaWindow �����o�֐�
		// �^�C�g�����
		// �~�b�V��������
		// ���v���C�ۑ�
		//***********************
		Title();
		Mission();
		SaveReplay();
		NotSaveReplay();

		//*******************
		// ���C�u�����̏���
		//*******************

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaDevice::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 620, "[600, 620] NyaDevice::Run() %d msec", (int)debug_time_msec);
#else 
		nya_device_->Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaEffect::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 640, "[600, 640] NyaEffect::Run() %d msec", (int)debug_time_msec);
#else 
		nya_effect_->Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaGraphic::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 660, "[600, 660] NyaGraphic::Run() %d msec", (int)debug_time_msec);
#else 
		nya_graphic::Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_position_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 680, "[600, 680] NyaPosition::Run() %d msec", (int)debug_time_msec);
#else 
		nya_position_->Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		NyaInput::Run(event_);
		NyaInterface::Run();
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

		//*****************************
		// ��ʍX�V
		// �t���[�����[�g�̏���
		//*****************************
		ScreenFlip();
		ClearDrawScreen();
		WaitFPS(1180, 660);

		//*******************************************************************************
		// enum_zero�łȂ��Ȃ�NyaWindow�̃����o�֐���event_next_��ύX�����Ƃ�������
		// enum_zero�łȂ��Ȃ�C�x���g�̍X�V������
		//*******************************************************************************
		if (event_next_ != eEVENT::enum_zero)
			event_ = event_next_;
	}

}

/**
 @param �~�b�V�����̏���������֐�
 @note
  �~�b�V�������o�^����ĂȂ��ꍇ�͉������Ȃ��Ń^�C�g���ɖ߂�
**/
void NyaWindow::Mission(void)
{
	InterfaceHandleMissionAllOver* ihandle_mission_all_over;
	InterfaceHandleMissionClear* ihandle_mission_clear;
	InterfaceHandleMissionEx* ihandle_mission_ex;

	if (!child_mission_.valid_)
	{
		event_next_ = eEVENT::TITLE;
		return;
	}

	// �C�x���g���Ƀ~�b�V�����̎q�I�u�W�F�N�g�ł���user, target, backgraound�̏����������Ȃ�
	if (child_mission_.index_ < child_mission_.mission_collection_.size())
		child_mission_.mission_collection_[child_mission_.index_]->Run(event_);

	switch (event_) 
	{	// �C���f�b�N�X�̍X�V
	case eEVENT::TITLE:
		// �Œ�ł�1�t���[���̓^�C�g����ʂɂ���̂�index�͕K���X�V�����
		child_mission_.index_ = 0;
		break;
	case eEVENT::MISSION_DELETE:
	case eEVENT::MISSION_REPLAY_DELETE:
		child_mission_.index_++;
		break;
	}

	switch (event_) 
	{	// �C�x���g�̍X�V
	case eEVENT::MISSION_CREATE:
		event_next_ = eEVENT::MISSION_RUN;
		break;
	case eEVENT::MISSION_RUN:
		ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
		if (ihandle_mission_clear->valid_)
			event_next_ = eEVENT::MISSION_CLEAR;
		ihandle_mission_all_over = NyaInterface::GetHandleMissionAllOver();
		if (ihandle_mission_all_over->valid_)
			event_next_ = eEVENT::MISSION_ALL_CLEAR;
		break;
	case eEVENT::MISSION_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::ENTER))
		{
			ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
			ihandle_mission_clear->valid_ = false;
			ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
			ihandle_mission_ex->valid_ = false;
			event_next_ = eEVENT::MISSION_DELETE;
		}
		break;
	case eEVENT::MISSION_ALL_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::ENTER))
		{
			ihandle_mission_all_over = NyaInterface::GetHandleMissionAllOver();
			ihandle_mission_all_over->valid_ = false;
			ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
			ihandle_mission_ex->valid_ = false;
			event_next_ = eEVENT::REPLAY_SAVE;		
		}
		break;
	case eEVENT::MISSION_DELETE:
		if (child_mission_.index_ < child_mission_.mission_collection_.size())
			event_next_ = eEVENT::MISSION_CREATE;
		else
			event_next_ = eEVENT::TITLE;
		break;
	//**************************************
	// �ȉ��̓��v���C�̍Đ����̃C�x���g
	//**************************************
	case eEVENT::MISSION_REPLAY_CREATE:
		event_next_ = eEVENT::MISSION_REPLAY_RUN;
		break;
	case eEVENT::MISSION_REPLAY_RUN:
		ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
		if (ihandle_mission_clear->valid_)
			event_next_ = eEVENT::MISSION_REPLAY_CLEAR;
		ihandle_mission_all_over = NyaInterface::GetHandleMissionAllOver();
		if (ihandle_mission_all_over->valid_)
			event_next_ = eEVENT::MISSION_REPLAY_ALL_CLEAR;
		break;
	case eEVENT::MISSION_REPLAY_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::ENTER))
		{
			ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
			ihandle_mission_clear->valid_ = false;
			ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
			ihandle_mission_ex->valid_ = false;
			event_ = eEVENT::MISSION_REPLAY_DELETE;
		}
		break;
	case eEVENT::MISSION_REPLAY_ALL_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::ENTER))
		{
			ihandle_mission_all_over = NyaInterface::GetHandleMissionAllOver();
			ihandle_mission_all_over->valid_ = false;
			ihandle_mission_ex = NyaInterface::GetHandleMissionEx();
			ihandle_mission_ex->valid_ = false;
			event_next_ = eEVENT::MISSION_REPLAY_DELETE;
		}
		break;
	case eEVENT::MISSION_REPLAY_DELETE:
		if (child_mission_.index_ < child_mission_.mission_collection_.size())
			event_next_ = eEVENT::MISSION_REPLAY_CREATE;
		else
			event_next_ = eEVENT::TITLE;
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
	string date;
	ifstream ifs;
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	tuple<int, int, int> red = make_tuple(255, 0, 0);
	static int select = 1;

	if (event_ != eEVENT::REPLAY_SAVE)
		return;

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
		getline(ifs, date);
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
		getline(ifs, date);
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
		getline(ifs, date);
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
		getline(ifs, date);
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
			NyaInput::OutputFile("replay/replay1.rep");
		if (select == 2)
			NyaInput::OutputFile("replay/replay2.rep");
		if (select == 3)
			NyaInput::OutputFile("replay/replay3.rep");
		if (select == 4)
			NyaInput::OutputFile("replay/replay4.rep");
	}

	//******************
	// �C�x���g�̍X�V
	//******************
	if (NyaInput::IsPressKey(eINPUT::ENTER) && select == 5)
		event_next_ = eEVENT::MISSION_DELETE;
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
 @brief �^�C�g����ʂ̏���������֐�
**/
void NyaWindow::Title(void)
{
	int x, y;
	string date;
	ifstream ifs;
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	tuple<int, int, int> red = make_tuple(255, 0, 0);
	static int select = 0;

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
	NyaString::Write("window_title_font", red, x, y - 40, "��");

	//******************
	// �^�C�g���̕\��
	//******************
	x = 60;
	y = 100;
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "mission");
	NyaString::Write("window_title_font", white, x + 70, y, "%s", title_);

	//***********************
	// ���v���C�̗L����\��
	//***********************
	y += 100;
	ifs.open("replay/replay1.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay1");
	if (ifs.is_open())
	{
		getline(ifs, date);
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
		getline(ifs, date);
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
		getline(ifs, date);
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
		getline(ifs, date);
		NyaString::Write("window_title_font", white, x + 70, y, "%s", date + " replay4.rep");
	}
	else
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	ifs.close();

	//******************
	// �I���̕\��
	//******************
	y += 100;
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "END");

	//***********************
	// �I�������肳�ꂽ
	//***********************
	if (NyaInput::IsPressKey(eINPUT::ENTER))
	{	
		// ���v���C�̎��s
		if (select == 1)
			NyaInput::InputFile("replay/replay1.rep");
		else if (select == 2)
			NyaInput::InputFile("replay/replay2.rep");
		else if (select == 3)
			NyaInput::InputFile("replay/replay3.rep");
		else if (select == 4)
			NyaInput::InputFile("replay/replay4.rep");

		switch (select)
		{	// �C�x���g�̍X�V
		case 0:
			event_next_ = eEVENT::MISSION_CREATE;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			event_next_ = eEVENT::MISSION_REPLAY_CREATE;
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
	static tuple<int, int, int> white = make_tuple(255, 255, 255);



#ifdef __DEBUG__
	if (frame_ave_ != 0) 
	{
		NyaString::Write("design_fps_font", white, x, y, "fps[%.1f fps]", 1000.0 / (double)frame_ave_);
		NyaString::Write("design_fps_font", white, x, y + 20, "loop[%d ms]", ltime_ave_);
		NyaString::Write("design_fps_font", white, x, y + 40, "wait[%d ms]", wtime_ave_);
	}
#else
	if (frame_ave_ != 0)
		DebugPrint::SetData(1200, 700, "fps[%.1f]", 1000.0 / (double)frame_ave_);
#endif


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
