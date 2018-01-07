#pragma once
#include <string>
#include "DefineNH.h"


class StageSound {
public:
	StageSound(void) {}
	~StageSound(void) {}
	void DataClear(void);
	void DataLoad(eGEVENT::TYPE type);
	void MemoryEnd(void);
	void MemoryInit(void);
	void Run(void);
private:
	// sound file
	int soundfile_bgm_stage_;
	int soundfile_bgm_boss_;
	// ÇªÇÃëº ïœêî
	int frames_;
	int phase_;
	int volume_;
	std::string filepass_sound_bgm_boss_;
	std::string filepass_sound_bgm_stage_;
};
