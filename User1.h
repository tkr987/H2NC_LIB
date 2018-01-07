#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1;
	struct ImgParam4;
	struct ImgParam4b;
	class PosParam1;
}


class User1 {
private:
	// 画像ファイル
	int imgdiv_main_;
	int imgdiv_sub_;
	int imgfile_arms1a;
	int imgfile_arms1b;
	int imgfile_death_;
	int imgfile_dot_;
	int imgfile_exarms_;
	int imgfile_effect_arms_;
	int imgfile_effect_exarms_;
	int imgfile_exeffect1_;
	int imgfile_exeffect2_;
	int imgfile_exeffect3_;
	int imgfile_sub_;
	int imgfile_user1a_;
	int imgfile_user1b_;
	// サウンドファイル
	int soundfile_arms_;
	int soundfile_death_;
	int soundfile_exstart_;
	// その他 変数
//	int effect_arms_;
//	int effect_exarms_;
	int invincible_frames_;
	int posid_main_;
	double sync_movecount_;
	NH2::ArmsParam1 *aparam_;
	NH2::ArmsParam1 *aparam_ex_;
	NH2::EffectParam1 *eparam_death_;
	NH2::ImgParam4b *iparam_exeffect1_;
	NH2::ImgParam4b *iparam_exeffect2_;
	NH2::ImgParam4 *iparam_exeffect3a_;
	NH2::ImgParam4 *iparam_exeffect3b_;
	NH2::ImgParam4 *iparam_main_;
	NH2::ImgParam4b *iparam_main_invincible_;
	NH2::ImgParam4 *iparam_sub_;
	NH2::PosParam1 *pparam_;
	void Attack1(void);
	void AttackEx1(void);
	void Attack2(void);
	void AttackEx2(void);
	void Attack3(void);
	void AttackEx3(void);
	void Collision(void);
//	void Delete(void);
	void Draw1(void);
	void Draw2(void);
	void Draw3(void);
	void DrawInvincible(void);
	void Move(void);
	// 便利そうな関数
	static double CalcAngle(double x) { return (x * 180.0 / 3.1415); }
	static double CalcRAD(double x) { return (x * 3.1415 / 180.0); }
public:
	User1();
	~User1();
	void Run(void);
	void Clear(void);
};

