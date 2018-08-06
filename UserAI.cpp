#include <tuple>
#include "UserAi.h"

#define USER_BARRIER_EXTEND_MAX_RATE	0.4
#define USER_MAIN_COLLISION_RANGE		5
#define __DEBUG__

using namespace std;
using namespace HNLIB;

UserAiBarrier::UserAiBarrier()
{
	count_frame_ = 0;
	valid_ = false;

	gpx_ = new GraphicPropertyX4;
	gpx_->extend_rate_ = USER_BARRIER_EXTEND_MAX_RATE;
	NyaGraphic::Load("img/user/barrier.png", &gpx_->file_);
}

UserAiBarrier::~UserAiBarrier()
{
	NyaGraphic::Delete(&gpx_->file_);

	delete gpx_;
	gpx_ = nullptr;
}

UserAiDevice::UserAiDevice()
{
	sound_index_ = 0;

	bit_gpx_ = new GraphicPropertyX4;
	bit_gpx_->extend_rate_ = 0.5;
	bit_gpx_->draw_angle_deg_ = -90;
	NyaGraphic::Load(9, 1,"img/user/bit.png", &bit_gpx_->file_);

	gadget_dpx_ = new DevicePropertyX1;
	gadget_dpx_->collision_range_ = 10;
	gadget_dpx_->move_speed_ = 20;

	device_gpx_ = new GraphicPropertyX4;
	device_gpx_->extend_rate_ = 0.1;
	NyaGraphic::Load("img/user/attack.png", &device_gpx_->file_);

	effect_epx_ = new EffectPropertyX2;
	effect_epx_->interval_time_frame_ = 2;

	effect_gpx_ = new GraphicPropertyX4;
	effect_gpx_->extend_rate_ = 1.0;
	NyaGraphic::Load(2, 2, "img/user/attack_effect.png", &effect_gpx_->file_);

	for (auto& e : spx_collection_)
	{
		e = new SoundPropertyX;
		NyaSound::Load("sound/user_attack.wav", &e->file_);
		NyaSound::ChangeVolume(&e->file_, 50);
	}
}

UserAiDevice::~UserAiDevice()
{
	NyaGraphic::Delete(&bit_gpx_->file_);
	NyaGraphic::Delete(&device_gpx_->file_);
	NyaGraphic::Delete(&effect_gpx_->file_);
	for (auto& e: spx_collection_)
		NyaSound::Delete(&e->file_);


	delete bit_gpx_;
	bit_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	for (auto& e : spx_collection_)
	{
		delete e;
		e = nullptr;
	}
}

UserAiDeviceEx::UserAiDeviceEx()
{
	count_ult_frame_ = 0;
	sound_index_ = 0;
	valid_ = false;

	bit_gpx_ = new GraphicPropertyX4;
	bit_gpx_->extend_rate_ = 0.5;
	NyaGraphic::Load(9, 1, "img/user/bit.png", &bit_gpx_->file_);

	gadget_dpx_ = new DevicePropertyX1;
	gadget_dpx_->collision_range_ = 2;
	gadget_dpx_->move_speed_ = 20;

	device_gpx_ = new GraphicPropertyX4;
	device_gpx_->extend_rate_ = 0.2;
	NyaGraphic::Load("img/user/attack_ex.png", &device_gpx_->file_);

	effect_epx_ = new EffectPropertyX2;
	effect_epx_->interval_time_frame_ = 2;

	effect_gpx_ = new GraphicPropertyX4;
	effect_gpx_->extend_rate_ = 0.5;
	NyaGraphic::Load(8, 2, "img/user/attack_ex_effect.png", &effect_gpx_->file_);

	for (auto& e : spx_collection_)
	{
		e = new SoundPropertyX;
		NyaSound::Load("sound/user_attack_ex.wav", &e->file_);
		NyaSound::ChangeVolume(&e->file_, 30);
	}
}

UserAiDeviceEx::~UserAiDeviceEx()
{
	NyaGraphic::Delete(&bit_gpx_->file_);
	NyaGraphic::Delete(&device_gpx_->file_);
	NyaGraphic::Delete(&effect_gpx_->file_);
	for (auto& e: spx_collection_)
		NyaSound::Delete(&e->file_);

	delete bit_gpx_;
	bit_gpx_ = nullptr;
	delete gadget_dpx_;
	gadget_dpx_ = nullptr;
	delete device_gpx_;
	device_gpx_ = nullptr;
	delete effect_epx_;
	effect_epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
	for (auto& e : spx_collection_)
	{
		delete e;
		e = nullptr;
	}
}

