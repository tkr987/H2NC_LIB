#pragma once
#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1;
	struct EffectParam1b;
}


namespace NH2T {

	class Target;

	class Boss3OXA48 :  public TargetBase {
	private:
		int action_;
		bool end_flag_;
		double health_;
		double health_max_;
		int frames_;
		int lv_;
		double act1_shot1_angleL_;
		double act1_shot1_angleR_;
		double act1_shot2_angleL_;
		double act1_shot2_angleR_;
		double act3_move_angle_;
		double act5_cristal_movex_[12];
		double act5_cristal_movey_[12];
		double act5_main_movex_;
		double act6_main_movex_;
		double act7_cristal_movex_[12];
		double act7_cristal_movey_[12];
		double act7_main_movex_;
		double act8_main_movex_;
		double act10_cristal2_movex_[2];
		double act10_cristal2_movey_[2];
		int imgdiv_cristal_;
		int imgdiv_main_;
		int imgfile_arms_blue16t_;
		int imgfile_arms_blue32t_;
		int imgfile_arms_red20t_;
		int imgfile_cristal_red_;
		int imgfile_cristal_black_;
		int imgfile_cristal_lock_;
		int imgfile_death_cristal_;
		int imgfile_death_main_;
		int imgfile_main_;
		int imgfile_main_lock_;
		int soundfile_death_cristal_;
		int soundfile_lock_;
		int effectset_death_;
		Target *main_;
		Target *cristal_[12];
		Target *cristal2_[2];
		NH2::ArmsParam1 *aparam_act1_cristal_;
		NH2::ArmsParam1 *aparam_act1_main_;
		NH2::ArmsParam1 *aparam_act3_cristal_;
		NH2::ArmsParam1 *aparam_act4_cristal_;
		NH2::ArmsParam1 *aparam_act6_cristal_;
		NH2::ArmsParam1 *aparam_act6_main_;
		NH2::ArmsParam1 *aparam_act11_cristal_;
		NH2::EffectParam1 *eparam_death_cristal_;
		NH2::EffectParam1b *eparam_death_main_;
	public:
		Boss3OXA48(double y, int lv);
		~Boss3OXA48();
		void Run(void);
		void Collision1(void);
		void Collision2(void);
		void Act0_SetPosition(void);
		void Act1_Move(void);
		void Act2_ShotHard1(void);
		void Act2_ShotHard2(void);
		void Act2_ShotHard3(void);
		void Act4_ShotHard(void);
		void Act5_ShotHard(void);
		void Act6_Move(void);
		void Act7_ShotHard1(void);
		void Act7_ShotHard2(void);
		void Act7_ShotHard3(void);
		void Act7_Move(void);
		void Act8_Move(void);
		void Act12_ShotHard1(void);
		void Act12_ShotHard2(void);
		void DeleteCristal(double scale, bool effect, bool sound);
		void DeleteCristal2(double scale, bool effect, bool sound);
		void DeleteMain(double scale, bool effect, bool sound);
		void Draw1(void);
		void Draw2(void);
	};

}
