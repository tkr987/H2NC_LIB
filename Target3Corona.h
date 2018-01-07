#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	class Target3Corona :  public TargetBase {
	private:
		int action_;
		double angle_cube_[4];
		bool angle_reverse_;
		int count_;
		int lv_;
		bool delete_flag_;
		double damage_;
		double start_posx_;
		double start_posy_;
		double end_posx_;
		double end_posy_;
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
		void AttackHard(void);
		void AttackNormal(void);
		void Collision(void);
		void Delete(void);
		void Draw(void);
		void Move(void);
	public:
		Target3Corona(double start_posx, double start_posy, bool reverse, int lv);
		~Target3Corona();
		void Run(void);
	};

}

