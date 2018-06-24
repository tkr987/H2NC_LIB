#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "TeemoTargetEx3b.h"

using namespace H2NLIB;

TeemoEx3bMain::TeemoEx3bMain()
{
	gpx_ = new GraphicPropertyX4;
	phandle_ = new PositionHandle;
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
	Act();
	Draw();
}

void TeemoTargetEx3b::Act(void)
{

}

void TeemoTargetEx3b::Draw(void)
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