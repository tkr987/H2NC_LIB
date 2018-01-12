#include "DxLib.h"
#include "NyaInput.h"


using namespace H2NLIB;


int NyaInput::key1_;
int NyaInput::key2_;
int NyaInput::key3_;
int NyaInput::key4_;
bool NyaInput::flag_now_[eINPUT::KEY::sizeof_enum];
bool NyaInput::flag_pre_[eINPUT::KEY::sizeof_enum];



NyaInput::NyaInput()
{

}


NyaInput::~NyaInput()
{

}

void NyaInput::Run(void){
	/*前フレームのキーフラグをセット*/
	flag_pre_[eINPUT::KEY::ENTER]		= flag_now_[eINPUT::KEY::ENTER];
	flag_pre_[eINPUT::KEY::UP]			= flag_now_[eINPUT::KEY::UP];
    flag_pre_[eINPUT::KEY::RIGHT]       = flag_now_[eINPUT::KEY::RIGHT];
    flag_pre_[eINPUT::KEY::DOWN]        = flag_now_[eINPUT::KEY::DOWN];
    flag_pre_[eINPUT::KEY::LEFT]        = flag_now_[eINPUT::KEY::LEFT];
    flag_pre_[eINPUT::KEY::Z]           = flag_now_[eINPUT::KEY::Z];
    flag_pre_[eINPUT::KEY::X]           = flag_now_[eINPUT::KEY::X];
	flag_pre_[eINPUT::KEY::C]           = flag_now_[eINPUT::KEY::C];
	flag_pre_[eINPUT::KEY::V]           = flag_now_[eINPUT::KEY::V];
    /*現入力されたキーのフラグをセット*/
    flag_now_[eINPUT::KEY::ENTER]		= ( CheckHitKey(KEY_INPUT_RETURN) != 0) ? true : false ;
    flag_now_[eINPUT::KEY::UP]          = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)    != 0 ) ? true : false ;
    flag_now_[eINPUT::KEY::RIGHT]       = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 ) ? true : false ;
    flag_now_[eINPUT::KEY::DOWN]        = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)  != 0 ) ? true : false ;
    flag_now_[eINPUT::KEY::LEFT]        = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)  != 0 ) ? true : false ;
    flag_now_[eINPUT::KEY::Z]			= ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1)     != 0 ) ? true : false ; 
    flag_now_[eINPUT::KEY::X]           = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_2)     != 0 ) ? true : false ;
    flag_now_[eINPUT::KEY::C]           = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_3)     != 0 ) ? true : false ; 
    flag_now_[eINPUT::KEY::V]           = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_4)     != 0 ) ? true : false ; 
}