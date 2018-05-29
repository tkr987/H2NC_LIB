#include "DxLib.h"
#include "NyaSound.h"
#include "NyaDesign.h"

using namespace std;
using namespace H2NLIB;

std::list<SoundFile> NyaSound::file_collection_;
std::deque<SoundProperty> NyaSound::play_collection_;

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
// class SoundProperty
//***************************

SoundProperty& SoundProperty::operator=(SoundProperty& sp)
{
	loop_ = sp.loop_;
	sound_file_ = sp.sound_file_;
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

void NyaSound::LoadSoundFile(std::string file_pass, SoundFile* file)
{
	list<SoundFile>::iterator it;
	const SoundFile empty_file;

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
	file_collection_.push_front(empty_file);
	it = file_collection_.begin();
	it->id_ = LoadSoundMem(file_pass.c_str());
	it->pass_ = file_pass;

	// ロード結果を返す
	*file = *it;
}


void NyaSound::Play(const SoundProperty* sp)
{
	if (sp == nullptr)
		return;

	play_collection_.push_back(*sp);
}


void NyaSound::Run(void)
{
	SoundProperty* sp;

	while (!play_collection_.empty())
	{
		sp = &play_collection_.front();
		PlaySoundMem(sp->sound_file_.id_, DX_PLAYTYPE_BACK, sp->loop_);
		play_collection_.pop_front();
	}
}


