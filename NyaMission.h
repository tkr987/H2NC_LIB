#pragma once


#include <string>
#include <utility>
#include <vector>
#include "NyaDefine.h"


namespace H2NLIB
{
	class NyaBackground;
	class NyaDesign;
	class NyaTarget;
	class GraphicFile;
	class GraphicProperty1;

	// target
	class MissionTarget
	{
	public:
		int start_frame_;
		int end_frame_;
		NyaTarget* target_;
	};

	class NyaMission
	{
	public:
		NyaMission();
		virtual ~NyaMission();
		virtual void Load(void) = 0;
		void AddChBackground(NyaBackground* background);
		void AddChTarget(int start_time_sec, int end_time_sec, NyaTarget* target);
		void LoadSound(void);
		void LoadSoundEx(void);
		void Run(eEVENT check_event);
	private:
		int count_;
		NyaDesign* nya_design_;
		NyaBackground* background_;
		std::vector<MissionTarget> mission_target_collection_;
		void ClearEvent(void);
		void EndEvent(void);
		void RunEvent(void);
	};

}
