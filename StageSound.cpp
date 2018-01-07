#include "DxLib.h"
#include "StageSound.h"
#include "SoundManager.h"
#include "DesignManager.h"

using namespace NH2;


void StageSound::MemoryInit(void)
{

}

void StageSound::MemoryEnd(void)
{

}

void StageSound::DataClear(void)
{

}


void StageSound::DataLoad(eGEVENT::TYPE type)
{
	// ファイルパス
	if (type == eGEVENT::TYPE::STAGE1_HARD_LOAD) {
		filepass_sound_bgm_boss_ = "data/sound/bgm_boss_Aqui-Priestess.mp3";
		filepass_sound_bgm_stage_ = "data/sound/bgm_st01_Anbrosia.mp3";
	} else if (type == eGEVENT::TYPE::STAGE2_HARD_LOAD) {
		filepass_sound_bgm_boss_ = "data/sound/bgm_boss_Aqui-Priestess.mp3";
		filepass_sound_bgm_stage_ = "data/sound/bgm_st01_Anbrosia.mp3";
	} else if (type == eGEVENT::TYPE::STAGE3_HARD_LOAD) {
		filepass_sound_bgm_boss_ = "data/sound/bgm_boss_Aqui-Priestess.mp3";
		filepass_sound_bgm_stage_ = "data/sound/Stage04Angelique.mp3";
	}

	// sound file load
	soundfile_bgm_boss_ = SoundManager::Load(filepass_sound_bgm_boss_);
	soundfile_bgm_stage_ = SoundManager::Load(filepass_sound_bgm_stage_);
	// 変数 初期化
	frames_ = 6400;
	phase_ = 10;
	volume_ = 255;
}

void StageSound::Run(void)
{
	double boss_health;
	int star;
	const int frames_boss_start = 6300;

	// case 10: stage bgm 初期化
	// case 11: stage bgm 通常動作
	// case 12: stage bgm フェードアウト
	// case 13: stage bgm 停止
	// case 14: stage bgm 再開
	// case 20: boss bgm 初期化
	// case 21: boss bgm 通常動作
	// case 22: boss bgm 停止
	// case 
	DesignManager::GetStar(&star);
	switch (phase_) {
	case 10:
		SoundManager::Play(soundfile_bgm_stage_, DX_PLAYTYPE_BACK);
		SetVolumeMusic(volume_);
		phase_ = 11;
		break;
	case 11:
		if (frames_boss_start < frames_)
			phase_ = 12;
		if (star == -1)
			phase_ = 13;
		break;
	case 12:
		volume_ -= 2;
		SoundManager::ChangeVolume(soundfile_bgm_stage_, volume_);
		if (volume_ < 3) {
			SoundManager::Stop(soundfile_bgm_stage_);
			phase_ = 20;
		}
		break;
	case 13:
		SoundManager::Stop(soundfile_bgm_stage_);
		if (star != -1)
			phase_ = 14;
		break;
	case 14:
		SoundManager::Play(soundfile_bgm_stage_, DX_PLAYTYPE_BACK, false);
		phase_ = 11;
		break;
	case 20:
		SoundManager::Play(soundfile_bgm_boss_, DX_PLAYTYPE_BACK);
		SoundManager::ChangeVolume(soundfile_bgm_boss_, 170);
		phase_ = 21;
		break;
	case 21:
		DesignManager::GetBossHealth(&boss_health);
		if (boss_health <= 0)
			phase_ = 22;
		break;
	case 22:
		SoundManager::Stop(soundfile_bgm_boss_);
		break;
	case 23:
		SoundManager::Stop(soundfile_bgm_boss_);
		if (star != -1)
			phase_ = 24;
		break;
	case 24:
		SoundManager::Play(soundfile_bgm_boss_, DX_PLAYTYPE_BACK, false);
		phase_ = 21;
		break;
	}

	if (star != -1)
		frames_++;
}

