#pragma once

namespace H2NLIB {

	class NyaDesign;
	class NyaGraphic;
	class NyaString;

	class NyaWindow {
	public:
		int Init(void);
		void Run(void);
		NyaWindow();
		~NyaWindow();
	private:
		NyaDesign* nya_design_;
		NyaGraphic* nya_graphic_;
		NyaString* nya_string_;
		void FpsUpdater(void);
	};

}
