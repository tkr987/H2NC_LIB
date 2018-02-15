#include "DxLib.h"
#include "NyaInput.h"


using namespace H2NLIB;

bool NyaInput::flag_now_[eINPUT::NUM::sizeof_enum];
bool NyaInput::flag_pre_[eINPUT::NUM::sizeof_enum];



NyaInput::NyaInput()
{

}


NyaInput::~NyaInput()
{

}

void NyaInput::Run(void){
	/*前フレームのキーフラグをセット*/
	flag_pre_[eINPUT::NUM::ENTER]		= flag_now_[eINPUT::NUM::ENTER];
	flag_pre_[eINPUT::NUM::UP]			= flag_now_[eINPUT::NUM::UP];
    flag_pre_[eINPUT::NUM::RIGHT]       = flag_now_[eINPUT::NUM::RIGHT];
    flag_pre_[eINPUT::NUM::DOWN]        = flag_now_[eINPUT::NUM::DOWN];
    flag_pre_[eINPUT::NUM::LEFT]        = flag_now_[eINPUT::NUM::LEFT];
    flag_pre_[eINPUT::NUM::Q]           = flag_now_[eINPUT::NUM::Q];
    flag_pre_[eINPUT::NUM::W]           = flag_now_[eINPUT::NUM::W];
	flag_pre_[eINPUT::NUM::E]           = flag_now_[eINPUT::NUM::E];
	flag_pre_[eINPUT::NUM::R]           = flag_now_[eINPUT::NUM::R];
	flag_pre_[eINPUT::NUM::SPACE]       = flag_now_[eINPUT::NUM::SPACE];
    /*現入力されたキーのフラグをセット*/
    flag_now_[eINPUT::NUM::ENTER]		= ( CheckHitKey(KEY_INPUT_RETURN) != 0) ? true : false ;
    flag_now_[eINPUT::NUM::UP]          = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)    != 0 ) ? true : false ;
    flag_now_[eINPUT::NUM::RIGHT]       = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 ) ? true : false ;
    flag_now_[eINPUT::NUM::DOWN]        = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)  != 0 ) ? true : false ;
    flag_now_[eINPUT::NUM::LEFT]        = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)  != 0 ) ? true : false ;
    flag_now_[eINPUT::NUM::Q]			= ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || CheckHitKey(KEY_INPUT_Q) != 0 ) ? true : false ; 
    flag_now_[eINPUT::NUM::W]           = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0 || CheckHitKey(KEY_INPUT_W) != 0 ) ? true : false ;
    flag_now_[eINPUT::NUM::E]           = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0 || CheckHitKey(KEY_INPUT_E) != 0 ) ? true : false ; 
    flag_now_[eINPUT::NUM::R]           = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0 || CheckHitKey(KEY_INPUT_R) != 0 ) ? true : false ; 
    flag_now_[eINPUT::NUM::SPACE]       = ( (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0 || CheckHitKey(KEY_INPUT_SPACE) != 0 ) ? true : false ; 
}