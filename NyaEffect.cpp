#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"

using namespace std;
using namespace H2NLIB;

list<Animation> NyaEffect::draw_list_[eOBJECT::GROUP::sizeof_enum];
list<Animation> NyaEffect::wait_list_;
std::vector<EffectOption> NyaEffect::option_vector_;

NyaEffect::NyaEffect()
{
	EffectOption default_option;
	static bool first_call = true;

	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;

	if (first_call)
	{
		NewOption(&default_option);
		wait_list_.resize(10000);
		for (auto& it : wait_list_)
			it.phx_ = nya_position_->Create();
		first_call = false;
	}
}


NyaEffect::~NyaEffect()
{
	delete nya_graphic_;
	delete nya_position_;
}

/**
@brief 描画命令を出す関数
@param epx プロパティ
@param option オプション
**/
void NyaEffect::Draw(EffectPropertyX* epx, int option_index)
{
	static GraphicPropertyX4 gpx4;
	static list<Animation>::iterator it;

	if (wait_list_.begin() == wait_list_.end())
		return;
	
	it = wait_list_.begin();
	it->count_ = 0;
	it->div_max_ = epx->animation_div_max_;
	it->file_id_ = epx->file_id_;
	it->interval_time_ = epx->animation_interval_time_;
	it->option_index_ = option_index;
	it->phx_->health_max_ = 1;
	it->phx_->health_now_ = 1;
	it->phx_->collision_pow_ = 0;
	it->phx_->collision_range_ = 0;
	it->phx_->grid_x_ = epx->grid_x_;
	it->phx_->grid_y_ = epx->grid_y_;

	draw_list_[epx->object_group_].splice(draw_list_[epx->object_group_].begin(), move(wait_list_), it);
}

int NyaEffect::LoadFile(int div_x, int div_y, string file_pass) 
{
	return nya_graphic_->LoadFile(div_x, div_y, file_pass);
}


/**
@brief オプション項目の設定をする関数
@param setting 設定する値
@note
 EffectSetting::effect_interval_time_ * EffectSetting::effect_div_max_ がint型最大値を超えないように注意すること。
**/
int NyaEffect::NewOption(EffectOption* option)
{
	int vector_index = 0;

	// 既に同じ設定が登録されていたら、その設定IDを返す
	for (auto& it : option_vector_)
	{
		if (it.draw_angle_ == option->draw_angle_ && it.draw_extend_ == option->draw_extend_ &&
			it.draw_move_x_ == option->draw_move_x_ && it.draw_move_y_ == option->draw_move_y_)
		{
			return vector_index;
		}
		vector_index++;
	}

	// 設定の新規登録
	option_vector_.push_back(*option);

	return ((int)option_vector_.size() - 1);
}

void NyaEffect::Run(void)
{
	for (int group = eOBJECT::GROUP::enum_zero; group != eOBJECT::GROUP::sizeof_enum; group++)
		DrawAll((eOBJECT::GROUP)group);

}

void NyaEffect::DrawAll(eOBJECT::GROUP group)
{
	GraphicPropertyX4 gpx4;
	list<Animation>::iterator it, it_delete;
	static deque<list<Animation>::iterator> delete_deque;

	///////////////
	// 削除処理
	///////////////
	for (auto it = draw_list_[group].begin(); it != draw_list_[group].end(); ++it)
	{
		if (it->interval_time_ * it->div_max_ == it->count_)
			delete_deque.push_back(it);
	}

	while (!delete_deque.empty())
	{
		wait_list_.splice(wait_list_.begin(), move(draw_list_[group]), delete_deque.front());
		delete_deque.pop_front();
	}

	///////////////
	// 描画処理
	///////////////
	gpx4.flag_trans_ = true;
	gpx4.flag_turn_ = false;
	for (auto& it : draw_list_[group])
	{
		gpx4.draw_angle_ = option_vector_[it.option_index_].draw_angle_;
		gpx4.extend_rate_ = option_vector_[it.option_index_].draw_extend_;
		gpx4.file_div_ = it.count_ / it.interval_time_;
		gpx4.file_id_ = it.file_id_;
		gpx4.object_group_ = group;
		gpx4.pos_cx_ = (int)it.phx_->grid_x_;
		gpx4.pos_cy_ = (int)it.phx_->grid_y_;
		nya_graphic_->Draw(&gpx4);

		it.count_++;
		it.phx_->grid_x_ += option_vector_[it.option_index_].draw_move_x_;
		it.phx_->grid_y_ += option_vector_[it.option_index_].draw_move_y_;
	}


}

