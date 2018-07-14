#include "HNLIB.h"
#include "Target3Bordetella.h"
#include "TeemoEnum.h"
#include "TeemoFactory.h"

using namespace HNLIB;

Target3BordetellaCubeDevice::Target3BordetellaCubeDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_ORANGE2;
	dpx_->move_speed_ = 3;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_orange2.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

Target3BordetellaCubeDevice::~Target3BordetellaCubeDevice()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

Target3BordetellaCube::Target3BordetellaCube()
{
	lock_.LoadGraphic("img/target/lock_cube.png");

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath1(death_epx_, death_gpx_);

	gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetCube(gpx_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_range_ = 20;
}

Target3BordetellaCube::~Target3BordetellaCube()
{
	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;
	NyaPosition::DeleteHandle(phandle_);
}

Target3BordetellaDevice::Target3BordetellaDevice()
{
	dpx_ = new DevicePropertyX1;
	dpx_->collision_range_ = TARGET_ATTACK_RANGE_BLUE3;
	dpx_->move_speed_ = 4;
	gadget_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/attack_blue3.png", &gadget_gpx_->file_);
	epx_ = new EffectPropertyX1;
	epx_->interval_time_frame_ = TARGET_DEVICE_EFFECT_INTERVAL;
	effect_gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile("img/target/point.png", &effect_gpx_->file_);
}

Target3BordetellaDevice::~Target3BordetellaDevice()
{
	NyaGraphic::DeleteGraphicFile(&gadget_gpx_->file_);
	NyaGraphic::DeleteGraphicFile(&effect_gpx_->file_);
	delete dpx_;
	dpx_ = nullptr;
	delete gadget_gpx_;
	gadget_gpx_ = nullptr;
	delete epx_;
	epx_ = nullptr;
	delete effect_gpx_;
	effect_gpx_ = nullptr;
}

Target3BordetellaMain::Target3BordetellaMain()
{
	health_max_ = 35000;
	lock_.LoadGraphic("img/target/lock_bordetella.png");

	death_epx_ = new EffectPropertyX1;
	death_gpx_ = new GraphicPropertyX4;
	TeemoFactory::TargetDeath2(death_epx_, death_gpx_);

	death_spx_ = new SoundPropertyX;
	NyaSound::LoadFile("sound/target_death2.wav", &death_spx_->file_);
	NyaSound::ChangeVolume(&death_spx_->file_, 50);

	gpx_ = new GraphicPropertyX4;
	NyaGraphic::LoadGraphicFile(4, 1, "img/target/target_bordetella.png", &gpx_->file_);

	phandle_ = NyaPosition::CreateHandle();
	phandle_->collision_power_ = 1;
	phandle_->collision_range_ = 10;
	phandle_->health_ = health_max_;
}

Target3BordetellaMain::~Target3BordetellaMain()
{
	NyaGraphic::DeleteGraphicFile(&death_gpx_->file_);
	NyaSound::DeleteSoundFile(&death_spx_->file_);
	NyaGraphic::DeleteGraphicFile(&gpx_->file_);

	delete death_epx_;
	death_epx_ = nullptr;
	delete death_gpx_;
	death_gpx_ = nullptr;
	delete death_spx_;
	death_spx_ = nullptr;
	delete gpx_;
	gpx_ = nullptr;

	NyaPosition::DeleteHandle(phandle_);
}

Target3Bordetella::Target3Bordetella(int x, int y)
{
	main_.phandle_->grid_x_ = x;
	main_.phandle_->grid_y_ = y;
	mode_ = 1;
	cube_collection_[0].phandle_->grid_x_ = x - 100;
	cube_collection_[0].phandle_->grid_y_ = y - 60;
	cube_collection_[1].phandle_->grid_x_ = x + 100;
	cube_collection_[1].phandle_->grid_y_ = y - 60;
}


Target3Bordetella::~Target3Bordetella()
{

}

void Target3Bordetella::Act(void)
{
	switch(mode_)
	{
	case 1:
		Act1();
		if (NyaPosition::InScreen(main_.phandle_))
		{
			count_frame_ = 0;
			mode_ = 2;
		}
		break;
	case 2:
		Act2();
		break;
	};

	main_.phandle_->grid_y_ += MAP_SCROLL_PER_FRAME;
	count_frame_++;
}

void Target3Bordetella::Draw(void)
{
	switch(mode_)
	{
	case 1:
		Draw1();
		break;
	case 2:
		Draw2();
		if (main_.phandle_->health_ < 0)
		{
			mode_ = 3;
			NyaInterface::GetHandleHealth()->valid_ = false;
			NyaDevice::Clear(eOBJECT::TARGET_ATTACK1);
			NyaGraphic::Swing();
		}
		break;
	};
}

void Target3Bordetella::Act1(void)
{
	// cube 配置
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;
}

void Target3Bordetella::Act2(void)
{
	// cube 配置
	cube_collection_[0].phandle_->grid_x_ = main_.phandle_->grid_x_ - 100;
	cube_collection_[0].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;
	cube_collection_[1].phandle_->grid_x_ = main_.phandle_->grid_x_ + 100;
	cube_collection_[1].phandle_->grid_y_ = main_.phandle_->grid_y_ - 60;

	// 衝突判定　衝突ダメージだけ経験値を追加
	NyaPosition::Collide(main_.phandle_, eOBJECT::TARGET1);
	NyaInterface::GetHandleSkill()->AddExp(main_.phandle_->collision_hit_damage_);
	main_.phandle_->health_ -= main_.phandle_->collision_hit_damage_;
	for (auto& e : cube_collection_)
	{
		NyaPosition::Collide(e.phandle_, eOBJECT::TARGET1);
		NyaInterface::GetHandleSkill()->AddExp(e.phandle_->collision_hit_damage_);
		main_.phandle_->health_ -= e.phandle_->collision_hit_damage_;
	}

	if (count_frame_ < FPS_MAX * 2)
		return;

	if (count_frame_ < FPS_MAX * 6 || FPS_MAX * 9 < count_frame_)
	{
		if (count_frame_ % 120 == 0 || count_frame_ % 120 == 20 || count_frame_ % 120 == 40)
		{
			main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
			main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
			main_.device_.dpx_->move_angle_deg_ = 0;
			for (int way = 0; way < 360 / 6; way++)
			{
				main_.device_.dpx_->move_angle_deg_ += 6;
				NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
		if (count_frame_ % 120 == 60 || count_frame_ % 120 == 80 || count_frame_ % 120 == 100)
		{
			main_.device_.dpx_->create_x_ = main_.phandle_->grid_x_;
			main_.device_.dpx_->create_y_ = main_.phandle_->grid_y_;
			main_.device_.dpx_->move_angle_deg_ = 3;
			for (int way = 0; way < 360 / 6; way++)
			{
				main_.device_.dpx_->move_angle_deg_ += 6;
				NyaDevice::Attack1414(main_.device_.dpx_, main_.device_.gadget_gpx_, main_.device_.epx_, main_.device_.effect_gpx_, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			}
		}
	}

	if (count_frame_ == FPS_MAX * 11)
	{
		DevicePropertyX1* cube_dpx = cube_collection_[0].device_.dpx_;
		GraphicPropertyX4* cube_gadget_gpx = cube_collection_[0].device_.gadget_gpx_;
		EffectPropertyX1* cube_epx = cube_collection_[0].device_.epx_;
		GraphicPropertyX4* cube_effect_gpx = cube_collection_[0].device_.effect_gpx_;
		cube_dpx->create_x_ = cube_collection_[0].phandle_->grid_x_;
		cube_dpx->create_y_ = cube_collection_[0].phandle_->grid_y_;
		for (int way = 0; way < 360 / 5; way++)
		{
			cube_dpx->move_angle_deg_ += 5;
			cube_dpx->delay_time_frame_ = 0;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			cube_dpx->delay_time_frame_ = 20;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
		cube_dpx = cube_collection_[1].device_.dpx_;
		cube_gadget_gpx = cube_collection_[1].device_.gadget_gpx_;
		cube_epx = cube_collection_[1].device_.epx_;
		cube_effect_gpx = cube_collection_[1].device_.effect_gpx_;
		cube_dpx->create_x_ = cube_collection_[1].phandle_->grid_x_;
		cube_dpx->create_y_ = cube_collection_[1].phandle_->grid_y_;
		for (int way = 0; way < 360 / 5; way++)
		{
			cube_dpx->move_angle_deg_ += 5;
			cube_dpx->delay_time_frame_ = 0;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
			cube_dpx->delay_time_frame_ = 20;
			NyaDevice::Attack1414(cube_dpx, cube_gadget_gpx, cube_epx, cube_effect_gpx, eOBJECT::TARGET_ATTACK1, eOBJECT::TARGET_ATTACK_EFFECT1);
		}
	}

}

void Target3Bordetella::Draw1(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (count_frame_ % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % 4;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);

	main_.lock_.Run(main_.phandle_);
}

void Target3Bordetella::Draw2(void)
{
	// main 描画
	main_.gpx_->draw_grid_cx_ = main_.phandle_->grid_x_;
	main_.gpx_->draw_grid_cy_ = main_.phandle_->grid_y_;
	if (NyaInput::GetFrameCount() % 20 == 0)
		main_.gpx_->file_div_ = ++main_.gpx_->file_div_ % 4;
	NyaGraphic::Draw(main_.gpx_, eOBJECT::TARGET1);
	// main ロック描画
	main_.lock_.Run(main_.phandle_);

	for (auto& e : cube_collection_)
	{	// cube描画
		if (count_frame_ % CUBE_ANIMATION_INTERVAL_FRAME == 0)
			e.gpx_->file_div_ = ++e.gpx_->file_div_ % e.gpx_->file_.div_total_;
		e.gpx_->draw_grid_cx_ = e.phandle_->grid_x_;
		e.gpx_->draw_grid_cy_ = e.phandle_->grid_y_;
		NyaGraphic::Draw(e.gpx_, eOBJECT::TARGET1);
		// cube ロック描画
		e.lock_.Run(e.phandle_);
	}
	
	// ヘルス表示
	NyaInterface::GetHandleHealth()->valid_ = true;
	if (0 < main_.phandle_->health_) 
		NyaInterface::GetHandleHealth()->value_ = (double)main_.phandle_->health_ / (double)main_.health_max_ * 100.0;
	else
		NyaInterface::GetHandleHealth()->value_ = 0;


	if (main_.phandle_->health_ < 0)
	{	// 爆発描画
		main_.death_epx_->grid_x_ = main_.phandle_->grid_x_;
		main_.death_epx_->grid_y_ = main_.phandle_->grid_y_;
		NyaEffect::Draw(main_.death_epx_, main_.death_gpx_, eOBJECT::TARGET_EFFECT1);
		NyaSound::Play(main_.death_spx_);
		NyaInterface::GetHandleSkill()->AddExp(10000);
	}

}
