#include <new>
#include "DxLib.h"
#include "DebugPrint.h"
#include "ImgManager.h"
#include "KeyManager.h"
#define IMG_DIV_MAXSIZE 128
#define IMG_FILE_MAXSIZE 512
#define IMG_TOKEN_MAXSIZE 8192
#define __DEBUG__

using namespace std;
using namespace NH2;
unsigned int ImgManager::id_load_;
unsigned int ImgManager::id_draw_[eOBJECT::NUM::sizeof_enum];
int ImgManager::swing_scale_y_;
int ImgManager::swing_time_y_;
vector<ImgLoad> ImgManager::vec_iload_;
vector<ImgToken> ImgManager::vec_itoken_[eOBJECT::NUM::sizeof_enum];


// *************
//  �������֘A
// *************

void ImgManager::Clear(void)
{
	id_load_ = 0;
	for (int i = 0; i < eOBJECT::NUM::sizeof_enum; i++)
		id_draw_[i] = 0;
	swing_scale_y_ = 0;
	swing_time_y_ = 0;

	InitGraph();
}


void ImgManager::End(void)
{

}


void ImgManager::Init(void)
{
	unsigned int itoken_maxsize_[eOBJECT::NUM::sizeof_enum];	// vec_itoken_�̍ő�v�f��

	// �������m�ۍς݂Ȃ牽�����Ȃ�
	if (vec_iload_.size() != 0)
		return;

	itoken_maxsize_[eOBJECT::NUM::TITLE_MAIN] = 32;
	itoken_maxsize_[eOBJECT::NUM::MAP_BOTTOM] = 32;
	itoken_maxsize_[eOBJECT::NUM::STAGE_CONTINUE] = 4;
	itoken_maxsize_[eOBJECT::NUM::STAGE_RESULT] = 32;
	itoken_maxsize_[eOBJECT::NUM::TARGET_READY] = 4;
	itoken_maxsize_[eOBJECT::NUM::TARGET_RUN_FLY] = 1024;
	itoken_maxsize_[eOBJECT::NUM::TARGET_RUN_WALK] = 1024;
	itoken_maxsize_[eOBJECT::NUM::TARGET_EFFECT] = 512;
	itoken_maxsize_[eOBJECT::NUM::USER] = 32;
	itoken_maxsize_[eOBJECT::NUM::USER_EFFECT] = 32;
	itoken_maxsize_[eOBJECT::NUM::USER_ARMS] = 128;
	itoken_maxsize_[eOBJECT::NUM::USER_ARMS_EFFECT] = 128;
	itoken_maxsize_[eOBJECT::NUM::TARGET_ARMS_SMALL] = 2048;
	itoken_maxsize_[eOBJECT::NUM::TARGET_ARMS_LARGE] = 2048;
	itoken_maxsize_[eOBJECT::NUM::TARGET_ARMS_EFFECT] = 4096;	
	itoken_maxsize_[eOBJECT::NUM::MAP_TOP] = 32;
	itoken_maxsize_[eOBJECT::NUM::DESIGN_LAYER1] = 32;
	itoken_maxsize_[eOBJECT::NUM::DESIGN_LAYER2] = 32;
	itoken_maxsize_[eOBJECT::NUM::DESIGN_LAYER3] = 32;
	itoken_maxsize_[eOBJECT::NUM::TITLE_HELP] = 4;
	
	// �摜�f�[�^�z��̏�����
	vec_iload_.resize(IMG_FILE_MAXSIZE);
	// �z��̏�����
	for (int group = eOBJECT::NUM::enum_zero; group != eOBJECT::NUM::sizeof_enum; group++)
		vec_itoken_[group].resize(1);



	vec_itoken_[eOBJECT::NUM::TITLE_MAIN].resize(itoken_maxsize_[eOBJECT::NUM::TITLE_MAIN]);
	vec_itoken_[eOBJECT::NUM::MAP_BOTTOM].resize(itoken_maxsize_[eOBJECT::NUM::MAP_BOTTOM]);
	vec_itoken_[eOBJECT::NUM::STAGE_CONTINUE].resize(itoken_maxsize_[eOBJECT::NUM::STAGE_CONTINUE]);
	vec_itoken_[eOBJECT::NUM::STAGE_RESULT].resize(itoken_maxsize_[eOBJECT::NUM::STAGE_RESULT]);
	vec_itoken_[eOBJECT::NUM::TARGET_READY].resize(itoken_maxsize_[eOBJECT::NUM::TARGET_READY]);
	vec_itoken_[eOBJECT::NUM::TARGET_RUN_FLY].resize(itoken_maxsize_[eOBJECT::NUM::TARGET_RUN_FLY]);
	vec_itoken_[eOBJECT::NUM::TARGET_RUN_WALK].resize(itoken_maxsize_[eOBJECT::NUM::TARGET_RUN_WALK]);
	vec_itoken_[eOBJECT::NUM::TARGET_EFFECT].resize(itoken_maxsize_[eOBJECT::NUM::TARGET_EFFECT]);
	vec_itoken_[eOBJECT::NUM::USER].resize(itoken_maxsize_[eOBJECT::NUM::USER]);
	vec_itoken_[eOBJECT::NUM::USER_EFFECT].resize(itoken_maxsize_[eOBJECT::NUM::USER_EFFECT]);
	vec_itoken_[eOBJECT::NUM::USER_ARMS].resize(itoken_maxsize_[eOBJECT::NUM::USER_ARMS]);
	vec_itoken_[eOBJECT::NUM::USER_ARMS_EFFECT].resize(itoken_maxsize_[eOBJECT::NUM::USER_ARMS_EFFECT]);
	vec_itoken_[eOBJECT::NUM::TARGET_ARMS_SMALL].resize(itoken_maxsize_[eOBJECT::NUM::TARGET_ARMS_SMALL]);
	vec_itoken_[eOBJECT::NUM::TARGET_ARMS_LARGE].resize(itoken_maxsize_[eOBJECT::NUM::TARGET_ARMS_LARGE]);
	vec_itoken_[eOBJECT::NUM::TARGET_ARMS_EFFECT].resize(itoken_maxsize_[eOBJECT::NUM::TARGET_ARMS_EFFECT]);
	vec_itoken_[eOBJECT::NUM::MAP_TOP].resize(itoken_maxsize_[eOBJECT::NUM::MAP_TOP]);
	vec_itoken_[eOBJECT::NUM::DESIGN_LAYER1].resize(itoken_maxsize_[eOBJECT::NUM::DESIGN_LAYER1]);
	vec_itoken_[eOBJECT::NUM::DESIGN_LAYER2].resize(itoken_maxsize_[eOBJECT::NUM::DESIGN_LAYER2]);
	vec_itoken_[eOBJECT::NUM::DESIGN_LAYER3].resize(itoken_maxsize_[eOBJECT::NUM::DESIGN_LAYER3]);
	vec_itoken_[eOBJECT::NUM::TITLE_HELP].resize(itoken_maxsize_[eOBJECT::NUM::TITLE_HELP]);

	// �f�[�^�N���A
	Clear();
}


