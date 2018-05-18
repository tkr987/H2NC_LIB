#include "DxLib.h"
#include "NyaDefine.h"
#include "NyaGraphic.h"
#include "NyaString.h"
#include <tuple>
#include <iterator>

//#define __DEBUG__

using namespace std;
using namespace H2NLIB;

int NyaGraphic::swing_x_;
int NyaGraphic::swing_y_;
std::list<GraphicFile> NyaGraphic::file_list_;
std::vector<DrawDequeSet> NyaGraphic::layer_vector_(static_cast<int>(eOBJECT::sizeof_enum));
std::vector<bool> NyaGraphic::swing_vector_(static_cast<int>(eOBJECT::sizeof_enum));


void NyaGraphic::DeleteGraphicFile(GraphicFile* file)
{
	// �t�@�C���p�X�ƕ����������������t�@�C�����폜����
	// �Ȃ��A�t�@�C���p�X�������ł����������Ⴄ�t�@�C���͍폜���Ȃ�
	for (list<GraphicFile>::iterator it = file_list_.begin(); it != file_list_.end(); ++it)
	{
		if (it->pass_ == file->pass_ && it->div_x_ == file->div_x_ && it->div_y_ == file->div_y_)
		{
			for (auto& e : it->div_vector_)
				DeleteGraph(e);
			
			file_list_.erase(it);
			return;
		}
	}
}

/**
@brief �摜���[�h�֐�
@param file_pass �t�@�C���p�X
@param *file ���[�h����
@note
 �摜�t�@�C�����������Ƀ��[�h���ăt�@�C���\���̂�Ԃ��B
 �t�@�C���\���̂�NyaGraphic::Draw()�Ȃǂŗ��p����B
**/
void NyaGraphic::LoadGraphicFile(std::string file_pass, GraphicFile* file)
{
	int check_graphic_handle, check_size_x, check_size_y;
	list<GraphicFile>::iterator it;
	const GraphicFile empty_file;

	// ���[�h�ς݃t�@�C���Ȃ�V�������[�h����K�v�Ȃ�
	for (auto& e : file_list_)
	{
		if (e.pass_ == file_pass && e.div_x_ == 0 && e.div_y_ == 0)
			*file = e;
	}

	// ���[�h����摜�t�@�C���̃T�C�Y�`�F�b�N
	check_graphic_handle = LoadGraph(file_pass.c_str());
	GetGraphSize(check_graphic_handle, &check_size_x, &check_size_y);
	DeleteGraph(check_graphic_handle);

	// �摜�t�@�C�����������Ƀ��[�h����
	file_list_.push_front(empty_file);
	it = file_list_.begin();
	it->div_total_ = 1;
	it->div_vector_.push_back(LoadGraph(file_pass.c_str()));
	it->div_x_ = 0;
	it->div_y_ = 0;
	it->pass_ = file_pass;
	it->size_x_ = check_size_x;
	it->size_y_ = check_size_y;

	// ���[�h���ʂ�Ԃ�
	*file = *it;
}

