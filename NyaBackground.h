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
		virtual void MissionRun(void) = 0;
		virtual void MissionContinue(void) = 0;
		virtual void MissionClear(void){}
		void Run(const eEVENT check_event);
	};
}
