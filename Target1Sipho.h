#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	class Target1Sipho :  public TargetBase {
	public:
		Target1Sipho(double start_posx, double end_posy, int lv);
		~Target1Sipho();
		void Action(void);
		void Draw(void);
	private:
		// image �ϐ�
		int imgdiv_cube_;
		int imgdiv_main_;
		int imgfile_arms_cube_;
		int imgfile_death_;
		int imgfile_cube_;
		int imgfile_cube_lock_;
		int imgfile_main_;
		int imgfile_main_lock_;
		// sound �ϐ�
		int soundfile_death_;
		int soundfile_lock_;
		// ���̑� �ϐ�
		int phase_;
//		int arms_count_;
		int frames_;
		int lv_;
		double health_;
		double end_posy_;
		int max_cube_;
		double move_speed_;
		// �^�[�Q�b�g
		Target *cube_[4];
		Target *main_;
		// �p�����[�^
		NH2::ArmsParam1 *aparam_cube_;
		NH2::EffectParam1b *eparam_death_;
		void ShotHard(void);
		void Collision(void);
		void Delete(double scale, bool effect, bool sound);
		void Move1(void);
		void Move2(void);
	};

}

