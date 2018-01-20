#pragma once

#include <deque>
#include <map>
#include <string>
#include <tuple>


namespace H2NLIB {


	// 文字列を表示するクラス
	// 常に一番上に表示されるのでデバッグなどに使える

	struct StringSet {
		int color_;
		int font_;
		int x_;
		int y_;
		std::tuple<bool, std::string, int> write_int_;
		std::tuple<bool, std::string, double> write_double_;
		std::tuple<bool, std::string> write_string_;
	};

	class NyaString {
	public:
		NyaString();
		~NyaString();
		static void Run(void);
		static void SettingFont(std::string, int, int);
		static void Write(std::string, std::tuple<int, int, int> color, int pos_x, int pos_y, std::string str);
		static void Write(std::string, std::tuple<int, int, int> color, int pos_x, int pos_y, std::string str, int value);
		static void Write(std::string, std::tuple<int, int, int> color, int pos_x, int pos_y, std::string str, double value);
	private:
		static std::deque<StringSet> deque_string_set_;
		static std::map<std::string, int> map_font_;
	};

}


