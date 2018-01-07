#pragma once

#include "FpsManager.h"

#define FPS_MAX 50

namespace NH3 {

	class FpsUpdater : public NH2::FpsManager {
	public:
		FpsUpdater();
		~FpsUpdater();
		void Run(void);
	private:
		int ave_frame_;			//�t���[�����[�g����
		int ave_wtime_;			//wait���ԕ���
		int ave_ltime_;			//loop���ԕ���
		int frame_[FPS_MAX];	//�t���[�����[�g
		int ltime_[FPS_MAX];	//loop����
		int wtime_[FPS_MAX];	//wait����
		int prev_time_;			//1�t���[���O�̎���
	};

}

