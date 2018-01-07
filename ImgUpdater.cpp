#include <fstream>
#include "DxLib.h"
#include "FpsManager.h"
#include "ImgUpdater.h"
#include "DebugPrint.h"
#define __DEBUG__

using namespace NH2;
using namespace NH3;
static int debug_imgnum = 0;


ImgUpdater::ImgUpdater(void)
{

}

ImgUpdater::~ImgUpdater(void)
{

}

/*!
@brief �O���t�B�b�N�X�V�֐�
@param �Ȃ�
@return �Ȃ�
@note
DXLIB�֐������̂܂܎g���ƕ`��D�揇�ʂ��Ǘ����Â炢���߁C
Img�g�[�N���̔z���p�ӂ��ĊǗ�����B
Img�g�[�N���z��̗v�f����Run()���Ăяo�����ɃN���A�����̂ŁC
�����ĕ`�悵�����Ƃ���Run()���Ăяo������ImgManager::Draw()�ŕ`�����o�^����B
*/
void ImgUpdater::Run(void)
{

	// �`�揈��
	// �ϐ�id_draw_�N���A
	for (int layer = 0; layer < eOBJECT::GROUP::sizeof_enum; layer++) {
		Draw(layer);
		id_draw_[layer] = 0;
	}
	// �ϐ�swing_time_y_�X�V
	if (swing_time_y_ != 0)
		swing_time_y_--;

	#ifdef __DEBUG__
		DebugPrint::SetData(615, 240, "img_num_: %d", debug_imgnum);
		debug_imgnum = 0;
	#endif
}

