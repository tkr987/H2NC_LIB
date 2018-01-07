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

	// *********************************************************
	//  Target4Denso
	//  初期x座標と終端y座標、レベルをコンストラクタに入力
	//  攻撃1: 自機狙い 1way * (5shot + rank) * 4cube
	//  攻撃2: 自機狙い 7way
	// *********************************************************

	class Target1Denso :  public TargetBase {
	public:
		Target1Denso(double start_posx, double end_posy, int lv);
		~Target1Denso();
		void Action(void);
		void Draw(void);
	private:
		int frames_;
		double health_;
		int lv_;
		int max_cube_;
		int phase_;
		double act11_end_position_y_;
		double act11_move_speed_;
		double act13_move_angle_;
		double act13_move_speed_;
		int imgdiv_main_;
		int imgdiv_main_shadow_;
		int imgdiv_cube_;
		int imgfile_arms_cube_;
		int imgfile_arms_main_;
		int imgfile_death_;
		int imgfile_cube_;
		int imgfile_cube_lock_;
		int imgfile_main_;
		int imgfile_main_lock_;
		int soundfile_death_;
		int soundfile_lock_;
		Target *main_;
		Target *cube_[2];
		NH2::ArmsParam1 *aparam_main_;
		NH2::ArmsParam1 *aparam_cube_;
		NH2::EffectParam1b *eparam_death_;
		void Act11_Move(void);
		void Act13_Move(void);
		void Collision(void);
		void Delete(double scale, bool effect, bool sound);
		void ShotCubeHard(void);
		void ShotMainHard(void);
	};

}