UserAiMain::UserAiMain()
{
	death_epx_ = new EffectPropertyX1;
	death_epx_->interval_time_frame_ = 3;

	death_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load(4, 2, "img/user/death.png", &death_gpx_->file_);

	death_spx_ = new SoundPropertyX;
	NyaSound::Load("sound/user_death.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 35);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load(8, 2, "img/user/main.png", &gpx_->file_);
	gpx_->extend_rate_ = 0.4;

	ult_epx_ = new EffectPropertyX2;
	ult_epx_->interval_time_frame_ = 3;

	ult_gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load(5, 2, "img/user/ult_effect.png", &ult_gpx_->file_);
	ult_gpx_->extend_rate_ = 1.5;

	for (auto& e : ult_spx_collection_)
	{
		e = new SoundPropertyX;
		NyaSound::Load("sound/user_ult.wav", &e->file_);
		NyaSound::ChangeVolume(&e->file_, 40);
	}

	phandle_ = NyaPosition::CreateHandle();
	phandle_->health_ = 1;
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = USER_MAIN_COLLISION_RANGE;
	phandle_->grid_x_ = SCREEN_CENTER_X;
	phandle_->grid_y_ = SCREEN_MAX_Y - 150;
	phandle_->name_ = "user";
}

UserAiMain::~UserAiMain()
{
	NyaGraphic::Delete(&death_gpx_->file_);
	NyaSound::Delete(&death_spx_->file_);
	NyaGraphic::Delete(&gpx_->file_);
	for (auto& e: ult_spx_collection_)
		NyaSound::Delete(&e->file_);

	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete death_spx_;
	death_spx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	delete ult_epx_;
	ult_epx_ = nullptr;
	delete ult_gpx_;
	ult_gpx_ = nullptr;
	for (auto& e : ult_spx_collection_)
	{
		delete e;
		e = nullptr;
	}

	NyaPosition::DeleteHandle(phandle_);
}

UserAiRange::UserAiRange()
{
	gpx_ = new GraphicPropertyX4;
	NyaGraphic::Load("img/user/range.png", &gpx_->file_);
}

UserAiRange::~UserAiRange()
{
	NyaGraphic::Delete(&gpx_->file_);
	delete gpx_;
	gpx_ = nullptr;
}

UserSkill::UserSkill()
{
	spx_q_ = new SoundPropertyX;
	NyaSound::Load("sound/user_skill_change.wav", &spx_q_->file_);
	NyaSound::ChangeVolume(&spx_q_->file_, 30);
	spx_w_ = new SoundPropertyX;
	NyaSound::Load("sound/user_skill_change.wav", &spx_w_->file_);
	NyaSound::ChangeVolume(&spx_w_->file_, 30);
	spx_e_ = new SoundPropertyX;
	NyaSound::Load("sound/user_skill_change.wav", &spx_e_->file_);
	NyaSound::ChangeVolume(&spx_e_->file_, 30);
	spx_r_ = new SoundPropertyX;
	NyaSound::Load("sound/user_skill_change.wav", &spx_r_->file_);
	NyaSound::ChangeVolume(&spx_r_->file_, 30);

	gpx_q_ = new GraphicPropertyX4;
	gpx_q_->extend_rate_ = 0.2;
	NyaGraphic::Load("img/user/skill_q.png", &gpx_q_->file_);
	gpx_w_ = new GraphicPropertyX4;
	gpx_w_->extend_rate_ = 0.2;
	NyaGraphic::Load("img/user/skill_w.png", &gpx_w_->file_);
	gpx_e_ = new GraphicPropertyX4;
	gpx_e_->extend_rate_ = 0.2;
	NyaGraphic::Load("img/user/skill_e.png", &gpx_e_->file_);
	gpx_r_ = new GraphicPropertyX4;
	gpx_r_->extend_rate_ = 0.2;
	NyaGraphic::Load("img/user/skill_r.png", &gpx_r_->file_);
}

UserSkill::~UserSkill()
{
	NyaGraphic::Delete(&gpx_q_->file_);
	NyaGraphic::Delete(&gpx_w_->file_);
	NyaGraphic::Delete(&gpx_e_->file_);
	NyaGraphic::Delete(&gpx_r_->file_);

	NyaSound::Delete(&spx_q_->file_);
	NyaSound::Delete(&spx_w_->file_);
	NyaSound::Delete(&spx_e_->file_);
	NyaSound::Delete(&spx_r_->file_);

	delete gpx_q_;
	gpx_q_ = nullptr;
	delete gpx_w_;
	gpx_w_ = nullptr;
	delete gpx_e_;
	gpx_e_ = nullptr;
	delete gpx_r_;
	gpx_r_ = nullptr;

	delete spx_q_;
	spx_q_ = nullptr;
	delete spx_w_;
	spx_w_ = nullptr;
	delete spx_e_;
	spx_e_ = nullptr;
	delete spx_r_;
	spx_r_ = nullptr;
}

UserAi::UserAi(void)
{
	count_frame_ = 0;

	// interface スキル 設定
	NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::Q)] =  400000;
	NyaInterface::GetHandleSkill()->lv2_exp_[static_cast<int>(eSKILL::Q)] =  800000;
	NyaInterface::GetHandleSkill()->lv3_exp_[static_cast<int>(eSKILL::Q)] = 1200000;
	NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::Q)] = 1600000;
	NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::W)] =  400000;
	NyaInterface::GetHandleSkill()->lv2_exp_[static_cast<int>(eSKILL::W)] =  800000;
	NyaInterface::GetHandleSkill()->lv3_exp_[static_cast<int>(eSKILL::W)] = 1200000;
	NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::W)] = 1600000;
	NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::E)] =  500000;
	NyaInterface::GetHandleSkill()->lv2_exp_[static_cast<int>(eSKILL::E)] = 1000000;
	NyaInterface::GetHandleSkill()->lv3_exp_[static_cast<int>(eSKILL::E)] = 1500000;
	NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::E)] = 2000000;
	NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::R)] =    5000;
	NyaInterface::GetHandleSkill()->lv2_exp_[static_cast<int>(eSKILL::R)] =   10000;
	NyaInterface::GetHandleSkill()->lv3_exp_[static_cast<int>(eSKILL::R)] =   15000;
	NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::R)] =   20000;

	// interface スキル 初期化
	NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::Q)] = NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::Q)];
	NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::W)] = NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::W)];
	NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::E)] = NyaInterface::GetHandleSkill()->lv3_exp_[static_cast<int>(eSKILL::E)];
	NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::R)] = NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::R)];

	// interface スキル 初期化
	//NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::Q)] = 0;
	//NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::W)] = 0;
	//NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::E)] = 0;
	//NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::R)] = 0;

	// interface 残機設定
	NyaInterface::GetHandleLife()->value_ = 2;
