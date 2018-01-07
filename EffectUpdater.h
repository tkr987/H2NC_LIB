#pragma once

#include "EffectManager.h"

namespace NH3 {

	class EffectUpdater : public NH2::EffectManager {
	public:
		EffectUpdater(void) : NH2::EffectManager() {}
		~EffectUpdater() {}
		void Run(void);
	private:
		void DrawType1(eOBJECT::GROUP group);
		void DrawType2(eOBJECT::GROUP group);
	};
}

