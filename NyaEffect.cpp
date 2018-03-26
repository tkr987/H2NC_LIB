#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"

using namespace std;
using namespace H2NLIB;

int NyaEffect::count_instance_ = 0;
list<EffectAnimation1> NyaEffect::ea1_draw_list_[eOBJECT::NUM::sizeof_enum];
list<EffectAnimation1> NyaEffect::ea1_wait_list_;
list<EffectAnimation2> NyaEffect::ea2_draw_list_[eOBJECT::NUM::sizeof_enum];
list<EffectAnimation2> NyaEffect::ea2_wait_list_;

NyaEffect::NyaEffect()
{

	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;

	if (count_instance_ == 0)
	{
		ea1_wait_list_.resize(10000);
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
@brief 描画命令を出す関数
@param epx エフェクトプロパティ
@param gpx グラフィックプロパティ
**/
void NyaEffect::Draw(EffectProperty1* epx, GraphicProperty4* gpx4, eOBJECT::NUM layer)
{
	static list<EffectAnimation1>::iterator it_from, it_to;

	if (ea1_wait_list_.begin() == ea1_wait_list_.end())
		return;
	
	it_from = ea1_wait_list_.begin();
	it_from->count_ = 0;
	*it_from->gp_ = *gpx4;
	*it_from->ep_ = *epx;

	it_to = ea1_draw_list_[layer].begin();
	ea1_draw_list_[layer].splice(it_to, move(ea1_wait_list_), it_from);
}

/**
@brief 描画命令を出す関数
@param epx エフェクトプロパティ
@param gpx グラフィックプロパティ
@note
 この関数では下記メンバ変数を利用するので、必ず値を設定すること。
 epx->draw_max_div_;
 epx->draw_move_x_;
 epx->draw_move_y_;
 epx->interval_time_frame_;
 epx->grid_x_;
 epx->grid_y_;
 gpx4->draw_angle_;
 gpx4->extend_rate_;
 gpx4->flag_turn_;
 gpx4->flag_trans_;
 gpx4->object_group_;
 この関数では下記メンバ変数は利用しないため、値を設定しても無視される。
 gpx4->file_div_;
 gpx4->int draw_grid_cx_; gpx4->int draw_grid_cy_;
**/
void NyaEffect::Draw(EffectProperty2* epx, GraphicProperty4* gpx4, eOBJECT::NUM layer)
{
	static list<EffectAnimation2>::iterator it_from, it_to;

	if (ea2_wait_list_.begin() == ea2_wait_list_.end())
		return;
	
	it_from = ea2_wait_list_.begin();
	it_from->count_ = 0;
	*it_from->gp_ = *gpx4;
	it_from->gp_->file_div_ = 0;
	*it_from->ep_ = *epx;

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

	///////////////
	// 削除処理
	///////////////
	for (auto it = ea1_draw_list_[layer].begin(); it != ea1_draw_list_[layer].end(); ++it)
	{
		if (it->gp_->file_div_ == it->ep_->draw_max_div_)
			delete_deque.push_back(it);
	}
	while (!delete_deque.empty())
	{
		ea1_wait_list_.splice(ea1_wait_list_.begin(), move(ea1_draw_list_[layer]), delete_deque.front());
		delete_deque.pop_front();
	}

	///////////////
	// 描画処理
	///////////////
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

