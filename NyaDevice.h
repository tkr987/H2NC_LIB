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
		double draw_extend_;
		double draw_rotate_;
		double collision_pow_;
		double collision_range_;
		eOBJECT::GROUP object_group_;
	};

	struct DevicePropertyX {
		double create_x_;					//!< ¶¬xÀ•W
		double create_y_;					//!< ¶¬yÀ•W	
		double draw_angle_;					//!< •`‰æŠp“x
		double move_angle_;					//!< ˆÚ“®Šp“x
		double move_speed_;					//!< ˆÚ“®‘¬“x
		int device_setting_id_;				//!< NyaDevice‚ÌÝ’èID
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
