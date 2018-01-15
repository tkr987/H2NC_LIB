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
		double create_x_;					//!< 生成x座標
		double create_y_;					//!< 生成y座標	
		double graphic_angle_;				//!< 画像角度(ラジアン)
		double graphic_rotate_;				//!< 画像回転角度
		double move_angle_;					//!< 移動角度
		double move_speed_;					//!< 移動速度
		eOBJECT::GROUP object_group_;		//!< オブジェクトグループ
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
