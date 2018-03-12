#include <math.h>
#include <utility>
#include <stdexcept>
#include "PosManager.h"
#include "DebugPrint.h"

#define POS_TOKEN_MAXSIZE 16384

using namespace NH2;
using namespace std;
double PosManager::axis_x_;
double PosManager::axis_y_;
double PosManager::move_axis_x_;
double PosManager::move_axis_y_;
int PosManager::swing_scale_y_;
int PosManager::swing_time_y_;
list<PosToken> PosManager::list_unused_;
list<PosToken> PosManager::list_used_[eOBJECT::NUM::sizeof_enum];


void PosManager::Clear(void)
{
	PosToken ptoken;

	axis_x_ = 0;
	axis_y_ = 0;
	move_axis_x_ = 0;
	move_axis_y_ = 0;
	swing_scale_y_ = 0;
	swing_time_y_ = 0;

	// リストの要素全消去
	list_unused_.clear();
	for (int group = eOBJECT::NUM::enum_zero; group != eOBJECT::NUM::sizeof_enum; group++)
		list_used_[group].clear();

	// 新規リスト生成
	for (int n = 0; n < POS_TOKEN_MAXSIZE; n++) {
		ptoken.id_ = n;
		list_unused_.push_back(ptoken);
	}
}

void PosManager::End(void) {
	list_unused_.clear();
	for (int group = 0; group != eOBJECT::NUM::sizeof_enum; group++)
		list_used_[group].clear();
}


/**
@brief PosToken生成関数
@param set_group グループ指定
@param *param パラメータ指定
@retval true 成功
@retval false 失敗
@note
 生成数が限界値のときは何もしない。
**/
bool PosManager::Generate(eOBJECT::GROUP set_group, PosParam1* param)
{
	list<PosToken>::iterator it;

	// 生成数が限界
	if (list_unused_.size() == 0)
		return false;

	it = list_unused_.begin();
	it->hit_ = 0;
	it->pow_ = param->pow_;
	it->range_ = param->range_;
	it->x_ = param->start_x_;
	it->y_ = param->start_y_;
	param->group_ = set_group;
	param->it_ = it;
	list_unused_.splice(list_used_[set_group].begin(), list_unused_, it);

	return true;
}

/**
@brief PosToken生成関数
@param *param パラメータ指定
@param name 設定する名前
@retval true 成功
@retval false 失敗
@note
 生成数が限界値のときは何もしない。
 生成と同時に pos token に特別な名前をつけることができる。
**/
bool PosManager::Generate(eOBJECT::GROUP set_group, PosParam1* param, std::string name)
{
	list<PosToken>::iterator it;

	// 生成数が限界
	if (list_unused_.size() == 0)
		return false;

	it = list_unused_.begin();
	it->hit_ = 0;
	it->name_ = name;
	it->pow_ = param->pow_;
	it->range_ = param->range_;
	it->x_ = param->start_x_;
	it->y_ = param->start_y_;
	param->group_ = set_group;
	param->it_ = it;
	list_unused_.splice(list_used_[set_group].begin(), list_unused_, it);

	return true;
}

/**
@brief 削除関数
@param group 指定グループ
@note
 引数で指定したグループの pos token を全て削除する。
 処理速度は生成されている pos token の数に依存する。
**/
void PosManager::Delete(eOBJECT::GROUP group)
{
	list<int>::iterator it;

	//	while (!list_used_[group].empty()) {
	//		it = list_used_[group].begin();
	//		list_used_[group].splice(list_unused_.begin(), list_used_[group], it);
	//	}
	//	上記コードはうまくいかなかった
	while (list_used_[group].begin() != list_used_[group].end())
		list_used_[group].splice(list_unused_.begin(), list_used_[group], list_used_[group].begin());
}

/**
@brief 削除関数
@param *param 削除する pos token のパラメータ
@note
 削除済みかどうかの検査を省略して高速化。
 自己責任で呼び出すこと。
**/
void PosManager::Delete(PosParam1 *param)
{
	static eOBJECT::GROUP group = param->group_;

	list_used_[group].splice(list_unused_.begin(), list_used_[group], param->it_);
}

/**
@brief 削除関数
@param *param 削除する pos token のパラメータ
@retval  1 成功
@retval -1 失敗
@note
 処理速度は生成されている pos token の数に依存する。
**/
int PosManager::Delete_s(PosParam1 *param)
{
	static list<PosToken>::iterator it;
	static eOBJECT::GROUP group = param->group_;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		if (it->id_ == param->it_->id_) {
			list_used_[group].splice(list_unused_.begin(), list_used_[group], it);
			return 1;
		}
	}

	return -1;
}

