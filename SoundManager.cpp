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
//  �������֘A
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
//  ���̑��̊֐�
// ***************


/**
@brief �T�E���h�ǂݍ��݊֐�
@param filename �t�@�C����
@retval  0 ����
@retval -1 ���s
@note
�������ɃT�E���h�t�@�C����ǂݍ��ށB
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
@brief �T�E���h�Đ��֐�
@param id �T�E���hid
@param type �Đ����[�h
@param posflag �Đ��ʒu(�w�肵�Ȃ����true)
@retval  0 ����
@retval -1 ���s
@note
 ����������邽�߁A�����T�E���hid�͏d�����čĐ�����Ȃ��B
 �Đ������^�C�~���O��SoundUpdater::Run()���Ăяo�����Ƃ��B
 �Đ����[�h����эĐ��ʒu��DXLIB::PlaySoundMem()�ɏ����B
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

