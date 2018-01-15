#pragma once

#include "NyaDefine.h"
#include "NyaGraphic.h"
#include "NyaPosition.h"
#include <list>


namespace H2NLIB {

	struct Bullet {
		double move_angle_;
		double move_x_;
		double move_y_;
		GraphicPropertyX4 gpx4_;
		PositionPropertyX ppx_;
	};

	struct AttackPropertyX {
		double create_x_;					//!< ����x���W
		double create_y_;					//!< ����y���W	
		double graphic_angle_;				//!< �摜�p�x(���W�A��)
		double graphic_rotate_;				//!< �摜��]�p�x
		double move_angle_;					//!< �ړ��p�x
		double move_speed_;					//!< �ړ����x
		eOBJECT::GROUP object_group_;		//!< �I�u�W�F�N�g�O���[�v
	};

	class NyaAttack {
	public:
		NyaAttack();
		~NyaAttack();
		void Create(AttackPropertyX*);
		void SettingBullet(eOBJECT::GROUP, double, double);
		void SettingEffect(void);
		void SettingGraphic(eOBJECT::GROUP, int, int);
		void Init(int);
		void Run(void);
		static std::list<Bullet> create_list_[eOBJECT::GROUP::sizeof_enum];
		static std::list<Bullet> wait_list_;
	private:
		double RadToAngle(double x) { return (x * 180.0 / 3.1415); }
		double AngleToRad(double x) { return (x * 3.1415 / 180.0); }
	};

}
