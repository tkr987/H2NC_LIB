#pragma once


#include <string>
#include <utility>
#include <vector>
#include "NyaDefine.h"


namespace H2NLIB
{
	class NyaDesign;
	class NyaGraphic;
	class NyaTarget;
	class GraphicFile;
	class GraphicProperty1;

	// îwåi
	class MissionBack
	{
	public:
		eOBJECT::NUM draw_layer_;
		double grid_x_;
		double grid_y_;
		int scroll_limit_frame_time_;
		double scroll_size_per_frame_;
		bool valid_;
		GraphicProperty1* gp_;
		MissionBack();
		~MissionBack();
	};

	// target
	class MissionTarget
	{
	public:
		int start_frame_;
		int end_frame_;
		NyaTarget* target_;
	};

	class NyaMission {
	public:
		NyaMission();
		virtual ~NyaMission();
		virtual void Load(void) = 0;
		void AddChTarget(int start_time_sec, int end_time_sec, NyaTarget* target);
		void LoadBack(GraphicProperty1* gp, eOBJECT::NUM draw_layer, int start_grid_x, int start_grid_y, int max_scroll_size, int max_scroll_time_sec);
		void LoadSound(void);
		void LoadSoundEx(void);
		void ProcessMissionContinue(void);
		void ProcessMissionDelete(void);
		void ProcessMissionRun(void);
	private:
		int count_;
		NyaDesign* nya_design_;
		NyaGraphic* nya_graphic_;
		MissionBack mission_back_;
		std::vector<MissionTarget> mission_target_vector_;
	};

}
