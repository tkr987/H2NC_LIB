#pragma once

namespace H2NLIB
{
	class NyaEnding
	{
	public:
		NyaEnding(){}
		virtual ~NyaEnding(){}
		virtual void Load(void) = 0;
		virtual void Run(void) = 0;
		virtual void Delete(void) = 0;
	};
}
