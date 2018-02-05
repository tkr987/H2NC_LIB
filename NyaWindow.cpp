#include <chrono>
#include "DxLib.h"
#include "DebugPrint.h"
#include "NyaDevice.h"
#include "NyaDesign.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "NyaTarget.h"
#include "NyaUser.h"
#include "NyaWindow.h"

#define __DEBUG__
#define FPS_MAX 60


using namespace H2NLIB;


NyaWindow::NyaWindow()
{

}


NyaWindow::~NyaWindow()
{
	delete nya_device_;
	delete nya_design_;
	delete nya_effect_;
	delete nya_graphic_;
	delete nya_posision_;
	DxLib_End();
}

int NyaWindow::Init(void)
{
	//	���������[�N���o
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// *****************
	//  dxlib������
	// *****************
	SetMainWindowText("H2NC++LIB v59");		// �^�C�g��
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
	nya_design_ = new NyaDesign;
	nya_graphic_ = new NyaGraphic;
	nya_posision_ = new NyaPosition;

	// �ϐ�������
	set_user_ = false;
	
	// �ݒ�
	NyaString::SettingFont("debug_window_font", 10, 2);


	return 0;
}


void NyaWindow::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);
	std::chrono::system_clock::time_point debug_time_start, debug_time_end;
	long long debug_time_msec;

	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1) {
		
		ClearDrawScreen();

		nya_device_->Run();
		nya_effect_->Run();

		debug_time_start = std::chrono::system_clock::now();
		nya_graphic_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_window_font", white, 600, 700, "[600, 700] NyaGraphic::Run() %d msec", (int)debug_time_msec);

		nya_posision_->Run();
		if (set_target_) {
			nya_target_->Action();
			nya_target_->Draw();
		}
		if (set_user_) {
			nya_user_->Action();
			nya_user_->Draw();
		}

		NyaInput::Run();
		nya_design_->Run();
		NyaString::Run();

		ScreenFlip();
	}

}

void NyaWindow::SetTarget(NyaTarget* target)
{
	nya_target_ = target;
	set_target_ = true;
}

void NyaWindow::SetUser(NyaUser* user)
{
	nya_user_ = user;
	set_user_ = true;
}

/**
@param FPS�X�V�֐�
@note
**/
//void NyaWindow::FpsUpdater(void)
//{
//
//	static	int frame_ave_ = 0;					//�t���[�����[�g����
//	static	int wtime_ave_ = 0;					//wait���ԕ���
//	static	int ltime_ave_ = 0;					//loop���ԕ���
//	static	int frame_[FPS_MAX] = {};			//�t���[�����[�g
//	static	int ltime_[FPS_MAX] = {};			//loop����
//	static	int wtime_[FPS_MAX] = {};			//wait����
//	static	int prev_time_ = 0;					//1�t���[���O�̎���
//	static	int frame_count_ = 0;				//���݂̃t���[��(0�`FPS_MAX-1)
//	static unsigned int all_frame_count_ = 0;	//�t���[�������J�E���g��������ϐ�
//
//
//#ifdef __DEBUG__
////	DebugPrint::SetData(615, 220, "frames_: %d", fpsall++);
//	if (frame_ave_ != 0) {
//		DebugPrint::SetData(1180, 660, "fps[%.1f]", 1000.0 / (double)frame_ave_);
//		DebugPrint::SetData(1180, 680, "loop[%dms]", ltime_ave_);
//		DebugPrint::SetData(1180, 700, "wait[%dms]", wtime_ave_);
//	}
//#else
//	if (frame_ave_ != 0)
//		DebugPrint::SetData(1200, 700, "fps[%.1f]", 1000.0 / (double)frame_ave_);
//#endif
//
//
//	frame_count_ = ++all_frame_count_ % FPS_MAX;
//	/*���ώZ�o*/
//	if (frame_count_ == FPS_MAX - 1)
//	{
//		frame_ave_ = 0;
//		ltime_ave_ = 0;
//		wtime_ave_ = 0;
//		for (int i = 0; i < FPS_MAX; i++)
//		{
//			frame_ave_ += frame_[i];
//			ltime_ave_ += ltime_[i];
//			wtime_ave_ += wtime_[i];
//		}
//		frame_ave_ = frame_ave_ / FPS_MAX;
//		ltime_ave_ = ltime_ave_ / FPS_MAX;
//		wtime_ave_ = wtime_ave_ / FPS_MAX;
//	}
//
//	ltime_[frame_count_] = GetNowCount() - prev_time_;
//	/*wait����*/
//	wtime_[frame_count_] = (1000 / FPS_MAX) - ltime_[frame_count_];
//	if (0 < wtime_[frame_count_])
//		Sleep(wtime_[frame_count_]);
//	frame_[frame_count_] = GetNowCount() - prev_time_;
//	prev_time_ = GetNowCount();
//}

