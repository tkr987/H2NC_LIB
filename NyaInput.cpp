#include <filesystem>
#include <fstream>
#include <iostream>
#include "DxLib.h"
#include "NyaInput.h"


using namespace std;
using namespace std::experimental::filesystem;
using namespace H2NLIB;

std::deque<int> NyaInput::save_state_collection_;
bool NyaInput::state_now_[eINPUT::NUM::sizeof_enum];
bool NyaInput::state_pre_[eINPUT::NUM::sizeof_enum];



NyaInput::NyaInput()
{
	create_directory("replay");
}


NyaInput::~NyaInput()
{

}

void NyaInput::InputFile(string file_name)
{
	string line;
	int nya;
	ifstream ifs(file_name);

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

	while (!save_state_collection_.empty())
	{
		ofs << save_state_collection_.front();
		ofs << endl;
		save_state_collection_.pop_front();
	}

	ofs.close();
}

void NyaInput::Run(eEVENT::NUM check_event)
{
	int save_state = 0;
	int replay_state = 0;

	// 前フレームのキー状態をセット
	state_pre_[eINPUT::NUM::UP]			= state_now_[eINPUT::NUM::UP];
    state_pre_[eINPUT::NUM::RIGHT]       = state_now_[eINPUT::NUM::RIGHT];
    state_pre_[eINPUT::NUM::DOWN]        = state_now_[eINPUT::NUM::DOWN];
    state_pre_[eINPUT::NUM::LEFT]        = state_now_[eINPUT::NUM::LEFT];
    state_pre_[eINPUT::NUM::Q]           = state_now_[eINPUT::NUM::Q];
    state_pre_[eINPUT::NUM::W]           = state_now_[eINPUT::NUM::W];
	state_pre_[eINPUT::NUM::E]           = state_now_[eINPUT::NUM::E];
	state_pre_[eINPUT::NUM::R]           = state_now_[eINPUT::NUM::R];
	state_pre_[eINPUT::NUM::SPACE]       = state_now_[eINPUT::NUM::SPACE];
	state_pre_[eINPUT::NUM::ENTER]		= state_now_[eINPUT::NUM::ENTER];
    // 現入力されたキー状態をセット
    state_now_[eINPUT::NUM::UP]          = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)    != 0 ) ? true : false ;
    state_now_[eINPUT::NUM::RIGHT]       = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 ) ? true : false ;
    state_now_[eINPUT::NUM::DOWN]        = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)  != 0 ) ? true : false ;
    state_now_[eINPUT::NUM::LEFT]        = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)  != 0 ) ? true : false ;
    state_now_[eINPUT::NUM::Q]			= ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || CheckHitKey(KEY_INPUT_Q) != 0 ) ? true : false ; 
    state_now_[eINPUT::NUM::W]           = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0 || CheckHitKey(KEY_INPUT_W) != 0 ) ? true : false ;
    state_now_[eINPUT::NUM::E]           = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0 || CheckHitKey(KEY_INPUT_E) != 0 ) ? true : false ; 
    state_now_[eINPUT::NUM::R]           = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0 || CheckHitKey(KEY_INPUT_R) != 0 ) ? true : false ; 
    state_now_[eINPUT::NUM::SPACE]       = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0 || CheckHitKey(KEY_INPUT_SPACE) != 0 ) ? true : false ; 
    state_now_[eINPUT::NUM::ENTER]		= ( CheckHitKey(KEY_INPUT_RETURN) != 0) ? true : false ;
	
	// 現入力されたキー状態を保存する
	if (check_event == eEVENT::MISSION_RUN)
	{
		save_state = (state_now_[eINPUT::NUM::UP]) ? save_state | (1 << eINPUT::NUM::UP) : save_state;
		save_state = (state_now_[eINPUT::NUM::RIGHT]) ? save_state | (1 << eINPUT::NUM::RIGHT) : save_state;
		save_state = (state_now_[eINPUT::NUM::DOWN]) ? save_state | (1 << eINPUT::NUM::DOWN) : save_state;
		save_state = (state_now_[eINPUT::NUM::LEFT]) ? save_state | (1 << eINPUT::NUM::LEFT) : save_state;
		save_state = (state_now_[eINPUT::NUM::Q]) ? save_state | (1 << eINPUT::NUM::Q) : save_state;
		save_state = (state_now_[eINPUT::NUM::W]) ? save_state | (1 << eINPUT::NUM::W) : save_state;
		save_state = (state_now_[eINPUT::NUM::E]) ? save_state | (1 << eINPUT::NUM::E) : save_state;
		save_state = (state_now_[eINPUT::NUM::R]) ? save_state | (1 << eINPUT::NUM::R) : save_state;
		save_state = (state_now_[eINPUT::NUM::SPACE]) ? save_state | (1 << eINPUT::NUM::SPACE) : save_state;
		save_state_collection_.push_back(save_state);
	}

	// リプレイファイルからの入力
	if (check_event == eEVENT::MISSION_REPLAY_RUN)
	{
		replay_state = save_state_collection_.front();
		state_now_[eINPUT::NUM::UP]         = ((replay_state & (1 << eINPUT::NUM::UP)) != 0 ) ? true : false;
		state_now_[eINPUT::NUM::RIGHT]      = ((replay_state & (1 << eINPUT::NUM::RIGHT)) != 0 ) ? true : false;
		state_now_[eINPUT::NUM::DOWN]       = ((replay_state & (1 << eINPUT::NUM::DOWN)) != 0 ) ? true : false;
		state_now_[eINPUT::NUM::LEFT]       = ((replay_state & (1 << eINPUT::NUM::LEFT)) != 0 ) ? true : false;
		state_now_[eINPUT::NUM::Q]			= ((replay_state & (1 << eINPUT::NUM::Q)) != 0 ) ? true : false; 
		state_now_[eINPUT::NUM::W]          = ((replay_state & (1 << eINPUT::NUM::W)) != 0 ) ? true : false;
		state_now_[eINPUT::NUM::E]          = ((replay_state & (1 << eINPUT::NUM::E)) != 0 ) ? true : false; 
		state_now_[eINPUT::NUM::R]          = ((replay_state & (1 << eINPUT::NUM::R)) != 0 ) ? true : false; 
		state_now_[eINPUT::NUM::SPACE]		= ((replay_state & (1 << eINPUT::NUM::SPACE)) != 0) ? true : false;
		state_now_[eINPUT::NUM::ENTER]		= ((replay_state & (1 << eINPUT::NUM::ENTER)) != 0) ? true : false;
		save_state_collection_.pop_front();
	}
}
	