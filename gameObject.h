#pragma once
#include <Windows.h>

namespace sprites
{
	struct spriteHandle;
}

class gameObject
{
public:
	gameObject(const wchar_t * sprAddr, HDC rcvDC);
	virtual ~gameObject();

	void initSprite();
	virtual void draw();
	virtual void update() = 0;

	void initPosX(LONG posX);
	void initPosY(LONG posY);
	void initPos(LONG posX, LONG posY);

	void addScore(int rcvScore = 0);
	int getScore() const;

protected:
	sprites::spriteHandle *sprHandles;
	const wchar_t* graphicResourceAddress;
	HDC baseDC;

	// Ä­½ºÅä 9999999999
	static int score;
};