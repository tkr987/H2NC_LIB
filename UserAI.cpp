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
	gadget_dpx_ = new DevicePropertyX1;
	gadget_gpx_ = new GraphicPropertyX4;
	effect_epx_ = new EffectProperty1;
	effect_gpx_ = new GraphicPropertyX4;
}

UserAiDevice::~UserAiDevice()
{
	delete gadget_dpx_;
	delete gadget_gpx_;
	delete effect_epx_;
	delete effect_gpx_;
}

UserAiEffectTest::UserAiEffectTest()
{
	ep_ = new EffectProperty1;
	gp_ = new GraphicPropertyX4;
}

UserAiEffectTest::~UserAiEffectTest()
{
	delete ep_;
	delete gp_;
}

UserAiMain::UserAiMain()
{
	gp_ = new H2NLIB::GraphicPropertyX4;
	ph_ = new H2NLIB::PositionHandle1;
}

UserAiMain::~UserAiMain()
{
	delete gp_;
	delete ph_;
}

UserAi::UserAi(void)
{
	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	nya_position_ = new NyaPosition;
	InterfaceHandleMissionSkill* ihandle_mission_skill = NyaInterface::GetHandleMissionSkill();

	count_frame_ = 0;

	// interface
	ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::W)] = 200;
	ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::W)] = 400;
	ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::W)] = 600;
	ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::W)] = 800;

	// user ai device 2 property
	user_device_.gadget_dpx_->collision_range_ = 2;
	user_device_.gadget_dpx_->move_speed_ = 20;
	user_device_.gadget_gpx_->extend_rate_ = 0.1;
	NyaGraphic::LoadGraphicFile("img/user/arms.png", &user_device_.gadget_gpx_->graphic_file_);
	user_device_.effect_epx_->interval_time_frame_ = 2;
	user_device_.effect_gpx_->extend_rate_ = 1.0;
	NyaGraphic::LoadGraphicFile(11, 1, "img/user/arms_effect2.png", &user_device_.effect_gpx_->graphic_file_);

	// user ai effect test property
	ai_effect_test_.ep_->grid_x_ = 500;
	ai_effect_test_.ep_->grid_y_ = 500;
	ai_effect_test_.ep_->interval_time_frame_ = 10;
	NyaGraphic::LoadGraphicFile(4, 2, "img/Death80.png", &ai_effect_test_.gp_->graphic_file_);

	// user ai effect test 2 property
	ai_effect_test2_.ep_->grid_x_ = 500;
	ai_effect_test2_.ep_->grid_y_ = 450;
	ai_effect_test2_.ep_->interval_time_frame_ = 10;
	NyaGraphic::LoadGraphicFile(4, 1, "img/user_ai_gadget_effect.png", &ai_effect_test2_.gp_->graphic_file_);

	// user ai main property
	NyaGraphic::LoadGraphicFile(8, 2, "img/user/main.png", &main_.gp_->graphic_file_);
	main_.gp_->extend_rate_ = 0.4;
	main_.gp_->draw_angle_ = 0;
	main_.ph_->health_ = 1;
	main_.ph_->collision_power_ = 1;
	main_.ph_->collision_range_ = 20;
	main_.ph_->grid_x_ = 100;
	main_.ph_->grid_y_ = 500;

	// 衝突判定設定
	NyaPosition::CollisionSetting(eOBJECT::USER_ATTACK1, eOBJECT::TARGET1);
	NyaPosition::CollisionSetting(eOBJECT::TARGET_ATTACK1, eOBJECT::USER1);

	// デバッグ
	NyaString::SettingFont("teemo_font", 10, 2);
}

