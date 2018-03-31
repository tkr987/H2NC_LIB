#include <chrono>
#include <tuple>
#include "DxLib.h"
#include "DebugPrint.h"
#include "NyaDevice.h"
#include "NyaDesign.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
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

}


NyaWindow::~NyaWindow()
{
	delete nya_design_;
	delete nya_device_;
	delete nya_effect_;
	delete nya_graphic_;
	delete nya_position_;
	delete nya_sound_;

	if (ch_user_.valid_)
		delete ch_user_.nya_user_;

	for (auto& it : ch_mission_.nya_mission_vector_)
		delete it;

	DxLib_End();
}

/**
@brief �~�b�V������ǉ�����֐�
@param mission �ǉ�����~�b�V����
@note
 NyaWindow�̎q�I�u�W�F�N�g�Ƃ��ă~�b�V�������ǉ������B
 �q�I�u�W�F�N�g�͐e�I�u�W�F�N�g(NyaWindow)��delete�����Ƃ��Ɏ����I�ɍ폜�����B
 �Ȃ̂ŁA�q�I�u�W�F�N�g���̂�delete�������K�v�͂Ȃ��B
**/
void NyaWindow::AddChMission(NyaMission* mission)
{
	ch_mission_.valid_ = true;
	ch_mission_.index_ = 0;
	ch_mission_.nya_mission_vector_.push_back(mission);
}

/**
@brief ���[�U�[��ǉ�����֐�
@param mission �ǉ����郆�[�U�[
@note
 NyaWindow�̎q�I�u�W�F�N�g�Ƃ��ă��[�U�[���ǉ������B
 �q�I�u�W�F�N�g�͐e�I�u�W�F�N�g(NyaWindow)��delete�����Ƃ��Ɏ����I�ɍ폜�����B
 �Ȃ̂ŁA�q�I�u�W�F�N�g���̂�delete�������K�v�͂Ȃ��B
**/

void NyaWindow::AddChUser(NyaUser* user)
{
	ch_user_.valid_ = true;
	ch_user_.nya_user_ = user;
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
	SetMainWindowText("H2NC++LIB v65");		// �^�C�g��
	ChangeWindowMode(true);					// �E�B���h�E���[�h
	SetGraphMode(1280, 720, 32);			// ��ʃT�C�Y, �F��
	if (DxLib_Init() == -1)					// ������
		return -1;							//
	SetAlwaysRunFlag(true);					// ��A�N�e�B�u��Ԃł����삳����
	SetUseDivGraphFlag(false);				// �O���t�B�b�N�`�敪�����@
	SetDrawScreen(DX_SCREEN_BACK);			// �`���O���t�B�b�N�̈�̎w��

	// �ϐ�������
	event_ = eEVENT::NUM::TITLE;
	title_name_ = title;

	// �R���X�g���N�^��DXLIB�֐��𗘗p����\��������̂�
	// DXLIB��������ɃC���X�^���X�𐶐�����K�v������B
	nya_design_ = new NyaDesign;
	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
	nya_sound_ = new NyaSound;
	
	// �ݒ�
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
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1) {

		ClearDrawScreen();

		// ****************************
		// �q�I�u�W�F�N�g�̏���
		// ****************************
#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		RunChMission();
		RunChUser();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 600, "[600, 600] NyaWindow::ch_***::Run() %d msec", (int)debug_time_msec);
#else
		RunChMission();
		RunChUser();
#endif

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
		nya_graphic_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 660, "[600, 660] NyaGraphic::Run() %d msec", (int)debug_time_msec);
#else 
		nya_graphic_->Run();
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
		nya_sound_->Run();
		NyaInput::Run();
		nya_design_->Run();
		NyaString::Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 700, "[600, 700] Nya*****::Run() %d msec", (int)debug_time_msec);
#else
		nya_sound_->Run();
		NyaInput::Run();
		nya_design_->Run();
		NyaString::Run();
#endif

		// *************
		// ��ʍX�V
		// *************
		ScreenFlip();

		// ***********************
		// NyaWindow �����o�֐�
		// ***********************
		RunFPS(1180, 660);
		RunEventUpdate();
		RunTitle();

		// *************
		// GAME_END
		// *************
		GameEnd();
	}

}

