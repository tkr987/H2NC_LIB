#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"

using namespace std;
using namespace H2NLIB;

#define EFFECT_MAX_DEFAULT 10000


int NyaEffect::count_instance_ = 0;
list<EffectAnimation1> NyaEffect::ea1_draw_list_[eOBJECT::NUM::sizeof_enum];
list<EffectAnimation1> NyaEffect::ea1_wait_list_;
list<EffectAnimation2> NyaEffect::ea2_draw_list_[eOBJECT::NUM::sizeof_enum];
list<EffectAnimation2> NyaEffect::ea2_wait_list_;

NyaEffect::NyaEffect()
{

	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;

	// ���߂ăN���X�̃C���X�^���X�����ꂽ�Ƃ��ɏ����������
	if (count_instance_ == 0)
	{
		ea1_wait_list_.resize(EFFECT_MAX_DEFAULT);
		for (auto& e : ea1_wait_list_)
		{
			e.ep_ = new EffectProperty1;
			e.gp_ = new GraphicProperty4;
		}
	}

	count_instance_++;
}


NyaEffect::~NyaEffect()
{
	delete nya_graphic_;
	delete nya_position_;

	// �N���X�̃C���X�^���X��1�����ɂȂ����Ƃ��������̉��
	if (count_instance_ == 1)
	{
		for (int type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; type++)
		{
			for (auto& e : ea1_draw_list_[type])
			{
				delete e.ep_;
				delete e.gp_;
			}
		}
		for (auto& e : ea1_wait_list_)
		{
			delete e.ep_;
			delete e.gp_;
		}
		for (int type = eOBJECT::enum_zero; type != eOBJECT::sizeof_enum; type++)
		{
			for (auto& e : ea2_draw_list_[type])
			{
				delete e.ep_;
				delete e.gp_;
			}
		}
		for (auto& e : ea2_wait_list_)
		{
			delete e.ep_;
			delete e.gp_;
		}
	}
}


/**
@brief �`��֐�
@param ep �G�t�F�N�g�v���p�e�B
@param gp �O���t�B�b�N�v���p�e�B
@param layer �`�惌�C���[
@note
 ���̊֐��ł͉��L�����o�ϐ��𗘗p����̂ŁA�K���l��ݒ肷�邱�ƁB
 ep_->draw_max_div_;
 ep_->grid_x_;
 ep_->grid_y_;
 ep_->interval_time_frame_;
 gp->draw_angle_;
 gp->extend_rate_;
 gp->flag_turn_;
 gp->flag_trans_;
 gp_->graphic_file_
 ���̊֐��ł͉��L�����o�ϐ��͗��p���Ȃ����߁A�l��ݒ肵�Ă����������B
 gp->file_div_;
 gp->int draw_grid_cx_; gp->int draw_grid_cy_;
**/
void NyaEffect::Draw(const EffectProperty1* ep, const GraphicProperty4* gp, eOBJECT::NUM layer)
{
	static list<EffectAnimation1>::iterator it_from, it_to;

	if (ea1_wait_list_.begin() == ea1_wait_list_.end())
		return;
	
	it_from = ea1_wait_list_.begin();
	it_from->count_ = 0;
	*it_from->ep_ = *ep;
	*it_from->gp_ = *gp;
	it_from->gp_->file_div_ = 0;

	it_to = ea1_draw_list_[layer].begin();
	ea1_draw_list_[layer].splice(it_to, move(ea1_wait_list_), it_from);
}

/**
@brief �`�施�߂��o���֐�
@param epx �G�t�F�N�g�v���p�e�B
@param gpx �O���t�B�b�N�v���p�e�B
@note
 ���̊֐��ł͉��L�����o�ϐ��𗘗p����̂ŁA�K���l��ݒ肷�邱�ƁB
 ep->draw_max_div_;
 ep->draw_move_x_;
 ep->draw_move_y_;
 ep->interval_time_frame_;
 ep->grid_x_;
 ep->grid_y_;
 gp->draw_angle_;
 gp->extend_rate_;
 gp->flag_turn_;
 gp->flag_trans_;
 gp->object_group_;
 ���̊֐��ł͉��L�����o�ϐ��͗��p���Ȃ����߁A�l��ݒ肵�Ă����������B
 gp->file_div_;
 gp->int draw_grid_cx_; gp->int draw_grid_cy_;
**/
void NyaEffect::Draw(const EffectProperty2* ep, const GraphicProperty4* gp, eOBJECT::NUM layer)
{
	static list<EffectAnimation2>::iterator it_from, it_to;

	if (ea2_wait_list_.begin() == ea2_wait_list_.end())
		return;
	
	it_from = ea2_wait_list_.begin();
	it_from->count_ = 0;
	*it_from->gp_ = *gp;
	it_from->gp_->file_div_ = 0;
	*it_from->ep_ = *ep;

	it_to = ea2_draw_list_[layer].begin();
	ea2_draw_list_[layer].splice(it_to, move(ea2_wait_list_), it_from);
}

void NyaEffect::Run(void)
{
	for (int layer = eOBJECT::NUM::enum_zero; layer != eOBJECT::NUM::sizeof_enum; layer++)
	{
		DrawAnimation1((eOBJECT::NUM)layer);
		DrawAnimation2((eOBJECT::NUM)layer);
	}
}

void NyaEffect::DrawAnimation1(eOBJECT::NUM layer)
{
	static list<EffectAnimation1>::iterator it, it_delete;
	static deque<list<EffectAnimation1>::iterator> delete_deque;

	// ************
	// �폜����
	// ************
	for (auto it = ea1_draw_list_[layer].begin(); it != ea1_draw_list_[layer].end(); ++it)
	{
		if (it->gp_->file_div_ == it->ep_->draw_div_max_)
			delete_deque.push_back(it);
	}
	while (!delete_deque.empty())
	{
		ea1_wait_list_.splice(ea1_wait_list_.begin(), move(ea1_draw_list_[layer]), delete_deque.front());
		delete_deque.pop_front();
	}

	// ************
	// �`�揈��
	// ************
	for (auto& e : ea1_draw_list_[layer])
	{		
		e.gp_->draw_grid_cx_ = e.ep_->grid_x_;
		e.gp_->draw_grid_cy_ = e.ep_->grid_y_;
		nya_graphic_->Draw(e.gp_, layer);

		e.count_++;
		if (e.count_ == e.ep_->interval_time_frame_)
		{
			e.gp_->file_div_++;
			e.count_ = 0;
		}
	}
}

void NyaEffect::DrawAnimation2(eOBJECT::NUM layer)
{

}

