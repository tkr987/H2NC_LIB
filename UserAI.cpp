#include <tuple>
#include "NyaEnum.h"
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaInterface.h"
#include "NyaPosition.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "UserAi.h"

using namespace std;
using namespace H2NLIB;


UserAiDevice::UserAiDevice()
{
	bit_gpx_ = new GraphicPropertyX4;
	bit_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(16, 1,"img/user/bit.png", &bit_gpx_->file_);

	gadget_dpx_ = new DevicePropertyX1;
	gadget_dpx_->collision_range_ = 10;
	gadget_dpx_->move_speed_ = 20;

	gadget_gpx_ = new GraphicPropertyX4;
	gadget_gpx_->extend_rate_ = 0.1;
	NyaGraphic::LoadGraphicFile("img/user/attack.png", &gadget_gpx_->file_);

	effect_epx_ = new EffectPropertyX1;
	effect_epx_->interval_time_frame_ = 2;

	effect_gpx_ = new GraphicPropertyX4;
	effect_gpx_->extend_rate_ = 1.0;
	NyaGraphic::LoadGraphicFile(11, 1, "img/user/attack_effect.png", &effect_gpx_->file_);

	for (int i = 0; i < 6; i++)
		spx_[i] = new SoundPropertyX;
	NyaSound::LoadFile("sound/user_attack1.wav", &spx_[0]->file_);
	NyaSound::LoadFile("sound/user_attack2.wav", &spx_[1]->file_);
	NyaSound::LoadFile("sound/user_attack3.wav", &spx_[2]->file_);
	NyaSound::LoadFile("sound/user_attack4.wav", &spx_[3]->file_);
	NyaSound::LoadFile("sound/user_attack5.wav", &spx_[4]->file_);
	NyaSound::LoadFile("sound/user_attack6.wav", &spx_[5]->file_);
	for (int i = 0; i < 6; i++)
		NyaSound::ChangeVolume(&spx_[i]->file_, 50);

	for (int i = 0; i < 6; i++)
		spx_ex_[i] = new SoundPropertyX;
	NyaSound::LoadFile("sound/user_attack_ex1.wav", &spx_ex_[0]->file_);
	NyaSound::LoadFile("sound/user_attack_ex2.wav", &spx_ex_[1]->file_);
	NyaSound::LoadFile("sound/user_attack_ex3.wav", &spx_ex_[2]->file_);
	NyaSound::LoadFile("sound/user_attack_ex4.wav", &spx_ex_[3]->file_);
	NyaSound::LoadFile("sound/user_attack_ex5.wav", &spx_ex_[4]->file_);
	NyaSound::LoadFile("sound/user_attack_ex6.wav", &spx_ex_[5]->file_);
	for (int i = 0; i < 6; i++)
		NyaSound::ChangeVolume(&spx_ex_[i]->file_, 30);
}

