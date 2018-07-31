#pragma once


#include "NyaEnum.h"
#include <array>
#include <list>
#include <string>
#include <utility>
#include <tuple>
#include <vector>


namespace HNLIB
{
	class EffectPropertyX1;
	class EffectPropertyX2;
	class GraphicPropertyX4;
	class PositionHandle;

	class DevicePropertyX1
	{
	public:
		int collision_power_;					//!< 衝撃力
		int collision_range_;					//!< 衝突範囲
		double create_x_;						//!< 生成x座標
		double create_y_;						//!< 生成y座標	
		unsigned int delay_time_frame_;			//!< 遅延時間(フレーム単位)
		double draw_angle_deg_;					//!< 描画角度
		double draw_angle_speed_deg_;			//!< 描画角速度
		double move_angle_deg_;					//!< 移動角度
		double move_speed_;						//!< 移動速度
		DevicePropertyX1();
	};

	class DevicePropertyX2
	{
	public:
		int collision_power_;					//!< 衝撃力
		int collision_range_;					//!< 衝突範囲
		double create_x_;						//!< 生成x座標
		double create_y_;						//!< 生成y座標	
		unsigned int delay_time_frame_;			//!< 遅延時間(フレーム単位)
		double draw_angle_deg_;					//!< 描画角度
		double draw_angle_speed_deg_;			//!< 描画角速度
		double move_angle_deg_;					//!< 移動角度
		double move_angle_speed_deg_;			//!< 移動角速度
		double move_speed_;						//!< 移動速度
		DevicePropertyX2();
	};

	class DevicePropertyX3
	{
	public:
		int collision_power_;					//!< 衝撃力
		int collision_range_;					//!< 衝突範囲
		double create_x_;						//!< 生成x座標
		double create_y_;						//!< 生成y座標	
		unsigned int delay_time_frame_;			//!< 遅延時間(フレーム単位)
		double draw_angle_deg_;					//!< 描画角度
		double draw_angle_speed_deg_;			//!< 描画角速度
		double move_angle_deg_;					//!< 移動角度
		double move_speed_;						//!< 移動速度
		double move_speed_accel_;				//!< 移動加速度
		DevicePropertyX3();
	};