// ***************************
//  ��������摜�ǂݍ��݊֐�
// ***************************


/**
�摜�ǂݍ��݊֐�
@param filename �t�@�C����
@return �摜id (-1�̂Ƃ����s)
@note
�摜�ǂݍ��ݐ��� IMG_FILE_MAXSIZE �ɓ��B���Ă���Ƃ��͉������Ȃ��B
**/
int ImgManager::LoadImg(std::string filename)
{
	int xsize, ysize;

	if (vec_iload_.empty())
		return -1;
	if (id_load_ == IMG_FILE_MAXSIZE)
		return -1;

	// ���łɃ��[�h�ς݃t�@�C�����ǂ������ׂ�
	for (unsigned int id = 0; id < id_load_; id++) {
		if (vec_iload_[id].divmax_ == 1 && vec_iload_[id].filename_.compare(filename) == 0)
			return id;
	}

	vec_iload_[id_load_].xnum_ = 1;
	vec_iload_[id_load_].ynum_ = 1;
	vec_iload_[id_load_].filename_ = filename;
	vec_iload_[id_load_].file_[0] = LoadGraph(filename.c_str());
	GetGraphSize(vec_iload_[id_load_].file_[0], &xsize, &ysize);
	vec_iload_[id_load_].xsize_ = xsize;
	vec_iload_[id_load_].ysize_ = ysize;
	vec_iload_[id_load_].divmax_ = 1;

	id_load_++;
	return (id_load_ - 1);
}


/**
�����摜�ǂݍ��݊֐�
@param xnum x������������
@param ynum y������������
@param xsize x�����������T�C�Y
@param ysize y�����������T�C�Y
@param filename �t�@�C����
@return �摜id (-1�̂Ƃ����s)
@note
�摜�ǂݍ��ݐ��� IMG_FILE_MAXSIZE �ɓ��B���Ă���Ƃ��͉������Ȃ��B
**/
int ImgManager::LoadImg(int xnum, int ynum, int xsize, int ysize, std::string filename)
{
	if (vec_iload_.empty())
		return -1;
	if (id_load_ == IMG_FILE_MAXSIZE)
		return -1;

	// ���łɃ��[�h�ς݃t�@�C�����ǂ������ׂ�
	for (unsigned int id = 0; id < id_load_; id++) {
		if (vec_iload_[id].xnum_ == xnum && vec_iload_[id].ynum_ == ynum
			&& vec_iload_[id].xsize_ == xsize && vec_iload_[id].ysize_ == ysize
			&& vec_iload_[id].filename_.compare(filename) == 0)
			return id;
	}

	vec_iload_[id_load_].xnum_ = xnum;
	vec_iload_[id_load_].ynum_ = ynum;
	vec_iload_[id_load_].xsize_ = xsize;
	vec_iload_[id_load_].ysize_ = ysize;
	vec_iload_[id_load_].divmax_ = xnum * ynum;
	vec_iload_[id_load_].filename_ = filename;
	LoadDivGraph(filename.c_str(), xnum * ynum, xnum, ynum, xsize, ysize, vec_iload_[id_load_].file_);
	
	id_load_++;
	return (id_load_ - 1);
}


