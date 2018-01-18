#include "NyaString.h"


using namespace std;
using namespace H2NLIB;

deque<StringSet> NyaString::deque_string_set_;
map<string, int> NyaString::map_font_;

NyaString::NyaString()
{

}


NyaString::~NyaString()
{

}

void NyaString::SettingFont(std::string font_name, int font_size, int font_thick)
{
	int font = CreateFontToHandle( font_name.c_str(), font_size, font_thick);
	map_font_.insert(make_pair(font_name, font));
}


void NyaString::Write(string font, std::tuple<int, int, int> color, int x, int y, string str)
{
	StringSet ss;

	ss.color_ = GetColor(get<0>(color), get<1>(color), get<2>(color));
	ss.font_ = map_font_.at(font);
	ss.x_ = x;
	ss.y_ = y;
	get<0>(ss.write_double_) = false;
	get<0>(ss.write_int_) = false;
	get<0>(ss.write_string_) = true;
	get<1>(ss.write_string_) = str;

	deque_string_set_.push_back(ss);
}


void NyaString::Write(string font, std::tuple<int, int, int> color, int x, int y, string str, int value)
{
	StringSet ss;

	ss.color_ = GetColor(get<0>(color), get<1>(color), get<2>(color));
	ss.font_ = map_font_.at(font);
	ss.x_ = x;
	ss.y_ = y;
	get<0>(ss.write_double_) = false;
	get<0>(ss.write_int_) = true;
	get<1>(ss.write_int_) = str;
	get<2>(ss.write_int_) = value;
	get<0>(ss.write_string_) = false;

	deque_string_set_.push_back(ss);
}


void NyaString::Write(string font, std::tuple<int, int, int> color, int x, int y, string str, double value)
{
	StringSet ss;

	ss.color_ = GetColor(get<0>(color), get<1>(color), get<2>(color));
	ss.font_ = map_font_.at(font);
	ss.x_ = x;
	ss.y_ = y;
	get<0>(ss.write_double_) = true;
	get<1>(ss.write_double_) = str;
	get<2>(ss.write_double_) = value;
	get<0>(ss.write_int_) = false;
	get<0>(ss.write_string_) = false;

	deque_string_set_.push_back(ss);
}


void NyaString::Run(void)
{
	StringSet ss;

	while (!deque_string_set_.empty()) {
		ss = deque_string_set_.front();
		if (get<0>(ss.write_double_)) {
			DrawFormatStringToHandle(ss.x_, ss.y_, ss.color_, ss.font_, get<1>(ss.write_double_).c_str(), get<2>(ss.write_double_));
		} else if (get<0>(ss.write_int_)) {
			DrawFormatStringToHandle(ss.x_, ss.y_, ss.color_, ss.font_, get<1>(ss.write_int_).c_str(), get<2>(ss.write_int_));
		} else {
			DrawStringToHandle(ss.x_, ss.y_, get<1>(ss.write_string_).c_str(), ss.color_, ss.font_);
		}
		deque_string_set_.pop_front();
	}
}

