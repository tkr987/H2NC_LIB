#include <chrono>
#include <fstream>
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
	delete nya_device_;
	delete nya_effect_;
	delete nya_position_;

	DxLib_End();
}

/**
@brief �~�b�V������ǉ�����֐�
@param mission �ǉ�����~�b�V����
@note
 NyaWindow�̎q�I�u�W�F�N�g�Ƃ��ă~�b�V�������ǉ������B
 �q�I�u�W�F�N�g�͐e�I�u�W�F�N�g(NyaWindow)��delete�����Ƃ��Ɏ����I�ɍ폜����邪�A
 ���C�u�����g�p�Ҏ��g�ō폜�������ꍇ��NyaWindow::Delete()���g���B
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
 �K���ŏ��Ɉ�x�Ăяo�����ƁB
**/
int NyaWindow::Init(string title)
{
	// *****************
	//  dxlib������
	// *****************
	SetMainWindowText("H2NC++LIB v67");		// �^�C�g��
	ChangeWindowMode(true);					// �E�B���h�E���[�h
	SetGraphMode(1280, 720, 32);			// ��ʃT�C�Y, �F��
	if (DxLib_Init() == -1)					// ������
		return -1;							//
	SetAlwaysRunFlag(true);					// ��A�N�e�B�u��Ԃł����삳����
	SetUseDivGraphFlag(false);				// �O���t�B�b�N�`�敪�����@
	SetDrawScreen(DX_SCREEN_BACK);			// �`���O���t�B�b�N�̈�̎w��

	// �R���X�g���N�^��DXLIB�֐��𗘗p����\��������̂�
	// DXLIB��������ɃC���X�^���X�𐶐�����K�v������B
	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	NyaInterface::Init();
	nya_position_ = new NyaPosition;
	
	// NyaWindow�̊e��ݒ�
	title_ = title;
	NyaString::SettingFont("window_title_font", 30, 4);
	NyaString::SettingFont("debug_font", 10, 2);

	return 0;
}


void NyaWindow::Run(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);
	static std::chrono::system_clock::time_point debug_time_start, debug_time_end;
	static long long debug_time_msec;


	// *********************************************************
	// �e�C�x���g����
	// �C�x���g�̕ύX��NyaWindow::RunEventUpdate()�ł����Ȃ�
	// *********************************************************
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1 && event_ != eEVENT::WINDOW_CLOSE)
	{
		// ***********************
		// NyaWindow �����o�֐�
		// �^�C�g������
		// �~�b�V��������
		// ���v���C�̕ۑ�
		// ***********************
		Title();
		Mission();
		SaveReplay();


		// ******************
		// ���N���X�̏���
		// ******************

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_device_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 620, "[600, 620] NyaDevice::Run() %d msec", (int)debug_time_msec);
#else 
		nya_device_->Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_effect_->Run();
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
		nya_sound::Run();
		NyaInput::Run();
		nya_design_->Run();
		NyaString::Run();
#endif

		// *************
		// ��ʍX�V
		// *************
		ScreenFlip();
		ClearDrawScreen();

		// ***********************
		// NyaWindow �����o�֐�
		// �C�x���g�X�V
		// �t���[�����Ԃ�҂�
		// ***********************
		UpdateEvent();
		WaitFPS(1180, 660);
	}

}


void NyaWindow::Mission(void)
{
	if (!child_mission_.valid_)
		return;

	// �C�x���g���Ƀ~�b�V�����̎q�I�u�W�F�N�g�ł���user, target, backgraound�̏����������Ȃ�
	if (child_mission_.index_ < child_mission_.mission_collection_.size())
		child_mission_.mission_collection_[child_mission_.index_]->Run(event_);

	switch (event_) 
	{	// �C���f�b�N�X�̍X�V
	case eEVENT::MISSION_INITIALIZE:
	case eEVENT::MISSION_REPLAY_INITIALIZE:
		child_mission_.index_ = 0;
		break;
	case eEVENT::MISSION_DELETE:
	case eEVENT::MISSION_REPLAY_DELETE:
			child_mission_.index_++;
		break;
	}
}