//	NyaInterface::GetHandleLife()->value_ = 3;

	// 衝突判定設定
	NyaPosition::CollisionPair(eOBJECT::USER_ATTACK1, eOBJECT::TARGET1);
	NyaPosition::CollisionPair(eOBJECT::USER1, eOBJECT::TARGET_ATTACK1);
	NyaPosition::CollisionPair(eOBJECT::USER1, eOBJECT::TARGET1);
}

UserAi::~UserAi()
{

}

//**********************
// UserAi メンバ関数
//**********************
void UserAi::Act(void)
{
	// 攻撃処理
	Act_Ult();
	Act_Attack();
	Act_AttackEx();

	// スキル変更
	Act_ChangeSkill();
	// 衝突判定
	Act_Collide();
	// 移動処理
	Act_Move();

	// ライフがゼロならコンテニュー画面を表示する
	if (NyaInterface::GetHandleLife()->value_ == 0)
		NyaInterface::GetHandleContinue()->valid_ = true;

	count_frame_++;
}

/**
@brief 攻撃をする(通常状態のとき)
**/
void UserAi::Act_Attack(void)
{
	const int device_collision_accuracy = 2;
	int exp_q = NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::Q)];
	int lv1_exp_q = NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::Q)];
	int lv2_exp_q = NyaInterface::GetHandleSkill()->lv2_exp_[static_cast<int>(eSKILL::Q)];
	int lv3_exp_q = NyaInterface::GetHandleSkill()->lv3_exp_[static_cast<int>(eSKILL::Q)];
	int lv4_exp_q = NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::Q)];
	int exp_w = NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::W)];
	int lv1_exp_w = NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::W)];
	int lv2_exp_w = NyaInterface::GetHandleSkill()->lv2_exp_[static_cast<int>(eSKILL::W)];
	int lv3_exp_w = NyaInterface::GetHandleSkill()->lv3_exp_[static_cast<int>(eSKILL::W)];
	int lv4_exp_w = NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::W)];

	// ウルト実行中の時は何もしない
	if (device_ex_.valid_)
		return;

	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && count_frame_ % 6 == 0)
	{	// 発射音の再生
		NyaSound::Play(device_.spx_collection_[device_.sound_index_]);
		device_.sound_index_ = (++device_.sound_index_) % device_.spx_collection_.size();
	}


	//***********************
	// 低速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == true && count_frame_ % 6 == 0)
	{	// 3wave
		if(exp_q < lv1_exp_q)
			device_.gadget_dpx_->collision_power_ = 2;
		else if(lv1_exp_q <= exp_q && exp_q < lv2_exp_q)
			device_.gadget_dpx_->collision_power_ = 6;
		else if(lv2_exp_q <= exp_q && exp_q < lv3_exp_q)
			device_.gadget_dpx_->collision_power_ = 13;
		else if(lv3_exp_q <= exp_q && exp_q < lv4_exp_q)
			device_.gadget_dpx_->collision_power_ = 23;
		else
			device_.gadget_dpx_->collision_power_ = 36;

		device_.gadget_dpx_->move_angle_deg_ = -90;
		device_.gadget_dpx_->draw_angle_deg_ = 90;
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		if (lv1_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_dpx_->draw_angle_deg_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -20;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +20;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv2_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_dpx_->draw_angle_deg_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv3_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_dpx_->draw_angle_deg_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv4_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_.gadget_dpx_->move_angle_deg_ = -90;
			device_.gadget_dpx_->draw_angle_deg_ = 90;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -50;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +50;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}

	}
	//***********************
	// 高速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == false && count_frame_ % 6 == 0)
	{	// 3wave
		if (exp_w < lv1_exp_w)
			device_.gadget_dpx_->collision_power_ = 1;
		else if(lv1_exp_w <= exp_w && exp_w < lv2_exp_w)
			device_.gadget_dpx_->collision_power_ = 2;
		else if(lv2_exp_w <= exp_w && exp_w < lv3_exp_w)
			device_.gadget_dpx_->collision_power_ = 3;
		else if(lv3_exp_w <= exp_w && exp_w < lv4_exp_w)
			device_.gadget_dpx_->collision_power_ = 4;
		else
			device_.gadget_dpx_->collision_power_ = 5;

		device_.gadget_dpx_->move_angle_deg_ = -90;
		device_.gadget_dpx_->draw_angle_deg_ = 90;
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +10;
		device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);

		if (lv1_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +30;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 5;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +40;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv2_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -70;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -60;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +60;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 10;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +70;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv3_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -100;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -90;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +90;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 15;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +100;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv4_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -130;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			device_.gadget_dpx_->draw_angle_deg_ = 90 - 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -120;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +120;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			device_.gadget_dpx_->draw_angle_deg_ = 90 + 20;
			device_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +130;
			device_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			NyaDevice::Attack1424(device_.gadget_dpx_, device_.device_gpx_, device_.effect_epx_, device_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
	}
}

