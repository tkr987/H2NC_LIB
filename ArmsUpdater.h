#pragma once

#include "ArmsManager.h"

namespace NH2 {
	struct ArmsParam;
	struct EffectParam1;
	struct ImgParam1;
	struct ImgParam4;
}

namespace NH3 {

	class ArmsUpdater : public NH2::ArmsManager {
	public:
		ArmsUpdater() : NH2::ArmsManager() {};
		~ArmsUpdater() {}
		void Run(void);
	private:
		NH2::EffectParam1 *eparam_user_arms_;
		void Calculate(eOBJECT::GROUP group);
		void Draw(eOBJECT::GROUP group);
		void Remove(eOBJECT::GROUP group);
		void RemoveTargetArms(void);
		void RemoveUserArms(void);
	};
}

