#pragma once


namespace H2NLIB {

	class NyaAttack;
	class NyaDesign;
	class NyaGraphic;
	class NyaInput;
	class NyaPosition;
	class NyaString;
	class NyaUser;

	class NyaWindow {
	public:
		int Init(void);
		void Run(void);
		void SetUser(NyaUser* user);
		NyaWindow();
		~NyaWindow();
	private:
		bool set_user_;
		NyaAttack* nya_attack_;
		NyaDesign* nya_design_;
		NyaGraphic* nya_graphic_;
		NyaInput* nya_input_;
		NyaPosition* nya_posision_;
		NyaString* nya_string_;
		NyaUser* nya_user_;
		void FpsUpdater(void);
	};

}
