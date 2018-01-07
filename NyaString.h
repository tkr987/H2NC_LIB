#pragma once

#include <deque>
#include <map>
#include <string>
#include "DxLib.h"


namespace H2NLIB {


	// 文字列を表示するクラス
	// 常に一番上に表示されるのでデバッグなどに使える

	struct StringData {
		int pos_x_;
		int pos_y_;
		std::string str_;
		int style_;
		bool type_i_;
		bool type_d_;
		int val_i_;
		double val_d_;
	};

	class NyaString {
	public:
		NyaString();
		~NyaString();
		void Init(std::string, int, int);
		void Run(void);
		void Write(std::string, int x, int y, std::string);
		void Write(std::string, int x, int y, std::string, int);
		void Write(std::string, int x, int y, std::string, double);
	private:
		static std::deque<StringData> deque_string_data_;
		static std::map<std::string, int> map_string_style_;
	};

}


