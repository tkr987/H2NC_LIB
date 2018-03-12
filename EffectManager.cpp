#include "DefineNH.h"
#include "EffectManager.h"
#include "ImgManager.h"
#include "PosManager.h"


using namespace std;
using namespace NH2;


list<EffectToken> EffectManager::list_unused_;
list<EffectToken> EffectManager::list_used_[eOBJECT::NUM::sizeof_enum];


void EffectManager::Clear(void)
{
	EffectToken temp;

	if (list_unused_.empty()) {
		for (int n = 0; n < EFFECT_TOKEN_MAXSIZE; n++)
			list_unused_.push_back(temp);
	}
}


void EffectManager::End(void) 
{

}

/**
@brief �G�t�F�N�g�����֐�
@param *eparam �p�����[�^�ݒ�
@return ����(1), ���s(-1)
@note
 �p�����[�^ img_divmin_ ���� img_divmax_ - 1 �܂ł̕����摜�� 
 interval �t���[�����ɐ؂�ւ��Ȃ���`�悷�邱�ƂŃG�t�F�N�g������������B
**/
int EffectManager::Create(EffectParam1 *param)
{
	list<EffectToken>::iterator it;

	if (list_unused_.begin() == list_unused_.end())
		return -1;

	it = list_unused_.begin();
	it->draw_type_ = eEFFECT::DRAW::TYPE1;
	it->frames_ = 1;
	it->img_div_ = param->img_divmin_;
	it->img_divmax_ = param->img_divmax_;
	it->img_extend_rate_ = param->extend_rate_;
	it->img_id_ = param->img_id_;
	it->img_interval_ = param->img_interval_;
	it->img_x_ = param->x_;
	it->img_y_ = param->y_;

	list_unused_.splice(list_used_[param->group_].begin(), list_unused_, it);
	return 1;
}


/**
@brief �G�t�F�N�g�����֐�
@param *eparam �p�����[�^�ݒ�
@return ����(1), ���s(-1)
@note
 �p�����[�^ img_divmin_ ���� img_divmax_ - 1 �܂ł̕����摜�� 
 interval �t���[�����ɐ؂�ւ��Ȃ���`�悷�邱�ƂŃG�t�F�N�g������������B
**/
int EffectManager::Create(EffectParam1b *param)
{
	list<EffectToken>::iterator it;

	if (list_unused_.begin() == list_unused_.end())
		return -1;

	it = list_unused_.begin();
	it->draw_type_ = eEFFECT::DRAW::TYPE1B;
	it->frames_ = 1;
	it->img_blend_alpha_ = param->blend_alpha_;
	it->img_blend_mode_ = param->blend_mode_;
	it->img_div_ = param->img_divmin_;
	it->img_divmax_ = param->img_divmax_;
	it->img_extend_rate_ = param->extend_rate_;
	it->img_id_ = param->img_id_;
	it->img_interval_ = param->img_interval_;
	it->img_x_ = param->x_;
	it->img_y_ = param->y_;

	list_unused_.splice(list_used_[param->group_].begin(), list_unused_, it);
	return 1;
}
