#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	class Boss1MRAB :  public TargetBase {
	public:
		Boss1MRAB(double x, double y, int lv);
		~Boss1MRAB();
		void Action(void);
		void Draw(void);
	private:
		int frames_;
		double health_;
		double health_max_;
		int lv_;
		int phase_;
		double act21_shot_angle_;
		double act23_move_angle_;
		int imgdiv_cristal_;
		int imgdiv_main_;
		int imgfile_arms_orange20t_;
		int imgfile_arms_red16t_;
		int imgfile_arms_red20t_;
		int imgfile_cristal_orange_;
		int imgfile_cristal_red_;
		int imgfile_cristal_lock_;
		int imgfile_death_cristal_;
		int imgfile_death_main_;
		int imgfile_main_;
		int imgfile_main_lock_;
		int soundfile_death_cristal_;
		int soundfile_death_main_;
		int soundfile_lock_;
		int effectset_death_;
		Target *main_;
		Target *cristal_orange_[2];
		Target *cristal_red_[2];
		NH2::ArmsParam1 *aparam_cristal_;
		NH2::ArmsParam1 *aparam_act21_cristal_;
		NH2::ArmsParam1 *aparam_act23_cristal_orange_;
		NH2::ArmsParam1 *aparam_act23_cristal_red_;
		NH2::ArmsParam1 *aparam_act41_main_;
		NH2::EffectParam1b *eparam_death_cristal_;
		NH2::EffectParam1b *eparam_death_main_;
		void Act11_Move(void);
		void Act21_ShotHard1(void);
		void Act21_ShotHard2(void);
		void Act23_Move(void);
		void Act23_ShotHard(void);
		void Act31_Delete(void);
		void Act41_ShotHard(void);
		void Act51_Delete(void);
		void Collision1(void);
		void Collision2(void);
		void Collision3(void);
//		void Delete1(void);
	};

}

