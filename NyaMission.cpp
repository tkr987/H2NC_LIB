#include "NyaDesign.h"
#include "NyaMission.h"
#include "NyaString.h"
#include "NyaTarget.h"

using namespace std;
using namespace H2NLIB;


NyaMission::NyaMission()
{
	nya_design_ = new NyaDesign;
	NyaString::SettingFont("debug_mission_font", 15, 2);
}

NyaMission::~NyaMission()
{
	delete nya_design_;
}


void NyaMission::AddChTarget(int frame, NyaTarget* target)
{
	pair<int, NyaTarget*> target_pair;

	target_pair.first = frame;
	target_pair.second = target;
	nya_target_vector_.push_back(target_pair);
}

void NyaMission::Run(void)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	NyaString::Write("debug_mission_font", white, 50, 150, "[50, 150] nya_target_frame = %d", nya_target_vector_[0].first);
	NyaString::Write("debug_mission_font", white, 50, 170, "[50, 170] nya_target_count = %d", count_);

	switch(nya_design_->GetProcess()){
	case ePROCESS::MISSION_LOAD:
		count_ = 0;
		break;
	case ePROCESS::MISSION_RUN:
		for (auto& it : nya_target_vector_) {
			if (it.first <= count_) {
				it.second->Action();



				it.second->Draw();



			}
		}
		count_++;
		break;
	case ePROCESS::MISSION_STOP:
		for (auto& it : nya_target_vector_) {
			if (it.first <= count_) {
				it.second->Draw();
			}
		}
		break;
	}
}
