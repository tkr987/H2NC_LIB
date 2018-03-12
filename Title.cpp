#include "DefineNH.h"
#include "Title.h"
#include "FpsManager.h"
#include "ImgManager.h"
#include "KeyManager.h"

using namespace NH2;
typedef FpsManager FPS;
typedef KeyManager KEY;

struct TitleData {
	int imgdiv_icon_;
	int imgfile_menu_;
	int imgfile_enter_;
	int imgfile_icon_;
	ImgParam1 iparam1_;
};

void Title::Init(void)
{
	iparam1_help_ = new ImgParam1;
	iparam1_main_ = new ImgParam1;
	imgfile_help_ = ImgManager::LoadImg("data/17_img_title/Help.png");
	imgfile_main_[0] = ImgManager::LoadImg("data/17_img_title/Title1.png");
	imgfile_main_[1] = ImgManager::LoadImg("data/17_img_title/Title2.png");
	imgfile_main_[2] = ImgManager::LoadImg("data/17_img_title/Title3.png");
	imgfile_main_[3] = ImgManager::LoadImg("data/17_img_title/Title4.png");
	imgfile_main_[4] = ImgManager::LoadImg("data/17_img_title/Title5.png");
	imgfile_main_[5] = ImgManager::LoadImg("data/17_img_title/Title6.png");
	imgfile_main_[6] = ImgManager::LoadImg("data/17_img_title/Title7.png");
	select_ = 0;
	// Img Help 固定パラメータ
	iparam1_help_->flag_trans_ = true;
	iparam1_help_->group_type_ = eOBJECT::NUM::TITLE_HELP;
	iparam1_help_->x_ = 0;
	iparam1_help_->y_ = 0;
	// Img Main 固定パラメータ
	iparam1_main_->flag_trans_ = true;
	iparam1_main_->group_type_ = eOBJECT::NUM::TITLE_MAIN;
	iparam1_main_->x_ = 0;
	iparam1_main_->y_ = 0;

}

void Title::End(void)
{
	delete iparam1_help_;
	delete iparam1_main_;
}



void Title::Run(eGEVENT::TYPE *type)
{
	eGEVENT::TYPE return_type = *type;

	Draw();
	KeyUpdate(&return_type);

	*type = return_type;
}

void Title::Draw(void)
{
	if (!help_) {
		if (select_ == 0) {
			ImgManager::Draw(imgfile_main_[0], 0, iparam1_main_);
		} else if (select_ == 1) {
			ImgManager::Draw(imgfile_main_[1], 0, iparam1_main_);
		} else if (select_ == 2) {
			ImgManager::Draw(imgfile_main_[2], 0, iparam1_main_);
		} else if (select_ == 3) {
			ImgManager::Draw(imgfile_main_[3], 0, iparam1_main_);
		} else if (select_ == 4) {
			ImgManager::Draw(imgfile_main_[4], 0, iparam1_main_);
		} else if (select_ == 5) {
			ImgManager::Draw(imgfile_main_[5], 0, iparam1_main_);
		} else if (select_ == 6) {
			ImgManager::Draw(imgfile_main_[6], 0, iparam1_main_);
		}
	} else {
		ImgManager::Draw(imgfile_help_, 0, iparam1_help_);
	}
}