/**
@brief グループ設定関数
@param *param 設定したい PosToken のパラメータ
@param group 設定するグループ
@note
 注意: 生成してない PosToken のグループは設定できない。
**/
void PosManager::SetGroup(PosParam1 *param, eOBJECT::GROUP set_group)
{
	static list<PosToken>::iterator it;
	static eOBJECT::GROUP group;
	
	group = param->group_;
	it = param->it_;
	list_used_[group].splice(list_used_[set_group].begin(), list_used_[group], it);
	param->group_ = set_group;
}


/**
@brief 名前設定関数
@param *param 設定したい pos token のパラメータ
@param name 設定する名前
@note
 第一引数で指定した pos token に特別な名前を設定できる。
 設定した名前は差分角度の計算(CalcDiffAngle)などに使える。
**/
void PosManager::SetName(PosParam1 *param, string name)
{
	param->it_->name_ = name;
}


/**
@brief 座標設定関数A
@param *param 座標をセットする pos token のパラメータ
@param *x セットするx座標
@param *y セットするy座標
@note
 x座標またはy座標にnullを指定した場合は，その値を変更しない。
**/
void PosManager::SetPosA(PosParam1 *param, double *x, double *y)
{
	static list<PosToken>::iterator it;

	it = param->it_;
	if (x != NULL)
		it->x_ = *x;
	if (y != NULL)
		it->y_ = *y;
}


/**
@brief 座標設定関数B
@param group 座標をセットする pos token のグループ
@param *x セットするx座標
@param *y セットするy座標
@note
第一引数で指定したグループ内の全ての pos token に対して値を代入する。
x座標またはy座標にnullを指定した場合は，その値を変更しない。
**/
void PosManager::SetPosB(eOBJECT::GROUP group, double *x, double *y)
{
	static list<PosToken>::iterator it;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {

		if (x != NULL)
			it->x_ = *x;
		if (y != NULL)
			it->y_ = *y;
	}
}


/**
@brief 当たり判定設定関数
@param *param 座標をセットする pos token のパラメータ
@param *x セットする当たり判定の範囲
**/
void PosManager::SetRange(PosParam1 *param, double set_value)
{
	static list<PosToken>::iterator it;
	
	it = param->it_;
	it->range_ = set_value;
}


/**
@brief X軸移動関数
@param move_value 移動量
@return 移動した量
@note
 軸の移動範囲に制限あり。
**/
double PosManager::MoveAxisX(double move_value)
{
	if (axis_x_ + move_value < -100) {
		move_axis_x_ = 0;
	} else if (100 < axis_x_ + move_value) {
		move_axis_x_ = 0;
	} else {
		move_axis_x_ = move_value;
	}

	return move_axis_x_;
}

/**
@brief Y軸移動関数
@param move_value 移動量
@return 0
@note
 使わないので未実装。
**/
double PosManager::MoveAxisY(double move_value)
{
	return 0;
}


/**
@brief 座標移動関数A
@param *param 座標を移動させる pos token のパラメータ
@param *add_x 移動(加算)するx座標
@param *add_y 移動(加算)するy座標
@note
 現在の座標に引数で指定した値を加算する。
 x座標またはy座標に null を指定した場合は，その値を変更しない。
**/
void PosManager::MovePosA(PosParam1 *param, double *add_x, double *add_y)
{
	static list<PosToken>::iterator it;

	it = param->it_;
	if (add_x != NULL)
		it->x_+= *add_x;
	if (add_y != NULL)
		it->y_ += *add_y;
}

/**
@brief 座標移動関数B
@param *param 座標を移動させる pos token のパラメータ
@param angle 角度(ラジアン指定)
@param dist 移動距離
@note
 角度と距離を指定して座標を移動させる。
**/
void PosManager::MovePosB(PosParam1 *param, double angle, double dist)
{
	static list<PosToken>::iterator it;

	it = param->it_;
	it->x_ += (cos(angle) * dist);
	it->y_ += (sin(angle) * dist);
}