/**
@brief �����摜���[�h�֐�
@param div_x x������������
@param div_y y������������
@param file_pass �t�@�C���p�X
@param *file ���[�h����
@note
 �摜�t�@�C�����������Ƀ��[�h���ĉ摜�t�@�C���̎���ID��Ԃ��B
 ����ID��NyaGraphic::Draw()�Ȃǂŗ��p����B
**/
void NyaGraphic::LoadGraphicFile(int div_x, int div_y, string file_pass, GraphicFile* file)
{
	int check_graphic_handle, check_size_x, check_size_y;
	static list<GraphicFile>::iterator it;
	const GraphicFile empty_file;

	// ���[�h�ς݃t�@�C���Ȃ�V�������[�h����K�v�Ȃ�
	for (auto& e : file_list_)
	{
		if (e.pass_ == file_pass && e.div_x_ == 0 && e.div_y_ == 0)
			*file = e;
	}

	// ���[�h����摜�t�@�C���̕����T�C�Y���v�Z
	check_graphic_handle = LoadGraph(file_pass.c_str());
	GetGraphSize(check_graphic_handle, &check_size_x, &check_size_y);
	check_size_x /= div_x;
	check_size_y /= div_y;
	DeleteGraph(check_graphic_handle);

	// �����摜�Ƃ��ă������Ƀ��[�h����
	file_list_.push_front(empty_file);
	it = file_list_.begin();
	it->div_total_ = div_x * div_y;
	it->div_vector_.resize(div_x * div_y);
	LoadDivGraph(file_pass.c_str(), div_x * div_y, div_x, div_y, check_size_x, check_size_y, &it->div_vector_.front());
	it->div_x_ = div_x;
	it->div_y_ = div_y;
	it->pass_ = file_pass;

	// ���[�h���ʂ�Ԃ�
	*file = *it;
}


/**
@brief �ʏ�`��֐�
@param *gp �v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::DrawGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicProperty1 *gp, eOBJECT layer)
{
	layer_vector_[static_cast<int>(layer)].gp1_deque_.push_back(*gp);
}


/**
@brief �摜�`��֐�2
@param *gp �v���p�e�B
@return �Ȃ�
@note
 DXLIB::DrawTurnGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(GraphicProperty2 *gp, eOBJECT layer)
{
	layer_vector_[static_cast<int>(layer)].gp2_deque_.push_back(*gp);
}


/**
@brief �摜�`��֐�3
@param *gp �v���p�e�B
@return �Ȃ�
@note
 DXLIB::DrawExtendGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(GraphicProperty3 *gp, eOBJECT layer)
{
	layer_vector_[static_cast<int>(layer)].gp3_deque_.push_back(*gp);
}

/**
@brief �摜�`��֐�4
@param *gp �v���p�e�B
@return �Ȃ�
@note
 DXLIB::DrawRotaGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicProperty4 *gp, eOBJECT layer)
{
	layer_vector_[static_cast<int>(layer)].gp4_deque_.push_back(*gp);
	layer_vector_[static_cast<int>(layer)].gp4_deque_.back().draw_angle_ = AngleToRad(gp->draw_angle_);
}


/**
@brief �摜�`��֐�5
@param *gpx �Z�b�g����v���p�e�B
@return �Ȃ�
@note
 DXLIB::DrawRotaGraph2() �ɑΉ��B
**/
void NyaGraphic::Draw(GraphicProperty5 *gp, eOBJECT layer)
{
	layer_vector_[static_cast<int>(layer)].gpx5_deque_.push_back(*gp);
	layer_vector_[static_cast<int>(layer)].gpx5_deque_.back().draw_angle_ = AngleToRad(gp->draw_angle_);
}


/**
@brief �摜�`��֐�6
@param *gpx �Z�b�g����v���p�e�B
@return �Ȃ�
@note
 DXLIB::DrawRotaGraph3() �ɑΉ��B
**/
void NyaGraphic::Draw(GraphicProperty6 *gp, eOBJECT layer)
{
	layer_vector_[static_cast<int>(layer)].gpx6_deque_.push_back(*gp);
	layer_vector_[static_cast<int>(layer)].gpx6_deque_.back().draw_angle_ = AngleToRad(gp->draw_angle_);
}

/**
@brief �摜�`��֐�1b
@param *gpx �v���p�e�B
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawGraph() �ɑΉ��B
 �������A�d�������Ȃ̂ő��p����Ƃ��͒��ӁB
**/
void NyaGraphic::Draw(GraphicProperty1b *gp, eOBJECT layer)
{
	layer_vector_[static_cast<int>(layer)].gpx1b_deque_.push_back(*gp);
}

