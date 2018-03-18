#include "TeemoTargetEx.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaTarget.h"

using namespace H2NLIB;



TeemoTargetEx::TeemoTargetEx()
{
	count_ = 0;

	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
	gpx4_teemo_ = new GraphicPropertyX4;
	phx_teemo_ = nya_position_->Create();

	// NyaDevice�ƃv���p�e�B�̐ݒ�
	//device_setting.collision_pow_ = 1.0;
	//device_setting.collision_range_ = 2.0;
	//device_setting.draw_extend_ = 1.0;
	//device_setting.draw_rotate_ = 0.0;
	//device_setting.object_group_ = eOBJECT::NUM::TARGET_ATTACK1;
	//dpx_teemo_->device_setting_id_ = nya_device_->LoadSetting(&device_setting);

	//graphic_id = nya_graphic_->LoadFile("img/attack.png");
	//nya_device_->SetGraphic(graphic_id, 0);

	// NyaGraphic�v���p�e�B�̐ݒ�
	gpx4_teemo_->draw_angle_ = 0;
	gpx4_teemo_->extend_rate_ = 1.0;
	gpx4_teemo_->file_div_ = 0;
	gpx4_teemo_->file_id_ = nya_graphic_->LoadFile("img/teemo_ex.png");
	gpx4_teemo_->flag_trans_ = true;
	gpx4_teemo_->flag_turn_ = false;
	gpx4_teemo_->object_group_ = eOBJECT::NUM::TARGET1;

	// NyaPosition�v���p�e�B�̐ݒ�
	phx_teemo_->health_max_ = 1;
	phx_teemo_->health_now_ = 1;
	phx_teemo_->collision_pow_ = 1.0;
	phx_teemo_->collision_range_ = 20.0;
	phx_teemo_->grid_x_ = 400;
	phx_teemo_->grid_y_ = 200;
}


TeemoTargetEx::~TeemoTargetEx()
{

}

void TeemoTargetEx::Act(void)
{
	if (phx_teemo_->health_now_ < 0)
	{

	}
}

void TeemoTargetEx::Draw(void)
{
	gpx4_teemo_->pos_cx_ = (int)phx_teemo_->grid_x_;
	gpx4_teemo_->pos_cy_ = (int)phx_teemo_->grid_y_;
	nya_graphic_->Draw(gpx4_teemo_);
}