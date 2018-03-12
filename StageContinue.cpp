#include "StageContinue.h"
#include "DesignManager.h"
#include "ImgManager.h"
#include "KeyManager.h"

using namespace NH2;

StageContinue::StageContinue()
{
	imgfile_no_ = ImgManager::LoadImg("data/11_img_continue/No.png");
	imgfile_yes_ = ImgManager::LoadImg("data/11_img_continue/Yes.png");
	iparam1_ = new ImgParam1;
}

StageContinue::~StageContinue()
{
	delete iparam1_;
}

void StageContinue::DataLoad(void)
{
	select_ = 0;
	// Image 固定パラメータ
	iparam1_->flag_trans_ = false;
	iparam1_->group_type_ = eOBJECT::NUM::STAGE_CONTINUE;
	iparam1_->x_ = 0;
	iparam1_->y_ = 100;
}


void StageContinue::Run(eGEVENT::TYPE *type)
{
	int star;
	bool gevent_update = false;

	DesignManager::GetStar(&star);
	if (star != -1)
		return;

	// 描画処理
	if(select_ == 0) {
		ImgManager::Draw(imgfile_yes_, 0, iparam1_);
	} else {
		ImgManager::Draw(imgfile_no_, 0, iparam1_);
	}

	// 選択処理
	if (KeyManager::IsPressKey(eKEY::TYPE::RIGHT) || KeyManager::IsPressKey(eKEY::TYPE::LEFT))
		select_ = ++select_ % 2;

	// 選択決定
	if (select_ == 0) {
		if (KeyManager::IsPressKey(eKEY::TYPE::ARMS) || KeyManager::IsPressKey(eKEY::TYPE::ENTER))
			DesignManager::SetStar(2);
	} else {
		if (KeyManager::IsPressKey(eKEY::TYPE::ARMS) || KeyManager::IsPressKey(eKEY::TYPE::ENTER)) {
			gevent_update = true;
		}
	}

	// イベント更新
	if (gevent_update) {
		if (*type == eGEVENT::TYPE::STAGE1_HARD_RUN) {
			*type = eGEVENT::TYPE::STAGE1_GAME_OVER;
		} else if (*type == eGEVENT::TYPE::STAGE2_HARD_RUN) {
			*type = eGEVENT::TYPE::STAGE2_GAME_OVER;
		} else if (*type == eGEVENT::TYPE::STAGE3_HARD_RUN){
			*type = eGEVENT::TYPE::STAGE3_GAME_OVER;
		}
	}

}
