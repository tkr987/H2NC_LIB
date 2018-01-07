#pragma once

#include "TargetBase.h"

namespace NH2 {
	struct ArmsParam;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	class Target1Erythro :  public TargetBase {
	private:
		// image file
		int imgdiv_cube_;
		int imgdiv_main_;
		int imgfile_arms_main_;
		int imgfile_arms_cube_;
		int imgfile_death_;
		int imgfile_cube_;
		int imgfile_cube_lock_;
		int imgfile_main_;
		int imgfile_main_lock_;
		int imgfile_main_shadow_;
		// sound file
		int soundfile_death_;
		int soundfile_lock_;
		// その他
		int cube_max_;
		int phase_;
		int frames_;
		int lv_;
		double health_;
		double end_posy_;
		double act11_move_speed_;
		double act13_shot_angle_r_;
		double act13_shot_angle_l_;
		double act15_move_speed_;
		// ターゲット、パラメータ
		Target *main_;
		Target *cube_[2];
		NH2::ArmsParam1 *aparam_cube_;
		NH2::ArmsParam1 *aparam_main_;
		NH2::EffectParam1b *eparam_death_;
		void Act13_ShotHard(void);
		void Act13_ShotHardR(void);
		void Act13_ShotHardL(void);
		void Collision(void);
		void Delete(double scale, bool effect, bool sound);
		void Act11_Move(void);
		void Act15_Move(void);
	public:
		Target1Erythro(double start_posx, double end_posy, int lv);
		~Target1Erythro();
		void Action(void);
		void Draw(void);
	};

}

