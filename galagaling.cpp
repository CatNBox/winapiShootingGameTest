// 시스템 라이브러리
#include <cstdlib>
#include <ctime>
// 프로젝트 클래스
#include "gameMetaData.h"
#include "sprites.h"
#include "galagaResourceAddr.h"
#include "bullet.h"
#include "bulletPool.h"
#include "galagaling.h"


galagaling::galagaling(HDC rcvDC, bulletPool * rcvPool)
	:gameObject(galagaResource::imgAddrGalagalingCollection, rcvDC)
{
	srand((unsigned int)time(NULL));

	bullets = rcvPool;
	isUsing = false;
}

galagaling::~galagaling()
{
}

void galagaling::init(galagaData::galagaling::bodyType rcvType, long initX, long initY)
{
	// 개체 식별 정보 세팅
	info.activated.galagaType = rcvType;
	initPos(initX, initY);

	const int typeIdx = (int)info.activated.galagaType;

	// 개체의 게임 정보 세팅
	info.activated.moveSpeed = galagaData::galagaling::moveSpeed[typeIdx];
	info.activated.shootTrigger = false;
	info.activated.shootCoolDown = galagaData::galagaling::shootCoolDown;

	// 스프라이트 정보 세팅
	info.activated.animeSpeed = galagaData::galagaling::animeSpeed[typeIdx];
	info.activated.sprOriX = galagaData::galagaling::oriX01[typeIdx];
	info.activated.sprOriY = galagaData::galagaling::oriY[typeIdx];
	info.activated.sprWidth = galagaData::galagaling::width[typeIdx];
	info.activated.sprHeight = galagaData::galagaling::height[typeIdx];

	// 히트박스 정보 세팅
	info.activated.hitboxGapX = galagaData::galagaling::hixboxGapX[typeIdx];
	info.activated.hitboxGapY = galagaData::galagaling::hixboxGapY[typeIdx];
	info.activated.hitboxWidth = galagaData::galagaling::hixboxWidth[typeIdx];
	info.activated.hitboxHeight = galagaData::galagaling::hixboxHeight[typeIdx];

	isUsing = true;
	changeState(galagaData::galagaling::state::normal);
}

void galagaling::update()
{
	// 상태에 따른 업데이트
	if (currState == galagaData::galagaling::state::normal)
	{
		animaIdle();
		chkConflictBullet();
	}
	else if (currState == galagaData::galagaling::state::conflict)
	{
		animaExplosion();
	}
	// 임시이동
	sprHandles->pt.y += info.activated.moveSpeed;
}

void galagaling::draw()
{
	long drawWidth;
	long drawHeight;

	if (currState == galagaData::galagaling::state::normal)
	{
		drawWidth = info.activated.sprWidth / 2;
		drawHeight = info.activated.sprHeight / 2;
	}
	else if (currState == galagaData::galagaling::state::conflict)
	{
		drawWidth = info.activated.sprWidth;
		drawHeight = info.activated.sprHeight;
	}
	else if (currState == galagaData::galagaling::state::conflictEnd)
	{
		return;
	}

	TransparentBlt(baseDC,
		sprHandles->pt.x,
		sprHandles->pt.y,
		drawWidth,
		drawHeight,
		sprHandles->dc,
		info.activated.sprOriX, info.activated.sprOriY,
		info.activated.sprWidth,
		info.activated.sprHeight,
		RGB(255, 0, 255));
}

void galagaling::targetPos(long posX, long posY)
{
	/*info.activated.targetPosX = posX;
	info.activated.targetPosY = posY;*/
}

galagaling * galagaling::getNext() const
{
	return info.next;
}

void galagaling::setNext(galagaling * nextObj)
{
	this->info.next = nextObj;
	if (info.next != nullptr)
	{
		isUsing = false;
	}
}

