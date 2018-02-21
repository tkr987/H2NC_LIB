#include <cmath>
#include <deque>
#include "NyaDevice.h"
#include "NyaEffect.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include "NyaString.h"

using namespace H2NLIB;
using namespace std;

std::vector<DeviceSetting> NyaDevice::setting_vector_;
list<Bullet> NyaDevice::attack_list_[eOBJECT::GROUP::sizeof_enum];
list<Bullet> NyaDevice::wait_list_;


NyaDevice::NyaDevice()
{
	static bool first_call = true;

	nya_effect_ = new NyaEffect;
	nya_position_ = new NyaPosition;
	set_effect_.first = false;
	get<0>(set_graphic_) = false;

	// �e�I�u�W�F�N�g�̍ő����10000��
	if (first_call) {
		wait_list_.resize(10000);
		for (auto& it : wait_list_)
			it.phx_ = nya_position_->Create();
		first_call = false;
	}
}


NyaDevice::~NyaDevice()
{
	delete nya_effect_;
	delete nya_position_;
}

/**
@brief �U���֐�
@param dpx �v���p�e�B
@note
 �e�I�u�W�F�N�g�̍ő����10000�B
**/
void NyaDevice::Attack(DevicePropertyX* dpx)
{
	eOBJECT::GROUP object_group;
	list<Bullet>::iterator it;

	// �e�I�u�W�F�N�g���ő���܂Ő�������Ă���Ƃ��͉������Ȃ�
	if (wait_list_.begin() == wait_list_.end())
		return;
	
	it = wait_list_.begin();
	it->device_setting_id_ = dpx->device_setting_id_;
	it->draw_angle_ = dpx->draw_angle_;
	it->move_angle_  = AngleToRad(dpx->move_angle_);
	it->move_x_ = cos(it->move_angle_) * dpx->move_speed_;
	it->move_y_ = sin(it->move_angle_) * dpx->move_speed_;
	it->phx_->health_max_ = 1.0;
	it->phx_->health_now_ = 1.0;
	it->phx_->grid_x_ = dpx->create_x_;
	it->phx_->grid_y_ = dpx->create_y_;
	it->set_effect_.first = set_effect_.first;
	it->set_effect_.second = set_effect_.second;
	get<0>(it->set_graphic_) = get<0>(set_graphic_);
	get<1>(it->set_graphic_) = get<1>(set_graphic_);
	get<2>(it->set_graphic_) = get<2>(set_graphic_);

	object_group = setting_vector_[it->device_setting_id_].object_group_;
	attack_list_[object_group].splice(attack_list_[object_group].begin(), move(wait_list_), it);
}

void NyaDevice::Run(void)
{
	tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (int group = eOBJECT::GROUP::enum_zero; group != eOBJECT::GROUP::sizeof_enum; group++)
		Calculate((eOBJECT::GROUP)group);


	NyaString::Write("debug_font", white, 50, 190, "[50, 190] attack list size = %d", (int)attack_list_[eOBJECT::GROUP::USER_ATTACK1].size());
	NyaString::Write("debug_font", white, 50, 210, "[50, 210] wait list size = %d", (int)wait_list_.size());
}

void NyaDevice::SetEffect(int effect_setting_id)
{
	set_effect_.first = true;
	set_effect_.second = effect_setting_id;
}

void NyaDevice::SetGraphic(int graphic_file_id, int graphic_file_div)
{
	get<0>(set_graphic_) = true;
	get<1>(set_graphic_) = graphic_file_id;
	get<2>(set_graphic_) = graphic_file_div;
}

int NyaDevice::LoadSetting(DeviceSetting* setting)
{
	setting_vector_.push_back(*setting);

	return ((int)setting_vector_.size() - 1);
}


void NyaDevice::Calculate(eOBJECT::GROUP group)
{
	EffectPropertyX epx;
	GraphicPropertyX4 gpx4;
	static deque<list<Bullet>::iterator> delete_deque;


	///////////////
	// �폜����
	///////////////
	for (auto it = attack_list_[group].begin(); it != attack_list_[group].end(); ++it) {

		// �\���̈�̌��E�𒴂���
		// ���̃I�u�W�F�N�g�ƏՓ˂���Ȃǂ��Ēe�I�u�W�F�N�g�̃w���X���[���ɂȂ���
		if ((int)it->phx_->grid_x_ < 0 || 1000 < (int)it->phx_->grid_x_ ||
			(int)it->phx_->grid_y_ < 0 || 700 < (int)it->phx_->grid_y_) {
		
			delete_deque.push_back(it);

		} else if (it->phx_->health_now_ <= 0) {

			// �G�t�F�N�g�`�揈��
			if (it->set_effect_.first) {
				epx.grid_x_ = (int)it->phx_->grid_x_;
				epx.grid_y_ = (int)it->phx_->grid_y_;
				epx.setting_id_ = it->set_effect_.second;
				nya_effect_->Draw(&epx);
			}

			delete_deque.push_back(it);
		}
	}

	while (!delete_deque.empty()) {
		wait_list_.splice(wait_list_.begin(), move(attack_list_[group]), delete_deque.front());
		delete_deque.pop_front();
	}


	////////////////////
	// �폜�ȊO�̏���
	////////////////////
	gpx4.flag_trans_ = true;
	gpx4.flag_turn_ = false;
	for (auto& it : attack_list_[group]) {

		// �`�揈��
		if (get<0>(it.set_graphic_)) {
			gpx4.draw_angle_ = it.draw_angle_;
			gpx4.draw_angle_ += setting_vector_[it.device_setting_id_].draw_rotate_;
			gpx4.extend_rate_ = setting_vector_[it.device_setting_id_].draw_extend_;
			gpx4.file_div_ = get<2>(it.set_graphic_);
			gpx4.file_id_ = get<1>(it.set_graphic_);
			gpx4.object_group_ = setting_vector_[it.device_setting_id_].object_group_;
			gpx4.pos_cx_ = (int)it.phx_->grid_x_;
			gpx4.pos_cy_ = (int)it.phx_->grid_y_;
			nya_graphic_->Draw(&gpx4);
		}

		// �Փ˔��菈��
		it.phx_->collision_pow_ = setting_vector_[it.device_setting_id_].collision_pow_;
		it.phx_->collision_range_ = setting_vector_[it.device_setting_id_].collision_range_;
		nya_position_->Collision(it.phx_, group);

		// �ړ�����
		it.phx_->grid_x_pre_ = it.phx_->grid_x_;
		it.phx_->grid_y_pre_ = it.phx_->grid_y_;
		it.phx_->grid_x_ += it.move_x_;
		it.phx_->grid_y_ += it.move_y_;
	}
}


