#include "DxLib.h"
#include "NyaEnum.h"
#include "NyaGraphic.h"
#include "NyaString.h"
#include <tuple>
#include <iterator>

//#define __DEBUG__

using namespace std;
using namespace H2NLIB;

std::list<GraphicFile> NyaGraphic::file_collection_;
std::vector<DrawDequeSet> NyaGraphic::layer_collection_(static_cast<int>(eOBJECT::sizeof_enum));

//***************************
// class GraphicFile
//***************************

GraphicFile& GraphicFile::operator=(const GraphicFile& file)
{
	div_collection_.clear();
	std::copy(file.div_collection_.begin(), file.div_collection_.end(), back_inserter(div_collection_));
	div_total_ = file.div_total_;
	div_x_ = file.div_x_;
	div_y_ = file.div_y_;
	pass_.clear();
	pass_ = file.pass_;
	size_x_ = file.size_x_;
	size_y_ = file.size_y_;

	return *this;
}

//**********************
// class NyaGraphic
//**********************

NyaGraphic::NyaGraphic()
{
	static bool first_call = true;

	if (first_call)
	{
#ifdef __DEBUG__
		NyaString::SettingFont("debug_image_font", 15, 2);
#endif
		first_call = false;
	}
}

NyaGraphic::~NyaGraphic()
{
	Clear();
}

void NyaGraphic::DeleteGraphicFile(GraphicFile* file)
{
	// ファイルパスと分割数が両方同じファイルを削除する
	// なお、ファイルパスが同じでも分割数が違うファイルは削除しない
	for (list<GraphicFile>::iterator it = file_collection_.begin(); it != file_collection_.end(); ++it)
	{
		if (it->pass_ == file->pass_ && it->div_x_ == file->div_x_ && it->div_y_ == file->div_y_)
		{
			for (auto& e : it->div_collection_)
				DeleteGraph(e);
			
			file_collection_.erase(it);
			return;
		}
	}
}

/**
@brief 画像をメモリにロードする関数
@param file_pass メモリにロードする画像のファイルパス
@param *file メモリにロードされたデータが格納されたファイル構造体
@note
 既にロード済みの画像だった場合、新しくロードせずにデータを格納してファイル構造体を返す。
 fileはNyaGraphic::Draw()などで利用する。
**/
void NyaGraphic::LoadGraphicFile(std::string file_pass, GraphicFile* file)
{
	int check_graphic_handle, check_size_x, check_size_y;
	list<GraphicFile>::iterator it;
	const GraphicFile empty_file;

	// ロード済みファイルなら新しくロードする必要ない
	for (auto& e : file_collection_)
	{
		if (e.pass_ == file_pass && e.div_x_ == 0 && e.div_y_ == 0)
			*file = e;
	}

	// ロードする画像ファイルのサイズチェック
	check_graphic_handle = LoadGraph(file_pass.c_str());
	GetGraphSize(check_graphic_handle, &check_size_x, &check_size_y);
	DeleteGraph(check_graphic_handle);

	// 画像ファイルをメモリにロードする
	file_collection_.push_front(empty_file);
	it = file_collection_.begin();
	it->div_collection_.push_back(LoadGraph(file_pass.c_str()));
	it->div_total_ = 1;
	it->div_x_ = 0;
	it->div_y_ = 0;
	it->pass_ = file_pass;
	it->size_x_ = check_size_x;
	it->size_y_ = check_size_y;

	// ロード結果を返す
	*file = *it;
}

