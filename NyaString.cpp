#include "NyaString.h"

//////////////////////////
// ビルドできるファイル
//////////////////////////

using namespace std;
using namespace H2NLIB;

deque<StringData> NyaString::deque_string_data_;
map<string, int> NyaString::map_string_style_;

NyaString::NyaString()
{

}


NyaString::~NyaString()
{

}

void NyaString::Init(std::string style_name, int font_size, int font_thick)
{
	int style = CreateFontToHandle( style_name.c_str(), font_size, font_thick);
	map_string_style_.insert(make_pair(style_name, style));
}


void NyaString::Write(string style, int x, int y, string str)
{
	StringData sd;

	sd.pos_x_ = x;
	sd.pos_y_ = y;
	sd.str_ = str;
	sd.style_ = map_string_style_.at(style);
	sd.type_i_ = false;
	sd.type_d_ = false;
	deque_string_data_.push_back(sd);
}


void NyaString::Write(string style, int x, int y, string str, int val)
{
	StringData sd;

	sd.pos_x_ = x;
	sd.pos_y_ = y;
	sd.str_ = str;
	sd.style_ = map_string_style_.at(style);
	sd.type_i_ = true;
	sd.type_d_ = false;
	sd.val_i_ = val;
	deque_string_data_.push_back(sd);
}


void NyaString::Write(string style, int x, int y, string str, double val)
{
	StringData sd;

	sd.pos_x_ = x;
	sd.pos_y_ = y;
	sd.str_ = str;
	sd.style_ = map_string_style_.at(style);
	sd.type_i_ = false;
	sd.type_d_ = true;
	sd.val_d_ = val;
	deque_string_data_.push_back(sd);
}


void NyaString::Run(void)
{
	StringData sd;
	int color = GetColor(255, 255, 255);

	while (!deque_string_data_.empty()) {
		sd = deque_string_data_.front();
		if (sd.type_i_) {
			DrawFormatStringToHandle(sd.pos_x_, sd.pos_y_, color, sd.style_, sd.str_.c_str(), sd.val_i_);
		} else if (sd.type_d_) {
			DrawFormatStringToHandle(sd.pos_x_, sd.pos_y_, color, sd.style_, sd.str_.c_str(), sd.val_d_);
		} else {
			DrawStringToHandle(sd.pos_x_, sd.pos_y_, sd.str_.c_str(), color, sd.style_);
		}
		deque_string_data_.pop_front();
	}
}

