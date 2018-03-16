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
		for (auto& it : ea1_wait_list_)
		{
			it.epx1_ = new EffectPropertyX1;
			it.gpx4_ = new GraphicPropertyX4;
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
		for (auto& it : ea1_draw_list_)
		{
			delete it.epx1_;
			delete it.gpx4_;
		}
		for (auto& it : ea1_wait_list_)
		{
			delete it.epx1_;
			delete it.gpx4_;
		}
		for (auto& it : ea2_draw_list_)
		{
			delete it.epx2_;
			delete it.gpx4_;
		}
		for (auto& it : ea2_wait_list_)
		{
			delete it.epx2_;
			delete it.gpx4_;
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
	it->gpx4_ = gpx4;
	it->epx1_ = epx;

	ea1_draw_list_.splice(ea1_draw_list_.begin(), move(ea1_wait_list_), it);
}

/**
@brief 描画命令を出す関数
@param epx エフェクトプロパティ
@param gpx グラフィックプロパティ
**/
void NyaEffect::Draw(EffectPropertyX2* epx, GraphicPropertyX4* gpx4)
{
	static list<EffectAnimation2>::iterator it;

	if (ea2_wait_list_.begin() == ea2_wait_list_.end())
		return;
	
	it = ea2_wait_list_.begin();
	it->count_ = 0;
	it->gpx4_ = gpx4;
	it->epx2_ = epx;

	ea2_draw_list_.splice(ea2_draw_list_.begin(), move(ea2_wait_list_), it);
}

void NyaEffect::Run(void)
{
	DrawAnimation1();
	DrawAnimation2();
}

void NyaEffect::DrawAnimation1(void)
{
	static GraphicPropertyX4 gpx4;
	static list<EffectAnimation1>::iterator it, it_delete;
	static deque<list<EffectAnimation1>::iterator> delete_deque;

	///////////////
	// 削除処理
	///////////////
	for (auto it = ea1_draw_list_.begin(); it != ea1_draw_list_.end(); ++it)
	{
		if (it->epx1_->interval_time_frame_ * it->gpx4_->graphic_file_.div_total_ == it->count_)
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
	gpx4.flag_trans_ = true;
	gpx4.flag_turn_ = false;
	for (auto& it : ea1_draw_list_)
	{		
		gpx4.draw_angle_ = it.gpx4_->draw_angle_;
		gpx4.extend_rate_ = it.gpx4_->extend_rate_;
		gpx4.file_div_ = it.count_ / it.epx1_->interval_time_frame_;
		gpx4.graphic_file_ = it.gpx4_->graphic_file_;
		gpx4.object_group_ = it.gpx4_->object_group_;
		gpx4.pos_cx_ = (int)it.epx1_->grid_x_;
		gpx4.pos_cy_ = (int)it.epx1_->grid_y_;
		nya_graphic_->Draw(&gpx4);

		it.count_++;
	}
}

void NyaEffect::DrawAnimation2(void)
{

}