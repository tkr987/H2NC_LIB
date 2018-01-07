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
		// image �ϐ�
		int imgdiv_main_;
		int imgfile_arms_;
		int imgfile_death_;
		int imgfile_main_;
		int imgfile_main_lock_;
		// sound �ϐ�
		int soundfile_death_;
		int soundfile_lock_;
		// ���̑� �ϐ�
		int frames_;
		double health_;
		int lv_;
		int phase_;
		// �^�[�Q�b�g
		Target *main_;
		// �p�����[�^
		NH2::ArmsParam1 *aparam_main_;
		NH2::EffectParam1b *eparam_death_;
		void ShotHard(void);
		void Collision(void);
		void Delete(double scale, bool effect, bool sound);
		void Move(void);
	};

}

