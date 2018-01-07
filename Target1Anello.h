#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	class Target1Anello :  public TargetBase {
	public:
		Target1Anello(double start_posx, double start_posy, int lv = 0);
		~Target1Anello();
		void Action(void);
		void Draw(void);
	private:
		// image 変数
		int imgdiv_main_;
		int imgfile_arms_;
		int imgfile_death_;
		int imgfile_main_;
		int imgfile_main_lock_;
		// sound 変数
		int soundfile_death_;
		int soundfile_lock_;
		// その他 変数
		int frames_;
		double health_;
		int lv_;
		int phase_;
		// ターゲット
		Target *main_;
		// パラメータ
		NH2::ArmsParam1 *aparam_main_;
		NH2::EffectParam1b *eparam_death_;
		void ShotHard(void);
		void Collision(void);
		void Delete(double scale, bool effect, bool sound);
		void Move(void);
	};

}

