#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	// *******************************************************************
	//  Target4Retro
	//  初期座標と移動速度、移動角度、レベルをコンストラクタに入力
	//  移動角度は-90から270の範囲
	//  自機狙い 2wave * (3num + rank) の攻撃
	// *******************************************************************

	class Target4Retro :  public TargetBase {
	private:
		// アクション変数
		double act11_move_speed_;
		double act11_move_angle_;
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
		Target *cube_[2];
		Target *main_;
		// パラメータ
		NH2::ArmsParam1 *aparam_main_;
		NH2::EffectParam1b *eparam_death_;
		void Act11_Move(void);
		void Act11_ShotHard(void);
		void Collision(void);
		void Delete(double scale, bool effect, bool sound);
		void Draw(void);
	public:
		Target4Retro(double start_posx, double start_posy, double move_speed, double move_angle, int lv);
		~Target4Retro();
		void Run(void);
	};

}

