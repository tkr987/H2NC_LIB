#pragma once

#include <list>
#include "NyaDefine.h"

using namespace std;


namespace H2NLIB {


	// �e�I�u�W�F�N�g�𐶐�����N���X

	struct ShotToken {

		//������

		//bool hit_effect_;
		//double img_angle_;
		//int img_id_;
		//double img_rotate_;
		//double plus_x_;
		//double plus_y_;
		//double pos_range_;
		//int wait_frames_;
		//EffectParam1 *eparam_;
		//PosParam1 *pparam_;
	};

	struct DevicePropertyX {
		double img_angle_;						//!< �摜�p�x(���W�A��, �����l0)
		int img_id_;							//!< �摜ID(�����l�s��)
		double img_rotate_;						//!< �摜��]�p�x(�����l0)
		double shot_angle_;						//!< �p�x(�����l�s��)
		double shot_pow_;						//!< �U����(�����l0)
		double shot_range_;						//!< �����蔻��͈̔�(�����l0)
		double shot_speed_;						//!< ���x(�����l�s��)
		unsigned int shot_wait_;				//!< �ҋ@�t���[����(�����l0)
		double shot_x_;							//!< ����x���W(�����l�s��)
		double shot_y_;							//!< ����y���W(�����l�s��)
		bool hit_effect_;						//!< �q�b�g�G�t�F�N�g(true = on, false = off, �����lfalse)
		int hit_effect_img_divmax_;				//!< �q�b�g�G�t�F�N�g�摜�����ő�l(�����l�s��)
		int hit_effect_img_divmin_;				//!< �q�b�g�G�t�F�N�g�摜�����ŏ��l(�����l0)
		int hit_effect_img_id_;					//!< �q�b�g�G�t�F�N�g�摜ID(�����l�s��)
		int hit_effect_img_interval_;			//!< �q�b�g�G�t�F�N�g�摜�؂�ւ��C���^�[�o������(�����l�s��)
		double hit_effect_img_extend_rate_;		//!< �q�b�g�G�t�F�N�g�摜�g�嗦(�����l1.0�{)
		DevicePropertyX(){
			img_angle_ = 0.0;
			img_rotate_ = 0.0;
			shot_pow_ = 0.0;
			shot_range_ = 0.0;
			shot_wait_ = 0;
			hit_effect_ = false;
			hit_effect_img_divmin_ = 0;
			hit_effect_img_extend_rate_ = 1.0;
		}
	};

	class Device {
	public:
		Device();
		~Device();
		void Run(void);
	private:
		static std::list<ShotToken> list_unused_;
		static std::list<ShotToken> list_used_[eOBJECT::GROUP::sizeof_enum];
		static std::list<ShotToken> list_wait_[eOBJECT::GROUP::sizeof_enum];
		int UserAttack(DevicePropertyX *dpx);
	};

}
