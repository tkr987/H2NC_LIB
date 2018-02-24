#pragma once

#include <string>
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
		int Init(std::string);
		void Run(void);
		NyaWindow();
		~NyaWindow();
	private:
		int nya_mission_index_;
		std::string title_name_;
		NyaDesign* nya_design_;
		NyaDevice* nya_device_;
		NyaEffect* nya_effect_;
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		std::pair<bool, NyaUser*> nya_user_;
		std::vector<NyaMission*> nya_mission_vector_;
		void RunTitle(void);
	};

}
