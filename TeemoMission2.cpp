#include "Target2Adeno.h"
#include "Target2Chloroflexi.h"
#include "Target2Ectromelia.h"
#include "Target2Pantoea.h"
#include "Target2Picorna.h"
#include "Target2Polyoma.h"
#include "Target2Spirochaetes.h"
#include "TeemoBack2.h"
#include "TeemoMission2.h"
#include "TeemoTarget.h"
#include "TeemoTargetEx2.h"
#include "UserAI.h"

using namespace HNLIB;


void TeemoMission2::Create(void)
{
	unsigned int ctime = 0;
	//*****************************************************
	// �X�N���[������w�i��BGM���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*****************************************************
	AddBack(new TeemoBack2);

	//*******************************************
	// �^�[�Q�b�g���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//*******************************************
	AddTarget(ctime, ctime + 30, new Target2Pantoea(SCREEN_CENTER_X - 210, 300));
	AddTarget(ctime, ctime + 30, new Target2Pantoea(SCREEN_CENTER_X - 70, 300));
	AddTarget(ctime, ctime + 30, new Target2Pantoea(SCREEN_CENTER_X + 70, 300));
	AddTarget(ctime, ctime + 30, new Target2Pantoea(SCREEN_CENTER_X + 210, 300));

	// ���U��+���E�ړ�+360
	ctime = 3;
	AddTarget(ctime, ctime + 60, new Target2Adeno(150, -100));
	for (int i = 0; i < 8; i++)
	{
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(SCREEN_MAX_X + 150 + 50 * i, SCREEN_MAX_Y - 150, true));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(SCREEN_MAX_X + 150 + 50 * i, SCREEN_MAX_Y - 250, true));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(SCREEN_MAX_X + 150 + 50 * i, SCREEN_MAX_Y - 350, true));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(SCREEN_MAX_X + 150 + 50 * i, SCREEN_MAX_Y - 450, true));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(SCREEN_MAX_X + 150 + 50 * i, SCREEN_MAX_Y - 550, true));
	}
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(520, -50));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(580, -50));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(560, -110));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(580, -240));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(640, -240));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(700, -240));
	ctime = 20;
	AddTarget(ctime, ctime + 60, new Target2Adeno(SCREEN_MAX_X - 150, -100));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(145, -85));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(200, -155));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(200, -210));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(200, -265));
	AddTarget(ctime, ctime + 60, new Target2Chloroflexi(420, -380));
	for (int i = 0; i < 8; i++)
	{
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(-150 - 50 * i, SCREEN_MAX_Y - 150, false));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(-150 - 50 * i, SCREEN_MAX_Y - 250, false));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(-150 - 50 * i, SCREEN_MAX_Y - 350, false));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(-150 - 50 * i, SCREEN_MAX_Y - 450, false));
		AddTarget(ctime + 7, ctime + 60, new Target2Polyoma(-150 - 50 * i, SCREEN_MAX_Y - 550, false));
	}

	// MID-BOSS
	ctime = 43;
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(140, -70));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(190, -70));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(140, -130));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(190, -130));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes( 90, -250));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(140, -250));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(190, -250));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes( 90, -310));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(140, -310));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(190, -310));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes( 90, -370));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(140, -370));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(190, -370));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes( 90, -430));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(140, -430));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(190, -430));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(250, -250));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(250, -310));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(310, -130));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(310, -190));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(310, -250));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(310, -310));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(370, -130));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(370, -190));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(370, -250));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(370, -310));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(440, -130));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(440, -190));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(440, -250));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(440, -310));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(620, -60));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(620, -120));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(620, -180));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(620, -240));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(700, -100));
	AddTarget(ctime, ctime + 60, new Target2Spirochaetes(700, -235));
	AddTarget(ctime + 1, ctime + 60, new Target2Picorna(SCREEN_CENTER_X, -100));

	ctime = 70;
	for (int i = 0; i < 30; i++)
	{
		AddTarget(ctime, ctime + 30, new Target2Ectromelia(SCREEN_CENTER_X - 300, SCREEN_MAX_Y + 150 + 50 * i));
		AddTarget(ctime, ctime + 30, new Target2Ectromelia(SCREEN_CENTER_X - 100, SCREEN_MAX_Y + 150 + 50 * i));
		AddTarget(ctime, ctime + 30, new Target2Ectromelia(SCREEN_CENTER_X + 100, SCREEN_MAX_Y + 150 + 50 * i));
		AddTarget(ctime, ctime + 30, new Target2Ectromelia(SCREEN_CENTER_X + 300, SCREEN_MAX_Y + 150 + 50 * i));
	}
	
	ctime = 100;
	AddTarget(ctime, ctime + 300, new TeemoTargetEx2);

	//**************************************
	// ���[�U�[���q�I�u�W�F�N�g�Ƃ��Ēǉ�
	//**************************************
	AddUser(new UserAi);
}

void TeemoMission2::Delete(void)
{
	ClearBackground();
	ClearTarget();
	ClearUser();
}
