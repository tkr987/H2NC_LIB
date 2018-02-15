#pragma once


#include <utility>
#include <vector>


namespace H2NLIB {

	class NyaDesign;
	class NyaTarget;

	class NyaMission {
	public:
		NyaMission();
		virtual ~NyaMission();
		virtual void Load(void) = 0;
		void AddChTarget(int frame, NyaTarget* add_target);
		void Run(void);
	private:
		int count_;
		NyaDesign* nya_design_;
		std::vector<std::pair<int, NyaTarget*>> nya_target_vector_;
	};

}
