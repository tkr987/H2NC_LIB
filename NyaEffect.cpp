#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"

using namespace std;
using namespace HNLIB;


list<EffectAnimation1> NyaEffect::ea1_draw_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<EffectAnimation1> NyaEffect::ea1_wait_list_;
list<EffectAnimation2> NyaEffect::ea2_draw_list_[static_cast<int>(eOBJECT::sizeof_enum)];
list<EffectAnimation2> NyaEffect::ea2_wait_list_;

EffectPropertyX1::EffectPropertyX1()
{
	interval_time_frame_ = 1;
}

EffectPropertyX2::EffectPropertyX2()
{
	interval_time_frame_ = 1;
	gap_x_ = 0;
	gap_y_ = 0;
}


EffectAnimation1::EffectAnimation1()
{
	count_ = 0;
	epx_ = new EffectPropertyX1;
	gpx_ = new GraphicPropertyX4;
}

EffectAnimation1::~EffectAnimation1()
{
	delete epx_;
	epx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
}

EffectAnimation2::EffectAnimation2()
{
	count_ = 0;
	epx_ = new EffectPropertyX2;
	gpx_ = new GraphicPropertyX4;
}

EffectAnimation2::~EffectAnimation2()
{
	delete epx_;
	epx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
}


/**
@brief 描画関数
@param ep エフェクトプロパティ
@param gp グラフィックプロパティ
@param layer 描画レイヤー
@note
 この関数では下記メンバ変数を利用するので、必ず値を設定すること。
 ep_->draw_max_div_;
 ep_->grid_x_;
 ep_->grid_y_;
 ep_->interval_time_frame_;
 gp->draw_angle_;
 gp->extend_rate_;
 gp->flag_turn_;
 gp->flag_trans_;
 gp_->file_
 この関数では下記メンバ変数は利用しないため、値を設定しても無視される。
 gp->file_div_;
 gp->int draw_grid_cx_; gp->int draw_grid_cy_;
**/
void NyaEffect::Draw(const EffectPropertyX1* epx, const GraphicPropertyX4* gpx, eOBJECT layer)
{
	static list<EffectAnimation1>::iterator it_from, it_to;

	if (ea1_wait_list_.begin() == ea1_wait_list_.end())
		ea1_wait_list_.resize(1);
	
	it_from = ea1_wait_list_.begin();
	it_from->count_ = 0;
	*it_from->epx_ = *epx;
	*it_from->gpx_ = *gpx;
	it_from->gpx_->file_div_ = 0;



	it_to = ea1_draw_list_[static_cast<int>(layer)].begin();
	ea1_draw_list_[static_cast<int>(layer)].splice(it_to, move(ea1_wait_list_), it_from);
}

/**
@brief 描画命令を出す関数
@param epx エフェクトプロパティ
@param gpx グラフィックプロパティ
@note
 この関数では下記メンバ変数を利用するので、必ず値を設定すること。
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
 この関数では下記メンバ変数は利用しないため、値を設定しても無視される。
 gp->file_div_;
 gp->int draw_grid_cx_; gp->int draw_grid_cy_;
**/
void NyaEffect::Draw(const EffectPropertyX2* epx, const GraphicPropertyX4* gpx, eOBJECT layer)
{
	static list<EffectAnimation2>::iterator it_from, it_to;

	if (ea2_wait_list_.begin() == ea2_wait_list_.end())
		ea2_wait_list_.resize(1);
	
	it_from = ea2_wait_list_.begin();
	it_from->count_ = 0;
	*it_from->gpx_ = *gpx;
	it_from->gpx_->file_div_ = 0;
	*it_from->epx_ = *epx;

	it_to = ea2_draw_list_[static_cast<int>(layer)].begin();
	ea2_draw_list_[static_cast<int>(layer)].splice(it_to, move(ea2_wait_list_), it_from);
}

void NyaEffect::Run(eEVENT check_event)
{
	switch(check_event)
	{
	case eEVENT::MISSION_CREATE:
	case eEVENT::MISSION_REPLAY_CREATE:
		for (eOBJECT layer = eOBJECT::enum_zero; layer != eOBJECT::sizeof_enum; ++layer)
		{
			ea1_draw_list_[static_cast<int>(layer)].clear();
			ea1_wait_list_.clear();
			ea2_draw_list_[static_cast<int>(layer)].clear();
			ea2_wait_list_.clear();
		}
		
		break;
	case eEVENT::MISSION_RUN:
	case eEVENT::MISSION_REPLAY_RUN:
		for (eOBJECT layer = eOBJECT::enum_zero; layer != eOBJECT::sizeof_enum; ++layer)
		{
			DrawAnimation1(layer);
			DrawAnimation2(layer);
		}
		break;
	}
}

void NyaEffect::DrawAnimation1(eOBJECT layer)
{
	static list<EffectAnimation1>::iterator it, it_delete;
	static deque<list<EffectAnimation1>::iterator> delete_deque;

	// ************
	// 削除処理
	// ************
	for (auto it = ea1_draw_list_[static_cast<int>(layer)].begin(); it != ea1_draw_list_[static_cast<int>(layer)].end(); ++it)
	{
		if (it->gpx_->file_div_ == it->gpx_->file_.div_total_)
			delete_deque.push_back(it);
	}
	while (!delete_deque.empty())
	{
		ea1_wait_list_.splice(ea1_wait_list_.begin(), move(ea1_draw_list_[static_cast<int>(layer)]), delete_deque.front());
		delete_deque.pop_front();
	}

	// ************
	// 描画処理
	// ************
	for (auto& e : ea1_draw_list_[static_cast<int>(layer)])
	{		
		e.gpx_->draw_grid_cx_ = e.epx_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.epx_->grid_y_;
		NyaGraphic::Draw(e.gpx_, layer);

		e.count_++;
		if (e.count_ == e.epx_->interval_time_frame_)
		{
			e.gpx_->file_div_++;
			e.count_ = 0;
		}
	}
}

void NyaEffect::DrawAnimation2(eOBJECT layer)
{
	static list<EffectAnimation2>::iterator it, it_delete;
	static deque<list<EffectAnimation2>::iterator> delete_deque;

	// ************
	// 削除処理
	// ************
	for (auto it = ea2_draw_list_[static_cast<int>(layer)].begin(); it != ea2_draw_list_[static_cast<int>(layer)].end(); ++it)
	{
		if (it->gpx_->file_div_ == it->gpx_->file_.div_total_)
			delete_deque.push_back(it);
	}
	while (!delete_deque.empty())
	{
		ea2_wait_list_.splice(ea2_wait_list_.begin(), move(ea2_draw_list_[static_cast<int>(layer)]), delete_deque.front());
		delete_deque.pop_front();
	}

	// ************
	// 描画処理
	// ************
	for (auto& e : ea2_draw_list_[static_cast<int>(layer)])
	{		
		e.gpx_->draw_grid_cx_ = *e.epx_->grid_x_ + e.epx_->gap_x_;
		e.gpx_->draw_grid_cy_ = *e.epx_->grid_y_ + e.epx_->gap_y_;
		NyaGraphic::Draw(e.gpx_, layer);

		e.count_++;
		if (e.count_ == e.epx_->interval_time_frame_)
		{
			e.gpx_->file_div_++;
			e.count_ = 0;
		}
	}
}

