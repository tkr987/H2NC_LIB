#pragma once

#include "SoundManager.h"

namespace NH3 {

	class SoundUpdater : public NH2::SoundManager {
	public:
		SoundUpdater();
		~SoundUpdater();
		void Run(void);
	};

}

