#include <list>
#include <math.h>
#include "DxLib.h"
#include "DebugPrint.h"
#include "PosUpdater.h"
#define __DEBUG__

using namespace NH2;
using namespace NH3;
using namespace std;

void PosUpdater::Run(void)
{
	InitHitCount(eOBJECT::NUM::USER);
	InitHitCount(eOBJECT::NUM::TARGET_RUN_FLY);
	InitHitCount(eOBJECT::NUM::TARGET_RUN_WALK);
	InitHitCount(eOBJECT::NUM::USER_ARMS);
	InitHitCount(eOBJECT::NUM::TARGET_ARMS_SMALL);
	InitHitCount(eOBJECT::NUM::TARGET_ARMS_LARGE);
	Collision(eOBJECT::NUM::USER, eOBJECT::NUM::TARGET_ARMS_SMALL);
	Collision(eOBJECT::NUM::USER, eOBJECT::NUM::TARGET_ARMS_LARGE);
	Collision(eOBJECT::NUM::USER, eOBJECT::NUM::TARGET_RUN_FLY);
	Collision(eOBJECT::NUM::USER, eOBJECT::NUM::TARGET_RUN_WALK);
	Collision(eOBJECT::NUM::TARGET_RUN_FLY, eOBJECT::NUM::USER_ARMS);
	Collision(eOBJECT::NUM::TARGET_RUN_WALK, eOBJECT::NUM::USER_ARMS);
	AxisCalculate(eOBJECT::NUM::MAP_BOTTOM);
	AxisCalculate(eOBJECT::NUM::TARGET_READY);
	AxisCalculate(eOBJECT::NUM::TARGET_RUN_FLY);
	AxisCalculate(eOBJECT::NUM::TARGET_RUN_WALK);
	AxisCalculate(eOBJECT::NUM::TARGET_ARMS_LARGE);
	AxisCalculate(eOBJECT::NUM::TARGET_ARMS_SMALL);
	AxisUpdate();

	list<PosToken>::iterator it;
	for (it = list_used_[eOBJECT::NUM::USER].begin(); it != list_used_[eOBJECT::NUM::USER].end(); ++it) {
		if (it->name_ == POS_NAME_USER_MAIN)
			break;
	}
	DebugPrint::SetData(490, 555, "user_itx[%d]", (int)it->x_);

}

void PosUpdater::AxisCalculate(eOBJECT::GROUP group)
{
	list<PosToken>::iterator it;

	if (move_axis_x_ == 0)
		return;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		it->x_ += move_axis_x_;
	}
}

void PosUpdater::AxisUpdate(void)
{
	axis_x_ += move_axis_x_;
	move_axis_x_ = 0;
}


void PosUpdater::Collision(eOBJECT::GROUP group1, eOBJECT::GROUP group2)
{
	double x1, x2, y1, y2;
	double range1, range2;
	list<PosToken>::iterator it1, it2;

	for (it1 = list_used_[group1].begin(); it1 != list_used_[group1].end(); ++it1) {
		for (it2 = list_used_[group2].begin(); it2 != list_used_[group2].end(); ++it2) {
			x1 = it1->x_;
			x2 = it2->x_;
			y1 = it1->y_;
			y2 = it2->y_;
			range1 = it1->range_;
			range2 = it2->range_;
			if (Pow2(x1 - x2) < Pow2(range1 + range2) && Pow2(y1 - y2) < Pow2(range1 + range2)) {
				it1->hit_ += it2->pow_;
				it2->hit_ += it1->pow_;
			}
		}
	}
}

void PosUpdater::InitHitCount(eOBJECT::GROUP group)
{
	list<PosToken>::iterator it;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it)
		it->hit_ = 0;
}
