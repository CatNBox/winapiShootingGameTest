#include "sprites.h"
#include "galagaResourceAddr.h"
#include "gameMetaData.h"
#include "uiNumber.h"

uiNumber::uiNumber(HDC rcvDC)
	:gameObject(galagaResource::imgAddrNumberSprite, rcvDC)
{
	isVisible = false;
}

uiNumber::~uiNumber()
{
}

void uiNumber::init(int targetNum, long initX, long initY)
{
	initPos(initX, initY);

	sprOriX = gameSysData::numSprData::oriX[targetNum];
	sprOriY = gameSysData::numSprData::oriY;
	sprWidth = gameSysData::numSprData::width[targetNum];
	sprHeight = gameSysData::numSprData::height;

	isVisible = true;
}

void uiNumber::update()
{
}

void uiNumber::draw()
{
	TransparentBlt(baseDC,
		sprHandles->pt.x,
		sprHandles->pt.y,
		sprWidth,
		sprHeight,
		sprHandles->dc,
		sprOriX, sprOriY,
		sprWidth,
		sprHeight,
		RGB(255, 0, 255));
}

bool uiNumber::getVisible() const
{
	return isVisible;
}

void uiNumber::setVisible(bool rcvBool)
{
	isVisible = rcvBool;
}

void uiNumber::addPosX(int addValue)
{
	sprHandles->pt.x += addValue;
}
