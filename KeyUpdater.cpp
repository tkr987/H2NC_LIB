#include "DxLib.h"
#include "KeyUpdater.h"

using namespace NH2;
using namespace NH3;

KeyUpdater::KeyUpdater()
{
	// キーコンフィグ読み込み
	fin_.open("keyconfig.ini", std::ios_base::in);
	fin_ >> key1_;
	fin_ >> key2_;
	fin_ >> key3_;
	fin_.close() ;

	// データクリア
	for (int i = 0; i < eKEY::sizeof_enum; i++) {
		flag_pre_[i] = false;
		flag_now_[i] = false;
	}
}


void KeyUpdater::Run(void){
	/*前フレームのキーフラグをセット*/
	flag_pre_[eKEY::ENTER]            = flag_now_[eKEY::ENTER];
	flag_pre_[eKEY::UP]               = flag_now_[eKEY::UP];
    flag_pre_[eKEY::RIGHT]            = flag_now_[eKEY::RIGHT];
    flag_pre_[eKEY::DOWN]             = flag_now_[eKEY::DOWN];
    flag_pre_[eKEY::LEFT]             = flag_now_[eKEY::LEFT];
    flag_pre_[eKEY::ARMS]             = flag_now_[eKEY::ARMS];
    flag_pre_[eKEY::SLOW]             = flag_now_[eKEY::SLOW];
	flag_pre_[eKEY::EXARMS]           = flag_now_[eKEY::EXARMS];
    /*現入力されたキーのフラグをセット*/
    flag_now_[eKEY::ENTER]            = ( CheckHitKey(KEY_INPUT_RETURN) != 0) ? true : false ;
    flag_now_[eKEY::UP]               = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP)    != 0 ) ? true : false ;
    flag_now_[eKEY::RIGHT]            = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 ) ? true : false ;
    flag_now_[eKEY::DOWN]             = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN)  != 0 ) ? true : false ;
    flag_now_[eKEY::LEFT]             = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT)  != 0 ) ? true : false ;
    flag_now_[eKEY::ARMS]             = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1)     != 0 ) ? true : false ; 
    flag_now_[eKEY::SLOW]             = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_2)     != 0 ) ? true : false ;
    flag_now_[eKEY::EXARMS]           = ( (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_3)     != 0 ) ? true : false ; 
}

