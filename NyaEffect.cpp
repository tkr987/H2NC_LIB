#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"

using namespace std;
using namespace H2NLIB;

list<Effect> NyaEffect::draw_list_[eOBJECT::GROUP::sizeof_enum];
list<Effect> NyaEffect::wait_list_;
std::vector<EffectSetting> NyaEffect::setting_vector_;

NyaEffect::NyaEffect()
{
	static bool first_call = true;

	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;
	if (first_call) {
		wait_list_.resize(10000);
		for (auto it = wait_list_.begin(); it != wait_list_.end(); ++it) {
			it->phx_ = nya_position_->Create();
		}
		first_call = false;
	}
}


NyaEffect::~NyaEffect()
{
	delete nya_graphic_;
	delete nya_position_;
}


void NyaEffect::Draw(EffectPropertyX* epx)
{
	static GraphicPropertyX4 gpx4;

	eOBJECT::GROUP object_group;
	list<Effect>::iterator it;

	if (wait_list_.begin() == wait_list_.end())
		return;
	
	it = wait_list_.begin();
	it->count_ = 0;
	it->phx_->health_max_ = 1;
	it->phx_->health_now_ = 1;
	it->phx_->pow_ = 0;
	it->phx_->range_ = 0;
	it->phx_->x_ = epx->pos_x_;
	it->phx_->y_ = epx->pos_y_;
	it->setting_id_ = epx->setting_id_;

	object_group = setting_vector_[epx->setting_id_].object_group_;
	wait_list_.splice(draw_list_[object_group].begin(), wait_list_, it);
}

/**
@brief 設定ロード関数
@param setting 設定する値
@note
 EffectSetting::effect_interval_time_ * EffectSetting::effect_div_max_ がint型最大値を超えないように注意すること。
**/
int NyaEffect::LoadSetting(EffectSetting* setting)
{
	setting_vector_.push_back(*setting);

	return ((int)setting_vector_.size() - 1);
}

void NyaEffect::Run(void)
{
	for (int group = eOBJECT::GROUP::enum_zero; group != eOBJECT::GROUP::sizeof_enum; group++)
		DrawAll((eOBJECT::GROUP)group);

}

void NyaEffect::DrawAll(eOBJECT::GROUP group)
{
	GraphicPropertyX4 gpx4;
	list<Effect>::iterator it_delete;

	// 削除処理
	for (list<Effect>::iterator it = draw_list_[group].begin(); it != draw_list_[group].end(); ++it) {

		if (setting_vector_[it->setting_id_].effect_interval_time_ * (setting_vector_[it->setting_id_].effect_div_max_ + 1) == it->count_) {
			it_delete = --it;
			draw_list_[group].splice(wait_list_.begin(), draw_list_[group], ++it_delete);
		}
	}

	gpx4.flag_trans_ = true;
	gpx4.flag_turn_ = false;
	for (list<Effect>::iterator it = draw_list_[group].begin(); it != draw_list_[group].end(); ++it) {

		gpx4.draw_angle_ = setting_vector_[it->setting_id_].graphic_draw_angle_;
		gpx4.extend_rate_ = setting_vector_[it->setting_id_].graphic_draw_extend_;
		gpx4.file_div_ = it->count_ / setting_vector_[it->setting_id_].effect_interval_time_;
		gpx4.file_id_ = setting_vector_[it->setting_id_].graphic_file_id_;
		gpx4.object_group_ = setting_vector_[it->setting_id_].object_group_;
		gpx4.pos_cx_ = (int)it->phx_->x_;
		gpx4.pos_cy_ = (int)it->phx_->y_;
		nya_graphic_->Draw(&gpx4);
		it->count_++;
		it->phx_->x_ += setting_vector_[it->setting_id_].effect_move_x_;
		it->phx_->y_ += setting_vector_[it->setting_id_].effect_move_y_;
	}


}

