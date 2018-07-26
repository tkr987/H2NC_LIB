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
using namespace HNLIB;

InterfaceHandleClear NyaInterface::handle_clear_;
InterfaceHandleComplete NyaInterface::handle_complete_;
InterfaceHandleContinue	NyaInterface::handle_continue_;
InterfaceHandleEnd NyaInterface::handle_end_;
InterfaceHandleHealth NyaInterface::handle_health_;
InterfaceHandleLife NyaInterface::handle_life_;
InterfaceHandleSkill NyaInterface::handle_skill_;
InterfaceHandleTitle NyaInterface::handle_title_;
InterfaceHandleWarning NyaInterface::handle_warning_;



void InterfaceHandleClear::Clear()
{
	valid_ = false;
}


void InterfaceHandleComplete::Clear()
{
	valid_ = false;
}

void InterfaceHandleContinue::Clear()
{
	cnum_ = 0;
	recovery_ = 1;
	select_ = 0;
	valid_ = false;
}

void InterfaceHandleEnd::Clear()
{
	valid_ = false;
}


void InterfaceHandleHealth::Clear()
{
	valid_ = false;
	value_ = 100;
}

void InterfaceHandleLife::Clear()
{
	value_ = 1;
}

void InterfaceHandleSkill::AddExp(unsigned int value)
{
	exp_[static_cast<int>(select_)] += value;
}

void InterfaceHandleSkill::Clear(void)
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

void InterfaceHandleWarning::Clear(void)
{
	draw_frame_ = 0;
	draw_frame_max_ = FPS_MAX * 4;
	valid_ = false;
}

/**
 @brief 初期化関数
 @note
  ライブラリのNyaWindowクラス内で自動的に呼ばれるので、ライブラリ使用者が呼ぶ必要はない
**/
void NyaInterface::Init(void)
{
	handle_complete_.Clear();
	handle_continue_.Clear();
	handle_end_.Clear();
	handle_health_.Clear();
	handle_life_.Clear();
	handle_skill_.Clear();
	handle_warning_.Clear();

	NyaString::SettingFont("interface_continue_font", 40, 6);
	NyaString::SettingFont("interface_clear_big_font", 50, 2);
	NyaString::SettingFont("interface_clear_small_font", 30, 2);
	NyaString::SettingFont("interface_complete_big_font", 50, 2);
	NyaString::SettingFont("interface_complete_small_font", 30, 2);
	NyaString::SettingFont("interface_end_big_font", 50, 2);
	NyaString::SettingFont("interface_end_small_font", 30, 2);
	NyaString::SettingFont("interface_lib_font", 50, 6);
	NyaString::SettingFont("interface_life_font", 30, 2);
	NyaString::SettingFont("interface_skill_font", 30, 2);
	NyaString::SettingFont("interface_skill_exp_font", 18, 2);
	NyaString::SettingFont("interface_title_font", 20, 6);
	NyaString::SettingFont("interface_input_font", 50, 2);
	NyaString::SettingFont("interface_warning_font", 64, 4);
}

/**
 @brief 実行関数
 @note
  ライブラリのNyaWindowクラス内で自動的に呼ばれるので、ライブラリ使用者が呼ぶ必要はない
**/
void NyaInterface::Run(eEVENT event_check)
{
	DrawBlack(850, 0, 1280, 720);
	DrawTitle(875, 35);
	DrawLife(875, 75);
	DrawSkill(875, 135);
	DrawLIB(910, 520);
	DrawInput(875, 640);

	DrawClear(225, 200);
	DrawComplete(225, 200);
	DrawContinue(220, 200, event_check);
	DrawEnd(225, 200);
	DrawHealth();
	DrawWarning(225, 200);
}

void NyaInterface::DrawBlack(int x, int y, int x2, int y2) 
{
	const int color = GetColor(16, 16, 16);

	DrawBox(x, y, x2, y2, color , true);
}

void NyaInterface::DrawClear(int x, int y)
{
	const int black = GetColor(0, 0, 0);
	const tuple<int, int, int> font_color = make_tuple(212, 212, 255);

	if (!handle_clear_.valid_)
		return;

	DrawBox(x, y, x + 400, y + 150, black, true);
	NyaString::Write("interface_clear_big_font", font_color, x + 40, y + 25, "MISSION CLEAR");
	NyaString::Write("interface_clear_small_font", font_color, x + 80, y + 90, "PRESS ENTER KEY");

	if (NyaInput::IsPressKey(eINPUT::ENTER))
		handle_clear_.valid_ = false;
}

