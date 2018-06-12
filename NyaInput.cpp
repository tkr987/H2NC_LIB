#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "DxLib.h"
#include "NyaInput.h"


using namespace std;
using namespace H2NLIB;

std::deque<int> NyaInput::save_state_collection_;
bool NyaInput::state_now_[static_cast<int>(eINPUT::sizeof_enum)];
bool NyaInput::state_pre_[static_cast<int>(eINPUT::sizeof_enum)];


void NyaInput::InputFile(string file_name)
{
	string line;
	ifstream ifs(file_name);

	// 1行目は日時なので読み飛ばす
	getline(ifs, line);
	
	// リプレイファイルに書かれたキー入力の内容を全て読み込む
	while (getline(ifs, line))
	{
		save_state_collection_.push_back(atoi(line.c_str()));
		line.clear();
	}

	ifs.close();
}

void NyaInput::OutputFile(string file_name)
{
	ofstream ofs(file_name);
	time_t time_;
	tm local_time;
	stringstream output_time;

	if (!save_state_collection_.empty())
	{



		time_ = time(nullptr);
		localtime_s(&local_time, &time_);
//		output_time << "20";
		output_time << local_time.tm_year+1900;
//		output_time << local_time.tm_year-100;
		output_time << "/";
		output_time << local_time.tm_mon + 1;
		output_time << "/";
		output_time << local_time.tm_mday;
		output_time << " ";
		output_time << local_time.tm_hour;
		output_time << ":";
		output_time << local_time.tm_min;
		ofs << output_time.str();
		ofs << endl;
	}


	while (!save_state_collection_.empty())
	{
		ofs << save_state_collection_.front();
		ofs << endl;
		save_state_collection_.pop_front();
	}

	ofs.close();
}

