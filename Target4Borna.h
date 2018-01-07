#pragma once

#include "TargetBase.h"


namespace NH2 {
	struct ArmsParam1;
	struct EffectParam1b;
}

namespace NH2T {

	class Target;

	// *******************************************************************
	//  Target4Caulimo
	//  �������W�ƈړ����x�A���x�����R���X�g���N�^�ɓ���
	//  4way
	//  ���@�_�� 2wave * (3num + rank) �̍U��
	// *******************************************************************

	class Target4Borna :  public TargetBase {
	private:
		// image �ϐ�
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
		// sound �ϐ�
		int soundfile_death_;
		int soundfile_lock_;
		// ���̑� �ϐ�
		int action_;
		int frames_;
		double health_;
		int lv_;
		// �^�[�Q�b�g
		Target *cube_[8];
		Target *main_;
		// �p�����[�^
		NH2::ArmsParam1 *aparam_cube_;
		NH2::ArmsParam1 *aparam_main_;
		NH2::EffectParam1b *eparam_death_;
		void Act11_Move(void);
		void Act12_MainShotHard(double shot_frames, double base_angle);
		void Act11_ShotHard(void);
		void Collision1(void);
		void Delete(double scale, bool effect, bool sound);
		void Draw(void);
	public:
		Target4Borna(double start_posx, double start_posy, int lv);
		~Target4Borna(void);
		void Run(void);
	};

}

