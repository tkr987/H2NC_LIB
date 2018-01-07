#pragma once

namespace NH2T {

	class TargetBase {
	public:
		TargetBase() {}
		virtual ~TargetBase() {}
		virtual void Run(void) {}
		virtual void Action(void) = 0;
		virtual void Draw(void) = 0;
	protected:
		double CalcRAD(double x) { return (x * 3.1415 / 180.0); }
		double CalcAngle(double x) { return (x * 180.0) / 3.1415; }
	};
}
