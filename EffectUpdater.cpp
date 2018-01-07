#include "ImgManager.h"
#include "EffectUpdater.h"
#include "PosManager.h"


using namespace std;
using namespace NH2;
using namespace NH3;


void EffectUpdater::Run(void)
{
	DrawType1(eOBJECT::GROUP::TARGET_EFFECT);
	DrawType1(eOBJECT::GROUP::USER_EFFECT);
	DrawType1(eOBJECT::GROUP::USER_ARMS_EFFECT);
	DrawType1(eOBJECT::GROUP::TARGET_ARMS_EFFECT);
	DrawType2(eOBJECT::GROUP::TARGET_EFFECT);
	DrawType2(eOBJECT::GROUP::USER_EFFECT);
	DrawType2(eOBJECT::GROUP::USER_ARMS_EFFECT);
	DrawType2(eOBJECT::GROUP::TARGET_ARMS_EFFECT);
}


void EffectUpdater::DrawType1(eOBJECT::GROUP group)
{
	ImgParam4 iparam;
	std::list<NH2::EffectToken>::iterator it, sit;

	iparam.draw_angle_ = 0;
	iparam.flag_trans_ = true;
	iparam.flag_turn_ = false;
	iparam.group_type_ = group;
	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		if (it->draw_type_ == eEFFECT::DRAW::TYPE1) {
			iparam.extend_rate_ = it->img_extend_rate_;
			iparam.pos_cx_ = it->img_x_;
			iparam.pos_cy_ = it->img_y_;
			ImgManager::Draw(it->img_id_, it->img_div_, &iparam);
			it->frames_++;
			if (it->frames_ % it->img_interval_ == 0)
				it->img_div_++;
			if (it->img_divmax_ < it->img_div_ || it->frames_ == 5000) {
				sit = --it;
				list_used_[group].splice(list_unused_.begin(), list_used_[group], ++sit);
			}
		}
	}

}

void EffectUpdater::DrawType2(eOBJECT::GROUP group)
{
	ImgParam4b iparam;
	std::list<NH2::EffectToken>::iterator it, sit;

	iparam.draw_angle_ = 0;
	iparam.flag_trans_ = false;
	iparam.flag_turn_ = false;
	iparam.group_type_ = group;
	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		if (it->draw_type_ == eEFFECT::DRAW::TYPE1B) {
			iparam.blend_alpha_ = it->img_blend_alpha_;
			iparam.blend_mode_ = it->img_blend_mode_;
			iparam.extend_rate_ = it->img_extend_rate_;
			iparam.pos_cx_ = it->img_x_;
			iparam.pos_cy_ = it->img_y_;
			ImgManager::Draw(it->img_id_, it->img_div_, &iparam);
			it->frames_++;
			if (it->frames_ % it->img_interval_ == 0)
				it->img_div_++;
			if (it->img_divmax_ < it->img_div_ || it->frames_ == 5000) {
				sit = --it;
				list_used_[group].splice(list_unused_.begin(), list_used_[group], ++sit);
			}
		}
	}

}


