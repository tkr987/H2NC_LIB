#include "HNLIB.h"
#include "Target2Warning.h"

using namespace HNLIB;

Target2Warning::Target2Warning(int x, int y)
{
	count_frame_ = 0;

	epx_ = new EffectPropertyX1;
	epx_->grid_x_ = x;
	epx_->grid_y_ = y;
	epx_->interval_time_frame_ = FPS_MAX * 2;

	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/target/warning.png", &effect_gpx_->file_);

	spx_ = new SoundPropertyX;
	NyaSound::Load("sound/warning2.wav", &spx_->file_);
	NyaSound::ChangeVolume(&spx_->file_, 20);
}


Target2Warning::~Target2Warning()
{
	NyaGraphic::Delete(&effect_gpx_->file_);
	
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

void Target2Warning::Act(void)
{
	count_frame_++;
}

void Target2Warning::Draw(void)
{
	if (count_frame_ == 1)
		NyaEffect::Draw(epx_, effect_gpx_, eOBJECT::TARGET_EFFECT1);
	if (count_frame_ == 2)
		NyaSound::Play(spx_);
	if (count_frame_ == FPS_MAX + 2)
		NyaSound::Play(spx_);
}


