#include "DxLib.h"
#include "NyaDefine.h"
#include "NyaGraphic.h"
#include "NyaString.h"
#include <tuple>

//#define __DEBUG__

using namespace std;
using namespace H2NLIB;

int NyaGraphic::swing_x_;
int NyaGraphic::swing_y_;
std::vector<GraphicFileSet> NyaGraphic::file_vector_;
std::vector<DrawDequeSet> NyaGraphic::layer_vector_(eOBJECT::GROUP::sizeof_enum);
std::vector<bool> NyaGraphic::swing_vector_(eOBJECT::GROUP::sizeof_enum);

NyaGraphic::NyaGraphic()
{
	static bool first_call = true;

	if (first_call) {
		swing_x_ = 0;
		swing_y_ = 0;
		for (auto& it : swing_vector_)
			it = false;
		NyaString::SettingFont("debug_image_font", 15, 2);
		first_call = false;
	}

}


NyaGraphic::~NyaGraphic()
{

}

/**
@brief �摜���[�h�֐�
@param file_pass �t�@�C���p�X
@return �摜�t�@�C���̎���ID
**/
int NyaGraphic::LoadFile(std::string file_pass)
{
	int graphic_id;
	int vector_index;
	int graphic_xsize, graphic_ysize;
	static GraphicFileSet file_set;

	vector_index = 0;
	for (auto& it : file_vector_) {

		if (it.file_pass_ == file_pass) {
			return vector_index;
		}
		vector_index++;
	}

	graphic_id = LoadGraph(file_pass.c_str());
	GetGraphSize(graphic_id, &graphic_xsize, &graphic_ysize);

	file_vector_.push_back(file_set);
	file_vector_.back().div_max_ = 0;
	file_vector_.back().div_vector_.push_back(graphic_id);
	file_vector_.back().div_x_ = 0;
	file_vector_.back().div_y_ = 0;
	file_vector_.back().file_pass_ = file_pass;
	file_vector_.back().size_x_ = graphic_xsize;
	file_vector_.back().size_y_ = graphic_ysize;

	return ((int)file_vector_.size() - 1);
}

/**
@brief �����摜���[�h�֐�
@param div_x x������������
@param div_y y������������
@param size_x x�����������T�C�Y
@param size_y y�����������T�C�Y
@param file_pass �t�@�C���p�X
@return �摜�t�@�C���̎���ID (���[�h���s�̂Ƃ�-1)
@note 
 xnum �� ynum �ɂ͎��R������͂���B
 xnum * ynum ��512�ȏ�ɂȂ�l�̓��[�h�ł��Ȃ��B
**/
int NyaGraphic::LoadFile(int div_x, int div_y, int size_x, int size_y, string file_pass)
{
	static GraphicFileSet file_set;
	static int file_id[512] = {};

	if (512 <= div_x * div_y)
		return -1;
	if (size_x <= 0 || size_y <= 0)
		return -1;

	file_vector_.push_back(file_set);
	LoadDivGraph(file_pass.c_str(), div_x * div_y, div_x, div_y, size_x, size_y, file_id);
	for (int i = 0; i < div_x * div_y; i++)
		file_vector_.back().div_vector_.push_back(file_id[i]);

	file_vector_.back().div_max_ = div_x * div_y - 1;
	file_vector_.back().div_x_ = size_x;
	file_vector_.back().div_y_ = size_y;
	file_vector_.back().file_pass_ = file_pass;
	file_vector_.back().size_x_ = size_x;
	file_vector_.back().size_y_ = size_y;
	
	return ((int)file_vector_.size() - 1);
}


