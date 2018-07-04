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

	class InterfaceHandleHealth
	{
	public:
		bool valid_;
		double value_;
		InterfaceHandleHealth();
	};

	class InterfaceHandleLife
	{
	public:
		int value_;
		InterfaceHandleLife();
	};

	class InterfaceHandleSkill
	{
	public:
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv1_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv2_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv3_exp_;
		std::array<unsigned int, static_cast<int>(eSKILL::sizeof_enum)> lv4_exp_;
		std::array<std::string, static_cast<int>(eSKILL::sizeof_enum)> name_;
		eSKILL select_;									// 現在選択しているスキル
		InterfaceHandleSkill();
		void AddExp(unsigned int value);
		void Clear(void);
	};

	class InterfaceHandleWarning
	{
	public:
		unsigned int draw_frame_;
		unsigned int draw_frame_max_;
		int draw_grid_x_;
		int draw_grid_y_;
		bool draw_valid_;
		SoundPropertyX* spx_;
		bool sound_valid_;
		void LoadSound(std::string file_pass, unsigned int volume = 100);
		void DeleteSound(void);
		InterfaceHandleWarning();
		~InterfaceHandleWarning();
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
		static InterfaceHandleHealth* GetHandleHealth (void) { return &handle_health_; }
		static InterfaceHandleLife* GetHandleLife(void) { return &handle_life_; }
		static InterfaceHandleSkill* GetHandleSkill(void) { return &handle_skill_; }
		static InterfaceHandleTitle* GetHandleTitle(void) { return &handle_title_; }
		static InterfaceHandleWarning* GetHandleWarning(void) { return &handle_warning_; }
	private:
		static InterfaceHandleLife handle_life_;
		static InterfaceHandleMissionAllOver handle_mission_all_over_;
		static InterfaceHandleMissionClear handle_mission_clear_;
		static InterfaceHandleHealth handle_health_;
		static InterfaceHandleSkill handle_skill_;
		static InterfaceHandleTitle handle_title_;
		static InterfaceHandleWarning handle_warning_;
		static void DrawBlack(int x, int y, int x2, int y2);
		static void DrawLIB(int x, int y);
		static void DrawMissionAllOver(void);
		static void DrawMissionClear(void);
		static void DrawHealth(void);
		static void DrawTitle(int x, int y);
		static void DrawInput(int x, int y);
		static void DrawLife(int x, int y);
		static void DrawSkill(int x, int y);
		static void DrawWarning(void);
	};

}

