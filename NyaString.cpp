#include "DxLib.h"
#include "NyaString.h"


using namespace std;
using namespace H2NLIB;

deque<StringOutput> NyaString::string_output_deque_;
map<string, int> NyaString::font_map_;

NyaString::NyaString()
{

}


NyaString::~NyaString()
{

}

void NyaString::SettingFont(std::string font_name, int font_size, int font_thick)
{
	auto it = font_map_.find(font_name);

	if (it != font_map_.end())
		return;

	int font = CreateFontToHandle(font_name.c_str(), font_size, font_thick);
	font_map_.insert(make_pair(font_name, font));
}

void NyaString::Write(string font, std::tuple<int, int, int> color, int grid_x, int grid_y, string str)
{
	StringOutput so;

	so.color_ = GetColor(get<0>(color), get<1>(color), get<2>(color));
	try { so.font_ = font_map_.at(font); } catch(std::out_of_range&) { return; }
	so.x_ = grid_x;
	so.y_ = grid_y;
	get<0>(so.write_string_) = true;
	get<1>(so.write_string_) = str;
	get<0>(so.write_value_int_) = false;
	get<0>(so.write_value_double_) = false;
	get<0>(so.write_value_string_) = false;

	string_output_deque_.push_back(so);
}


void NyaString::Write(string font, std::tuple<int, int, int> color, int grid_x, int grid_y, string str, int value)
{
	StringOutput so;

	so.color_ = GetColor(get<0>(color), get<1>(color), get<2>(color));
	try { so.font_ = font_map_.at(font); } catch(std::out_of_range&) { return; }
	so.x_ = grid_x;
	so.y_ = grid_y;
	get<0>(so.write_string_) = false;
	get<0>(so.write_value_int_) = true;
	get<1>(so.write_value_int_) = str;
	get<2>(so.write_value_int_) = value;
	get<0>(so.write_value_double_) = false;
	get<0>(so.write_value_string_) = false;

	string_output_deque_.push_back(so);
}


void NyaString::Write(string font, std::tuple<int, int, int> color, int x, int y, string str, double value)
{
	StringOutput so;

	so.color_ = GetColor(get<0>(color), get<1>(color), get<2>(color));
	try { so.font_ = font_map_.at(font); } catch(std::out_of_range&) { return; }
	so.x_ = x;
	so.y_ = y;
	get<0>(so.write_string_) = false;
	get<0>(so.write_value_int_) = false;
	get<0>(so.write_value_double_) = true;
	get<1>(so.write_value_double_) = str;
	get<2>(so.write_value_double_) = value;
	get<0>(so.write_value_string_) = false;

	string_output_deque_.push_back(so);
}


void NyaString::Write(string font, std::tuple<int, int, int> color, int grid_x, int grid_y, string str, string value)
{
	StringOutput so;

	so.color_ = GetColor(get<0>(color), get<1>(color), get<2>(color));
	try { so.font_ = font_map_.at(font); } catch(std::out_of_range&) { return; }
	so.x_ = grid_x;
	so.y_ = grid_y;
	get<0>(so.write_string_) = false;
	get<0>(so.write_value_int_) = false;
	get<0>(so.write_value_double_) = false;
	get<0>(so.write_value_string_) = true;
	get<1>(so.write_value_string_) = str;
	get<2>(so.write_value_string_) = value;

	string_output_deque_.push_back(so);
}


void NyaString::Run(void)
{
	StringOutput so;

	while (!string_output_deque_.empty())
	{
		so = string_output_deque_.front();

		if (get<0>(so.write_value_int_))
		{
			DrawFormatStringToHandle(so.x_, so.y_, so.color_, so.font_, get<1>(so.write_value_int_).c_str(), get<2>(so.write_value_int_));
		}
		else if (get<0>(so.write_value_double_)) 
		{
			DrawFormatStringToHandle(so.x_, so.y_, so.color_, so.font_, get<1>(so.write_value_double_).c_str(), get<2>(so.write_value_double_));
		} 
		else if (get<0>(so.write_value_string_))
		{
			DrawFormatStringToHandle(so.x_, so.y_, so.color_, so.font_, get<1>(so.write_value_string_).c_str(), get<2>(so.write_value_string_).c_str());
		}
		else
		{
			DrawStringToHandle(so.x_, so.y_, get<1>(so.write_string_).c_str(), so.color_, so.font_);
		}
		string_output_deque_.pop_front();
	}
}

