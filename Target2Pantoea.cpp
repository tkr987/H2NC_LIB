#include "HNLIB.h"
#include "Target2Pantoea.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"
#include "TeemoLock.h"

using namespace HNLIB;

Target2PantoeaDevice::Target2PantoeaDevice()
{

}

Target2PantoeaDevice::~Target2PantoeaDevice()
{

}

Target2PantoeaMain::Target2PantoeaMain(): exp_(5000), health_max_(200)
{
	lock_ = new TeemoLock(eLOCK::PANTOEA);

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);
	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, TARGET_DEATH1_SOUND_VOLUME);

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = 1.5;
	NyaGraphic::Load(4, 1, "img/target/main_pantoea.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
	phandle_->health_ = health_max_;
}

Target2PantoeaMain::~Target2PantoeaMain()
{
	NyaGraphic::Delete(&gpx_->file_);
	NyaSound::Delete(&death_spx_->file_);

	delete lock_;
	lock_ = nullptr;
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

Target2Pantoea::Target2Pantoea(int x, int y)
{
	count_frame_ = 0;
	mode_ = 1;
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
}

Target2Pantoea::~Target2Pantoea()
{

}

void Target2Pantoea::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		if (main_.phandle_->health_ <= 0)
		{
			count_frame_ = 0;
			NyaInterface::GetHandleSkill()->AddExp(5000);
			NyaSound::Play(main_.death_spx_);
		}
		break;
	case 2:
		return;
	};

	main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
	count_frame_++;
}

void Target2Pantoea::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if (main_.phandle_->health_ <= 0)
			mode_ = 2;
		if (FPS_MAX * 20 < count_frame_)
			mode_ = 2;
		break;
	case 2:
		return;
	};
}

void Target2Pantoea::Act1(void)
{
	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
}

void Target2Pantoea::Draw1(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 30 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % 4;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_->Run(main_.phandle_);

	if (main_.phandle_->health_ <= 0)
	{	// 爆発描画
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
	}

}



