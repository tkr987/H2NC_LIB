#include "HNLIB.h"
#include "TeemoLock.h"

using namespace HNLIB;

unsigned int TeemoLock::played_sound_frame_ = 0;

TeemoLock::TeemoLock()
{
	gpx_ = new GraphicPropertyX4;
	lock_frame_ = 0;
	spx_ = new SoundPropertyX;
	NyaSound::Load("sound/lock.wav", &spx_->file_);
	NyaSound::ChangeVolume(&spx_->file_, 50);
}

TeemoLock::TeemoLock(eLOCK type)
{
	lock_frame_ = 0;
	
	gpx_ = new GraphicPropertyX4;
	switch (type)
	{
	case eLOCK::ADENO:
		NyaGraphic::Load("img/target/lock_adeno.png", &gpx_->file_);
		break;
	case eLOCK::AQUIFICAE:
		NyaGraphic::Load("img/target/lock_aquificae.png", &gpx_->file_);
		break;
	case eLOCK::BACILLUS:
		NyaGraphic::Load("img/target/lock_bacillus.png", &gpx_->file_);
		break;
	case eLOCK::BORDETELLA:
		NyaGraphic::Load("img/target/lock_bordetella.png", &gpx_->file_);
		break;
	case eLOCK::CHLOROBI:
		NyaGraphic::Load("img/target/lock_chlorobi.png", &gpx_->file_);
		break;
	case eLOCK::CHLAMYDIAE:
		NyaGraphic::Load("img/target/lock_chlamydiae.png", &gpx_->file_);
		break;
	case eLOCK::DICTYOGLOMI:
		NyaGraphic::Load("img/target/lock_dictyoglomi.png", &gpx_->file_);
		break;
	case eLOCK::ECTROMELIA:
		NyaGraphic::Load("img/target/lock_ectromelia.png", &gpx_->file_);
		break;
	case eLOCK::ERWINIA:
		NyaGraphic::Load("img/target/lock_erwinia.png", &gpx_->file_);
		break;
	case eLOCK::FIRMICUTES:
		NyaGraphic::Load("img/target/lock_firmicutes.png", &gpx_->file_);
		break;
	case eLOCK::PANTOEA:
		NyaGraphic::Load("img/target/lock_pantoea.png", &gpx_->file_);
		break;
	case eLOCK::PICORNA:
		NyaGraphic::Load("img/target/lock_picorna.png", &gpx_->file_);
		break;
	case eLOCK::POLYOMA:
		NyaGraphic::Load("img/target/lock_polyoma.png", &gpx_->file_);
		break;
	case eLOCK::SHIGELLA:
		NyaGraphic::Load("img/target/lock_shigella.png", &gpx_->file_);
		break;
	case eLOCK::SPIROCHAETE:
		NyaGraphic::Load("img/target/lock_spirochaete.png", &gpx_->file_);
		break;
	case eLOCK::TENERICUTES:
		NyaGraphic::Load("img/target/lock_tenericutes.png", &gpx_->file_);
		break;
	case eLOCK::VIBRIO:
		NyaGraphic::Load("img/target/lock_vibrio.png", &gpx_->file_);
		break;
	case eLOCK::CUBE:
		NyaGraphic::Load("img/target/lock_cube.png", &gpx_->file_);
		break;
	case eLOCK::TEEMO_EX:
		NyaGraphic::Load("img/target/lock_teemo_ex.png", &gpx_->file_);
		break;
	case eLOCK::TEEMO_MARK1:
		NyaGraphic::Load("img/target/lock_teemo_mark1.png", &gpx_->file_);
		break;
	case eLOCK::TEEMO_MARK2:
		NyaGraphic::Load("img/target/lock_teemo_mark2.png", &gpx_->file_);
		break;
	case eLOCK::TEEMO_MARK3:
		NyaGraphic::Load("img/target/lock_teemo_mark3.png", &gpx_->file_);
		break;
	}

	spx_ = new SoundPropertyX;
	NyaSound::Load("sound/lock.wav", &spx_->file_);
	NyaSound::ChangeVolume(&spx_->file_, 50);
}


TeemoLock::~TeemoLock()
{
	NyaGraphic::Delete(&gpx_->file_);
	NyaSound::Delete(&spx_->file_);
	delete gpx_;
	gpx_ = nullptr;
	delete spx_;
	spx_ = nullptr;
}

void TeemoLock::LoadGraphic(eLOCK type)
{

}

void TeemoLock::LoadGraphic(std::string pass)
{
	NyaGraphic::Load(pass, &gpx_->file_);
}

void TeemoLock::Run(const PositionHandle* phandle)
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

