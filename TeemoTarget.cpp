#include <tuple>
#include "NyaDefine.h"
#include "NyaDevice.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "TeemoTarget.h"

using namespace std;
using namespace H2NLIB;


TeemoTarget::TeemoTarget()
{
	count_ = 0;

	//nya_device_ = new NyaDevice;
	//nya_graphic_ = new NyaGraphic;
	//nya_position_ = new NyaPosition;
	//teemo_dpx1_ = new DeviceProperty1;
	//teemo_gpx4_ = new GraphicPropertyX4;
	//nya_position_->Create(teemo_ph1_);

	// NyaDeviceとプロパティの設定
	//device_setting.collision_pow_ = 1.0;
	//device_setting.collision_range_ = 2.0;
	//device_setting.draw_extend_ = 1.0;
	//device_setting.draw_rotate_ = 0.0;
	//device_setting.object_group_ = eOBJECT::NUM::TARGET_ATTACK1;
	//dpx_teemo_->device_setting_id_ = nya_device_->LoadSetting(&device_setting);

	//graphic_id = nya_graphic_->LoadFile("img/attack.png");
	//nya_device_->SetGraphic(graphic_id, 0);

	// teemo プロパティの設定
	//nya_graphic_->LoadGraphicFile("img/teemo.png", &teemo_gpx4_->graphic_file_);
	//teemo_gpx4_->object_group_ = eOBJECT::NUM::TARGET1;
	//teemo_ph1_->health_max_ = 1000;
	//teemo_ph1_->health_now_ = 1000;
	//teemo_ph1_->collision_pow_ = 1.0;
	//teemo_ph1_->collision_range_ = 20.0;
	//teemo_ph1_->grid_x_ = 400;
	//teemo_ph1_->grid_y_ = 200;
}


TeemoTarget::~TeemoTarget()
{
	//delete nya_device_;
	//delete nya_graphic_;
	//delete nya_position_;
	//delete teemo_dpx1_;
	//delete teemo_gpx4_;
}


void TeemoTarget::Act(void)
{

	//if (count_ % 120 == 0) {
	//	dpx_teemo_->draw_angle_ = 0;
	//	dpx_teemo_->move_angle_ = 110;
	//	dpx_teemo_->move_speed_ = 1;
	//	dpx_teemo_->create_x_ = phx_teemo_->grid_x_;
	//	dpx_teemo_->create_y_ = phx_teemo_->grid_y_;
	//	nya_device_->Attack(dpx_teemo_);
	//}
	
	//nya_position_->Collision(phx_teemo_, eOBJECT::NUM::TARGET1);

	count_++;

}

void TeemoTarget::Draw(void)
{
	//teemo_gpx4_->draw_grid_cx_ = (int)teemo_ph1_->grid_x_;
	//teemo_gpx4_->draw_grid_cy_ = (int)teemo_ph1_->grid_y_;
	//nya_graphic_->Draw(teemo_gpx4_);
}


