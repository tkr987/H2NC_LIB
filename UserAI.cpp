#include <tuple>
#include "NyaEnum.h"
#include "NyaDesign.h"
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "UserAI.h"

using namespace std;
using namespace H2NLIB;


UserAiDevice2::UserAiDevice2()
{
	gadget_dp_ = new DeviceProperty1;
	gadget_gp_ = new GraphicProperty4;
	effect_ep_ = new EffectProperty1;
	effect_gp_ = new GraphicProperty4;
}

UserAiDevice2::~UserAiDevice2()
{
	delete gadget_dp_;
	delete gadget_gp_;
	delete effect_ep_;
	delete effect_gp_;
}

UserAiEffectTest::UserAiEffectTest()
{
	ep_ = new EffectProperty1;
	gp_ = new GraphicProperty4;
}

UserAiEffectTest::~UserAiEffectTest()
{
	delete ep_;
	delete gp_;
}

UserAiMain::UserAiMain()
{
	gp_ = new H2NLIB::GraphicProperty4;
	ph_ = new H2NLIB::PositionHandle1;
}

UserAiMain::~UserAiMain()
{
	delete gp_;
	delete ph_;
}

void UserAI::Act(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

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

	// 攻撃テスト2
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && count_ % 10 == 0)
	{
		ai_device2_.gadget_dp_->create_x_ = main_.ph_->grid_x_;
		ai_device2_.gadget_dp_->create_y_ = main_.ph_->grid_y_;
		nya_device_->Attack1414(ai_device2_.gadget_dp_, ai_device2_.gadget_gp_, ai_device2_.effect_ep_, ai_device2_.effect_gp_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1);
	}

	// 衝突判定
	//nya_position_->Collision(ai_ph1_, eOBJECT::USER1);		

	// その他
	count_++;

	// デバッグ
	NyaString::Write("teemo_font", white, 50, 70, "[50, 70] teemo count = %d", count_);
	NyaString::Write("teemo_font", white, 50, 110, "[50, 110] teemo x = %d", (int)main_.ph_->grid_x_);
	NyaString::Write("teemo_font", white, 50, 130, "[50, 130] teemo y = %d", (int)main_.ph_->grid_y_);
}

void UserAI::Draw(void)
{
	// 描画テスト
	main_.gp_->draw_grid_cx_ = (int)main_.ph_->grid_x_;
	main_.gp_->draw_grid_cy_ = (int)main_.ph_->grid_y_;
	if (count_ % 2 == 0)
		main_.gp_->file_div_ = ++main_.gp_->file_div_ % 16;
	NyaGraphic::Draw(main_.gp_, eOBJECT::USER1);


	// エフェクトテスト
	if (count_ % 200 == 0)
		nya_effect_->Draw(ai_effect_test_.ep_, ai_effect_test_.gp_, eOBJECT::USER_EFFECT1);
}

void UserAI::GameStart()
{
	count_ = 0;

	nya_design_ = new NyaDesign;
	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	nya_position_ = new NyaPosition;

	// user ai device 2 property
	ai_device2_.gadget_dp_->collision_pow_ = 1.0;
	ai_device2_.gadget_dp_->collision_range_ = 2.0;
	ai_device2_.gadget_dp_->move_angle_deg_ = -90;
	ai_device2_.gadget_dp_->move_speed_ = 10;
	ai_device2_.gadget_gp_->draw_angle_ = -90;
	NyaGraphic::LoadGraphicFile("img/user_ai_gadget.png", &ai_device2_.gadget_gp_->graphic_file_);
	ai_device2_.effect_ep_->interval_time_frame_ = 2;
	NyaGraphic::LoadGraphicFile(4, 1, "img/user_ai_gadget_effect.png", &ai_device2_.effect_gp_->graphic_file_);

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
	NyaGraphic::LoadGraphicFile(8, 2, "img/user_ai.png", &main_.gp_->graphic_file_);
	main_.gp_->extend_rate_ = 0.4;
	main_.gp_->draw_angle_ = 90;
	main_.ph_->health_max_ = 100;
	main_.ph_->health_now_ = 100;
	main_.ph_->collision_pow_ = 1;
	main_.ph_->collision_range_ = 20;
	main_.ph_->grid_x_ = 100;
	main_.ph_->grid_y_ = 500;
	nya_position_->Regist(main_.ph_);

	// 衝突判定設定
	nya_position_->SettingCollision(eOBJECT::USER_ATTACK1, eOBJECT::TARGET1);
	nya_position_->SettingCollision(eOBJECT::TARGET_ATTACK1, eOBJECT::USER1);

	// デバッグ
	NyaString::SettingFont("teemo_font", 10, 2);
}

void UserAI::GameEnd()
{
	NyaGraphic::DeleteGraphicFile(&ai_device2_.gadget_gp_->graphic_file_);
	NyaGraphic::DeleteGraphicFile(&ai_device2_.effect_gp_->graphic_file_);
	NyaGraphic::DeleteGraphicFile(&ai_effect_test_.gp_->graphic_file_);
	NyaGraphic::DeleteGraphicFile(&ai_effect_test2_.gp_->graphic_file_);
	NyaGraphic::DeleteGraphicFile(&main_.gp_->graphic_file_);

	delete nya_design_;
	delete nya_device_;
	delete nya_effect_;
	delete nya_position_;
}