#pragma once


#include <string>
#include <list>
#include "DefineNH.h"

namespace NH3 {
	class PosUpdater;
}


namespace NH2 {

	class PosManager;

	namespace ePOS {
		enum DIRECT { UP, RIGHT, DOWN, LEFT };
		enum LIMIT { MIN_X, MAX_X, MIN_Y, MAX_Y };
	};

	// ****************************************************
	//  class PosToken
	//  ���ۂ̍��W�f�[�^���i�[�����N���X
	//  class PosManager �� Postoken �f�[�^�W�����Ǘ�����
	// ****************************************************
	class PosToken {
		int id_;
		bool flag_collision_;
		bool flag_move_;
		double hit_;
		double pow_;
		double range_;
		double x_;
		double y_;
		std::string name_;
		friend class PosManager;
		friend class NH3::PosUpdater;
	};

	// ********************************************************************************************
	//  class PosParam1
	//  �����o�ϐ��̃C�e���[�^��ID�̂悤�Ȗ��������Ă���
	//  class PosManager �̃����o�֐����g���ăf�[�^�����o���Ƃ��ɗ��p����
	//  PosManager::Generate() ���g���Ƃ��́A�K�� PosParam1 �̃����o�֐��Œl���Z�b�g���邱��
	// ********************************************************************************************
	class PosParam1 {
	public:
		PosParam1(void) {
			pow_ = 0;
			range_ = 0;
		}
		void SetPow(double set_value) { pow_ = set_value; }
		void SetRange(double set_value) { range_ = set_value; }
		void SetStartX(double set_value) { start_x_ = set_value; }
		void SetStartY(double set_value) { start_y_ = set_value; }
	private:
		double pow_;					//!< �U����(�����l0)
		double range_;				//!< �����蔻��(�����l0)
		double start_x_;			//!< ����x���W(�����l�s��)
		double start_y_;			//!< ����y���W(�����l�s��)
		eOBJECT::GROUP group_;		//!< �I�u�W�F�N�g����(�����l�s��)
	private:
		std::list<PosToken>::iterator it_;
		friend class PosManager;
	};

