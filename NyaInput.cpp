#include "DxLib.h"
#include "NyaInput.h"


using namespace H2NLIB;

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
    flag_pre_[eINPUT::KEY::Q]           = flag_now_[eINPUT::KEY::Q];
    flag_pre_[eINPUT::KEY::W]           = flag_now_[eINPUT::KEY::W];
	flag_pre_[eINPUT::KEY::E]           = flag_now_[eINPUT::KEY::E];
	flag_pre_[eINPUT::KEY::R]           = flag_now_[eINPUT::KEY::R];
	flag_pre_[eINPUT::KEY::SPACE]       = flag_now_[eINPUT::KEY::SPACE];
    /*現入力されたキーのフラグをセット*/
    flag_now_[eINPUT::KEY::ENTER]		= ( CheckHitKey(KEY_INPUT_RETURN) != 0) ? true : false ;
    flag_now_[eINPUT::KEY::UP]          = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)    != 0 ) ? true : false ;
    flag_now_[eINPUT::KEY::RIGHT]       = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 ) ? true : false ;
    flag_now_[eINPUT::KEY::DOWN]        = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)  != 0 ) ? true : false ;
    flag_now_[eINPUT::KEY::LEFT]        = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)  != 0 ) ? true : false ;
    flag_now_[eINPUT::KEY::Q]			= ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || CheckHitKey(KEY_INPUT_Q) != 0 ) ? true : false ; 
    flag_now_[eINPUT::KEY::W]           = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0 || CheckHitKey(KEY_INPUT_W) != 0 ) ? true : false ;
    flag_now_[eINPUT::KEY::E]           = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0 || CheckHitKey(KEY_INPUT_E) != 0 ) ? true : false ; 
    flag_now_[eINPUT::KEY::R]           = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0 || CheckHitKey(KEY_INPUT_R) != 0 ) ? true : false ; 
    flag_now_[eINPUT::KEY::SPACE]       = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0 || CheckHitKey(KEY_INPUT_SPACE) != 0 ) ? true : false ; 
}