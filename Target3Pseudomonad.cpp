#include "HNLIB.h"
#include "Target3Pseudomonad.h"
#include "TeemoEnum.h"

using namespace HNLIB;

Target3PseudomonadMain::Target3PseudomonadMain()
{
	gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/target_pseudomonad.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;

	lock_.LoadGraphic("img/target/lock_pseudomonad.png");
}

Target3PseudomonadMain::~Target3PseudomonadMain()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);

	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

Target3Pseudomonad::Target3Pseudomonad(int x, int y, int move_max_x, int move_max_y, bool turn)
{
	// main オブジェクト
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	main_.phandle_->health_ = 100000;
	main_.gpx_->flag_turn_ = turn;
	// 衝突判定用
	main_collection_[0].phandle_->grid_x_ = x - 80;
	main_collection_[0].phandle_->grid_y_ = y + 20;
	main_collection_[1].phandle_->grid_x_ = x - 60;
	main_collection_[1].phandle_->grid_y_ = y + 20;
	main_collection_[2].phandle_->grid_x_ = x - 20;
	main_collection_[2].phandle_->grid_y_ = y + 20;
	main_collection_[3].phandle_->grid_x_ = x + 20;
	main_collection_[3].phandle_->grid_y_ = y + 20;
	main_collection_[4].phandle_->grid_x_ = x + 60;
	main_collection_[4].phandle_->grid_y_ = y + 20;
	main_collection_[4].phandle_->grid_x_ = x + 80;
	main_collection_[4].phandle_->grid_y_ = y - 20;
	main_collection_[5].phandle_->grid_x_ = x - 20;
	main_collection_[5].phandle_->grid_y_ = y - 20;
	main_collection_[6].phandle_->grid_x_ = x + 20;
	main_collection_[6].phandle_->grid_y_ = y - 20;
	main_collection_[8].phandle_->grid_x_ = x + 40;
	main_collection_[8].phandle_->grid_y_ = y - 20;
	for (auto&e : main_collection_)
		e.phandle_->health_ = 100000;
	// その他
	mode_ = 1;
	move_max_x_ = move_max_x;
	move_max_y_ = move_max_y;
	turn_ = turn;
}

Target3Pseudomonad::~Target3Pseudomonad()
{

}

void Target3Pseudomonad::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		break;
	};

	main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
	for (auto& e : main_collection_)
		e.phandle_->grid_y_ += 0.2;
	count_frame_++;
}

void Target3Pseudomonad::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		break;
	};
}

void Target3Pseudomonad::Act1(void)
{
	// 初期位置へ移動
	if (count_frame_ == 1)
		NyaPosition::MoveGridMode(main_.phandle_, move_max_x_, move_max_y_, FPS_MAX * 2);

	// 衝突判定もmainに追従
	main_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 80;
	main_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ + 20;
	main_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ - 60;
	main_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ + 20;
	main_collection_[2].phandle_->grid_x_ = main_.phandle_->grid_x_ - 20;
	main_collection_[2].phandle_->grid_y_ = main_.phandle_->grid_y_ + 20;
	main_collection_[3].phandle_->grid_x_ = main_.phandle_->grid_x_ + 20;
	main_collection_[3].phandle_->grid_y_ = main_.phandle_->grid_y_ + 20;
	main_collection_[4].phandle_->grid_x_ = main_.phandle_->grid_x_ + 60;
	main_collection_[4].phandle_->grid_y_ = main_.phandle_->grid_y_ + 20;
	main_collection_[4].phandle_->grid_x_ = main_.phandle_->grid_x_ + 80;
	main_collection_[4].phandle_->grid_y_ = main_.phandle_->grid_y_ - 20;
	main_collection_[5].phandle_->grid_x_ = main_.phandle_->grid_x_ - 20;
	main_collection_[5].phandle_->grid_y_ = main_.phandle_->grid_y_ - 20;
	main_collection_[6].phandle_->grid_x_ = main_.phandle_->grid_x_ + 20;
	main_collection_[6].phandle_->grid_y_ = main_.phandle_->grid_y_ - 20;
	main_collection_[8].phandle_->grid_x_ = main_.phandle_->grid_x_ + 40;
	main_collection_[8].phandle_->grid_y_ = main_.phandle_->grid_y_ - 20;

	// 衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (auto& e : main_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
		main_.phandle_->collision_hit_damage_ += e.phandle_->collision_hit_damage_;
	}
}

void Target3Pseudomonad::Draw1(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	// main ロック描画
	main_.lock_.Run(main_.phandle_);
}



