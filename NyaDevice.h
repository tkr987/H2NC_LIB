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
		int collision_power_;					//!< �Ռ���
		int collision_range_;					//!< �Փ˔͈�
		double create_x_;						//!< ����x���W
		double create_y_;						//!< ����y���W	
		unsigned int delay_time_frame_;			//!< �x������(�t���[���P��)
		double draw_angle_deg_;					//!< �`��p�x
		double draw_angle_speed_deg_;			//!< �`��p���x
		double move_angle_deg_;					//!< �ړ��p�x
		double move_speed_;						//!< �ړ����x
		DevicePropertyX1();
	};

	class DevicePropertyX2
	{
	public:
		int collision_power_;					//!< �Ռ���
		int collision_range_;					//!< �Փ˔͈�
		double create_x_;						//!< ����x���W
		double create_y_;						//!< ����y���W	
		unsigned int delay_time_frame_;			//!< �x������(�t���[���P��)
		double draw_angle_deg_;					//!< �`��p�x
		double draw_angle_speed_deg_;			//!< �`��p���x
		double move_angle_deg_;					//!< �ړ��p�x
		double move_angle_speed_deg_;			//!< �ړ��p���x
		double move_speed_;						//!< �ړ����x
		DevicePropertyX2();
	};

	class DevicePropertyX3
	{
	public:
		int collision_power_;					//!< �Ռ���
		int collision_range_;					//!< �Փ˔͈�
		double create_x_;						//!< ����x���W
		double create_y_;						//!< ����y���W	
		unsigned int delay_time_frame_;			//!< �x������(�t���[���P��)
		double draw_angle_deg_;					//!< �`��p�x
		double draw_angle_speed_deg_;			//!< �`��p���x
		double move_angle_deg_;					//!< �ړ��p�x
		double move_speed_;						//!< �ړ����x
		double move_speed_accel_;				//!< �ړ������x
		DevicePropertyX3();
	};

	//*****************************************************
	// class DeviceGadget14
	// DevicePropertyX1�P�̎g�p�A�G�t�F�N�g�Ȃ�
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
		DevicePropertyX1* gadget_dpx_;
		GraphicPropertyX4* gadget_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget14();
		~DeviceGadget14();
	};

	//*****************************************************
	// class DeviceGadget24
	// DevicePropertyX2�P�̎g�p�A�G�t�F�N�g�Ȃ�
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
		GraphicPropertyX4* gadget_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget24();
		~DeviceGadget24();
	};

	//*****************************************************
	// class DeviceGadget34
	// DevicePropertyX3�P�̎g�p�A�G�t�F�N�g�Ȃ�
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
		GraphicPropertyX4* gadget_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget34();
		~DeviceGadget34();
	};

	//*****************************************************
	// class DeviceGadget1414
	// DevicePropertyX1��EffectPropertyX1�̑g�ݍ��킹
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
		GraphicPropertyX4* gadget_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget1414();
		~DeviceGadget1414();
	};

	//*****************************************************
	// class DeviceGadget1424
	// DevicePropertyX1��EffectPropertyX1�̑g�ݍ��킹
	//*****************************************************
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
		GraphicPropertyX4* gadget_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget1424();
		~DeviceGadget1424();
	};

	//*****************************************************
	// class DeviceGadget2414
	// DevicePropertyX2��EffectPropertyX1�̑g�ݍ��킹
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
		GraphicPropertyX4* gadget_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget2414();
		~DeviceGadget2414();
	};

	//*****************************************************
	// class DeviceGadget3414
	// DevicePropertyX3��EffectPropertyX1�̑g�ݍ��킹
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
		GraphicPropertyX4* gadget_gpx_;
		std::array<PositionHandle*, DEVICE_COLLISION_MAX_ACCURACY> gadget_phandle_collection_;
		DeviceGadget3414();
		~DeviceGadget3414();
	};


	class NyaDevice
	{
	public:
		static void Attack14(const DevicePropertyX1* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type, unsigned int collision_accuracy = 1);
		static void Attack24(const DevicePropertyX2* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type, unsigned int collision_accuracy = 1);
		static void Attack34(const DevicePropertyX3* const gadget_dpx, const GraphicPropertyX4* const gadget_gpx, eOBJECT gadget_type, unsigned int collision_accuracy = 1);
		static void Attack1414(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
		static void Attack1424(const DevicePropertyX1* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX2* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
		static void Attack2414(const DevicePropertyX2* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
		static void Attack3414(const DevicePropertyX3* gadget_dpx, const GraphicPropertyX4* gadget_gpx, const EffectPropertyX1* effect_epx, const GraphicPropertyX4* effect_gpx, eOBJECT gadget_type, eOBJECT effect_type, unsigned int collision_accuracy = 1);
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
		static std::list<DeviceGadget3414> gadget3414_attack_list_[(int)eOBJECT::sizeof_enum];
		static std::list<DeviceGadget3414> gadget3414_wait_list_;
		static void CalculateGadget(eOBJECT group);
		static double RadToAngle(double x) { return (x * 180.0 / 3.14159); }
		static double AngleToRad(double x) { return (x * 3.14159 / 180.0); }
	};

}
