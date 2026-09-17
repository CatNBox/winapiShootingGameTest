#include <cstdlib>
#include <ctime>
#include "gameMetaData.h"
#include "sprites.h"
#include "galagaResourceAddr.h"
#include "bullet.h"
#include "bulletPool.h"
#include "galagaFighter.h"

using namespace galagaData;

galagaFighter::galagaFighter(HDC rcvDC, bulletPool* rcvPool)
	:gameObject(galagaResource::imgAddrGalagaFighter, rcvDC)
{
	srand((unsigned int)time(NULL));

	bullets = rcvPool;
	shootTrigger = false;
	shootCoolDown = fighterData::shootCoolDown;

	moveSpeed = fighterData::basicSpeed;

	initPosX(gameSysData::resWidth / 2 - fighterData::witdh / 2);
	initPosY(gameSysData::resHeight - 150 - fighterData::height / 2);
}

galagaFighter::~galagaFighter()
{
}

void galagaFighter::update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		sprHandles->pt.x -= moveSpeed;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		sprHandles->pt.x += moveSpeed;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (shootTrigger == false)
		{
			int randType = 1001 + rand() % 4;
			int bulletInitX = sprHandles->pt.x + fighterData::witdh/2 - basicBullet::Width/2;
			int bulletInitY = sprHandles->pt.y;
			if (bullets->create(bulletType(randType), bulletInitX, bulletInitY, true) == true)
			{
				shootTrigger = true;
				shootCoolDown = fighterData::shootCoolDown;
			}
		}
	}
	if (shootTrigger == true)
	{
		if (shootCoolDown > 0)
		{
			shootCoolDown -= gameSysData::baseGameTick;
		}
		else
		{
			shootTrigger = false;
		}
	}
}

void galagaFighter::draw()
{
	gameObject::draw();
}
