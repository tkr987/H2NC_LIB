#include <tuple>
#include "NyaDefine.h"
#include "NyaDevice.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "TeemoTarget.h"

using namespace H2NLIB;


TeemoTarget::TeemoTarget()
{
	DeviceSetting device_setting;

	count_ = 0;


	nya_device_ = new NyaDevice;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
//	nya_position_->SettingCollision(eOBJECT::GROUP::TARGET_ATTACK1, eOBJECT::GROUP::USER1);
//	nya_position_->SettingCollisionHighAccuracy(eOBJECT::GROUP::TARGET_ATTACK1);


	// dpx Ý’è
	dpx_teemo_ = new DevicePropertyX;
	device_setting.graphic_file_div_ = 0;
	device_setting.graphic_file_id_ = nya_graphic_->LoadFile("attack.png");
	device_setting.graphic_draw_extend_ = 1;
	device_setting.graphic_draw_rotate_ = 0;
	device_setting.object_group_ = eOBJECT::GROUP::TARGET_ATTACK1;
	device_setting.position_collide_pow_ = 10;
	device_setting.position_collide_range_ = 2;
	dpx_teemo_->setting_id_ = nya_device_->LoadSetting(&device_setting);

	// gpx Ý’è
	gpx4_teemo_ = new GraphicPropertyX4;
	gpx4_teemo_->draw_angle_ = 0;
	gpx4_teemo_->extend_rate_ = 1.0;
	gpx4_teemo_->file_div_ = 0;
	gpx4_teemo_->file_id_ = nya_graphic_->LoadFile("teemo_target.png");
	gpx4_teemo_->flag_trans_ = true;
	gpx4_teemo_->flag_turn_ = false;
	gpx4_teemo_->object_group_ = eOBJECT::GROUP::TARGET1;

	// phx Ý’è
	phx_teemo_ = nya_position_->Create();
	phx_teemo_->health_max_ = 1;
	phx_teemo_->health_now_ = 1;
	phx_teemo_->pow_ = 1;
	phx_teemo_->range_ = 1;
	phx_teemo_->x_ = 400;
	phx_teemo_->y_ = 200;
}


TeemoTarget::~TeemoTarget()
{

	delete nya_device_;
	delete nya_graphic_;
	delete nya_position_;
	delete dpx_teemo_;
	delete gpx4_teemo_;
}


void TeemoTarget::Action(void)
{

	if (count_ % 120 == 0) {
		dpx_teemo_->draw_angle_ = 0;
		dpx_teemo_->move_angle_ = 110;
		dpx_teemo_->move_speed_ = 1;
		dpx_teemo_->create_x_ = phx_teemo_->x_;
		dpx_teemo_->create_y_ = phx_teemo_->y_;
		nya_device_->Attack(dpx_teemo_);
	}

	count_++;

}

void TeemoTarget::Draw(void)
{
	gpx4_teemo_->pos_cx_ = (int)phx_teemo_->x_;
	gpx4_teemo_->pos_cy_ = (int)phx_teemo_->y_;
	nya_graphic_->Draw(gpx4_teemo_);
}

void TeemoTarget::Init(void)
{


}

