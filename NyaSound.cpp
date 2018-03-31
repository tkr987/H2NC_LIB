#include "DxLib.h"
#include "NyaSound.h"
#include "NyaDesign.h"

using namespace std;
using namespace H2NLIB;

std::list<SoundFile> NyaSound::file_list_;
std::deque<SoundProperty> NyaSound::play_deque_;

NyaSound::NyaSound()
{
}




NyaSound::~NyaSound()
{

}

void NyaSound::ChangeVolume(SoundProperty* sp, int volume)
{
	double change_value = 255.0 * (double)volume / 100.0;

	ChangeVolumeSoundMem((int)change_value, sp->sound_file_.id_);
}

void NyaSound::DeleteSoundFile(SoundFile* file)
{
	// ファイルパスが同じファイルを削除する
	for (list<SoundFile>::iterator it = file_list_.begin(); it != file_list_.end(); ++it)
	{
		if (it->pass_ == file->pass_)
		{
			DeleteSoundMem(it->id_);
			file_list_.erase(it);
			break;
		}
	}
}

void NyaSound::LoadSoundFile(std::string file_pass, SoundFile* file)
{
	list<SoundFile>::iterator it;
	const SoundFile empty_file;

	// ロード済みファイルなら新しくロードする必要ない
	for (auto& e : file_list_)
	{
		if (e.pass_ == file_pass)
			*file = e;
	}

	// サウンドファイルをメモリにロードする
	file_list_.push_front(empty_file);
	it = file_list_.begin();
	it->id_ = LoadSoundMem(file_pass.c_str());
	it->pass_ = file_pass;

	// ロード結果を返す
	*file = *it;
}


void NyaSound::Play(const SoundProperty* sp)
{
	if (sp == nullptr)
		return;

	play_deque_.push_back(*sp);
}


void NyaSound::Run(void)
{
	static SoundProperty* sp;

	while (!play_deque_.empty())
	{
		sp = &play_deque_.front();
		PlaySoundMem(sp->sound_file_.id_, DX_PLAYTYPE_BACK, sp->loop_);
		play_deque_.pop_front();
	}
}


