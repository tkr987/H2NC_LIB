#pragma once


#include "NyaDefine.h"
#include <list>
#include <vector>


namespace H2NLIB {

	struct GraphicPropertyX4;
	struct PositionPropertyX;
	class NyaGraphic;
	class NyaPosition;

	struct Bullet {
		double draw_angle_;
		double draw_rotate_;
		double move_angle_;
		double move_x_;
		double move_y_;
		int setting_id_;
		PositionPropertyX* ppx_;
	};

	struct DeviceSetting {
		int graphic_id_;
		int graphic_div_;
		double graphic_extend_;
		double graphic_rotate_;
		bool graphic_trans_;
		bool graphic_turn_;
		double position_collide_pow_;
		double position_collide_range_;
		eOBJECT::GROUP object_group_;
	};

	struct DevicePropertyX {
		double create_x_;					//!< ¶¬xÀ•W
		double create_y_;					//!< ¶¬yÀ•W	
		double draw_angle_;					//!< •`‰æŠp“x
		double move_angle_;					//!< ˆÚ“®Šp“x
		double move_speed_;					//!< ˆÚ“®‘¬“x
		int setting_id_;
	};

	class NyaDevice {
	public:
		NyaDevice();
		~NyaDevice();
		void Attack(DevicePropertyX* dpx);
		int LoadSetting(DeviceSetting* setting);
		void Run(void);
	private:
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		static std::vector<DeviceSetting> setting_vector_;
		static std::list<Bullet> create_list_[eOBJECT::GROUP::sizeof_enum];
		static std::list<Bullet> wait_list_;
		void Calculate(eOBJECT::GROUP group);
		double RadToAngle(double x) { return (x * 180.0 / 3.1415); }
		double AngleToRad(double x) { return (x * 3.1415 / 180.0); }
	};

}
