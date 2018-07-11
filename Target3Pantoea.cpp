#include "HNLIB.h"
#include "Target3Pantoea.h"

using namespace HNLIB;

Target3PantoeaDevice::Target3PantoeaDevice()
{

}

Target3PantoeaDevice::~Target3PantoeaDevice()
{

}

Target3PantoeaMain::Target3PantoeaMain()
{
	death_epx_ = new EffectPropertyX1;
	death_epx_->interval_time_frame_ = 3;

	death_gpx_ = new GraphicPropertyX4;
	death_gpx_->extend_rate_ = 0.5;
	NyaGraphic::LoadGraphicFile(4, 2, "img/target/death1.png", &death_gpx_->file_);

	death_spx_ = new SoundPropertyX;
	NyaSound::LoadFile("sound/target_death1.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 50);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile(3, 1, "img/target/target_pantoea.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 20;

	lock_.LoadGraphic("img/target/lock_pantoea.png");
}

Target3PantoeaMain::~Target3PantoeaMain()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaSound::DeleteSoundFile(&death_spx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);

	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

Target3Pantoea::Target3Pantoea(int x, int y)
{
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	main_.phandle_->health_ = 150;
	mode_ = 1;
}

Target3Pantoea::~Target3Pantoea()
{

}

void Target3Pantoea::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		break;
	};

	main_.phandle_->grid_y_ += 0.2;
	count_frame_++;
}

void Target3Pantoea::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		if (main_.phandle_->health_ < 0)
			mode_ = 2;
		break;
	};
}

void Target3Pantoea::Act1(void)
{

	// �Փ˔���@�Փ˃_���[�W�����o���l��ǉ�
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
}

void Target3Pantoea::Draw1(void)
{
	// main �`��
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (count_frame_ % 30 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % 3;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	main_.lock_.Run(main_.phandle_);

	if (main_.phandle_->health_ < 0)
	{	// �����`��
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaSound::Play(main_.death_spx_);
		NyaInterface::GetHandleSkill()->AddExp(10000);
	}

}

