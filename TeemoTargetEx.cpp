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
	teemo_gp4_ = new GraphicProperty4;
	teemo_ph1_ = new PositionHandle1;
	nya_position_->Regist(teemo_ph1_);

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
	teemo_gp4_->draw_angle_ = 0;
	teemo_gp4_->extend_rate_ = 1.0;
	teemo_gp4_->file_div_ = 0;
	nya_graphic_->LoadGraphicFile("img/teemo_ex.png", &teemo_gp4_->graphic_file_);
	teemo_gp4_->flag_trans_ = true;
	teemo_gp4_->flag_turn_ = false;

	// NyaPositionプロパティの設定
	teemo_ph1_->health_max_ = 100;
	teemo_ph1_->health_now_ = 100;
	teemo_ph1_->collision_pow_ = 1.0;
	teemo_ph1_->collision_range_ = 20.0;
	teemo_ph1_->grid_x_ = 400;
	teemo_ph1_->grid_y_ = 200;
	nya_position_->SettingCollision(eOBJECT::NUM::TARGET1, eOBJECT::NUM::USER_ATTACK1);
}


TeemoTargetEx::~TeemoTargetEx()
{
	delete nya_design_;
	delete nya_graphic_;
	delete nya_position_;
	delete teemo_gp4_;
	delete teemo_ph1_;
}

void TeemoTargetEx::Act(void)
{
	DesignHandleMissionClear* handle_mission_clear;
	DesignHandleMissionEx* handle_mission_ex;

	if (count_ == 1)
	{
		handle_mission_ex = nya_design_->GetHandleMissionEx();
		handle_mission_ex->valid_ = true;
		handle_mission_ex->value_ = 100;
	}

	nya_position_->Collision(teemo_ph1_, eOBJECT::NUM::TARGET1);
	

	if (teemo_ph1_->health_now_ <= 0)
	{
		handle_mission_clear = nya_design_->GetHandleMissionClear();
		handle_mission_clear->valid_ = true;
	}

	count_++;
}

void TeemoTargetEx::Draw(void)
{
	DesignHandleMissionEx* handle_mission_ex;

	teemo_gp4_->draw_grid_cx_ = (int)teemo_ph1_->grid_x_;
	teemo_gp4_->draw_grid_cy_ = (int)teemo_ph1_->grid_y_;
	nya_graphic_->Draw(teemo_gp4_, eOBJECT::NUM::TARGET1);

	if (0 < teemo_ph1_->health_now_) 
	{
		handle_mission_ex = nya_design_->GetHandleMissionEx();
		handle_mission_ex->value_ = teemo_ph1_->health_now_ / teemo_ph1_->health_max_ * 100;
	}
	else
	{
		handle_mission_ex = nya_design_->GetHandleMissionEx();
		handle_mission_ex->value_ = 0;
	}

}