UserAi::~UserAi()
{
	NyaGraphic::DeleteGraphicFile(&main_.gp_->graphic_file_);
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
		main_.ph_->grid_x_ += 5;
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::LEFT))
	{
		main_.ph_->grid_x_ -= 5;
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::UP))
	{
		main_.ph_->grid_y_ -= 5;
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::DOWN))
	{
		main_.ph_->grid_y_ += 5;
	}

	// 境界チェック
	if (main_.ph_->grid_x_ < SCREEN_MIN_X)
		main_.ph_->grid_x_ = SCREEN_MIN_X;
	if (main_.ph_->grid_y_ < SCREEN_MIN_Y)
		main_.ph_->grid_y_ = SCREEN_MIN_Y;
	if (SCREEN_MAX_X < main_.ph_->grid_x_)
		main_.ph_->grid_x_ = SCREEN_MAX_X;
	if (SCREEN_MAX_Y < main_.ph_->grid_y_)
		main_.ph_->grid_y_ = SCREEN_MAX_Y;

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
	NyaString::Write("teemo_font", white, 50, 110, "[50, 110] teemo x = %d", (int)main_.ph_->grid_x_);
	NyaString::Write("teemo_font", white, 50, 130, "[50, 130] teemo y = %d", (int)main_.ph_->grid_y_);
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
			user_device_.gadget_dpx_->collision_power_ = 1;
		else if(lv1_exp_q <= exp_q && exp_q < lv2_exp_q)
			user_device_.gadget_dpx_->collision_power_ = 2;
		else if(lv2_exp_q <= exp_q && exp_q < lv3_exp_q)
			user_device_.gadget_dpx_->collision_power_ = 3;
		else if(lv3_exp_q <= exp_q && exp_q < lv4_exp_q)
			user_device_.gadget_dpx_->collision_power_ = 4;
		else
			user_device_.gadget_dpx_->collision_power_ = 5;
		user_device_.gadget_dpx_->move_angle_deg_ = -90;
		user_device_.gadget_gpx_->draw_angle_ = 90;
		user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -10;
		user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_;
		nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_;
		user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_;
		nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +10;
		user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_;
		nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		if (lv1_exp_w <= exp_w)
		{	// 1wave + 1wave
			user_device_.gadget_dpx_->collision_power_ = 1;
			user_device_.gadget_dpx_->move_angle_deg_ = -90;
			user_device_.gadget_gpx_->draw_angle_ = 90;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -20;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +20;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv2_exp_w <= exp_w)
		{	// 1wave + 1wave
			user_device_.gadget_dpx_->collision_power_ = 1;
			user_device_.gadget_dpx_->move_angle_deg_ = -90;
			user_device_.gadget_gpx_->draw_angle_ = 90;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -30;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +30;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv3_exp_w <= exp_w)
		{	// 1wave + 1wave
			user_device_.gadget_dpx_->collision_power_ = 1;
			user_device_.gadget_dpx_->move_angle_deg_ = -90;
			user_device_.gadget_gpx_->draw_angle_ = 90;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -40;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +40;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv4_exp_w <= exp_w)
		{	// 1wave + 1wave
			user_device_.gadget_dpx_->collision_power_ = 1;
			user_device_.gadget_dpx_->move_angle_deg_ = -90;
			user_device_.gadget_gpx_->draw_angle_ = 90;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -50;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +50;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}

	}
	//***********************
	// 高速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == false && count_frame_ % 6 == 0)
	{	// 3wave
		user_device_.gadget_dpx_->collision_power_ = 1;
		user_device_.gadget_dpx_->move_angle_deg_ = -90;
		user_device_.gadget_gpx_->draw_angle_ = 90;
		user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -10;
		user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_;
		nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_;
		user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_;
		nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +10;
		user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_;
		nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		if (lv1_exp_w <= exp_w)
		{	// 2wave + 2wave
			user_device_.gadget_dpx_->collision_power_ = 1;
			user_device_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			user_device_.gadget_gpx_->draw_angle_ = 90 - 5;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -40;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			user_device_.gadget_gpx_->draw_angle_ = 90 - 5;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -30;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			user_device_.gadget_gpx_->draw_angle_ = 90 + 5;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +30;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			user_device_.gadget_gpx_->draw_angle_ = 90 + 5;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +40;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv2_exp_w <= exp_w)
		{	// 2wave + 2wave
			user_device_.gadget_dpx_->collision_power_ = 1;
			user_device_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			user_device_.gadget_gpx_->draw_angle_ = 90 - 10;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -70;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			user_device_.gadget_gpx_->draw_angle_ = 90 - 10;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -60;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			user_device_.gadget_gpx_->draw_angle_ = 90 + 10;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +60;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			user_device_.gadget_gpx_->draw_angle_ = 90 + 10;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +70;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv3_exp_w <= exp_w)
		{	// 2wave + 2wave
			user_device_.gadget_dpx_->collision_power_ = 1;
			user_device_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			user_device_.gadget_gpx_->draw_angle_ = 90 - 15;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -100;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			user_device_.gadget_gpx_->draw_angle_ = 90 - 15;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -90;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			user_device_.gadget_gpx_->draw_angle_ = 90 + 15;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +90;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			user_device_.gadget_gpx_->draw_angle_ = 90 + 15;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +100;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
		if (lv4_exp_w <= exp_w)
		{	// 2wave + 2wave
			user_device_.gadget_dpx_->collision_power_ = 1;
			user_device_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			user_device_.gadget_gpx_->draw_angle_ = 90 - 20;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -130;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			user_device_.gadget_gpx_->draw_angle_ = 90 - 20;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ -120;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			user_device_.gadget_gpx_->draw_angle_ = 90 + 20;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +120;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
			user_device_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			user_device_.gadget_gpx_->draw_angle_ = 90 + 20;
			user_device_.gadget_dpx_->create_x_ = main_.ph_->grid_x_ +130;
			user_device_.gadget_dpx_->create_y_ = main_.ph_->grid_y_ +30;
			nya_device_->Attack1414(user_device_.gadget_dpx_, user_device_.gadget_gpx_, user_device_.effect_epx_, user_device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
		}
	}
}

void UserAi::Draw(void)
{
	// 描画テスト
	main_.gp_->draw_grid_cx_ = (int)main_.ph_->grid_x_;
	main_.gp_->draw_grid_cy_ = (int)main_.ph_->grid_y_;
	if (count_frame_ % 2 == 0)
		main_.gp_->file_div_ = ++main_.gp_->file_div_ % 16;
	NyaGraphic::Draw(main_.gp_, eOBJECT::USER1);

	// エフェクトテスト
	if (count_frame_ % 200 == 0)
		nya_effect_->Draw(ai_effect_test_.ep_, ai_effect_test_.gp_, eOBJECT::USER_EFFECT1);
}
