#pragma once

#include "NyaDefine.h"
#include <list>
#include <string>
#include <utility>
#include <vector>


namespace H2NLIB 
{

	class NyaGraphic;
	class NyaPosition;
	class GraphicPropertyX4;
	class PositionHandleX;


	class EffectPropertyX1
	{
	public:
		int interval_time_frame_;
		int grid_x_;
		int grid_y_;
		EffectPropertyX1(){}
		~EffectPropertyX1(){}
	};

	class EffectPropertyX2
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
		EffectPropertyX1* epx1_;
		GraphicPropertyX4* gpx4_;
	};

	class EffectAnimation2
	{
	public:
		int count_;
		EffectPropertyX2* epx2_;
		GraphicPropertyX4* gpx4_;
	};

	class NyaEffect
	{
	public:
		NyaEffect();
		~NyaEffect();
		void Draw(EffectPropertyX1* epx, GraphicPropertyX4* gpx4);
		void Draw(EffectPropertyX2* epx, GraphicPropertyX4* gpx4);
		void Run(void);
	private:
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		static int count_instance_;
		static std::list<EffectAnimation1> ea1_draw_list_;
		static std::list<EffectAnimation1> ea1_wait_list_;
		static std::list<EffectAnimation2> ea2_draw_list_;
		static std::list<EffectAnimation2> ea2_wait_list_;
		void DrawAnimation1(void);
		void DrawAnimation2(void);
	};

}