/**
@brief �摜�`��֐�2b
@param *gpx �v���p�e�B
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawTurnGraph() �ɑΉ��B
 �������A�d�������Ȃ̂ő��p����Ƃ��͒��ӁB
**/
void NyaGraphic::Draw(GraphicProperty2b *gp, eOBJECT layer)
{
	layer_vector_[static_cast<int>(layer)].gpx2b_deque_.push_back(*gp);
}

/**
@brief �摜�`��֐�3b
@param *gpx �v���p�e�B
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawExtendGraph() �ɑΉ��B
 �������A�d�������Ȃ̂ő��p����Ƃ��͒��ӁB
**/
void NyaGraphic::Draw(GraphicProperty3b *gp, eOBJECT layer)
{
	layer_vector_[static_cast<int>(layer)].gpx3b_deque_.push_back(*gp);
}

/**
@brief ��]�`��֐�
@param *gp �v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawRotaGraph() �ɑΉ��B
 �������A�d�������Ȃ̂ő��p����Ƃ��͒��ӁB
**/
void NyaGraphic::Draw(GraphicProperty4b *gp, eOBJECT layer)
{
	layer_vector_[static_cast<int>(layer)].gpx4b_deque_.push_back(*gp);
}

void NyaGraphic::Init(void)
{
	static bool first_call = true;

	if (first_call)
	{
		swing_x_ = 0;
		swing_y_ = 0;
		for (auto& e : swing_vector_)
			e = false;
		NyaString::SettingFont("debug_image_font", 15, 2);
		first_call = false;
	}

	swing_x_ = 0;
	swing_y_ = 0;
	file_list_.clear();
	for (auto& e : layer_vector_)
		e.Clear();
	for (auto& e : swing_vector_)
		e = false;
}

