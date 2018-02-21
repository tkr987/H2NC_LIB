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
@brief ï`âÊñΩóﬂÇèoÇ∑ä÷êî
@param epx ñΩóﬂÇÃÉvÉçÉpÉeÉB
**/
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
	it->phx_->collision_pow_ = 0;
	it->phx_->collision_range_ = 0;
	it->phx_->grid_x_ = epx->grid_x_;
	it->phx_->grid_y_ = epx->grid_y_;
	it->setting_id_ = epx->setting_id_;

	object_group = setting_vector_[it->setting_id_].object_group_;
	draw_list_[object_group].splice(draw_list_[object_group].begin(), move(wait_list_), it);
}

/**
@brief ê›íËÇÉçÅ[ÉhÇ∑ÇÈä÷êî
@param setting ê›íËÇ∑ÇÈíl
@note
 EffectSetting::effect_interval_time_ * EffectSetting::effect_div_max_ Ç™intå^ç≈ëÂílÇí¥Ç¶Ç»Ç¢ÇÊÇ§Ç…íçà”Ç∑ÇÈÇ±Ç∆ÅB
**/
int NyaEffect::LoadSetting(EffectSetting* setting)
{
	int vector_index = 0;

	// ä˘Ç…ìØÇ∂ê›íËÇ™ìoò^Ç≥ÇÍÇƒÇ¢ÇΩÇÁÅAÇªÇÃê›íËIDÇï‘Ç∑
	for (auto& it : setting_vector_) {

		if (it.effect_div_max_ == setting->effect_div_max_ && it.effect_interval_time_ == setting->effect_interval_time_ &&
			it.effect_move_x_ == setting->effect_move_x_ && it.effect_move_y_ == setting->effect_move_y_ &&
			it.graphic_draw_angle_ == setting->graphic_draw_angle_ && it.graphic_draw_extend_ == setting->graphic_draw_extend_ &&
			it.graphic_file_id_ == setting->graphic_file_id_ && it.object_group_ == setting->object_group_) {

			return vector_index;
		}
		vector_index++;
	}

	// ê›íËÇÃêVãKìoò^
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
	list<Effect>::iterator it, it_delete;
	static deque<list<Effect>::iterator> delete_deque;

	///////////////
	// çÌèúèàóù
	///////////////
	for (auto it = draw_list_[group].begin(); it != draw_list_[group].end(); ++it) {

		if (setting_vector_[it->setting_id_].effect_interval_time_ * (setting_vector_[it->setting_id_].effect_div_max_ + 1) == it->count_)
			delete_deque.push_back(it);
	}

	while (!delete_deque.empty()) {
		wait_list_.splice(wait_list_.begin(), move(draw_list_[group]), delete_deque.front());
		delete_deque.pop_front();
	}

	///////////////
	// ï`âÊèàóù
	///////////////
	gpx4.flag_trans_ = true;
	gpx4.flag_turn_ = false;
	for (auto& it : draw_list_[group]) {

		gpx4.draw_angle_ = setting_vector_[it.setting_id_].graphic_draw_angle_;
		gpx4.extend_rate_ = setting_vector_[it.setting_id_].graphic_draw_extend_;
		gpx4.file_div_ = it.count_ / setting_vector_[it.setting_id_].effect_interval_time_;
		gpx4.file_id_ = setting_vector_[it.setting_id_].graphic_file_id_;
		gpx4.object_group_ = setting_vector_[it.setting_id_].object_group_;
		gpx4.pos_cx_ = (int)it.phx_->grid_x_;
		gpx4.pos_cy_ = (int)it.phx_->grid_y_;
		nya_graphic_->Draw(&gpx4);

		it.count_++;
		it.phx_->grid_x_ += setting_vector_[it.setting_id_].effect_move_x_;
		it.phx_->grid_y_ += setting_vector_[it.setting_id_].effect_move_y_;
	}


}

