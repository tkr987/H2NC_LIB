#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "TeemoEnum.h"
#include "TeemoTargetEx3b.h"

using namespace H2NLIB;

TeemoExDevice311::TeemoExDevice311()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_power_ = 1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_RED1;
	dpx_->move_speed_ = 3;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_red1.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

TeemoExDevice311::~TeemoExDevice311()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}


TeemoEx3bMain::TeemoEx3bMain()
{
	gpx_ = new GraphicPropertyX4;
	phandle_ = NyaPosition::CreateHandle();
}

TeemoEx3bMain::~TeemoEx3bMain()
{
	delete gpx_;
	gpx_ = nullptr;
	delete phandle_;
	phandle_ = nullptr;
}

TeemoTargetEx3b::TeemoTargetEx3b()
{
	count_frame_ = 0;
	
	// main メンバを初期化
	NyaGraphic::LoadGraphicFile("img/target/teemo_ex3b.png", &main_.gpx_->file_);
	main_.phandle_->health_ = 1000;
	main_.phandle_->collision_power_ = 1;
	main_.phandle_->collision_range_ = 20;
	main_.phandle_->grid_x_ = -100;
	main_.phandle_->grid_y_ = -100;
}


TeemoTargetEx3b::~TeemoTargetEx3b()
{
	NyaGraphic::DeleteGraphicFile(&main_.gpx_->file_);
}

void TeemoTargetEx3b::MissionRun(void)
{
	static int mode = 1;

	switch (mode)
	{
	case 1:
		Act1();
		Draw1();
		break;
	}

	count_frame_++;

#ifdef __DEBUG__
		NyaString::Write("design_fps_font", white, 50, 90, "[50, 90] count_frame = %u", count_frame_);
#endif
}

void TeemoTargetEx3b::Act1(void)
{
	PositionHandle* phandle_user = nullptr;

	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, SCREEN_MAX_X / 2, SCREEN_MIN_Y + 150, FPS_MAX * 4);

	if (count_frame_ < FPS_MAX * 4)
		return;

	if (count_frame_ % 60 == 0)
	{ 
		NyaPosition::FindHandle("user_main_handle", phandle_user);
		main_.device11_.dpx_->move_angle_deg_ =  NyaPosition::Angle(main_.phandle_, phandle_user);
		NyaDevice::Attack1414(main_.device11_.dpx_, main_.device11_.gadget_gpx_, main_.device11_.epx_, main_.device11_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
	}

}

void TeemoTargetEx3b::Draw1(void)
{

}

//void TeemoTargetEx4::Act2(void)
//{
//	InterfaceHandleMissionEx* ihandle_mission_ex;
//	InterfaceHandleMissionSkill *ihandle_mission_skill;
//
//	cube2_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 70;
//	cube2_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
//	cube2_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_     ;
//	cube2_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
//	cube2_collection_[2].phandle_->grid_x_ = main_.phandle_->grid_x_ + 70;
//	cube2_collection_[2].phandle_->grid_y_ = main_.phandle_->grid_y_ - 70;
//	cube2_collection_[3].phandle_->grid_x_ = main_.phandle_->grid_x_ + 70;
//	cube2_collection_[3].phandle_->grid_y_ = main_.phandle_->grid_y_     ;
//	cube2_collection_[4].phandle_->grid_x_ = main_.phandle_->grid_x_ + 70;
//	cube2_collection_[4].phandle_->grid_y_ = main_.phandle_->grid_y_ + 70;
//	cube2_collection_[5].phandle_->grid_x_ = main_.phandle_->grid_x_     ;
//	cube2_collection_[5].phandle_->grid_y_ = main_.phandle_->grid_y_ + 70;
//	cube2_collection_[6].phandle_->grid_x_ = main_.phandle_->grid_x_ - 70;
//	cube2_collection_[6].phandle_->grid_y_ = main_.phandle_->grid_y_ + 70;
//	cube2_collection_[7].phandle_->grid_x_ = main_.phandle_->grid_x_ - 70;
//	cube2_collection_[7].phandle_->grid_y_ = main_.phandle_->grid_y_     ;
//
//	// 衝突判定　衝突ダメージだけ経験値を追加
//	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
//	ihandle_mission_skill = NyaInterface::GetHandleMissionSkill();
//	ihandle_mission_skill->AddExp(main_.phandle_->collision_hit_);
//
//	// ここから下の処理は
//	// フレームカウントFPS_MAX * 4以上で実行する
//	if (count_frame_ < FPS_MAX * 3)
//		return;
//
//	if (count_frame_ % 2 == 0)
//	{
//		for (int i = 0; i < 8; i+=2)
//		{
//			cube2_collection_[i].device2_.dpx_->create_x_ = cube2_collection_[i].phandle_->grid_x_;
//			cube2_collection_[i].device2_.dpx_->create_y_ = cube2_collection_[i].phandle_->grid_y_;
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ += 8;
//			NyaDevice::Attack1414(cube2_collection_[i].device2_.dpx_, cube2_collection_[i].device2_.gadget_gpx_, cube2_collection_[i].device2_.epx_, cube2_collection_[i].device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ += 180;
//			NyaDevice::Attack1414(cube2_collection_[i].device2_.dpx_, cube2_collection_[i].device2_.gadget_gpx_, cube2_collection_[i].device2_.epx_, cube2_collection_[i].device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ += 180;
//		}
//		for (int i = 1; i < 8; i+=2)
//		{
//			cube2_collection_[i].device2_.dpx_->create_x_ = cube2_collection_[i].phandle_->grid_x_;
//			cube2_collection_[i].device2_.dpx_->create_y_ = cube2_collection_[i].phandle_->grid_y_;
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ -= 8;
//			NyaDevice::Attack1414(cube2_collection_[i].device2_.dpx_, cube2_collection_[i].device2_.gadget_gpx_, cube2_collection_[i].device2_.epx_, cube2_collection_[i].device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ -= 180;
//			NyaDevice::Attack1414(cube2_collection_[i].device2_.dpx_, cube2_collection_[i].device2_.gadget_gpx_, cube2_collection_[i].device2_.epx_, cube2_collection_[i].device2_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
//			cube2_collection_[i].device2_.dpx_->move_angle_deg_ -= 180;
//		}
//	}
//
//	// 移動処理
//	if (count_frame_ % FPS_MAX == 0)
//	{
//		int move_end_x = (int)main_.phandle_->grid_x_ + NyaInput::GetRand(-20, 20);
//		int move_end_y = (int)main_.phandle_->grid_y_ + NyaInput::GetRand(-20, 20);
//		if (SCREEN_MIN_X + 250 < move_end_x  && move_end_x < SCREEN_MAX_X - 250 && SCREEN_MIN_Y + 140 < move_end_y && move_end_y < SCREEN_MIN_Y + 200)
//		NyaPosition::MoveGridMode(main_.phandle_, move_end_x, move_end_y, FPS_MAX - 3);
//	}
//}