UserAiDevice::~UserAiDevice()
{
	NyaGraphic::DeleteGraphicFile(&bit_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	for (int i = 0; i < 6; i++)
		NyaSound::DeleteSoundFile(&spx_[i]->file_);
	for (int i = 0; i < 6; i++)
		NyaSound::DeleteSoundFile(&spx_ex_[i]->file_);

	delete bit_gpx_;
	bit_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	for (int i = 0; i < 6; i++)
	{
		delete spx_[i];
		spx_[i] = nullptr;
	}
	for (int i = 0; i < 6; i++)
	{
		delete spx_ex_[i];
		spx_ex_[i] = nullptr;
	}
}

UserAiDeviceEx::UserAiDeviceEx()
{
	bit_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
}

UserAiDeviceEx::~UserAiDeviceEx()
{
	delete bit_gpx_;
	bit_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

UserAiMain::UserAiMain()
{
	gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile(8, 2, "img/user/main.png", &gpx_->file_);
	gpx_->extend_rate_ = 0.4;
	gpx_->draw_angle_deg_ = 0;

	phandle_ = NyaPosition::CreateHandle();
	phandle_->health_ = 1;
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->grid_x_ = 100;
	phandle_->grid_y_ = 500;
	phandle_->name_ = "user_main_handle";

	InterfaceHandleSkill* ihandle_skill = NyaInterface::GetHandleSkill();
	ihandle_skill->exp_[static_cast<int>(eSKILL::Q)] = 700000;
	ihandle_skill->exp_[static_cast<int>(eSKILL::W)] = 700000;
	ihandle_skill->exp_[static_cast<int>(eSKILL::E)] = 200;
	ihandle_skill->exp_[static_cast<int>(eSKILL::R)] = 700000;
}

UserAiMain::~UserAiMain()
{
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

UserAi::UserAi(void)
{
	InterfaceHandleSkill* ihandle_mission_skill = NyaInterface::GetHandleSkill();

	count_frame_ = 0;

	// interface スキル 設定
	ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::Q)] = 200000;
	ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::Q)] = 400000;
	ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::Q)] = 600000;
	ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::Q)] = 800000;
	ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::W)] = 200000;
	ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::W)] = 400000;
	ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::W)] = 600000;
	ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::W)] = 800000;
	ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::E)] = 100;
	ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::E)] = 200;
	ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::E)] = 300;
	ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::E)] = 400;
	ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::R)] = 200000;
	ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::R)] = 400000;
	ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::R)] = 600000;
	ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::R)] = 800000;

	// device ex プロパティ
	device_ex_.bit_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(16, 1,"img/user/bit.png", &device_ex_.bit_gpx_->file_);
	device_ex_.gadget_dpx_->collision_range_ = 2;
	device_ex_.gadget_dpx_->move_speed_ = 20;
	device_ex_.gadget_gpx_->extend_rate_ = 0.2;
	NyaGraphic::LoadGraphicFile("img/user/attack_ex.png", &device_ex_.gadget_gpx_->file_);
	device_ex_.effect_epx_->interval_time_frame_ = 2;
	device_ex_.effect_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(8, 2, "img/user/attack_ex_effect.png", &device_ex_.effect_gpx_->file_);

	// 衝突判定設定
	NyaPosition::CollisionPair(eOBJECT::USER_ATTACK1, eOBJECT::TARGET1);
	NyaPosition::CollisionPair(eOBJECT::TARGET_ATTACK1, eOBJECT::USER1);

	// デバッグ
	NyaString::SettingFont("teemo_font", 10, 2);
}

UserAi::~UserAi()
{
	NyaGraphic::DeleteGraphicFile(&device_.bit_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&device_.gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&device_.effect_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&main_.gpx_->file_);
}

void UserAi::MissionRun(void)
{
	Act();
	Draw();
}

void UserAi::Act(void)
{
	InterfaceHandleSkill *ihandle_mission_skill = NyaInterface::GetHandleSkill();
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	// 移動テスト
	Act_Move();

	// 攻撃処理
	Act_Ult();
	Act_Attack();
	Act_AttackEx();

	//スキルの選択肢を更新
	if (NyaInput::IsPressKey(eINPUT::SPACE))
	{
		if      (ihandle_mission_skill->select_ == eSKILL::Q)
			ihandle_mission_skill->select_ = eSKILL::W;
		else if (ihandle_mission_skill->select_ == eSKILL::W)
			ihandle_mission_skill->select_ = eSKILL::E;
		else if (ihandle_mission_skill->select_ == eSKILL::E)
			ihandle_mission_skill->select_ = eSKILL::R;
		else
			ihandle_mission_skill->select_ = eSKILL::Q;
	}



	// 衝突判定
	//nya_position_->Collision(ai_ph1_, eOBJECT::USER1);		

	// その他
	count_frame_++;

	// デバッグ
	NyaString::Write("teemo_font", white, 50, 70, "[50, 70] teemo count = %d", (int)count_frame_);
	NyaString::Write("teemo_font", white, 50, 110, "[50, 110] teemo x = %d", (int)main_.phandle_->grid_x_);
	NyaString::Write("teemo_font", white, 50, 130, "[50, 130] teemo y = %d", (int)main_.phandle_->grid_y_);
}

