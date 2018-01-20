#include <tuple>
#include "NyaAttack.h"
#include "NyaDefine.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaPosition.h"
#include "NyaString.h"
#include "TeemoUser.h"

using namespace std;
using namespace H2NLIB;

TeemoUser::TeemoUser()
{
	count_ = 0;
	apx_teemo_ = new AttackPropertyX;
	gpx4_teemo_ = new GraphicPropertyX4;
	ppx_teemo_ = new PositionPropertyX;
	nya_attack_ = new NyaAttack;
	nya_graphic_ = new NyaGraphic;
	nya_position_ = new NyaPosition;


	apx_teemo_->collision_pow_ = 1;
	apx_teemo_->collision_range_ = 1;
	apx_teemo_->graphic_angle_ = 0;
	apx_teemo_->graphic_rotate_ = 0;
	apx_teemo_->move_angle_ = 0;
	apx_teemo_->move_speed_ = 2;
	nya_attack_->SettingGraphic(nya_graphic_->LoadFile("attack.png"), 0);
	nya_attack_->SettingGroup(eOBJECT::GROUP::USER_ATTACK1);

	gpx4_teemo_->draw_angle_ = 0;
	gpx4_teemo_->extend_rate_ = 1.0;
	gpx4_teemo_->file_div_ = 0;
	gpx4_teemo_->file_id_ = nya_graphic_->LoadFile("teemo.png");
	gpx4_teemo_->flag_trans_ = true;
	gpx4_teemo_->flag_turn_ = false;
	gpx4_teemo_->object_group_ = eOBJECT::GROUP::USER1;

	ppx_teemo_->health_max_ = 1;
	ppx_teemo_->health_now_ = 1;
	ppx_teemo_->object_group_ = eOBJECT::GROUP::USER1;
	ppx_teemo_->pow_ = 1;
	ppx_teemo_->range_ = 1;
	ppx_teemo_->x_ = 100;
	ppx_teemo_->y_ = 500;

	NyaString::SettingFont("teemo", 10, 2);
}


TeemoUser::~TeemoUser()
{
	delete apx_teemo_;
	delete gpx4_teemo_;
	delete ppx_teemo_;
	delete nya_attack_;
	delete nya_graphic_;
	delete nya_position_;
}


void TeemoUser::Init(void)
{
	apx_teemo_->collision_pow_ = 1;
	apx_teemo_->collision_range_ = 1;
	apx_teemo_->graphic_angle_ = 0;
	apx_teemo_->graphic_rotate_ = 0;
	apx_teemo_->move_angle_ = 0;
	apx_teemo_->move_speed_ = 2;
	nya_attack_->SettingGraphic(nya_graphic_->LoadFile("attack.png"), 0);
	nya_attack_->SettingGroup(eOBJECT::GROUP::USER_ATTACK1);

	gpx4_teemo_->draw_angle_ = 0;
	gpx4_teemo_->extend_rate_ = 1.0;
	gpx4_teemo_->file_div_ = 0;
	gpx4_teemo_->file_id_ = nya_graphic_->LoadFile("teemo.png");
	gpx4_teemo_->flag_trans_ = true;
	gpx4_teemo_->flag_turn_ = false;
	gpx4_teemo_->object_group_ = eOBJECT::GROUP::USER1;

	ppx_teemo_->health_max_ = 1;
	ppx_teemo_->health_now_ = 1;
	ppx_teemo_->object_group_ = eOBJECT::GROUP::USER1;
	ppx_teemo_->pow_ = 1;
	ppx_teemo_->range_ = 1;
	ppx_teemo_->x_ = 100;
	ppx_teemo_->y_ = 500;

	NyaString::SettingFont("teemo", 10, 2);
}


void TeemoUser::Action(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::RIGHT)) {
		ppx_teemo_->x_ += 5;
	} else if (NyaInput::GetKeyFlagNow(eINPUT::KEY::LEFT)) {
		ppx_teemo_->x_ -= 5;
	} else if (NyaInput::GetKeyFlagNow(eINPUT::KEY::UP)) {
		ppx_teemo_->y_ -= 5;
	} else if (NyaInput::GetKeyFlagNow(eINPUT::KEY::DOWN)) {
		ppx_teemo_->y_ += 5;
	}

	NyaString::Write("teemo", white, 300, 300, "teemo x = %d", (int)ppx_teemo_->x_);
	NyaString::Write("teemo", white, 300, 320, "teemo y = %d", (int)ppx_teemo_->y_);

	if (NyaInput::GetKeyFlagNow(eINPUT::KEY::Q) == true && count_ % 10 == 0) {
		apx_teemo_->create_x_ = ppx_teemo_->x_;
		apx_teemo_->create_y_ = ppx_teemo_->y_;
		nya_attack_->Create(apx_teemo_);
	}

	count_++;
}

void TeemoUser::Draw(void)
{
	gpx4_teemo_->pos_cx_ = (int)ppx_teemo_->x_;
	gpx4_teemo_->pos_cy_ = (int)ppx_teemo_->y_;
	nya_graphic_->Draw(gpx4_teemo_);
}