	//*****************************************************
	// class DeviceGadget14
	// DevicePropertyX1単体使用、エフェクトなし
	//*****************************************************
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
		GraphicPropertyX4* device_gpx_;
		DevicePropertyX1* dpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> phandle_collection_;
		DeviceGadget14();
		~DeviceGadget14();
	};

	//*****************************************************
	// class DeviceGadget24
	// DevicePropertyX2単体使用、エフェクトなし
	//*****************************************************
	class DeviceGadget24
	{
	public:
		bool clear_;
		unsigned int collision_accuracy_;
		unsigned int count_frame_;
		double move_angle_deg_;
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		DevicePropertyX2* gadget_dpx_;
		GraphicPropertyX4* device_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget24();
		~DeviceGadget24();
	};

	//*****************************************************
	// class DeviceGadget34
	// DevicePropertyX3単体使用、エフェクトなし
	//*****************************************************
	class DeviceGadget34
	{
	public:
		bool clear_;
		unsigned int collision_accuracy_;
		unsigned int count_frame_;
		double move_angle_deg_;
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		DevicePropertyX3* gadget_dpx_;
		GraphicPropertyX4* device_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget34();
		~DeviceGadget34();
	};

	//*****************************************************
	// class DeviceGadget1414
	// DevicePropertyX1とEffectPropertyX1の組み合わせ
	//*****************************************************
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
		GraphicPropertyX4* device_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget1414();
		~DeviceGadget1414();
	};

	//**********************************************************
	// class DeviceGadget1424
	// DevicePropertyX1とEffectPropertyX2の組み合わせで構成
	//**********************************************************
	class DeviceGadget1424
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
		EffectPropertyX2* effect_epx_;
		GraphicPropertyX4* effect_gpx_;
		DevicePropertyX1* gadget_dpx_;
		GraphicPropertyX4* device_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget1424();
		~DeviceGadget1424();
	};

	//*****************************************************
	// class DeviceGadget2414
	// DevicePropertyX2とEffectPropertyX1の組み合わせ
	//*****************************************************
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
		GraphicPropertyX4* device_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget2414();
		~DeviceGadget2414();
	};

	//**********************************************************
	// class DeviceGadget2424
	// DevicePropertyX2とEffectPropertyX2の組み合わせで構成
	//**********************************************************
	class DeviceGadget2424
	{
	public:
		bool clear_;
		unsigned int collision_accuracy_;
		unsigned int count_frame_;
		eOBJECT effect_type_;
		double move_angle_deg_;
		double move_angle_rad_;
		double move_x_;
		double move_y_;
		GraphicPropertyX4* device_gpx_;
		DevicePropertyX2* dpx_;
		GraphicPropertyX4* effect_gpx_;
		EffectPropertyX2* epx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> phandle_collection_;
		DeviceGadget2424();
		~DeviceGadget2424();
	};

	//*****************************************************
	// class DeviceGadget3414
	// DevicePropertyX3とEffectPropertyX1の組み合わせ
	//*****************************************************
	class DeviceGadget3414
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
		DevicePropertyX3* gadget_dpx_;
		GraphicPropertyX4* device_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget3414();
		~DeviceGadget3414();
	};


	class NyaDevice
	{
	public:
		static void Attack14(const DevicePropertyX1* const dpx, const GraphicPropertyX4* const device_gpx, eOBJECT gadget_type, unsigned int collision_accuracy = 1);
		static void Attack24(const DevicePropertyX2* const dpx, const GraphicPropertyX4* const device_gpx, eOBJECT gadget_type, unsigned int collision_accuracy = 1);
		static void Attack34(const DevicePropertyX3* const dpx, const GraphicPropertyX4* const device_gpx, eOBJECT gadget_type, unsigned int collision_accuracy = 1);
		static void Attack1414(const DevicePropertyX1* dpx, const GraphicPropertyX4* device_gpx, const EffectPropertyX1* epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
		static void Attack1424(const DevicePropertyX1* dpx, const GraphicPropertyX4* device_gpx, const EffectPropertyX2* epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
		static void Attack2414(const DevicePropertyX2* dpx, const GraphicPropertyX4* device_gpx, const EffectPropertyX1* epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
		static void Attack2424(const DevicePropertyX2* dpx, const GraphicPropertyX4* device_gpx, const EffectPropertyX2* epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
		static void Attack3414(const DevicePropertyX3* dpx, const GraphicPropertyX4* device_gpx, const EffectPropertyX1* epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
		static void Clear(eOBJECT type);
		static void Run(void);
		static size_t Size(eOBJECT type);
	private:
		static std::list<DeviceGadget14> gadget14_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget14> gadget14_wait_list_;
		static std::list<DeviceGadget24> gadget24_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget24> gadget24_wait_list_;
		static std::list<DeviceGadget34> gadget34_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget34> gadget34_wait_list_;
		static std::list<DeviceGadget1414> gadget1414_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget1414> gadget1414_wait_list_;
		static std::list<DeviceGadget1424> gadget1424_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget1424> gadget1424_wait_list_;
		static std::list<DeviceGadget2414> gadget2414_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget2414> gadget2414_wait_list_;
		static std::list<DeviceGadget2424> gadget2424_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget2424> gadget2424_wait_list_;
		static std::list<DeviceGadget3414> gadget3414_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget3414> gadget3414_wait_list_;
		static void Calculate(eOBJECT group);
		static double RadToAngle(double x) { return (x * 180.0 / 3.14159); }
		static double AngleToRad(double x) { return (x * 3.14159 / 180.0); }
	};

}
