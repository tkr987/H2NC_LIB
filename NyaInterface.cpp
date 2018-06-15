#include <limits>
#include <tuple>
#include "DxLib.h"
#include "NyaInterface.h"
#include "NyaInput.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "NyaTarget.h"

#define __DEBUG__

using namespace std;
using namespace H2NLIB;

unsigned int NyaInterface::count_frame_;
InterfaceHandleMissionAllOver NyaInterface::handle_mission_all_over_;
InterfaceHandleMissionClear NyaInterface::handle_mission_clear_;
InterfaceHandleMissionEx NyaInterface::handle_mission_ex_;
InterfaceHandleMissionSkill NyaInterface::handle_mission_skill_;
eSKILL InterfaceHandleMissionSkill::select_;
InterfaceHandleMissionWarning NyaInterface::handle_mission_warning_;

InterfaceHandleMissionAllOver::InterfaceHandleMissionAllOver()
{
	draw_grid_x_ = INTERFACE_MISSION_CLEAR_DEFAULT_DRAW_X;
	draw_grid_y_ = INTERFACE_MISSION_CLEAR_DEFAULT_DRAW_Y;
	valid_ = false;
}

InterfaceHandleMissionClear::InterfaceHandleMissionClear()
{
	draw_grid_x_ = INTERFACE_MISSION_CLEAR_DEFAULT_DRAW_X;
	draw_grid_y_ = INTERFACE_MISSION_CLEAR_DEFAULT_DRAW_Y;
	valid_ = false;
}

InterfaceHandleMissionSkill::InterfaceHandleMissionSkill()
{
	for (int i = 0; i < static_cast<int>(eSKILL::sizeof_enum); i++)
	{
		exp_[i] = 0;
		lv1_exp_[i] = UINT_MAX;
		lv2_exp_[i] = UINT_MAX;
		lv3_exp_[i] = UINT_MAX;
		lv4_exp_[i] = UINT_MAX;
	}
	name_[static_cast<unsigned int>(eSKILL::Q)] = "Skill Q";
	name_[static_cast<unsigned int>(eSKILL::W)] = "Skill W";
	name_[static_cast<unsigned int>(eSKILL::E)] = "Skill E";
	name_[static_cast<unsigned int>(eSKILL::R)] = "Skill R";
	select_ = eSKILL::Q;
}


InterfaceHandleMissionWarning::InterfaceHandleMissionWarning()
{
	draw_grid_x_ = 225;
	draw_grid_y_ = 200;
	draw_frame_ = 0;
	draw_frame_max_ = 300;
	draw_valid_ = false;
	sound_valid_ = false;
	spx_ = new SoundPropertyX;
}

InterfaceHandleMissionWarning::~InterfaceHandleMissionWarning()
{
	draw_grid_x_ = 225;
	draw_grid_y_ = 200;
	draw_frame_ = 0;
	draw_frame_max_ = 300;
	draw_valid_ = false;
	sound_valid_ = false;
	delete spx_;
	spx_ = nullptr;
}


InterfaceHandleMissionEx::InterfaceHandleMissionEx()
{
	valid_ = false;
	value_ = 100;
}

/**
 @brief 初期化関数
 @note
  ライブラリのNyaWindowクラス内で自動的に呼ばれるので、ライブラリ使用者が呼ぶ必要はない
**/
void NyaInterface::Init(void)
{
	count_frame_ = 0;
	NyaString::SettingFont("interface_exp_font", 18, 2);
	NyaString::SettingFont("design_fps_font", 14, 2);
	NyaString::SettingFont("interface_lib_font", 50, 6);
	NyaString::SettingFont("design_mission_clear_big_font", 50, 2);
	NyaString::SettingFont("design_mission_clear_small_font", 30, 2);
	NyaString::SettingFont("design_skill_font", 30, 2);
	NyaString::SettingFont("design_input_font", 50, 2);
	NyaString::SettingFont("design_warning_font", 64, 4);
}

/**
 @brief 実行関数
 @note
  ライブラリのNyaWindowクラス内で自動的に呼ばれるので、ライブラリ使用者が呼ぶ必要はない
**/
void NyaInterface::Run(void)
{
	DrawBlack(850, 0, 1280, 720);
	DrawMissionClear();
	DrawMissionAllOver();
	DrawMissionEx();
	DrawMissionWarning();
	DrawSkill(875, 110);
	DrawLIB(910, 500);
	DrawInput(875, 620);
}