/**
@brief 攻撃をする(ult状態のとき)
**/
void UserAi::Act_AttackEx(void)
{
	const int device_collision_accuracy = 2;
	int exp_q = NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::Q)];
	int lv1_exp_q = NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::Q)];
	int lv2_exp_q = NyaInterface::GetHandleSkill()->lv2_exp_[static_cast<int>(eSKILL::Q)];
	int lv3_exp_q = NyaInterface::GetHandleSkill()->lv3_exp_[static_cast<int>(eSKILL::Q)];
	int lv4_exp_q = NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::Q)];
	int exp_w = NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::W)];
	int lv1_exp_w = NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::W)];
	int lv2_exp_w = NyaInterface::GetHandleSkill()->lv2_exp_[static_cast<int>(eSKILL::W)];
	int lv3_exp_w = NyaInterface::GetHandleSkill()->lv3_exp_[static_cast<int>(eSKILL::W)];
	int lv4_exp_w = NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::W)];

	// ウルト実行中でない時は何もしない
	if (!device_ex_.valid_)
		return;

	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && count_frame_ % 6 == 0)
	{	// 発射音の再生
		NyaSound::Play(device_ex_.spx_collection_[device_ex_.sound_index_]);
		device_ex_.sound_index_ = (++device_ex_.sound_index_) % device_ex_.spx_collection_.size();
	}


	//***********************
	// 低速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == true && count_frame_ % 6 == 0)
	{	// 3wave
		if(exp_q < lv1_exp_q)
			device_ex_.gadget_dpx_->collision_power_ = 3;
		else if(lv1_exp_q <= exp_q && exp_q < lv2_exp_q)
			device_ex_.gadget_dpx_->collision_power_ = 9;
		else if(lv2_exp_q <= exp_q && exp_q < lv3_exp_q)
			device_ex_.gadget_dpx_->collision_power_ = 17;
		else if(lv3_exp_q <= exp_q && exp_q < lv4_exp_q)
			device_ex_.gadget_dpx_->collision_power_ = 29;
		else
			device_ex_.gadget_dpx_->collision_power_ = 43;

		device_ex_.gadget_dpx_->move_angle_deg_ = -90;
		device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -10;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +10;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		if (lv1_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_ex_.gadget_dpx_->move_angle_deg_ = -90;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -25;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +25;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv2_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_ex_.gadget_dpx_->move_angle_deg_ = -90;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -40;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +40;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv3_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_ex_.gadget_dpx_->move_angle_deg_ = -90;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -55;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +55;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv4_exp_w <= exp_w)
		{	// 1wave + 1wave
			device_ex_.gadget_dpx_->move_angle_deg_ = -90;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -70;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +70;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}

	}
	//***********************
	// 高速移動時の攻撃
	//***********************
	if (NyaInput::GetKeyStateNow(eINPUT::Q) == true && NyaInput::GetKeyStateNow(eINPUT::W) == false && count_frame_ % 6 == 0)
	{	// 3wave
		if (exp_w < lv1_exp_w)
			device_ex_.gadget_dpx_->collision_power_ = 1 + 1;
		else if(lv1_exp_w <= exp_w && exp_w < lv2_exp_w)
			device_ex_.gadget_dpx_->collision_power_ = 2 + 1;
		else if(lv2_exp_w <= exp_w && exp_w < lv3_exp_w)
			device_ex_.gadget_dpx_->collision_power_ = 3 + 1;
		else if(lv3_exp_w <= exp_w && exp_w < lv4_exp_w)
			device_ex_.gadget_dpx_->collision_power_ = 4 + 1;
		else
			device_ex_.gadget_dpx_->collision_power_ = 5 + 1;

		device_ex_.gadget_dpx_->move_angle_deg_ = -90;
		device_ex_.gadget_dpx_->draw_angle_deg_ = 90;
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -10;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +10;
		device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_;
		device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
		NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		if (lv1_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 5;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -40;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 5;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 5;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -30;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 5;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +30;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 5;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 5;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +40;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv2_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 10;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -70;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 10;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 10;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -60;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 10;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +60;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 10;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 10;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +70;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv3_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 15;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -100;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 15;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 15;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -90;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 15;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +90;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 15;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 15;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +100;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
		if (lv4_exp_w <= exp_w)
		{	// 2wave + 2wave
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 20;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -130;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 - 20;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 - 20;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ -120;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 20;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +120;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
			device_ex_.gadget_dpx_->move_angle_deg_ = -90 + 20;
			device_ex_.gadget_dpx_->draw_angle_deg_ = 90 + 20;
			device_ex_.gadget_dpx_->create_x_ = main_.phandle_->grid_x_ +130;
			device_ex_.gadget_dpx_->create_y_ = main_.phandle_->grid_y_ +20;
			device_ex_.effect_gpx_->draw_angle_deg_ = NyaInput::GetRand(0.0, 360.0);
			NyaDevice::Attack1424(device_ex_.gadget_dpx_, device_ex_.device_gpx_, device_ex_.effect_epx_, device_ex_.effect_gpx_, eOBJECT::USER_ATTACK1, eOBJECT::USER_ATTACK_EFFECT1, device_collision_accuracy);
		}
	}

	//************************************************
	// ウルト実行フレーム数をカウントする
	// ウルト実行時間を超えたらウルトを終了させる
	//************************************************
	device_ex_.count_ult_frame_++;
	if (FPS_MAX * 3 < device_ex_.count_ult_frame_)
	{
		device_ex_.count_ult_frame_ = 0;
		device_ex_.valid_ = false;
	}
}

