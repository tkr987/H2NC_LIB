#include "DxLib.h"
#include "NyaSound.h"
#include "NyaDesign.h"

using namespace H2NLIB;

std::vector<SoundFile> NyaSound::file_vector_;
std::deque<SoundPropertyX> NyaSound::play_deque_;

NyaSound::NyaSound()
{
}




NyaSound::~NyaSound()
{

}

void NyaSound::ChangeVolume(SoundPropertyX* spx, int volume)
{
	ChangeVolumeSoundMem(255 * volume / 100, file_vector_[spx->file_id_].id_);
}


int NyaSound::LoadFile(std::string pass)
{
	static SoundFile file;


	file.pass_ = pass;
	file.id_ = LoadSoundMem(pass.c_str());
	file_vector_.push_back(file);

	return ((int)file_vector_.size() - 1);
}


void NyaSound::Play(std::string pass, bool loop)
{
	PlaySoundFile(pass.c_str(), loop);
}


void NyaSound::Play(SoundPropertyX* spx)
{
	if (spx == nullptr)
		return;

	play_deque_.push_back(*spx);
}


void NyaSound::Run(void)
{
	static SoundPropertyX spx;

	while (!play_deque_.empty())
	{
		spx = play_deque_.front();
		PlaySoundMem(file_vector_[spx.file_id_].id_, DX_PLAYTYPE_BACK, spx.loop_);
		play_deque_.pop_front();
	}
}