void NyaInput::Run(eEVENT check_event)
{
	int save_state = 0;
	int replay_state = 0;

	// 前フレームのキー状態をセット
	state_pre_[static_cast<int>(eINPUT::UP)]		= state_now_[static_cast<int>(eINPUT::UP)];
    state_pre_[static_cast<int>(eINPUT::RIGHT)]		= state_now_[static_cast<int>(eINPUT::RIGHT)];
    state_pre_[static_cast<int>(eINPUT::DOWN)]		= state_now_[static_cast<int>(eINPUT::DOWN)];
    state_pre_[static_cast<int>(eINPUT::LEFT)]		= state_now_[static_cast<int>(eINPUT::LEFT)];
    state_pre_[static_cast<int>(eINPUT::Q)]			= state_now_[static_cast<int>(eINPUT::Q)];
    state_pre_[static_cast<int>(eINPUT::W)]			= state_now_[static_cast<int>(eINPUT::W)];
	state_pre_[static_cast<int>(eINPUT::E)]			= state_now_[static_cast<int>(eINPUT::E)];
	state_pre_[static_cast<int>(eINPUT::R)]			= state_now_[static_cast<int>(eINPUT::R)];
	state_pre_[static_cast<int>(eINPUT::SPACE)]		= state_now_[static_cast<int>(eINPUT::SPACE)];
	state_pre_[static_cast<int>(eINPUT::ENTER)]		= state_now_[static_cast<int>(eINPUT::ENTER)];
    // 現入力されたキー状態をセット
    state_now_[static_cast<int>(eINPUT::UP)]		= ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)    != 0 ) ? true : false ;
    state_now_[static_cast<int>(eINPUT::RIGHT)]		= ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 ) ? true : false ;
    state_now_[static_cast<int>(eINPUT::DOWN)]		= ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)  != 0 ) ? true : false ;
    state_now_[static_cast<int>(eINPUT::LEFT)]		= ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)  != 0 ) ? true : false ;
    state_now_[static_cast<int>(eINPUT::Q)]			= ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || CheckHitKey(KEY_INPUT_Q) != 0 ) ? true : false ; 
    state_now_[static_cast<int>(eINPUT::W)]			= ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0 || CheckHitKey(KEY_INPUT_W) != 0 ) ? true : false ;
    state_now_[static_cast<int>(eINPUT::E)]			= ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0 || CheckHitKey(KEY_INPUT_E) != 0 ) ? true : false ; 
    state_now_[static_cast<int>(eINPUT::R)]			= ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0 || CheckHitKey(KEY_INPUT_R) != 0 ) ? true : false ; 
    state_now_[static_cast<int>(eINPUT::SPACE)]		= ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0 || CheckHitKey(KEY_INPUT_SPACE) != 0 ) ? true : false ; 
    state_now_[static_cast<int>(eINPUT::ENTER)]		= ( CheckHitKey(KEY_INPUT_RETURN) != 0 ) ? true : false ;

	// 現入力されたキー状態を保存する
	if (check_event == eEVENT::MISSION_RUN)
	{
		save_state = (state_now_[static_cast<int>(eINPUT::UP)]) ? save_state | (1 << static_cast<int>(eINPUT::UP)) : save_state;
		save_state = (state_now_[static_cast<int>(eINPUT::RIGHT)]) ? save_state | (1 << static_cast<int>(eINPUT::RIGHT)) : save_state;
		save_state = (state_now_[static_cast<int>(eINPUT::DOWN)]) ? save_state | (1 << static_cast<int>(eINPUT::DOWN)) : save_state;
		save_state = (state_now_[static_cast<int>(eINPUT::LEFT)]) ? save_state | (1 << static_cast<int>(eINPUT::LEFT)) : save_state;
		save_state = (state_now_[static_cast<int>(eINPUT::Q)]) ? save_state | (1 << static_cast<int>(eINPUT::Q)) : save_state;
		save_state = (state_now_[static_cast<int>(eINPUT::W)]) ? save_state | (1 << static_cast<int>(eINPUT::W)) : save_state;
		save_state = (state_now_[static_cast<int>(eINPUT::E)]) ? save_state | (1 << static_cast<int>(eINPUT::E)) : save_state;
		save_state = (state_now_[static_cast<int>(eINPUT::R)]) ? save_state | (1 << static_cast<int>(eINPUT::R)) : save_state;
		save_state = (state_now_[static_cast<int>(eINPUT::SPACE)]) ? save_state | (1 << static_cast<int>(eINPUT::SPACE)) : save_state;
		save_state_collection_.push_back(save_state);
	}

	// リプレイファイルからの入力
	if (check_event == eEVENT::MISSION_REPLAY_RUN && !save_state_collection_.empty())
	{
		replay_state = save_state_collection_.front();
		state_now_[static_cast<int>(eINPUT::UP)]         = ((replay_state & (1 << static_cast<int>(eINPUT::UP))) != 0 ) ? true : false;
		state_now_[static_cast<int>(eINPUT::RIGHT)]      = ((replay_state & (1 << static_cast<int>(eINPUT::RIGHT))) != 0 ) ? true : false;
		state_now_[static_cast<int>(eINPUT::DOWN)]       = ((replay_state & (1 << static_cast<int>(eINPUT::DOWN))) != 0 ) ? true : false;
		state_now_[static_cast<int>(eINPUT::LEFT)]       = ((replay_state & (1 << static_cast<int>(eINPUT::LEFT))) != 0 ) ? true : false;
		state_now_[static_cast<int>(eINPUT::Q)]			 = ((replay_state & (1 << static_cast<int>(eINPUT::Q))) != 0 ) ? true : false; 
		state_now_[static_cast<int>(eINPUT::W)]          = ((replay_state & (1 << static_cast<int>(eINPUT::W))) != 0 ) ? true : false;
		state_now_[static_cast<int>(eINPUT::E)]          = ((replay_state & (1 << static_cast<int>(eINPUT::E))) != 0 ) ? true : false; 
		state_now_[static_cast<int>(eINPUT::R)]          = ((replay_state & (1 << static_cast<int>(eINPUT::R))) != 0 ) ? true : false; 
		state_now_[static_cast<int>(eINPUT::SPACE)]		= ((replay_state & (1 << static_cast<int>(eINPUT::SPACE))) != 0) ? true : false;
		state_now_[static_cast<int>(eINPUT::ENTER)]		= ((replay_state & (1 << static_cast<int>(eINPUT::ENTER))) != 0) ? true : false;
		save_state_collection_.pop_front();
	}
}
	