void UserAi::Act_ChangeSkill(void)
{
	if (NyaInput::IsPressKey(eINPUT::SPACE))
	{	// スキル切り替え時のSE再生
		if (NyaInterface::GetHandleSkill()->select_ == eSKILL::Q)
			NyaSound::Play(skill_.spx_q_);
		else if (NyaInterface::GetHandleSkill()->select_ == eSKILL::W)
			NyaSound::Play(skill_.spx_w_);
		else if (NyaInterface::GetHandleSkill()->select_ == eSKILL::E)
			NyaSound::Play(skill_.spx_e_);
		else
			NyaSound::Play(skill_.spx_r_);
	}
}

void UserAi::Act_Collide(void)
{
	NyaPosition::Collide(main_.phandle_, eOBJECT::USER1);
	if (main_.phandle_->collision_hit_damage_ != 0 && !barrier_.valid_)
	{	// オブジェクトTARGETまたはTARGET_ATTACKと衝突した
		size_t size = 0;
		size += NyaDevice::Size(eOBJECT::TARGET_ATTACK1);
		size += NyaDevice::Size(eOBJECT::TARGET_ATTACK2);
		size += NyaDevice::Size(eOBJECT::TARGET_ATTACK3);
		size += NyaDevice::Size(eOBJECT::TARGET_ATTACK4);
		size += NyaDevice::Size(eOBJECT::TARGET_ATTACK5);
		NyaInterface::GetHandleSkill()->AddExp((unsigned int)size);
		NyaInterface::GetHandleLife()->value_--;
		NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::E)] = NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::E)];
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
		NyaSound::Play(main_.death_spx_);
	}

	// バリア時の衝突判定変更
	if (barrier_.valid_)
		main_.phandle_->collision_range_ = USER_MAIN_COLLISION_RANGE + 15;
	else
		main_.phandle_->collision_range_ = USER_MAIN_COLLISION_RANGE;
}

