#pragma once

#include "ImgManager.h"

namespace NH3 {

	class ImgUpdater : public NH2::ImgManager {
	public:
		ImgUpdater();
		~ImgUpdater();
		void Run(void);
	private:
		void Draw(int type);
		void GetSwingScale(int layer, int *x, int *y);
	};

}
