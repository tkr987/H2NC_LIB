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
	class MissionBackSc
	{
	public:
		eOBJECT::NUM draw_layer_;
		double end_grid_y_;
		GraphicProperty1* gp_;
		double scroll_speed_per_frame_;
		double start_grid_x_;
		double start_grid_y_;
		bool valid_;
		MissionBackSc();
		~MissionBackSc();
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
		void LoadBackSc(std::string file_pass, eOBJECT::NUM draw_layer, double start_grid_x, double start_grid_y, double max_scroll_size, unsigned int max_scroll_time_sec);
		void LoadSound(void);
		void LoadSoundEx(void);
		void ProcessMissionContinue(void);
		void ProcessMissionDelete(void);
		void ProcessMissionRun(void);
	private:
		int count_;
		NyaDesign* nya_design_;
		NyaGraphic* nya_graphic_;
		MissionBackSc mission_back_sc_;
		std::vector<MissionTarget> mission_target_vector_;
	};

}
