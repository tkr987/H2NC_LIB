#pragma once


#include "NyaEnum.h"
#include <array>
#include <list>
#include <string>
#include <utility>
#include <tuple>
#include <vector>


namespace H2NLIB
{

	class EffectPropertyX1;
	class GraphicPropertyX4;
	class PositionHandle;

	class DevicePropertyX1
	{
	public:
		int collision_power_;					//!< Õ“Ë—Í
		int collision_range_;					//!< Õ“Ë”ÍˆÍ
		double create_x_;						//!< ¶¬xÀ•W
		double create_y_;						//!< ¶¬yÀ•W	
		unsigned int delay_time_frame_;			//!< ’x‰„ŽžŠÔ(ƒtƒŒ[ƒ€’PˆÊ)
		double draw_angle_deg_;					//!< •`‰æŠp“x
		double draw_angle_speed_deg_;			//!< •`‰æŠp‘¬“x
		double move_angle_deg_;					//!< ˆÚ“®Šp“x
		double move_speed_;						//!< ˆÚ“®‘¬“x
		DevicePropertyX1();
	};

	class DevicePropertyX2
	{
	public:
		int collision_power_;					//!< Õ“Ë—Í
		int collision_range_;					//!< Õ“Ë”ÍˆÍ
		double create_x_;						//!< ¶¬xÀ•W
		double create_y_;						//!< ¶¬yÀ•W	
		unsigned int delay_time_frame_;			//!< ’x‰„ŽžŠÔ(ƒtƒŒ[ƒ€’PˆÊ)
		double draw_angle_deg_;					//!< •`‰æŠp“x
		double draw_angle_speed_deg_;			//!< •`‰æŠp‘¬“x
		double move_angle_deg_;					//!< ˆÚ“®Šp“x
		double move_angle_speed_deg_;			//!< ˆÚ“®Šp‘¬“x
		double move_speed_;						//!< ˆÚ“®‘¬“x
		DevicePropertyX2();
	};


	class DeviceGadget14
	{
	public:
		bool clear_;
		unsigned int collision_accuracy_;
		unsigned int count_frame_;
		double move_angle_deg_;
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		DevicePropertyX1* gadget_dpx_;
		GraphicPropertyX4* gadget_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget14();
		~DeviceGadget14();
	};

	class DeviceGadget1414
	{
	public:
		bool clear_;
		unsigned int collision_accuracy_;
		unsigned int count_frame_;
		double move_angle_deg_;
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		eOBJECT effect_type_;
		EffectPropertyX1* effect_epx_;
		GraphicPropertyX4* effect_gpx_;
		DevicePropertyX1* gadget_dpx_;
		GraphicPropertyX4* gadget_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget1414();
		~DeviceGadget1414();
	};

	class DeviceGadget2414
	{
	public:
		bool clear_;
		unsigned int collision_accuracy_;
		unsigned int count_frame_;
		double move_angle_deg_;
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		eOBJECT effect_type_;
		EffectPropertyX1* effect_epx_;
		GraphicPropertyX4* effect_gpx_;
		DevicePropertyX2* gadget_dpx_;
		GraphicPropertyX4* gadget_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget2414();
		~DeviceGadget2414();
	};


	class NyaDevice
	{
	public:
		static void Attack14(const DevicePropertyX1* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type, unsigned int collision_accuracy = 1);
		static void Attack1414(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
		static void Attack2414(const DevicePropertyX2* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
		static void Clear(eOBJECT type);
		static void Run(void);
	private:
		static std::list<DeviceGadget14> dg14_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget14> dg14_wait_list_;
		static std::list<DeviceGadget1414> dg1414_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget1414> dg1414_wait_list_;
		static std::list<DeviceGadget2414> dg2414_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget2414> dg2414_wait_list_;
		static void CalculateGadget(eOBJECT group);
		static double RadToAngle(double x) { return (x * 180.0 / 3.14159); }
		static double AngleToRad(double x) { return (x * 3.14159 / 180.0); }
	};

}
