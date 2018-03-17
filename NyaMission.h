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
	class MissionBack
	{
	public:
		bool empty_;
		double grid_x_;
		double grid_y_;
		int scroll_limit_frame_time_;
		double scroll_size_per_frame_;
		GraphicPropertyX1* gpx1_;
		MissionBack()
		{
			empty_ = true;
		}
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
		void AddChTarget(int start_time_sec, int end_time_sec, NyaTarget* target);
		virtual void Load(void) = 0;
		void LoadBack(GraphicPropertyX1* gpx1, int start_grid_x, int start_grid_y, int max_scroll_size, int max_scroll_time_sec);
		void LoadSound(void);
		void LoadSoundEx(void);
		void MissionEnd(void);
		void MissionRun(void);
		void MissionStop(void);
	private:
		int count_;
		NyaDesign* nya_design_;
		NyaGraphic* nya_graphic_;
		MissionBack mission_back_;
		std::vector<MissionTarget> mission_target_vector_;
	};

}
