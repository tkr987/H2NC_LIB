#pragma once


namespace HNLIB
{
	enum class eEVENT;

	// ”wŒi‰æ‘œ‚Æ”wŒi‰¹Šy‚ÌŠî’êƒNƒ‰ƒX
	class NyaBack
	{
	public:
		NyaBack(){}
		virtual ~NyaBack(){}
		virtual void Act(void) = 0;
		virtual void Draw(void) = 0;
		void Run(const eEVENT check_event);
	};
}
