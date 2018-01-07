#include "Boss1MRAB.h"
#include "DxLib.h"
#include "DesignManager.h"
#include "ImgManager.h"
#include "KeyManager.h"
#include "PosManager.h"
#include "SoundManager.h"
#include "Stage1.h"
#include "StageTarget.h"
#include "Target1Anello.h"
#include "Target1Denso.h"
#include "Target1Erythro.h"
#include "Target1Picorna.h"
#include "Target1Sipho.h"
#include "Target1Virga.h"

using namespace std;
using namespace NH2;
using namespace NH2T;

Stage1::Stage1()
{
	iparam1_continue_ = new ImgParam1;
	iparam1b_map_ = new ImgParam1b;
	pparam1_map_ = new PosParam1;
	// continue 固定imgパラメータ
	iparam1_continue_->flag_trans_ = false;
	iparam1_continue_->group_type_ = eOBJECT::GROUP::STAGE_CONTINUE;
	iparam1_continue_->x_ = 0;
	iparam1_continue_->y_ = 100;
	// map 固定imgパラメータ
	iparam1b_map_->blend_alpha_ = 255;
	iparam1b_map_->blend_mode_ = DX_BLENDMODE_ADD;
	iparam1b_map_->flag_trans_ = false;
	iparam1b_map_->group_type_ = eOBJECT::GROUP::MAP_BOTTOM;
	// map 固定posパラメータ
	pparam1_map_->SetStartX(-21);
	pparam1_map_->SetStartY(-3200);
	PosManager::Generate(eOBJECT::GROUP::MAP_BOTTOM, pparam1_map_);
}


Stage1::~Stage1()
{

}

/**
@brief フェーズ１０ターゲット処理
@note
 通常処理、行動処理と描画処理をおこなう。
**/
void Stage1::Phase10_Target(void)
{
	// target 処理
	for (multimap<long, TargetBase*>::iterator it = map_target_.begin(); it != map_target_.end(); ++it) {
		if (it->first < frame_) {
			it->second->Action();
			it->second->Draw();
		}
	}
}

/**
@brief フェーズ１１ターゲット処理
@note
 コンテニュー表示画面なので、描画処理のみおこなう。
**/
void Stage1::Phase11_Target(void)
{
	for (multimap<long, TargetBase*>::iterator it = map_target_.begin(); it != map_target_.end(); ++it) {
		if (it->first < frame_)
			it->second->Draw();
	}
}

/**
@brief フェーズ１１コンテニュー処理
@param *gevent 決定キーを押した時の戻り値を格納する
**/
void Stage1::Phase11_Continue(eGEVENT::TYPE* gevent)
{
	bool gevent_update = false;

	//*********************************
	// case 0 ... コンテニューyes
	// case 1 ... コンテニューno
	//*********************************
	switch (continue_select_) {
	case 0:
		ImgManager::Draw(imgfile_continue_yes_, 0, iparam1_continue_);
		if (KeyManager::IsPressKey(eKEY::TYPE::ARMS) || KeyManager::IsPressKey(eKEY::TYPE::ENTER))
			DesignManager::SetStar(2);
		break;
	case 1:
		ImgManager::Draw(imgfile_continue_no_, 0, iparam1_continue_);
		if (KeyManager::IsPressKey(eKEY::TYPE::ARMS) || KeyManager::IsPressKey(eKEY::TYPE::ENTER))
			*gevent = eGEVENT::STAGE_GAME_OVER;
		break;
	default:
		break;
	}

	// 選択処理
	if (KeyManager::IsPressKey(eKEY::TYPE::RIGHT) || KeyManager::IsPressKey(eKEY::TYPE::LEFT))
		continue_select_ = ++continue_select_ % 2;

	// イベント更新
	//if (gevent_update) {
	//	if (*gevent == eGEVENT::TYPE::STAGE1_HARD_RUN) {
	//		*gevent = eGEVENT::TYPE::STAGE1_GAME_OVER;
	//	} else if (*gevent == eGEVENT::TYPE::STAGE2_HARD_RUN) {
	//		*gevent = eGEVENT::TYPE::STAGE2_GAME_OVER;
	//	} else if (*gevent == eGEVENT::TYPE::STAGE3_HARD_RUN){
	//		*gevent = eGEVENT::TYPE::STAGE3_GAME_OVER;
	//	}
	//}
}


