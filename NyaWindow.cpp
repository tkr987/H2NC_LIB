#include "DxLib.h"
#include "DebugPrint.h"
#include "NyaAttack.h"
#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
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
	delete nya_attack_;
	delete nya_design_;
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
	SetMainWindowText("H2NC++LIB v56");		// �^�C�g��
	ChangeWindowMode(true);					// �E�B���h�E���[�h
	SetGraphMode(1280, 720, 32);			// ��ʃT�C�Y, �F��
	if (DxLib_Init() == -1)					// ������
		return -1;							//
	SetAlwaysRunFlag(true);					// ��A�N�e�B�u��Ԃł����삳����
	SetUseDivGraphFlag(false);				// �O���t�B�b�N�`�敪�����@
	SetDrawScreen(DX_SCREEN_BACK);			// �`���O���t�B�b�N�̈�̎w��

	// �R���X�g���N�^��DXLIB�֐��𗘗p����\��������̂�
	// DXLIB��������ɃC���X�^���X�𐶐�����K�v������B
	nya_attack_ = new NyaAttack;
	nya_design_ = new NyaDesign;
	nya_graphic_ = new NyaGraphic;
	nya_posision_ = new NyaPosition;

	// �ϐ�������
	set_user_ = false;

	return 0;
}


void NyaWindow::Run(void)
{
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1) {
		
		ClearDrawScreen();

		nya_attack_->Run();
		nya_design_->Run();
		nya_graphic_->Run();
		nya_posision_->Run();
		if (set_user_) {
			nya_user_->Action();
			nya_user_->Draw();
		}

		NyaInput::Run();
		NyaString::Run();
		DebugPrint::Run();

		FpsUpdater();

		ScreenFlip();
	}

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
void NyaWindow::FpsUpdater(void)
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


#ifdef __DEBUG__
//	DebugPrint::SetData(615, 220, "frames_: %d", fpsall++);
	if (frame_ave_ != 0) {
		DebugPrint::SetData(1180, 660, "fps[%.1f]", 1000.0 / (double)frame_ave_);
		DebugPrint::SetData(1180, 680, "loop[%dms]", ltime_ave_);
		DebugPrint::SetData(1180, 700, "wait[%dms]", wtime_ave_);
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

