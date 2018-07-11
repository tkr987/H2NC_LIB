#include "HNLIB.h"
#include "TargetLock.h"

using namespace HNLIB;

unsigned int TargetLock::played_sound_frame_ = 0;

TargetLock::TargetLock()
{
	gpx_ = new GraphicPropertyX4;
	lock_frame_ = 0;
	spx_ = new SoundPropertyX;
	NyaSound::LoadFile("sound/lock.wav", &spx_->file_);
	NyaSound::ChangeVolume(&spx_->file_, 50);
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
	// 最初の衝突なら効果音を再生
	if (phandle->collision_hit_damage_ != 0)
	{
		if (lock_frame_ == 0)
		{
			if (played_sound_frame_ != NyaInput::GetFrameCount())
			{	// ロック音は1フレーム1回まで再生する(重なって音量が大きくなるのを防ぐため)
				NyaSound::Play(spx_);
				played_sound_frame_ = NyaInput::GetFrameCount();
			}
		}
		lock_frame_++;
		if (0 < lock_frame_)
			lock_frame_ = 1;
	}

	if (lock_frame_ != 0)
	{	// 一度衝突判定がtrueになったらロックの描画は１秒間持続させる
		lock_frame_++;
		if (FPS_MAX < lock_frame_)
			lock_frame_ = 0;
		gpx_->draw_grid_cx_ = phandle->grid_x_;
		gpx_->draw_grid_cy_ = phandle->grid_y_;
		NyaGraphic::Draw(gpx_, eOBJECT::TARGET_EFFECT1);
	}
}

