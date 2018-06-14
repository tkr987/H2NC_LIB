#pragma once

#include "NyaEnum.h"
#include <list>
#include <string>
#include <utility>
#include <vector>


namespace H2NLIB 
{

	class NyaGraphic;
	class NyaPosition;
	class GraphicPropertyX4;
	class PositionHandle1;


	class EffectProperty1
	{
	public:
		int interval_time_frame_;		//!< アニメーションインターバル時間(フレーム指定)
		int grid_x_;					//!< 描画x座標
		int grid_y_;					//!< 描画y座標
	};

	class EffectProperty2
	{
	public:
		double draw_move_x_;
		double draw_move_y_;
		int interval_time_frame_;
		int grid_x_;
		int grid_y_;
	};

	class EffectAnimation1
	{
	public:
		int count_;
		EffectProperty1* ep_;
		GraphicPropertyX4* gp_;
	};

	class EffectAnimation2
	{
	public:
		int count_;
		EffectProperty2* ep_;
		GraphicPropertyX4* gp_;
	};

	class NyaEffect
	{
	public:
		NyaEffect();
		~NyaEffect();
		void Draw(const EffectProperty1* ep, const GraphicPropertyX4* gp, eOBJECT layer);
		void Draw(const EffectProperty2* ep, const GraphicPropertyX4* gp, eOBJECT layer);
		void Run(void);
	private:
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		static int count_instance_;
		static std::list<EffectAnimation1> ea1_draw_list_[(int)eOBJECT::sizeof_enum];
		static std::list<EffectAnimation1> ea1_wait_list_;
		static std::list<EffectAnimation2> ea2_draw_list_[(int)eOBJECT::sizeof_enum];
		static std::list<EffectAnimation2> ea2_wait_list_;
		void DrawAnimation1(eOBJECT layer);
		void DrawAnimation2(eOBJECT layer);
	};

}

