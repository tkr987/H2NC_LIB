#include "DxLib.h"
#include "NyaDefine.h"
#include "NyaGraphic.h"


///////////////////////////////////////
// 未完成なのでビルドできないファイル
///////////////////////////////////////


using namespace H2NLIB;

std::vector<DrawQueueSet> layer_vector_(eOBJECT::GROUP::sizeof_enum);



NyaGraphic::NyaGraphic()
{

}


NyaGraphic::~NyaGraphic()
{

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
	static ImgToken* itoken;

	
	draw_deque_set = layer_vector_.at(layer);
	while (!draw_deque_set.gpx1_deque_.empty()) {
		gpx1 = &draw_deque_set.gpx1_deque_.front();
		DrawGraph(gpx1->pos_x_ + swing_x, gpx1->pos_y_ + swing_y, vec_iload_[itoken->id_].file_[itoken->div_], gpx1->flag_trans_);
		draw_deque_set.gpx1_deque_.pop_front();
	}

	//while (!deque_string_data_.empty()) {
	//	sd = deque_string_data_.front();
	//	if (sd.type_i_) {
	//		DrawFormatStringToHandle(sd.pos_x_, sd.pos_y_, color, sd.style_, sd.str_.c_str(), sd.val_i_);
	//	} else if (sd.type_d_) {
	//		DrawFormatStringToHandle(sd.pos_x_, sd.pos_y_, color, sd.style_, sd.str_.c_str(), sd.val_d_);
	//	} else {
	//		DrawStringToHandle(sd.pos_x_, sd.pos_y_, sd.str_.c_str(), color, sd.style_);
	//	}
	//	deque_string_data_.pop_front();
	//}


	for (unsigned int i = 0; i < id_draw_[layer]; i++) {

	#ifdef __DEBUG__
		debug_imgnum++;
	#endif

		// 描画処理
		itoken = &vec_itoken_[layer][i];
		switch (vec_itoken_[layer][i].draw_type_) {
		case eGRAPHIC::DRAW::TYPE1:
			DrawGraph(itoken->param1_.x_ + swing_x, itoken->param1_.y_ + swing_y,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param1_.flag_trans_);
			break;
		case eGRAPHIC::DRAW::TYPE2:
			DrawTurnGraph(itoken->param2_.pos_x_ + swing_x, itoken->param2_.pos_y_ + swing_y,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param2_.flag_trans_);
			break;
		case eGRAPHIC::DRAW::TYPE3:
			DrawExtendGraph(itoken->param3_.pos_x1_ + swing_x, itoken->param3_.pos_y1_+ swing_y,
				itoken->param3_.pos_x2_ + swing_x, itoken->param3_.pos_y2_ + swing_y, 
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param3_.flag_trans_);
			break;
		case eGRAPHIC::DRAW::TYPE4:
			DrawRotaGraph(itoken->param4_.pos_cx_ + swing_x, itoken->param4_.pos_cy_ + swing_y,
				itoken->param4_.extend_rate_, itoken->param4_.draw_angle_,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param4_.flag_trans_, itoken->param4_.flag_turn_);
			break;
		case eGRAPHIC::DRAW::TYPE5:
			DrawRotaGraph2(itoken->param5_.pos_x_ + swing_x, itoken->param5_.pos_y_ + swing_y, 
				itoken->param5_.pos_cx_ + swing_x, itoken->param5_.pos_cy_ + swing_y,
				itoken->param5_.extend_rate_, itoken->param5_.draw_angle_, 
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param5_.flag_trans_, itoken->param5_.flag_turn_);
			break;
		case eGRAPHIC::DRAW::TYPE6:
			DrawRotaGraph3(itoken->param6_.pos_x_ + swing_x, itoken->param6_.pos_y_ + swing_y, 
				itoken->param6_.pos_cx_ + swing_x, itoken->param6_.pos_cy_ + swing_y,
				itoken->param6_.extend_ratex_, itoken->param6_.extend_ratey_, itoken->param6_.draw_angle_,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param6_.flag_trans_, itoken->param6_.flag_turn_);
			break;
		case eGRAPHIC::DRAW::TYPE7:
			DrawModiGraph(itoken->param7_.pos_x1_ + swing_x, itoken->param7_.pos_y1_ + swing_y, 
				itoken->param7_.pos_x2_ + swing_x, itoken->param7_.pos_y2_ + swing_y,
				itoken->param7_.pos_x3_ + swing_x, itoken->param7_.pos_y3_ + swing_y, 
				itoken->param7_.pos_x4_ + swing_x, itoken->param7_.pos_y4_ + swing_y,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param7_.flag_trans_);
			break;
		case eGRAPHIC::DRAW::TYPE8:
			DrawRectGraph(itoken->param8_.pos_dx_ + swing_x, itoken->param8_.pos_dy_ + swing_y, 
				itoken->param8_.pos_sx_ + swing_x, itoken->param8_.pos_sy_ + swing_y,
				itoken->param8_.val_width_, itoken->param8_.val_height_, 
				vec_iload_[itoken->id_].file_[itoken->div_],itoken->param8_.flag_trans_, itoken->param8_.flag_turn_);
			break;
		case eGRAPHIC::DRAW::TYPE1B:
			SetDrawBlendMode(itoken->param1b_.blend_mode_, itoken->param1b_.blend_alpha_);
			DrawGraph(itoken->param1b_.pos_x_ + swing_x, itoken->param1b_.pos_y_ + swing_y,
			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param1b_.flag_trans_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case eGRAPHIC::DRAW::TYPE2B:
			SetDrawBlendMode(itoken->param2b_.blend_mode_, itoken->param2b_.blend_alpha_);
			DrawTurnGraph(itoken->param2b_.pos_x_ + swing_x, itoken->param2b_.pos_y_ + swing_y, 
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param2b_.flag_trans_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case eGRAPHIC::DRAW::TYPE3B:
			SetDrawBlendMode(itoken->param3b_.blend_mode_, itoken->param3b_.blend_alpha_);
			DrawExtendGraph(itoken->param3b_.pos_x1_ + swing_x, itoken->param3b_.pos_y1_ + swing_y, 
				itoken->param3b_.pos_x2_ + swing_x, itoken->param3b_.pos_y2_ + swing_y, 
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param3b_.flag_trans_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case eGRAPHIC::DRAW::TYPE4B:
			SetDrawBlendMode(itoken->param4b_.blend_mode_, itoken->param4b_.blend_alpha_);
			DrawRotaGraph(itoken->param4b_.pos_cx_ + swing_x, itoken->param4b_.pos_cy_,
				itoken->param4b_.extend_rate_, itoken->param4b_.draw_angle_,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param4b_.flag_trans_, itoken->param4b_.flag_turn_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case eGRAPHIC::DRAW::TYPE5B:
			SetDrawBlendMode(itoken->param5b_.blend_mode_, itoken->param5b_.blend_alpha_);
			DrawRotaGraph2(itoken->param5b_.pos_x_ + swing_x, itoken->param5b_.pos_y_ + swing_y, 
				itoken->param5b_.pos_cx_ + swing_x, itoken->param5b_.pos_cy_ + swing_y,
				itoken->param5b_.extend_rate_, itoken->param5b_.draw_angle_, 
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param5b_.flag_trans_, itoken->param5b_.flag_turn_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		default:
			break;
		}
	}
}

