#include "DxLib.h"
#include "NyaEnum.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaString.h"
#include <tuple>
#include <iterator>

//#define __DEBUG__

using namespace std;
using namespace HNLIB;

std::list<GraphicFile> NyaGraphic::file_collection_;
std::vector<GraphicDrawSet> NyaGraphic::layer_collection_(static_cast<int>(eOBJECT::sizeof_enum));
GraphicSwing NyaGraphic::swing_;

//***************************
// class GraphicPropertyX
//***************************

GraphicPropertyX1::GraphicPropertyX1()
{
	file_div_ = 0;
	flag_trans_ = true;
}

GraphicPropertyX2::GraphicPropertyX2()
{
	file_div_ = 0;
	flag_trans_ = true;
}

GraphicPropertyX3::GraphicPropertyX3()
{
	file_div_ = 0;
	flag_trans_ = true;
}

GraphicPropertyX4::GraphicPropertyX4()
{
	draw_angle_deg_ = 0;
	extend_rate_ = 1.0;
	file_div_ = 0;
	flag_turn_ = false;
	flag_trans_ = true;
}

GraphicPropertyX5::GraphicPropertyX5()
{
	draw_angle_deg_ = 0;
	extend_rate_ = 1.0;
	file_div_ = 0;
	flag_turn_ = false;
	flag_trans_ = true;
}


//**********************
// class GraphicSwing
//**********************

GraphicSwing::GraphicSwing()
{	// count_��8�������ƐU�����Ă��܂��̂�8�ŏ�����
	count_ = 8;
	grid_x_ = 0;
}

//**********************
// class NyaGraphic
//**********************

NyaGraphic::NyaGraphic()
{

}

