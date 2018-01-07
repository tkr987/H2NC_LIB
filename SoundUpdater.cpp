#include "DxLib.h"
#include "SoundUpdater.h"

using namespace NH2;
using namespace NH3;

SoundUpdater::SoundUpdater(void)
{

}

SoundUpdater::~SoundUpdater(void)
{

}

/*!
@brief サウンド更新関数
@note
 サウンドを再生し、初期値にクリアする。
*/
void SoundUpdater::Run(void)
{
	//for (int i = 0; i < splay_num_; i++)
	//	DxLib::PlaySoundMem(vec_splay_[i].id_, vec_splay_[i].mode_, vec_splay_[i].posflag_);
	splay_num_ = 0;
}

