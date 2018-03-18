#pragma once

#include "NyaDefine.h"
#include <list>
#include <string>
#include <vector>


namespace H2NLIB {

	class NyaGraphic;
	class NyaPosition;
	class PositionHandleX;

	class Animation {
	public:
		int count_;
		int div_max_;
		int file_id_;
		int interval_time_;
		PositionHandleX* phx_;
		int option_index_;
	};

	class EffectPropertyX {
	public:
		int animation_div_max_;
		int animation_interval_time_;
		int file_id_;
		int grid_x_;
		int grid_y_;
		eOBJECT::NUM object_group_;
	};


	class EffectOption {
	public:
		double draw_angle_;
		double draw_extend_;
		double draw_move_x_;
		double draw_move_y_;
		EffectOption() {
			draw_angle_ = 0;
			draw_extend_ = 1.0;
			draw_move_x_ = 0;
			draw_move_y_ = 0;
		}

	};

	class NyaEffect {
	public:
		NyaEffect();
		~NyaEffect();
		void Draw(EffectPropertyX* epx, int option_index = 0);
		int LoadFile(int div_x, int div_y, std::string file_pass);
		int NewOption(EffectOption* option);
		void Run(void);
	private:
		int graphic_file_id_;
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		static std::list<Animation> draw_list_[eOBJECT::NUM::sizeof_enum];
		static std::list<Animation> wait_list_;
		static std::vector<EffectOption> option_vector_;
		void DrawAll(eOBJECT::NUM group);
	};

}

