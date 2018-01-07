#pragma once
#include <string>

namespace NH2 {

	class DesignManager {
	public:
		DesignManager() {}
		virtual ~DesignManager() {}
		// 初期化
		static void Clear(void);
		// 加算関連
		static void AddAttackLV(double add_value) { value_alv_ = (value_alv_ + add_value < 1.0) ? 1.0 : (999.0 < value_alv_ + add_value) ? 999.0 : value_alv_ + add_value; }
		static void AddClockRank(double add_value) { value_rank_ = (value_rank_ + add_value < 1.0) ? 1.0 : (10.0 < value_rank_ + add_value) ? 10.0 : value_rank_ + add_value; }
		static void AddClockScoreRatio(double add_value);
		static void AddExArms(double add_value) { value_exarms_ = (value_exarms_ + add_value < 0) ? 0 : (200 < value_exarms_ + add_value) ? 200 : value_exarms_ + add_value; }
		static void AddScore(long val) { value_score_ = (99999999 < value_score_ + val * (long)value_score_ratio_) ? 99999999 : (value_score_ + val * (long)value_score_ratio_ < 0) ? 0 : value_score_ + val * (long)value_score_ratio_; }
		static void AddScore(double add_value) { value_score_ = (99999999 < value_score_ + add_value * value_score_ratio_) ? 99999999 : (value_score_ + add_value * value_score_ratio_ < 0) ? 0 : value_score_ + (long)(add_value * value_score_ratio_); }
		static void AddStar(int val) { value_star_ = (6 < value_star_ + val) ? 6 : (value_star_ + val < -1) ? -1 : value_star_ + val; }
		// フラグ関連
		static void FlagDrawBossHealth(bool set) { flag_draw_boss_health_ = set; }
		static bool IsFlagDrawBossHealth(void) { return flag_draw_boss_health_; }
		// 取得関連
		static void GetAttackLV(int *ret, double scale = 1.0) { *ret = (int)(value_alv_ * scale); }
		static void GetAttackLV(double *ret, double scale = 1.0) { *ret = value_alv_ * scale; }
		static void GetBossHealth(int *return_value) { *return_value = (int)value_boss_health_; }
		static void GetBossHealth(double *ret) { *ret = value_boss_health_; }
		static void GetExArms(int* return_value) { *return_value = (int)value_exarms_; }
		static void GetExArms(double* return_value) { *return_value = value_exarms_; }
//		static double GetExTime(void) { return extime_; }
		static void GetRank(unsigned int* ret, double scale = 1.0) { *ret = (unsigned int)(value_rank_ * scale); }
		static void GetRank(int* ret, double scale = 1.0) { *ret = (int)(value_rank_ * scale); }
		static void GetRank(double* ret, double scale = 1.0) { *ret = value_rank_ * scale;}
		static void GetStar(int *star){ *star = value_star_;  }
		static long GetScore(void) { return value_score_; }
		// 設定関連
		static void SetAttackLV(double set_value) { value_alv_ = set_value; }
		static void SetExArms(double set_value) { value_exarms_ = (set_value < 0) ? 0 : (200 < set_value) ? 200 : set_value; }
//		static void SetExTime(int set_value) { extime_ = set_value; }
		static void SetStar(int set_value) { value_star_ = (6 < set_value) ? 6 : (set_value < -1) ? -1 : set_value; }
		static void SetBossHealth(double set_value) { value_boss_health_ = (set_value < 0.0) ? 0.0 : (100.0 < set_value) ? 100.0 : set_value; }
		static void SetBossHealthColor(std::string set_color) { color_boss_health_ = set_color; }
	protected:
		static bool flag_draw_boss_health_;
		static double value_alv_;
		static double value_exarms_;
		static double value_boss_health_;		//!< 範囲は 0 - 100
		static double value_rank_;				//!< 範囲は 1.0 - 10.0
		static long value_score_;				//!< 範囲は 0 - 99999999
		static double value_score_ratio_;		//!< 範囲は 1.0 - 2.0
		static int value_star_;
		static std::string color_boss_health_;
		double CalcRAD(double x) { return (x * 3.1415 / 180.0); }
		double CalcAngle(double x) { return (x * 180.0) / 3.1415; }
	};
}

