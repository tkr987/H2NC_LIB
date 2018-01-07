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

	class Target1Picorna :  public TargetBase {
	public:
		Target1Picorna(double start_posx, double start_posy, int lv);
		~Target1Picorna();
		void Draw(void);
		void Action(void);
	private:
		// image file
		int imgfile_arms_main_;
		int imgfile_death_;
		int imgfile_main_;
		int imgfile_main_lock_;
		// sound file
		int soundfile_death_;
		int soundfile_lock_;
		// ÇªÇÃëº ïœêî
		int frames_;
		double health_;
		int lv_;
		int phase_;
		double draw_angle_;
		Target *main_;
		NH2::ArmsParam1 *aparam_main_;
		NH2::ArmsParam1 *aparam_cube_;
		NH2::EffectParam1b *eparam_death_;
		void Collision(void);
		void Delete(double scale, bool effect, bool sound);
		void Move(void);
	};

}

