#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"

using namespace std;
using namespace H2NLIB;

int NyaEffect::count_instance_ = 0;
list<EffectAnimation1> NyaEffect::ea1_draw_list_;
list<EffectAnimation1> NyaEffect::ea1_wait_list_;
list<EffectAnimation2> NyaEffect::ea2_draw_list_;
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
			e.epx1_ = new EffectPropertyX1;
			e.gpx4_ = new GraphicPropertyX4;
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
		for (auto& e : ea1_draw_list_)
		{
			delete e.epx1_;
			delete e.gpx4_;
		}
		for (auto& e : ea1_wait_list_)
		{
			delete e.epx1_;
			delete e.gpx4_;
		}
		for (auto& e : ea2_draw_list_)
		{
			delete e.epx2_;
			delete e.gpx4_;
		}
		for (auto& e : ea2_wait_list_)
		{
			delete e.epx2_;
			delete e.gpx4_;
		}
	}
}


/**
@brief 描画命令を出す関数
@param epx エフェクトプロパティ
@param gpx グラフィックプロパティ
**/
void NyaEffect::Draw(EffectPropertyX1* epx, GraphicPropertyX4* gpx4)
{
	static list<EffectAnimation1>::iterator it;

	if (ea1_wait_list_.begin() == ea1_wait_list_.end())
		return;
	
	it = ea1_wait_list_.begin();
	it->count_ = 0;
	*it->gpx4_ = *gpx4;
	*it->epx1_ = *epx;

	ea1_draw_list_.splice(ea1_draw_list_.begin(), move(ea1_wait_list_), it);
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
void NyaEffect::Draw(EffectPropertyX2* epx, GraphicPropertyX4* gpx4)
{
	static list<EffectAnimation2>::iterator it;

	if (ea2_wait_list_.begin() == ea2_wait_list_.end())
		return;
	
	it = ea2_wait_list_.begin();
	it->count_ = 0;
	*it->gpx4_ = *gpx4;
	it->gpx4_->file_div_ = 0;
	*it->epx2_ = *epx;

	ea2_draw_list_.splice(ea2_draw_list_.begin(), move(ea2_wait_list_), it);
}

void NyaEffect::Run(void)
{
	DrawAnimation1();
	DrawAnimation2();
}

void NyaEffect::DrawAnimation1(void)
{
	static list<EffectAnimation1>::iterator it, it_delete;
	static deque<list<EffectAnimation1>::iterator> delete_deque;

	///////////////
	// 削除処理
	///////////////
	for (auto it = ea1_draw_list_.begin(); it != ea1_draw_list_.end(); ++it)
	{
		if (it->gpx4_->file_div_ == it->epx1_->draw_max_div_)
			delete_deque.push_back(it);
	}
	while (!delete_deque.empty())
	{
		ea1_wait_list_.splice(ea1_wait_list_.begin(), move(ea1_draw_list_), delete_deque.front());
		delete_deque.pop_front();
	}

	///////////////
	// 描画処理
	///////////////
	for (auto& e : ea1_draw_list_)
	{		
		e.gpx4_->draw_grid_cx_ = e.epx1_->grid_x_;
		e.gpx4_->draw_grid_cy_ = e.epx1_->grid_y_;
		nya_graphic_->Draw(e.gpx4_);

		e.count_++;
		if (e.count_ == e.epx1_->interval_time_frame_)
		{
			e.gpx4_->file_div_++;
			e.count_ = 0;
		}
	}
}

void NyaEffect::DrawAnimation2(void)
{

}