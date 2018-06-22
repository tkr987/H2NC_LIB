#pragma once


#include "NyaEnum.h"
#include <list>
#include <string>
#include <utility>
#include <tuple>
#include <vector>


namespace H2NLIB
{

	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle1;

	class DevicePropertyX1
	{
	public:
		int collision_power_;				//!< 衝突力
		int collision_range_;				//!< 衝突範囲
		double create_x_;					//!< 生成x座標
		double create_y_;					//!< 生成y座標	
		double move_angle_deg_;				//!< 移動角度
		double move_speed_;					//!< 移動速度
		DevicePropertyX1();
	};

	class DevicePropertyX2
	{
	public:
		int collision_power_;				//!< 衝突力
		int collision_range_;				//!< 衝突範囲
		double create_x_;					//!< 生成x座標
		double create_y_;					//!< 生成y座標	
		double draw_angle_deg_;				//!< 描画角速度
		double move_angle_deg_;				//!< 移動角度
		double move_angle_deg_speed_;		//!< 移動角速度
		double move_speed_;					//!< 移動速度
		double move_speed_accel_;			//!< 移動速度の加速度
	};


	class DeviceGadget14
	{
	public:
		bool clear_;
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		DevicePropertyX1* gadget_dpx_;
		GraphicPropertyX4* gadget_gpx_;
		PositionHandle1* gadget_phandle_;
		DeviceGadget14();
		~DeviceGadget14();
	};

	class DeviceGadget1414
	{
	public:
		bool clear_;
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		EffectPropertyX1* effect_epx_;
		GraphicPropertyX4* effect_gpx_;
		DevicePropertyX1* gadget_dpx_;
		GraphicPropertyX4* gadget_gpx_;
		PositionHandle1* gadget_phandle_;
		eOBJECT effect_type_;
		DeviceGadget1414();
		~DeviceGadget1414();
	};

	class DeviceGadget2414
	{
	public:

	};


	class NyaDevice
	{
	public:
		static void Attack14(const DevicePropertyX1* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type);
		static void Attack1414(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type);
		static void Attack2414(DevicePropertyX2* gadget_dpx, GraphicPropertyX4* gadget_gpx, EffectPropertyX1* effect_epx, GraphicPropertyX4* effect_gpx);
		static void Clear(eOBJECT type);
		static void Run(void);
	private:
		static std::list<DeviceGadget14> dg14_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget14> dg14_wait_list_;
		static std::list<DeviceGadget1414> dg1414_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget1414> dg1414_wait_list_;
		static std::list<DeviceGadget2414> dg2414_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget2414> dg2414_wait_list_;
		static void MoveGadget(eOBJECT group);
		static double RadToAngle(double x) { return (x * 180.0 / 3.14159); }
		static double AngleToRad(double x) { return (x * 3.14159 / 180.0); }
	};

}
