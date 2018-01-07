#pragma once

#include "DesignManager.h"

namespace NH2 {
	struct ImgParam1;
	struct ImgParam3;
	struct ImgParam4;
	class ImgManager;
	class PosManager;
}

namespace NH3 {

	class DesignUpdater : public NH2::DesignManager {
	public:
		DesignUpdater();
		~DesignUpdater();
		void Run(void);
	private:
		int imgfile_black_;
		int imgfile_clock_dial_;
		int imgfile_clock_hands_;
		int imgfile_clock_pin_;
		int imgfile_gblack_;
		int imgfile_gblue_;
		int imgfile_gred_;
		int imgfile_boss_health_black_;
		int imgfile_boss_health_green_;
		int imgfile_boss_health_red_;
		int imgfile_boss_health_frame_;
		int imgfile_kblack_;
		int imgfile_kred_;
		int imgfile_rank_;
		int imgfile_score_;
		int imgfile_star_;
		int imgfile_window_;
		void DrawBossHealth(void);
		void DrawExArms(void);
		void DrawExTime(void);
		void DrawKey(void);
		void DrawAttackLV(void);
		void DrawClockScore(void);
		void DrawClockRank(void);
		void DrawScore(void);
		void DrawStar(void);
		void DrawTargetHP(void);
		void DrawWindow(void);
		NH2::ImgParam1 *iparam1_;
		NH2::ImgParam1 *iparam1_alv_;
		NH2::ImgParam1 *iparam1_boss_frame_;
		NH2::ImgParam1 *iparam1_boss_health_;
		NH2::ImgParam1 *iparam1_clock_dial_;
		NH2::ImgParam4 *iparam4_clock_hands_;
		NH2::ImgParam1 *iparam1_key_;
		NH2::ImgParam1 *iparam1_score_;
		NH2::ImgParam1 *iparam1_window_;
		NH2::ImgParam1 *iparam1_exarms_;
		NH2::ImgParam3 *iparam3_exarms_;
		NH2::ImgParam3 *iparam3_;
		NH2::ImgParam4 *iparam4_;
	};
}

