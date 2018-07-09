#pragma once


namespace H2NLIB
{
	enum class eEVENT;

	// ”wŒi‰æ‘œ‚Æ”wŒi‰¹Šy‚ÌŠî’êƒNƒ‰ƒX
	class NyaBackground
	{
	public:
		NyaBackground(){}
		virtual ~NyaBackground(){}
		virtual void Act(void) = 0;
		virtual void Draw(void) = 0;
		void Run(const eEVENT check_event);
	};
}