void Stage1::Load(int lv, int rand, long frame)
{
	long create_frames = 0;
	int map_center_x, map_center_y;
	int map_min_x, map_max_x;
	int map_min_y, map_max_y;

	PosManager::GetRelativeMapCenterX(&map_center_x);
	PosManager::GetRelativeMapCenterX(&map_center_y);
	PosManager::GetRelativeMapMinX(&map_min_x);
	PosManager::GetRelativeMapMaxX(&map_max_x);
	PosManager::GetRelativeMapMinY(&map_min_y);
	PosManager::GetRelativeMapMaxY(&map_max_y);

	srand(rand);
	frame_ = frame;
	phase_ = 10;


	//*************
	// load bgm
	//*************
	soundfile_bgm_boss_ = SoundManager::Load("data/sound/bgm_boss_Aqui-Priestess.mp3");
	soundfile_bgm_stage_ = SoundManager::Load("data/sound/bgm_st01_Anbrosia.mp3");

	//*************
	// load map
	//*************
	imgfile_map_ = ImgManager::LoadImg("data/img_map/map1.png");

	//******************
	// target load
	//******************

	// *********
	//  wave 1
	// *********
	create_frames = 50;
	for (int i = 0; i < 5; i++)
		map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -50, lv)));
	for (int i = 0; i < 5; i++)
		map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -110, lv)));
	for (int i = 0; i < 5; i++)
		map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -170, lv)));
	for (int i = 0; i < 5; i++)
		map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -230, lv)));

	//create_frames = 300;
	//for (int n = 0; n < 10; n++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + n * 30 + rand() % 5, new Target1Denso(map_min_x + 50 + rand() % 250, 50 + rand() % 100, lv)));

	//create_frames = 550;
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -110, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -170, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -230, lv)));

	//create_frames = 800;
	//for (int n = 0; n < 10; n++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + n * 30 + rand() % 5, new Target1Denso(map_max_x - 50 - rand() % 250, 50 + rand() % 100, lv)));

	//create_frames = 1150;
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -150, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -250, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -150, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -250, lv)));

	//create_frames = 1300;
	//for (int n = 0; n < 10; n++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + n * 20 + rand() % 5, new Target1Denso(map_center_x - rand() % 250, 50 + rand() % 100, lv)));
	//for (int n = 0; n < 10; n++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + n * 20 + rand() % 5, new Target1Denso(map_center_x + rand() % 250, 50 + rand() % 100, lv)));

	//// *********
	////  wave 2
	//// *********
	//create_frames = 1900;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Anello(400, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(350, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(450, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(300, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(500, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(250, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(550, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(200, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(600, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(150, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(650, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Anello(400, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(350, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(450, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(300, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(500, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(250, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(550, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(200, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(600, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(150, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(650, -140, lv)));
	//create_frames = 2350;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Sipho(400, 50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Sipho(300, 50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Sipho(500, 50, lv)));
	//create_frames = 2600;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Anello(400, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(350, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(450, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(300, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(500, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(250, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(550, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(200, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(600, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(150, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(650, -100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Anello(400, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(350, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Anello(450, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(300, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 200, new Target1Anello(500, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(250, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 300, new Target1Anello(550, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(200, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 400, new Target1Anello(600, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(150, -140, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 500, new Target1Anello(650, -140, lv)));

	//// *********
	////  wave 3
	//// *********
	//create_frames = 3000;
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -110, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_min_x + 50 + i * 50, -170, lv)));
	//create_frames = 3200;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Erythro(map_max_x - 200, 80, lv)));

	//create_frames = 3400;
	//for (int n = 0; n < 10; n++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + n * 30 + rand() % 5, new Target1Denso(map_min_x + 50 + rand() % 250, 50 + rand() % 100, lv)));	
	//create_frames = 3600;
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -50, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -110, lv)));
	//for (int i = 0; i < 5; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Virga(map_max_x - 50 - i * 50, -170, lv)));
	//create_frames = 3800;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Erythro(map_min_x + 200, 130, lv)));

	//create_frames = 4300;
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_min_x + 250, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_min_x + 250, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_min_x + 250,  50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_max_x - 250, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_max_x - 250, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_max_x - 250,  50, lv)));
	//create_frames = 4350;
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_min_x + 200, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_min_x + 200, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_min_x + 200,  50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_max_x - 200, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_max_x - 200, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_max_x - 200,  50, lv)));
	//create_frames = 4400;
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_min_x + 150, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_min_x + 150, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_min_x + 150,  50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_max_x - 150, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_max_x - 150, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_max_x - 150,  50, lv)));
	//create_frames = 4450;
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_min_x + 100, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_min_x + 100, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_min_x + 100,  50, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames,       new Target1Denso(map_max_x - 100, 150, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 50,  new Target1Denso(map_max_x - 100, 100, lv)));
	//map_target_.insert(pair<int, TargetBase*>(create_frames + 100, new Target1Denso(map_max_x - 100,  50, lv)));
	//create_frames = 4800;
	//map_target_.insert(pair<int, TargetBase*>(create_frames, new Target1Erythro(map_center_x, 180, lv)));

	//// *********
	////  wave 4
	//// *********
	//create_frames = 5600;
	//for (int i = 0; i < 40; i++)
	//	map_target_.insert(pair<int, TargetBase*>(create_frames + 10 * i, new Target1Picorna(100 + rand() % 600, -100 + rand() % 50, lv)));

	// ********
	//  boss
	// ********
	create_frames = 6450;
	map_target_.insert(pair<long, TargetBase*>(create_frames, new Boss1MRAB(map_center_x, -100, lv)));
}