/**
@brief 画像を分割してメモリにロードする関数
@param div_x x軸方向分割数
@param div_y y軸方向分割数
@param file_pass ファイルパス
@param *file ロード結果
@note
 既に分割数が全く同じロード済みの画像だった場合、新しくロードせずにデータを格納してファイル構造体を返す。
 fileはNyaGraphic::Draw()などで利用する。
**/
void NyaGraphic::LoadGraphicFile(int div_x, int div_y, string file_pass, GraphicFile* file)
{
	int check_graphic_handle, check_size_x, check_size_y;
	static list<GraphicFile>::iterator it;
	const GraphicFile empty_file;

	// ロード済みファイルなら新しくロードする必要ない
	for (auto& e : file_collection_)
	{
		if (e.pass_ == file_pass && e.div_x_ == 0 && e.div_y_ == 0)
			*file = e;
	}

	// ロードする画像ファイルの分割サイズを計算
	check_graphic_handle = LoadGraph(file_pass.c_str());
	GetGraphSize(check_graphic_handle, &check_size_x, &check_size_y);

	check_size_x /= div_x;
	check_size_y /= div_y;
	DeleteGraph(check_graphic_handle);

	// 分割画像としてメモリにロードする
	file_collection_.push_front(empty_file);
	it = file_collection_.begin();
	it->div_collection_.resize(div_x * div_y);
	it->div_total_ = div_x * div_y;
	LoadDivGraph(file_pass.c_str(), div_x * div_y, div_x, div_y, check_size_x, check_size_y, &it->div_collection_.front());
	it->div_x_ = div_x;
	it->div_y_ = div_y;
	it->pass_ = file_pass;
	it->size_x_ = check_size_x;
	it->size_y_ = check_size_y;

	// ロード結果を返す
	*file = *it;
}


/**
@brief 通常描画関数
@param *gp プロパティ
@param layer 描画レイヤー
@return なし
@note
 DXLIB::DrawGraph() に対応。
**/
void NyaGraphic::Draw(const GraphicProperty1 *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gp1_deque_.push_back(*gp);
}


/**
@brief 画像描画関数2
@param *gp プロパティ
@return なし
@note
 DXLIB::DrawTurnGraph() に対応。
**/
void NyaGraphic::Draw(GraphicProperty2 *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gp2_deque_.push_back(*gp);
}


/**
@brief 画像描画関数3
@param *gp プロパティ
@return なし
@note
 DXLIB::DrawExtendGraph() に対応。
**/
void NyaGraphic::Draw(GraphicProperty3 *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gp3_deque_.push_back(*gp);
}

/**
@brief 画像描画関数4
@param *gp プロパティ
@return なし
@note
 DXLIB::DrawRotaGraph() に対応。
**/
void NyaGraphic::Draw(const GraphicProperty4 *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gp4_deque_.push_back(*gp);
	layer_collection_[static_cast<int>(layer)].gp4_deque_.back().draw_angle_ = AngleToRad(gp->draw_angle_);
}


/**
@brief 画像描画関数5
@param *gpx セットするプロパティ
@return なし
@note
 DXLIB::DrawRotaGraph2() に対応。
**/
void NyaGraphic::Draw(GraphicProperty5 *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx5_deque_.push_back(*gp);
	layer_collection_[static_cast<int>(layer)].gpx5_deque_.back().draw_angle_ = AngleToRad(gp->draw_angle_);
}


/**
@brief 画像描画関数6
@param *gpx セットするプロパティ
@return なし
@note
 DXLIB::DrawRotaGraph3() に対応。
**/
void NyaGraphic::Draw(GraphicProperty6 *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx6_deque_.push_back(*gp);
	layer_collection_[static_cast<int>(layer)].gpx6_deque_.back().draw_angle_ = AngleToRad(gp->draw_angle_);
}

/**
@brief 画像描画関数1b
@param *gpx プロパティ
@return なし
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawGraph() に対応。
 ただし、重い処理なので多用するときは注意。
**/
void NyaGraphic::Draw(GraphicProperty1b *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx1b_deque_.push_back(*gp);
}

/**
@brief 画像描画関数2b
@param *gpx プロパティ
@return なし
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawTurnGraph() に対応。
 ただし、重い処理なので多用するときは注意。
**/
void NyaGraphic::Draw(GraphicProperty2b *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx2b_deque_.push_back(*gp);
}