/**
@brief �`��֐�
@param layer �`�悷�郌�C���[
*/
void ImgUpdater::Draw(int layer)
{
	int swing_x = 0;
	int swing_y = 0;
	static ImgToken* itoken;



	// �U�������擾
	GetSwingScale(layer, &swing_x, &swing_y);


	for (unsigned int i = 0; i < id_draw_[layer]; i++) {

	#ifdef __DEBUG__
		debug_imgnum++;
	#endif

		// �`�揈��
		itoken = &vec_itoken_[layer][i];
		switch (vec_itoken_[layer][i].draw_type_) {
		case eIMG::DRAW::TYPE1:
			DrawGraph(itoken->param1_.x_ + swing_x, itoken->param1_.y_ + swing_y,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param1_.flag_trans_);
			break;
		case eIMG::DRAW::TYPE2:
			DrawTurnGraph(itoken->param2_.pos_x_ + swing_x, itoken->param2_.pos_y_ + swing_y,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param2_.flag_trans_);
			break;
		case eIMG::DRAW::TYPE3:
			DrawExtendGraph(itoken->param3_.pos_x1_ + swing_x, itoken->param3_.pos_y1_+ swing_y,
				itoken->param3_.pos_x2_ + swing_x, itoken->param3_.pos_y2_ + swing_y, 
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param3_.flag_trans_);
			break;
		case eIMG::DRAW::TYPE4:
			DrawRotaGraph(itoken->param4_.pos_cx_ + swing_x, itoken->param4_.pos_cy_ + swing_y,
				itoken->param4_.extend_rate_, itoken->param4_.draw_angle_,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param4_.flag_trans_, itoken->param4_.flag_turn_);
			break;
		case eIMG::DRAW::TYPE5:
			DrawRotaGraph2(itoken->param5_.pos_x_ + swing_x, itoken->param5_.pos_y_ + swing_y, 
				itoken->param5_.pos_cx_ + swing_x, itoken->param5_.pos_cy_ + swing_y,
				itoken->param5_.extend_rate_, itoken->param5_.draw_angle_, 
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param5_.flag_trans_, itoken->param5_.flag_turn_);
			break;
		case eIMG::DRAW::TYPE6:
			DrawRotaGraph3(itoken->param6_.pos_x_ + swing_x, itoken->param6_.pos_y_ + swing_y, 
				itoken->param6_.pos_cx_ + swing_x, itoken->param6_.pos_cy_ + swing_y,
				itoken->param6_.extend_ratex_, itoken->param6_.extend_ratey_, itoken->param6_.draw_angle_,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param6_.flag_trans_, itoken->param6_.flag_turn_);
			break;
		case eIMG::DRAW::TYPE7:
			DrawModiGraph(itoken->param7_.pos_x1_ + swing_x, itoken->param7_.pos_y1_ + swing_y, 
				itoken->param7_.pos_x2_ + swing_x, itoken->param7_.pos_y2_ + swing_y,
				itoken->param7_.pos_x3_ + swing_x, itoken->param7_.pos_y3_ + swing_y, 
				itoken->param7_.pos_x4_ + swing_x, itoken->param7_.pos_y4_ + swing_y,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param7_.flag_trans_);
			break;
		case eIMG::DRAW::TYPE8:
			DrawRectGraph(itoken->param8_.pos_dx_ + swing_x, itoken->param8_.pos_dy_ + swing_y, 
				itoken->param8_.pos_sx_ + swing_x, itoken->param8_.pos_sy_ + swing_y,
				itoken->param8_.val_width_, itoken->param8_.val_height_, 
				vec_iload_[itoken->id_].file_[itoken->div_],itoken->param8_.flag_trans_, itoken->param8_.flag_turn_);
			break;
		case eIMG::DRAW::TYPE1B:
			SetDrawBlendMode(itoken->param1b_.blend_mode_, itoken->param1b_.blend_alpha_);
			DrawGraph(itoken->param1b_.pos_x_ + swing_x, itoken->param1b_.pos_y_ + swing_y,
			vec_iload_[itoken->id_].file_[itoken->div_], itoken->param1b_.flag_trans_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case eIMG::DRAW::TYPE2B:
			SetDrawBlendMode(itoken->param2b_.blend_mode_, itoken->param2b_.blend_alpha_);
			DrawTurnGraph(itoken->param2b_.pos_x_ + swing_x, itoken->param2b_.pos_y_ + swing_y, 
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param2b_.flag_trans_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case eIMG::DRAW::TYPE3B:
			SetDrawBlendMode(itoken->param3b_.blend_mode_, itoken->param3b_.blend_alpha_);
			DrawExtendGraph(itoken->param3b_.pos_x1_ + swing_x, itoken->param3b_.pos_y1_ + swing_y, 
				itoken->param3b_.pos_x2_ + swing_x, itoken->param3b_.pos_y2_ + swing_y, 
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param3b_.flag_trans_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case eIMG::DRAW::TYPE4B:
			SetDrawBlendMode(itoken->param4b_.blend_mode_, itoken->param4b_.blend_alpha_);
			DrawRotaGraph(itoken->param4b_.pos_cx_ + swing_x, itoken->param4b_.pos_cy_,
				itoken->param4b_.extend_rate_, itoken->param4b_.draw_angle_,
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param4b_.flag_trans_, itoken->param4b_.flag_turn_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case eIMG::DRAW::TYPE5B:
			SetDrawBlendMode(itoken->param5b_.blend_mode_, itoken->param5b_.blend_alpha_);
			DrawRotaGraph2(itoken->param5b_.pos_x_ + swing_x, itoken->param5b_.pos_y_ + swing_y, 
				itoken->param5b_.pos_cx_ + swing_x, itoken->param5b_.pos_cy_ + swing_y,
				itoken->param5b_.extend_rate_, itoken->param5b_.draw_angle_, 
				vec_iload_[itoken->id_].file_[itoken->div_], itoken->param5b_.flag_trans_, itoken->param5b_.flag_turn_);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		default:
			break;
		}
	}
}


/**
@brief �`��֐�
@param *x �U�������i�[���ĕԂ�
@param *y �U�������i�[���ĕԂ�
@note
 �������A��O�����A�ɐU�������i�[���邪�A�������͍��̂Ƃ��뗘�p���Ȃ��̂ŕω����Ȃ��B
*/
void ImgUpdater::GetSwingScale(int layer, int *x, int *y)
{
	if (swing_time_y_ == 0)
		return;

	switch(layer) {
		case eOBJECT::MAP_BOTTOM:
		case eOBJECT::GROUP::TARGET_ARMS_EFFECT:
		case eOBJECT::GROUP::TARGET_ARMS_SMALL:
		case eOBJECT::GROUP::TARGET_ARMS_LARGE:
		case eOBJECT::GROUP::TARGET_RUN_FLY:
		case eOBJECT::GROUP::TARGET_RUN_WALK:
		case eOBJECT::GROUP::USER:
		case eOBJECT::GROUP::USER_ARMS:
		case eOBJECT::GROUP::USER_ARMS_EFFECT:
		case eOBJECT::GROUP::USER_EFFECT:
			*y = (swing_time_y_ % 4 == 0) ? swing_scale_y_ : (swing_scale_y_ % 4 == 2) ? -swing_scale_y_ : 0 ;
			break;
	}
}