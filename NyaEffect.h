#pragma once

#include "NyaDefine.h"
#include <list>
#include <vector>


namespace H2NLIB {

	class NyaGraphic;
	class NyaPosition;
	struct PositionHandleX;

	struct Effect {
		int count_;
		int setting_id_;
		PositionHandleX* phx_;
	};

	struct EffectPropertyX {
		int setting_id_;
		int grid_x_;
		int grid_y_;
	};


	struct EffectSetting {
		int graphic_file_id_;
		double graphic_draw_extend_;
		double graphic_draw_angle_;
		int effect_div_max_;
		int effect_interval_time_;
		double effect_move_x_;
		double effect_move_y_;
		eOBJECT::GROUP object_group_;
	};

	class NyaEffect {
	public:
		NyaEffect();
		~NyaEffect();
		void Draw(EffectPropertyX* epx);
		int LoadSetting(EffectSetting* setting);
		void Run(void);
	private:
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		static std::list<Effect> draw_list_[eOBJECT::GROUP::sizeof_enum];
		static std::list<Effect> wait_list_;
		static std::vector<EffectSetting> setting_vector_;
		void DrawAll(eOBJECT::GROUP group);
	};

}

