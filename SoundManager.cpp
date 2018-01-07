#include "DxLib.h"
#include "SoundManager.h"
#define SOUND_FILE_MAXSIZE		128
#define SOUND_PLAY_MAXSIZE		128

using namespace std;
using namespace NH2;
int SoundManager::sload_num_;
int SoundManager::splay_num_;
vector<SoundLoad> SoundManager::vec_sload_;
vector<SoundPlay> SoundManager::vec_splay_;


// *************
//  初期化関連
// *************


void SoundManager::Clear(void)
{
	InitSoundMem();
	sload_num_ = 0;
	splay_num_ = 0;
}

void SoundManager::End(void)
{

}

void SoundManager::Init(void)
{
	if (vec_sload_.empty())
		vec_sload_.resize(SOUND_FILE_MAXSIZE);
	if (vec_splay_.empty())
		vec_splay_.resize(SOUND_PLAY_MAXSIZE);

	Clear();
}


// ***************
//  その他の関数
// ***************


/**
@brief サウンド読み込み関数
@param filename ファイル名
@retval  0 成功
@retval -1 失敗
@note
メモリにサウンドファイルを読み込む。
**/
int SoundManager::Load(std::string filename)
{
	if (sload_num_ == SOUND_FILE_MAXSIZE)
		return -1;

	for (int n = 0; n < sload_num_; n++) {
		if (vec_sload_[n].filename_.compare(filename) == 0)
			return vec_sload_[n].id_;
	}
	vec_sload_[sload_num_].filename_ = filename;
	vec_sload_[sload_num_].id_ = LoadSoundMem(filename.c_str());
	sload_num_++;

	return vec_sload_[sload_num_ - 1].id_;
}


/**
@brief サウンド再生関数
@param id サウンドid
@param type 再生モード
@param posflag 再生位置(指定しなければtrue)
@retval  0 成功
@retval -1 失敗
@note
 爆音を避けるため、同じサウンドidは重複して再生されない。
 再生されるタイミングはSoundUpdater::Run()を呼び出したとき。
 再生モードおよび再生位置はDXLIB::PlaySoundMem()に準拠。
**/
int SoundManager::Play(int id, int mode, bool posflag)
{
	if (splay_num_ == SOUND_PLAY_MAXSIZE)
		return -1;

	for (int i = 0; i < splay_num_; i++) {
		if (vec_splay_[i].id_ == id)
			return -1;
	}

	vec_splay_[splay_num_].id_ = id;
	vec_splay_[splay_num_].mode_ = mode;
	vec_splay_[splay_num_].posflag_ = posflag;
	splay_num_++;

	return 0;
}

void SoundManager::ChangeVolume(int id, int set_volume)
{
	ChangeVolumeSoundMem(set_volume, id);
}

void SoundManager::Stop(int id)
{
	StopSoundMem(id);
}

