#pragma once

#include "TargetBase.h"

namespace NH2 {
	struct ArmsParam;
	struct EffectParam1;
}

namespace NH2T {

	class Target;

	class Target0Sample : public TargetBase {
	private:
		int action_;
		int arms_count_;
		int frames_;
		int lv_;
		bool delete_flag_;
		double damage_;
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
		int soundfile_bomb_;
		int soundfile_lock_;
		int effectset_death_;
		Target *main_;
		NH2::EffectParam1 *eparam_death_;
		void Collision(void);
		void Delete(void);
		void Draw(void);
	public:
		Target0Sample(double posx, double posy, int lv);
		~Target0Sample();
		void Run(void);
	};

}
