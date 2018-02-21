#pragma once


#include "NyaDefine.h"
#include <list>
#include <utility>
#include <tuple>
#include <vector>


namespace H2NLIB {

	struct GraphicPropertyX4;
	struct PositionHandleX;
	class NyaEffect;
	class NyaGraphic;
	class NyaPosition;

	struct Bullet {
		bool delete_flag_;
		double draw_angle_;
		double move_angle_;
		double move_x_;
		double move_y_;
		int device_setting_id_;
		std::pair<bool, int> set_effect_;
		std::tuple<bool, int, int> set_graphic_;
		PositionHandleX* phx_;
	};

	struct DeviceSetting {
		double draw_extend_;				//!< 描画拡大率
		double draw_rotate_;				//!< 描画角速度
		double collision_pow_;				//!< 衝突時の攻撃力
		double collision_range_;			//!< 衝突範囲
		eOBJECT::GROUP object_group_;		//!< オブジェクトのグループ設定
	};

	struct DevicePropertyX {
		double create_x_;					//!< 生成x座標
		double create_y_;					//!< 生成y座標	
		double draw_angle_;					//!< 描画角度
		double move_angle_;					//!< 移動角度
		double move_speed_;					//!< 移動速度
		int device_setting_id_;				//!< NyaDeviceの設定ID
	};

	class NyaDevice {
	public:
		NyaDevice();
		~NyaDevice();
		void Attack(DevicePropertyX* dpx);
		int LoadSetting(DeviceSetting* setting);
		void Run(void);
		void SetEffect(int effect_setting_id);
		void SetGraphic(int graphic_file_id, int graphic_file_div);
	private:
		std::pair<bool, int> set_effect_;
		std::tuple<bool, int, int> set_graphic_;
		NyaEffect* nya_effect_;
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		static std::vector<DeviceSetting> setting_vector_;
		static std::list<Bullet> attack_list_[eOBJECT::GROUP::sizeof_enum];
		static std::list<Bullet> wait_list_;
		void Calculate(eOBJECT::GROUP group);
		double RadToAngle(double x) { return (x * 180.0 / 3.14159); }
		double AngleToRad(double x) { return (x * 3.14159 / 180.0); }
	};

}
