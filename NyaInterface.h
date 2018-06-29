#pragma once

#include <array>
#include <limits>
#include <string>
#include <vector>
#include <utility>
#include "NyaEnum.h"


namespace H2NLIB
{
	class SoundPropertyX;


	class InterfaceHandleMissionAllOver
	{
	public:
		int draw_grid_x_;
		int draw_grid_y_;
		bool valid_;						// trueならmission all overと表示する
		InterfaceHandleMissionAllOver();
	};

	class InterfaceHandleMissionClear
	{
	public:
		int draw_grid_x_;
		int draw_grid_y_;
		bool valid_;						// trueならmission clearと表示する
		InterfaceHandleMissionClear();
	};

	class InterfaceHandleMissionEx
	{
	public:
		bool valid_;
		double value_;
		InterfaceHandleMissionEx();
	};

	class InterfaceHandleMissionLife
	{
	public:
		int value_;
		InterfaceHandleMissionLife();
	};

	class InterfaceHandleMissionWarning
	{
	public:
		unsigned int draw_frame_;
		unsigned int draw_frame_max_;
		int draw_grid_x_;
		int draw_grid_y_;
		bool draw_valid_;
		SoundPropertyX* spx_;
		bool sound_valid_;
		InterfaceHandleMissionWarning();
		~InterfaceHandleMissionWarning();
	};

	class InterfaceHandleMissionSkill
	{
	public:
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv1_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv2_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv3_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv4_exp_;
		std::array<std::string, static_cast<int>(eSKILL::sizeof_enum)> name_;
		static eSKILL select_;		// 現在選択しているスキル
		InterfaceHandleMissionSkill();
		void AddExp(unsigned int value);
		void Clear(void);
	};

	class InterfaceHandleTitle
	{
	public:
		std::string name_;
		InterfaceHandleTitle();
	};


	class NyaInterface {
	public:
		NyaInterface();
		~NyaInterface();
		static void Init(void);
		static void Run(void);
		static InterfaceHandleMissionClear* GetHandleMissionClear(void) { return &handle_mission_clear_; }
		static InterfaceHandleMissionAllOver* GetHandleMissionAllOver(void) { return &handle_mission_all_over_; }
		static InterfaceHandleMissionEx* GetHandleMissionEx(void) { return &handle_mission_ex_; }
		static InterfaceHandleMissionLife* GetHandleMissionLife(void) { return &handle_mission_life_; }
		static InterfaceHandleMissionSkill* GetHandleMissionSkill(void) { return &handle_mission_skill_; }
		static InterfaceHandleMissionWarning* GetHandleMissionWarning(void) { return &handle_mission_warning_; }
		static InterfaceHandleTitle* GetHandleTitle(void) { return &handle_title_; }
	private:
		static InterfaceHandleMissionAllOver handle_mission_all_over_;
		static InterfaceHandleMissionClear handle_mission_clear_;
		static InterfaceHandleMissionEx handle_mission_ex_;
		static InterfaceHandleMissionSkill handle_mission_skill_;
		static InterfaceHandleMissionLife handle_mission_life_;
		static InterfaceHandleMissionWarning handle_mission_warning_;
		static InterfaceHandleTitle handle_title_;
		static void DrawBlack(int x, int y, int x2, int y2);
		static void DrawLIB(int x, int y);
		static void DrawMissionAllOver(void);
		static void DrawMissionClear(void);
		static void DrawMissionEx(void);
		static void DrawMissionWarning(void);
		static void DrawTitle(int x, int y);
		static void DrawUserInput(int x, int y);
		static void DrawUserLife(int x, int y);
		static void DrawUserSkill(int x, int y);
	};

}

