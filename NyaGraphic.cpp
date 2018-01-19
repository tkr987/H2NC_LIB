#include "DxLib.h"
#include "NyaDefine.h"
#include "NyaGraphic.h"
#include "NyaString.h"
#include <tuple>


using namespace std;
using namespace H2NLIB;

std::vector<GraphicFileSet> NyaGraphic::file_vector_;
std::vector<DrawDequeSet> NyaGraphic::layer_vector_(eOBJECT::GROUP::sizeof_enum);


NyaGraphic::NyaGraphic()
{
	static bool first_call = true;

	if (first_call) {
		swing_x_ = 0;
		swing_y_ = 0;
		nya_string_ = new NyaString;
		nya_string_->SettingFont("image", 15, 2);
		first_call = false;
	}

}


NyaGraphic::~NyaGraphic()
{

}

/**
画像ロード関数
@param filepass ファイルパス
@return 画像ファイルの識別ID
**/
int NyaGraphic::LoadFile(std::string file_pass)
{
	GraphicFileSet file_set;
	int graphic_id;
	int graphic_xsize, graphic_ysize;

	file_set.div_max_ = 0;
	graphic_id = LoadGraph(file_pass.c_str());
	file_set.div_vector_.push_back(graphic_id);
	file_set.div_x_ = 0;
	file_set.div_y_ = 0;
	GetGraphSize(graphic_id, &graphic_xsize, &graphic_ysize);
	file_set.size_x_ = graphic_xsize;
	file_set.size_y_ = graphic_ysize;

	file_vector_.push_back(file_set);
	return (int)(file_vector_.size() - 1);
}

/**
分割画像ロード関数
@param xnum x軸方向分割数
@param ynum y軸方向分割数
@param xsize x軸方向分割サイズ
@param ysize y軸方向分割サイズ
@param filename ファイル名
@return 画像ファイルの識別ID (ロード失敗のとき-1)
@note 
 xnum と ynum には自然数を入力する。
 xnum * ynum が512以上になる値はロードできない。
**/
int NyaGraphic::LoadFile(int xnum, int ynum, int xsize, int ysize, std::string file_pass)
{
	GraphicFileSet file_set;
	static int file_id[512] = {};

	if (512 <= xnum * ynum)
		return -1;
	if (xnum <= 0 || ynum <= 0)
		return -1;

	file_set.div_max_ = xnum * ynum - 1;
	LoadDivGraph(file_pass.c_str(), xnum * ynum, xnum, ynum, xsize, ysize, file_id);
	for (int i = 0; i< xnum * ynum; i++)
		file_set.div_vector_.push_back(file_id[i]);
	file_set.div_x_ = xnum - 1;
	file_set.div_y_ = ynum - 1;
	file_set.size_x_ = xsize;
	file_set.size_y_ = ysize;
	
	file_vector_.push_back(file_set);
	return (int)(file_vector_.size() - 1);
}


/**
画像描画関数1
@param *gpx プロパティ
@return なし
@note
DXLIB DrawGraph() に対応。
**/
void NyaGraphic::Draw(GraphicPropertyX1 *gpx)
{
	layer_vector_[gpx->object_group_].gpx1_deque_.push_back(*gpx);
}


/**
画像描画関数2
@param *gpx プロパティ
@return なし
@note
 DXLIB DrawTurnGraph() に対応。
 **/
void NyaGraphic::Draw(GraphicPropertyX2 *gpx)
{
	layer_vector_[gpx->object_group_].gpx2_deque_.push_back(*gpx);
}


/**
画像描画関数3
@param *gpx プロパティ
@return なし
@note
DXLIB DrawExtendGraph() に対応。
**/
void NyaGraphic::Draw(GraphicPropertyX3 *gpx)
{
	layer_vector_[gpx->object_group_].gpx3_deque_.push_back(*gpx);
}

/**
画像描画関数4
@param *gpx プロパティ
@return なし
@note
DXLIB DrawRotaGraph() に対応。
**/
void NyaGraphic::Draw(GraphicPropertyX4 *gpx)
{
	layer_vector_[gpx->object_group_].gpx4_deque_.push_back(*gpx);
}


void NyaGraphic::Run(void)
{

	DrawAll(eOBJECT::GROUP::USER1, true);
	DrawAll(eOBJECT::GROUP::USER_ATTACK1, true);
}


