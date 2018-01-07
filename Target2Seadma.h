#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	class Target2Seadma :  public TargetBase {
	private:
		int action_;
		int arms_count_;
		int frames_;
		int lv_;
		bool delete_flag_;
		double damage_;
		double start_posx_;
		double start_posy_;
		double end_posx_;
		double end_posy_;
		double move_speed_;
		int imgdiv_cube_;
		int imgdiv_main_;
		int imgdiv_main_shadow_;
		int imgfile_arms_cube_;
		int imgfile_arms_main_;
		int imgfile_death_;
		int imgfile_cube_;
		int imgfile_cube_lock_;
		int imgfile_main_;
		int imgfile_main_lock_;
		int imgfile_main_shadow_;
		int soundfile_death_;
		int soundfile_lock_;
		Target *cube1_;
		Target *cube2_;
		Target *cube3_;
		Target *cube4_;
		Target *main_;
		NH2::ArmsParam1 *aparam_cube_;
		NH2::EffectParam1b *eparam_death_;
		void Attack(int interval);
		void Collision(void);
		void Delete(void);
		void Draw(void);
		void Move1(void);
		void Move2(void);
	public:
		Target2Seadma(double start_posx, double end_posy, int lv);
		~Target2Seadma();
		void Run(void);
	};

}

