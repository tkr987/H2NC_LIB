#include "DxLib.h"
#include "DesignManager.h"
#include "ImgManager.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "Result.h"

using namespace NH2;

void Result::Init(void)
{
	iparam1_clear_stage_ = new ImgParam1;
	iparam1_stage_ = new ImgParam1;
	iparam1_score_number_ = new ImgParam1;
	imgfile_clear_stage_ = IMG_LOAD_RESULT_CLEAR_STAGE;
	imgfile_score_number_ = IMG_LOAD_RESULT_SCORE_NUMBER;
	imgfile_score_pt_ = IMG_LOAD_RESULT_SCORE_PT;
	imgfile_stage_ = IMG_LOAD_RESULT_STAGE;
	soundfile_score_ = SoundManager::Load("data/sound/ResultScore.wav");
	// IMG CLEAR STAGE 固定パラメータ
	iparam1_clear_stage_->flag_trans_ = true;
	iparam1_clear_stage_->group_type_ = eOBJECT::NUM::STAGE_RESULT;
	iparam1_clear_stage_->x_ = 192;
	iparam1_clear_stage_->y_ = 320;
	// IMG STAGE 固定パラメータ
	iparam1_stage_->flag_trans_ = true;
	iparam1_stage_->group_type_ = eOBJECT::NUM::STAGE_RESULT;
	iparam1_stage_->x_ = 0;
	iparam1_stage_->y_ = 0;
	// IMG SCORE NUMBER 固定パラメータ
	iparam1_score_number_->flag_trans_ = true;
	iparam1_score_number_->group_type_ = eOBJECT::NUM::STAGE_RESULT;
	Clear();
}

void Result::Clear(void)
{
	for (int i = 0; i < 3; i++)
		value_stage_score_[i] = 0;
}

void Result::End(void)
{
	delete iparam1_stage_;
	delete iparam1_score_number_;
}

void Result::Load(int stage)
{
	frames_ = 0;
	if (stage == 1) {
		value_stage_score_[0] = DesignManager::GetScore();
		value_stage_score_[1] = 0;
		value_stage_score_[2] = 0;
	} else if (stage == 2) {
		value_stage_score_[1] = DesignManager::GetScore();
		value_stage_score_[1] -= value_stage_score_[0];
		value_stage_score_[2] = 0;
	} else if (stage == 3) {
		value_stage_score_[0] = 10;
		value_stage_score_[1] = 20;
//		value_stage_score_[2] = DesignManager::GetScore();
		value_stage_score_[2] = 55421;
		value_stage_score_[2] -= value_stage_score_[1];
		value_stage_score_[2] -= value_stage_score_[0];
	}
}

int Result::Run(int stage)
{
	if (frames_ != 401)
		frames_++;



	// *****************
	//  result 描画
	// *****************
	ImgManager::Draw(imgfile_stage_, 0, iparam1_stage_);

	// *****************
	//  score 描画
	// *****************
	if (100 < frames_)
		DrawScore(320, 128, value_stage_score_[0]);	
	if (200 < frames_)
		DrawScore(320, 192, value_stage_score_[1]);
	if (300 < frames_)
		DrawScore(320, 256, value_stage_score_[2]);

	// **********************
	//  clear 描画
	// **********************
	if (400 < frames_) {
		if (stage == 1) {
			ImgManager::Draw(imgfile_clear_stage_, 0, iparam1_clear_stage_);
		} else if (stage == 2) {
			ImgManager::Draw(imgfile_clear_stage_, 1, iparam1_clear_stage_);
		} else if (stage == 3) {
			ImgManager::Draw(imgfile_clear_stage_, 2, iparam1_clear_stage_);
		}
	}


	// *****************
	//  サウンド処理
	// *****************
	if (frames_ == 100) {
		SoundManager::Play(soundfile_score_, DX_PLAYTYPE_BACK);
	} else if (frames_ == 200) {
		SoundManager::Play(soundfile_score_, DX_PLAYTYPE_BACK);
	} else if (frames_ == 300) {
		SoundManager::Play(soundfile_score_, DX_PLAYTYPE_BACK);
	} else if (frames_ == 400) {
		SoundManager::Play(soundfile_score_, DX_PLAYTYPE_BACK);
	}

	//if (300 <= frames_) {
	//	if (KeyManager::IsPressKey(eKEY::TYPE::ARMS) || KeyManager::IsPressKey(eKEY::TYPE::ENTER))
	//		return RETURN_RESULT_RUN_END;
	//}

	return RETURN_RESULT_RUN_OK;
}

