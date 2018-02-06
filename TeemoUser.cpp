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
	int effect_setting_id;
	int graphic_file_id;
	DeviceSetting device_setting;
	EffectSetting effect_setting;

	count_ = 0;

	nya_device_ = new NyaDevice;
	nya_effect_ = new NyaEffect;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
	dpx_teemo_ = new DevicePropertyX;
	epx_teemo_ = new EffectPropertyX;
	gpx4_teemo_ = new GraphicPropertyX4;
	phx_teemo_ = nya_position_->Create();
	nya_position_->SettingCollision(eOBJECT::GROUP::USER_ATTACK1, eOBJECT::GROUP::TARGET1);
	nya_position_->SettingCollision(eOBJECT::GROUP::TARGET_ATTACK1, eOBJECT::GROUP::USER1);

	// デバイスとプロパティの設定
	device_setting.collision_pow_ = 1;
	device_setting.collision_range_ = 3.0;
	device_setting.draw_extend_ = 1.0;
	device_setting.draw_rotate_ = 0.0;
	device_setting.object_group_ = eOBJECT::GROUP::USER_ATTACK1;
	dpx_teemo_->device_setting_id_ = nya_device_->LoadSetting(&device_setting);
	// エフェクト追加
	effect_setting.effect_div_max_ = 3;
	effect_setting.effect_interval_time_ = 5;
	effect_setting.effect_move_x_ = 0;
	effect_setting.effect_move_y_ = 0;
	effect_setting.graphic_draw_angle_ = 0;
	effect_setting.graphic_draw_extend_ = 1.0;
	effect_setting.graphic_file_id_ = nya_graphic_->LoadFile(4, 1, 64, 64, "img/teemo_user_attack_effect.png");
	effect_setting.object_group_ = eOBJECT::GROUP::USER_ATTACK_EFFECT1;
	effect_setting_id = nya_effect_->LoadSetting(&effect_setting);
	nya_device_->SetEffect(effect_setting_id);
	// 画像追加
	graphic_file_id = nya_graphic_->LoadFile("img/teemo_user_attack.png");
	nya_device_->SetGraphic(graphic_file_id, 0);

	// NyaEffectとプロパティの設定
	effect_setting.effect_div_max_ = 7;
	effect_setting.effect_interval_time_ = 10;
	effect_setting.effect_move_x_ = 0;
	effect_setting.effect_move_y_ = 0;
	effect_setting.graphic_draw_angle_ = 0;
	effect_setting.graphic_draw_extend_ = 1.0;
	effect_setting.graphic_file_id_ = nya_graphic_->LoadFile(4, 2, 80, 80, "Death80.png");
	effect_setting.object_group_ = eOBJECT::GROUP::USER_EFFECT1;
	epx_teemo_->setting_id_ = nya_effect_->LoadSetting(&effect_setting);
	
	// NyaGraphicプロパティの設定
	gpx4_teemo_->draw_angle_ = 0;
	gpx4_teemo_->extend_rate_ = 1.0;
	gpx4_teemo_->file_id_ = nya_graphic_->LoadFile(2, 1, 32, 32, "img/teemo_div.png");
	gpx4_teemo_->flag_trans_ = true;
	gpx4_teemo_->flag_turn_ = false;
	gpx4_teemo_->object_group_ = eOBJECT::GROUP::USER1;

	// NyaPositionプロパティの設定
	phx_teemo_->health_max_ = 100;
	phx_teemo_->health_now_ = 100;
	phx_teemo_->collision_pow_ = 1;
	phx_teemo_->collision_range_ = 20;
	phx_teemo_->grid_x_ = 100;
	phx_teemo_->grid_y_ = 500;



	// デバッグ
	NyaString::SettingFont("teemo_font", 10, 2);
}


TeemoUser::~TeemoUser()
{
	delete nya_device_;
	delete nya_effect_;
	delete nya_graphic_;
	delete nya_position_;
	delete dpx_teemo_;
	delete epx_teemo_;
	delete gpx4_teemo_;
}


void TeemoUser::Init(void)
{

}


void TeemoUser::Action(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::RIGHT)) {
		phx_teemo_->grid_x_ += 5;
	} else if (NyaInput::GetKeyFlagNow(eINPUT::KEY::LEFT)) {
		phx_teemo_->grid_x_ -= 5;
	} else if (NyaInput::GetKeyFlagNow(eINPUT::KEY::UP)) {
		phx_teemo_->grid_y_ -= 5;
	} else if (NyaInput::GetKeyFlagNow(eINPUT::KEY::DOWN)) {
		phx_teemo_->grid_y_ += 5;
	}

	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::Q) == true && count_ % 10 == 0) {
		dpx_teemo_->draw_angle_ = -90.0;
		dpx_teemo_->move_angle_ = -90.0;
		dpx_teemo_->move_speed_ = 10.0;
		dpx_teemo_->create_x_ = phx_teemo_->grid_x_;
		dpx_teemo_->create_y_ = phx_teemo_->grid_y_;
		nya_device_->Attack(dpx_teemo_);
	}
	
	nya_position_->Collision(phx_teemo_, eOBJECT::GROUP::USER1);


	count_++;

	// デバッグ
	NyaString::Write("teemo_font", white, 50, 70, "[50, 70] teemo count = %d", count_);
	NyaString::Write("teemo_font", white, 50, 110, "[50, 110] teemo x = %d", (int)phx_teemo_->grid_x_);
	NyaString::Write("teemo_font", white, 50, 130, "[50, 130] teemo y = %d", (int)phx_teemo_->grid_y_);
}

void TeemoUser::Draw(void)
{
	//gpx4_teemo_->pos_cx_ = (int)phx_teemo_->x_;
	//gpx4_teemo_->pos_cy_ = (int)phx_teemo_->y_;
	//nya_graphic_->Draw(gpx4_teemo_);

	gpx4_teemo_->pos_cx_ = (int)phx_teemo_->grid_x_;
	gpx4_teemo_->pos_cy_ = (int)phx_teemo_->grid_y_;
	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::RIGHT)) {
		gpx4_teemo_->file_div_ = 1;
	} else {
		gpx4_teemo_->file_div_ = 0;
	}
	nya_graphic_->Draw(gpx4_teemo_);

	if (count_ % 200 == 0) {
		epx_teemo_->grid_x_ = 500;
		epx_teemo_->grid_y_ = 500;
//		nya_effect_->Draw(epx_teemo_);
	}

}

