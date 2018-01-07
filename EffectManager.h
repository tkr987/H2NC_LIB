#pragma once

#include <list>
#include <vector>
#include "DefineNH.h"

namespace NH2 {
	class PosManager;
}

namespace NH2 {

	namespace eEFFECT {
		enum DRAW {
			TYPE1, TYPE1B,
		};
	};

	struct EffectParam1 {
		int img_divmin_;
		int img_divmax_;
		int img_id_;
		int img_interval_;
		int x_;
		int y_;
		double extend_rate_;
		eOBJECT::GROUP group_;
		EffectParam1(void) {
			img_divmin_ = 0;
			img_divmax_ = 0;
			img_interval_ = 1;
			x_ = 0;
			y_ = 0;
		}
	};

	struct EffectParam1b {
		int blend_alpha_;
		int blend_mode_;
		int img_divmin_;
		int img_divmax_;
		int img_id_;
		int img_interval_;
		int x_;
		int y_;
		double extend_rate_;
		eOBJECT::GROUP group_;
		EffectParam1b(void) {
			blend_alpha_ = 0;
			img_divmin_ = 0;
			img_divmax_ = 0;
			img_interval_ = 1;
			x_ = 0;
			y_ = 0;
		}
	};

	struct EffectToken {
		int frames_;
		int img_blend_alpha_;
		int img_blend_mode_;
		int img_div_;
		int img_divmax_;
		int img_id_;
		int img_interval_;
		int img_x_;
		int img_y_;
		double img_extend_rate_;
		eOBJECT::GROUP group_;
		eEFFECT::DRAW draw_type_;
	};


	class EffectManager {
	public:
		EffectManager(void) {}
		virtual ~EffectManager(void) {}
		static void Clear(void);
		static void End(void);
		static int Create(EffectParam1 *param);
		static int Create(EffectParam1b *param);
	protected:
		static int eparam_id_;
		static std::list<EffectToken> list_unused_;
		static std::list<EffectToken> list_used_[eOBJECT::GROUP::sizeof_enum];
	};
}

