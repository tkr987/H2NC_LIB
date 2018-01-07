#pragma once
#include "DefineNH.h"
#include <string>


namespace NH2 {
	struct ImgParam1b;
	class PosParam1;
}


class Map {
public:
	Map(void) {}
	~Map(void) {}
	void DataClear(void);
	void DataLoad(int stage);
	void MemoryEnd(void);
	void MemoryInit(void);
	void Ran(void);
private:
	int sound_phase_;
	int bgm_volume_;
	int frame_counter_;
	int imgfile_gameover_;
	int imgfile_map_;
	int imgfile_warning_;
	int soundfile_bgm_stage_;
	int soundfile_bgm_boss_;
	std::string filepass_img_map_;
	std::string filepass_img_gameover_;
	std::string filepass_img_warning_;
	std::string filepass_sound_bgm_boss_;
	std::string filepass_sound_bgm_stage_;
	NH2::ImgParam1b* iparam_map_;
	NH2::PosParam1* pparam_map_;
	void DrawMap(void);
	void MoveMap(void);
	void PlaySeBgm(void);
};