/**
@brief userを移動する
**/
void UserAi::Act_Move(void)
{
	int speed;
	int exp_r = NyaInterface::GetHandleSkill()->exp_[static_cast<int>(eSKILL::R)];
	int lv1_exp_r = NyaInterface::GetHandleSkill()->lv1_exp_[static_cast<int>(eSKILL::R)];
	int lv2_exp_r = NyaInterface::GetHandleSkill()->lv2_exp_[static_cast<int>(eSKILL::R)];
	int lv3_exp_r = NyaInterface::GetHandleSkill()->lv3_exp_[static_cast<int>(eSKILL::R)];
	int lv4_exp_r = NyaInterface::GetHandleSkill()->lv4_exp_[static_cast<int>(eSKILL::R)];

	//*********************************
	// 入力に応じて移動量を決める
	//*********************************
	if (NyaInput::GetKeyStateNow(eINPUT::W))
	{
		if     (exp_r < lv1_exp_r)
			speed = 2;
		else if(lv1_exp_r <= exp_r && exp_r < lv2_exp_r)
			speed = 3;
		else if(lv2_exp_r <= exp_r && exp_r < lv3_exp_r)
			speed = 4;
		else if(lv3_exp_r <= exp_r && exp_r < lv4_exp_r)
			speed = 5;
		else
			speed = 6;
	}
	else
	{
		if (exp_r < lv1_exp_r)
			speed = 9;
		else if(lv1_exp_r <= exp_r && exp_r < lv2_exp_r)
			speed = 10;
		else if(lv2_exp_r <= exp_r && exp_r < lv3_exp_r)
			speed = 11;
		else if(lv3_exp_r <= exp_r && exp_r < lv4_exp_r)
			speed = 12;
		else
			speed = 13;

	}

	//*********************************
	// 入力に応じて座標を更新する
	//*********************************
	if (NyaInput::GetKeyStateNow(eINPUT::RIGHT))
	{
		if (NyaInput::GetKeyStateNow(eINPUT::UP))
		{
			main_.phandle_->grid_y_ -= speed;
			main_.phandle_->grid_x_ += speed;
		}
		else if (NyaInput::GetKeyStateNow(eINPUT::DOWN))
		{
			main_.phandle_->grid_y_ += speed;
			main_.phandle_->grid_x_ += speed;
		}
		else
			main_.phandle_->grid_x_ += speed;
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::LEFT))
	{
		if (NyaInput::GetKeyStateNow(eINPUT::UP))
		{
			main_.phandle_->grid_y_ -= speed;
			main_.phandle_->grid_x_ -= speed;
		}
		else if (NyaInput::GetKeyStateNow(eINPUT::DOWN))
		{
			main_.phandle_->grid_y_ += speed;
			main_.phandle_->grid_x_ -= speed;
		}
		else
			main_.phandle_->grid_x_ -= speed;	
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::UP))
	{
		if (NyaInput::GetKeyStateNow(eINPUT::LEFT))
		{
			main_.phandle_->grid_y_ -= speed;
			main_.phandle_->grid_x_ -= speed;
		}
		else if (NyaInput::GetKeyStateNow(eINPUT::RIGHT))
		{
			main_.phandle_->grid_y_ -= speed;
			main_.phandle_->grid_x_ += speed;
		}
		else
			main_.phandle_->grid_y_ -= speed;	
	}
	else if (NyaInput::GetKeyStateNow(eINPUT::DOWN))
	{
		if (NyaInput::GetKeyStateNow(eINPUT::LEFT))
		{
			main_.phandle_->grid_y_ += speed;
			main_.phandle_->grid_x_ -= speed;
		}
		else if (NyaInput::GetKeyStateNow(eINPUT::RIGHT))
		{
			main_.phandle_->grid_y_ += speed;
			main_.phandle_->grid_x_ += speed;
		}
		else
			main_.phandle_->grid_y_ += speed;
	}

	//******************
	// 境界チェック
	//******************
	if (main_.phandle_->grid_x_ < SCREEN_MIN_X + 20)
		main_.phandle_->grid_x_ = SCREEN_MIN_X + 20;
	if (main_.phandle_->grid_y_ < SCREEN_MIN_Y + 40)
		main_.phandle_->grid_y_ = SCREEN_MIN_Y + 40;
	if (SCREEN_MAX_X - 20 < main_.phandle_->grid_x_)
		main_.phandle_->grid_x_ = SCREEN_MAX_X - 20;
	if (SCREEN_MAX_Y - 50 < main_.phandle_->grid_y_)
		main_.phandle_->grid_y_ = SCREEN_MAX_Y - 50;
}

