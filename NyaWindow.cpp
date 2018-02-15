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
	delete nya_posision_;

	if (nya_user_.first)
		delete nya_user_.second;

	for (auto& it : nya_mission_vector_)
		delete it;

	DxLib_End();
}

void NyaWindow::AddChMission(NyaMission* mission)
{
	nya_mission_vector_.push_back(mission);
}

void NyaWindow::AddChUser(NyaUser* user)
{
	nya_user_.first = true;
	nya_user_.second = user;
}


int NyaWindow::Init(void)
{
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
	nya_design_ = new NyaDesign;
	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	nya_graphic_ = new NyaGraphic;
	nya_posision_ = new NyaPosition;

	// �ϐ�������
	nya_user_.first = false;
	
	// �ݒ�
	NyaString::SettingFont("debug_window_font", 10, 2);


	return 0;
}


void NyaWindow::Run(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);
	static std::chrono::system_clock::time_point debug_time_start, debug_time_end;
	static long long debug_time_msec;


	nya_design_->SetProcess(ePROCESS::TITLE);
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1) {
		
		ClearDrawScreen();

		switch (nya_design_->GetProcess()) {
		case ePROCESS::TITLE:
			nya_mission_index_ = 0;
			nya_design_->SetProcess(ePROCESS::MISSION_LOAD);
			break;
		case ePROCESS::MISSION_LOAD:
			nya_mission_vector_[nya_mission_index_]->Load();
			nya_mission_vector_[nya_mission_index_]->Run();
			nya_design_->SetProcess(ePROCESS::MISSION_RUN);
			break;
		case ePROCESS::MISSION_RUN:
			if (nya_user_.first) {
				nya_user_.second->Action();
				nya_user_.second->Draw();
			}
			nya_mission_vector_[nya_mission_index_]->Run();
			break;
		case ePROCESS::MISSION_STOP:
			if (nya_user_.first) 
				nya_user_.second->Draw();
			nya_mission_vector_[nya_mission_index_]->Run();
		break;
		case ePROCESS::CLEAR:
			nya_mission_index_++;
			break;
		}

		nya_design_->Run();
//		nya_device_->Run();
//		nya_effect_->Run();

		debug_time_start = std::chrono::system_clock::now();
		nya_graphic_->Run();
		debug_time_end = std::chrono::system_clock::now();
		debug_time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(debug_time_end - debug_time_start).count();
		NyaString::Write("debug_window_font", white, 600, 700, "[600, 700] NyaGraphic::Run() %d msec", (int)debug_time_msec);

		nya_posision_->Run();

		NyaInput::Run();
		nya_design_->Run();
		NyaString::Run();
	
		ScreenFlip();
	}

}

