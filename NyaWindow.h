#pragma once

namespace H2NLIB {

	class NyaDesign;
	class NyaString;

	class NyaWindow {
	public:
		int Init(void);
		void Run(void);
		NyaWindow();
		~NyaWindow();
	private:
		NyaDesign* nya_design_;
		NyaString* nya_string_;
		void FpsUpdater(void);
	};

}
