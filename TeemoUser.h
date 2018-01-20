#pragma once

#include "NyaUser.h"

namespace H2NLIB {
	class NyaAttack;
	class NyaGraphic;
	class NyaPosition;
	class NyaString;
	struct AttackPropertyX;
	struct GraphicPropertyX4;
	struct PositionPropertyX;
}


class TeemoUser : public H2NLIB::NyaUser {
public:
	TeemoUser();
	~TeemoUser();
	void Action(void);
	void Draw(void);
private:
	long count_;
	H2NLIB::AttackPropertyX* apx_teemo_;
	H2NLIB::GraphicPropertyX4* gpx4_teemo_;
	H2NLIB::PositionPropertyX* ppx_teemo_;
	H2NLIB::NyaAttack* nya_attack_;
	H2NLIB::NyaGraphic* nya_graphic_;
	H2NLIB::NyaPosition* nya_position_;
	void Init(void);
};

