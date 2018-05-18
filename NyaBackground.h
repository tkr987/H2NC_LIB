#pragma once


namespace H2NLIB
{
	// ”wŒi‰æ‘œ‚Æ”wŒi‰¹Šy‚ÌŠî’êƒNƒ‰ƒX
	class NyaBackground
	{
	public:
		NyaBackground(){}
		virtual ~NyaBackground(){}
		virtual void Act(void){}
		virtual void Draw(void) = 0;
	};
}