/**
@brief 全てのグラフィックデータを描画する関数
@param layer 描画するレイヤー
@param swing 振動幅
**/
void NyaGraphic::DrawAll(int layer, bool swing)
{
	DrawDequeSet draw_deque_set;
	GraphicPropertyX1* gpx1;
	GraphicPropertyX2* gpx2;
	GraphicPropertyX3* gpx3;
	GraphicPropertyX4* gpx4;
	GraphicPropertyX5* gpx5;
	GraphicPropertyX6* gpx6;
	GraphicPropertyX7* gpx7;
	GraphicPropertyX8* gpx8;
	GraphicPropertyX1b* gpx1b;
	GraphicPropertyX2b* gpx2b;
	GraphicPropertyX3b* gpx3b;
	GraphicPropertyX4b* gpx4b;
	GraphicPropertyX5b* gpx5b;
	int swing_x = 0;
	int swing_y = 0;
	int count = 0;


	if (swing) {
		swing_x = swing_x_;
		swing_y = swing_y_;
	}

	
	draw_deque_set = layer_vector_.at(layer);
	while (!draw_deque_set.gpx1_deque_.empty()) {
		gpx1 = &draw_deque_set.gpx1_deque_.front();
		DrawGraph(gpx1->pos_x_ + swing_x, gpx1->pos_y_ + swing_y, 
			file_vector_[gpx1->file_id_].div_vector_[gpx1->file_div_], gpx1->flag_trans_);
		draw_deque_set.gpx1_deque_.pop_front();
	}
	while (!draw_deque_set.gpx2_deque_.empty()) {
		gpx2 = &draw_deque_set.gpx2_deque_.front();
		DrawTurnGraph(gpx2->pos_x_ + swing_x, gpx2->pos_y_ + swing_y,
			file_vector_[gpx2->file_id_].div_vector_[gpx2->file_div_], gpx2->flag_trans_);
		draw_deque_set.gpx2_deque_.pop_front();
	}
	while (!draw_deque_set.gpx3_deque_.empty()) {
		gpx3 = &draw_deque_set.gpx3_deque_.front();
		DrawExtendGraph(gpx3->pos_x1_ + swing_x, gpx3->pos_y1_+ swing_y,
			gpx3->pos_x2_ + swing_x, gpx3->pos_y2_ + swing_y, 
			file_vector_[gpx3->file_id_].div_vector_[gpx3->file_div_], gpx3->flag_trans_);
		draw_deque_set.gpx3_deque_.pop_front();
	}
	while (!draw_deque_set.gpx4_deque_.empty()) {
		gpx4 = &draw_deque_set.gpx4_deque_.front();
		DrawRotaGraph(gpx4->pos_cx_ + swing_x, gpx4->pos_cy_ + swing_y, gpx4->extend_rate_, gpx4->draw_angle_,
			file_vector_[gpx4->file_id_].div_vector_[gpx4->file_div_], gpx4->flag_trans_, gpx4->flag_turn_);
		draw_deque_set.gpx4_deque_.pop_front();
		count++;
	}


	tuple<int, int, int> color = make_tuple(255, 255, 255);
	nya_string_->Write("image=", color, 50, 50, "%d", count);


	while (!draw_deque_set.gpx5_deque_.empty()) {
		gpx5 = &draw_deque_set.gpx5_deque_.front();
		DrawRotaGraph2(gpx5->pos_x_ + swing_x, gpx5->pos_y_ + swing_y, 
			gpx5->pos_cx_ + swing_x, gpx5->pos_cy_ + swing_y, gpx5->extend_rate_, gpx5->draw_angle_, 
			file_vector_[gpx5->file_id_].div_vector_[gpx5->file_div_], gpx5->flag_trans_, gpx5->flag_turn_);
		draw_deque_set.gpx5_deque_.pop_front();
	}
	while (!draw_deque_set.gpx6_deque_.empty()) {
		gpx6 = &draw_deque_set.gpx6_deque_.front();
		DrawRotaGraph3(gpx6->pos_x_ + swing_x, gpx6->pos_y_ + swing_y, 
			gpx6->pos_cx_ + swing_x, gpx6->pos_cy_ + swing_y, gpx6->extend_ratex_, gpx6->extend_ratey_, gpx6->draw_angle_,
			file_vector_[gpx6->file_id_].div_vector_[gpx6->file_div_], gpx6->flag_trans_, gpx6->flag_turn_);
		draw_deque_set.gpx6_deque_.pop_front();
	}
	while (!draw_deque_set.gpx7_deque_.empty()) {
		gpx7 = &draw_deque_set.gpx7_deque_.front();
		DrawModiGraph(
			gpx7->pos_x1_ + swing_x, gpx7->pos_y1_ + swing_y, gpx7->pos_x2_ + swing_x, gpx7->pos_y2_ + swing_y, 
			gpx7->pos_x3_ + swing_x, gpx7->pos_y3_ + swing_y, gpx7->pos_x4_ + swing_x, gpx7->pos_y4_ + swing_y,
			file_vector_[gpx7->file_id_].div_vector_[gpx7->file_div_], gpx7->flag_trans_);
		draw_deque_set.gpx7_deque_.pop_front();
	}
	while (!draw_deque_set.gpx8_deque_.empty()) {
		gpx8 = &draw_deque_set.gpx8_deque_.front();
		DrawRectGraph(gpx8->pos_dx_ + swing_x, gpx8->pos_dy_ + swing_y, 
			gpx8->pos_sx_ + swing_x, gpx8->pos_sy_ + swing_y, gpx8->val_width_, gpx8->val_height_, 
			file_vector_[gpx8->file_id_].div_vector_[gpx8->file_div_], gpx8->flag_trans_, gpx8->flag_turn_);
		draw_deque_set.gpx8_deque_.pop_front();
	}

	if (!draw_deque_set.gpx1b_deque_.empty()) {
		gpx1b = &draw_deque_set.gpx1b_deque_.front();
		SetDrawBlendMode(gpx1b->blend_mode_, gpx1b->blend_alpha_);
	}
	while (!draw_deque_set.gpx1b_deque_.empty()) {
		gpx1b = &draw_deque_set.gpx1b_deque_.front();
		DrawGraph(gpx1b->pos_x_ + swing_x, gpx1b->pos_y_ + swing_y, 
			file_vector_[gpx1b->file_id_].div_vector_[gpx1b->file_div_], gpx1b->flag_trans_);
		draw_deque_set.gpx1b_deque_.pop_front();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (!draw_deque_set.gpx2b_deque_.empty()) {
		gpx2b = &draw_deque_set.gpx2b_deque_.front();
		SetDrawBlendMode(gpx2b->blend_mode_, gpx2b->blend_alpha_);
	}
	while (!draw_deque_set.gpx2b_deque_.empty()) {
		gpx2b = &draw_deque_set.gpx2b_deque_.front();
		DrawTurnGraph(gpx2b->pos_x_ + swing_x, gpx2b->pos_y_ + swing_y,
			file_vector_[gpx2b->file_id_].div_vector_[gpx2b->file_div_], gpx2b->flag_trans_);
		draw_deque_set.gpx2b_deque_.pop_front();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (!draw_deque_set.gpx3b_deque_.empty()) {
		gpx3b = &draw_deque_set.gpx3b_deque_.front();
		SetDrawBlendMode(gpx3b->blend_mode_, gpx3b->blend_alpha_);
	}
	while (!draw_deque_set.gpx3_deque_.empty()) {
		gpx3b = &draw_deque_set.gpx3b_deque_.front();
		DrawExtendGraph(gpx3b->pos_x1_ + swing_x, gpx3b->pos_y1_+ swing_y,
			gpx3b->pos_x2_ + swing_x, gpx3b->pos_y2_ + swing_y, 
			file_vector_[gpx3b->file_id_].div_vector_[gpx3b->file_div_], gpx3b->flag_trans_);
		draw_deque_set.gpx3b_deque_.pop_front();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (!draw_deque_set.gpx4b_deque_.empty()) {
		gpx4b = &draw_deque_set.gpx4b_deque_.front();
		SetDrawBlendMode(gpx4b->blend_mode_, gpx4b->blend_alpha_);
	}
	while (!draw_deque_set.gpx4b_deque_.empty()) {
		gpx4b = &draw_deque_set.gpx4b_deque_.front();
		DrawRotaGraph(gpx4b->pos_cx_ + swing_x, gpx4b->pos_cy_ + swing_y, gpx4b->extend_rate_, gpx4b->draw_angle_,
			file_vector_[gpx4b->file_id_].div_vector_[gpx4b->file_div_], gpx4b->flag_trans_, gpx4b->flag_turn_);
		draw_deque_set.gpx4b_deque_.pop_front();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (!draw_deque_set.gpx5b_deque_.empty()) {
		gpx5b = &draw_deque_set.gpx5b_deque_.front();
		SetDrawBlendMode(gpx5b->blend_mode_, gpx5b->blend_alpha_);
	}
	while (!draw_deque_set.gpx5_deque_.empty()) {
		gpx5b = &draw_deque_set.gpx5b_deque_.front();
		DrawRotaGraph2(gpx5b->pos_x_ + swing_x, gpx5b->pos_y_ + swing_y, 
			gpx5b->pos_cx_ + swing_x, gpx5b->pos_cy_ + swing_y, gpx5b->extend_rate_, gpx5b->draw_angle_, 
			file_vector_[gpx5b->file_id_].div_vector_[gpx5b->file_div_], gpx5b->flag_trans_, gpx5b->flag_turn_);
		draw_deque_set.gpx5b_deque_.pop_front();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