/**
@param ���v���C�̕ۑ�������֐�
@note
 �t�H���g�̓^�C�g����ʂ𗬗p
**/void NyaWindow::SaveReplay(void)
{
	string pass;
	int x, y;
	ifstream ifs;
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	tuple<int, int, int> red = make_tuple(255, 0, 0);
	static int select = 1;

	if (event_ != eEVENT::REPLAY_SAVE)
		return;

	// ************
	// �I��
	// ************
	if (NyaInput::IsPressKey(eINPUT::DOWN))
		select = (select == 5) ? 1 : select + 1;
	if (NyaInput::IsPressKey(eINPUT::UP))
		select = (select == 1) ? 5 : select - 1;
	x = 60;
	y = 100 + select * 100;
	NyaString::Write("window_title_font", red, x, y - 40, "��");


	// ************
	// �^�C�g��
	// ************
	x = 60;
	y = 100;
	NyaString::Write("window_title_font", white, x + 70, y - 40, "SAVE REPLAY");

	// ************
	// ���v���C
	// ************
	y += 100;
	ifs.open("replay/repay1.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay1");
	if (ifs.is_open())
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "replay1.rep");
	}
	else
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	}
	ifs.close();
	y += 100;
	ifs.open("replay/repay2.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay2");
	if (ifs.is_open())
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "replay2.rep");
	}
	else
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	}
	ifs.close();
	y += 100;
	ifs.open("replay/repay3.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay3");
	if (ifs.is_open())
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "replay3.rep");
	}
	else
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	}
	y += 100;
	ifs.close();
	ifs.open("replay/repay4.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay4");
	if (ifs.is_open())
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "replay4.rep");
	}
	else
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	}
	ifs.close();

	// ************
	// �I��
	// ************
	y += 100;
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "END");

	// �t�@�C���ւ̏�������
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

	// �C�x���g�X�V
	if (NyaInput::IsPressKey(eINPUT::ENTER) && select == 5)
		event_ = eEVENT::MISSION_FINALIZE;
}

/**
 @brief �^�C�g����ʂ̏���������֐�
**/
void NyaWindow::Title(void)
{
	int x, y;
	ifstream ifs;
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	tuple<int, int, int> red = make_tuple(255, 0, 0);
	static int select = 1;

	if (event_ != eEVENT::TITLE)
		return;

	//************
	// �I��
	//************
	if (NyaInput::IsPressKey(eINPUT::DOWN))
		select = (select == 6) ? 1 : select + 1;
	if (NyaInput::IsPressKey(eINPUT::UP))
		select = (select == 1) ? 6 : select - 1;
	x = 60;
	y = select * 100;
	NyaString::Write("window_title_font", red, x, y - 40, "��");


	//************
	// �^�C�g��
	//************
	x = 60;
	y = 100;
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "mission title");
	NyaString::Write("window_title_font", white, x + 70, y, "%s", title_);

	//************
	// ���v���C
	//************
	y += 100;
	ifs.open("replay/repay1.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay1");
	if (ifs.is_open())
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "replay1.rep");
	}
	else
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	}
	ifs.close();
	y += 100;
	ifs.open("replay/repay2.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay2");
	if (ifs.is_open())
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "replay2.rep");
	}
	else
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	}
	ifs.close();
	y += 100;
	ifs.open("replay/repay3.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay3");
	if (ifs.is_open())
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "replay3.rep");
	}
	else
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	}
	ifs.close();
	y += 100;
	ifs.open("replay/repay4.rep");
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "replay4");
	if (ifs.is_open())
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "replay4.rep");
	}
	else
	{
		NyaString::Write("window_title_font", white, x + 70, y, "%s", "no_replay");
	}
	ifs.close();

	//************
	// �I��
	//************
	y += 100;
	NyaString::Write("window_title_font", white, x, y - 40, "��");
	NyaString::Write("window_title_font", white, x + 70, y - 40, "END");

	//*****************
	// �I���̌���
	//*****************
	if (NyaInput::IsPressKey(eINPUT::ENTER))
	{
		if (select == 1)
		{
			event_ = eEVENT::MISSION_INITIALIZE;
		}
		else if (select == 2)
		{
			NyaInput::InputFile("replay/replay1.rep");
			event_ = eEVENT::MISSION_REPLAY_INITIALIZE;
		}
		else if (select == 3)
		{
			NyaInput::InputFile("replay/replay2.rep");
			event_ = eEVENT::MISSION_REPLAY_INITIALIZE;
		}
		else if (select == 4)
		{
			NyaInput::InputFile("replay/replay3.rep");
			event_ = eEVENT::MISSION_REPLAY_INITIALIZE;
		}
		else if (select == 5)
		{
			NyaInput::InputFile("replay/replay4.rep");


			event_ = eEVENT::MISSION_REPLAY_INITIALIZE;
		}
		else 
		{
			event_ = eEVENT::WINDOW_CLOSE;
		}
	}
}