/**
 @brief ウルト発動した瞬間の処理をする
**/
void UserAi::Act_Ult(void)
{
	InterfaceHandleSkill* ihandle_mission_skill = NyaInterface::GetHandleSkill();
	int exp_e = ihandle_mission_skill->exp_[static_cast<int>(eSKILL::E)];
	int lv1_exp_e = ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::E)];
	int lv2_exp_e = ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::E)];
	int lv3_exp_e = ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::E)];
	int lv4_exp_e = ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::E)];

	if (NyaInput::IsPressKey(eINPUT::E) && lv1_exp_e <= exp_e)
	{
		size_t size = 0;
		// 弾数だけスキルの経験値追加
		size += NyaDevice::Size(eOBJECT::TARGET_ATTACK1);
		size += NyaDevice::Size(eOBJECT::TARGET_ATTACK2);
		size += NyaDevice::Size(eOBJECT::TARGET_ATTACK3);
		size += NyaDevice::Size(eOBJECT::TARGET_ATTACK4);
		size += NyaDevice::Size(eOBJECT::TARGET_ATTACK5);
		NyaInterface::GetHandleSkill()->AddExp((unsigned int)size);
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK2);
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK3);
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK4);
		NyaDevice::Clear(eOBJECT::TARGET_ATTACK5);
		// ウルト有効化、ウルトの経験値を減らすことでウルトスキルをlv1下げる
		device_ex_.valid_ = true;
		if (lv1_exp_e <= exp_e && exp_e < lv2_exp_e)
		{
			ihandle_mission_skill->exp_[static_cast<int>(eSKILL::E)] -= lv1_exp_e;
			NyaSound::Play(main_.ult_spx_collection_[0]);
		}
		else if (lv2_exp_e <= exp_e && exp_e < lv3_exp_e)
		{
			ihandle_mission_skill->exp_[static_cast<int>(eSKILL::E)] -= (lv2_exp_e - lv1_exp_e);
			NyaSound::Play(main_.ult_spx_collection_[1]);
		}
		else if (lv3_exp_e <= exp_e && exp_e < lv4_exp_e)
		{
			ihandle_mission_skill->exp_[static_cast<int>(eSKILL::E)] -= (lv3_exp_e - lv2_exp_e);
			NyaSound::Play(main_.ult_spx_collection_[2]);
		}
		else if (lv4_exp_e <= exp_e)
		{
			ihandle_mission_skill->exp_[static_cast<int>(eSKILL::E)] -= (lv4_exp_e - lv3_exp_e);
			NyaSound::Play(main_.ult_spx_collection_[3]);
		}
		main_.ult_epx_->grid_x_ = &main_.phandle_->grid_x_;
		main_.ult_epx_->grid_y_ = &main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.ult_epx_, main_.ult_gpx_, eOBJECT::USER_EFFECT1);
	}
}


