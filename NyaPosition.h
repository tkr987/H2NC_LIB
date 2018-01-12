#pragma once

#include <list>

namespace H2NLIB {

	struct PositionPropertyX {
		double health_now_;
		double health_max_;
		double pow_;
		double range_;
		double x_;
		double y_;
	};

	class NyaPosition {
	public:
		NyaPosition();
		~NyaPosition();
		void Create(PositionPropertyX* ppx);
		void Run(void);
	private:
		std::list<PositionPropertyX> used_;
		std::list<PositionPropertyX> wait_;
	};


}

