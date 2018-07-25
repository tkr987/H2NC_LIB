#include "HNLIB.h"
#include "Target1Pantoea.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"

using namespace HNLIB;

Target1PantoeaDevice::Target1PantoeaDevice()
{

}

Target1PantoeaDevice::~Target1PantoeaDevice()
{

}

Target1PantoeaMain::Target1PantoeaMain(): exp_(5000), health_max_(10)
{
	lock_ = new TeemoLock(eLOCK::PICORNA);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	death_spx_ = new SoundPropertyX;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_, death_spx_);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(4, 1, "img/target/main_pantoea.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;
	phandle_->health_ = health_max_;
}

Target1PantoeaMain::~Target1PantoeaMain() 
{
	NyaGraphic::Delete(&gpx_->file_);

	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete death_spx_;
	death_spx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

Target1Pantoea::Target1Pantoea(int x, int y)
{
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
}

Target1Pantoea::~Target1Pantoea()
{

}

void Target1Pantoea::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		if (main_.phandle_->health_ < 0)
		{
			NyaSound::Play(main_.death_spx_);
			NyaInterface::GetHandleSkill()->AddExp(main_.exp_);
		}
		break;
	case 2:
		return;
	};

	main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
	count_frame_++;
}

void Target1Pantoea::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if (main_.phandle_->health_ < 0)
			mode_ = 2;
		break;
	case 2:
		return;
	};
}

void Target1Pantoea::Act1(void)
{

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
}

void Target1Pantoea::Draw1(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 30 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);

	if (main_.phandle_->health_ < 0)
	{	// 爆発描画
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
	}

}


