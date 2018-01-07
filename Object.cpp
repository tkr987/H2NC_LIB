#include "DxLib.h"
#include "DefineNH.h"
#include "DesignManager.h"
#include "FpsManager.h"
#include "ImgManager.h"
#include "PosManager.h"
#include "SoundManager.h"
#include "Object.h"

using namespace NH2;

Object::Object(void)
{
	collision_interval_img_ = -1;
	collision_interval_sound_ = -1;
}


Object::~Object(void)
{

}

double Object::Collision(double extension, PosParam1 *pparam)
{
	double hit;

	if (InsideDisplayWindow(extension, pparam)) {
		hit = PosManager::GetHit(pparam);
	} else {
		hit = 0;
	}

	return hit;
}


void Object::CollisionImg(int imgfile, int imgdiv, int interval, PosParam1 *pparam, ImgParam4 *iparam)
{
	if (collision_interval_img_ == -1) {
		if (PosManager::GetHit(pparam) != 0) {
			collision_interval_img_ = 0;
		}
	} else {
		PosManager::GetPosX(pparam, &iparam->pos_cx_);
		PosManager::GetPosY(pparam, &iparam->pos_cy_);
		ImgManager::Draw(imgfile, imgdiv, iparam);
		if (PosManager::GetHit(pparam) != 0) {
			collision_interval_img_ = 0;
		}
		else {
			collision_interval_img_++;
		}
		if (interval <= collision_interval_img_)
			collision_interval_img_ = -1;
	}
}


void Object::CollisionSound(int soundfile, int interval, PosParam1 *pparam)
{
	if (collision_interval_sound_ == -1) {
		if (PosManager::GetHit(pparam) != 0) {
			SoundManager::Play(soundfile, DX_PLAYTYPE_BACK);
			collision_interval_sound_ = 0;
		}
	}
	else {
		if (PosManager::GetHit(pparam) != 0) {
			collision_interval_sound_ = 0;
		}
		else {
			collision_interval_sound_++;
		}
		if (interval <= collision_interval_sound_)
			collision_interval_sound_ = -1;
	}

}

void Object::Draw(unsigned int imgfile, unsigned int imgdiv, PosParam1 *pparam, ImgParam4 *iparam)
{
	PosManager::GetPosX(pparam, &iparam->pos_cx_);
	PosManager::GetPosY(pparam, &iparam->pos_cy_);
	ImgManager::Draw(imgfile, imgdiv, iparam);
}


void Object::GetPos(int *x, int *y, PosParam1 *pparam)
{
	if (x != NULL)
		PosManager::GetPosX(pparam, x);
	if (y != NULL)
		PosManager::GetPosY(pparam, y);
}

void Object::GetPos(double *x, double *y, PosParam1 *pparam)
{
	if (x != NULL)
		PosManager::GetPosX(pparam, x);
	if (y != NULL)
		PosManager::GetPosY(pparam, y);
}

bool Object::InsideDisplayWindow(double extension, PosParam1 *pparam) {
	double x, y;
	const int DISPLAY_MIN_X = 160;
	const int DISPLAY_MIN_Y = 32;
	const int DISPLAY_MAX_X = 610;
	const int DISPLAY_MAX_Y = 575;

	PosManager::GetPosX(pparam, &x);
	PosManager::GetPosY(pparam, &y);
	if (x < DISPLAY_MIN_X - extension || DISPLAY_MAX_X + extension < x) {
		return false;
	}
	else if (y < DISPLAY_MIN_Y - extension || DISPLAY_MAX_Y + extension < y) {
		return false;
	}

	return true;
}
