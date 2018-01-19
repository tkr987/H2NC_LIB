#pragma once


#include "NyaDefine.h"
#include <list>


namespace H2NLIB {

	struct GraphicPropertyX4;
	struct PositionPropertyX;
	class NyaGraphic;
	class NyaPosition;
	class NyaString;

	struct Bullet {
		double draw_angle_;
		double draw_rotate_;
		int limit_min_x_;
		int limit_max_x_;
		int limit_min_y_;
		int limit_max_y_;
		double move_angle_;
		double move_x_;
		double move_y_;
		PositionPropertyX* ppx_;
	};

	struct AttackPropertyX {
		double collision_pow_;				//!< UŒ‚—Í
		double collision_range_;			//!< Õ“Ë”ÍˆÍ
		double create_x_;					//!< ¶¬xÀ•W
		double create_y_;					//!< ¶¬yÀ•W	
		double graphic_angle_;				//!< ‰æ‘œŠp“x(ƒ‰ƒWƒAƒ“)
		double graphic_rotate_;				//!< ‰æ‘œ‰ñ“]Šp“x
		double move_angle_;					//!< ˆÚ“®Šp“x
		double move_speed_;					//!< ˆÚ“®‘¬“x
	};

	class NyaAttack {
	public:
		NyaAttack();
		~NyaAttack();
		void Create(AttackPropertyX*);
		void SettingEffect(void);
		void SettingGraphic(int file_id, int file_div);
		void SettingGroup(eOBJECT::GROUP);
		void Init(int);
		void Run(void);
	private:
		eOBJECT::GROUP setting_group_;
		GraphicPropertyX4* gpx4_setting_graphic_;
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		NyaString* nya_string_;
		static std::list<Bullet> create_list_[eOBJECT::GROUP::sizeof_enum];
		static std::list<Bullet> wait_list_;
		void Calculate(eOBJECT::GROUP group);
		double RadToAngle(double x) { return (x * 180.0 / 3.1415); }
		double AngleToRad(double x) { return (x * 3.1415 / 180.0); }
	};

}