/**
@brief �摜�`��֐�1
@param *gpx �v���p�e�B
@return �Ȃ�
@note
 DXLIB DrawGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(GraphicPropertyX1 *gpx)
{
	layer_vector_[gpx->object_group_].gpx1_deque_.push_back(*gpx);
}


/**
@brief �摜�`��֐�2
@param *gpx �v���p�e�B
@return �Ȃ�
@note
 DXLIB DrawTurnGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(GraphicPropertyX2 *gpx)
{
	layer_vector_[gpx->object_group_].gpx2_deque_.push_back(*gpx);
}


/**
@brief �摜�`��֐�3
@param *gpx �v���p�e�B
@return �Ȃ�
@note
 DXLIB DrawExtendGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(GraphicPropertyX3 *gpx)
{
	layer_vector_[gpx->object_group_].gpx3_deque_.push_back(*gpx);
}

/**
@brief �摜�`��֐�4
@param *gpx �v���p�e�B
@return �Ȃ�
@note
DXLIB DrawRotaGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(GraphicPropertyX4 *gpx)
{
	gpx->draw_angle_ = AngleToRad(gpx->draw_angle_);
	layer_vector_[gpx->object_group_].gpx4_deque_.push_back(*gpx);
}


/**
@brief �摜�`��֐�5
@param *gpx �Z�b�g����v���p�e�B
@return �Ȃ�
@note
 DXLIB DrawRotaGraph2() �ɑΉ��B
**/
void NyaGraphic::Draw(GraphicPropertyX5 *gpx)
{
	gpx->draw_angle_ = AngleToRad(gpx->draw_angle_);
	layer_vector_.at(gpx->object_group_).gpx5_deque_.push_back(*gpx);
}


/**
@brief �摜�`��֐�6
@param *gpx �Z�b�g����v���p�e�B
@return �Ȃ�
@note
 DXLIB DrawRotaGraph3() �ɑΉ��B
**/
void NyaGraphic::Draw(GraphicPropertyX6 *gpx)
{
	gpx->draw_angle_ = AngleToRad(gpx->draw_angle_);
	layer_vector_.at(gpx->object_group_).gpx6_deque_.push_back(*gpx);
}

/**
�摜�`��֐�1b
@param *gpx �v���p�e�B
@return �Ȃ�
@note
 DXLIB DrawGraph(), DXLIB SetDrawBlendMode() �ɑΉ��B
 �������A�d�������Ȃ̂ő��p����Ƃ��͒��ӁB
**/
void NyaGraphic::Draw(GraphicPropertyX1b *gpx)
{
	layer_vector_[gpx->object_group_].gpx1b_deque_.push_back(*gpx);
}


void NyaGraphic::Run(void)
{
	static tuple<int, int, int> color = make_tuple(255, 255, 255);

	// �U������
	for (int group = eOBJECT::GROUP::enum_zero; group != eOBJECT::GROUP::sizeof_enum; group++) {
		if (swing_vector_[group]) {
			DrawAll((eOBJECT::GROUP)group, swing_x_, swing_y_);
		} else {
			DrawAll((eOBJECT::GROUP)group, 0, 0);		
		}
	}

#ifdef __DEBUG__
	NyaString::Write("debug_image_font", color, 50, 230, "[50, 230] file_vec.size = %d", (int)file_vector_.size());
#endif

}