void NyaWindow::GameEnd(void)
{
	if (event_ != eEVENT::GAME_END)
		return;

	nya_design_->Init();
	nya_graphic_->Init();
	nya_position_->Init();
}

void NyaWindow::RunChMission(void)
{
	if (!ch_mission_.valid_)
		return;

	switch (event_) 
	{
	case eEVENT::GAME_START:
		break;
	case eEVENT::MISSION_START:
		ch_mission_.nya_mission_vector_[ch_mission_.index_]->Load();
		ch_mission_.nya_mission_vector_[ch_mission_.index_]->MissionStart();
		break;
	case eEVENT::MISSION_RUN:
		ch_mission_.nya_mission_vector_[ch_mission_.index_]->MissionRun();
		break;
	case eEVENT::NUM::MISSION_RUN_CONTINUE:
		ch_mission_.nya_mission_vector_[ch_mission_.index_]->MissionRunContinue();
	break;
	case eEVENT::NUM::MISSION_RUN_CLEAR:
		ch_mission_.nya_mission_vector_[ch_mission_.index_]->MissionRunClear();
		break;
	case eEVENT::NUM::MISSION_END:
		ch_mission_.nya_mission_vector_[ch_mission_.index_]->MissionEnd();
		ch_mission_.index_++;
		break;
	case eEVENT::GAME_END:
		ch_mission_.index_ = 0;
		break;
	}
}

void NyaWindow::RunChUser(void)
{
	if (!ch_user_.valid_)
		return;

	switch (event_) 
	{
	case eEVENT::GAME_START:
		ch_user_.nya_user_->GameStart();
		break;
	case eEVENT::MISSION_START:
		ch_user_.nya_user_->MissionStart();
		break;
	case eEVENT::MISSION_RUN:
		ch_user_.nya_user_->Act();
		ch_user_.nya_user_->Draw();
		break;
	case eEVENT::NUM::MISSION_RUN_CLEAR:
	case eEVENT::NUM::MISSION_RUN_CONTINUE:
		ch_user_.nya_user_->Draw();
		break;
	case eEVENT::MISSION_END:
		ch_user_.nya_user_->MissionEnd();
		break;
	case eEVENT::GAME_END:
		ch_user_.nya_user_->GameEnd();
		break;
	}
}

/**
@param FPS�X�V�֐�
**/
void NyaWindow::RunFPS(int x, int y)
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



void NyaWindow::RunTitle(void)
{
	static tuple<int, int, int> white = make_tuple(255, 37, 37);

	switch (event_) 
	{
	case eEVENT::TITLE:
		NyaString::Write("window_title_font", white, 100, 70, "%s start", title_name_);
		NyaString::Write("window_title_font", white, 50, 70, "=>");
		break;
	}
}


void NyaWindow::RunEventUpdate(void)
{
	DesignHandleMissionClear* handle_mission_clear;
	
	switch (event_) 
	{
	case eEVENT::TITLE:
		if (NyaInput::IsPressKey(eINPUT::NUM::ENTER))
			event_ = eEVENT::GAME_START;
		break;
	case eEVENT::GAME_START:
		event_ = eEVENT::MISSION_START;
		break;
	case eEVENT::MISSION_START:
		event_ = eEVENT::MISSION_RUN;
		break;
	case eEVENT::MISSION_RUN:
		handle_mission_clear = nya_design_->GetHandleMissionClear();
		if (handle_mission_clear->valid_)
			event_ = eEVENT::MISSION_RUN_CLEAR;
		break;
	case eEVENT::MISSION_RUN_CONTINUE:
		break;
	case eEVENT::MISSION_RUN_CLEAR:
		if (NyaInput::IsPressKey(eINPUT::NUM::ENTER))
		{
			handle_mission_clear = nya_design_->GetHandleMissionClear();
			handle_mission_clear->valid_ = false;
			event_ = eEVENT::NUM::MISSION_END;
		}
		break;
	case eEVENT::MISSION_END:
		if (ch_mission_.index_ + 1 != ch_mission_.nya_mission_vector_.size())
		{
			event_ = eEVENT::REPLAY_SAVE;
		}
		else
		{
			event_ = eEVENT::NUM::MISSION_START;
		}
		break;
	case eEVENT::REPLAY_SAVE:
		event_ = eEVENT::GAME_END;
		break;
	case eEVENT::GAME_END:
		event_ = eEVENT::TITLE;
		break;
	}
}




