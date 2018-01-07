#pragma once


namespace NH2 {

	class FpsManager {
	public:
		static unsigned int GetInterval(unsigned int x) { return all_frame_count_ % x; }
	protected:
		static unsigned int frame_count_;
		static unsigned int all_frame_count_;

	};

}

