#pragma once


namespace H2NLIB {


	class NyaUser {
	public:
		NyaUser(){}
		virtual ~NyaUser(){}
		virtual void Init(void) = 0;
		virtual void Action(void) = 0;
		virtual void Draw(void) = 0;
	};

}