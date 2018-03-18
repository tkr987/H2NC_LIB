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
		double collision_pow_;				//!< 衝突力
		double collision_range_;			//!< 衝突範囲
		double create_x_;					//!< 生成x座標
		double create_y_;					//!< 生成y座標	
		double move_angle_deg_;				//!< 移動角度
		double move_speed_;					//!< 移動速度
		eOBJECT::NUM object_group_;			//!< オブジェクトのグループ設定
	};

	class DevicePropertyX2
	{
	public:
		double collision_pow_;				//!< 衝突力
		double collision_range_;			//!< 衝突範囲
		double create_x_;					//!< 生成x座標
		double create_y_;					//!< 生成y座標	
		double draw_angle_deg_;				//!< 描画角速度
		double move_angle_deg_;				//!< 移動角度
		double move_angle_deg_speed_;		//!< 移動角速度
		double move_speed_;					//!< 移動速度
		double move_speed_accel_;			//!< 移動速度の加速度
		eOBJECT::NUM object_group_;			//!< オブジェクトのグループ設定
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
