#pragma once


namespace H2NLIB {


	class NyaUser {
	public:
		NyaUser(){}
		virtual ~NyaUser(){}
		virtual void Act(void) = 0;
		virtual void Draw(void) = 0;
		virtual void GameEnd(void) = 0;
		virtual void GameStart(void) = 0;
		virtual void MissionEnd(void){}
		virtual void MissionStart(void){}
	};

}