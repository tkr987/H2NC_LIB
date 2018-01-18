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
		void SettingBullet(eOBJECT::GROUP object_group, double pow, double range, int limit_min_x, int limit_max_x, int limit_min_y, int limit_max_y);
		void SettingCollision(int collision_type, eOBJECT::GROUP group1, eOBJECT::GROUP group2);
		void SettingEffect(void);
		void SettingGraphic(eOBJECT::GROUP object_group, int file_id, int file_div, double extend_rate, bool flag_trans, bool flag_turn);
		void Init(int);
		void Run(void);
	private:
		GraphicPropertyX4* gpx4_bullet_;
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