/**
@brief 画像描画関数3b
@param *gpx プロパティ
@return なし
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawExtendGraph() に対応。
 ただし、重い処理なので多用するときは注意。
**/
void NyaGraphic::Draw(GraphicProperty3b *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx3b_deque_.push_back(*gp);
}

/**
@brief 回転描画関数
@param *gp プロパティ
@param layer 描画レイヤー
@return なし
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawRotaGraph() に対応。
 ただし、重い処理なので多用するときは注意。
**/
void NyaGraphic::Draw(GraphicProperty4b *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx4b_deque_.push_back(*gp);
}

void NyaGraphic::Clear(void)
{
	for (auto& e : file_collection_)
	{
		for (auto& e2 : e.div_collection_)
			DeleteGraph(e2);
		e.div_collection_.clear();
	}

	file_collection_.clear();
	for (auto& e : layer_collection_)
		e.Clear();
}

void NyaGraphic::Run(void)
{
	static tuple<int, int, int> color = make_tuple(255, 255, 255);

	for (eOBJECT layer = eOBJECT::enum_zero; layer != eOBJECT::sizeof_enum; ++layer)
		DrawAll(layer);		

#ifdef __DEBUG__
	NyaString::Write("debug_image_font", color, 50, 230, "[50, 230] file_vec.size = %d", (int)file_vector_.size());
#endif

}


