#include "DxLib.h"
#include "NyaDefine.h"
#include "NyaGraphic.h"


///////////////////////////////////////
// 未完成なのでビルドできないファイル
///////////////////////////////////////


using namespace std;
using namespace H2NLIB;

std::vector<GraphicFileSet> NyaGraphic::file_vector_;
std::vector<DrawDequeSet> NyaGraphic::layer_vector_(eOBJECT::GROUP::sizeof_enum);


NyaGraphic::NyaGraphic()
{

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

void NyaGraphic::Run(void)
{

	Draw(eOBJECT::USER, swing_x_, swing_y_);


}


/**
@brief 描画関数
@param layer 描画するレイヤー
*/
void NyaGraphic::Draw(int layer, int swing_x, int swing_y)
{
	DrawDequeSet draw_deque_set;
	GraphicPropertyX1* gpx1;
	GraphicPropertyX2* gpx2;

	
	draw_deque_set = layer_vector_.at(layer);
	while (!draw_deque_set.gpx1_deque_.empty()) {
		gpx1 = &draw_deque_set.gpx1_deque_.front();
		DrawGraph(gpx1->pos_x_ + swing_x, gpx1->pos_y_ + swing_y, 
			file_vector_[gpx1->file_id_].div_vector_[gpx1->file_div_], gpx1->flag_trans_);
		draw_deque_set.gpx1_deque_.pop_front();
	}
	while (!draw_deque_set.gpx2_deque_.empty()) {
		gpx2 = &draw_deque_set.gpx2_deque_.front();
		DrawGraph(gpx2->pos_x_ + swing_x, gpx2->pos_y_ + swing_y, 
			file_vector_[gpx2->file_id_].div_vector_.at(gpx2->file_div_), gpx2->flag_trans_);
		DrawTurnGraph(gpx2->pos_x_ + swing_x, gpx2->pos_y_ + swing_y,
				file_vector_[gpx2->file_id_].div_vector_[gpx2->file_div_], gpx2->flag_trans_);
		draw_deque_set.gpx1_deque_.pop_front();
	}


	//for (unsigned int i = 0; i < id_draw_[layer]; i++) {

	//#ifdef __DEBUG__
	//	debug_imgnum++;
	//#endif

	//	// 描画処理
	//	itoken = &vec_itoken_[layer][i];
	//	switch (vec_itoken_[layer][i].draw_type_) {
	//	case eGRAPHIC::DRAW::TYPE1:
	//		DrawGraph(itoken->param1_.x_ + swing_x, itoken->param1_.y_ + swing_y,
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param1_.flag_trans_);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE2:
	//		DrawTurnGraph(itoken->param2_.pos_x_ + swing_x, itoken->param2_.pos_y_ + swing_y,
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param2_.flag_trans_);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE3:
	//		DrawExtendGraph(itoken->param3_.pos_x1_ + swing_x, itoken->param3_.pos_y1_+ swing_y,
	//			itoken->param3_.pos_x2_ + swing_x, itoken->param3_.pos_y2_ + swing_y, 
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param3_.flag_trans_);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE4:
	//		DrawRotaGraph(itoken->param4_.pos_cx_ + swing_x, itoken->param4_.pos_cy_ + swing_y,
	//			itoken->param4_.extend_rate_, itoken->param4_.draw_angle_,
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param4_.flag_trans_, itoken->param4_.flag_turn_);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE5:
	//		DrawRotaGraph2(itoken->param5_.pos_x_ + swing_x, itoken->param5_.pos_y_ + swing_y, 
	//			itoken->param5_.pos_cx_ + swing_x, itoken->param5_.pos_cy_ + swing_y,
	//			itoken->param5_.extend_rate_, itoken->param5_.draw_angle_, 
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param5_.flag_trans_, itoken->param5_.flag_turn_);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE6:
	//		DrawRotaGraph3(itoken->param6_.pos_x_ + swing_x, itoken->param6_.pos_y_ + swing_y, 
	//			itoken->param6_.pos_cx_ + swing_x, itoken->param6_.pos_cy_ + swing_y,
	//			itoken->param6_.extend_ratex_, itoken->param6_.extend_ratey_, itoken->param6_.draw_angle_,
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param6_.flag_trans_, itoken->param6_.flag_turn_);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE7:
	//		DrawModiGraph(itoken->param7_.pos_x1_ + swing_x, itoken->param7_.pos_y1_ + swing_y, 
	//			itoken->param7_.pos_x2_ + swing_x, itoken->param7_.pos_y2_ + swing_y,
	//			itoken->param7_.pos_x3_ + swing_x, itoken->param7_.pos_y3_ + swing_y, 
	//			itoken->param7_.pos_x4_ + swing_x, itoken->param7_.pos_y4_ + swing_y,
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param7_.flag_trans_);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE8:
	//		DrawRectGraph(itoken->param8_.pos_dx_ + swing_x, itoken->param8_.pos_dy_ + swing_y, 
	//			itoken->param8_.pos_sx_ + swing_x, itoken->param8_.pos_sy_ + swing_y,
	//			itoken->param8_.val_width_, itoken->param8_.val_height_, 
	//			vec_iload_[itoken->id_].file_[itoken->div_],itoken->param8_.flag_trans_, itoken->param8_.flag_turn_);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE1B:
	//		SetDrawBlendMode(itoken->param1b_.blend_mode_, itoken->param1b_.blend_alpha_);
	//		DrawGraph(itoken->param1b_.pos_x_ + swing_x, itoken->param1b_.pos_y_ + swing_y,
	//		vec_iload_[itoken->id_].file_[itoken->div_], itoken->param1b_.flag_trans_);
	//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE2B:
	//		SetDrawBlendMode(itoken->param2b_.blend_mode_, itoken->param2b_.blend_alpha_);
	//		DrawTurnGraph(itoken->param2b_.pos_x_ + swing_x, itoken->param2b_.pos_y_ + swing_y, 
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param2b_.flag_trans_);
	//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE3B:
	//		SetDrawBlendMode(itoken->param3b_.blend_mode_, itoken->param3b_.blend_alpha_);
	//		DrawExtendGraph(itoken->param3b_.pos_x1_ + swing_x, itoken->param3b_.pos_y1_ + swing_y, 
	//			itoken->param3b_.pos_x2_ + swing_x, itoken->param3b_.pos_y2_ + swing_y, 
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param3b_.flag_trans_);
	//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE4B:
	//		SetDrawBlendMode(itoken->param4b_.blend_mode_, itoken->param4b_.blend_alpha_);
	//		DrawRotaGraph(itoken->param4b_.pos_cx_ + swing_x, itoken->param4b_.pos_cy_,
	//			itoken->param4b_.extend_rate_, itoken->param4b_.draw_angle_,
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param4b_.flag_trans_, itoken->param4b_.flag_turn_);
	//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//		break;
	//	case eGRAPHIC::DRAW::TYPE5B:
	//		SetDrawBlendMode(itoken->param5b_.blend_mode_, itoken->param5b_.blend_alpha_);
	//		DrawRotaGraph2(itoken->param5b_.pos_x_ + swing_x, itoken->param5b_.pos_y_ + swing_y, 
	//			itoken->param5b_.pos_cx_ + swing_x, itoken->param5b_.pos_cy_ + swing_y,
	//			itoken->param5b_.extend_rate_, itoken->param5b_.draw_angle_, 
	//			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param5b_.flag_trans_, itoken->param5b_.flag_turn_);
	//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//	default:
	//		break;
	//	}
	//}
}

