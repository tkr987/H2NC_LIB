#pragma once

#include "TargetBase.h"

namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	class Target1Virga :  public TargetBase {
	public:
		Target1Virga(double x, double y, int lv);
		~Target1Virga();
		void Draw(void);
		void Action(void);
	private:
		// image file
		int imgdiv_main_;
		int imgfile_arms_main_;
		int imgfile_death_;
		int imgfile_main_;
		int imgfile_main_lock_;
		// sound file
		int soundfile_death_;
		int soundfile_lock_;
		// ÇªÇÃëº ïœêî
		int attack_count_;
		int frames_;
		double health_;
		int lv_;
		int phase_;
		Target *main_;
		NH2::ArmsParam1 *aparam_main_;
		NH2::EffectParam1b *eparam_death_;
		void Attack(void);
		void Collision(void);
		void Delete(double scale, bool effect, bool sound);
	};

}
