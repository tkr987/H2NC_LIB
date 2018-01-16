#include <tuple>
#include "NyaAttack.h"
#include "NyaGraphic.h"
#include "NyaInput.h"
#include "NyaString.h"
#include "TeemoUser.h"

using namespace std;
using namespace H2NLIB;

TeemoUser::TeemoUser()
{
	apx_teemo_ = new AttackPropertyX;
	gpx4_teemo_ = new GraphicPropertyX4;
	ppx_teemo_ = new PositionPropertyX;
	nya_attack_ = new NyaAttack;
	nya_graphic_ = new NyaGraphic;
	nya_input_ = new NyaInput;
	nya_position_ = new NyaPosition;
	nya_string_ = new NyaString;
}


TeemoUser::~TeemoUser()
{
	delete apx_teemo_;
	delete gpx4_teemo_;
	delete ppx_teemo_;
	delete nya_attack_;
	delete nya_graphic_;
	delete nya_input_;
	delete nya_position_;
}


void TeemoUser::Init(void)
{
	gpx4_teemo_->draw_angle_ = 0;
	gpx4_teemo_->extend_rate_ = 1.0;
	gpx4_teemo_->file_div_ = 0;
	gpx4_teemo_->file_id_ = nya_graphic_->LoadFile("teemo.png");
	gpx4_teemo_->flag_trans_ = true;
	gpx4_teemo_->flag_turn_ = false;
	gpx4_teemo_->object_group_ = eOBJECT::GROUP::USER;

	ppx_teemo_->health_max_ = 1;
	ppx_teemo_->health_now_ = 1;
	ppx_teemo_->object_group_ = eOBJECT::GROUP::USER;
	ppx_teemo_->pow_ = 1;
	ppx_teemo_->range_ = 1;
	ppx_teemo_->x_ = 100;
	ppx_teemo_->y_ = 500;

	nya_string_->SetFont("teemo", 10, 2);
}


void TeemoUser::Run(void)
{
	static bool first_call = true;
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	if (first_call) {
		Init();
		first_call = false;
	}

	if (nya_input_->GetKeyFlagNow(eINPUT::KEY::RIGHT)) {
		ppx_teemo_->x_ += 1;
	} else if (nya_input_->GetKeyFlagNow(eINPUT::KEY::LEFT)) {
		ppx_teemo_->x_ -= 1;
	} else if (nya_input_->GetKeyFlagNow(eINPUT::KEY::UP)) {
		ppx_teemo_->y_ -= 1;
	} else if (nya_input_->GetKeyFlagNow(eINPUT::KEY::DOWN)) {
		ppx_teemo_->y_ += 1;
	}
	
	gpx4_teemo_->pos_cx_ = (int)ppx_teemo_->x_;
	gpx4_teemo_->pos_cy_ = (int)ppx_teemo_->y_;
	nya_graphic_->Draw(gpx4_teemo_);

	nya_string_->Write("teemo", white, 300, 300, "teemo x = %d", (int)ppx_teemo_->x_);
	nya_string_->Write("teemo", white, 300, 320, "teemo y = %d", (int)ppx_teemo_->y_);
}

