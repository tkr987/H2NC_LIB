#include <fstream>
#include <iomanip>
#include <iostream>
#include "DxLib.h"
#include "NyaInput.h"
#include "NyaInterface.h"


using namespace std;
using namespace HNLIB;

unsigned int NyaInput::count_frame_ = 0;
mt19937 NyaInput::mt_rand_;
stringstream NyaInput::output_date_;
stringstream NyaInput::output_seed_;
deque<int> NyaInput::save_state_collection_;
bool NyaInput::state_now_[static_cast<int>(eINPUT::sizeof_enum)];
bool NyaInput::state_pre_[static_cast<int>(eINPUT::sizeof_enum)];


void NyaInput::Init(void)
{
	int seed_value = 0;
	time_t system_time;
	tm local_time;

	output_date_.str("");
	output_date_.clear(stringstream::goodbit);
	output_seed_.str("");
	output_seed_.clear(stringstream::goodbit);

	system_time = time(nullptr);
	localtime_s(&local_time, &system_time);
	seed_value = local_time.tm_year + local_time.tm_mon + local_time.tm_mday + local_time.tm_hour + local_time.tm_min;
	mt_rand_.seed(seed_value);
	output_seed_ << seed_value;
	output_date_ << local_time.tm_year+1900;
	output_date_ << "/";
	if (local_time.tm_mon < 9)
		output_date_ << "0";
	output_date_ << local_time.tm_mon + 1;
	output_date_ << "/";
	output_date_ << local_time.tm_mday;
	output_date_ << " ";
	if (local_time.tm_hour < 10)
		output_date_ << "0";
	output_date_ << local_time.tm_hour;
	output_date_ << ":";
	if (local_time.tm_min < 10)
		output_date_ << "0";
	output_date_ << local_time.tm_min;
	save_state_collection_.clear();
}

bool NyaInput::InputReplay(string file_name)
{
	string line;
	ifstream ifs;
	
	// �t�@�C���I�[�v��
	// �t�@�C�����Ȃ���Ή��������I��
	ifs.open(file_name);
	if (!ifs.is_open())
		return false;

	// 1�s�ڂ͗����̃V�[�h
	getline(ifs, line);
	mt_rand_.seed(std::atoi(line.c_str()));
	// 2�s�ڂ͓����Ȃ̂œǂݔ�΂�
	getline(ifs, line);
	// �^�C�g���Ȃ̂�3�s�ڂ��ǂݔ�΂�
	getline(ifs, line);	
	// ���v���C�t�@�C���ɏ����ꂽ�L�[���͂̓��e��S�ēǂݍ���
	while (getline(ifs, line))
	{
		save_state_collection_.push_back(atoi(line.c_str()));
		line.clear();
	}

	// �t�@�C���N���[�Y
	// true��Ԃ��ďI��
	ifs.close();
	return true;
}

void NyaInput::OutputReplay(string file_name)
{
	ofstream ofs(file_name);

	ofs << output_seed_.str();
	ofs << endl;
	ofs << output_date_.str();
	ofs << endl;
	ofs << NyaInterface::GetHandleTitle()->name_.str();
	ofs << endl;

	for (auto& e : save_state_collection_)
	{
		ofs << e;
		ofs << endl;
	}

	ofs.close();
}

void NyaInput::Run(eEVENT check_event)
{
	int save_state = 0;
	int replay_state = 0;

	// �O�t���[���̃L�[��Ԃ��Z�b�g
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
    // �����͂��ꂽ�L�[��Ԃ��Z�b�g
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

	// �����͂��ꂽ�L�[��Ԃ�ۑ�����
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

	// ���v���C�t�@�C������̓���
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
		state_now_[static_cast<int>(eINPUT::SPACE)]		 = ((replay_state & (1 << static_cast<int>(eINPUT::SPACE))) != 0) ? true : false;
		save_state_collection_.pop_front();
	}

	count_frame_++;
}
	