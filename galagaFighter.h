#pragma once
#include "gameObject.h"

class bulletPool;

class galagaFighter : public gameObject
{
public:
	galagaFighter(HDC rcvDC, bulletPool* rcvPool);
	~galagaFighter();

	void update();
	void draw();

private:
	long moveSpeed;
	bool shootTrigger;
	int shootCoolDown;
	bulletPool* bullets;
};