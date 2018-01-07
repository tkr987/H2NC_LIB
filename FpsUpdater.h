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
		int ave_frame_;			//フレームレート平均
		int ave_wtime_;			//wait時間平均
		int ave_ltime_;			//loop時間平均
		int frame_[FPS_MAX];	//フレームレート
		int ltime_[FPS_MAX];	//loop時間
		int wtime_[FPS_MAX];	//wait時間
		int prev_time_;			//1フレーム前の時間
	};

}

