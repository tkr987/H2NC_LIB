#include <tuple>
#include "DxLib.h"
#include "NyaDesign.h"
#include "NyaInput.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "NyaTarget.h"

#define __DEBUG__

using namespace std;
using namespace H2NLIB;

unsigned int NyaDesign::count_;
DesignHandleMissionClear NyaDesign::handle_mission_clear_;
DesignHandleMissionEx NyaDesign::handle_mission_ex_;
DesignHandleMissionWarning NyaDesign::handle_mission_warning_;
int NyaDesign::instance_ = 0;
DesignSkillInfo NyaDesign::skill_info_[4];
DesignUserInfo NyaDesign::user_info_;

DesignHandleMissionWarning::DesignHandleMissionWarning()
{
	Init();
	sp_ = new SoundProperty;
}

DesignHandleMissionWarning::~DesignHandleMissionWarning()
{
	delete sp_;
}


NyaDesign::NyaDesign()
{
	DesignSkillInfo init_skill_info;

	nya_sound_ = new NyaSound;

	// èâä˙âªÇ∑ÇÈÇÃÇÕ1âÒÇæÇØ
	if (instance_ == 0) {
		count_ = 0;
		instance_ = 0;
		init_skill_info.exp_ = 0;
		init_skill_info.exp_next_[0] = 2147483647;
		init_skill_info.exp_next_[1] = 2147483647;
		init_skill_info.exp_next_[2] = 2147483647;
		init_skill_info.exp_next_[3] = 2147483647;
		init_skill_info.lv_ = 1;
		init_skill_info.name_ = "Skill Q";
		init_skill_info.select_ = true;
		skill_info_[0] = init_skill_info;
		init_skill_info.name_ = "Skill W";
		init_skill_info.select_ = false;
		skill_info_[1] = init_skill_info;
		init_skill_info.name_ = "Skill E";
		init_skill_info.select_ = false;
		skill_info_[2] = init_skill_info;
		init_skill_info.name_ = "Skill R";
		init_skill_info.select_ = false;
		skill_info_[3] = init_skill_info;
		NyaString::SettingFont("design_exp_font", 18, 2);
		NyaString::SettingFont("design_fps_font", 14, 2);
		NyaString::SettingFont("design_lv_font", 60, 6);
		NyaString::SettingFont("design_mission_clear_big_font", 50, 2);
		NyaString::SettingFont("design_mission_clear_small_font", 30, 2);
		NyaString::SettingFont("design_skill_font", 30, 2);
		NyaString::SettingFont("design_input_font", 50, 2);
		NyaString::SettingFont("design_warning_font", 64, 4);
	}

	instance_++;
}


NyaDesign::~NyaDesign()
{
	delete nya_sound_;

	instance_--;
}

void NyaDesign::AddEXP(int x)
{
	user_info_.exp_ += x;
	for (int skill_type = eSKILL::NUM::Q; skill_type != eSKILL::NUM::sizeof_enum; skill_type++)
	{
		if (skill_info_[skill_type].select_)
			skill_info_[skill_type].exp_ += x;
	}
}

void NyaDesign::Init(void)
{
	handle_mission_clear_.Init();
	handle_mission_ex_.Init();
	handle_mission_warning_.Init();
}

void NyaDesign::Run(void)
{
	DrawBlack(850, 0, 1280, 720);
	DrawMissionClear();
	DrawMissionEx();
	DrawMissionWarning();
	DrawSkill(875, 110);
	DrawLv(875, 515);
	DrawInput(875, 600);
}

void NyaDesign::DrawBlack(int x, int y, int x2, int y2) 
{
	const int color = GetColor(16, 16, 16);

	DrawBox(x, y, x2, y2, color , true);
}

