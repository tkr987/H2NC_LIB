#include <tuple>
#include "NyaDefine.h"
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

UserAiDevice::UserAiDevice()
{
	dp_ = new DeviceProperty1;
	gp_ = new GraphicProperty4;
}

UserAiDevice::~UserAiDevice()
{
	delete dp_;
	delete gp_;
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

UserAI::UserAI()
{
	count_ = 0;

	nya_design_ = new NyaDesign;
	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;

	// user ai device property
	ai_device_.dp_->collision_pow_ = 1.0;
	ai_device_.dp_->collision_range_ = 2.0;
	ai_device_.dp_->move_angle_deg_ = -90;
	ai_device_.dp_->move_speed_ = 10;
	ai_device_.gp_->draw_angle_ = -90;
	ai_device_.gp_->file_div_ = 0;
	//nya_graphic_->LoadGraphicFile("img/ai_device.png", &ai_device_.gp_->graphic_file_);

	// user ai effect test property
	ai_effect_test_.ep_->draw_max_div_ = 8;
	ai_effect_test_.ep_->interval_time_frame_ = 10;
	//nya_graphic_->LoadGraphicFile(4, 2, "img/Death80.png", &ai_effect_test_.gp_->graphic_file_);

	// user ai main property
	nya_graphic_->LoadGraphicFile(8, 2, "img/user_ai.png", &ai_main_.gp_->graphic_file_);
	ai_main_.gp_->extend_rate_ = 0.4;
	ai_main_.gp_->draw_angle_ = 90;
	ai_main_.ph_->health_max_ = 100;
	ai_main_.ph_->health_now_ = 100;
	ai_main_.ph_->collision_pow_ = 1;
	ai_main_.ph_->collision_range_ = 20;
	ai_main_.ph_->grid_x_ = 100;
	ai_main_.ph_->grid_y_ = 500;

	// 衝突判定設定
	nya_position_->SettingCollision(eOBJECT::NUM::USER_ATTACK1, eOBJECT::NUM::TARGET1);
	nya_position_->SettingCollision(eOBJECT::NUM::TARGET_ATTACK1, eOBJECT::NUM::USER1);

	// デバッグ
	NyaString::SettingFont("teemo_font", 10, 2);
}


UserAI::~UserAI()
{
	delete nya_design_;
	delete nya_device_;
	delete nya_effect_;
	delete nya_graphic_;
	delete nya_position_;
}


void UserAI::Init(void)
{

}


void UserAI::Act(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	// 移動テスト
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::RIGHT))
	{
		ai_main_.ph_->grid_x_ += 5;
	}
	else if (NyaInput::GetKeyFlagNow(eINPUT::NUM::LEFT))
	{
		ai_main_.ph_->grid_x_ -= 5;
	}
	else if (NyaInput::GetKeyFlagNow(eINPUT::NUM::UP))
	{
		ai_main_.ph_->grid_y_ -= 5;
	}
	else if (NyaInput::GetKeyFlagNow(eINPUT::NUM::DOWN))
	{
		ai_main_.ph_->grid_y_ += 5;
	}

	// 境界チェック
	if (ai_main_.ph_->grid_x_ < SCREEN_MIN_X)
		ai_main_.ph_->grid_x_ = SCREEN_MIN_X;
	if (ai_main_.ph_->grid_y_ < SCREEN_MIN_Y)
		ai_main_.ph_->grid_y_ = SCREEN_MIN_Y;
	if (SCREEN_MAX_X < ai_main_.ph_->grid_x_)
		ai_main_.ph_->grid_x_ = SCREEN_MAX_X;
	if (SCREEN_MAX_Y < ai_main_.ph_->grid_y_)
		ai_main_.ph_->grid_y_ = SCREEN_MAX_Y;

	// 攻撃テスト
	//if (NyaInput::GetKeyFlagNow(eINPUT::NUM::Q) == true && count_ % 10 == 0)
	//{
	//	ai_device_.dp_->create_x_ = ai_main_.ph_->grid_x_;
	//	ai_device_.dp_->create_y_ = ai_main_.ph_->grid_y_;
	//	nya_device_->Attack(user_device_.attack1_dp1_, user_device_.gpx4_);
	//}

	// 衝突判定
	//nya_position_->Collision(ai_ph1_, eOBJECT::NUM::USER1);		

	// その他
	count_++;

	// デバッグ
	NyaString::Write("teemo_font", white, 50, 70, "[50, 70] teemo count = %d", count_);
	NyaString::Write("teemo_font", white, 50, 110, "[50, 110] teemo x = %d", (int)ai_main_.ph_->grid_x_);
	NyaString::Write("teemo_font", white, 50, 130, "[50, 130] teemo y = %d", (int)ai_main_.ph_->grid_y_);
}

void UserAI::Draw(void)
{
	// 描画テスト
	ai_main_.gp_->draw_grid_cx_ = (int)ai_main_.ph_->grid_x_;
	ai_main_.gp_->draw_grid_cy_ = (int)ai_main_.ph_->grid_y_;
	if (count_ % 2 == 0)
		ai_main_.gp_->file_div_ = ++ai_main_.gp_->file_div_ % 16;
	nya_graphic_->Draw(ai_main_.gp_, eOBJECT::NUM::USER1);


	//nya_graphic_->Draw(test_gpx1_);

	// エフェクトテスト
	if (count_ % 200 == 0) {
//		test_effect_.epx1_->grid_x_ = 500;
//		test_effect_.epx1_->grid_y_ = 500;
//		nya_effect_->Draw(test_effect_.epx1_, test_effect_.gpx4_);
	}

}