/**
@brief 攻撃処理関数
@note
 攻撃力の設定
 - W true MAX power
 lv0 = 3, lv1 = 6+2, lv2 = 9+4, lv3 = 12+6, lv4 = 15+8
 - W false (bit true) MAX power
 lv0 = 3, lv1 = 7, lv2 = 11, lv3 = 15, lv4 = 19 
**/
void UserAi::Act_Attack(void)
{
	int device_collision_accuracy = 2;
	InterfaceHandleSkill *ihandle_mission_skill = NyaInterface::GetHandleSkill();
	int exp_q = ihandle_mission_skill->exp_[static_cast<int>(eSKILL::Q)];
	int lv1_exp_q = ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::Q)];
	int lv2_exp_q = ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::Q)];
	int lv3_exp_q = ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::Q)];
	int lv4_exp_q = ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::Q)];
	int exp_w = ihandle_mission_skill->exp_[static_cast<int>(eSKILL::W)];
	int lv1_exp_w = ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::W)];
	int lv2_exp_w = ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::W)];
	int lv3_exp_w = ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::W)];
	int lv4_exp_w = ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::W)];
	static int sound_index = 0;

	// ウルト実行中ならば、この関数では何もしない
	if (device_ex_.valid_)
		return;

	// 発射音の再生
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && count_frame_ % 6 == 0)
	{
		NyaSound::Play(device_.spx_[sound_index]);
		sound_index = (++sound_index) % 6;
	}


	//***********************
	// 低速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == true && count_frame_ % 6 == 0)
	{	// 3wave
		if(exp_q < lv1_exp_q)
			device_.gadget_dpx_->collision_power_ = 1;
		else if(lv1_exp_q <= exp_q && exp_q < lv2_exp_q)
			device_.gadget_dpx_->collision_power_ = 3;
		else if(lv2_exp_q <= exp_q && exp_q < lv3_exp_q)
			device_.gadget_dpx_->collision_power_ = 5;
		else if(lv3_exp_q <= exp_q && exp_q < lv4_exp_q)
			device_.gadget_dpx_->collision_power_ = 7;
		else
			device_.gadget_dpx_->collision_power_ = 9;
		device_.gadget_dpx_->move_angle_deg_ = -90;
		device_.gadget_dpx_->draw_angle_deg_ = 90;
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		if (lv1_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_dpx_->draw_angle_deg_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -20;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +20;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv2_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_dpx_->draw_angle_deg_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv3_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_dpx_->draw_angle_deg_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv4_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_dpx_->draw_angle_deg_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -50;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +50;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}

	}
	//***********************
	// 高速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == false && count_frame_ % 6 == 0)
	{	// 3wave
		device_.gadget_dpx_->collision_power_ = 1;
		device_.gadget_dpx_->move_angle_deg_ = -90;
		device_.gadget_dpx_->draw_angle_deg_ = 90;
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		if (lv1_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv2_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -70;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -60;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +60;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +70;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv3_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -100;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -90;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +90;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +100;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv4_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -130;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -120;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +120;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +130;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
	}
}

