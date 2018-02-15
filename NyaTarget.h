#pragma once


namespace H2NLIB {


	class NyaTarget {
	public:
		NyaTarget(){}
		virtual ~NyaTarget(){}
		virtual void Action(void) = 0;
		virtual void Draw(void) = 0;
	};

}

