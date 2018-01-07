#include "KeyManager.h"

using namespace NH2;

int KeyManager::key1_;
int KeyManager::key2_;
int KeyManager::key3_;
bool KeyManager::flag_now_[eKEY::sizeof_enum];
bool KeyManager::flag_pre_[eKEY::sizeof_enum];

void KeyManager::Clear(void)
{


}