//////////////////////////////
// ��������摜�`��֐�
//////////////////////////////

/*!
�摜�`��֐�v1
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawGraph() �ɑΉ��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam1 *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE1;
	vec_itoken_[layer][ref].param1_ = *param;
}

/*!
�摜�`��֐�v2
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawTurnGraph() �ɑΉ��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam2 *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE2;
	vec_itoken_[layer][ref].param2_ = *param;
}

/*!
�摜�`��֐�v3
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawExtendGraph() �ɑΉ��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam3 *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE3;
	vec_itoken_[layer][ref].param3_ = *param;
}

/*!
�摜�`��֐�v4
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawRotaGraph() �ɑΉ��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam4 *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE4;
	vec_itoken_[layer][ref].param4_ = *param;
}

/*!
�摜�`��֐�v5
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawRotaGraph2() �ɑΉ��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam5 *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE5;
	vec_itoken_[layer][ref].param5_ = *param;
}

/*!
�摜�`��֐�v6
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawRotaGraph3() �ɑΉ��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam6 *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE6;
	vec_itoken_[layer][ref].param6_ = *param;
}

/*!
�摜�`��֐�v7
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawModiGraph() �ɑΉ��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam7 *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE7;
	vec_itoken_[layer][ref].param7_ = *param;
}

/*!
�摜�`��֐�v8
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawRectGraph() �ɑΉ��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam8 *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE8;
	vec_itoken_[layer][ref].param8_ = *param;
}

/*!
�摜�`��֐�v1b
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawGraph() �ɑΉ��B
�A���t�@�l���w�肷��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam1b *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE1B;
	vec_itoken_[layer][ref].param1b_ = *param;
}

/*!
�摜�`��֐�v2b
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawTurnGraph() �ɑΉ��B
�A���t�@�l���w�肷��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam2b *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE2B;
	vec_itoken_[layer][ref].param2b_ = *param;
}

/*!
�摜�`��֐�v3b
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawExtendGraph() �ɑΉ��B
�A���t�@�l���w�肷��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam3b *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE3B;
	vec_itoken_[layer][ref].param3b_ = *param;
}

/*!
�摜�`��֐�v4b
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawRotaGraph() �ɑΉ��B
�A���t�@�l���w�肷��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam4b *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE4B;
	vec_itoken_[layer][ref].param4b_ = *param;
}

/*!
�摜�`��֐�v5b
@param img_id �摜id
@param img_div �摜������
@param param �p�����[�^�w��
@return �Ȃ�
@note
DXLIB DrawRotaGraph2() �ɑΉ��B
�A���t�@�l���w�肷��B
�z��ɃO���t�B�b�N�f�[�^�̓o�^���邾���ŁA
���ۂɕ`�������̂�ImgUpdater::Run()�̖����B
*/
void ImgManager::Draw(unsigned int img_id, unsigned int img_div, ImgParam5b *param)
{
	int ref;	// Img�g�[�N���z��ւ̎Q�Ɣԍ�
	eOBJECT::GROUP layer = param->group_type_;		// eOBJECT::GROUP�����C���[�Ƃ��ė��p����

	if (vec_itoken_[layer].size() <= id_draw_[layer])
		return;

	// push_back(img_token)�͈����̍\���̂����I�[�o�[�w�b�h��������̂ŁA
	// �Q�Ɨp�̕ϐ���p�ӂ���[]�ŃA�N�Z�X����B
	ref = id_draw_[layer]++;
	vec_itoken_[layer][ref].id_ = img_id;
	vec_itoken_[layer][ref].div_ = img_div;
	vec_itoken_[layer][ref].draw_type_ = eIMG::DRAW::TYPE5B;
	vec_itoken_[layer][ref].param5b_ = *param;
}


// **********
//  ���̑�
// **********


eIMG::RET ImgManager::CheckFileTableRange(unsigned int id)
{
	try {
		vec_iload_.at(id);
	} catch(std::out_of_range) {
		return eIMG::RET::OUT_OF_RANGE;
	}

	return eIMG::RET::OK;
}


eIMG::RET ImgManager::CheckTokenTableRange(eOBJECT::GROUP group, long id)
{
	try {
		vec_itoken_[group].at(id);
	} catch(std::out_of_range) {
		return eIMG::RET::OUT_OF_RANGE;
	}

	return eIMG::RET::OK;
}

bool ImgManager::SwingX(unsigned int scale, unsigned int time)
{
		return false;
}

bool ImgManager::SwingY(unsigned int scale, unsigned int time)
{
	if (swing_time_y_ != 0)
		return false;

	swing_scale_y_ = scale;
	swing_time_y_ = time * 4;
	return true;
}
