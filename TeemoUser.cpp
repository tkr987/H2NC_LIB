#include <tuple>
#include "NyaDefine.h"
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "TeemoUser.h"

using namespace std;
using namespace H2NLIB;

TeemoUser::TeemoUser()
{
	count_ = 0;

	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
	dpx_ = new DevicePropertyX;
	epx_ = new EffectPropertyX;
	gpx4_teemo_ = new GraphicPropertyX4;
	phx_teemo_ = nya_position_->Create();
	device_option_pair_.first = new DeviceOption;
	effect_option_pair_.first = new EffectOption;

	// NyaDeviceとプロパティの設定
	device_option_pair_.first->collision_range_ = 3.0;
	device_option_pair_.first->draw_angle_ = -90.0;
	device_option_pair_.second = nya_device_->NewOption(device_option_pair_.first);
	nya_device_->SetEffect("img/teemo_user_attack_effect.png", 4, 1, 4, 5, eOBJECT::GROUP::USER_ATTACK_EFFECT1);
	nya_device_->SetGraphic("img/teemo_user_attack.png");
	dpx_->object_group_ = eOBJECT::GROUP::USER_ATTACK1;

	// NyaEffectとプロパティの設定
	epx_->animation_div_max_ = 8;
	epx_->animation_interval_time_ = 10;
	epx_->file_id_ = nya_effect_->LoadFile(4, 2, "img/Death80.png");
	epx_->object_group_ = eOBJECT::GROUP::USER_EFFECT1;

	// NyaGraphicとプロパティの設定
	gpx4_teemo_->draw_angle_ = 0;
	gpx4_teemo_->extend_rate_ = 1.0;
	gpx4_teemo_->file_id_ = nya_graphic_->LoadFile(2, 1, "img/teemo_div.png");
	gpx4_teemo_->flag_trans_ = true;
	gpx4_teemo_->flag_turn_ = false;
	gpx4_teemo_->object_group_ = eOBJECT::GROUP::USER1;

	// NyaPositionとプロパティの設定
	phx_teemo_->health_max_ = 100;
	phx_teemo_->health_now_ = 100;
	phx_teemo_->collision_pow_ = 1;
	phx_teemo_->collision_range_ = 20;
	phx_teemo_->grid_x_ = 100;
	phx_teemo_->grid_y_ = 500;
	nya_position_->SettingCollision(eOBJECT::GROUP::USER_ATTACK1, eOBJECT::GROUP::TARGET1);
	nya_position_->SettingCollision(eOBJECT::GROUP::TARGET_ATTACK1, eOBJECT::GROUP::USER1);

	// デバッグ
	NyaString::SettingFont("teemo_font", 10, 2);
}


TeemoUser::~TeemoUser()
{
	delete nya_device_;
	delete nya_effect_;
	delete nya_graphic_;
	delete nya_position_;
	delete dpx_;
	delete epx_;
	delete gpx4_teemo_;
	delete device_option_pair_.first;
	delete effect_option_pair_.first;
}


void TeemoUser::Init(void)
{

}


void TeemoUser::Action(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	// 移動テスト
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::RIGHT))
	{
		phx_teemo_->grid_x_ += 5;
	}
	else if (NyaInput::GetKeyFlagNow(eINPUT::NUM::LEFT))
	{
		phx_teemo_->grid_x_ -= 5;
	}
	else if (NyaInput::GetKeyFlagNow(eINPUT::NUM::UP))
	{
		phx_teemo_->grid_y_ -= 5;
	}
	else if (NyaInput::GetKeyFlagNow(eINPUT::NUM::DOWN))
	{
		phx_teemo_->grid_y_ += 5;
	}

	// 攻撃テスト
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::Q) == true && count_ % 10 == 0)
	{
		dpx_->create_x_ = phx_teemo_->grid_x_;
		dpx_->create_y_ = phx_teemo_->grid_y_;
		dpx_->move_angle_ = -90.0;
		dpx_->move_speed_ = 10.0;
		nya_device_->Attack(dpx_, device_option_pair_.second);
	}

	// 衝突判定
	nya_position_->Collision(phx_teemo_, eOBJECT::GROUP::USER1);

	// その他
	count_++;

	// デバッグ
	NyaString::Write("teemo_font", white, 50, 70, "[50, 70] teemo count = %d", count_);
	NyaString::Write("teemo_font", white, 50, 110, "[50, 110] teemo x = %d", (int)phx_teemo_->grid_x_);
	NyaString::Write("teemo_font", white, 50, 130, "[50, 130] teemo y = %d", (int)phx_teemo_->grid_y_);
}

void TeemoUser::Draw(void)
{
	// 描画テスト
	gpx4_teemo_->pos_cx_ = (int)phx_teemo_->grid_x_;
	gpx4_teemo_->pos_cy_ = (int)phx_teemo_->grid_y_;
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::RIGHT))
	{
		gpx4_teemo_->file_div_ = 1;
	}
	else
	{
		gpx4_teemo_->file_div_ = 0;
	}
	nya_graphic_->Draw(gpx4_teemo_);

	// エフェクトテスト
	if (count_ % 200 == 0) {
		epx_->grid_x_ = 500;
		epx_->grid_y_ = 500;
		nya_effect_->Draw(epx_);
	}

}