void NyaInterface::DrawBlack(int x, int y, int x2, int y2) 
{
	const int color = GetColor(16, 16, 16);

	DrawBox(x, y, x2, y2, color , true);
}

void NyaInterface::DrawInput(int x, int y)
{
	const tuple<int, int, int> white = make_tuple(255, 255, 255);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);

	// Q, W, E, R, SPACE
	if (NyaInput::GetKeyStateNow(eINPUT::Q))
		NyaString::Write("design_input_font", red, x, y, "■");
	NyaString::Write("design_input_font", white, x, y, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::W))
		NyaString::Write("design_input_font", red, x + 50, y, "■");
	NyaString::Write("design_input_font", white, x + 50, y, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::E))
		NyaString::Write("design_input_font", red, x + 100, y, "■");
	NyaString::Write("design_input_font", white, x + 100, y, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::R))
		NyaString::Write("design_input_font", red, x + 150, y, "■");
	NyaString::Write("design_input_font", white, x + 150, y, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::SPACE))
		NyaString::Write("design_input_font", red, x + 200, y, "■");
	NyaString::Write("design_input_font", white, x + 200, y, "□");
	// up, right, down, left
	if (NyaInput::GetKeyStateNow(eINPUT::UP))
		NyaString::Write("design_input_font", red, x + 275, y -120, "■");
	NyaString::Write("design_input_font", white, x + 275, y - 120, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::RIGHT))
		NyaString::Write("design_input_font", red, x + 325, y - 70, "■");
	NyaString::Write("design_input_font", white, x + 325, y - 70, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::DOWN))
		NyaString::Write("design_input_font", red, x + 275, y - 20, "■");
	NyaString::Write("design_input_font", white, x + 275, y -20, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::LEFT))
		NyaString::Write("design_input_font", red, x + 225, y - 70, "■");
	NyaString::Write("design_input_font", white, x + 225, y - 70, "□");
}

void NyaInterface::DrawLIB(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	NyaString::Write("interface_lib_font", white, x, y, "Happy");
	NyaString::Write("interface_lib_font", white, x, y + 50, "2 Nya");
}

void NyaInterface::DrawMissionAllOver()
{
	int draw_grid_x, draw_grid_y;
	const int black = GetColor(0, 0, 0);
	const tuple<int, int, int> font_color = make_tuple(212, 212, 255);

	if (!handle_mission_all_over_.valid_)
		return;

	draw_grid_x = handle_mission_all_over_.draw_grid_x_;
	draw_grid_y = handle_mission_all_over_.draw_grid_y_;
	DrawBox(draw_grid_x, draw_grid_y, draw_grid_x + 460, draw_grid_y + 150, black, true);
	NyaString::Write("design_mission_clear_big_font", font_color, draw_grid_x + 20, draw_grid_y + 25, "MISSION ALL OVER");
	NyaString::Write("design_mission_clear_small_font", font_color, draw_grid_x + 105, draw_grid_y + 90, "PRESS ENTER KEY");
}

void NyaInterface::DrawMissionClear()
{
	int draw_grid_x, draw_grid_y;
	const int black = GetColor(0, 0, 0);
	const tuple<int, int, int> font_color = make_tuple(212, 212, 255);

	if (!handle_mission_clear_.valid_)
		return;

	draw_grid_x = handle_mission_clear_.draw_grid_x_;
	draw_grid_y = handle_mission_clear_.draw_grid_y_;
	DrawBox(draw_grid_x, draw_grid_y, draw_grid_x + 400, draw_grid_y + 150, black, true);
	NyaString::Write("design_mission_clear_big_font", font_color, draw_grid_x + 40, draw_grid_y + 25, "MISSION CLEAR");
	NyaString::Write("design_mission_clear_small_font", font_color, draw_grid_x + 80, draw_grid_y + 90, "PRESS ENTER KEY");
}

void NyaInterface::DrawMissionEx(void)
{
	const double ex_max_size_x = 840.0;
	const int black = GetColor(0, 0, 0);
	const int red = GetColor(255, 0, 0);

	if (!handle_mission_ex_.valid_)
		return;

	DrawBox(0, 0, 850, 20, black, true);
	DrawBox(5, 4, 5 + (int)(ex_max_size_x * handle_mission_ex_.value_ / 100.0), 15, red, true);
}