/**
 @brief userを描画する
**/
void UserAi::Draw(void)
{
	InterfaceHandleSkill* ihandle_mission_skill = NyaInterface::GetHandleSkill();
	int exp_w = ihandle_mission_skill->exp_[static_cast<int>(eSKILL::W)];
	int lv1_exp_w = ihandle_mission_skill->lv1_exp_[static_cast<int>(eSKILL::W)];
	int lv2_exp_w = ihandle_mission_skill->lv2_exp_[static_cast<int>(eSKILL::W)];
	int lv3_exp_w = ihandle_mission_skill->lv3_exp_[static_cast<int>(eSKILL::W)];
	int lv4_exp_w = ihandle_mission_skill->lv4_exp_[static_cast<int>(eSKILL::W)];

	//*************
	// skill 描画
	//*************
	if (!barrier_.valid_)
	{
		if (NyaInterface::GetHandleSkill()->select_ == eSKILL::Q)
		{
			skill_.gpx_q_->draw_grid_cx_ = (int)main_.phandle_->grid_x_;
			skill_.gpx_q_->draw_grid_cy_ = (int)main_.phandle_->grid_y_ - 8;
			skill_.gpx_q_->draw_angle_deg_ += 2;
			NyaGraphic::Draw(skill_.gpx_q_, eOBJECT::USER1);
		}
		else if (NyaInterface::GetHandleSkill()->select_ == eSKILL::W)
		{
			skill_.gpx_w_->draw_grid_cx_ = (int)main_.phandle_->grid_x_;
			skill_.gpx_w_->draw_grid_cy_ = (int)main_.phandle_->grid_y_ - 8;
			skill_.gpx_w_->draw_angle_deg_ += 2;
			NyaGraphic::Draw(skill_.gpx_w_, eOBJECT::USER1);
		}
		else if (NyaInterface::GetHandleSkill()->select_ == eSKILL::E)
		{
			skill_.gpx_e_->draw_grid_cx_ = (int)main_.phandle_->grid_x_;
			skill_.gpx_e_->draw_grid_cy_ = (int)main_.phandle_->grid_y_ - 8;
			skill_.gpx_e_->draw_angle_deg_ += 2;
			NyaGraphic::Draw(skill_.gpx_e_, eOBJECT::USER1);
		}
		else
		{
			skill_.gpx_r_->draw_grid_cx_ = (int)main_.phandle_->grid_x_;
			skill_.gpx_r_->draw_grid_cy_ = (int)main_.phandle_->grid_y_ - 8;
			skill_.gpx_r_->draw_angle_deg_ += 2;
			NyaGraphic::Draw(skill_.gpx_r_, eOBJECT::USER1);
		}
	}

	//*************
	// main 描画
	//*************
	main_.gpx_->draw_grid_cx_ = (int)main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = (int)main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 2 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % main_.gpx_->file_.div_total_;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::USER1);

	//*************
	// bit 描画
	//*************
	if (!NyaInput::GetKeyStateNow(eINPUT::W))
	{
		if (NyaInput::GetFrameCount() % 2 == 0)
			device_.bit_gpx_->file_div_ = ++device_.bit_gpx_->file_div_ % device_.bit_gpx_->file_.div_total_;
		if (lv1_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 35;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 35;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}
		if (lv2_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 65;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 65;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}
		if (lv3_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 95;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 95;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}
		if (lv4_exp_w <= exp_w)
		{
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ - 125;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
			device_.bit_gpx_->draw_grid_cx_ = main_.phandle_->grid_x_ + 125;
			device_.bit_gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ + 20;
			NyaGraphic::Draw(device_.bit_gpx_, eOBJECT::USER1);
		}	
	}

	//******************
	// 衝突エフェクト
	//******************
	if (main_.phandle_->collision_hit_damage_ != 0 && !barrier_.valid_)
	{
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::USER_EFFECT1);
		// barrier 有効化
		barrier_.count_frame_ = 0;
		barrier_.valid_ = true;
		barrier_.gpx_->extend_rate_ = USER_BARRIER_EXTEND_MAX_RATE;
	}

	//***********************
	// barrier エフェクト
	//***********************
	if (barrier_.valid_)
	{
		barrier_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
		barrier_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_ - 10;
		barrier_.gpx_->draw_angle_deg_ += 2;
		barrier_.gpx_->extend_rate_ -= 0.002;
		NyaGraphic::Draw(barrier_.gpx_, eOBJECT::USER_EFFECT1);
		barrier_.count_frame_++;
		if (barrier_.count_frame_ == FPS_MAX * 3)
			barrier_.valid_ = false;
	}

#ifdef __DEBUG__
	// 衝突判定範囲
	range_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	range_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;	
	NyaGraphic::Draw(range_.gpx_, eOBJECT::USER1);
#endif

}


