#include "NyaDesign.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaTarget.h"
#include "TeemoTargetEx.h"

using namespace H2NLIB;



TeemoTargetEx::TeemoTargetEx()
{
	count_ = 0;

	nya_design_ = new NyaDesign;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
	gpx4_teemo_ = new GraphicPropertyX4;
	phx_teemo_ = nya_position_->Create();

	// NyaDeviceとプロパティの設定
	//device_setting.collision_pow_ = 1.0;
	//device_setting.collision_range_ = 2.0;
	//device_setting.draw_extend_ = 1.0;
	//device_setting.draw_rotate_ = 0.0;
	//device_setting.object_group_ = eOBJECT::NUM::TARGET_ATTACK1;
	//dpx_teemo_->device_setting_id_ = nya_device_->LoadSetting(&device_setting);

	//graphic_id = nya_graphic_->LoadFile("img/attack.png");
	//nya_device_->SetGraphic(graphic_id, 0);

	// NyaGraphicプロパティの設定
	gpx4_teemo_->draw_angle_ = 0;
	gpx4_teemo_->extend_rate_ = 1.0;
	gpx4_teemo_->file_div_ = 0;
	nya_graphic_->LoadGraphicFile("img/teemo_ex.png", &gpx4_teemo_->graphic_file_);
	gpx4_teemo_->flag_trans_ = true;
	gpx4_teemo_->flag_turn_ = false;
	gpx4_teemo_->object_group_ = eOBJECT::NUM::TARGET1;

	// NyaPositionプロパティの設定
	phx_teemo_->health_max_ = 100;
	phx_teemo_->health_now_ = 100;
	phx_teemo_->collision_pow_ = 1.0;
	phx_teemo_->collision_range_ = 20.0;
	phx_teemo_->grid_x_ = 400;
	phx_teemo_->grid_y_ = 200;
	nya_position_->SettingCollision(eOBJECT::NUM::TARGET1, eOBJECT::NUM::USER_ATTACK1);
}


TeemoTargetEx::~TeemoTargetEx()
{
	delete nya_design_;
	delete nya_graphic_;
	delete nya_position_;
	delete gpx4_teemo_;
}

void TeemoTargetEx::Act(void)
{
	if (count_ == 1)
	{
		nya_design_->Warning(5);
		nya_design_->ExMode(true);
		nya_design_->SetExValue(100);
	}

	nya_position_->Collision(phx_teemo_, eOBJECT::NUM::TARGET1);
	

	if (phx_teemo_->health_now_ <= 0)
	{
		nya_design_->SetProcess(ePROCESS::MISSION_CLEAR);
	}

	count_++;
}

void TeemoTargetEx::Draw(void)
{
	gpx4_teemo_->draw_grid_cx_ = (int)phx_teemo_->grid_x_;
	gpx4_teemo_->draw_grid_cy_ = (int)phx_teemo_->grid_y_;
	nya_graphic_->Draw(gpx4_teemo_);

	if (0 < phx_teemo_->health_now_) 
	{
		nya_design_->SetExValue(phx_teemo_->health_now_ / phx_teemo_->health_max_ * 100);
	}
	else
	{
		nya_design_->SetExValue(0);		
	}

}