void Title::KeyUpdate(eGEVENT::TYPE *type)
{
	if (!help_) {

		// ***********************
		//  選択項目の決定処理
		// ***********************
		if (select_ == 0) {
			if (KeyManager::IsPressKey(eKEY::TYPE::ENTER) || KeyManager::IsPressKey(eKEY::ARMS)) {
				*type = eGEVENT::STAGE1_HARD_LOAD;
				return;
			}
		} else if (select_ == 5) {
			if (KeyManager::IsPressKey(eKEY::TYPE::ENTER) || KeyManager::IsPressKey(eKEY::ARMS)) {
				help_ = true;
				return;
			}
		}

		// *************
		//  選択処理
		// *************
		if (KeyManager::IsPressKey(eKEY::DOWN)) {
			select_++;
			if (select_ == 7)
				select_ = 0;
		} else if (KeyManager::IsPressKey(eKEY::UP)) {
			select_--;
			if (select_ == -1)
				select_ = 6;
		}

	} else {

		if (KeyManager::IsPressKey(eKEY::TYPE::ENTER) || KeyManager::IsPressKey(eKEY::ARMS)) {
			help_ = false;
			return;
		}

	}
}
//
///*!
//@brief タイトル画面処理関数
//@param timg 画像管理クラス
//@param title_inst 命令番号
//@return なし
//@note
// title_inst = 0: 何もしない
// title_inst = 1: 画像ロード
// title_inst = 2: 画像描画
// title_inst = 3: 画像破棄
//*/
//int Title(int title_inst)
//{
//	static TitleData tdata;
//	static int tselect = 1;
//	static int icon_posy = 125;
//
//	///////////////
//	// 画像ロード
//	///////////////
//	if (title_inst == INST_LOAD) {
//		tdata.imgdiv_icon_ = 0;
//		tdata.imgfile_menu_ = ImgManager::LoadImg("data/img_design/menu2.png");
//		tdata.imgfile_enter_ = ImgManager::LoadImg("data/img_design/enter.png");
//		tdata.imgfile_icon_ = ImgManager::LoadImg(12, 1, 32, 32, "data/img_design/icon.png");
//		// 描画固定パラメータ
//		tdata.iparam1_.group_type_ = eOBJECT::NUM::TITLE;
//	}
//
//
//	///////////////
//	// 画像描画
//	///////////////
//	if (title_inst != INST_RUN)
//		return 0;
//	
//	if (FPS::GetInterval(5) == 0)
//		tdata.imgdiv_icon_ = ++tdata.imgdiv_icon_ % 12;
//
//	if (KEY::IsPressKey(eKEY::DOWN)) {
//		tselect++;
//		if (tselect == 6)
//			tselect = 1;
//	} else if (KEY::IsPressKey(eKEY::UP)) {
//		tselect--;
//		if (tselect == -1)
//			tselect = 5;
//	}
//
//
//	switch (tselect) {
//	case 1:
//		if (!KEY::GetKeyFlagPre(eKEY::ENTER) && KEY::GetKeyFlagNow(eKEY::ENTER)) {
//			return 1;
//		} else if (!KEY::GetKeyFlagPre(eKEY::ARMS) && KEY::GetKeyFlagNow(eKEY::ARMS)) {
//			return 1;
//		}
//		icon_posy = 125;
//		break;
//	case 2:
//		if (!KEY::GetKeyFlagPre(eKEY::ENTER) && KEY::GetKeyFlagNow(eKEY::ENTER)) {
//			return 2;
//		} else if (!KEY::GetKeyFlagPre(eKEY::ARMS) && KEY::GetKeyFlagNow(eKEY::ARMS)) {
//			return 2;
//		}
//		icon_posy = 179;
//		break;
//	case 3:
//		if (!KEY::GetKeyFlagPre(eKEY::ENTER) && KEY::GetKeyFlagNow(eKEY::ENTER)) {
//			return 3;
//		} else if (!KEY::GetKeyFlagPre(eKEY::ARMS) && KEY::GetKeyFlagNow(eKEY::ARMS)) {
//			return 3;
//		}
//		icon_posy = 233;
//		break;
//	case 4:
//		if (!KEY::GetKeyFlagPre(eKEY::ENTER) && KEY::GetKeyFlagNow(eKEY::ENTER)) {
//			return 4;
//		} else if (!KEY::GetKeyFlagPre(eKEY::ARMS) && KEY::GetKeyFlagNow(eKEY::ARMS)) {
//			return 4;
//		}
//		icon_posy = 287;
//		break;
//	case 5:
//		if (!KEY::GetKeyFlagPre(eKEY::ENTER) && KEY::GetKeyFlagNow(eKEY::ENTER)) {
//			return 5;
//		} else if (!KEY::GetKeyFlagPre(eKEY::ARMS) && KEY::GetKeyFlagNow(eKEY::ARMS)) {
//			return 5;
//		}
//		icon_posy = 395;
//		break;
//	}
//
//	tdata.iparam1_.flag_trans_ = false;
//	tdata.iparam1_.x_ = 160;
//	tdata.iparam1_.y_ = 32;
//	ImgManager::Draw(tdata.imgfile_menu_, 0, &tdata.iparam1_);
//	tdata.iparam1_.flag_trans_ = true;
//	tdata.iparam1_.x_ = 190;
//	tdata.iparam1_.y_ = icon_posy;
//	ImgManager::Draw(tdata.imgfile_icon_, tdata.imgdiv_icon_, &tdata.iparam1_);
//
//	return 0;
//}
