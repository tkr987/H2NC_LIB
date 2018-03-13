#pragma once

#include <deque>
#include <map>
#include <string>
#include <tuple>


namespace H2NLIB {


	// 文字列を表示するクラス
	// 常に一番上に表示されるのでデバッグなどに使える

	struct StringOutput
	{
		int color_;
		int font_;
		int x_;
		int y_;
		std::tuple<bool, std::string> write_string_;
		std::tuple<bool, std::string, int> write_value_int_;
		std::tuple<bool, std::string, double> write_value_double_;
		std::tuple<bool, std::string, std::string> write_value_string_;
	};

	class NyaString {
	public:
		NyaString();
		~NyaString();
		static void Run(void);
		static void SettingFont(std::string, int, int);
		static void Write(std::string font, std::tuple<int, int, int> color, int grid_x, int grid_y, std::string str);
		static void Write(std::string font, std::tuple<int, int, int> color, int grid_x, int grid_y, std::string str, int value);
		static void Write(std::string font, std::tuple<int, int, int> color, int grid_x, int grid_y, std::string str, double value);
		static void Write(std::string font, std::tuple<int, int, int> color, int grid_x, int grid_y, std::string str, std::string value);
	private:
		static std::map<std::string, int> font_map_;
		static std::deque<StringOutput> string_output_deque_;
	};

}


