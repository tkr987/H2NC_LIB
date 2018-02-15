#pragma once

#include <vector>
#include <utility>

namespace H2NLIB {

	class NyaDesign;
	class NyaDevice;
	class NyaEffect;
	class NyaGraphic;
	class NyaInput;
	class NyaMission;
	class NyaPosition;
	class NyaTarget;
	class NyaUser;

	class NyaWindow {
	public:
		void AddChMission(NyaMission*);
		void AddChUser(NyaUser* user);
		int Init(void);
		void Run(void);
		NyaWindow();
		~NyaWindow();
	private:
		int nya_mission_index_;
		NyaDesign* nya_design_;
		NyaDevice* nya_device_;
		NyaEffect* nya_effect_;
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_posision_;
		std::pair<bool, NyaUser*> nya_user_;
		std::vector<NyaMission*> nya_mission_vector_;
		void ProcessMissionRun(void);
		void ProcessMissionStop(void);
	};

}
