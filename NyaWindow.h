#pragma once

namespace H2NLIB {

	class NyaDesign;
	class NyaPosition;
	class NyaString;
	struct PositionPropertyX;

	class NyaWindow {
	public:
		int Init(void);
		void Run(void);
		NyaWindow();
		~NyaWindow();
	private:
		NyaDesign* nya_design_;
		NyaPosition* nya_posision_;
		NyaString* nya_string_;
		PositionPropertyX* ppx_;
		void FpsUpdater(void);
	};

}
