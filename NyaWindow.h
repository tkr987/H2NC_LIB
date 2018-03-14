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
	class NyaSound;
	class NyaTarget;
	class NyaUser;

	struct WindowUser
	{
		bool empty_;
		NyaUser* nya_user_;
	};

	struct WindowMission
	{
		bool empty_;
		int index_;
		std::vector<NyaMission*> nya_mission_vector_;
	};

	class NyaWindow {
	public:
		void AddChMission(NyaMission*);
		void AddChUser(NyaUser* user);
		int Init(std::string title);
		void Run(void);
		void RunChangeProcess(void);
		void RunMission(void);
		void RunUser(void);
		NyaWindow();
		~NyaWindow();
	private:
		WindowUser ch_user_;
		WindowMission ch_mission_;
		NyaDesign* nya_design_;
		NyaDevice* nya_device_;
		NyaEffect* nya_effect_;
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_position_;
		NyaSound* nya_sound_;
		std::string title_name_;
		void RunTitle(void);
	};

}