void Result::DrawScore(int x, int y, long score)
{
	int imgdiv_score_number;
	int draw_posx = x;
	int draw_posy = y;
	int keta = (int)log10(score) + 1;

	if (score == 0) {
		for (int i = 0; i < 8; i++) {
			iparam1_score_number_->x_ = draw_posx;
			iparam1_score_number_->y_ = draw_posy;
			ImgManager::Draw(imgfile_score_number_, 0, iparam1_score_number_);
			draw_posx += 16;
		}
		return;
	}
	for (int i = 8; i != keta; i--) {
			iparam1_score_number_->x_ = draw_posx;
			iparam1_score_number_->y_ = draw_posy;
			ImgManager::Draw(imgfile_score_number_, 0, iparam1_score_number_);
			draw_posx += 16;
	}
	while(1 < keta) {
		imgdiv_score_number = (int)(score / (long)pow(10.0, keta - 1));
		iparam1_score_number_->x_ = draw_posx;
		iparam1_score_number_->y_ = draw_posy;
		ImgManager::Draw(imgfile_score_number_, imgdiv_score_number, iparam1_score_number_);
		score -= imgdiv_score_number * (long)pow(10.0, keta - 1);
		draw_posx += 16;
		keta--;
	}
	iparam1_score_number_->x_ = draw_posx;
	iparam1_score_number_->y_ = draw_posy;
	ImgManager::Draw(imgfile_score_number_, score, iparam1_score_number_);
	// pt 描画
	draw_posx += 16;
	iparam1_score_number_->x_ = draw_posx;
	iparam1_score_number_->y_ = draw_posy;
	ImgManager::Draw(imgfile_score_pt_, 0, iparam1_score_number_);

//	int imgdiv;
//	int imgx, imgy;
//	long score = value_score_;
//	int keta = (int)log10(score) + 1;
//	static ImgParam1 iparam1;
//
//#ifdef __DEBUG__
//	int color = GetColor(255, 255, 255);
//	DebugPrint::SetData(300, 400, "keta: %d", keta);
//	DebugPrint::SetData(300, 380, "score: %ld", score_);
//#endif
//
//	iparam1.flag_trans_ = true;
//	imgx = 616;
//	imgy = 56;
//	if (score == 0) {
//		for (int i = 0; i < 8; i++) {
//			iparam1_score_->x_ = imgx;
//			iparam1_score_->y_ = imgy;
//			ImgManager::Draw(imgfile_score_, 0, iparam1_score_);
//			imgx += 22;
//		}
//		return;
//	}
//	for (int i = 8; i != keta; i--) {
//			iparam1_score_->x_ = imgx;
//			iparam1_score_->y_ = imgy;
//			ImgManager::Draw(imgfile_score_, 0, iparam1_score_);
//			imgx += 22;
//	}
//	while(1 < keta) {
//		imgdiv = (int)(score / (long)pow(10.0, keta - 1));
//		iparam1_score_->x_ = imgx;
//		iparam1_score_->y_ = imgy;
//		ImgManager::Draw(imgfile_score_, imgdiv, iparam1_score_);
//		score -= imgdiv * (long)pow(10.0, keta - 1);
//		imgx += 22;
//		keta--;
//	}
//	iparam1_score_->x_ = imgx;
//	iparam1_score_->y_ = imgy;
//	ImgManager::Draw(imgfile_score_, score, iparam1_score_);
}