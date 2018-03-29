#pragma once


#include "NyaDefine.h"
#include <list>
#include <string>
#include <utility>
#include <tuple>
#include <vector>


namespace H2NLIB
{

	class NyaEffect;
	class NyaGraphic;
	class NyaPosition;
	class EffectProperty1;
	class GraphicProperty4;
	class PositionHandle1;

	class DeviceProperty1
	{
	public:
		double collision_pow_;				//!< 衝突力
		double collision_range_;			//!< 衝突範囲
		double create_x_;					//!< 生成x座標
		double create_y_;					//!< 生成y座標	
		double move_angle_deg_;				//!< 移動角度
		double move_speed_;					//!< 移動速度
	};

	class DeviceProperty2
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
	};


	class DeviceGadget14
	{
	public:
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		DeviceProperty1* gadget_dp_;
		GraphicProperty4* gadget_gp_;
		PositionHandle1* gadget_ph_;
		DeviceGadget14();
		~DeviceGadget14();
	};

	class DeviceGadget1414
	{
	public:
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		EffectProperty1* effect_ep_;
		GraphicProperty4* effect_gp_;
		DeviceProperty1* gadget_dp_;
		GraphicProperty4* gadget_gp_;
		PositionHandle1* gadget_ph_;
		eOBJECT::NUM effect_type_;
		DeviceGadget1414();
		~DeviceGadget1414();
	};

	class DeviceGadget2414
	{
	public:

	};


	class NyaDevice {
	public:
		NyaDevice();
		~NyaDevice();
		void Attack14(const DeviceProperty1* const gadget_dp, const GraphicProperty4* const gadget_gp, eOBJECT::NUM gadget_type);
		void Attack1414(const DeviceProperty1* gadget_dp, const GraphicProperty4* gadget_gp, const EffectProperty1* effect_ep, const GraphicProperty4* effect_gp, eOBJECT::NUM gadget_type, eOBJECT::NUM effect_type);
		void Attack2414(DeviceProperty2* gadget_dp, GraphicProperty4* gadget_gp, EffectProperty1* effect_ep, GraphicProperty4* effect_gp);
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
		static std::list<DeviceGadget2414> dg2414_attack_list_[eOBJECT::NUM::sizeof_enum];
		static std::list<DeviceGadget2414> dg2414_wait_list_;
		void MoveGadget(eOBJECT::NUM group);
		double RadToAngle(double x) { return (x * 180.0 / 3.14159); }
		double AngleToRad(double x) { return (x * 3.14159 / 180.0); }
	};

}