void NyaInterface::DrawComplete(int x, int y)
{
	const int black = GetColor(0, 0, 0);
	const tuple<int, int, int> font_color = make_tuple(212, 212, 255);

	if (!handle_complete_.valid_)
		return;

	DrawBox(x, y, x + 460, y + 150, black, true);
	NyaString::Write("interface_complete_big_font", font_color, x + 20, y + 25, "MISSION COMPLETE");
	NyaString::Write("interface_complete_small_font", font_color, x + 105, y + 90, "PRESS ENTER KEY");

	if (NyaInput::IsPressKey(eINPUT::ENTER))
		handle_complete_.valid_ = false;
}

void NyaInterface::DrawContinue(int x, int y, eEVENT event_check)
{
	const int black = GetColor(0, 0, 0);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	if (!handle_continue_.valid_)
		return;

	if (event_check != eEVENT::MISSION_RUN && event_check != eEVENT::MISSION_CONTINUE)
		return;

	DrawBox(x, y, x + 400, y + 200, black, true);

	if (handle_continue_.select_ == 0)
		NyaString::Write("interface_continue_font", red, x + 20, y + 80, "★");
	if (handle_continue_.select_ == 1)
		NyaString::Write("interface_continue_font", red, x + 20, y + 130, "★");

	if (NyaInput::IsPressKey(eINPUT::UP) || NyaInput::IsPressKey(eINPUT::DOWN))
		handle_continue_.select_ = ++handle_continue_.select_ % 2;

	NyaString::Write("interface_continue_font", white, x + 100, y + 20, "continue?");
	NyaString::Write("interface_continue_font", white, x + 20, y + 80, "☆　yes");
	NyaString::Write("interface_continue_font", white, x + 20, y + 130, "☆　no");

	if (NyaInput::IsPressKey(eINPUT::ENTER))
	{
		if (handle_continue_.select_ == 0)
			handle_continue_.cnum_++;
		handle_continue_.valid_ = false;
		handle_life_.value_ = handle_continue_.recovery_;
	}
}

void NyaInterface::DrawEnd(int x, int y)
{
	const int black = GetColor(0, 0, 0);
	const tuple<int, int, int> white = make_tuple(212, 212, 255);

	if (!handle_end_.valid_)
		return;

	DrawBox(x, y, x + 400, y + 150, black, true);
	NyaString::Write("interface_end_big_font", white, x + 75, y + 25, "REPLAY END");
	NyaString::Write("interface_end_small_font", white, x + 85, y + 90, "PRESS ENTER KEY");

	if (NyaInput::IsPressKey(eINPUT::ENTER))
		handle_end_.valid_ = false;
}

void NyaInterface::DrawInput(int x, int y)
{
	const tuple<int, int, int> white = make_tuple(255, 255, 255);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);

	// Q, W, E, R, SPACE
	if (NyaInput::GetKeyStateNow(eINPUT::Q))
		NyaString::Write("interface_input_font", red, x, y, "■");
	NyaString::Write("interface_input_font", white, x, y, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::W))
		NyaString::Write("interface_input_font", red, x + 50, y, "■");
	NyaString::Write("interface_input_font", white, x + 50, y, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::E))
		NyaString::Write("interface_input_font", red, x + 100, y, "■");
	NyaString::Write("interface_input_font", white, x + 100, y, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::R))
		NyaString::Write("interface_input_font", red, x + 150, y, "■");
	NyaString::Write("interface_input_font", white, x + 150, y, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::SPACE))
		NyaString::Write("interface_input_font", red, x + 200, y, "■");
	NyaString::Write("interface_input_font", white, x + 200, y, "□");
	// up, right, down, left
	if (NyaInput::GetKeyStateNow(eINPUT::UP))
		NyaString::Write("interface_input_font", red, x + 275, y -120, "■");
	NyaString::Write("interface_input_font", white, x + 275, y - 120, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::RIGHT))
		NyaString::Write("interface_input_font", red, x + 325, y - 70, "■");
	NyaString::Write("interface_input_font", white, x + 325, y - 70, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::DOWN))
		NyaString::Write("interface_input_font", red, x + 275, y - 20, "■");
	NyaString::Write("interface_input_font", white, x + 275, y -20, "□");
	if (NyaInput::GetKeyStateNow(eINPUT::LEFT))
		NyaString::Write("interface_input_font", red, x + 225, y - 70, "■");
	NyaString::Write("interface_input_font", white, x + 225, y - 70, "□");
}

void NyaInterface::DrawLIB(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	NyaString::Write("interface_lib_font", white, x, y, "Happy");
	NyaString::Write("interface_lib_font", white, x, y + 50, "2 Nya");
}

