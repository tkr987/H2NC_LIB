#include <tuple>
#include "NyaDefine.h"
#include "NyaDevice.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "TeemoUser.h"

using namespace std;
using namespace H2NLIB;

TeemoUser::TeemoUser()
{
	DeviceSetting device_setting;

	count_ = 0;

	nya_device_ = new NyaDevice;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
//	nya_position_->SettingCollision(eOBJECT::GROUP::USER_ATTACK1, eOBJECT::GROUP::TARGET1);
//	nya_position_->SettingCollision(eOBJECT::GROUP::USER1, eOBJECT::GROUP::TARGET_ATTACK1);
	nya_position_->SettingCollision(eOBJECT::GROUP::TARGET_ATTACK1, eOBJECT::GROUP::USER1);

	// gpx 設定
	gpx4_teemo_ = new GraphicPropertyX4;
	gpx4_teemo_->draw_angle_ = 0;
	gpx4_teemo_->extend_rate_ = 1.0;
	gpx4_teemo_->file_div_ = 0;
	gpx4_teemo_->file_id_ = nya_graphic_->LoadFile("teemo.png");
	gpx4_teemo_->flag_trans_ = true;
	gpx4_teemo_->flag_turn_ = false;
	gpx4_teemo_->object_group_ = eOBJECT::GROUP::USER1;

	// phx 設定
	phx_teemo_ = nya_position_->Create();
	phx_teemo_->health_max_ = 100;
	phx_teemo_->health_now_ = 100;
	phx_teemo_->pow_ = 1;
	phx_teemo_->range_ = 50;
	phx_teemo_->x_ = 100;
	phx_teemo_->y_ = 500;

	// dpx 設定
	dpx_teemo_ = new DevicePropertyX;
	device_setting.graphic_file_div_ = 0;
	device_setting.graphic_file_id_ = nya_graphic_->LoadFile("attack.png");
	device_setting.graphic_draw_extend_ = 1;
	device_setting.graphic_draw_rotate_ = 0;
	device_setting.object_group_ = eOBJECT::GROUP::USER_ATTACK1;
	device_setting.position_collide_pow_ = 1;
	device_setting.position_collide_range_ = 1;
	dpx_teemo_->setting_id_ = nya_device_->LoadSetting(&device_setting);

	// デバッグ
	NyaString::SettingFont("teemo_font", 10, 2);
}


TeemoUser::~TeemoUser()
{
	delete nya_device_;
	delete nya_graphic_;
	delete nya_position_;
	delete dpx_teemo_;
	delete gpx4_teemo_;
}


void TeemoUser::Init(void)
{

}


void TeemoUser::Action(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::RIGHT)) {
		phx_teemo_->x_ += 5;
	} else if (NyaInput::GetKeyFlagNow(eINPUT::KEY::LEFT)) {
		phx_teemo_->x_ -= 5;
	} else if (NyaInput::GetKeyFlagNow(eINPUT::KEY::UP)) {
		phx_teemo_->y_ -= 5;
	} else if (NyaInput::GetKeyFlagNow(eINPUT::KEY::DOWN)) {
		phx_teemo_->y_ += 5;
	}

	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::Q) == true && count_ % 120 == 0) {
		dpx_teemo_->draw_angle_ = 0;
		dpx_teemo_->move_angle_ = 0;
		dpx_teemo_->move_speed_ = 1;
		dpx_teemo_->create_x_ = phx_teemo_->x_;
		dpx_teemo_->create_y_ = phx_teemo_->y_;
		nya_device_->Attack(dpx_teemo_);
	}
	
	nya_position_->Collision(phx_teemo_, eOBJECT::GROUP::USER1);


	count_++;

	// デバッグ
	NyaString::Write("teemo_font", white, 50, 70, "(50, 70) teemo health = %3.3lf", phx_teemo_->health_now_);
	NyaString::Write("teemo_font", white, 50, 110, "(50, 110) teemo x = %d", (int)phx_teemo_->x_);
	NyaString::Write("teemo_font", white, 50, 130, "(50, 130) teemo y = %d", (int)phx_teemo_->y_);
}

void TeemoUser::Draw(void)
{
	gpx4_teemo_->pos_cx_ = (int)phx_teemo_->x_;
	gpx4_teemo_->pos_cy_ = (int)phx_teemo_->y_;
	nya_graphic_->Draw(gpx4_teemo_);
}

