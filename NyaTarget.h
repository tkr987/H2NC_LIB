#pragma once


namespace H2NLIB {


	class NyaTarget {
	public:
		NyaTarget(){}
		virtual ~NyaTarget(){}
		virtual void Act(void) = 0;
		virtual void Draw(void) = 0;
		virtual void End(void) = 0;
	};

}