/**
@brief 攻撃処理関数
@note
 攻撃力の設定
 - W true MAX power
 lv0 = 3, lv1 = 6+2, lv2 = 9+4, lv3 = 12+6, lv4 = 15+8
 - W false (bit true) MAX power
 lv0 = 3, lv1 = 7, lv2 = 11, lv3 = 15, lv4 = 19 
**/
void UserAi::Act_AttackEx(void)
{
	int device_collision_accuracy = 2;
	InterfaceHandleSkill *ihandle_mission_skill = NyaInterface::GetHandleSkill();
	int exp_q = ihandle_mission_skill->exp_[static_cast<int>(eSKILL::Q)];
	int lv1_exp_q = ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::Q)];
	int lv2_exp_q = ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::Q)];
	int lv3_exp_q = ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::Q)];
	int lv4_exp_q = ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::Q)];
	int exp_w = ihandle_mission_skill->exp_[static_cast<int>(eSKILL::W)];
	int lv1_exp_w = ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::W)];
	int lv2_exp_w = ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::W)];
	int lv3_exp_w = ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::W)];
	int lv4_exp_w = ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::W)];
	static int sound_index = 0;

	// ウルト実行中でないなら、この関数では何もしない
	if (!device_ex_.valid_)
		return;

	// 発射音の再生
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && count_frame_ % 6 == 0)
	{
		NyaSound::Play(device_.spx_ex_[sound_index]);
		sound_index = (++sound_index) % 6;
	}


	//***********************
	// 低速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == true && count_frame_ % 6 == 0)
	{	// 3wave
		if(exp_q < lv1_exp_q)
			device_.gadget_dpx_->collision_power_ = 1 + 1;
		else if(lv1_exp_q <= exp_q && exp_q < lv2_exp_q)
			device_.gadget_dpx_->collision_power_ = 3 + 1;
		else if(lv2_exp_q <= exp_q && exp_q < lv3_exp_q)
			device_.gadget_dpx_->collision_power_ = 5 + 1;
		else if(lv3_exp_q <= exp_q && exp_q < lv4_exp_q)
			device_.gadget_dpx_->collision_power_ = 7 + 1;
		else
			device_.gadget_dpx_->collision_power_ = 9 + 1;

		device_ex_.gadget_dpx_->move_angle_deg_ = -90;
		device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -10;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +10;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		if (lv1_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_ex_.gadget_dpx_->collision_power_ = 1;
			device_ex_.gadget_dpx_->move_angle_deg_ = -90;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -25;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +25;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv2_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_ex_.gadget_dpx_->collision_power_ = 1;
			device_ex_.gadget_dpx_->move_angle_deg_ = -90;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -40;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +40;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv3_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_ex_.gadget_dpx_->collision_power_ = 1;
			device_ex_.gadget_dpx_->move_angle_deg_ = -90;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -55;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +55;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv4_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_ex_.gadget_dpx_->collision_power_ = 1;
			device_ex_.gadget_dpx_->move_angle_deg_ = -90;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -70;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +70;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}

	}
	//***********************
	// 高速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == false && count_frame_ % 6 == 0)
	{	// 3wave
		device_ex_.gadget_dpx_->collision_power_ = 2;
		device_ex_.gadget_dpx_->move_angle_deg_ = -90;
		device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -10;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +10;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		if (lv1_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_ex_.gadget_dpx_->collision_power_ = 1;
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 5;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -40;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 5;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -30;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 5;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +30;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 5;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +40;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv2_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_ex_.gadget_dpx_->collision_power_ = 1;
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 10;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -70;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 10;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -60;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 10;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +60;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 10;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +70;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv3_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_ex_.gadget_dpx_->collision_power_ = 1;
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 15;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -100;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 15;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -90;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 15;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +90;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 15;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +100;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv4_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_ex_.gadget_dpx_->collision_power_ = 1;
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 20;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -130;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 20;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -120;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 20;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +120;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 20;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +130;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1414(device_ex_.gadget_dpx_, device_ex_.gadget_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
	}

	//************************************************
	// ウルト実行フレーム数をカウントする
	// ウルト実行時間を超えたらウルトを終了させる
	//************************************************
	device_ex_.count_ult_frame_++;
	if (FPS_MAX * 5 < device_ex_.count_ult_frame_)
	{
		device_ex_.count_ult_frame_ = 0;
		device_ex_.valid_ = false;
	}
}


void UserAi::Act_Move(void)
{
	int speed;
	InterfaceHandleSkill *ihandle_mission_skill = NyaInterface::GetHandleSkill();
	int exp_e = ihandle_mission_skill->exp_[static_cast<int>(eSKILL::E)];
	int lv1_exp_e = ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::E)];
	int lv2_exp_e = ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::E)];
	int lv3_exp_e = ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::E)];
	int lv4_exp_e = ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::E)];

	if (NyaInput::GetKeyStateNow(eINPUT::W))
	{
		if     (exp_e < lv1_exp_e)
			speed = 1;
		else if(lv1_exp_e <= exp_e && exp_e < lv2_exp_e)
			speed = 3;
		else if(lv2_exp_e <= exp_e && exp_e < lv3_exp_e)
			speed = 5;
		else if(lv3_exp_e <= exp_e && exp_e < lv4_exp_e)
			speed = 7;
		else
			speed = 9;
	}
	else
	{
		if     (exp_e < lv1_exp_e)
			speed = 4;
		else if(lv1_exp_e <= exp_e && exp_e < lv2_exp_e)
			speed = 7;
		else if(lv2_exp_e <= exp_e && exp_e < lv3_exp_e)
			speed = 10;
		else if(lv3_exp_e <= exp_e && exp_e < lv4_exp_e)
			speed = 13;
		else
			speed = 16;

	}

	if (NyaInput::GetKeyStateNow(eINPUT::RIGHT))
	{
		if (NyaInput::GetKeyStateNow(eINPUT::UP))
		{
			main_.phandle_->grid_y_ -= speed;
			main_.phandle_->grid_x_ += speed;
		}
		else if (NyaInput::GetKeyStateNow(eINPUT::DOWN))
		{
			main_.phandle_->grid_y_ += speed;
			main_.phandle_->grid_x_ += speed;
		}
		else
			main_.phandle_->grid_x_ += speed;
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::LEFT))
	{
		if (NyaInput::GetKeyStateNow(eINPUT::UP))
		{
			main_.phandle_->grid_y_ -= speed;
			main_.phandle_->grid_x_ -= speed;
		}
		else if (NyaInput::GetKeyStateNow(eINPUT::DOWN))
		{
			main_.phandle_->grid_y_ += speed;
			main_.phandle_->grid_x_ -= speed;
		}
		else
			main_.phandle_->grid_x_ -= speed;	
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::UP))
	{
		if (NyaInput::GetKeyStateNow(eINPUT::LEFT))
		{
			main_.phandle_->grid_y_ -= speed;
			main_.phandle_->grid_x_ -= speed;
		}
		else if (NyaInput::GetKeyStateNow(eINPUT::RIGHT))
		{
			main_.phandle_->grid_y_ -= speed;
			main_.phandle_->grid_x_ += speed;
		}
		else
			main_.phandle_->grid_y_ -= speed;	
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::DOWN))
	{
		if (NyaInput::GetKeyStateNow(eINPUT::LEFT))
		{
			main_.phandle_->grid_y_ += speed;
			main_.phandle_->grid_x_ -= speed;
		}
		else if (NyaInput::GetKeyStateNow(eINPUT::RIGHT))
		{
			main_.phandle_->grid_y_ += speed;
			main_.phandle_->grid_x_ += speed;
		}
		else
			main_.phandle_->grid_y_ += speed;
	}

	// 境界チェック
	if (main_.phandle_->grid_x_ < SCREEN_MIN_X + 20)
		main_.phandle_->grid_x_ = SCREEN_MIN_X + 20;
	if (main_.phandle_->grid_y_ < SCREEN_MIN_Y + 40)
		main_.phandle_->grid_y_ = SCREEN_MIN_Y + 40;
	if (SCREEN_MAX_X - 20 < main_.phandle_->grid_x_)
		main_.phandle_->grid_x_ = SCREEN_MAX_X - 20;
	if (SCREEN_MAX_Y - 50 < main_.phandle_->grid_y_)
		main_.phandle_->grid_y_ = SCREEN_MAX_Y - 50;
}

