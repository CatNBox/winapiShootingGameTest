#include "sprites.h"
#include "gameObject.h"

int gameObject::score = 0;

gameObject::gameObject(const wchar_t * sprAddr, HDC rcvDC)
	:graphicResourceAddress(sprAddr),baseDC(rcvDC)
{
	sprHandles = new sprites::spriteHandle;
	initSprite();
}

gameObject::~gameObject()
{
}

void gameObject::initSprite()
{
	this->sprHandles->hBmp = (HBITMAP)LoadImage(NULL, graphicResourceAddress, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);
	if (sprHandles->hBmp == NULL)
	{
		MessageBox(NULL, graphicResourceAddress, L"Bitmap loading error.", MB_OK);
		exit(-1);
	}
	GetObject(sprHandles->hBmp, sizeof(BITMAP), &sprHandles->bit);
	sprHandles->dc = CreateCompatibleDC(baseDC);
	sprHandles->hOldbmp = (HBITMAP)SelectObject(sprHandles->dc, sprHandles->hBmp);
}

void gameObject::draw()
{
	TransparentBlt(baseDC,
		sprHandles->pt.x,
		sprHandles->pt.y,
		sprHandles->bit.bmWidth,
		sprHandles->bit.bmHeight,
		sprHandles->dc,
		0, 0,
		sprHandles->bit.bmWidth,
		sprHandles->bit.bmHeight,
		RGB(255, 0, 255));
}

void gameObject::initPosX(LONG posX)
{
	sprHandles->pt.x = posX;
}

void gameObject::initPosY(LONG posY)
{
	sprHandles->pt.y = posY;
}

void gameObject::initPos(LONG posX, LONG posY)
{
	sprHandles->pt.x = posX;
	sprHandles->pt.y = posY;
}

void gameObject::addScore(int rcvScore)
{
	// 카운트 스탑
	if ((score+rcvScore) > 9999999999)
	{
		score = 9999999999;
		return;
	}
	score += rcvScore;
}

int gameObject::getScore() const
{
	return score;
}
