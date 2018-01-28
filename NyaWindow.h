#pragma once


namespace H2NLIB {

	class NyaDevice;
	class NyaDesign;
	class NyaGraphic;
	class NyaInput;
	class NyaPosition;
	class NyaTarget;
	class NyaUser;

	class NyaWindow {
	public:
		int Init(void);
		void Run(void);
		void SetUser(NyaUser* user);
		void SetTarget(NyaTarget* target);
		NyaWindow();
		~NyaWindow();
	private:
		bool set_target_;
		bool set_user_;
		NyaDesign* nya_design_;
		NyaDevice* nya_device_;
		NyaGraphic* nya_graphic_;
		NyaPosition* nya_posision_;
		NyaTarget* nya_target_;
		NyaUser* nya_user_;
		void FpsUpdater(void);
	};

}