/**
@brief ヘルス表示関数
@note
 handle_health_.value_の値を%として処理する
 0以下の値が指定されたときは0%として処理する
 100以上の値が指定されたときは100%として処理する
**/
void NyaInterface::DrawHealth(void)
{
	const double ex_max_size_x = 840.0;
	const int black = GetColor(0, 0, 0);
	const int red = GetColor(255, 0, 0);

	if (!handle_health_.valid_)
		return;

	handle_health_.value_ = (handle_health_.value_ <= 0) ? 0 : (100 <= handle_health_.value_) ? 100 : handle_health_.value_;
	DrawBox(0, 0, 850, 20, black, true);
	DrawBox(5, 4, 5 + (int)(ex_max_size_x * handle_health_.value_ / 100.0), 15, red, true);
}

void NyaInterface::DrawLife(int x, int y)
{
	int value_grid_x = x + 90;
	const tuple<int, int, int> red = make_tuple(255, 0, 0);
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	// 範囲外のライフ数が設定されていたら値を範囲内に収める
	if (handle_life_.value_ < 0)
		handle_life_.value_ = 0;
	if (9 <= handle_life_.value_)
		handle_life_.value_ = 8;

	// ライフ描画
	NyaString::Write("interface_life_font", white, x, y, "user:");

	if      (handle_life_.value_ == 1)
		NyaString::Write("interface_life_font", red, value_grid_x, y, "■□□□□□□□");
	else if (handle_life_.value_ == 2)
		NyaString::Write("interface_life_font", red, value_grid_x, y, "■■□□□□□□");
	else if (handle_life_.value_ == 3)
		NyaString::Write("interface_life_font", red, value_grid_x, y, "■■■□□□□□");
	else if (handle_life_.value_ == 4)
		NyaString::Write("interface_life_font", red, value_grid_x, y, "■■■■□□□□");
	else if (handle_life_.value_ == 5)
		NyaString::Write("interface_life_font", red, value_grid_x, y, "■■■■■□□□");
	else if (handle_life_.value_ == 6)
		NyaString::Write("interface_life_font", red, value_grid_x, y, "■■■■■■□□");
	else if (handle_life_.value_ == 7)
		NyaString::Write("interface_life_font", red, value_grid_x, y, "■■■■■■■□");
	else if (8 <= handle_life_.value_)
		NyaString::Write("interface_life_font", red, value_grid_x, y, "■■■■■■■■");

	NyaString::Write("interface_life_font", white, value_grid_x, y, "□□□□□□□□");
}


