#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	class Target3Arena :  public TargetBase {
	private:
		int action_;
		int count_frames_;
		int lv_;
		bool delete_flag_;
		double health_;
		double move_speed_;
		double speed_down_value_;
		double speed_up_value_;
		int imgdiv_cube_;
		int imgdiv_main_;
		int imgdiv_main_shadow_;
		int imgfile_arms_cube_;
		int imgfile_arms_main_;
		int imgfile_cube_;
		int imgfile_cube_lock_;
		int imgfile_death_;
		int imgfile_main_;
		int imgfile_main_lock_;
		int imgfile_main_shadow_;
		int soundfile_bomb_;
		int soundfile_lock_;
		Target *cube_[4];
		Target *main_;
		NH2::ArmsParam1 *aparam_;
		NH2::EffectParam1b *eparam_death_;
		void Attack1Hard(void);
		void Attack2Hard(void);
		void AttackNormal(void);
		void Collision(void);
		void Delete(double scale, bool effect, bool sound);
		void Draw(void);
		void Move1(void);
		void Move2(void);
	public:
		Target3Arena(double start_posx, double start_posy, double move_speed, double move_time, int lv);
		~Target3Arena();
		void Run(void);
	};

}