	// *************************************************************
	//  class PosManager
	//  PosToken �̃f�[�^�W�����Ǘ�����N���X
	//  PosToken �̃f�[�^���擾����C���^�[�t�F�[�X�̖���
	// **************************************************************
	class PosManager {
	public:
		PosManager(void) {}
		virtual ~PosManager(void) {};
		// �������֘A
		static void Clear(void);
		static void End(void);
		// �����֐�
		static bool Generate(eOBJECT::GROUP set_group, PosParam1 *param);
		static bool Generate(eOBJECT::GROUP set_group, PosParam1 *param, std::string name);
		static void Delete(eOBJECT::GROUP group);
		static void Delete(PosParam1 *param);
		static int Delete_s(PosParam1 *param);
		// �p�����[�^�ݒ�֐�
		static void SetGroup(PosParam1 *param, eOBJECT::GROUP set_group);
		static void SetName(PosParam1 *param, std::string name);
		static void SetPosA(PosParam1 *param, double *x, double *y);
		static void SetPosB(eOBJECT::GROUP group, double *x, double *y);
		static void SetRange(PosParam1 *param, double set_value);
		// �ړ��֐�
		static double MoveAxisX(double move_value);
		static double MoveAxisY(double move_value);
		static void MovePosA(PosParam1 *param, double *add_x, double *add_y);
		static void MovePosB(PosParam1 *param, double angle, double dist);
		static void MovePosC(eOBJECT::GROUP group, double *px, double *py);
		static bool MoveSwingX(int scale, int time);
		static bool MoveSwingY(int scale, int time);
		// �����v�Z�֐�
		static double GetAtan(PosParam1 *param, eOBJECT::GROUP group, std::string name);
		static double CalcDiffDistance(PosParam1 *param, eOBJECT::GROUP group, std::string name);
		// ���擾�֐�
		static double GetHit(PosParam1 *param) { return param->it_->hit_; }
		static void GetHit(PosParam1 *param, double *return_value) { *return_value = param->it_->hit_; }
		static void GetPos(eOBJECT::GROUP group, std::string name, int *x, int *y);
		static void GetPos(eOBJECT::GROUP group, std::string name, double *x, double *y);
		static void GetPos(PosParam1 *param, int *return_x, int *return_y);
		static void GetPos(PosParam1 *param, double *return_x, double *return_y);
		static void GetPosX(PosParam1 *param, int *return_x) { *return_x = (int)param->it_->x_; }
		static void GetPosY(PosParam1 *param, int *return_y) { *return_y = (int)param->it_->y_; }
		static void GetPosX(PosParam1 *param, double *return_x) { *return_x = param->it_->x_; }
		static void GetPosY(PosParam1 *param, double *return_y) { *return_y = param->it_->y_; }
		static void GetAbsolutePanelCenterX(int *return_value) { *return_value = 384; }
		static void GetAbsolutePanelCenterX(double *return_value) { *return_value = 384.0; }
		static void GetAbsolutePanelMaxX(int *return_value) { *return_value = 608; }
		static void GetAbsolutePanelMaxX(double *return_value) { *return_value = 608.0; }
		static void GetAbsolutePanelMaxY(int *return_value) { *return_value = 576; }
		static void GetAbsolutePanelMaxY(double *return_value) { *return_value = 576.0; }
		static void GetAbsolutePanelMinX(int *return_value) { *return_value = 160; }
		static void GetAbsolutePanelMinX(double *return_value) { *return_value = 160.0; }
		static void GetAbsolutePanelMinY(int *return_value) { *return_value = 32; }
		static void GetAbsolutePanelMinY(double *return_value) { *return_value = 32.0; }
		static void GetAbsoluteMapMinX(int *return_value) { *return_value = -100; }
		static void GetAbsoluteMapMinX(double *return_value) { *return_value = -100.0; }
		static void GetAbsoluteMapMaxX(int *return_value) { *return_value = 708; }
		static void GetAbsoluteMapMaxX(double *return_value) { *return_value = 708.0; }
		static void GetRelativeMapCenterX(int *return_value) { *return_value = 384 + (int)axis_x_; }
		static void GetRelativeMapCenterX(double *return_value) { *return_value = 384.0 + axis_x_; }
		static void GetRelativeMapCenterY(int *return_value) { *return_value = 400 + (int)axis_x_; }
		static void GetRelativeMapCenterY(double *return_value) { *return_value = 400.0 + axis_x_; }
		static void GetRelativeMapMinX(int *return_value) { *return_value = 60 + (int)axis_x_; }
		static void GetRelativeMapMinX(double *return_value) { *return_value = 60.0 + axis_x_; }
		static void GetRelativeMapMinY(int *return_value) { *return_value = 0 + (int)axis_y_; }
		static void GetRelativeMapMinY(double *return_value) { *return_value = 0.0 + axis_y_; }
		static void GetRelativeMapMaxX(int *return_value) { *return_value = 708 + (int)axis_x_; }
		static void GetRelativeMapMaxX(double *return_value) { *return_value = 708.0 + axis_x_; }
		static void GetRelativeMapMaxY(int *return_value) { *return_value = 800 + (int)axis_y_; }
		static void GetRelativeMapMaxY(double *return_value) { *return_value = 800.0 + axis_y_; }
		static void GetRelativePanelCenterX(int *return_value) { *return_value = 384 + (int)axis_x_; }
		static void GetRelativePanelCenterX(double *return_value) { *return_value = 384.0 + axis_x_; }
		static void GetRelativePanelMaxX(int *return_value) { *return_value = 608 + (int)axis_x_; }
		static void GetRelativePanelMaxX(double *return_value) { *return_value = 608.0 + axis_x_; }
		static void GetRelativePanelMaxY(int *return_value) { *return_value = 576 + (int)axis_y_; }
		static void GetRelativePanelMaxY(double *return_value) { *return_value = 576.0 + axis_y_; }
		static void GetRelativePanelMinX(int *return_value) { *return_value = 160 + (int)axis_x_; }
		static void GetRelativePanelMinX(double *return_value) { *return_value = 160.0 + axis_x_; }
		static void GetRelativePanelMinY(int *return_value) { *return_value = 32 + (int)axis_y_; }
		static void GetRelativePanelMinY(double *return_value) { *return_value = 32.0 + axis_y_; }
	protected:
		static double axis_x_;
		static double axis_y_;
		static double move_axis_x_;
		static double move_axis_y_;
		static int swing_x_;
		static int swing_y_;
		static int swing_scale_y_;
		static int swing_time_y_;
		static std::list<PosToken> list_unused_;
		static std::list<PosToken> list_used_[eOBJECT::GROUP::sizeof_enum];
	private:

		static double CalcRAD(double x) { return (x * 3.1415 / 180.0); }
		static double CalcAngle(double x) { return (x * 180.0) / 3.1415; }
	};
}

