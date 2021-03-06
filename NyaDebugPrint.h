#pragma once
#pragma once

#include <deque>
#include "DxLib.h"


namespace HNLIB {


	struct NyaDebugData {
		int pos_x_;
		int pos_y_;
		bool type_i_;
		bool type_d_;
		int val_i_;
		double val_d_;
		std::string str_;
	};

	class NyaDebugPrint {
	public:
		NyaDebugPrint() {}
		~NyaDebugPrint() {}
		static void SetData(int x, int y, std::string str)
		{
			NyaDebugData dd;

			dd.pos_x_ = x;
			dd.pos_y_ = y;
			dd.type_i_ = false;
			dd.type_d_ = false;
			dd.str_ = str;
			deque_data_.push_back(dd);
		}
		static void SetData(int x, int y, std::string str, int val)
		{
			NyaDebugData dd;

			dd.pos_x_ = x;
			dd.pos_y_ = y;
			dd.type_i_ = true;
			dd.type_d_ = false;
			dd.val_i_ = val;
			dd.str_ = str;
			deque_data_.push_back(dd);
		}
		static void SetData(int x, int y, std::string str, double val)
		{
			NyaDebugData dd;

			dd.pos_x_ = x;
			dd.pos_y_ = y;
			dd.type_i_ = false;
			dd.type_d_ = true;
			dd.val_d_ = val;
			dd.str_ = str;
			deque_data_.push_back(dd);
		}
		static void Run(void)
		{
			NyaDebugData dd;
			int color = GetColor(255, 255, 255);

			while (!deque_data_.empty()) {
				dd = deque_data_.front();
				if (dd.type_i_ == true) {
					DrawFormatString(dd.pos_x_, dd.pos_y_, color, dd.str_.c_str(), dd.val_i_);
				}
				else if (dd.type_d_ == true) {
					DrawFormatString(dd.pos_x_, dd.pos_y_, color, dd.str_.c_str(), dd.val_d_);
				}
				else {
					DrawFormatString(dd.pos_x_, dd.pos_y_, color, dd.str_.c_str());
				}
				deque_data_.pop_front();
			}
		}
	private:
		static std::deque<NyaDebugData> deque_data_;
	};


}