void NyaGraphic::Run(void)
{
	static tuple<int, int, int> color = make_tuple(255, 255, 255);

	// �U������
	for (eOBJECT group = eOBJECT::enum_zero; group != eOBJECT::sizeof_enum; ++group)
	{
		if (swing_vector_[static_cast<int>(group)]) {
			DrawAll((eOBJECT)group, swing_x_, swing_y_);
		} else {
			DrawAll((eOBJECT)group, 0, 0);		
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
void NyaGraphic::DrawAll(eOBJECT draw_layer, int swing_x, int swing_y)
{
	GraphicProperty1* gp1;
	GraphicProperty2* gp2;
	GraphicProperty3* gp3;
	GraphicProperty4* gp4;
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
	int layer = static_cast<int>(draw_layer);

	while (!layer_vector_[layer].gp1_deque_.empty())
	{
		gp1 = &layer_vector_[layer].gp1_deque_.front();
		DrawGraph((int)(gp1->draw_grid_x_ + swing_x), (int)(gp1->draw_grid_y_ + swing_y), 
			gp1->graphic_file_.div_vector_[gp1->file_div_], gp1->flag_trans_);
		layer_vector_[layer].gp1_deque_.pop_front();
	}
	while (!layer_vector_[layer].gp2_deque_.empty())
	{
		gp2 = &layer_vector_[layer].gp2_deque_.front();
		DrawTurnGraph((int)(gp2->draw_grid_x_ + swing_x), (int)(gp2->draw_grid_y_ + swing_y),
			gp2->graphic_file_.div_vector_[gp2->file_div_], gp2->flag_trans_);
		layer_vector_[layer].gp2_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gp3_deque_.empty()) 
	{
		gp3 = &layer_vector_.at(layer).gp3_deque_.front();
		DrawExtendGraph((int)(gp3->draw_grid_x1_ + swing_x), (int)(gp3->draw_grid_y1_+ swing_y),
			(int)(gp3->draw_grid_x2_ + swing_x), (int)(gp3->draw_grid_y2_ + swing_y), 
			gp3->graphic_file_.div_vector_[gp3->file_div_], gp3->flag_trans_);
		layer_vector_.at(layer).gp3_deque_.pop_front();
	}
	while (!layer_vector_[layer].gp4_deque_.empty())
	{
		gp4 = &layer_vector_[layer].gp4_deque_.front();
		DrawRotaGraph((int)(gp4->draw_grid_cx_ + swing_x), (int)(gp4->draw_grid_cy_ + swing_y), 
			gp4->extend_rate_, gp4->draw_angle_,
			gp4->graphic_file_.div_vector_[gp4->file_div_], gp4->flag_trans_, gp4->flag_turn_);
		layer_vector_[layer].gp4_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx5_deque_.empty()) {
		gpx5 = &layer_vector_.at(layer).gpx5_deque_.front();
		DrawRotaGraph2(gpx5->pos_x_ + swing_x, gpx5->pos_y_ + swing_y, 
			gpx5->pos_cx_ + swing_x, gpx5->pos_cy_ + swing_y, gpx5->extend_rate_, gpx5->draw_angle_, 
			gpx5->graphic_file_.div_vector_[gpx5->file_div_], gpx5->flag_trans_, gpx5->flag_turn_);
		layer_vector_.at(layer).gpx5_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx6_deque_.empty()) {
		gpx6 = &layer_vector_.at(layer).gpx6_deque_.front();
		DrawRotaGraph3(gpx6->pos_x_ + swing_x, gpx6->pos_y_ + swing_y, 
			gpx6->pos_cx_ + swing_x, gpx6->pos_cy_ + swing_y, gpx6->extend_ratex_, gpx6->extend_ratey_, gpx6->draw_angle_,
			gpx6->graphic_file_.div_vector_[gpx6->file_div_], gpx6->flag_trans_, gpx6->flag_turn_);
		layer_vector_.at(layer).gpx6_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx7_deque_.empty()) {
		gpx7 = &layer_vector_.at(layer).gpx7_deque_.front();
		DrawModiGraph(
			gpx7->pos_x1_ + swing_x, gpx7->pos_y1_ + swing_y, gpx7->pos_x2_ + swing_x, gpx7->pos_y2_ + swing_y, 
			gpx7->pos_x3_ + swing_x, gpx7->pos_y3_ + swing_y, gpx7->pos_x4_ + swing_x, gpx7->pos_y4_ + swing_y,
			gpx7->graphic_file_.div_vector_[gpx7->file_div_], gpx7->flag_trans_);
		layer_vector_.at(layer).gpx7_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx8_deque_.empty()) {
		gpx8 = &layer_vector_.at(layer).gpx8_deque_.front();
		DrawRectGraph(gpx8->pos_dx_ + swing_x, gpx8->pos_dy_ + swing_y, 
			gpx8->pos_sx_ + swing_x, gpx8->pos_sy_ + swing_y, gpx8->val_width_, gpx8->val_height_, 
			gpx8->graphic_file_.div_vector_[gpx8->file_div_], gpx8->flag_trans_, gpx8->flag_turn_);
		layer_vector_.at(layer).gpx8_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx1b_deque_.empty()) {
		gpx1b = &layer_vector_.at(layer).gpx1b_deque_.front();
		SetDrawBlendMode(gpx1b->blend_mode_, gpx1b->blend_alpha_);
		DrawGraph(gpx1b->pos_x_ + swing_x, gpx1b->pos_y_ + swing_y, 
			gpx1b->graphic_file_.div_vector_[gpx1b->file_div_], gpx1b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx1b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx2b_deque_.empty()) {
		gpx2b = &layer_vector_.at(layer).gpx2b_deque_.front();
		SetDrawBlendMode(gpx2b->blend_mode_, gpx2b->blend_alpha_);
		DrawTurnGraph(gpx2b->pos_x_ + swing_x, gpx2b->pos_y_ + swing_y,
			gpx2b->graphic_file_.div_vector_[gpx2b->file_div_], gpx2b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx2b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx3b_deque_.empty()) {
		gpx3b = &layer_vector_.at(layer).gpx3b_deque_.front();
		SetDrawBlendMode(gpx3b->blend_mode_, gpx3b->blend_alpha_);
		DrawExtendGraph(gpx3b->pos_x1_ + swing_x, gpx3b->pos_y1_+ swing_y,
			gpx3b->pos_x2_ + swing_x, gpx3b->pos_y2_ + swing_y, 
			gpx3b->graphic_file_.div_vector_[gpx3b->file_div_], gpx3b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx3b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx4b_deque_.empty()) {
		gpx4b = &layer_vector_.at(layer).gpx4b_deque_.front();
		SetDrawBlendMode(gpx4b->blend_mode_, gpx4b->blend_alpha_);
		DrawRotaGraph(gpx4b->pos_cx_ + swing_x, gpx4b->pos_cy_ + swing_y, gpx4b->extend_rate_, gpx4b->draw_angle_,
			gpx4b->graphic_file_.div_vector_[gpx4b->file_div_], gpx4b->flag_trans_, gpx4b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx4b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx5b_deque_.empty()) {
		gpx5b = &layer_vector_.at(layer).gpx5b_deque_.front();
		SetDrawBlendMode(gpx5b->blend_mode_, gpx5b->blend_alpha_);
		DrawRotaGraph2(gpx5b->pos_x_ + swing_x, gpx5b->pos_y_ + swing_y, 
			gpx5b->pos_cx_ + swing_x, gpx5b->pos_cy_ + swing_y, gpx5b->extend_rate_, gpx5b->draw_angle_, 
			gpx5b->graphic_file_.div_vector_[gpx5b->file_div_], gpx5b->flag_trans_, gpx5b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx5b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx6b_deque_.empty()) {
		gpx6b = &layer_vector_.at(layer).gpx6b_deque_.front();
		SetDrawBlendMode(gpx6b->blend_mode_, gpx6b->blend_alpha_);
		DrawRotaGraph3(gpx6b->pos_x_ + swing_x, gpx6b->pos_y_ + swing_y, 
			gpx6b->pos_cx_ + swing_x, gpx6b->pos_cy_ + swing_y, gpx6b->extend_ratex_, gpx6b->extend_ratey_, gpx6b->draw_angle_,
			gpx6b->graphic_file_.div_vector_[gpx6b->file_div_], gpx6b->flag_trans_, gpx6b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx6b_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx7_deque_.empty()) {
		gpx7b = &layer_vector_.at(layer).gpx7b_deque_.front();
		SetDrawBlendMode(gpx7b->blend_mode_, gpx7b->blend_alpha_);
		DrawModiGraph(
			gpx7b->pos_x1_ + swing_x, gpx7b->pos_y1_ + swing_y, gpx7b->pos_x2_ + swing_x, gpx7b->pos_y2_ + swing_y, 
			gpx7b->pos_x3_ + swing_x, gpx7b->pos_y3_ + swing_y, gpx7b->pos_x4_ + swing_x, gpx7b->pos_y4_ + swing_y,
			gpx7b->graphic_file_.div_vector_[gpx7b->file_div_], gpx7b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx7_deque_.pop_front();
	}
	while (!layer_vector_.at(layer).gpx8_deque_.empty()) {
		gpx8b = &layer_vector_.at(layer).gpx8b_deque_.front();
		SetDrawBlendMode(gpx8b->blend_mode_, gpx8b->blend_alpha_);
		DrawRectGraph(gpx8b->pos_dx_ + swing_x, gpx8b->pos_dy_ + swing_y, 
			gpx8b->pos_sx_ + swing_x, gpx8b->pos_sy_ + swing_y, gpx8b->val_width_, gpx8b->val_height_, 
			gpx8b->graphic_file_.div_vector_[gpx8b->file_div_], gpx8b->flag_trans_, gpx8b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_vector_.at(layer).gpx8b_deque_.pop_front();
	}
}

