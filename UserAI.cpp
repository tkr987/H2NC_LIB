#include <tuple>
#include "NyaEnum.h"
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaInterface.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "UserAi.h"

using namespace std;
using namespace H2NLIB;


UserAiDevice::UserAiDevice()
{
	bit_gpx_ = new GraphicPropertyX4;
	gadget_dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	effect_epx_ = new EffectPropertyX1;
	effect_gpx_ = new GraphicPropertyX4;
}

UserAiDevice::~UserAiDevice()
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
	phandle_ = new PositionHandle1;
}

UserAiMain::~UserAiMain()
{
	delete gpx_;
	gpx_ = nullptr;
	delete phandle_;
	phandle_ = nullptr;
}

UserAi::UserAi(void)
{
	nya_position_ = new NyaPosition;
	InterfaceHandleMissionSkill* ihandle_mission_skill = NyaInterface::GetHandleMissionSkill();

	count_frame_ = 0;

	// interface
	ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::W)] = 200;
	ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::W)] = 400;
	ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::W)] = 600;
	ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::W)] = 800;

	// device プロパティ
	device_.bit_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(16, 1,"img/user/bit.png", &device_.bit_gpx_->file_);
	device_.gadget_dpx_->collision_range_ = 2;
	device_.gadget_dpx_->move_speed_ = 20;
	device_.gadget_gpx_->extend_rate_ = 0.1;
	NyaGraphic::LoadGraphicFile("img/user/arms.png", &device_.gadget_gpx_->file_);
	device_.effect_epx_->interval_time_frame_ = 2;
	device_.effect_gpx_->extend_rate_ = 1.0;
	NyaGraphic::LoadGraphicFile(11, 1, "img/user/arms_effect2.png", &device_.effect_gpx_->file_);

	// user ai main property
	NyaGraphic::LoadGraphicFile(8, 2, "img/user/main.png", &main_.gpx_->file_);
	main_.gpx_->extend_rate_ = 0.4;
	main_.gpx_->draw_angle_ = 0;
	main_.phandle_->health_ = 1;
	main_.phandle_->collision_power_ = 1;
	main_.phandle_->collision_range_ = 20;
	main_.phandle_->grid_x_ = 100;
	main_.phandle_->grid_y_ = 500;

	// 衝突判定設定
	NyaPosition::CollisionSetting(eOBJECT::USER_ATTACK1, eOBJECT::TARGET1);
	NyaPosition::CollisionSetting(eOBJECT::TARGET_ATTACK1, eOBJECT::USER1);

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
	InterfaceHandleMissionSkill *ihandle_mission_skill = NyaInterface::GetHandleMissionSkill();
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	// 移動テスト
	if (NyaInput::GetKeyStateNow(eINPUT::RIGHT))
	{
		main_.phandle_->grid_x_ += 5;
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::LEFT))
	{
		main_.phandle_->grid_x_ -= 5;
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::UP))
	{
		main_.phandle_->grid_y_ -= 5;
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::DOWN))
	{
		main_.phandle_->grid_y_ += 5;
	}

	// 境界チェック
	if (main_.phandle_->grid_x_ < SCREEN_MIN_X)
		main_.phandle_->grid_x_ = SCREEN_MIN_X;
	if (main_.phandle_->grid_y_ < SCREEN_MIN_Y)
		main_.phandle_->grid_y_ = SCREEN_MIN_Y;
	if (SCREEN_MAX_X < main_.phandle_->grid_x_)
		main_.phandle_->grid_x_ = SCREEN_MAX_X;
	if (SCREEN_MAX_Y < main_.phandle_->grid_y_)
		main_.phandle_->grid_y_ = SCREEN_MAX_Y;

	// 攻撃処理
	Act_Attack();

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
	InterfaceHandleMissionSkill *ihandle_mission_skill = NyaInterface::GetHandleMissionSkill();
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

	//***********************
	// 低速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == true && count_frame_ % 6 == 0)
	{	// 3wave
		if(exp_q < lv1_exp_q)
			device_.gadget_dpx_->collision_power_ = 1;
		else if(lv1_exp_q <= exp_q && exp_q < lv2_exp_q)
			device_.gadget_dpx_->collision_power_ = 2;
		else if(lv2_exp_q <= exp_q && exp_q < lv3_exp_q)
			device_.gadget_dpx_->collision_power_ = 3;
		else if(lv3_exp_q <= exp_q && exp_q < lv4_exp_q)
			device_.gadget_dpx_->collision_power_ = 4;
		else
			device_.gadget_dpx_->collision_power_ = 5;
		device_.gadget_dpx_->move_angle_deg_ = -90;
		device_.gadget_gpx_->draw_angle_ = 90;
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		if (lv1_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_gpx_->draw_angle_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -20;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +20;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv2_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_gpx_->draw_angle_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv3_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_gpx_->draw_angle_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv4_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_gpx_->draw_angle_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -50;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +50;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}

	}
	//***********************
	// 高速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == false && count_frame_ % 6 == 0)
	{	// 3wave
		device_.gadget_dpx_->collision_power_ = 1;
		device_.gadget_dpx_->move_angle_deg_ = -90;
		device_.gadget_gpx_->draw_angle_ = 90;
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		if (lv1_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			device_.gadget_gpx_->draw_angle_ = 90 - 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			device_.gadget_gpx_->draw_angle_ = 90 - 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			device_.gadget_gpx_->draw_angle_ = 90 + 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			device_.gadget_gpx_->draw_angle_ = 90 + 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv2_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			device_.gadget_gpx_->draw_angle_ = 90 - 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -70;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			device_.gadget_gpx_->draw_angle_ = 90 - 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -60;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			device_.gadget_gpx_->draw_angle_ = 90 + 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +60;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			device_.gadget_gpx_->draw_angle_ = 90 + 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +70;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv3_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			device_.gadget_gpx_->draw_angle_ = 90 - 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -100;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			device_.gadget_gpx_->draw_angle_ = 90 - 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -90;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			device_.gadget_gpx_->draw_angle_ = 90 + 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +90;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			device_.gadget_gpx_->draw_angle_ = 90 + 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +100;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv4_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->collision_power_ = 1;
			device_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			device_.gadget_gpx_->draw_angle_ = 90 - 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -130;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			device_.gadget_gpx_->draw_angle_ = 90 - 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -120;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			device_.gadget_gpx_->draw_angle_ = 90 + 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +120;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			device_.gadget_gpx_->draw_angle_ = 90 + 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +130;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +30;
			NyaDevice::Attack1414(device_.gadget_dpx_, device_.gadget_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
	}
}

/**
 @brief 描画関数
**/
void UserAi::Draw(void)
{
	InterfaceHandleMissionSkill* ihandle_mission_skill = NyaInterface::GetHandleMissionSkill();
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
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 30;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 35;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 30;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}
		if (lv2_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 65;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 30;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 65;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 30;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}
		if (lv3_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 95;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 30;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 95;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 30;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}
		if (lv4_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 125;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 30;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 125;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 30;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}	
	}

}