/**
 @brief ウルトの実行
**/
void UserAi::Act_Ult(void)
{
	InterfaceHandleSkill* ihandle_mission_skill = NyaInterface::GetHandleSkill();
	int exp_r = ihandle_mission_skill->exp_[static_cast<int>(eSKILL::R)];
	int lv1_exp_r = ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::R)];
	int lv2_exp_r = ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::R)];
	int lv3_exp_r = ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::R)];
	int lv4_exp_r = ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::R)];

	if (NyaInput::IsPressKey(eINPUT::R) && lv1_exp_r <= exp_r && !device_ex_.valid_)
	{
		device_ex_.valid_ = true;
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK2);
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK3);
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK4);
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK5);
		if (lv1_exp_r <= exp_r && exp_r < lv2_exp_r)
			ihandle_mission_skill->exp_[static_cast<int>(eSKILL::R)] -= lv1_exp_r;
		else if (lv2_exp_r <= exp_r && exp_r < lv3_exp_r)
			ihandle_mission_skill->exp_[static_cast<int>(eSKILL::R)] -= (lv2_exp_r - lv1_exp_r);
		else if (lv3_exp_r <= exp_r && exp_r < lv4_exp_r)
			ihandle_mission_skill->exp_[static_cast<int>(eSKILL::R)] -= (lv3_exp_r - lv2_exp_r);
		else if (lv4_exp_r <= exp_r)
			ihandle_mission_skill->exp_[static_cast<int>(eSKILL::R)] -= (lv4_exp_r - lv3_exp_r);
	}
}


/**
 @brief 描画関数
**/
void UserAi::Draw(void)
{
	InterfaceHandleSkill* ihandle_mission_skill = NyaInterface::GetHandleSkill();
	int exp_w = ihandle_mission_skill->exp_[static_cast<int>(eSKILL::W)];
	int lv1_exp_w = ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::W)];
	int lv2_exp_w = ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::W)];
	int lv3_exp_w = ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::W)];
	int lv4_exp_w = ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::W)];

	// 描画テスト
	main_.gpx_->draw_grid_cx_ = (int)main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = (int)main_.phandle_->grid_y_;
	if (count_frame_ % 2 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % 16;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::USER1);

	//******************
	// ビットの描画
	//******************
	if (!NyaInput::GetKeyStateNow(eINPUT::W))
	{
		device_.bit_gpx_->file_div_ = ++device_.bit_gpx_->file_div_ % 16;
		if (lv1_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 35;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 35;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}
		if (lv2_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 65;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 65;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}
		if (lv3_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 95;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 95;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}
		if (lv4_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 125;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 125;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}	
	}

}