/**
@brief 全てのグラフィックデータを描画する関数
@param layer 描画するレイヤー
**/
void NyaGraphic::DrawAll(eOBJECT draw_layer)
{
	static GraphicProperty1* gp1;
	static GraphicProperty2* gp2;
	static GraphicProperty3* gp3;
	static GraphicProperty4* gp4;
	static GraphicProperty5* gpx5;
	static GraphicProperty6* gpx6;
	static GraphicProperty7* gpx7;
	static GraphicProperty8* gpx8;
	static GraphicProperty1b* gpx1b;
	static GraphicProperty2b* gpx2b;
	static GraphicProperty3b* gpx3b;
	static GraphicProperty4b* gpx4b;
	static GraphicProperty5b* gpx5b;
	static GraphicProperty6b* gpx6b;
	static GraphicProperty7b* gpx7b;
	static GraphicProperty8b* gpx8b;
	// static int layer = static_cast<int>(draw_layer);
	int layer = static_cast<int>(draw_layer);

	// 振動処理（未実装）
	int swing_x = 0;
	int swing_y = 0;

	while (!layer_collection_[layer].gp1_deque_.empty())
	{
		gp1 = &layer_collection_[layer].gp1_deque_.front();
		DrawGraph((int)(gp1->draw_grid_x_ + swing_x), (int)(gp1->draw_grid_y_ + swing_y), 
			gp1->graphic_file_.div_collection_[gp1->file_div_], gp1->flag_trans_);
		layer_collection_[layer].gp1_deque_.pop_front();
	}
	while (!layer_collection_[layer].gp2_deque_.empty())
	{
		gp2 = &layer_collection_[layer].gp2_deque_.front();
		DrawTurnGraph((int)(gp2->draw_grid_x_ + swing_x), (int)(gp2->draw_grid_y_ + swing_y),
			gp2->graphic_file_.div_collection_[gp2->file_div_], gp2->flag_trans_);
		layer_collection_[layer].gp2_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gp3_deque_.empty()) 
	{
		gp3 = &layer_collection_.at(layer).gp3_deque_.front();
		DrawExtendGraph((int)(gp3->draw_grid_x1_ + swing_x), (int)(gp3->draw_grid_y1_+ swing_y),
			(int)(gp3->draw_grid_x2_ + swing_x), (int)(gp3->draw_grid_y2_ + swing_y), 
			gp3->graphic_file_.div_collection_[gp3->file_div_], gp3->flag_trans_);
		layer_collection_.at(layer).gp3_deque_.pop_front();
	}
	while (!layer_collection_[layer].gp4_deque_.empty())
	{
		gp4 = &layer_collection_[layer].gp4_deque_.front();
		DrawRotaGraph((int)(gp4->draw_grid_cx_ + swing_x), (int)(gp4->draw_grid_cy_ + swing_y), 
			gp4->extend_rate_, gp4->draw_angle_,
			gp4->graphic_file_.div_collection_[gp4->file_div_], gp4->flag_trans_, gp4->flag_turn_);
		layer_collection_[layer].gp4_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx5_deque_.empty()) {
		gpx5 = &layer_collection_.at(layer).gpx5_deque_.front();
		DrawRotaGraph2(gpx5->pos_x_ + swing_x, gpx5->pos_y_ + swing_y, 
			gpx5->pos_cx_ + swing_x, gpx5->pos_cy_ + swing_y, gpx5->extend_rate_, gpx5->draw_angle_, 
			gpx5->graphic_file_.div_collection_[gpx5->file_div_], gpx5->flag_trans_, gpx5->flag_turn_);
		layer_collection_.at(layer).gpx5_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx6_deque_.empty()) {
		gpx6 = &layer_collection_.at(layer).gpx6_deque_.front();
		DrawRotaGraph3(gpx6->pos_x_ + swing_x, gpx6->pos_y_ + swing_y, 
			gpx6->pos_cx_ + swing_x, gpx6->pos_cy_ + swing_y, gpx6->extend_ratex_, gpx6->extend_ratey_, gpx6->draw_angle_,
			gpx6->graphic_file_.div_collection_[gpx6->file_div_], gpx6->flag_trans_, gpx6->flag_turn_);
		layer_collection_.at(layer).gpx6_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx7_deque_.empty()) {
		gpx7 = &layer_collection_.at(layer).gpx7_deque_.front();
		DrawModiGraph(
			gpx7->pos_x1_ + swing_x, gpx7->pos_y1_ + swing_y, gpx7->pos_x2_ + swing_x, gpx7->pos_y2_ + swing_y, 
			gpx7->pos_x3_ + swing_x, gpx7->pos_y3_ + swing_y, gpx7->pos_x4_ + swing_x, gpx7->pos_y4_ + swing_y,
			gpx7->graphic_file_.div_collection_[gpx7->file_div_], gpx7->flag_trans_);
		layer_collection_.at(layer).gpx7_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx8_deque_.empty()) {
		gpx8 = &layer_collection_.at(layer).gpx8_deque_.front();
		DrawRectGraph(gpx8->pos_dx_ + swing_x, gpx8->pos_dy_ + swing_y, 
			gpx8->pos_sx_ + swing_x, gpx8->pos_sy_ + swing_y, gpx8->val_width_, gpx8->val_height_, 
			gpx8->graphic_file_.div_collection_[gpx8->file_div_], gpx8->flag_trans_, gpx8->flag_turn_);
		layer_collection_.at(layer).gpx8_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx1b_deque_.empty()) {
		gpx1b = &layer_collection_.at(layer).gpx1b_deque_.front();
		SetDrawBlendMode(gpx1b->blend_mode_, gpx1b->blend_alpha_);
		DrawGraph(gpx1b->pos_x_ + swing_x, gpx1b->pos_y_ + swing_y, 
			gpx1b->graphic_file_.div_collection_[gpx1b->file_div_], gpx1b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx1b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx2b_deque_.empty()) {
		gpx2b = &layer_collection_.at(layer).gpx2b_deque_.front();
		SetDrawBlendMode(gpx2b->blend_mode_, gpx2b->blend_alpha_);
		DrawTurnGraph(gpx2b->pos_x_ + swing_x, gpx2b->pos_y_ + swing_y,
			gpx2b->graphic_file_.div_collection_[gpx2b->file_div_], gpx2b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx2b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx3b_deque_.empty()) {
		gpx3b = &layer_collection_.at(layer).gpx3b_deque_.front();
		SetDrawBlendMode(gpx3b->blend_mode_, gpx3b->blend_alpha_);
		DrawExtendGraph(gpx3b->pos_x1_ + swing_x, gpx3b->pos_y1_+ swing_y,
			gpx3b->pos_x2_ + swing_x, gpx3b->pos_y2_ + swing_y, 
			gpx3b->graphic_file_.div_collection_[gpx3b->file_div_], gpx3b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx3b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx4b_deque_.empty()) {
		gpx4b = &layer_collection_.at(layer).gpx4b_deque_.front();
		SetDrawBlendMode(gpx4b->blend_mode_, gpx4b->blend_alpha_);
		DrawRotaGraph(gpx4b->pos_cx_ + swing_x, gpx4b->pos_cy_ + swing_y, gpx4b->extend_rate_, gpx4b->draw_angle_,
			gpx4b->graphic_file_.div_collection_[gpx4b->file_div_], gpx4b->flag_trans_, gpx4b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx4b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx5b_deque_.empty()) {
		gpx5b = &layer_collection_.at(layer).gpx5b_deque_.front();
		SetDrawBlendMode(gpx5b->blend_mode_, gpx5b->blend_alpha_);
		DrawRotaGraph2(gpx5b->pos_x_ + swing_x, gpx5b->pos_y_ + swing_y, 
			gpx5b->pos_cx_ + swing_x, gpx5b->pos_cy_ + swing_y, gpx5b->extend_rate_, gpx5b->draw_angle_, 
			gpx5b->graphic_file_.div_collection_[gpx5b->file_div_], gpx5b->flag_trans_, gpx5b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx5b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx6b_deque_.empty()) {
		gpx6b = &layer_collection_.at(layer).gpx6b_deque_.front();
		SetDrawBlendMode(gpx6b->blend_mode_, gpx6b->blend_alpha_);
		DrawRotaGraph3(gpx6b->pos_x_ + swing_x, gpx6b->pos_y_ + swing_y, 
			gpx6b->pos_cx_ + swing_x, gpx6b->pos_cy_ + swing_y, gpx6b->extend_ratex_, gpx6b->extend_ratey_, gpx6b->draw_angle_,
			gpx6b->graphic_file_.div_collection_[gpx6b->file_div_], gpx6b->flag_trans_, gpx6b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx6b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx7_deque_.empty()) {
		gpx7b = &layer_collection_.at(layer).gpx7b_deque_.front();
		SetDrawBlendMode(gpx7b->blend_mode_, gpx7b->blend_alpha_);
		DrawModiGraph(
			gpx7b->pos_x1_ + swing_x, gpx7b->pos_y1_ + swing_y, gpx7b->pos_x2_ + swing_x, gpx7b->pos_y2_ + swing_y, 
			gpx7b->pos_x3_ + swing_x, gpx7b->pos_y3_ + swing_y, gpx7b->pos_x4_ + swing_x, gpx7b->pos_y4_ + swing_y,
			gpx7b->graphic_file_.div_collection_[gpx7b->file_div_], gpx7b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx7_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx8_deque_.empty()) {
		gpx8b = &layer_collection_.at(layer).gpx8b_deque_.front();
		SetDrawBlendMode(gpx8b->blend_mode_, gpx8b->blend_alpha_);
		DrawRectGraph(gpx8b->pos_dx_ + swing_x, gpx8b->pos_dy_ + swing_y, 
			gpx8b->pos_sx_ + swing_x, gpx8b->pos_sy_ + swing_y, gpx8b->val_width_, gpx8b->val_height_, 
			gpx8b->graphic_file_.div_collection_[gpx8b->file_div_], gpx8b->flag_trans_, gpx8b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx8b_deque_.pop_front();
	}
}