bool galagaling::chkScreenRangeOver()
{
	if (sprHandles->pt.x < -100 ||
		sprHandles->pt.x > 1124 ||
		sprHandles->pt.y < -100 ||
		sprHandles->pt.y > 869)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool galagaling::chkUsing()
{
	return isUsing;
}

void galagaling::setAvaliable()
{
	isUsing = false;
}

void galagaling::changeState(galagaData::galagaling::state rcvState)
{
	currState = rcvState;
}

galagaData::galagaling::state galagaling::getState() const
{
	return currState;
}

void galagaling::initPosScreenOut()
{
	initPos(-200, -200);
}

void galagaling::applyScore()
{

	switch (info.activated.galagaType)
	{
	case galagaData::galagaling::bodyType::zakoUp:
	case galagaData::galagaling::bodyType::zakoDown:
		addScore((int)galagaData::galagaling::score::zako);
		break;
	case galagaData::galagaling::bodyType::goeiUp:
	case galagaData::galagaling::bodyType::goeiDown:
		addScore((int)galagaData::galagaling::score::goei);
		break;
	case galagaData::galagaling::bodyType::midoriUp:
	case galagaData::galagaling::bodyType::midoriDown:
		addScore((int)galagaData::galagaling::score::midori);
		break;
	default:
		score += 1;
		break;
	}
}

void galagaling::animaIdle()
{
	info.activated.animeSpeed -= gameSysData::baseGameTick;
	if (info.activated.animeSpeed > 0)
	{
		info.activated.sprOriX = galagaData::galagaling::oriX01[(int)info.activated.galagaType];
	}
	else if (info.activated.animeSpeed <= 0 && info.activated.animeSpeed > -160)
	{
		info.activated.sprOriX = galagaData::galagaling::oriX02[(int)info.activated.galagaType];
	}
	else
	{
		info.activated.animeSpeed = galagaData::galagaling::animeSpeed[(int)info.activated.galagaType];
	}
}

void galagaling::animaExplosion()
{
	info.activated.animeSpeed -= gameSysData::baseGameTick;
	if (info.activated.animeSpeed < 0)
	{
		currState = galagaData::galagaling::state::conflictEnd;
		graphicResourceAddress = galagaResource::imgAddrGalagalingCollection;
		initSprite();
	}
	else if (info.activated.animeSpeed <= 64)
	{
		info.activated.sprOriX = galagaData::explosionData::oriX[7];
		info.activated.sprOriY = galagaData::explosionData::oriY[7];
		info.activated.sprWidth = galagaData::explosionData::width[7];
		info.activated.sprHeight = galagaData::explosionData::height[7];
	}
	else if (info.activated.animeSpeed <= 128)
	{
		info.activated.sprOriX = galagaData::explosionData::oriX[6];
		info.activated.sprOriY = galagaData::explosionData::oriY[6];
		info.activated.sprWidth = galagaData::explosionData::width[6];
		info.activated.sprHeight = galagaData::explosionData::height[6];
	}
	else if (info.activated.animeSpeed <= 192)
	{
		info.activated.sprOriX = galagaData::explosionData::oriX[5];
		info.activated.sprOriY = galagaData::explosionData::oriY[5];
		info.activated.sprWidth = galagaData::explosionData::width[5];
		info.activated.sprHeight = galagaData::explosionData::height[5];
	}
	else if (info.activated.animeSpeed <= 256)
	{
		info.activated.sprOriX = galagaData::explosionData::oriX[4];
		info.activated.sprOriY = galagaData::explosionData::oriY[4];
		info.activated.sprWidth = galagaData::explosionData::width[4];
		info.activated.sprHeight = galagaData::explosionData::height[4];
	}
	else if (info.activated.animeSpeed <= 320)
	{
		info.activated.sprOriX = galagaData::explosionData::oriX[3];
		info.activated.sprOriY = galagaData::explosionData::oriY[3];
		info.activated.sprWidth = galagaData::explosionData::width[3];
		info.activated.sprHeight = galagaData::explosionData::height[3];
	}
	else if (info.activated.animeSpeed <= 384)
	{
		info.activated.sprOriX = galagaData::explosionData::oriX[2];
		info.activated.sprOriY = galagaData::explosionData::oriY[2];
		info.activated.sprWidth = galagaData::explosionData::width[2];
		info.activated.sprHeight = galagaData::explosionData::height[2];
	}
	else if (info.activated.animeSpeed <= 448)
	{
		info.activated.sprOriX = galagaData::explosionData::oriX[1];
		info.activated.sprOriY = galagaData::explosionData::oriY[1];
		info.activated.sprWidth = galagaData::explosionData::width[1];
		info.activated.sprHeight = galagaData::explosionData::height[1];
	}
	else if (info.activated.animeSpeed <= 512)
	{
		info.activated.sprOriX = galagaData::explosionData::oriX[0];
		info.activated.sprOriY = galagaData::explosionData::oriY[0];
		info.activated.sprWidth = galagaData::explosionData::width[0];
		info.activated.sprHeight = galagaData::explosionData::height[0];
	}
}

void galagaling::chkConflictBullet()
{
	// ally 탄환과의 충돌체크
	long hitboxX = sprHandles->pt.x + info.activated.hitboxGapX;
	long hitboxY = sprHandles->pt.y + info.activated.hitboxGapY;

	if (bullets->chkConflict(hitboxX,hitboxY,info.activated.hitboxWidth,info.activated.hitboxHeight,true) == true)
	{
		// 충돌하면 상태를 격추로 바꿈 - 업데이트에서 애니메이션 진행
		changeState(galagaData::galagaling::state::conflict);
		info.activated.animeSpeed = 512;
		graphicResourceAddress = galagaResource::imgAddrExplosion;
		initSprite();
		applyScore();
	}

}