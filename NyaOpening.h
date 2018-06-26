#pragma once


namespace H2NLIB
{
	class NyaOpening
	{
	public:
		NyaOpening(){}
		virtual ~NyaOpening(){}
		virtual void Load(void) = 0;
		virtual void Run(void) = 0;
		virtual void Delete(void) = 0;
	};
}
