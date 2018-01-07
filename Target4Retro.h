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
	//  �������W�ƈړ����x�A�ړ��p�x�A���x�����R���X�g���N�^�ɓ���
	//  �ړ��p�x��-90����270�͈̔�
	//  ���@�_�� 2wave * (3num + rank) �̍U��
	// *******************************************************************

	class Target4Retro :  public TargetBase {
	private:
		// �A�N�V�����ϐ�
		double act11_move_speed_;
		double act11_move_angle_;
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
		Target *cube_[2];
		Target *main_;
		// �p�����[�^
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