void NyaInterface::DrawSkill(int x, int y)
{
	const tuple<int, int, int> red = make_tuple(255, 0, 0);
	const tuple<int, int, int> white = make_tuple(255, 255, 255);

	//***********************
	// スキルの選択肢を更新
	//***********************
	if (NyaInput::IsPressKey(eINPUT::SPACE))
	{
		if      (handle_skill_.select_ == eSKILL::Q)
			handle_skill_.select_ = eSKILL::W;
		else if (handle_skill_.select_ == eSKILL::W)
			handle_skill_.select_ = eSKILL::E;
		else if (handle_skill_.select_ == eSKILL::E)
			handle_skill_.select_ = eSKILL::R;
		else
			handle_skill_.select_ = eSKILL::Q;
	}

	
	//***********************
	// スキル選択肢の表示
	//***********************
	NyaString::Write("interface_skill_font", red, x, y + 90 * (static_cast<int>(handle_skill_.select_) - 1), "★");
	for (int skill = static_cast<int>(eSKILL::Q); skill < static_cast<int>(eSKILL::sizeof_enum); skill++)
	{
		NyaString::Write("interface_skill_font", white, x, y + 90 * (skill - 1), "☆");
		NyaString::Write("interface_skill_font", white, x + 50, y + 90 * (skill - 1), handle_skill_.name_[skill]);
	}
	
	//*********************************
	// スキルのレベルと経験値の表示
	//*********************************
	for (int skill = static_cast<int>(eSKILL::Q); skill < static_cast<int>(eSKILL::sizeof_enum); skill++)
	{
		unsigned int exp = handle_skill_.exp_[skill];
		unsigned int lv1_exp = handle_skill_.lv1_exp_[skill];
		unsigned int lv2_exp = handle_skill_.lv2_exp_[skill];
		unsigned int lv3_exp = handle_skill_.lv3_exp_[skill];
		unsigned int lv4_exp = handle_skill_.lv4_exp_[skill];
		NyaString::Write("interface_skill_exp_font", white, x + 150, y + 90 * (skill - 1) + 40, "Exp : %u pt", exp);
		if (exp < lv1_exp)
		{
			NyaString::Write("interface_skill_exp_font", white, x + 150, y + 90 * (skill - 1) + 60, "Next: %u pt", lv1_exp);
			int red_width = (int)((350.0 - 1.0) * (double)exp / (double)lv1_exp);
			red_width = (350 - 1 < red_width) ? 350 : red_width;
			DrawBox(x + 1, y + 90 * (skill - 1) + 80 + 1, x + red_width, y + 90 * (skill - 1) + 80 + 6 - 1, GetColor(255, 0, 0), true);
			DrawBox(x, y + 90 * (skill - 1) + 80, x + 350, y + 90 * (skill - 1) + 80 + 6, GetColor(255, 255, 255), false);
		}
		else if (lv1_exp <= exp && exp < lv2_exp)
		{
			NyaString::Write("interface_skill_font", red, x, y + 90 * (skill - 1) + 45, "■□□□");
			NyaString::Write("interface_skill_exp_font", white, x + 150, y + 90 * (skill - 1) + 60, "Next: %u pt", lv2_exp);
			int red_width = (int)((350.0 - 1.0) * (double)(exp - lv1_exp) / (double)(lv2_exp - lv1_exp));
			red_width = (350 - 1 < red_width) ? 350 : red_width;
			DrawBox(x + 1, y + 90 * (skill - 1) + 80 + 1, x + red_width, y + 90 * (skill - 1) + 80 + 6 - 1, GetColor(255, 0, 0), true);
			DrawBox(x, y + 90 * (skill - 1) + 80, x + 350, y + 90 * (skill - 1) + 80 + 6, GetColor(255, 255, 255), false);
		}
		else if (lv2_exp <= exp && exp < lv3_exp)
		{
			NyaString::Write("interface_skill_font", red, x, y + 90 * (skill - 1) + 45, "■■□□");
			NyaString::Write("interface_skill_exp_font", white, x + 150, y + 90 * (skill - 1) + 60, "Next: %u pt", lv3_exp);
			int red_width = (int)((350.0 - 1.0) * (double)(exp - lv2_exp) / (double)(lv3_exp - lv2_exp));
			red_width = (350 - 1 < red_width) ? 350 : red_width;
			DrawBox(x + 1, y + 90 * (skill - 1) + 80 + 1, x + red_width, y + 90 * (skill - 1) + 80 + 6 - 1, GetColor(255, 0, 0), true);
			DrawBox(x, y + 90 * (skill - 1) + 80, x + 350, y + 90 * (skill - 1) + 80 + 6, GetColor(255, 255, 255), false);
		}
		else if (lv3_exp <= exp && exp < lv4_exp)
		{
			NyaString::Write("interface_skill_font", red, x, y + 90 * (skill - 1) + 45, "■■■□");
			NyaString::Write("interface_skill_exp_font", white, x + 150, y + 90 * (skill - 1) + 60, "Next: %u pt", lv4_exp);
			int red_width = (int)((350.0 - 1.0) * (double)(exp - lv3_exp) / (double)(lv4_exp - lv3_exp));
			red_width = (350 - 1 < red_width) ? 350 : red_width;
			DrawBox(x + 1, y + 90 * (skill - 1) + 80 + 1, x + red_width, y + 90 * (skill - 1) + 80 + 6 - 1, GetColor(255, 0, 0), true);
			DrawBox(x, y + 90 * (skill - 1) + 80, x + 350, y + 90 * (skill - 1) + 80 + 6, GetColor(255, 255, 255), false);
		}
		else if (lv4_exp <= exp)
		{
			NyaString::Write("interface_skill_font", red, x, y + 90 * (skill - 1) + 45, "■■■■");
			NyaString::Write("interface_skill_exp_font", white, x + 150, y + 90 * (skill - 1) + 60, "Next: %u pt", lv4_exp);
			int red_width = 350 - 1;
			DrawBox(x + 1, y + 90 * (skill - 1) + 80 + 1, x + red_width, y + 90 * (skill - 1) + 80 + 6 - 1, GetColor(255, 0, 0), true);
			DrawBox(x, y + 90 * (skill - 1) + 80, x + 350, y + 90 * (skill - 1) + 80 + 6, GetColor(255, 255, 255), false);
		}
		NyaString::Write("interface_skill_font", white, x, y + 90 * (skill - 1) + 45, "□□□□");
	}
}

void NyaInterface::DrawTitle(int x, int y)
{
	const tuple<int, int, int> white = make_tuple(212, 227, 255);

	NyaString::Write("interface_title_font", white, x, y, "%s", handle_title_.name_.str());
}

void NyaInterface::DrawWarning(int x, int y)
{
	const int black = GetColor(0, 0, 0);
	const tuple<int, int, int> red = make_tuple(255, 0, 0);

	if (handle_warning_.valid_)
	{	// warning 表示
		DrawBox(x, y, x + 400, y + 150, black, true);
		NyaString::Write("interface_warning_font", red, x + 90, y + 25, "WARNING");
		handle_warning_.draw_frame_++;

		if (handle_warning_.draw_frame_ == handle_warning_.draw_frame_max_)
		{
			handle_warning_.valid_ = false;
			handle_warning_.draw_frame_ = 0;
		}
	}	
}
