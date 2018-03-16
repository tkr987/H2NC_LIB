#pragma once


#include <string>
#include <utility>
#include <vector>


namespace H2NLIB
{
	class NyaDesign;
	class NyaGraphic;
	class NyaTarget;
	class GraphicFile;
	class GraphicPropertyX1;

	// îwåi
	struct MissionBack {
		int img_;
		int scroll_limit_frame_time_;
		double scroll_size_per_frame_;
		double grid_x_;
		double grid_y_;
	};

	// target
	struct MissionTarget {
		int start_frame_;
		int end_frame_;
		NyaTarget* target_;
	};

	class NyaMission {
	public:
		NyaMission();
		virtual ~NyaMission();
		void AddChTarget(int start_time_sec, int end_time_sec, NyaTarget* target);
		void End(void);
		void LoadBack(std::string file_pass, int start_grid_x, int start_grid_y, int max_scroll_size, int max_scroll_time_sec);
		void LoadSound(void);
		void LoadSoundEx(void);
		void Run(void);
		void Stop(void);
		virtual void Load(void) = 0;
	private:
		int count_;
		NyaDesign* nya_design_;
		NyaGraphic* nya_graphic_;
		GraphicPropertyX1* gpx1_back_;
		std::pair<bool, MissionBack> back_pair_;
		std::vector<MissionTarget> nya_target_vector_;
	};

}
