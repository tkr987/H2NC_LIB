#pragma once


namespace H2NLIB {


	class NyaTarget {
	public:
		NyaTarget(){}
		virtual ~NyaTarget(){}
		virtual void Act(void) = 0;
		virtual void Draw(void) = 0;
		virtual void MissionEnd(void) = 0;
		virtual void MissionStart(void) = 0;
	};

}