/**
@brief 座標移動関数C
@param group 座標を移動させる pos token のグループ
@param *add_x 移動(加算)するx座標
@param *add_y 移動(加算)するy座標
@note
 第一引数で指定したグループ内の全ての pos token に対して値を更新する。
 x座標またはy座標に null を指定した場合は，その値を変更しない。
**/
void PosManager::MovePosC(eOBJECT::GROUP group, double *add_x, double *add_y)
{
	static list<PosToken>::iterator it;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {

		if (add_x != NULL)
			it->x_ += *add_x;
		if (add_y != NULL)
			it->y_ += *add_y;
	}
}

/*!
@brief オブジェクト間の角度を求める関数
@param param 起点となるオブジェクトのパラメータ
@param group 対象オブジェクトのグループ
@param name 対象オブジェクトの名前
@return 計算結果(ラジアン)
@note
 起点と対象オブジェクト間の角度を計算して結果をラジアンで返す。
*/
double PosManager::GetAtan(PosParam1 *param, eOBJECT::GROUP group, string name)
{
	double x, y;
	double ret = 0;
	list<PosToken>::iterator it_start, it_end;

	it_start = param->it_;
	for (it_end = list_used_[group].begin(); it_end != list_used_[group].end(); ++it_end) {
		if (it_end->name_ == name) {
			x = it_end->x_ - it_start->x_;
			y = it_end->y_ - it_start->y_;
			ret = atan2(y, x);
			break;
		}
	}

	return ret;
}

/**
@brief 差分距離計算関数
@param *param 起点の pos token param
@param group 終点の pos token group
@param name 終点の pos token name
@return 計算結果
@note
 計算速度は生成されている pos token の数に依存する。
**/
double PosManager::CalcDiffDistance(PosParam1 *param, eOBJECT::GROUP group, string name)
{
	double x, y;
	double ret = 0;
	list<PosToken>::iterator it_start, it_end;

	it_start = param->it_;
	for (it_end = list_used_[group].begin(); it_end != list_used_[group].end(); ++it_end) {
		if (it_end->name_ == name) {
			x = it_end->x_ - it_start->x_;
			y = it_end->y_ - it_start->y_;
			ret = sqrt(x * x + y * y);
		}
	}

	return ret;
}

/**
@brief 座標取得関数int型(名前指定)
@param group 座標取得する PosTokenのグループ
@param name 座標取得する PosToken の名前
@param return_x 取得したx座標を格納する
@param return_x 取得したy座標を格納する
@note
 x座標またはy座標に null を指定した場合は，その値を変更しない。
**/
void PosManager::GetPos(eOBJECT::GROUP group, std::string name, int *return_x, int *return_y)
{
	list<PosToken>::iterator it;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		if (it->name_ == name) {
			if (return_x != NULL)
				*return_x = (int)it->x_;
			if (return_y != NULL)
				*return_y = (int)it->y_;
			return;
		}
	}
}

/**
@brief 座標取得関数double型(名前指定)
@param group 座標取得する PosTokenのグループ
@param name 座標取得する PosToken の名前
@param return_x 取得したx座標を格納する
@param return_x 取得したy座標を格納する
@note
 x座標またはy座標に null を指定した場合は，その値を変更しない。
**/
void PosManager::GetPos(eOBJECT::GROUP group, std::string name, double *return_x, double *return_y)
{
	list<PosToken>::iterator it;

	for (it = list_used_[group].begin(); it != list_used_[group].end(); ++it) {
		if (it->name_ == name) {
			if (return_x != NULL)
				*return_x = (int)it->x_;
			if (return_y != NULL)
				*return_y = (int)it->y_;
			return;
		}
	}
}

/**
@brief 座標取得関数double型
@param param 座標取得する PosTokenのパラメータ
@param name 座標取得する PosToken の名前
@param return_x 取得したx座標を格納する
@param return_x 取得したy座標を格納する
@note
 x座標またはy座標に null を指定した場合は，その値を変更しない。
**/
void PosManager::GetPos(PosParam1 *param, int *return_x, int *return_y)
{
	if (return_x != NULL)
		*return_x = (int)param->it_->x_;
	if (return_y != NULL)
		*return_y = (int)param->it_->y_;
}

/**
@brief 座標取得関数double型
@param param 座標取得する PosToken のパラメータ
@param return_x 取得したx座標を格納する
@param return_x 取得したy座標を格納する
@note
 x座標またはy座標に null を指定した場合は，その値を変更しない。
**/
void PosManager::GetPos(PosParam1 *param, double *return_x, double *return_y)
{
	if (return_x != NULL)
		*return_x = param->it_->x_;
	if (return_y != NULL)
		*return_y = param->it_->y_;
}
