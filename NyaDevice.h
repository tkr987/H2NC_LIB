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
	class GraphicPropertyX4;
	class PositionHandleX;

	class DeviceEffect {
	public:
		bool set_;
		int animation_div_max_;
		int animation_interval_time_;
		int file_id_;
		eOBJECT::GROUP object_group_;
		int effect_option_index_;
	};

	class DeviceGraphic {
	public:
		bool set_;
		int file_id_;
	};

	struct Gadget {
		double draw_angle_;
		double move_angle_;
		double move_x_;
		double move_y_;
		DeviceEffect effect_;
		DeviceGraphic graphic_;
		PositionHandleX* phx_;
		int device_option_index_;
	};

	class DeviceOption {
	public:
		double draw_angle_;					//!< 描画角度
		double draw_extend_;				//!< 描画拡大率
		double draw_rotate_;				//!< 描画角速度
		double collision_pow_;				//!< 衝突力
		double collision_range_;			//!< 衝突範囲
		DeviceOption() {
			draw_angle_ = 0;
			draw_extend_ = 1.0;
			draw_rotate_ = 0;
			collision_pow_ = 1.0;
			collision_range_ = 10;
		}
	};

	class DevicePropertyX {
	public:
		double create_x_;					//!< 生成x座標
		double create_y_;					//!< 生成y座標	
		double move_angle_;					//!< 移動角度
		double move_speed_;					//!< 移動速度
		eOBJECT::GROUP object_group_;		//!< オブジェクトのグループ設定
	};

	class NyaDevice {
	public:
		NyaDevice();
		~NyaDevice();
		void Attack(DevicePropertyX* dpx, int option_index = 0);
		int NewOption(DeviceOption* option);
		void Run(void);
		void SetEffect(std::string file_pass, int div_x, int div_y, int animation_div_max, int animation_interval_time, eOBJECT::GROUP object_group);
		void SetEffect(std::string file_pass, int div_x, int div_y, int animation_div_max, int animation_interval_time, eOBJECT::GROUP object_group, double draw_angle, double draw_extend_, double draw_move_x_, double draw_move_y_);
		void SetGraphic(std::string file_pass);
	private:
		NyaEffect* nya_effect_;
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		DeviceEffect effect_;
		DeviceGraphic graphic_;
		static std::vector<DeviceOption> option_vector_;
		static std::list<Gadget> attack_list_[eOBJECT::GROUP::sizeof_enum];
		static std::list<Gadget> wait_list_;
		void Calculate(eOBJECT::GROUP group);
		double RadToAngle(double x) { return (x * 180.0 / 3.14159); }
		double AngleToRad(double x) { return (x * 3.14159 / 180.0); }
	};

}
