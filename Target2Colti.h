#pragma once

#include "TargetBase.h"

namespace NH2 {
	struct ArmsParam;
	struct EffectParam1b;
}


namespace NH2T {

	class Target;

	class Target2Colti :  public TargetBase {
	private:
		unsigned int action_;
		unsigned int frames_;
		unsigned int lv_;
		unsigned int rank_;
		bool delete_flag_;
		double damage_;
		double move_angle_;
		double move_speed_;
		int imgdiv_main_;
		int imgfile_death_;
		int imgfile_main_;
		int imgfile_main_arms_;
		int imgfile_main_lock_;
		int soundfile_delete_;
		int soundfile_lock_;
		Target *main_;
		NH2::ArmsParam1 *aparam_main_;
		NH2::EffectParam1b *eparam_death_;
		void Attack(double shot_speed);
		void Draw(void);
		void Collision(void);
		void Delete(void);
		void Move(void);
	public:
		Target2Colti(double start_posx, double start_posy, double move_angle, double move_speed, unsigned int lv);
		~Target2Colti(void);
		void Run(void);
	};

}

