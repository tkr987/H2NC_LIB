#pragma once
#include "NyaEnum.h"

namespace HNLIB
{
	class NyaUser {
	public:
		NyaUser(){}
		virtual ~NyaUser(){}
		virtual void Act(void) = 0;
		virtual void Draw(void) = 0;
		void Run(eEVENT check_event);
	};

}