#pragma once


namespace H2NLIB 
{
	enum class eEVENT;

	//****************************************************************************************
	// class NyaTarget
	// たいていの場合、MissionRun()は必須なので純粋仮想関数になっている。
	// 他の仮想関数は必要に応じて定義すること。
	//****************************************************************************************
	class NyaTarget {
	public:
		NyaTarget(){}
		virtual ~NyaTarget(){}
		virtual void Act(void) = 0;
		virtual void Draw(void) = 0;
		void Run(eEVENT check_event);
	};
}

