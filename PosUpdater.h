#pragma once

#include "PosManager.h"

namespace NH3 {

	class PosUpdater : public NH2::PosManager {
	public:
		PosUpdater() : NH2::PosManager() {};
		~PosUpdater() {}
		void Run(void);
	private:
		void Collision(eOBJECT::GROUP group1, eOBJECT::GROUP group2);
		void InitHitCount(eOBJECT::GROUP group);
		void AxisCalculate(eOBJECT::GROUP group);
		void AxisUpdate(void);
		void SwingCalculate(eOBJECT::GROUP group);
		void SwingUpdate(void);
		double Pow2(double x) { return x * x; }
	};
}

