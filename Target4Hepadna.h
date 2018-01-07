#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	// *******************************************************************
	//  Target4Hepadna
	//  初期座標と移動速度、移動角度、レベルをコンストラクタに入力
	//  攻撃1: (25 + rank) way * 4cube
	//  攻撃2: 3way (angle 90)
	// *******************************************************************

	class Target4Hepadna :  public TargetBase {
	private:
		// アクション変数
		double act11_move_speed_;
		// image 変数
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
		// sound 変数
		int soundfile_death_;
		int soundfile_lock_;
		// その他 変数
		int action_;
		int frames_;
		double health_;
		int lv_;
		// ターゲット
		Target *cube_[4];
		Target *main_;
		// パラメータ
		NH2::ArmsParam1 *aparam_cube_;
		NH2::ArmsParam1 *aparam_main_;
		NH2::EffectParam1b *eparam_death_;
		void Act11_Move(void);
		void Act12_MainShotHard(void);
		void Act12_CubeShotHard(void);
		void Collision1(void);
		void Collision2(void);
		void Delete(double scale, bool effect, bool sound);
		void Draw(void);
	public:
		Target4Hepadna(double start_posx, double start_posy, double move_speed, int lv);
		~Target4Hepadna(void);
		void Run(void);
	};

}

