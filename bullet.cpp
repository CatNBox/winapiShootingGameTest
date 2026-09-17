#include "gameMetaData.h"
#include "sprites.h"
#include "galagaResourceAddr.h"
#include "bullet.h"

bullet::bullet(HDC rcvDC)
	:gameObject(galagaResource::imgAddrBulletCollection, rcvDC)
{
	isUsing = false;
}

bullet::~bullet()
{
}

void bullet::init(galagaData::bulletType rcvBulType, long initX, long initY, bool ally)
{
	info.activated.bulType = rcvBulType;
	initPos(initX, initY);
	isAlly = ally;

	if ((int)info.activated.bulType > 1000 && (int)info.activated.bulType < 2000)
	{
		// basicBullet
		info.activated.sprOriX = galagaData::basicBullet::OriX;
		info.activated.sprWidth = galagaData::basicBullet::Width;
		info.activated.sprHeight = galagaData::basicBullet::Height;
		info.activated.bulletSpeed = galagaData::basicBullet::basicSpeed;
	}

	switch (info.activated.bulType)
	{
	case galagaData::bulletType::basicRedBullet:
		info.activated.sprOriY = galagaData::basicBullet::redOriY;
		break;
	case galagaData::bulletType::basicGreenBullet:
		info.activated.sprOriY = galagaData::basicBullet::greenOriY;
		break;
	case galagaData::bulletType::basicYellowBullet:
		info.activated.sprOriY = galagaData::basicBullet::yellowOriY;
		break;
	case galagaData::bulletType::basicBlueBullet:
		info.activated.sprOriY = galagaData::basicBullet::blueOriY;
		break;
	default:
		break;
	}

	isUsing = true;
	changeState(galagaData::bulletState::normal);
}

void bullet::update()
{	
	sprHandles->pt.y -= info.activated.bulletSpeed;
}

void bullet::draw()
{
	TransparentBlt(baseDC,
		sprHandles->pt.x,
		sprHandles->pt.y,
		info.activated.sprWidth,
		info.activated.sprHeight,
		sprHandles->dc,
		info.activated.sprOriX, info.activated.sprOriY,
		info.activated.sprWidth,
		info.activated.sprHeight,
		RGB(255, 0, 255));
}

void bullet::targetPos(long posX, long posY)
{
	info.activated.targetPosX = posX;
	info.activated.targetPosY = posY;
}

bullet * bullet::getNext() const
{
	return info.next;
}

void bullet::setNext(bullet* nextObj)
{
	this->info.next = nextObj;
	isUsing = false;
}

bool bullet::chkScreenRangeOver()
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

bool bullet::chkUsing()
{
	return isUsing;
}

void bullet::setAvaliable()
{
	isUsing = false;
}

bool bullet::chkAlly()
{
	return isAlly;
}

bool bullet::chkConflict(long rcvX, long rcvY, long rcvWidth, long rcvHeight)
{
	// 전달받은 히트박스와 자신의 좌표를 비교
	// x, y / x+widht, y / x, y+height / x+width, y+height
	long posX = sprHandles->pt.x;
	long posY = sprHandles->pt.y;
	long posXWidth = posX + info.activated.sprWidth;
	long posYHeight = posY + info.activated.sprHeight;

	long rcvXWidth = rcvX + rcvWidth;
	long rcvYHeight = rcvY + rcvHeight;

	if ((rcvX < posX && rcvXWidth > posX) || (rcvX < posXWidth && rcvXWidth > posXWidth))
	{
		if ((rcvY < posY && rcvYHeight > posY) || (rcvY < posYHeight && rcvYHeight > posYHeight))
		{
			changeState(galagaData::bulletState::conflict);

			return true;
		}
	}
	return false;
}

void bullet::changeState(galagaData::bulletState rcvState)
{
	currState = rcvState;
}

galagaData::bulletState bullet::getState() const
{
	return currState;
}

void bullet::initPosScreenOut()
{
	initPos(-200, -200);
}
