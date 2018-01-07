#pragma once

namespace NH2 {
	struct ImgParam1;
}

class Result {
public:
	int Run(int stage);
	void Clear(void);
	void End(void);
	void Init(void);
	void Load(int stage);
	Result(void) {}
	~Result(void) {}
private:
	int frames_;
	long value_stage_score_[3];
	int imgfile_clear_stage_;
	int imgfile_score_number_;
	int imgfile_score_pt_;
	int imgfile_stage_;
	int soundfile_score_;
	NH2::ImgParam1 *iparam1_clear_stage_;
	NH2::ImgParam1 *iparam1_stage_;
	NH2::ImgParam1 *iparam1_score_number_;
	void DrawScore(int x, int y, long score);
};