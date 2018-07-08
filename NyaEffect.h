#pragma once

#include "NyaEnum.h"
#include <list>
#include <string>
#include <utility>
#include <vector>


namespace H2NLIB 
{
	class GraphicPropertyX4;
	class PositionHandle;

	//********************************************************************
	// class EffectPropertyX2
	// 絶対座標を指定してエフェクトを貼りたいときに使うプロパティ
	//********************************************************************
	class EffectPropertyX1
	{
	public:
		int interval_time_frame_;		//!< アニメーションインターバル時間(フレーム指定)
		double grid_x_;					//!< 描画x座標
		double grid_y_;					//!< 描画y座標
		EffectPropertyX1();
	};

	//*****************************************************************************************************
	// class EffectPropertyX2
	// 動的に動くオブジェクトに追随してエフェクトを貼りたいときに使うプロパティ
	// PositionHandle::grid_x_やPositionHandle::grid_y_のアドレスを渡すときなどオブジェクトの寿命に注意
	//*****************************************************************************************************
	class EffectPropertyX2
	{
	public:
		int interval_time_frame_;		//!< アニメーションインターバル時間(フレーム指定)
		double gap_x_;					//!< x座標ギャップ
		double gap_y_;					//!< y座標ギャップ
		double* grid_x_;				//!< 描画x座標
		double* grid_y_;				//!< 描画y座標
		EffectPropertyX2();
	};

	class EffectAnimation1
	{
	public:
		int count_;
		EffectPropertyX1* epx_;
		GraphicPropertyX4* gpx_;
		EffectAnimation1();
		~EffectAnimation1();
	};

	class EffectAnimation2
	{
	public:
		int count_;
		EffectPropertyX2* epx_;
		GraphicPropertyX4* gpx_;
		EffectAnimation2();
		~EffectAnimation2();
	};

	class NyaEffect
	{
	public:
		static void Draw(const EffectPropertyX1* epx, const GraphicPropertyX4* gpx, eOBJECT layer);
		static void Draw(const EffectPropertyX2* epx, const GraphicPropertyX4* gpx, eOBJECT layer);
		static void Run(void);
	private:
		static std::list<EffectAnimation1> ea1_draw_list_[(int)eOBJECT::sizeof_enum];
		static std::list<EffectAnimation1> ea1_wait_list_;
		static std::list<EffectAnimation2> ea2_draw_list_[(int)eOBJECT::sizeof_enum];
		static std::list<EffectAnimation2> ea2_wait_list_;
		static void DrawAnimation1(eOBJECT layer);
		static void DrawAnimation2(eOBJECT layer);
	};

}