void Stage1::Run(void)
{
	double move_speed = 0.5;
	int user_star;

	// 未完成

	// ************************************************************************
	//  case 10: 通常(mapとシンクロさせるために0.5だけ移動させる処理も入る)
	//  case 11: コンテニュー表示
	//  case 12: ボス戦終了
	//  case 13: リザルト画面へ移行
	// ************************************************************************
	//switch (phase_) {
	//case 10:
	//	Phase10_Target();
	//	PosManager::MovePosC(eOBJECT::GROUP::TARGET_RUN_WALK, NULL, &move_speed);
	//	DesignManager::GetStar(&user_star);
	//	if (user_star == -1)
	//		phase_ = 11;
	//	break;
	//case 11:
	//	// target 処理
	//	Phase11_Target();
	//	// continue 処理
	//	Phase11_Continue(gevent);
	//	DesignManager::GetStar(&user_star);
	//	if (user_star != -1)
	//		phase_target_ = 10;
	//	break;
	//}
}


void Stage1::RunMap(void)
{
	double move_speed = 0.5;

	// 未完成

	// *************************************
	//  case 10: 道中
	//  case 11: ボス戦前フェードアウト
	//  case 12: ボス戦
	// *************************************
	//switch (phase_map_) {
	//case 10:
	//	PosManager::GetPosX(pparam1_map_, &iparam1b_map_->pos_x_);
	//	PosManager::GetPosY(pparam1_map_, &iparam1b_map_->pos_y_);
	//	ImgManager::Draw(imgfile_map_, 0, iparam1b_map_);
	//	PosManager::MovePosA(pparam1_map_, NULL, &move_speed);
	//	if (frame_ == 6300)
	//		phase_target_ = 11;
	//	break;
	//case 11:
	//	if (0 < iparam1b_map_->blend_alpha_ - 5) {
	//		iparam1b_map_->blend_alpha_ -= 5;
	//	} else {
	//		iparam1b_map_->blend_alpha_ = 0;
	//	}
	//	PosManager::GetPosX(pparam1_map_, &iparam1b_map_->pos_x_);
	//	PosManager::GetPosY(pparam1_map_, &iparam1b_map_->pos_y_);
	//	ImgManager::Draw(imgfile_map_, 0, iparam1b_map_);
	//	PosManager::MovePosA(pparam1_map_, NULL, &move_speed);
	//	if (iparam1b_map_->blend_alpha_ == 0)
	//		phase_map_ = 12;
	//	break;
	//case 12:
	//	break;
	//}
}