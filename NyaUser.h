#pragma once


namespace H2NLIB {


	class NyaUser {
	public:
		NyaUser(){}
		~NyaUser(){}
		virtual void Action(void) = 0;
		virtual void Draw(void) = 0;
	};

}