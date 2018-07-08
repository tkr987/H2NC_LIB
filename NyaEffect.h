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
	// ��΍��W���w�肵�ăG�t�F�N�g��\�肽���Ƃ��Ɏg���v���p�e�B
	//********************************************************************
	class EffectPropertyX1
	{
	public:
		int interval_time_frame_;		//!< �A�j���[�V�����C���^�[�o������(�t���[���w��)
		double grid_x_;					//!< �`��x���W
		double grid_y_;					//!< �`��y���W
		EffectPropertyX1();
	};

	//*****************************************************************************************************
	// class EffectPropertyX2
	// ���I�ɓ����I�u�W�F�N�g�ɒǐ����ăG�t�F�N�g��\�肽���Ƃ��Ɏg���v���p�e�B
	// PositionHandle::grid_x_��PositionHandle::grid_y_�̃A�h���X��n���Ƃ��ȂǃI�u�W�F�N�g�̎����ɒ���
	//*****************************************************************************************************
	class EffectPropertyX2
	{
	public:
		int interval_time_frame_;		//!< �A�j���[�V�����C���^�[�o������(�t���[���w��)
		double gap_x_;					//!< x���W�M���b�v
		double gap_y_;					//!< y���W�M���b�v
		double* grid_x_;				//!< �`��x���W
		double* grid_y_;				//!< �`��y���W
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

