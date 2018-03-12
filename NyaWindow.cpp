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

	if (nya_user_.first)
		delete nya_user_.second;


	for (vector<NyaMission*>::iterator it = nya_mission_vector_.begin(); it != nya_mission_vector_.end(); ++it)
		delete *it;

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
	nya_mission_vector_.push_back(mission);
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
	nya_user_.first = true;
	nya_user_.second = user;
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
	SetMainWindowText("H2NC++LIB v60");		// �^�C�g��
	ChangeWindowMode(true);					// �E�B���h�E���[�h
	SetGraphMode(1280, 720, 32);			// ��ʃT�C�Y, �F��
	if (DxLib_Init() == -1)					// ������
		return -1;							//
	SetAlwaysRunFlag(true);					// ��A�N�e�B�u��Ԃł����삳����
	SetUseDivGraphFlag(false);				// �O���t�B�b�N�`�敪�����@
	SetDrawScreen(DX_SCREEN_BACK);			// �`���O���t�B�b�N�̈�̎w��

	// �R���X�g���N�^��DXLIB�֐��𗘗p����\��������̂�
	// DXLIB��������ɃC���X�^���X�𐶐�����K�v������B
	nya_design_ = new NyaDesign;
	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;

	// �ϐ�������
	title_name_ = title;
	nya_user_.first = false;
	
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


	// �e�v���Z�X����
	// �v���Z�X�̕ύX�͂����ł����Ȃ�
	nya_design_->SetProcess(ePROCESS::TITLE);
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1) {

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
#endif

		ClearDrawScreen();

		switch (nya_design_->GetProcess()) 
		{
		case ePROCESS::TITLE:
			nya_mission_index_ = 0;
			RunTitle();
			if (NyaInput::IsPressKey(eINPUT::ENTER))
				nya_design_->SetProcess(ePROCESS::MISSION_LOAD);
			break;
		case ePROCESS::MISSION_LOAD:
			if (nya_mission_vector_.size() != 0)
			{ 
				nya_mission_vector_[nya_mission_index_]->Load();
				nya_mission_vector_[nya_mission_index_]->Run();
			}
			nya_design_->SetProcess(ePROCESS::MISSION_RUN);
			break;
		case ePROCESS::MISSION_RUN:
			if (nya_user_.first) 
			{
				nya_user_.second->Action();
				nya_user_.second->Draw();
			}
			if (nya_mission_vector_.size() != 0)
				nya_mission_vector_[nya_mission_index_]->Run();
			break;
		case ePROCESS::MISSION_STOP:
			if (nya_user_.first) 
				nya_user_.second->Draw();
			if (nya_mission_vector_.size() != 0)
				nya_mission_vector_[nya_mission_index_]->Run();
		break;
		case ePROCESS::CLEAR:
			nya_mission_index_++;
			break;
		case ePROCESS::CONTINUE:
			break;
		case ePROCESS::OVER:
			break;
		}

#ifdef __DEBUG__
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 620, "[600, 620] NyaWindow Process %d msec", (int)debug_time_msec);
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_device_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 640, "[600, 640] NyaDevice::Run() %d msec", (int)debug_time_msec);
#else 
		nya_device_->Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_effect_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 660, "[600, 660] NyaEffect::Run() %d msec", (int)debug_time_msec);
#else 
		nya_effect_->Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_graphic_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 680, "[600, 680] NyaGraphic::Run() %d msec", (int)debug_time_msec);
#else 
		nya_graphic_->Run();
#endif

#ifdef __DEBUG__
		debug_time_start = std::chrono::system_clock::now();
		nya_position_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_font", white, 600, 700, "[600, 700] NyaPosition::Run() %d msec", (int)debug_time_msec);
#else 
		nya_position_->Run();
#endif

		NyaInput::Run();
		nya_design_->Run();
		NyaString::Run();
	
		ScreenFlip();
	}

}

void NyaWindow::RunTitle(void)
{
	static tuple<int, int, int> white = make_tuple(255, 37, 37);

	NyaString::Write("window_title_font", white, 100, 70, "title [%s] start", title_name_);
	NyaString::Write("window_title_font", white, 50, 70, "=>");
}

