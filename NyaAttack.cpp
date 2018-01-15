#include <cmath>
#include "NyaAttack.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"


using namespace H2NLIB;
using namespace std;


list<Bullet> NyaAttack::create_list_[eOBJECT::GROUP::sizeof_enum];
list<Bullet> NyaAttack::wait_list_;


NyaAttack::NyaAttack()
{

}


NyaAttack::~NyaAttack()
{

}

void NyaAttack::Create(AttackPropertyX* apx)
{
	list<Bullet>::iterator it;

	if (wait_list_.begin() == wait_list_.end())
		return;
	
	it = wait_list_.begin();
	it->gpx4_.draw_angle_ = apx->graphic_angle_;
	it->move_angle_  = AngleToRad(apx->move_angle_);
	it->move_x_ = cos(AngleToRad(apx->move_angle_)) * apx->move_speed_;
	it->move_x_ = sin(AngleToRad(apx->move_angle_)) * apx->move_speed_;
	it->ppx_.x_ = apx->create_x_;
	it->ppx_.y_ = apx->create_y_;

	wait_list_.splice(create_list_[it->ppx_.object_group_].begin(), wait_list_, it);
}


void NyaAttack::Init(int size)
{
	wait_list_.resize(size);
	for (auto it = wait_list_.begin(); it != wait_list_.end(); ++it) {
		it->ppx_.health_max_ = 1;
		it->ppx_.health_now_ = 1;
	}
}

void NyaAttack::Run(void)
{


}

void NyaAttack::SettingBullet(eOBJECT::GROUP object_group, double pow, double range)
{
	for (auto it = wait_list_.begin(); it != wait_list_.end(); ++it) {
		it->ppx_.object_group_ = object_group;
		it->ppx_.pow_ = pow;
		it->ppx_.range_ = range;
	}
}

void NyaAttack::SettingEffect(void)
{


}

void NyaAttack::SettingGraphic(eOBJECT::GROUP object_group, int id, int div)
{
	for (auto it = wait_list_.begin(); it != wait_list_.end(); ++it) {
		it->gpx4_.extend_rate_ = 1.0;
		it->gpx4_.file_div_ = div;
		it->gpx4_.file_id_ = id;
		it->gpx4_.flag_trans_ = true;
		it->gpx4_.flag_turn_ = false;
		it->gpx4_.object_group_ = object_group;
	}
}