/**
@brief �S�ẴO���t�B�b�N�f�[�^��`�悷��֐�
@param layer �`�悷�郌�C���[
@param swing_x x�������U����
@param swing_y y�������U����
**/
void NyaGraphic::DrawAll(eOBJECT::GROUP layer, int swing_x, int swing_y)
{
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
	GraphicPropertyX6b* gpx6b;
	GraphicPropertyX7b* gpx7b;
	
	while (!layer_vector_.at(layer).gpx1_deque_.empty()) {
		gpx1 = &layer_vector_.at(layer).gpx1_deque_.front();
		DrawGraph(gpx1->pos_x_ + swing_x, gpx1->pos_y_ + swing_y, 
			file_vector_[gpx1->file_id_].div_vector_[gpx1->file_div_], gpx1->flag_trans_);
		layer_vector_.at(layer).gpx1_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx2_deque_.empty()) {
		gpx2 = &layer_vector_.at(layer).gpx2_deque_.front();
		DrawTurnGraph(gpx2->pos_x_ + swing_x, gpx2->pos_y_ + swing_y,
			file_vector_[gpx2->file_id_].div_vector_[gpx2->file_div_], gpx2->flag_trans_);
		layer_vector_.at(layer).gpx2_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx3_deque_.empty()) {
		gpx3 = &layer_vector_.at(layer).gpx3_deque_.front();
		DrawExtendGraph(gpx3->pos_x1_ + swing_x, gpx3->pos_y1_+ swing_y,
			gpx3->pos_x2_ + swing_x, gpx3->pos_y2_ + swing_y, 
			file_vector_[gpx3->file_id_].div_vector_[gpx3->file_div_], gpx3->flag_trans_);
		layer_vector_.at(layer).gpx3_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx4_deque_.empty()) {
		gpx4 = &layer_vector_.at(layer).gpx4_deque_.front();
		DrawRotaGraph(gpx4->pos_cx_ + swing_x, gpx4->pos_cy_ + swing_y, gpx4->extend_rate_, gpx4->draw_angle_,
			file_vector_[gpx4->file_id_].div_vector_[gpx4->file_div_], gpx4->flag_trans_, gpx4->flag_turn_);
		layer_vector_.at(layer).gpx4_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx5_deque_.empty()) {
		gpx5 = &layer_vector_.at(layer).gpx5_deque_.front();
		DrawRotaGraph2(gpx5->pos_x_ + swing_x, gpx5->pos_y_ + swing_y, 
			gpx5->pos_cx_ + swing_x, gpx5->pos_cy_ + swing_y, gpx5->extend_rate_, gpx5->draw_angle_, 
			file_vector_[gpx5->file_id_].div_vector_[gpx5->file_div_], gpx5->flag_trans_, gpx5->flag_turn_);
		layer_vector_.at(layer).gpx5_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx6_deque_.empty()) {
		gpx6 = &layer_vector_.at(layer).gpx6_deque_.front();
		DrawRotaGraph3(gpx6->pos_x_ + swing_x, gpx6->pos_y_ + swing_y, 
			gpx6->pos_cx_ + swing_x, gpx6->pos_cy_ + swing_y, gpx6->extend_ratex_, gpx6->extend_ratey_, gpx6->draw_angle_,
			file_vector_[gpx6->file_id_].div_vector_[gpx6->file_div_], gpx6->flag_trans_, gpx6->flag_turn_);
		layer_vector_.at(layer).gpx6_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx7_deque_.empty()) {
		gpx7 = &layer_vector_.at(layer).gpx7_deque_.front();
		DrawModiGraph(
			gpx7->pos_x1_ + swing_x, gpx7->pos_y1_ + swing_y, gpx7->pos_x2_ + swing_x, gpx7->pos_y2_ + swing_y, 
			gpx7->pos_x3_ + swing_x, gpx7->pos_y3_ + swing_y, gpx7->pos_x4_ + swing_x, gpx7->pos_y4_ + swing_y,
			file_vector_[gpx7->file_id_].div_vector_[gpx7->file_div_], gpx7->flag_trans_);
		layer_vector_.at(layer).gpx7_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx8_deque_.empty()) {
		gpx8 = &layer_vector_.at(layer).gpx8_deque_.front();
		DrawRectGraph(gpx8->pos_dx_ + swing_x, gpx8->pos_dy_ + swing_y, 
			gpx8->pos_sx_ + swing_x, gpx8->pos_sy_ + swing_y, gpx8->val_width_, gpx8->val_height_, 
			file_vector_[gpx8->file_id_].div_vector_[gpx8->file_div_], gpx8->flag_trans_, gpx8->flag_turn_);
		layer_vector_.at(layer).gpx8_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx1b_deque_.empty()) {
		gpx1b = &layer_vector_.at(layer).gpx1b_deque_.front();
		SetDrawBlendMode(gpx1b->blend_mode_, gpx1b->blend_alpha_);
		DrawGraph(gpx1b->pos_x_ + swing_x, gpx1b->pos_y_ + swing_y, 
			file_vector_[gpx1b->file_id_].div_vector_[gpx1b->file_div_], gpx1b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx1b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx2b_deque_.empty()) {
		gpx2b = &layer_vector_.at(layer).gpx2b_deque_.front();
		SetDrawBlendMode(gpx2b->blend_mode_, gpx2b->blend_alpha_);
		DrawTurnGraph(gpx2b->pos_x_ + swing_x, gpx2b->pos_y_ + swing_y,
			file_vector_[gpx2b->file_id_].div_vector_[gpx2b->file_div_], gpx2b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx2b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx3b_deque_.empty()) {
		gpx3b = &layer_vector_.at(layer).gpx3b_deque_.front();
		SetDrawBlendMode(gpx3b->blend_mode_, gpx3b->blend_alpha_);
		DrawExtendGraph(gpx3b->pos_x1_ + swing_x, gpx3b->pos_y1_+ swing_y,
			gpx3b->pos_x2_ + swing_x, gpx3b->pos_y2_ + swing_y, 
			file_vector_[gpx3b->file_id_].div_vector_[gpx3b->file_div_], gpx3b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx3b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx4b_deque_.empty()) {
		gpx4b = &layer_vector_.at(layer).gpx4b_deque_.front();
		SetDrawBlendMode(gpx4b->blend_mode_, gpx4b->blend_alpha_);
		DrawRotaGraph(gpx4b->pos_cx_ + swing_x, gpx4b->pos_cy_ + swing_y, gpx4b->extend_rate_, gpx4b->draw_angle_,
			file_vector_[gpx4b->file_id_].div_vector_[gpx4b->file_div_], gpx4b->flag_trans_, gpx4b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx4b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx5b_deque_.empty()) {
		gpx5b = &layer_vector_.at(layer).gpx5b_deque_.front();
		SetDrawBlendMode(gpx5b->blend_mode_, gpx5b->blend_alpha_);
		DrawRotaGraph2(gpx5b->pos_x_ + swing_x, gpx5b->pos_y_ + swing_y, 
			gpx5b->pos_cx_ + swing_x, gpx5b->pos_cy_ + swing_y, gpx5b->extend_rate_, gpx5b->draw_angle_, 
			file_vector_[gpx5b->file_id_].div_vector_[gpx5b->file_div_], gpx5b->flag_trans_, gpx5b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx5b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx6b_deque_.empty()) {
		gpx6b = &layer_vector_.at(layer).gpx6b_deque_.front();
		SetDrawBlendMode(gpx6b->blend_mode_, gpx6b->blend_alpha_);
		DrawRotaGraph3(gpx6b->pos_x_ + swing_x, gpx6b->pos_y_ + swing_y, 
			gpx6b->pos_cx_ + swing_x, gpx6b->pos_cy_ + swing_y, gpx6b->extend_ratex_, gpx6b->extend_ratey_, gpx6b->draw_angle_,
			file_vector_[gpx6b->file_id_].div_vector_[gpx6b->file_div_], gpx6b->flag_trans_, gpx6b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx6b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx7_deque_.empty()) {
		gpx7b = &layer_vector_.at(layer).gpx7b_deque_.front();
		SetDrawBlendMode(gpx7b->blend_mode_, gpx7b->blend_alpha_);
		DrawModiGraph(
			gpx7b->pos_x1_ + swing_x, gpx7b->pos_y1_ + swing_y, gpx7b->pos_x2_ + swing_x, gpx7b->pos_y2_ + swing_y, 
			gpx7b->pos_x3_ + swing_x, gpx7b->pos_y3_ + swing_y, gpx7b->pos_x4_ + swing_x, gpx7b->pos_y4_ + swing_y,
			file_vector_[gpx7b->file_id_].div_vector_[gpx7b->file_div_], gpx7b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx7_deque_.pop_front();
	}
}

