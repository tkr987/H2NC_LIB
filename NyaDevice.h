#pragma once


#include "NyaDefine.h"
#include <list>
#include <string>
#include <utility>
#include <tuple>
#include <vector>


namespace H2NLIB {

	class NyaEffect;
	class NyaGraphic;
	class NyaPosition;
	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandleX;

	class DevicePropertyX1
	{
	public:
		double collision_pow_;				//!< �Փ˗�
		double collision_range_;			//!< �Փ˔͈�
		double create_x_;					//!< ����x���W
		double create_y_;					//!< ����y���W	
		double move_angle_deg_;				//!< �ړ��p�x
		double move_speed_;					//!< �ړ����x
		eOBJECT::NUM object_group_;			//!< �I�u�W�F�N�g�̃O���[�v�ݒ�
	};

	class DevicePropertyX2
	{
	public:
		double collision_pow_;				//!< �Փ˗�
		double collision_range_;			//!< �Փ˔͈�
		double create_x_;					//!< ����x���W
		double create_y_;					//!< ����y���W	
		double draw_angle_deg_;				//!< �`��p���x
		double move_angle_deg_;				//!< �ړ��p�x
		double move_angle_deg_speed_;		//!< �ړ��p���x
		double move_speed_;					//!< �ړ����x
		double move_speed_accel_;			//!< �ړ����x�̉����x
		eOBJECT::NUM object_group_;			//!< �I�u�W�F�N�g�̃O���[�v�ݒ�
	};


	class DeviceGadget14
	{
	public:
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		DevicePropertyX1* dpx1_;
		GraphicPropertyX4* gadget_gpx4_;
		PositionHandleX* phx_;

	};

	class DeviceGadget1414
	{
	public:
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		DevicePropertyX1* dpx1_;
		GraphicPropertyX4* gadget_gpx4_;
		EffectPropertyX1* epx1_;
		GraphicPropertyX4* effect_gpx4_;
		PositionHandleX* phx_;
	};


	class NyaDevice {
	public:
		NyaDevice();
		~NyaDevice();
		void Attack(DevicePropertyX1* dpx, GraphicPropertyX4* gadget_gpx4);
		void Attack(DevicePropertyX1* dpx, GraphicPropertyX4* gadget_gpx4, EffectPropertyX1* epx1, GraphicPropertyX4* effect_gpx4);
		void Attack(DevicePropertyX2* dpx, GraphicPropertyX4* gadget_gpx4, EffectPropertyX1* epx1, GraphicPropertyX4* effect_gpx4);
		void Run(void);
	private:
		NyaEffect* nya_effect_;
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		static int count_instance_;
		static std::list<DeviceGadget14> dg14_attack_list_[eOBJECT::NUM::sizeof_enum];
		static std::list<DeviceGadget14> dg14_wait_list_;
		static std::list<DeviceGadget1414> dg1414_attack_list_[eOBJECT::NUM::sizeof_enum];
		static std::list<DeviceGadget1414> dg1414_wait_list_;
		void MoveGadget(eOBJECT::NUM group);
		double RadToAngle(double x) { return (x * 180.0 / 3.14159); }
		double AngleToRad(double x) { return (x * 3.14159 / 180.0); }
	};

}
