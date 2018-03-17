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

UserAI::UserAI()
{
	count_ = 0;

	nya_design_ = new NyaDesign;
	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
	dpx1_ = new DevicePropertyX1;
	test_effect_.epx1_ = new EffectPropertyX1;
	test_effect_.gpx4_ = new GraphicPropertyX4;

	//test_gpx1_ = new GraphicPropertyX1;
	//test_gpx1_->pos_x_ = 0;
	//test_gpx1_->pos_y_ = 0;
	//test_gpx1_->graphic_file_ = nya_graphic_->LoadGraphicFile("img/back1.png");
	//test_gpx1_->object_group_ = eOBJECT::NUM::MAP1;


	gpx4_ai_ = new GraphicPropertyX4;
	phx_ai_ = nya_position_->Create();

	// NyaDesignの設定
	nya_design_->LoadWarningSound("sound/warning.wav", 40);

	// NyaDeviceとプロパティの設定
	//dpx1_->collision_pow_ = 1.0;
	//dpx1_->collision_range_ = 2.0;
	//dpx1_->move_angle_deg_ = -90;
	//dpx1_->move_speed_ = 5;
	//dpx1_->object_group_ = eOBJECT::NUM::USER_ATTACK1;
	//nya_device_->SetEffect("img/teemo_user_attack_effect.png", 4, 1, 4, 5, eOBJECT::NUM::USER_ATTACK_EFFECT1);
	//nya_device_->SetGraphic("img/teemo_user_attack.png");
	//dpx_->object_group_ = eOBJECT::NUM::USER_ATTACK1;

	// エフェクト関連プロパティの設定
	test_effect_.epx1_->interval_time_frame_ = 10;
	nya_graphic_->LoadGraphicFile("img/Death80.png", &test_effect_.gpx4_->graphic_file_);
	test_effect_.gpx4_->object_group_ = eOBJECT::NUM::USER_EFFECT1;

	// NyaGraphicとプロパティの設定
	gpx4_ai_->draw_angle_ = 0;
	gpx4_ai_->extend_rate_ = 0.4;
	gpx4_ai_->file_div_ = 0;
	nya_graphic_->LoadGraphicFile(8, 2, "img/user_ai.png", &gpx4_ai_->graphic_file_);
	gpx4_ai_->flag_trans_ = true;
	gpx4_ai_->flag_turn_ = false;
	gpx4_ai_->object_group_ = eOBJECT::NUM::USER1;

	// NyaPositionとハンドルの設定
	phx_ai_->health_max_ = 100;
	phx_ai_->health_now_ = 100;
	phx_ai_->collision_pow_ = 1;
	phx_ai_->collision_range_ = 20;
	phx_ai_->grid_x_ = 100;
	phx_ai_->grid_y_ = 500;
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
	delete dpx1_;
	delete test_effect_.epx1_;
	delete test_effect_.gpx4_;
	delete gpx4_ai_;
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
		phx_ai_->grid_x_ += 5;
	}
	else if (NyaInput::GetKeyFlagNow(eINPUT::NUM::LEFT))
	{
		phx_ai_->grid_x_ -= 5;
	}
	else if (NyaInput::GetKeyFlagNow(eINPUT::NUM::UP))
	{
		phx_ai_->grid_y_ -= 5;
	}
	else if (NyaInput::GetKeyFlagNow(eINPUT::NUM::DOWN))
	{
		phx_ai_->grid_y_ += 5;
	}

	// 境界チェック
	if (phx_ai_->grid_x_ < SCREEN_MIN_X)
		phx_ai_->grid_x_ = SCREEN_MIN_X;
	if (phx_ai_->grid_y_ < SCREEN_MIN_Y)
		phx_ai_->grid_y_ = SCREEN_MIN_Y;
	if (SCREEN_MAX_X < phx_ai_->grid_x_)
		phx_ai_->grid_x_ = SCREEN_MAX_X;
	if (SCREEN_MAX_Y < phx_ai_->grid_y_)
		phx_ai_->grid_y_ = SCREEN_MAX_Y;

	// 攻撃テスト
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::Q) == true && count_ % 10 == 0)
	{
		//dpx_->create_x_ = phx_ai_->grid_x_;
		//dpx_->create_y_ = phx_ai_->grid_y_;
		//dpx_->move_angle_ = -90.0;
		//dpx_->move_speed_ = 10.0;
		//nya_device_->Attack(dpx_, device_option_pair_.second);
	}

	// 衝突判定
	nya_position_->Collision(phx_ai_, eOBJECT::NUM::USER1);		

	// その他
	count_++;

	// デバッグ
	NyaString::Write("teemo_font", white, 50, 70, "[50, 70] teemo count = %d", count_);
	NyaString::Write("teemo_font", white, 50, 110, "[50, 110] teemo x = %d", (int)phx_ai_->grid_x_);
	NyaString::Write("teemo_font", white, 50, 130, "[50, 130] teemo y = %d", (int)phx_ai_->grid_y_);
}

void UserAI::Draw(void)
{
	// 描画テスト
	gpx4_ai_->pos_cx_ = (int)phx_ai_->grid_x_;
	gpx4_ai_->pos_cy_ = (int)phx_ai_->grid_y_;
	if (count_ % 2 == 0)
		gpx4_ai_->file_div_ = ++gpx4_ai_->file_div_ % 16;
	nya_graphic_->Draw(gpx4_ai_);


	//nya_graphic_->Draw(test_gpx1_);

	// エフェクトテスト
	if (count_ % 200 == 0) {
//		test_effect_.epx1_->grid_x_ = 500;
//		test_effect_.epx1_->grid_y_ = 500;
//		nya_effect_->Draw(test_effect_.epx1_, test_effect_.gpx4_);
	}

}

