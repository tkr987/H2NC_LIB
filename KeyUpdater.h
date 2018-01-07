#pragma once

#include "KeyManager.h"

namespace NH3 {

	class KeyUpdater :  public NH2::KeyManager {
	public:
		KeyUpdater();
		~KeyUpdater() {}
		void Run(void);
	private:
		std::ifstream fin_;
		std::ofstream fout_;
		char buf_[256];
	};

}

