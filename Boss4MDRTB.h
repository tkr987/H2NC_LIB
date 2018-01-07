#pragma once
#include <list>
#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1;
	struct EffectParam1b;
}


namespace NH2T {

	class Target;

	struct Boss4Cube {
		double health_;
		Target *target_;
	};

	class Boss4MDRTB :  public TargetBase {
	private:
		// action 変数
		double act20_movex_1f_;
		double act20_movey_1f_;
		double act20_main_shot_angleL_;
		double act20_main_shot_angleR_;
		double act21_movex_1f_;
		double act21_movey_1f_;
		double act20_shot2_angleL_;
		double act20_shot2_angleR_;
		double act42_cristal_movey_[2];
		double act43_main_shot_angle_[2];
		double act51_cristal_movex_[16];
		double act51_cristal_movey_[16];
		double act51_main_movex_;
		double act51_main_movey_;
		double act52_cristal_movex_[16];
		double act52_cristal_movey_[16];
		int act52_shot_number_stack_[8];
		int act52_shot_time_;
		// image 変数
		int imgdiv_cristal_;
		int imgdiv_cube_;
		int imgdiv_main_;
		int imgfile_arms_blue16t_;
		int imgfile_arms_blue32t_;
		int imgfile_arms_green20t_;
		int imgfile_arms_purple20t_;
		int imgfile_arms_red16t_;
		int imgfile_arms_red20t_;
		int imgfile_arms_red26t_;
		int imgfile_arms_red30t_;
		int imgfile_cristal_green_;
		int imgfile_cristal_red_;
		int imgfile_cristal_black_;
		int imgfile_cube_blue_;
		int imgfile_death_cristal_;
		int imgfile_death_cube_;
		int imgfile_death_main_;
		int imgfile_main_;
		int imgfile_lock_cristal_;
		int imgfile_lock_cube_;
		int imgfile_lock_main_;
		// sound 変数
		int soundfile_death_cristal_;
		int soundfile_death_cube_;
		int soundfile_death_main_;
		int soundfile_lock_;
		// その他 変数
		int action_;
		bool end_flag_;
		double health_;
		double health_max_;
		int frames_;
		int lv_;
		// ターゲット
		Target *main_;
		Target *cristal1_[6];
		Target *cristalL_[12];
		Target *cristalR_[12];
		Target *cristal2_[2];
		Target *cristal3_[16];
		std::list<Boss4Cube*> cube_run_;
		std::list<Boss4Cube*> cube_wait_;
		// パラメータ
		NH2::ArmsParam1 *aparam_act20_cristal_;
		NH2::ArmsParam1 *aparam_act20_main_;
		NH2::ArmsParam1 *aparam_act21_cristal_;
		NH2::ArmsParam1 *aparam_act31_cube_;
		NH2::ArmsParam1 *aparam_act43_cristal_;
		NH2::ArmsParam1 *aparam_act43_main_;
		NH2::ArmsParam1 *aparam_act52_cristal_;
		NH2::ArmsParam1 *aparam_act52_main_;
		NH2::EffectParam1 *eparam_death_cristal_;
		NH2::EffectParam1 *eparam_death_cube_;
		NH2::EffectParam1b *eparam_death_main_;
	public:
		Boss4MDRTB(double y, int lv);
		~Boss4MDRTB();
		void Run(void);
		void Act10_SetPosition(void);
		void Act11_Move(void);
		void Act20_MainMove(void);
		void Act20_CristalShotHard(void);
		void Act20_MainShotHard(void);
		void Act21_MainMove(void);
		void Act21_CristalShotHard(void);
		void Act22_Delete(void);
		void Act31_CubeCreate(void);
		void Act31_CubeDelete(void);
		void Act31_CubeShot(void);
		void Act32_CubeDeleteAll(void);
		void Act32_CubeShot(void);
		void Act41_CristalCreate(void);
		void Act42_CristalMove(void);
		void Act43_CristalShotHard(void);
		void Act43_MainShotHard1(void);
		void Act43_MainShotHard2(void);
		void Act44_CristalDelete(void);
		void Act50_CristalCreate(void);
		void Act51_CristalMove(void);
		void Act51_MainMove(void);
		void Act52_CristalMove(void);
		void Act52_CristalShotHard(void);
		void Act52_MainShotHard(double base_angle);
		void Act53_Delete(void);
		void Collision1(void);
		void Collision2(void);
		void Collision3(void);
		void Collision4(void);
		void Collision5(void);
		void Collision6(void);
		void Collision7(void);
		void Collision8(void);
		void Collision9(void);
		void Act31_CubeRun(void);
		void Draw1(void);
		void Draw2(void);
		void Draw3(void);
		void Draw4(void);
		void Draw5(void);
		void Draw6(void);
		void Draw7(void);
	};

}
