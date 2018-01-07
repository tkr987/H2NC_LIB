#pragma once

#include "TargetBase.h"

namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1b;
	struct ImgParam1;
	struct ImgParam4;
}


namespace NH2T {

	class Target;

	class Target3Asfar :  public TargetBase {
	private:
		int action_;
		int count_;
		int lv_;
		bool delete_flag_;
		double cube_angle_;
		double damage_;
		double move_angle_;
		double move_speed_;
		int imgdiv_cube_;
		int imgdiv_main_;
		int imgfile_arms_;
		int imgfile_cube_;
		int imgfile_cube_lock_;
		int imgfile_death_;
		int imgfile_main_;
		int imgfile_main_lock_;
		int soundfile_death_;
		int soundfile_lock_;
		Target *cube_;
		Target *main_;
		NH2::ArmsParam1 *aparam_;
		NH2::EffectParam1b *eparam_death_;
		NH2::ImgParam1 *iparam1_;
		NH2::ImgParam4 *iparam4_;
		void AttackHard(void);
		void AttackNormal(void);
		void Collision(void);
		void Delete(void);
		void Draw(void);
		void Move(void);
	public:
		Target3Asfar(double start_posx, double start_posy, double move_angle, double move_speed, int lv);
		~Target3Asfar(void);
		void Run(void);
	};

}