void NyaDesign::DrawInput(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);
	static tuple<int, int, int> red = make_tuple(255, 0, 0);

	if (NyaInput::GetKeyStateNow(eINPUT::NUM::Q))
		NyaString::Write("design_input_font", red, x, y, "Å°");
	NyaString::Write("design_input_font", white, x, y, "Å†");
	if (NyaInput::GetKeyStateNow(eINPUT::NUM::W))
		NyaString::Write("design_input_font", red, x + 50, y, "Å°");
	NyaString::Write("design_input_font", white, x + 50, y, "Å†");
	if (NyaInput::GetKeyStateNow(eINPUT::NUM::E))
		NyaString::Write("design_input_font", red, x + 100, y, "Å°");
	NyaString::Write("design_input_font", white, x + 100, y, "Å†");
	if (NyaInput::GetKeyStateNow(eINPUT::NUM::R))
		NyaString::Write("design_input_font", red, x + 150, y, "Å°");
	NyaString::Write("design_input_font", white, x + 150, y, "Å†");
	if (NyaInput::GetKeyStateNow(eINPUT::NUM::SPACE))
		NyaString::Write("design_input_font", red, x + 200, y, "Å°");
	NyaString::Write("design_input_font", white, x + 200, y, "Å†");

	if (NyaInput::GetKeyStateNow(eINPUT::NUM::UP))
		NyaString::Write("design_input_font", red, x + 275, y -120, "Å°");
	NyaString::Write("design_input_font", white, x + 275, y - 120, "Å†");
	if (NyaInput::GetKeyStateNow(eINPUT::NUM::RIGHT))
		NyaString::Write("design_input_font", red, x + 325, y - 70, "Å°");
	NyaString::Write("design_input_font", white, x + 325, y - 70, "Å†");
	if (NyaInput::GetKeyStateNow(eINPUT::NUM::DOWN))
		NyaString::Write("design_input_font", red, x + 275, y - 20, "Å°");
	NyaString::Write("design_input_font", white, x + 275, y -20, "Å†");
	if (NyaInput::GetKeyStateNow(eINPUT::NUM::LEFT))
		NyaString::Write("design_input_font", red, x + 225, y - 70, "Å°");
	NyaString::Write("design_input_font", white, x + 225, y - 70, "Å†");
}

void NyaDesign::DrawLv(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	NyaString::Write("design_lv_font", white, x, y, "Lv.%d", user_info_.lv_);
}

void NyaDesign::DrawMissionClear()
{
	int draw_grid_x, draw_grid_y;
	static int black = GetColor(0, 0, 0);
	static tuple<int, int, int> color = make_tuple(212, 212, 255);

	if (!handle_mission_clear_.valid_)
		return;

	draw_grid_x = handle_mission_clear_.draw_grid_x_;
	draw_grid_y = handle_mission_clear_.draw_grid_y_;
	DrawBox(draw_grid_x, draw_grid_y, draw_grid_x + 400, draw_grid_y + 150, black, true);
	NyaString::Write("design_mission_clear_big_font", color, draw_grid_x + 40, draw_grid_y + 25, "MISSION CLEAR");
	NyaString::Write("design_mission_clear_small_font", color, draw_grid_x + 80, draw_grid_y + 90, "PRESS ENTER KEY");
}

void NyaDesign::DrawMissionEx(void)
{
	const double ex_max_size_x = 840.0;
	const int black = GetColor(0, 0, 0);
	const int red = GetColor(255, 0, 0);

	if (!handle_mission_ex_.valid_)
		return;

	DrawBox(0, 0, 850, 20, black, true);
	DrawBox(5, 4, 5 + (int)(ex_max_size_x * handle_mission_ex_.value_ / 100.0), 15, red, true);
}

void NyaDesign::DrawMissionWarning(void)
{
	int draw_grid_x, draw_grid_y;
	int black = GetColor(0, 0, 0);
	tuple<int, int, int> red = make_tuple(255, 0, 0);

	if (handle_mission_warning_.sound_valid_)
	{
		nya_sound_->Play(handle_mission_warning_.sp_);
		handle_mission_warning_.sound_valid_ = false;
	}

	if (handle_mission_warning_.draw_valid_)
	{
		draw_grid_x = handle_mission_warning_.draw_grid_x_;
		draw_grid_y = handle_mission_warning_.draw_grid_y_;
		DrawBox(draw_grid_x, draw_grid_y, draw_grid_x + 400, draw_grid_y + 150, black, true);
		NyaString::Write("design_warning_font", red, draw_grid_x + 90, draw_grid_y + 25, "WARNING");
		handle_mission_warning_.draw_time_frame_++;

		if (handle_mission_warning_.draw_time_frame_ == handle_mission_warning_.draw_time_max_frame_)
		{
			handle_mission_warning_.draw_valid_ = false;
			handle_mission_warning_.draw_time_frame_ = 0;
		}
	}	
}

void NyaDesign::DrawSkill(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (int i = 0; i < 4; i++) {
		NyaString::Write("design_skill_font", white, x, y + 90 * i, "Åô");
		NyaString::Write("design_skill_font", white, x + 50, y + 90 * i, skill_info_[i].name_);
	}
	for (int i = 0; i < 4; i++) {
		NyaString::Write("design_skill_font", white, x, y + 90 * i + 45, "Å†Å†Å†Å†");
		NyaString::Write("design_exp_font", white, x + 150, y + 90 * i + 40, "Exp : %d pt", skill_info_[i].exp_);
		NyaString::Write("design_exp_font", white, x + 150, y + 90 * i + 60, "Next: %d pt", skill_info_[i].exp_next_[skill_info_[i].lv_]);
	}
}






