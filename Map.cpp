#include "DxLib.h"
#include "DesignManager.h"
#include "ImgManager.h"
#include "PosManager.h"
#include "SoundManager.h"
#include "Map.h"

using namespace NH2;

void Map::MemoryInit(void)
{
	pparam_map_ = new PosParam1;
	iparam_map_ = new ImgParam1b;
}

void Map::MemoryEnd(void)
{
	delete pparam_map_;
	delete iparam_map_;
}

void Map::DataClear(void)
{

}


void Map::DataLoad(int stage)
{
	// pos パラメータ初期化
	pparam_map_->SetStartX(-21);
	pparam_map_->SetStartY(-3200);
	PosManager::Generate(eOBJECT::GROUP::MAP_BOTTOM, pparam_map_);

	// img パラメータ初期化
	iparam_map_->blend_alpha_ = 255;
	iparam_map_->blend_mode_ = DX_BLENDMODE_ADD;
	iparam_map_->flag_trans_ = false;
	iparam_map_->group_type_ = eOBJECT::GROUP::MAP_BOTTOM;

	// ファイルパス
	filepass_img_gameover_ = "data/img_map/gameover.png";
	if (stage == 1) {
		filepass_img_map_ = "data/img_map/map1.png";
		filepass_sound_bgm_boss_ = "data/sound/bgm_boss_Aqui-Priestess.mp3";
		filepass_sound_bgm_stage_ = "data/sound/bgm_st01_Anbrosia.mp3";
	} else if (stage == 2) {
		filepass_img_map_ = "data/img_map/map1.png";
	} else if (stage == 4) {
		filepass_img_map_ = "data/img_map/map1.png";
		filepass_sound_bgm_boss_ = "data/sound/bgm_boss_Aqui-Priestess.mp3";
		filepass_sound_bgm_stage_ = "data/sound/Stage04Angelique.mp3";
	}

	// 変数 初期化
	sound_phase_ = 1;
	bgm_volume_ = 255;
	frame_counter_ = 0;
	imgfile_map_ = ImgManager::LoadImg(filepass_img_map_);
	imgfile_gameover_ = ImgManager::LoadImg(filepass_img_gameover_);
	soundfile_bgm_boss_ = SoundManager::Load(filepass_sound_bgm_boss_);
	soundfile_bgm_stage_ = SoundManager::Load(filepass_sound_bgm_stage_);
}

void Map::Ran(void)
{
	frame_counter_++;

	DrawMap();
	MoveMap();
	PlaySeBgm();
}

void Map::DrawMap(void)
{

	if (6300 + 50 < frame_counter_)
		return;

	if (6300 < frame_counter_)
		iparam_map_->blend_alpha_ -= 5;


	PosManager::GetPosX(pparam_map_, &iparam_map_->pos_x_);
	PosManager::GetPosY(pparam_map_, &iparam_map_->pos_y_);
	ImgManager::Draw(imgfile_map_, 0, iparam_map_);
}

void Map::MoveMap(void)
{
	double add_y = 0.5;

	if (6400 - 10 < frame_counter_)
		return;

	PosManager::MovePosA(pparam_map_, NULL, &add_y);

	// マップ以外のオブジェクト(target)をシンクロさせて移動させる
	PosManager::MovePosC(eOBJECT::GROUP::TARGET_RUN_WALK, NULL, &add_y);
}

void Map::PlaySeBgm(void)
{
	int boss_health;
	int star;

	// case 1: stage bgm 初期化
	// case 2: stage bgm 通常動作
	// case 3: stage bgm フェードアウト
	// case 4: stage bgm 停止
	// case 5: stage bgm 再開
	// case 11: boss bgm 初期化
	// case 12: boss bgm 通常動作
	// case 13: boss bgm 停止
	DesignManager::GetStar(&star);
	switch (sound_phase_) {
	case 1:
		SoundManager::Play(soundfile_bgm_stage_, DX_PLAYTYPE_BACK);
		SetVolumeMusic(bgm_volume_);
		sound_phase_ = 2;
		break;
	case 2:
		if (6300 < frame_counter_)
			sound_phase_ = 3;
		if (star == -1)
			sound_phase_ = 4;
		break;
	case 3:
		bgm_volume_ -= 2;
		SoundManager::ChangeVolume(soundfile_bgm_stage_, bgm_volume_);
		if (bgm_volume_ < 3) {
			SoundManager::Stop(soundfile_bgm_stage_);
			sound_phase_ = 11;
		}
		break;
	case 4:
		SoundManager::Stop(soundfile_bgm_stage_);
		if (star != -1)
			sound_phase_ = 5;
		break;
	case 5:
		SoundManager::Play(soundfile_bgm_stage_, DX_PLAYTYPE_BACK, false);
		sound_phase_ = 2;
		break;
	case 11:
		SoundManager::Play(soundfile_bgm_boss_, DX_PLAYTYPE_BACK);
		SoundManager::ChangeVolume(soundfile_bgm_boss_, 170);
		sound_phase_ = 12;
		break;
	case 12:
		DesignManager::GetBossHealth(&boss_health);
		if (boss_health <= 0)
			sound_phase_ = 13;
		break;
	case 13:
		SoundManager::Stop(soundfile_bgm_boss_);
		break;
	}
}
