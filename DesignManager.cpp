#include "DxLib.h"
#include "DesignManager.h"

using namespace std;
using namespace NH2;


int DesignManager::value_star_;
double DesignManager::value_alv_;
double DesignManager::value_boss_health_;
double DesignManager::value_exarms_;
double DesignManager::value_rank_;
double DesignManager::value_score_ratio_;
long DesignManager::value_score_;
bool DesignManager::flag_draw_boss_health_;
string DesignManager::color_boss_health_;


/**
@brief �f�[�^�N���A�֐�
**/
void DesignManager::Clear(void)
{
	value_alv_ = 1.0;
	value_boss_health_ = 0.0;
	value_exarms_ = 160;
	value_rank_ = 1.0;
	value_score_ratio_ = 1.0;
	value_score_ = 0;
	value_star_ = 0;
	flag_draw_boss_health_ = false;
}


// ***********
//  ���Z�֘A
// ***********


/**
@brief �X�R�A�{�����Z�֐�
@param add_value ���Z�l
**/
void DesignManager::AddClockScoreRatio(double add_value)
{
	if (value_score_ratio_ + add_value < 1.0) {
		value_score_ratio_ = 1.0;
	} else if (10.0 < value_score_ratio_ + add_value) {
		value_score_ratio_ = 10.0;
	} else {
		value_score_ratio_ += add_value;
	}
}