NyaGraphic::~NyaGraphic()
{
	Clear();
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
/**
@brief �������Ƀ��[�h�����摜���폜����֐�
@param file_pass �������Ƀ��[�h�����f�[�^���i�[���ꂽ�t�@�C���\����
@note
 �t�@�C���p�X�ƕ����������������t�@�C�����폜����
 �Ȃ��A�t�@�C���p�X�������ł����������Ⴄ�t�@�C���͍폜���Ȃ�
**/
void NyaGraphic::DeleteGraphicFile(GraphicFile* file)
{
	if (file->pass_.empty())
		return;

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
@brief �摜���������Ƀ��[�h����֐�
@param file_pass �������Ƀ��[�h����摜�̃t�@�C���p�X
@param *file �������Ƀ��[�h���ꂽ�f�[�^���i�[���ꂽ�t�@�C���\����
@note
 ���Ƀ��[�h�ς݂̉摜�������ꍇ�A�V�������[�h�����Ƀf�[�^���i�[���ăt�@�C���\���̂�Ԃ��B
 file��NyaGraphic::Draw()�Ȃǂŗ��p����B
**/
void NyaGraphic::LoadGraphicFile(std::string file_pass, GraphicFile* file)
{
	int check_graphic_handle, check_size_x, check_size_y;
	list<GraphicFile>::iterator it;
	const GraphicFile empty_file;

	// ���[�h�ς݃t�@�C���Ȃ�V�������[�h����K�v�Ȃ�
	for (auto& e : file_collection_)
	{
		if (e.pass_ == file_pass && e.div_x_ == 0 && e.div_y_ == 0)
		{
			*file = e;
			return;
		}
	}

	// ���[�h����摜�t�@�C���̃T�C�Y�`�F�b�N
	check_graphic_handle = LoadGraph(file_pass.c_str());
	GetGraphSize(check_graphic_handle, &check_size_x, &check_size_y);
	DeleteGraph(check_graphic_handle);

	// �摜�t�@�C�����������Ƀ��[�h����
	file_collection_.push_front(empty_file);
	it = file_collection_.begin();
	it->div_collection_.push_back(LoadGraph(file_pass.c_str()));
	it->div_total_ = 1;
	it->div_x_ = 0;
	it->div_y_ = 0;
	it->pass_ = file_pass;
	it->size_x_ = check_size_x;
	it->size_y_ = check_size_y;

	// ���[�h���ʂ�Ԃ�
	*file = *it;
}

/**
@brief �摜�𕪊����ă������Ƀ��[�h����֐�
@param div_x x������������
@param div_y y������������
@param file_pass �t�@�C���p�X
@param *file ���[�h����
@note
 ���ɕ��������S���������[�h�ς݂̉摜�������ꍇ�A�V�������[�h�����Ƀf�[�^���i�[���ăt�@�C���\���̂�Ԃ��B
 file��NyaGraphic::Draw()�Ȃǂŗ��p����B
**/
void NyaGraphic::LoadGraphicFile(int div_x, int div_y, string file_pass, GraphicFile* file)
{
	int check_graphic_handle, check_size_x, check_size_y;
	static list<GraphicFile>::iterator it;
	const GraphicFile empty_file;

	// ���[�h�ς݃t�@�C���Ȃ�V�������[�h����K�v�Ȃ�
	for (auto& e : file_collection_)
	{
		if (e.pass_ == file_pass && e.div_x_ == div_x && e.div_y_ == div_y)
		{
			*file = e;
			return;
		}
	}

	// ���[�h����摜�t�@�C���̕����T�C�Y���v�Z
	check_graphic_handle = LoadGraph(file_pass.c_str());
	GetGraphSize(check_graphic_handle, &check_size_x, &check_size_y);

	check_size_x /= div_x;
	check_size_y /= div_y;
	DeleteGraph(check_graphic_handle);

	// �����摜�Ƃ��ă������Ƀ��[�h����
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

	// ���[�h���ʂ�Ԃ�
	*file = *it;
}

/**
@brief �ʏ�`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::DrawGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX1 *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx1_deque_.push_back(*gpx);
}

/**
@brief LR���]�`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::DrawTurnGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX2 *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx2_deque_.push_back(*gpx);
}


/**
@brief �g��k���`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::DrawExtendGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX3 *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx3_deque_.push_back(*gpx);
}

/**
@brief ��]�`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::DrawRotaGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX4 *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx4_deque_.push_back(*gpx);
}


/**
@brief ��]�`��֐�II
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::DrawRotaGraph2() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX5 *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx5_deque_.push_back(*gpx);
}


/**
@brief ��]�`��֐�III
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::DrawRotaGraph3() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX6 *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx6_deque_.push_back(*gpx);
}

/**
@brief ���R�ό`�`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::DrawModiGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX7 *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx7_deque_.push_back(*gpx);
}

/**
@brief ���`�`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::DrawRotaGraph3() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX8 *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx8_deque_.push_back(*gpx);
}

/**
@brief �u�����h���[�h�t���ʏ�`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX1b *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx1b_deque_.push_back(*gp);
}

/**
@brief �u�����h���[�h�t��LR���]�`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawTurnGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX2b *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx2b_deque_.push_back(*gp);
}

/**
@brief �u�����h���[�h�t���g��k���`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawExtendGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX3b *gp, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx3b_deque_.push_back(*gp);
}

/**
@brief �u�����h���[�h�t����]�`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawRotaGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX4b *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx4b_deque_.push_back(*gpx);
}

/**
@brief �u�����h���[�h�t����]�`��֐�II
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawRotaGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX5b *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx5b_deque_.push_back(*gpx);
}

/**
@brief �u�����h���[�h�t����]�`��֐�III
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawRotaGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX6b *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx6b_deque_.push_back(*gpx);
}

/**
@brief �u�����h���[�h�t�����R�ό`�`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawRotaGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX7b *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx7b_deque_.push_back(*gpx);
}

/**
@brief �u�����h���[�h�t���w���`�`��֐�
@param *gpx �`��v���p�e�B
@param layer �`�惌�C���[
@return �Ȃ�
@note
 DXLIB::SetDrawBlendMode(), DXLIB::DrawRotaGraph() �ɑΉ��B
**/
void NyaGraphic::Draw(const GraphicPropertyX8b *gpx, eOBJECT layer)
{
	layer_collection_[static_cast<int>(layer)].gpx8b_deque_.push_back(*gpx);
}

/**
@brief �S�Ă̏��������s����֐�
@note
 NyaWindow���Ŏ����I�Ɏ��s�����̂ŁA���C�u�����g�p�҂��Ăяo���K�v�͂Ȃ��B
**/
void NyaGraphic::Run(void)
{
	static tuple<int, int, int> color = make_tuple(255, 255, 255);

	CalculateSwing();
	for (eOBJECT layer = eOBJECT::enum_zero; layer != eOBJECT::sizeof_enum; ++layer)
		DrawAll(layer);

#ifdef __DEBUG__
	NyaString::Write("debug_image_font", color, 50, 230, "[50, 230] file_vec.size = %d", (int)file_vector_.size());
#endif
}

/**
@brief �U�����߂��o���֐�
**/
void HNLIB::NyaGraphic::Swing(void)
{
	// �U�����J�E���g����ϐ�count_��8�����̂Ƃ��U������̂ŁAcount_��0�ɏ���������
	// �U����x���W��0�ɏ���������
	// ����āA�A���ŌĂяo���ꂽ�ꍇ�͐U���̒l��0�ɂȂ�ď��������
	swing_.count_ = 0;
	swing_.grid_x_ = 0;
}

/**
@brief �U�������̌v�Z������֐�
**/
void NyaGraphic::CalculateSwing(void)
{
	if (swing_.count_ < 8)
	{
		if (swing_.count_ == 0 || swing_.count_ == 4)
		{	// �����ʒu����E�֐U��
			if (swing_.grid_x_ < 16)
				swing_.grid_x_ += 8;
			else
				swing_.count_++;
		}
		else if (swing_.count_ == 1 || swing_.count_ == 5)
		{	// �E���珉���ʒu�֐U��
			if (swing_.grid_x_ != 0)
				swing_.grid_x_ -= 8;
			else
				swing_.count_++;
		}
		else if (swing_.count_ == 2 || swing_.count_ == 6)
		{	// �����ʒu���獶�֐U��
			if (-16 < swing_.grid_x_)
				swing_.grid_x_ -= 8;
			else
				swing_.count_++;
		}
		else if (swing_.count_ == 3 || swing_.count_ == 7)
		{	// �����珉���ʒu�֐U��
			if (swing_.grid_x_ != 0)
				swing_.grid_x_ += 8;
			else
				swing_.count_++;
		}
	}
}

/**
@brief �S�ẴO���t�B�b�N�f�[�^��`�悷��֐�
@param draw_layer �`�悷�郌�C���[
**/
void NyaGraphic::DrawAll(eOBJECT draw_layer)
{
	GraphicPropertyX1* gp1;
	GraphicPropertyX2* gp2;
	GraphicPropertyX3* gp3;
	GraphicPropertyX4* gp4;
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
	GraphicPropertyX8b* gpx8b;
	int layer = static_cast<int>(draw_layer);

	while (!layer_collection_[layer].gpx1_deque_.empty())
	{
		gp1 = &layer_collection_[layer].gpx1_deque_.front();
		DrawGraph((int)gp1->draw_grid_x_ + swing_.grid_x_, (int)gp1->draw_grid_y_, 
			gp1->file_.div_collection_[gp1->file_div_], gp1->flag_trans_);
		layer_collection_[layer].gpx1_deque_.pop_front();
	}
	while (!layer_collection_[layer].gpx2_deque_.empty())
	{
		gp2 = &layer_collection_[layer].gpx2_deque_.front();
		DrawTurnGraph((int)gp2->draw_grid_x_ + swing_.grid_x_, (int)gp2->draw_grid_y_,
			gp2->file_.div_collection_[gp2->file_div_], gp2->flag_trans_);
		layer_collection_[layer].gpx2_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx3_deque_.empty()) 
	{
		gp3 = &layer_collection_.at(layer).gpx3_deque_.front();
		DrawExtendGraph((int)gp3->draw_grid_x1_ + swing_.grid_x_, (int)gp3->draw_grid_y1_,
			(int)(gp3->draw_grid_x2_ + swing_.grid_x_), (int)(gp3->draw_grid_y2_), 
			gp3->file_.div_collection_[gp3->file_div_], gp3->flag_trans_);
		layer_collection_.at(layer).gpx3_deque_.pop_front();
	}
	while (!layer_collection_[layer].gpx4_deque_.empty())
	{
		gp4 = &layer_collection_[layer].gpx4_deque_.front();
		DrawRotaGraph((int)gp4->draw_grid_cx_ + swing_.grid_x_, (int)gp4->draw_grid_cy_, 
			gp4->extend_rate_, NyaInput::AngleToRad(gp4->draw_angle_deg_),
			gp4->file_.div_collection_[gp4->file_div_], gp4->flag_trans_, gp4->flag_turn_);
		layer_collection_[layer].gpx4_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx5_deque_.empty()) {
		gpx5 = &layer_collection_.at(layer).gpx5_deque_.front();
		DrawRotaGraph2((int)gpx5->draw_grid_x_ + swing_.grid_x_, (int)gpx5->draw_grid_y_, 
			(int)gpx5->draw_grid_cx_ + swing_.grid_x_, (int)gpx5->draw_grid_cy_, gpx5->extend_rate_, NyaInput::AngleToRad(gpx5->draw_angle_deg_), 
			gpx5->file_.div_collection_[gpx5->file_div_], gpx5->flag_trans_, gpx5->flag_turn_);
		layer_collection_.at(layer).gpx5_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx6_deque_.empty()) {
		gpx6 = &layer_collection_.at(layer).gpx6_deque_.front();
		DrawRotaGraph3((int)gpx6->draw_grid_x_ + swing_.grid_x_, (int)gpx6->draw_grid_y_, 
			(int)gpx6->draw_grid_cx_ + swing_.grid_x_, (int)gpx6->draw_grid_cy_, gpx6->extend_ratex_, gpx6->extend_ratey_, NyaInput::AngleToRad(gpx6->draw_angle_deg_),
			gpx6->file_.div_collection_[gpx6->file_div_], gpx6->flag_trans_, gpx6->flag_turn_);
		layer_collection_.at(layer).gpx6_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx7_deque_.empty()) {
		gpx7 = &layer_collection_.at(layer).gpx7_deque_.front();
		DrawModiGraph(
			(int)gpx7->pos_x1_ + swing_.grid_x_, (int)gpx7->pos_y1_, (int)gpx7->pos_x2_ + swing_.grid_x_, (int)gpx7->pos_y2_, 
			(int)gpx7->pos_x3_ + swing_.grid_x_, (int)gpx7->pos_y3_, (int)gpx7->pos_x4_ + swing_.grid_x_, (int)gpx7->pos_y4_,
			gpx7->file_.div_collection_[gpx7->file_div_], gpx7->flag_trans_);
		layer_collection_.at(layer).gpx7_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx8_deque_.empty()) {
		gpx8 = &layer_collection_.at(layer).gpx8_deque_.front();
		DrawRectGraph(gpx8->pos_dx_ + swing_.grid_x_, gpx8->pos_dy_, 
			gpx8->pos_sx_ + swing_.grid_x_, gpx8->pos_sy_, gpx8->val_width_, gpx8->val_height_, 
			gpx8->file_.div_collection_[gpx8->file_div_], gpx8->flag_trans_, gpx8->flag_turn_);
		layer_collection_.at(layer).gpx8_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx1b_deque_.empty()) {
		gpx1b = &layer_collection_.at(layer).gpx1b_deque_.front();
		SetDrawBlendMode(gpx1b->blend_mode_, gpx1b->blend_alpha_);
		DrawGraph(gpx1b->pos_x_ + swing_.grid_x_, gpx1b->pos_y_, 
			gpx1b->file_.div_collection_[gpx1b->file_div_], gpx1b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx1b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx2b_deque_.empty()) {
		gpx2b = &layer_collection_.at(layer).gpx2b_deque_.front();
		SetDrawBlendMode(gpx2b->blend_mode_, gpx2b->blend_alpha_);
		DrawTurnGraph(gpx2b->pos_x_ + swing_.grid_x_, gpx2b->pos_y_,
			gpx2b->file_.div_collection_[gpx2b->file_div_], gpx2b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx2b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx3b_deque_.empty()) {
		gpx3b = &layer_collection_.at(layer).gpx3b_deque_.front();
		SetDrawBlendMode(gpx3b->blend_mode_, gpx3b->blend_alpha_);
		DrawExtendGraph(gpx3b->pos_x1_ + swing_.grid_x_, gpx3b->pos_y1_,
			gpx3b->pos_x2_ + swing_.grid_x_, gpx3b->pos_y2_, 
			gpx3b->file_.div_collection_[gpx3b->file_div_], gpx3b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx3b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx4b_deque_.empty()) {
		gpx4b = &layer_collection_.at(layer).gpx4b_deque_.front();
		SetDrawBlendMode(gpx4b->blend_mode_, gpx4b->blend_alpha_);
		DrawRotaGraph(gpx4b->pos_cx_ + swing_.grid_x_, gpx4b->pos_cy_, gpx4b->extend_rate_, NyaInput::AngleToRad(gpx4b->draw_angle_deg_),
			gpx4b->file_.div_collection_[gpx4b->file_div_], gpx4b->flag_trans_, gpx4b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx4b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx5b_deque_.empty()) {
		gpx5b = &layer_collection_.at(layer).gpx5b_deque_.front();
		SetDrawBlendMode(gpx5b->blend_mode_, gpx5b->blend_alpha_);
		DrawRotaGraph2(gpx5b->pos_x_ + swing_.grid_x_, gpx5b->pos_y_, 
			gpx5b->pos_cx_ + swing_.grid_x_, gpx5b->pos_cy_, gpx5b->extend_rate_, NyaInput::AngleToRad(gpx5b->draw_angle_deg_), 
			gpx5b->file_.div_collection_[gpx5b->file_div_], gpx5b->flag_trans_, gpx5b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx5b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx6b_deque_.empty()) {
		gpx6b = &layer_collection_.at(layer).gpx6b_deque_.front();
		SetDrawBlendMode(gpx6b->blend_mode_, gpx6b->blend_alpha_);
		DrawRotaGraph3(gpx6b->pos_x_ + swing_.grid_x_, gpx6b->pos_y_, 
			gpx6b->pos_cx_ + swing_.grid_x_, gpx6b->pos_cy_, gpx6b->extend_ratex_, gpx6b->extend_ratey_, NyaInput::AngleToRad(gpx6b->draw_angle_deg_),
			gpx6b->file_.div_collection_[gpx6b->file_div_], gpx6b->flag_trans_, gpx6b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx6b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx7b_deque_.empty()) {
		gpx7b = &layer_collection_.at(layer).gpx7b_deque_.front();
		SetDrawBlendMode(gpx7b->blend_mode_, gpx7b->blend_alpha_);
		DrawModiGraph(
			gpx7b->pos_x1_ + swing_.grid_x_, gpx7b->pos_y1_, gpx7b->pos_x2_ + swing_.grid_x_, gpx7b->pos_y2_, 
			gpx7b->pos_x3_ + swing_.grid_x_, gpx7b->pos_y3_, gpx7b->pos_x4_ + swing_.grid_x_, gpx7b->pos_y4_,
			gpx7b->file_.div_collection_[gpx7b->file_div_], gpx7b->flag_trans_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx7b_deque_.pop_front();
	}
	while (!layer_collection_.at(layer).gpx8b_deque_.empty()) {
		gpx8b = &layer_collection_.at(layer).gpx8b_deque_.front();
		SetDrawBlendMode(gpx8b->blend_mode_, gpx8b->blend_alpha_);
		DrawRectGraph(gpx8b->pos_dx_ + swing_.grid_x_, gpx8b->pos_dy_, 
			gpx8b->pos_sx_ + swing_.grid_x_, gpx8b->pos_sy_, gpx8b->val_width_, gpx8b->val_height_, 
			gpx8b->file_.div_collection_[gpx8b->file_div_], gpx8b->flag_trans_, gpx8b->flag_turn_);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		layer_collection_.at(layer).gpx8b_deque_.pop_front();
	}
}

