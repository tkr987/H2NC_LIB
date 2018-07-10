#include "HNLIB.h"
#include "TargetLock.h"

using namespace HNLIB;

TargetLock::TargetLock()
{
	gpx_ = new GraphicPropertyX4;
	lock_frame_ = 0;
	spx_ = new SoundPropertyX;
	NyaSound::LoadFile("sound/lock.wav", &spx_->file_);
}


TargetLock::~TargetLock()
{
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);
	NyaSound::DeleteSoundFile(&spx_->file_);
	delete gpx_;
	gpx_ = nullptr;
	delete spx_;
	spx_ = nullptr;
}

void TargetLock::LoadGraphic(std::string pass)
{
	NyaGraphic::LoadGraphicFile(pass, &gpx_->file_);
}

void TargetLock::Run(const PositionHandle* phandle)
{

	if (phandle->collision_hit_damage_ != 0)
	{	// Å‰‚ÌÕ“Ë‚È‚çŒø‰Ê‰¹‚ğÄ¶
		if (lock_frame_ == 0)
			NyaSound::Play(spx_);
		lock_frame_++;
		if (0 < lock_frame_)
			lock_frame_ = 1;
	}

	if (lock_frame_ != 0)
	{	// ˆê“xÕ“Ë”»’è‚ªtrue‚É‚È‚Á‚½‚çƒƒbƒN‚Ì•`‰æ‚Í‚P•bŠÔ‘±‚³‚¹‚é
		lock_frame_++;
		if (FPS_MAX < lock_frame_)
			lock_frame_ = 0;
		gpx_->draw_grid_cx_ = phandle->grid_x_;
		gpx_->draw_grid_cy_ = phandle->grid_y_;
		NyaGraphic::Draw(gpx_, eOBJECT::TARGET_EFFECT1);
	}
}