void NyaInterface::DrawMissionWarning(void)
{
	int draw_grid_x, draw_grid_y;
	const int black = GetColor(0, 0, 0);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);

	// 効果音再生
	if (handle_mission_warning_.sound_valid_)
	{
		NyaSound::Play(handle_mission_warning_.spx_);
		handle_mission_warning_.sound_valid_ = false;
	}

	// warning表示
	if (handle_mission_warning_.draw_valid_)
	{
		draw_grid_x = handle_mission_warning_.draw_grid_x_;
		draw_grid_y = handle_mission_warning_.draw_grid_y_;
		DrawBox(draw_grid_x, draw_grid_y, draw_grid_x + 400, draw_grid_y + 150, black, true);
		NyaString::Write("design_warning_font", red, draw_grid_x + 90, draw_grid_y + 25, "WARNING");
		handle_mission_warning_.draw_frame_++;

		if (handle_mission_warning_.draw_frame_ == handle_mission_warning_.draw_frame_max_)
		{
			handle_mission_warning_.draw_valid_ = false;
			handle_mission_warning_.draw_frame_max_ = 0;
		}
	}	
}

void NyaInterface::DrawSkill(int x, int y)
{
	const tuple<int, int, int> red = make_tuple(255, 0, 0);
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	// スキル選択肢の表示
	NyaString::Write("design_skill_font", red, x, y + 90 * (static_cast<int>(handle_mission_skill_.select_) - 1), "★");
	for (int skill = static_cast<int>(eSKILL::Q); skill < static_cast<int>(eSKILL::sizeof_enum); skill++)
	{
		NyaString::Write("design_skill_font", white, x, y + 90 * (skill - 1), "☆");
		NyaString::Write("design_skill_font", white, x + 50, y + 90 * (skill - 1), handle_mission_skill_.name_[skill]);
	}
	// スキルのレベルと経験値の表示
	for (int skill = static_cast<int>(eSKILL::Q); skill < static_cast<int>(eSKILL::sizeof_enum); skill++)
	{
		unsigned int exp = handle_mission_skill_.exp_[skill];
		unsigned int lv1_exp = handle_mission_skill_.lv1_exp_[skill];
		unsigned int lv2_exp = handle_mission_skill_.lv2_exp_[skill];
		unsigned int lv3_exp = handle_mission_skill_.lv3_exp_[skill];
		unsigned int lv4_exp = handle_mission_skill_.lv4_exp_[skill];
		NyaString::Write("interface_exp_font", white, x + 150, y + 90 * (skill - 1) + 40, "Exp : %u pt", exp);
		if (exp < lv1_exp)
		{
			NyaString::Write("interface_exp_font", white, x + 150, y + 90 * (skill - 1) + 60, "Next: %u pt", lv1_exp);
		}
		else if (lv1_exp <= exp && exp < lv2_exp)
		{
			NyaString::Write("design_skill_font", red, x, y + 90 * (skill - 1) + 45, "■□□□");
			NyaString::Write("interface_exp_font", white, x + 150, y + 90 * (skill - 1) + 60, "Next: %u pt", lv2_exp);
		}
		else if (lv2_exp <= exp && exp < lv3_exp)
		{
			NyaString::Write("design_skill_font", red, x, y + 90 * (skill - 1) + 45, "■■□□");
			NyaString::Write("interface_exp_font", white, x + 150, y + 90 * (skill - 1) + 60, "Next: %u pt", lv3_exp);
		}
		else if (lv3_exp <= exp && exp < lv4_exp)
		{
			NyaString::Write("design_skill_font", red, x, y + 90 * (skill - 1) + 45, "■■■□");
			NyaString::Write("interface_exp_font", white, x + 150, y + 90 * (skill - 1) + 60, "Next: %u pt", lv4_exp);
		}
		else if (lv4_exp <= exp)
		{
			NyaString::Write("design_skill_font", red, x, y + 90 * (skill - 1) + 45, "■■■■");
			NyaString::Write("interface_exp_font", white, x + 150, y + 90 * (skill - 1) + 60, "Next: %u pt", lv4_exp);
		}
		NyaString::Write("design_skill_font", white, x, y + 90 * (skill - 1) + 45, "□□□□");
	}
}