void NyaWindow::UpdateEvent(void)
{
	InterfaceHandleMissionClear* ihandle_mission_clear;
	
	switch (event_) 
	{
	case eEVENT::MISSION_INITIALIZE:
		event_ = eEVENT::MISSION_CREATE;
		break;
	case eEVENT::MISSION_CREATE:
		event_ = eEVENT::MISSION_RUN;
		break;
	case eEVENT::MISSION_RUN:
		ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
		if (ihandle_mission_clear->valid_)
			event_ = eEVENT::MISSION_CLEAR;
		break;
	case eEVENT::MISSION_CONTINUE:
		break;
	case eEVENT::MISSION_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::ENTER))
		{
			ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
			ihandle_mission_clear->valid_ = false;
			event_ = eEVENT::MISSION_DELETE;
		}
		break;
	case eEVENT::MISSION_DELETE:
		if (child_mission_.index_ + 1 != child_mission_.mission_collection_.size())
		{
			event_ = eEVENT::REPLAY_SAVE;
		}
		else
		{
			event_ = eEVENT::MISSION_DELETE;
		}
		break;
	case eEVENT::MISSION_FINALIZE:
		event_ = eEVENT::TITLE;
		break;
	case eEVENT::MISSION_REPLAY_INITIALIZE:
		event_ = eEVENT::MISSION_REPLAY_CREATE;
		break;
	case eEVENT::MISSION_REPLAY_CREATE:
		event_ = eEVENT::MISSION_REPLAY_RUN;
		break;
	case eEVENT::MISSION_REPLAY_RUN:
		ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
		if (ihandle_mission_clear->valid_)
			event_ = eEVENT::MISSION_REPLAY_CLEAR;
		break;
	case eEVENT::MISSION_REPLAY_OVER:
		break;
	case eEVENT::MISSION_REPLAY_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::ENTER))
		{
			ihandle_mission_clear = NyaInterface::GetHandleMissionClear();
			ihandle_mission_clear->valid_ = false;
			event_ = eEVENT::MISSION_REPLAY_DELETE;
		}
		break;
	case eEVENT::MISSION_REPLAY_DELETE:
		if (child_mission_.index_ + 1 != child_mission_.mission_collection_.size())
		{
			event_ = eEVENT::MISSION_REPLAY_FINALIZE;
		}
		else
		{
			event_ = eEVENT::MISSION_REPLAY_CREATE;
		}
		break;
	case eEVENT::MISSION_REPLAY_FINALIZE:
		event_ = eEVENT::TITLE;
		break;
	}
}



/**
@param FPS�X�V�֐�
@note
 �t���[�����Ԃ�҂�
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
	if (frame_ave_ != 0) {
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
