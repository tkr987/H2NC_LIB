#include "DxLib.h"
#include "NyaSound.h"

using namespace std;
using namespace H2NLIB;

std::list<SoundFile> NyaSound::file_collection_;
std::deque<SoundPropertyX> NyaSound::play_collection_;

//**********************
// class SoundFile
//**********************

SoundFile& SoundFile::operator=(const SoundFile& file)
{
	id_ = file.id_;
	pass_.clear();
	pass_ = file.pass_;
	return *this;
}

//***************************
// class SoundPropertyX
//***************************

SoundPropertyX& SoundPropertyX::operator=(SoundPropertyX& sp)
{
	loop_ = sp.loop_;
	file_ = sp.file_;
	return *this;
}

//**********************
// class NyaSound
//**********************

void NyaSound::ChangeVolume(SoundFile* file, int volume)
{
	double change_value = 255.0 * (double)volume / 100.0;

	ChangeVolumeSoundMem((int)change_value, file->id_);
}

void NyaSound::DeleteSoundFile(SoundFile* file)
{
	// ファイルパスが同じファイルを削除する
	for (list<SoundFile>::iterator it = file_collection_.begin(); it != file_collection_.end(); ++it)
	{
		if (it->pass_ == file->pass_)
		{
			DeleteSoundMem(it->id_);
			file_collection_.erase(it);
			break;
		}
	}
}

void NyaSound::LoadFile(std::string file_pass, SoundFile* file)
{
	list<SoundFile>::iterator it;
	SoundFile new_file;

	// ロード済みファイルなら新しくロードする必要ない
	for (auto& e : file_collection_)
	{
		if (e.pass_ == file_pass)
		{
			*file = e;
			return;
		}
	}

	// サウンドファイルをメモリにロードする
	new_file.id_ = LoadSoundMem(file_pass.c_str());
	new_file.pass_ = file_pass;
	file_collection_.push_front(new_file);

	// ロード結果を返す
	if (file != nullptr)
		*file = new_file;
}


void NyaSound::Play(const SoundPropertyX* spx)
{
	if (spx == nullptr)
		return;

	play_collection_.push_back(*spx);
}


void NyaSound::Run(void)
{
	SoundPropertyX* sp;

	while (!play_collection_.empty())
	{
		sp = &play_collection_.front();
		PlaySoundMem(sp->file_.id_, DX_PLAYTYPE_BACK, sp->loop_);
		play_collection_.pop_front();
	}
}


