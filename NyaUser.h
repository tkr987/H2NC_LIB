#pragma once


namespace H2NLIB {


	class NyaUser {
	public:
		NyaUser(){}
		~NyaUser(){}
		virtual void Run(void) = 0;
	};

}