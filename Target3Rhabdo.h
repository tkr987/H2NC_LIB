#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	// ****************************************************
	//  Target3Rhabdo
	//  初期座標とレベルをコンストラクタに入力
	//  移動なし
	//  5waveの攻撃
	// ****************************************************

	class Target3Rhabdo :  public TargetBase {
	private:
		int action_;
		int count_frames_;
		int lv_;
		bool delete_flag_;
		double health_;
		double move_speed_;
		double quadratic_a_;
		double quadratic_vx_;
		double quadratic_vy_;
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
		int soundfile_bomb_;
		int soundfile_lock_;
		Target *cube_[2];
		Target *main_;
		NH2::ArmsParam1 *aparam_;
		NH2::EffectParam1b *eparam_death_;
		void Attack1Hard(void);
		void AttackNormal(void);
		void Collision(void);
		void Delete(double scale, bool effect, bool sound);
		void Draw(void);
		void Move1(void);
		// 二次関数の計算 a = 比例定数, vx = 頂点X座標, vy = 頂点Y座標
		double QuadraticFunction(double posx, double a, double vx, double vy) { return a * (posx - vx) * (posx - vx) + vy; }
	public:
		Target3Rhabdo(double start_posx, double start_posy, int lv);
		~Target3Rhabdo();
		void Run(void);
	};

}

